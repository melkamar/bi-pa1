/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 23. listopad 2012, 10:11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WRONG_INPUT "Nespravny vstup.\n"
#define WORD_NOT_FOUND "Slovo '%s' nenalezeno.\n"

/*
 * 
 */

/*
 * type: 0 - criscross
 *       1 - task
 */
int readRebus(char*** outRebus, int* x, int* y) {
    int horzResizeC = 2;
    int vertResizeC = 2;

    int horzRead = 0;
    int vertRead = 0;

    int horzSize = 0;
    int vertSize = 0;
    int horzMax = 0;

    int endLineCount = 0;
    char readChar;

    int i;

    char ** rebus = (char**) malloc(vertResizeC * sizeof (*rebus));
    vertSize = vertResizeC;
    vertResizeC *= 2;

    *rebus = (char*) malloc(horzResizeC * sizeof (**rebus));
    horzSize = horzResizeC;
    horzResizeC *= 2;

    printf("Zadejte osmismerku:\n");

    while (1) {
        while (scanf("%c", &readChar) == 1) {
            if (readChar == 13) continue;
            if (readChar == '\n') {
                //printf("\\n READ!\n");
                if (vertRead == 0) {
                    if (horzRead == 0) { // No char before LF, wrong input
                        //printf("RET 1\n");
                        return 0;
                    }
                    horzMax = horzRead;
                    for (i = 1; i < vertSize; i++)
                        rebus[i] = (char*) malloc(horzResizeC * sizeof (**rebus));
                } else if (horzRead != horzMax && horzRead != 0) { // Length != lengths of other lines
                    //printf("RET 2. horzRead==%d, horzMax==%d\n", horzRead, horzMax);
                    return 0;
                }


                endLineCount++;
                vertRead++;

                if (horzRead > horzMax) horzMax = horzRead;
                horzRead = 0;

                break;
            } else endLineCount = 0;

            //printf("Char read. %c\n", readChar);

            if (horzRead == horzSize) {
                *rebus = (char*) realloc(*rebus, horzResizeC * sizeof (**rebus));
                horzSize = horzResizeC;
                horzResizeC *= 2;
                horzMax = horzSize;
            }

            if (vertRead == vertSize) {
                rebus = (char**) realloc(rebus, vertResizeC * sizeof (*rebus));
                vertSize = vertResizeC;
                vertResizeC *= 2;

                for (i = vertRead; i < vertSize; i++) {
                    rebus[i] = (char*) malloc(horzResizeC * sizeof (**rebus));
                }
            }

            rebus[vertRead][horzRead++] = readChar;

            if (abs(readChar - 'a') > 'z' - 'a' && readChar != '.' && readChar != '\n') {
                return 0;
            }
        }

        if (feof(stdin)) {
            return 0;
        }

        if (endLineCount > 1) // Empty line
            break;
    }

    vertRead--;

    *outRebus = rebus;
    *x = horzMax;
    *y = vertRead;
    return 1;
}

int readTask(char*** outTask, int* y) {
    int horzResizeC = 2;
    int vertResizeC = 2;

    int horzRead = 0;
    int vertRead = 0;

    int horzSize = 0;
    int vertSize = 0;

    int endLineCount = 0;
    char readChar;

    char ** task = (char**) malloc(vertResizeC * sizeof (*task));
    vertSize = vertResizeC;
    vertResizeC *= 2;


    while (1) {
        while (scanf("%c", &readChar) == 1) {
            if (readChar == 13) continue;
            if (readChar == '\n') { // If newline
                if (horzRead == 0) { // If nothing read and newline, EOF.
                    *outTask = NULL;
                    *y = 0;
                    return 1;
                }

                task[vertRead][horzRead] = 0; // Ending $0 char

                endLineCount++;
                vertRead++;
                horzRead = 0;
                horzSize = 0;
                horzResizeC = 2;

                if (vertRead == vertSize) {
                    task = (char**) realloc(task, vertResizeC * sizeof (*task));
                    vertSize = vertResizeC;
                    vertResizeC *= 2;
                }

                break; // Dont parse \n any longer.
            } else endLineCount = 0; // If not \n, then empty "buffer" of newlines


            if (horzRead + 1 >= horzSize) {
                if (horzRead == 0) task[vertRead] = (char*) malloc(horzResizeC * sizeof (char*));
                else task[vertRead] = (char*) realloc(task[vertRead], horzResizeC * sizeof (char*));
                horzSize = horzResizeC;
                horzResizeC *= 2;
            }

            task[vertRead][horzRead++] = readChar;

            if (abs(readChar - 'a') > 'z' - 'a' && readChar != '\n')
                return 0;

        }

        if (vertRead == 0) {
            *outTask = NULL;
            *y = 0;
            return 1;
        }

        if (endLineCount > 1) { // Empty line
            break;
        }

        if (feof(stdin)) {
            vertRead++; // Inc linecount to not omit last line
            if (readChar != '\n') {
                task[vertRead - 1][horzRead] = 0; // Ending $0 char
                vertRead++;
            }
            break;
        }
    }

    vertRead--;

    *outTask = task;
    *y = vertRead;

    return 1;
}

int findRight(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find R : %s\n", task[taskIndex]);

    if (findX + len > rebusW) return 0;

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY][findX + i]) {
            return 0;
        }
    }

    return 1;
}

int findRightDown(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find RD: %s\n", task[taskIndex]);

    if (findX + len > rebusW || findY + len > rebusH) return 0;

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY + i][findX + i]) {
            return 0;
        }
    }

    return 1;
}

int findDown(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find  D: %s\n", task[taskIndex]);

    if (findY + len > rebusH) return 0;

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY + i][findX]) {
            return 0;
        }
    }

    return 1;
}

int findLeftDown(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find LD: %s\n", task[taskIndex]);

    if (findX - len + 1 < 0 || findY + len > rebusH) return 0;

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY + i][findX - i]) {
            return 0;
        }
    }

    return 1;
}

int findLeft(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find L : %s\n", task[taskIndex]);

    if (findX - len + 1 < 0) {
        //printf("    > findX-len=%d (f=%d, l=%d)\n", findX - len, findX, len);
        return 0;
    }

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY][findX - i]) {
            //printf("i=%d, %c != %c\n", task[taskIndex][i], rebus[findY][findX - i]);
            return 0;
        }
    }

    return 1;
}

int findLeftUp(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find LU: %s\n", task[taskIndex]);

    if (findX - len + 1 < 0 || findY - len + 1 < 0) return 0;

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY - i][findX - i]) {
            return 0;
        }
    }

    return 1;
}

int findUp(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find  U: %s\n", task[taskIndex]);

    if (findY - len + 1 < 0) return 0;

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY - i][findX]) {
            return 0;
        }
    }

    return 1;
}

int findRightUp(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, int findX, int findY) {
    int i;
    int len = strlen(task[taskIndex]);

    //printf("  > Find RU: %s\n", task[taskIndex]);

    if (findX + len > rebusW || findY - len + 1 < 0) return 0;

    //printf("    > [%d, %d]\n", findX, findY);

    for (i = 0; i < len; i++) {
        if (task[taskIndex][i] != rebus[findY - i][findX + i]) {
            return 0;
        }
    }

    return 1;
}

int findWord(char **rebus, char **task, int taskIndex, int rebusW, int rebusH, char **foundMap) {
    int x, y, i;
    int wordFound = 0;
    int len = strlen(task[taskIndex]);

    //printf("FIND WORD: %s\n", task[taskIndex]);

    for (y = 0; y < rebusH; y++) {
        for (x = 0; x < rebusW; x++) {
            if (findRight(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find right, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y][x + i] = 0;
                wordFound = 1;
            } 
            
            if (findRightDown(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find right-down, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y + i][x + i] = 0;
                wordFound = 1;
            } 
            
            if (findDown(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find down, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y + i][x] = 0;
                wordFound = 1;
            } 
            
            if (findLeftDown(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find left-down, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y + i][x - i] = 0;
                wordFound = 1;
            } 
            
            if (findLeft(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find left, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y][x - i] = 0;
                wordFound = 1;
            } 
            
            if (findLeftUp(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find left-up, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y - i][x - i] = 0;
                wordFound = 1;
            } 
            
            if (findUp(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find up, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y - i][x] = 0;
                wordFound = 1;
            } 
            
            if (findRightUp(rebus, task, taskIndex, rebusW, rebusH, x, y)) {
                //printf("Find right-up, [%d;%d]: FOUND\n\n", y, x);
                for (i = 0; i < len; i++)
                    foundMap[y - i][x + i] = 0;
                wordFound = 1;
            }
        }
    }

    return wordFound;
}

int main(int argc, char** argv) {

    char ** rebus;
    char ** task;
    char ** foundMap;

    int x, i, j;
    int rebusXLen, rebusYLen, taskLen;

    if (!readRebus(&rebus, &rebusXLen, &rebusYLen)) {
        printf(WRONG_INPUT);
        return 0;
    }

    if (!readTask(&task, &taskLen)) {
        printf(WRONG_INPUT);
        return 0;
    }

    //printf("Mallocing map. rebusY=%d, rebusX=%d\n", rebusYLen, rebusXLen);
    foundMap = (char**) malloc(rebusYLen * sizeof (*foundMap));
    for (i = 0; i < rebusYLen; i++)
        foundMap[i] = (char*) malloc(rebusXLen * sizeof (**foundMap));

    //printf("Filling map.\n");
    for (i = 0; i < rebusXLen; i++)
        for (j = 0; j < rebusYLen; j++)
            foundMap[j][i] = 1;


    /*
    printf("\nREBUS:\n");
    for (j = 0; j < rebusYLen; j++) {
        for (i = 0; i < rebusXLen; i++) {
            printf("%c", rebus[j][i]);
        }
        printf("\n");
    }

    printf("\nTASK(len=%d):\n", taskLen);
    for (i = 0; i < taskLen; i++) {
        printf("%s\n", task[i]);
    }
     * */

    for (i = 0; i < taskLen; i++)
        if (!findWord(rebus, task, i, rebusXLen, rebusYLen, foundMap)) {
            printf(WORD_NOT_FOUND, task[i]);
            return 0;
        }

    //printf("\nFOUND MAP:\n");
    x = 0;
    printf("Vysledek:\n");
    for (j = 0; j < rebusYLen; j++) {
        for (i = 0; i < rebusXLen; i++) {
            if (foundMap[j][i] && rebus[j][i] != '.') {
                printf("%c", rebus[j][i]);
                if (++x % 60 == 0) printf("\n");
            }
        }

    }

    if (x % 60 != 0)
        printf("\n");

    for (j = 0; j < rebusYLen; j++) {
        free(rebus[j]);
        free(foundMap[j]);
    }
    free(rebus);
    free(foundMap);

    for (j = 0; j < taskLen; j++)
        free(task[j]);
    free(task);

    return (EXIT_SUCCESS);
}

