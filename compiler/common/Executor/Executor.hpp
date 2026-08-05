#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <vector>
#include <string>
#include <map>
#include "../IR/IRGenerator.hpp"

class Executor {
public:
    static bool execute(const std::vector<TACInstruction>& instructions);
};

#endif // EXECUTOR_HPP
