.
. Convert a two-digit string to a number and store the number in
. register A.
.
PROG02   START   1000
FIRST    CLEAR   A
         LDX     #0
         LDCH    STRING,X
         SUB     ZERO
         MUL     #10
         RMO     A,S
         CLEAR   A
         LDX     #1
         LDCH    STRING,X
         SUB     ZERO
         ADDR    S,A
ZERO     WORD    48
STRING   RESB    2
         END     FIRST
