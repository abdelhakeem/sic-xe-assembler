.
. Convert a string to uppercase.
.
PROG03   START   1000
FIRST    CLEAR   X
LOOP     LDCH    STR1,X
         COMP    SMLA              SKIP ALL BUT LOWERCASE LETTERS
         JLT     SKIP
         COMP    SMLZ
         JGT     SKIP
         SUB     DIFF              CONVERT TO UPPERCASE
SKIP     STCH    STR2,X
         COMP    #0
         JEQ     NULL              STOP AFTER NULL CHARACTER
         TIX     LEN
         JLT     LOOP
NULL     CLEAR   A                 DUMMY OPERATION
SMLA     WORD    97
SMLZ     WORD    122
DIFF     WORD    32
LEN      WORD    32
STR1     RESB    32
STR2     RESB    32
         END     FIRST
