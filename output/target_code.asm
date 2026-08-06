.DATA
.CODE
main:
  LOAD R1, "Hello, World!"
  PRINT R1
  MOV R1, 5
  STORE R1, a
  MOV R1, 10
  STORE R1, b
  LOAD R1, 5
  LOAD R2, 10
  ADD R1, R2
  STORE R1, t0
  MOV R1, t0
  STORE R1, sum
  LOAD R1, "Sum: "
  PRINT R1
  LOAD R1, t0
  PRINT R1
  LOAD R1, 0
  RET
  LOAD R1, 0
  RET
