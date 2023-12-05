/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/*--------------------------------------------------------------------*/

#include <stdio.h>

int main() {
    /* create and open file dataB */
    char *names = "Nora and Teddy";
    FILE *psFile;
    psFile = fopen("dataB", "w");

    /* put names into file */
    for (int i = 0; i < strlen(names); i++) {
        fprintf(psFile, "&c", names[i]);
    }
    fprintf(psFile, "%c", '\0'); /* terminating null byte */

    /* fill remaining buffer */
    for (int i = 0; i < (48 - strlen(names) -1); i++) {
        fprintf(psFile, "%c", '\0');
    }

}
