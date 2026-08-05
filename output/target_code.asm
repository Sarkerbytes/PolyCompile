.DATA
.CODE
main:
  MOV R1, 3
  STORE R1, day
  LOAD R1, 3
  LOAD R2, 1
  CMP R1, R2
  STORE R1, t0
  LOAD R1, t0
  CMP R1, 0
  JMP_NE L1
  LOAD R1, day
  LOAD R2, 2
  CMP R1, R2
  STORE R1, t1
  LOAD R1, t1
  CMP R1, 0
  JMP_NE L2
  LOAD R1, day
  LOAD R2, 3
  CMP R1, R2
  STORE R1, t2
  LOAD R1, t2
  CMP R1, 0
  JMP_NE L3
  LOAD R1, day
  LOAD R2, 4
  CMP R1, R2
  STORE R1, t3
  LOAD R1, t3
  CMP R1, 0
  JMP_NE L4
  LOAD R1, day
  LOAD R2, 5
  CMP R1, R2
  STORE R1, t4
  LOAD R1, t4
  CMP R1, 0
  JMP_NE L5
  LOAD R1, day
  LOAD R2, 6
  CMP R1, R2
  STORE R1, t5
  LOAD R1, t5
  CMP R1, 0
  JMP_NE L6
  LOAD R1, day
  LOAD R2, 7
  CMP R1, R2
  STORE R1, t6
  LOAD R1, t6
  CMP R1, 0
  JMP_NE L7
  JMP L8
L1:
  LOAD R1, "Monday\n"
  PRINT R1
  JMP L0
L2:
  LOAD R1, "Tuesday\n"
  PRINT R1
  JMP L0
L3:
  LOAD R1, "Wednesday\n"
  PRINT R1
  JMP L0
L4:
  LOAD R1, "Thursday\n"
  PRINT R1
  JMP L0
L5:
  LOAD R1, "Friday\n"
  PRINT R1
  JMP L0
L6:
  LOAD R1, "Saturday\n"
  PRINT R1
  JMP L0
L7:
  LOAD R1, "Sunday\n"
  PRINT R1
  JMP L0
L8:
  LOAD R1, "Invalid Input\n"
  PRINT R1
  JMP L0
L0:
  LOAD R1, 0
  RET
  LOAD R1, 0
  RET
