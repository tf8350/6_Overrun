/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/*--------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

int main() {
    /* create and open file dataB */
    size_t i;
    char *names = "Nora and Teddy";
    FILE *psFile;
    psFile = fopen("dataB", "w");

    /* put names into file */
    for (i = 0; i < strlen(names); i++) {
        fprintf(psFile, "%c", names[i]);
    }
    fprintf(psFile, "%c", '\0'); /* terminating null byte */

    /* fill remaining buffer */
    for (i = 0; i < (48 - strlen(names) -1); i++) {
        fprintf(psFile, "%c", '\0');
    }

    return 0;
}
