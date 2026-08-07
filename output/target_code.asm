.DATA
.CODE
main:
  LOAD R1, "Hello, World!"
  PRINT R1
  MOV R1, 10
  STORE R1, x
  MOV R1, 20
  STORE R1, y
  LOAD R1, 10
  LOAD R2, 20
  ADD R1, R2
  STORE R1, t0
  MOV R1, t0
  STORE R1, result
  LOAD R1, "Result = "
  PRINT R1
  LOAD R1, t0
  PRINT R1
  LOAD R1, 0
  RET
  LOAD R1, 0
  RET
