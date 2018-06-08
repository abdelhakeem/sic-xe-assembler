.
. Set ALPHA equal to 4 * BETA + 3 * GAMMA.
.
PROG01   START   1000
FIRST    LDA     #3
         MUL     GAMMA
         RMO     A,S
         LDA     #4
         MUL     BETA
         ADDR    S,A
         STA     ALPHA
ALPHA    RESW    1
BETA     RESW    1
GAMMA    RESW    1
         END     FIRST
