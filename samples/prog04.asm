.
. Implement the bubble sort algorithm to sort characters in a string.
.
PROG04   START   1000
FIRST    CLEAR   X
SORT     LDCH    STR,X
         COMP    #0
         JEQ     NULL              STOP AFTER NULL CHARACTER
         STA     CHR
         STX     IDX
INNER    LDCH    STR,X
         COMP    #0
         JEQ     ENDINNR
         COMP    CHR
         JLT     SWAP
         J       NEXT
SWAP     RMO     A,S
         LDA     CHR
         STCH    STR,X
         RMO     S,A
         STA     CHR
         RMO     X,T
         LDX     IDX
         STCH    STR,X
         RMO     T,X
NEXT     TIX     LEN
         JLT     INNER
ENDINNR  LDX     IDX
         TIX     LEN
         JLT     SORT
NULL     CLEAR   A                 DUMMY OPERATION
LEN      WORD    32
STR      RESB    32
IDX      RESW    1
CHR      RESW    1
         END     FIRST
