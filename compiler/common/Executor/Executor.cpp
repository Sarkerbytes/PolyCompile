#include "Executor.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <cstdlib>
#include <sstream>
#include <cctype>

struct Value {
    enum Type { INT, FLOAT, STRING } type;
    long long intVal;
    double floatVal;
    std::string strVal;

    Value() : type(INT), intVal(0), floatVal(0.0), strVal("") {}
    Value(long long v) : type(INT), intVal(v), floatVal(static_cast<double>(v)), strVal("") {}
    Value(double v) : type(FLOAT), intVal(static_cast<long long>(v)), floatVal(v), strVal("") {}
    Value(const std::string& s) : type(STRING), intVal(0), floatVal(0.0), strVal(s) {}

    std::string toString() const {
        if (type == STRING) return strVal;
        std::stringstream ss;
        if (type == FLOAT) ss << floatVal;
        else ss << intVal;
        return ss.str();
    }
};

static bool isNum(const std::string& str) {
    if (str.empty()) return false;
    size_t start = (str[0] == '-' || str[0] == '+') ? 1 : 0;
    if (start >= str.size()) return false;
    bool hasDot = false;
    for (size_t i = start; i < str.size(); ++i) {
        if (str[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

static int countSpecifiers(const std::string& s) {
    int count = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '%') {
            if (i + 1 < s.size()) {
                if (s[i+1] == '%') {
                    i++;
                    continue;
                }
                size_t j = i + 1;
                while (j < s.size() && (std::isdigit(s[j]) || s[j] == '.' || s[j] == '-' || s[j] == '+')) {
                    j++;
                }
                if (j < s.size() && (s[j] == 'd' || s[j] == 'f' || s[j] == 's' || s[j] == 'c')) {
                    count++;
                    i = j;
                }
            }
        }
    }
    return count;
}

static std::string formatString(const std::string& fmt, const std::vector<std::string>& args) {
    std::string result;
    size_t argIdx = 0;
    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] == '%') {
            if (i + 1 < fmt.size()) {
                if (fmt[i+1] == '%') {
                    result += '%';
                    i++;
                    continue;
                }
                size_t j = i + 1;
                std::string spec;
                while (j < fmt.size() && (std::isdigit(fmt[j]) || fmt[j] == '.' || fmt[j] == '-' || fmt[j] == '+')) {
                    spec += fmt[j];
                    j++;
                }
                if (j < fmt.size() && (fmt[j] == 'd' || fmt[j] == 'f' || fmt[j] == 's' || fmt[j] == 'c')) {
                    char type = fmt[j];
                    if (argIdx < args.size()) {
                        std::string valStr = args[argIdx++];
                        if (type == 'f' && spec.find('.') != std::string::npos) {
                            size_t dot = spec.find('.');
                            int precision = 0;
                            if (dot + 1 < spec.size() && std::isdigit(spec[dot+1])) {
                                precision = spec[dot+1] - '0';
                            }
                            double val = std::atof(valStr.c_str());
                            char buf[64];
                            std::string fmtStr = "%." + std::to_string(precision) + "f";
                            sprintf(buf, fmtStr.c_str(), val);
                            result += buf;
                        } else {
                            result += valStr;
                        }
                    } else {
                        result += "%" + spec + type;
                    }
                    i = j;
                } else {
                    result += fmt[i];
                }
            } else {
                result += fmt[i];
            }
        } else {
            result += fmt[i];
        }
    }
    return result;
}

static Value evalOperand(const std::string& opStr, const std::map<std::string, Value>& localFrame, const std::map<std::string, Value>& globalFrame) {
    if (opStr.empty()) return Value((long long)0);
    if (opStr.size() >= 2 && opStr.front() == '"' && opStr.back() == '"') {
        std::string unquoted = opStr.substr(1, opStr.size() - 2);
        std::string processed;
        for (size_t i = 0; i < unquoted.size(); ++i) {
            if (unquoted[i] == '\\' && i + 1 < unquoted.size() && unquoted[i+1] == 'n') {
                processed += '\n';
                ++i;
            } else {
                processed += unquoted[i];
            }
        }
        return Value(processed);
    }
    if (opStr.size() >= 2 && opStr.front() == '\'' && opStr.back() == '\'') {
        std::string unquoted = opStr.substr(1, opStr.size() - 2);
        if (unquoted == "\\n") return Value("\n");
        if (unquoted == "\\t") return Value("\t");
        return Value(unquoted);
    }
    if (isNum(opStr)) {
        if (opStr.find('.') != std::string::npos) {
            return Value(std::atof(opStr.c_str()));
        } else {
            return Value(std::atoll(opStr.c_str()));
        }
    }
    auto it = localFrame.find(opStr);
    if (it != localFrame.end()) {
        return it->second;
    }
    auto itg = globalFrame.find(opStr);
    if (itg != globalFrame.end()) {
        return itg->second;
    }
    return Value((long long)0);
}

bool Executor::execute(const std::vector<TACInstruction>& instructions) {
    std::vector<std::map<std::string, Value>> callStack;
    callStack.push_back(std::map<std::string, Value>()); 

    std::map<std::string, size_t> labels;
    std::vector<std::string> callParams;
    std::vector<std::string> callTargets; 
    std::string pendingFormat;
    int expectedArgs = 0;
    std::vector<std::string> formatArgs;

    for (size_t i = 0; i < instructions.size(); ++i) {
        if (instructions[i].op == TACOp::LABEL) {
            labels[instructions[i].result] = i;
        }
    }

    std::vector<size_t> returnAddresses;
    size_t pc = 0;
    if (labels.find("main") != labels.end()) {
        pc = labels["main"];
    }

    while (pc < instructions.size()) {
        const auto& inst = instructions[pc];
        auto& currentFrame = callStack.back();
        auto& globalFrame = callStack.front();

        switch (inst.op) {
            case TACOp::LABEL:
                break;
            case TACOp::ASSIGN: {
                Value val = evalOperand(inst.arg1, currentFrame, globalFrame);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = val;
                } else {
                    currentFrame[inst.result] = val;
                }
                break;
            }
            case TACOp::ADD: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res;
                if (v1.type == Value::FLOAT || v2.type == Value::FLOAT) {
                    res = Value(v1.floatVal + v2.floatVal);
                } else {
                    res = Value(v1.intVal + v2.intVal);
                }
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::SUB: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res;
                if (v1.type == Value::FLOAT || v2.type == Value::FLOAT) {
                    res = Value(v1.floatVal - v2.floatVal);
                } else {
                    res = Value(v1.intVal - v2.intVal);
                }
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::MUL: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res;
                if (v1.type == Value::FLOAT || v2.type == Value::FLOAT) {
                    res = Value(v1.floatVal * v2.floatVal);
                } else {
                    res = Value(v1.intVal * v2.intVal);
                }
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::DIV: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                double divisor = v2.type == Value::FLOAT ? v2.floatVal : v2.intVal;
                if (divisor == 0) {
                    std::cerr << "Runtime Error: Division by zero!" << std::endl;
                    return false;
                }
                Value res;
                if (v1.type == Value::FLOAT || v2.type == Value::FLOAT) {
                    res = Value(v1.floatVal / divisor);
                } else {
                    res = Value(v1.intVal / static_cast<long long>(divisor));
                }
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::MOD: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                if (v2.intVal == 0) {
                    std::cerr << "Runtime Error: Modulo by zero!" << std::endl;
                    return false;
                }
                Value res = Value(v1.intVal % v2.intVal);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::CMP_EQ: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res = Value((long long)(v1.type == Value::STRING ? v1.strVal == v2.strVal : v1.intVal == v2.intVal) ? 1LL : 0LL);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::CMP_NE: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res = Value((long long)(v1.type == Value::STRING ? v1.strVal != v2.strVal : v1.intVal != v2.intVal) ? 1LL : 0LL);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::CMP_LT: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res = Value((v1.intVal < v2.intVal) ? 1LL : 0LL);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::CMP_GT: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res = Value((v1.intVal > v2.intVal) ? 1LL : 0LL);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::CMP_LE: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res = Value((v1.intVal <= v2.intVal) ? 1LL : 0LL);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::CMP_GE: {
                Value v1 = evalOperand(inst.arg1, currentFrame, globalFrame);
                Value v2 = evalOperand(inst.arg2, currentFrame, globalFrame);
                Value res = Value((v1.intVal >= v2.intVal) ? 1LL : 0LL);
                if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                    globalFrame[inst.result] = res;
                } else {
                    currentFrame[inst.result] = res;
                }
                break;
            }
            case TACOp::GOTO: {
                if (labels.find(inst.result) != labels.end()) {
                    pc = labels[inst.result];
                    continue;
                }
                break;
            }
            case TACOp::IF_FALSE_GOTO: {
                Value cond = evalOperand(inst.arg1, currentFrame, globalFrame);
                if (cond.intVal == 0 && labels.find(inst.result) != labels.end()) {
                    pc = labels[inst.result];
                    continue;
                }
                break;
            }
            case TACOp::IF_TRUE_GOTO: {
                Value cond = evalOperand(inst.arg1, currentFrame, globalFrame);
                if (cond.intVal != 0 && labels.find(inst.result) != labels.end()) {
                    pc = labels[inst.result];
                    continue;
                }
                break;
            }
            case TACOp::PARAM: {
                callParams.push_back(inst.arg1);
                break;
            }
            case TACOp::CALL: {
                if (labels.find(inst.arg1) != labels.end()) {
                    int numArgs = std::atoi(inst.arg2.c_str());
                    std::vector<Value> evaluatedArgs;
                    for (int a = 0; a < numArgs; ++a) {
                        if (!callParams.empty()) {
                            std::string paramName = callParams[callParams.size() - numArgs + a];
                            evaluatedArgs.push_back(evalOperand(paramName, currentFrame, globalFrame));
                        }
                    }
                    for (int a = 0; a < numArgs; ++a) {
                        if (!callParams.empty()) callParams.pop_back();
                    }

                    std::map<std::string, Value> newFrame;
                    for (size_t a = 0; a < evaluatedArgs.size(); ++a) {
                        std::stringstream ss;
                        ss << "__param_" << a << "__";
                        newFrame[ss.str()] = evaluatedArgs[a];
                    }

                    callTargets.push_back(inst.result);
                    returnAddresses.push_back(pc + 1);
                    callStack.push_back(newFrame);
                    pc = labels[inst.arg1];
                    continue;
                }
                break;
            }
            case TACOp::RETURN: {
                Value retVal;
                if (!inst.arg1.empty()) {
                    retVal = evalOperand(inst.arg1, currentFrame, globalFrame);
                }
                if (callStack.size() > 1) {
                    callStack.pop_back();
                    std::string target = callTargets.back();
                    callTargets.pop_back();

                    if (!target.empty()) {
                        callStack.back()[target] = retVal;
                    }
                    pc = returnAddresses.back();
                    returnAddresses.pop_back();
                    continue;
                } else {
                    std::cout << "\nProgram exited successfully.\n";
                    return true;
                }
                break;
            }
            case TACOp::READ: {
                std::string inputStr;
                if (std::cin >> inputStr) {
                    Value val = evalOperand(inputStr, currentFrame, globalFrame);
                    if (callStack.size() > 1 && globalFrame.count(inst.result) > 0) {
                        globalFrame[inst.result] = val;
                    } else {
                        currentFrame[inst.result] = val;
                    }
                }
                break;
            }
            case TACOp::PRINT: {
                Value v = evalOperand(inst.arg1, currentFrame, globalFrame);
                std::string valStr = v.toString();
                if (expectedArgs > 0) {
                    formatArgs.push_back(valStr);
                    expectedArgs--;
                    if (expectedArgs == 0) {
                        std::cout << formatString(pendingFormat, formatArgs);
                    }
                } else {
                    int specs = countSpecifiers(valStr);
                    if (specs > 0) {
                        pendingFormat = valStr;
                        expectedArgs = specs;
                        formatArgs.clear();
                    } else {
                        std::cout << valStr;
                    }
                }
                break;
            }
            default:
                break;
        }
        pc++;
    }

    std::cout << "\nProgram exited successfully.\n";
    return true;
}
