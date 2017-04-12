/* 
 * File:   main.c
 * Author: Magicmaster
 *
 * Created on 27. listopad 2012, 14:31
 * 
 * 
 * TODO
 *   vertFillWord
 *   recursive fill
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WRONG_INPUT "Nespravny vstup.\n"
#define HORIZONTAL 0
#define VERTICAL 1

#define HORZ_START 0
#define VERT_START 1
#define HORZ_FILLED 2
#define VERT_FILLED 3

typedef struct TPos {
    int x;
    int y;
} TSTARTPOS;

int verbose = 0;

TSTARTPOS *startingPositions; // Holds all positions where words start
int startingPositionsCount;

int solutionsCount = 0;
char ** lastSolution;


// -----------------------------------------------------------------------------

void printIndent(int level) {
    int i;
    for (i = 0; i < level * 2; i++)
        if (i % 2) printf(" ");
        else printf("|");
}

void printCrossword(char **field, int xLen, int yLen, int level) {
    int i, j;


    for (j = 0; j < yLen; j++) {
        printIndent(level);
        for (i = 0; i < xLen; i++) {
            if (field[j][i] == ' ')
                printf("#");
            else printf("%c", field[j][i]);
        }
        printf("\n");
    }

    printIndent(level);
    printf("\n");
}

void printMap(int **map, int xLen, int yLen, int level) {
    int i, j;

    for (j = 0; j < yLen; j++) {
        printIndent(level);
        for (i = 0; i < xLen; i++) {
            printf("%3d", map[j][i]);
        }
        printf("\n");
    }

    printIndent(level);
    printf("\n");
}

void printWordsLeft(int maxWordLen, int *wordOfLengthCount,
        int ** wordOfLengthOccur, char ***words, int level) {
    int i, j;

    printIndent(level);
    printf("REMAINING WORDS:\n");

    for (i = 0; i < maxWordLen; i++) {
        for (j = 0; j < wordOfLengthCount[i]; j++) {
            printIndent(level);
            printf("%10s : %dx\n", words[i][j], wordOfLengthOccur[i][j]);
        }
    }
}

// -----------------------------------------------------------------------------

int newMapValue(int **startingMap, int x, int y, int bitPos, int newVal) {
    int curVal = startingMap[y][x];

    if (newVal == 1) {
        return (curVal | (1 << bitPos));
        //        printf(" -- setmapval[%d][%d]. New=%d\n       ref=%d", x, y, curVal | (1 << bitPos), *(startingMap[y][x]));
    } else {
        return curVal & (~(1 << bitPos));
    }
}

int readMapValue(int **startingMap, int x, int y, int bitPos) {
    return (startingMap[y][x] >> bitPos) & 1;
}

int isCrosswordDone(int **map, int xLen, int yLen, int maxWordLen, int *wordOfLengthCount,
        int ** wordOfLengthOccur) {
    int i, j;

    for (i = 0; i < xLen; i++) {
        for (j = 0; j < yLen; j++) {
            if (readMapValue(map, i, j, HORZ_START)) {
                if (!readMapValue(map, i, j, HORZ_FILLED)) {
                    return 0;
                }
            }

            if (readMapValue(map, i, j, VERT_START)) {
                if (!readMapValue(map, i, j, VERT_FILLED)) {
                    return 0;
                }
            }
        }
    }

    for (i = 0; i < maxWordLen; i++) {
        for (j = 0; j < wordOfLengthCount[i]; j++)
            if (wordOfLengthOccur[i][j] != 0) return 0;
    }

    return 1;
}

int getFieldLength(char **field, int x, int y, int xLen, int yLen, char direction) {
    /*
     * Returns how many characters needed to fill before '*' or end of line
     */

    int i;

    if (field[y][x] == '*') return -1;

    if (direction == HORIZONTAL) {
        for (i = x; i < xLen; i++) if (field[y][i] == '*') break;
        return i - x;
    } else {
        for (i = y; i < yLen; i++) if (field[i][x] == '*') break;

        return i - y;
    }
}

/*
int countFieldGaps(char **field, int x, int y, int direction, int xLen, int yLen) {
    int i;
    int gaps = 0;

    if (direction == HORIZONTAL) {
        for (i = 0; i + x < xLen; i++) {
            if (field[y][x + i] == ' ') gaps++;
        }
    } else {
        for (i = 0; i + y < yLen; i++) {
            if (field[y + i][x] == ' ') gaps++;
        }
    }

    return gaps;
}

int getOptimalStartField(int **startingMap, char **field, int xLen, int yLen, int *direction) {
    int i;
    int minGaps = -1, minIndex = -1, minDirection;
    int thisX, thisY, thisGaps;

    for (i = 0; i < startingPositionsCount; i++) {
        thisX = startingPositions[i].x;
        thisY = startingPositions[i].y;

        if (readMapValue(startingMap, thisX, thisY, HORZ_START)
                && !readMapValue(startingMap, thisX, thisY, HORZ_FILLED)) { // Position is horz start and is not filled

            thisGaps = countFieldGaps(field, thisX, thisY, HORIZONTAL, xLen, yLen);
            if (thisGaps < minGaps || minGaps == -1) {
                minGaps = thisGaps;
                minIndex = i;
                minDirection = HORIZONTAL;
            }
        }

        if (readMapValue(startingMap, thisX, thisY, VERT_START)
                && !readMapValue(startingMap, thisX, thisY, VERT_FILLED)) { // Position is vert start and is not filled

            thisGaps = countFieldGaps(field, thisX, thisY, VERTICAL, xLen, yLen);
            if (thisGaps < minGaps || minGaps == -1) {
                minGaps = thisGaps;
                minIndex = i;
                minDirection = VERTICAL;
            }
        }
    }

 *direction = minDirection;
    return minIndex;
}
 * */

int countFieldFilled(char **field, int x, int y, int direction, int xLen, int yLen) {
    int i;
    int filled = 0;

    //printf("\n\nCount filled\n");

    if (direction == HORIZONTAL) {
        //printf("Horz\n");
        for (i = 0; i + x < xLen; i++) {
            //printf("[%d, %d]: ", x + i, y);
            if (field[y][x + i] != ' ' && field[y][x + i] != '*') {
                filled++;
                //printf("filled++ (%c)\n", field[y][x + i]);
            }// else printf("nothin\n");
        }
    } else {
        //printf("Vert\n");
        for (i = 0; i + y < yLen; i++) {
            // printf("[%d, %d]: ", x, y + i);
            if (field[y + i][x] != ' ' && field[y + i][x] != '*') {
                filled++;
                // printf("filled++ (%c) \n", field[y + i][x ]);
            } //else printf("nothin\n");
        }
    }

    return filled;
}

int getHorzPossibles(char ***words, int *wordOfLengthCount, int **wordOfLengthOccur,
        char **field, int x, int y, int xLen, int yLen, int level) {

    int fillCount = 0;
    int len;
    int i, j, canUse;

    len = getFieldLength(field, x, y, xLen, yLen, HORIZONTAL);


    for (i = 0; i < wordOfLengthCount[len - 1]; i++) { // Loop for all viable words

        if (wordOfLengthOccur[len - 1][i] > 0) { // Can use the word in terms of availability
            canUse = 1;

            for (j = x; j < x + len; j++) { // Does the word fit the field?
                if (field[y][j] != words[len - 1][i][j - x] && field[y][j] != ' ') {
                    canUse = 0;
                    break;
                }
            }

            if (canUse) {
                fillCount++;
            }
        }
    }

    return fillCount;
}

int getVertPossibles(char ***words, int *wordOfLengthCount, int **wordOfLengthOccur,
        char **field, int x, int y, int xLen, int yLen, int level) {

    int fillCount = 0;
    int len;
    int i, j, canUse;


    len = getFieldLength(field, x, y, xLen, yLen, VERTICAL);


    for (i = 0; i < wordOfLengthCount[len - 1]; i++) { // Loop for all viable words

        if (wordOfLengthOccur[len - 1][i] > 0) { // Can use the word in terms of availability
            canUse = 1;

            for (j = y; j < y + len; j++) { // Does the word fit the field?
                if (field[j][x] != words[len - 1][i][j - y] && field[j][x] != ' ') {
                    canUse = 0;
                    break;
                }
            }

            if (canUse) {
                fillCount++;
            }
        }
    }

    return fillCount;
}


int getOptimalStartField(int **startingMap, char **field, char ***words, int *wordOfLengthCount,
        int **wordOfLengthOccur, int xLen, int yLen, int *direction, int level) {

    int i;
    int minPossibles = 999, optIndex = -1, optDirection;
    int thisX, thisY, thisPossibles;



    //printIndent(level);
    //printf("  > getOptimalStartField!\n");

    for (i = 0; i < startingPositionsCount; i++) {
        thisX = startingPositions[i].x;
        thisY = startingPositions[i].y;

        if (readMapValue(startingMap, thisX, thisY, HORZ_START)
                && !readMapValue(startingMap, thisX, thisY, HORZ_FILLED)) { // Position is horz start and is not filled

            thisPossibles = getHorzPossibles(words, wordOfLengthCount, wordOfLengthOccur,
                    field, thisX, thisY, xLen, yLen, level);

            if (i == 0 || thisPossibles < minPossibles) {
                
                //printIndent(level);
                //printf("  > > New opt position: [%d,%d] horz - %d possible.\n", thisX, thisY, thisPossibles);
                
                minPossibles = thisPossibles;
                optIndex = i;
                optDirection = HORIZONTAL;

                if (minPossibles == 1) {
                    goto function_end;
                }
            }

        }
        
        if (readMapValue(startingMap, thisX, thisY, VERT_START)
                && !readMapValue(startingMap, thisX, thisY, VERT_FILLED)) { // Position is horz start and is not filled

            thisPossibles = getVertPossibles(words, wordOfLengthCount, wordOfLengthOccur,
                    field, thisX, thisY, xLen, yLen, level);

            if (i == 0 || thisPossibles < minPossibles) {
                
                //printIndent(level);
                //printf("  > > New opt position: [%d,%d] vert - %d possible.\n", thisX, thisY, thisPossibles);
                
                minPossibles = thisPossibles;
                optIndex = i;
                optDirection = VERTICAL;

                if (minPossibles == 1) {
                    goto function_end;
                }
            }

        }
        

        /*
        if (readMapValue(startingMap, thisX, thisY, HORZ_START)
                && !readMapValue(startingMap, thisX, thisY, HORZ_FILLED)) { // Position is horz start and is not filled

            thisLen = getFieldLength(field, thisX, thisY, xLen, yLen, HORIZONTAL);
            thisFilled = countFieldFilled(field, thisX, thisY, HORIZONTAL, xLen, yLen);

            if (thisFilled > maxFilled || maxFilled == -1 || (thisFilled == maxFilled && thisLen > maxLen)) {
                maxFilled = thisFilled;
                optIndex = i;
                optDirection = HORIZONTAL;
                maxLen = thisLen;
            }
        }

        if (readMapValue(startingMap, thisX, thisY, VERT_START)
                && !readMapValue(startingMap, thisX, thisY, VERT_FILLED)) { // Position is vert start and is not filled

            thisLen = getFieldLength(field, thisX, thisY, xLen, yLen, VERTICAL);
            thisFilled = countFieldFilled(field, thisX, thisY, VERTICAL, xLen, yLen);

            if (thisFilled > maxFilled || maxFilled == -1 || (thisFilled == maxFilled && thisLen > maxLen)) {
                maxFilled = thisFilled;
                optIndex = i;
                optDirection = VERTICAL;
                maxLen = thisLen;
            }
        }*/
    }

    //printf("\nOptimalStart: maxFilled==%d, maxLen==%d & [%d, %d]\n\n", maxFilled, maxLen, startingPositions[optIndex].x, startingPositions[optIndex].y);

function_end:
    {
        //printIndent(level);
        //printf("  > Returning from optimalPos.\n");
    
        *direction = optDirection;
        return optIndex;
    }
}


int *fillWordHorz(char ***words, int *wordOfLengthCount, int **wordOfLengthOccur,
        char **field, int x, int y, int xLen, int yLen, int *filledCount, int level) {
    /*
     * returns array: 
     *          [0] - the length of words filled
     *          [1] - index of the first word filled
     *          [2] - index of the second word filled
     *          ...
     */

    int fillCount = 0;
    int *res;
    int len;
    int i, j, canUse;

    len = getFieldLength(field, x, y, xLen, yLen, HORIZONTAL);

    res = (int*) malloc((wordOfLengthCount[len - 1] + 1) * sizeof (*res));
    res[0] = len;


    for (i = 0; i < wordOfLengthCount[len - 1]; i++) { // Loop for all viable words

        if (wordOfLengthOccur[len - 1][i] > 0) { // Can use the word in terms of availability
            canUse = 1;

            for (j = x; j < x + len; j++) { // Does the word fit the field?
                if (field[y][j] != words[len - 1][i][j - x] && field[y][j] != ' ') {
                    canUse = 0;
                    break;
                }
            }

            if (canUse) {
                res[1 + fillCount++] = i;
            }
        }
    }

    *filledCount = fillCount;

    return res;
}

int *fillWordVert(char ***words, int *wordOfLengthCount, int **wordOfLengthOccur,
        char **field, int x, int y, int xLen, int yLen, int *filledCount, int level) {
    /*
     * returns array: 
     *          [0] - the length of words filled
     *          [1] - index of the first word filled
     *          [2] - index of the second word filled
     *          ...
     */

    int fillCount = 0;
    int *res;
    int len;
    int i, j, canUse;


    len = getFieldLength(field, x, y, xLen, yLen, VERTICAL);

    res = (int*) malloc((wordOfLengthCount[len - 1] + 1) * sizeof (*res));
    res[0] = len;


    for (i = 0; i < wordOfLengthCount[len - 1]; i++) { // Loop for all viable words


        if (wordOfLengthOccur[len - 1][i] > 0) { // Can use the word in terms of availability
            canUse = 1;

            for (j = y; j < y + len; j++) { // Does the word fit the field?
                if (field[j][x] != words[len - 1][i][j - y] && field[j][x] != ' ') {
                    canUse = 0;
                    break;
                }
            }

            if (canUse) {
                res[1 + fillCount++] = i;
            }
        }
    }

    *filledCount = fillCount;

    return res;
}

void fillCrossword(char ***words, int *wordOfLengthCount, int **wordOfLengthOccur,
        int maxWordLen, char **field, int xLen, int yLen, int **startingMap, int level) {
    int x, y;
    int *filledWords;
    int filledCount;

    char **recField; // Field for passing to recursive func
    int **recWordOfLengthOccur;
    int **recStartingMap;

    int i, j;

    int optimalFieldIndex, optimalDirection;


    if (isCrosswordDone(startingMap, xLen, yLen, maxWordLen, wordOfLengthCount, wordOfLengthOccur)) {
        solutionsCount++;

        //printf("Solution found!\n");

        for (i = 0; i < xLen; i++) {
            for (j = 0; j < yLen; j++) {
                //printf("writing [%d][%d].. ", j, i);
                lastSolution[j][i] = field[j][i];
                //printf("done.\n");
            }
        }
        return;
        //goto end_function;
    }

    //printCrossword(field, xLen, yLen, level);


    recField = (char**) malloc(yLen * sizeof (*recField));
    recStartingMap = (int**) malloc(yLen * sizeof (*recStartingMap));

    for (i = 0; i < yLen; i++) {
        recField[i] = (char*) malloc(xLen * sizeof (**recField));
        recStartingMap[i] = (int*) malloc(xLen * sizeof (**recStartingMap));
    }


    for (i = 0; i < xLen; i++)
        for (j = 0; j < yLen; j++) {
            recField[j][i] = field[j][i];
            recStartingMap[j][i] = startingMap[j][i];
        }

    recWordOfLengthOccur = (int**) malloc(maxWordLen * sizeof (*recWordOfLengthOccur));
    for (i = 0; i < maxWordLen; i++)
        recWordOfLengthOccur[i] = (int*) malloc(wordOfLengthCount[i] * sizeof (**recWordOfLengthOccur));

    for (i = 0; i < maxWordLen; i++)
        for (j = 0; j < wordOfLengthCount[i]; j++)
            recWordOfLengthOccur[i][j] = wordOfLengthOccur[i][j];


    //printIndent(level);
    //printf(" Finding optimal start pos:\n");

    optimalFieldIndex = getOptimalStartField(startingMap, field, words, wordOfLengthCount, wordOfLengthOccur, xLen, yLen, &optimalDirection, level);

    x = startingPositions[optimalFieldIndex].x;
    y = startingPositions[optimalFieldIndex].y;

    /*
    printIndent(level);
    printf("---------------------------------------------\n");

    printIndent(level);
    printf("fillCrossword!\n");
    printIndent(level);

    printf("\n");

    printCrossword(field, xLen, yLen, level);
    printIndent(level);
    printf("\n");

    printMap(startingMap, xLen, yLen, level);

    printWordsLeft(maxWordLen, wordOfLengthCount, wordOfLengthOccur, words, level);

    printIndent(level);
    printf("\n");

    printIndent(level);
    printf("Putting a word at [%d, %d] %s\n", x, y, optimalDirection == HORIZONTAL ? "Horz" : "Vert");

    printIndent(level);
    printf("\n");
     * */

    if (optimalDirection == HORIZONTAL) { // Optimal direction is horizontal

        filledWords = fillWordHorz(words, wordOfLengthCount,
                wordOfLengthOccur, field, x, y, xLen, yLen, &filledCount, level);

        if (!filledCount) { // Cannot complete crossword this way
            goto end_function;
            free(filledWords);
        } else {
            // Can complete crossword
            for (i = 0; i < filledCount; i++) { // Recursively call fillCW with added words

                //printIndent(level);
                //printf("Adding word [%s]\n", words[filledWords[0] - 1][filledWords[i + 1]]);

                //printIndent(level);
                //printf("\n");

                for (j = 0; j < filledWords[0]; j++) {
                    recField[y][x + j] = words[filledWords[0] - 1][filledWords[i + 1]][j];
                }


                recStartingMap[y][x] = newMapValue(recStartingMap, x, y, HORZ_FILLED, 1);
                recWordOfLengthOccur[filledWords[0] - 1][filledWords[i + 1]]--;

                fillCrossword(words, wordOfLengthCount, recWordOfLengthOccur,
                        maxWordLen, recField, xLen, yLen, recStartingMap, level + 1);

                recWordOfLengthOccur[filledWords[0] - 1][filledWords[i + 1]]++;
                recStartingMap[y][x] = newMapValue(recStartingMap, x, y, HORZ_FILLED, 0);
            }
            free(filledWords);
        }


    } else { // Optimal direction is vertical

        filledWords = fillWordVert(words, wordOfLengthCount,
                wordOfLengthOccur, field, x, y, xLen, yLen, &filledCount, level);

        if (!filledCount) { // Cannot complete crossword this way
            free(filledWords);
            goto end_function;
        } else { // Can complete crossword

            for (i = 0; i < filledCount; i++) {
                // Recursively call fillCW with added words

                //printIndent(level);
                //printf("Adding word [%s]\n", words[filledWords[0] - 1][filledWords[i + 1]]);

                //printIndent(level);
                //printf("\n");


                for (j = 0; j < filledWords[0]; j++) {
                    recField[y + j][x] = words[filledWords[0] - 1][filledWords[i + 1]][j];
                }


                recWordOfLengthOccur[filledWords[0] - 1][filledWords[i + 1]]--;
                recStartingMap[y][x] = newMapValue(recStartingMap, x, y, VERT_FILLED, 1);

                fillCrossword(words, wordOfLengthCount, recWordOfLengthOccur,
                        maxWordLen, recField, xLen, yLen, recStartingMap, level + 1);

                recWordOfLengthOccur[filledWords[0] - 1][filledWords[i + 1]]++;
                recStartingMap[y][x] = newMapValue(recStartingMap, x, y, VERT_FILLED, 0);
            }
            free(filledWords);
        }


    }


end_function:
    {
        // printf("freeing alloced stuff:\n");

        //printf("1..\n");
        for (i = 0; i < yLen; i++) {
            //  printf("i=%d\n", i);
            free(recField[i]);
            free(recStartingMap[i]);
        }

        //printf("2..\n");
        free(recField);
        free(recStartingMap);

        // printf("3..\n");
        for (i = 0; i < maxWordLen; i++) {
            free(recWordOfLengthOccur[i]);
        }

        //printf("4..\n");
        free(recWordOfLengthOccur);

        //printf("done freeing\n");
        return;
    }
}


// Initializing functions

int isStartOfField(int x, int y, char **field, int xLen, int yLen, int direction, int level) {
    if (direction == HORIZONTAL)
        if ((field[y][x] != '*') && (x == 0 || (x > 0 && field[y][x - 1] == '*'))) {

            //printIndent(level);
            //printf("[%d,%d] is horz start.\n", x, y);

            return 1;
        } else return 0;
    else {
        if ((field[y][x] != '*') && (y == 0 || (y > 0 && field[y - 1][x] == '*'))) {

            //printIndent(level);
            //printf("[%d,%d] is vert start.\n", x, y);

            return 1;
        } else return 0;
    }
}

int **initStartingMap(char **field, int xLen, int yLen) {
    int i, j;
    int **resMap;

    resMap = (int**) malloc(yLen * sizeof (*resMap));
    for (i = 0; i < yLen; i++) {
        resMap[i] = (int*) malloc(xLen * sizeof (**resMap));
    }

    for (j = 0; j < yLen; j++) {
        for (i = 0; i < xLen; i++) {
            resMap[j][i] = 0;

            if (isStartOfField(i, j, field, xLen, yLen, HORIZONTAL, 0))
                resMap[j][i] = resMap[j][i] | 0x1;

            if (isStartOfField(i, j, field, xLen, yLen, VERTICAL, 0))
                resMap[j][i] = resMap[j][i] | 0x2;
        }
    }

    return resMap;
}

void freeStartingMap(int yLen, int *** startingMap) {
    int i;

    for (i = 0; i < yLen; i++)
        free((*startingMap)[i]);

    free(*startingMap);
}

void initLastSolution(int xLen, int yLen) {
    int i;

    lastSolution = (char**) malloc(yLen * sizeof (*lastSolution));
    for (i = 0; i < yLen; i++)
        lastSolution[i] = (char*) malloc(xLen * sizeof (**lastSolution));
}

void freeLastSolution(int yLen) {
    int i;

    for (i = 0; i < yLen; i++)
        free(lastSolution[i]);

    free(lastSolution);
}

int readBoundaryLine() { // Reads top or bottom line without the first plus sign
    int size = 0;
    char readChar;

    while (scanf("%c", &readChar) == 1 && readChar == '-')
        size++;

    if (readChar != '+') {
        return -1;
    } else {
        if (scanf("%c", &readChar) != 1 || (readChar != '\n' && readChar != 13)) {
            return -1;
        }

        if (readChar == 13) scanf("%c", &readChar);

        return size;
    }
}

int fieldFilled(int x, int y, char **field, int xLen, int yLen, int direction) {
    int i;
    int isFilled = 1;


    if (direction == HORIZONTAL) {
        for (i = 0; x + i < xLen; i++) {
            if (field[y][x + i] == ' ') {
                isFilled = 0;
                break;
            } else if (field[y][x + i] == '*') break;
        }
    } else {
        for (i = 0; y + i < yLen; i++) {
            if (field[y + i][x] == ' ') {
                isFilled = 0;
                break;
            } else

                if (field[y + i][x] == '*') break;
        }
    }

    return isFilled;
}

int checkTaskFits(int *wordCounts, int countLen, int **wordOfLengthOccur, char **field, int xLen, int yLen) {
    int x, y, i, j;
    int foundLen;

    int *counts = (int*) malloc(countLen * sizeof (int));
    for (i = 0; i < countLen; i++) {
        counts[i] = 0;
        for (j = 0; j < wordCounts[i]; j++)
            counts[i] += wordOfLengthOccur[i][j];
    }

    for (y = 0; y < yLen; y++)
        for (x = 0; x < xLen; x++) {
            // Horz

            if (isStartOfField(x, y, field, xLen, yLen, HORIZONTAL, 0)) {
                foundLen = getFieldLength(field, x, y, xLen, yLen, HORIZONTAL);
                if (foundLen == -1) {
                    continue;
                }

                counts[foundLen - 1]--;

            }

            if (isStartOfField(x, y, field, xLen, yLen, VERTICAL, 0)) {
                foundLen = getFieldLength(field, x, y, xLen, yLen, VERTICAL);

                if (foundLen == -1) {
                    continue;
                }

                counts[foundLen - 1]--;
            }
        }

    for (i = 0; i < countLen; i++) {
        if (counts[i] != 0) {
            free(counts);
            return 0;
        }
    }

    free(counts);

    return 1;
}

int countLengths(char **task, int taskLen, int wantedLength) {
    int i;
    int res = 0;

    for (i = 0; i < taskLen; i++)
        if ((int) strlen(task[i]) == wantedLength) res++;

    return res;
}

char **getWordsOfLength(char **task, int taskLen, int *wantedLength, int **rCountsRes) {
    char **res; // Resulting array of truncated strings
    int *rCounts; // Array with quantities of individual strings

    int i, j;
    int count = 0;
    char alreadyAdded;

    //printf("  **GetWOL.\n");

    rCounts = (int*) malloc(taskLen * sizeof (rCounts));
    res = (char**) malloc(taskLen * sizeof (*res));
    for (i = 0; i < taskLen; i++) {
        //printf(">> mallocing res[%d] to %d\n", i, *wantedLength+1);
        res[i] = (char*) malloc((*wantedLength + 1) * sizeof (**res));
        rCounts[i] = 0;
    }

    for (i = 0; i < taskLen; i++) {
        if ((int) strlen(task[i]) == *wantedLength) { // If the length of i-th string is what I want
            //printf("    > found |%s|, checking if already added: ", task[i]);

            alreadyAdded = 0;
            for (j = 0; j < count; j++) // Compare if not previously found;
                if (strcmp(task[i], res[j]) == 0) { // If yes, increment its appropriate number
                    alreadyAdded = 1;
                    break;
                }

            if (alreadyAdded) {
                rCounts[j]++;
                //printf("[previously added, inc count]\n");
            } else { // If not, add the new string
                strncpy(res[count++], task[i], *wantedLength + 1);
                rCounts[j]++;
                //printf("[not found, adding new]\n");
            }
        }
    }

    rCounts = (int*) realloc(rCounts, count * sizeof (rCounts));

    for (i = count; i < taskLen; i++) {
        //printf(">> freeing res[%d]\n", i);
        free(res[i]);
    }

    *wantedLength = count;
    *rCountsRes = rCounts;

    return res;
}

int maxLen(char **task, int taskLen) {
    int i;
    int res = 0;

    for (i = 0; i < taskLen; i++)
        if ((int) strlen(task[i]) > res) res = strlen(task[i]);

    return res;
}

char ***refactorTask(int ***refactorWordsCounts, int **refactorWords, int *refLenOut, char **task, int taskLen) {
    /*
     * refactorWordsCounts - out parameter
     *       rWC[i][j] keeps track of how many times was a word of length==i on index j found
     * 
     * refactorWords - out parameter
     *       rW[i] keeps track of how many words of length i was found
     * 
     * refLenOut - out parameter
     *       rLO represents the word of biggest length (and so the length of RWC and RW)
     * 
     * task - in parameter
     *       task contains all words to be found
     * 
     * taskLen - in parameter
     *       taskLen contains the length of task array
     */

    int refLen;
    int i;
    int lenCount;

    int wantedLen;

    char *** rTask;
    int ** rTaskCnts;
    int * foundCnt;

    refLen = maxLen(task, taskLen);

    rTask = (char***) malloc(refLen * sizeof (*rTask));
    rTaskCnts = (int**) malloc(refLen * sizeof (*rTaskCnts));
    foundCnt = (int*) malloc(refLen * sizeof (*foundCnt));

    for (i = 0; i < refLen; i++) {

        wantedLen = i + 1;

        lenCount = countLengths(task, taskLen, wantedLen);

        // Fill up this length
        rTask[i] = getWordsOfLength(task, taskLen, &wantedLen, &rTaskCnts[i]);

        foundCnt[i] = wantedLen;
    }


    *refactorWordsCounts = rTaskCnts;
    *refactorWords = foundCnt;
    *refLenOut = refLen;


    return rTask;
}

TSTARTPOS * fillStartsArray(char **field, int xLen, int yLen, int *startsCount) {
    int i, j, found = 0;
    TSTARTPOS * res = (TSTARTPOS*) malloc(xLen * yLen * sizeof (*res));

    for (j = 0; j < yLen; j++)
        for (i = 0; i < xLen; i++)
            if (isStartOfField(i, j, field, xLen, yLen, HORIZONTAL, 0) ||
                    isStartOfField(i, j, field, xLen, yLen, VERTICAL, 0)) {
                res[found].x = i;
                res[found].y = j;
                found++;
            }

    res = (TSTARTPOS*) realloc(res, found * sizeof (*res));

    *startsCount = found;
    return res;
}

int readRebus(char*** outRebus, int* x, int* y) {
    int vertResizeC = 2;

    int horzRead = 0; // actual chars
    char firstChar = 1;
    int vertRead = 0;

    int horzSize = 0;
    int vertSize = 0;

    char readChar;

    char endOfInput = 0;

    int i;

    char ** rebus;


    if (scanf("%c", &readChar) != 1 || readChar != '+') {
        return 0;
    }
    //printf("Read +\n");

    horzSize = readBoundaryLine();
    if (horzSize < 1) {
        return 0;
    }

    //printf("Length: %d\n", horzSize);

    rebus = (char**) malloc(vertResizeC * sizeof (*rebus));
    vertSize = vertResizeC;
    vertResizeC *= 2;

    for (i = 0; i < vertSize; i++)
        rebus[i] = (char*) malloc(horzSize * sizeof (**rebus));
    //printf("Mallocing horz to %d\n", horzSize);

    //printf("Read: ");
    while (1) {
        while (scanf("%c", &readChar) == 1) {

            if (readChar == 13) continue;

            if (readChar == '\n') {
                return 0;
            }

            if (readChar == 13) continue;

            if (firstChar) {
                if (readChar == '+') {
                    if (horzSize != readBoundaryLine()) {
                        return 0;
                    } else {
                        endOfInput = 1;
                        break;
                    }
                } else {
                    if (readChar == '|') {
                        firstChar = 0;
                        continue;
                    } else {
                        return 0;
                    }
                }
            }

            if (readChar == '|') { // Not the left-border,that was filtered out ^
                if (horzRead == 0 || scanf("%c", &readChar) != 1
                        || (readChar != '\n' && readChar != 13) || horzRead != horzSize) { // Empty line read or | not end of line
                    return 0;
                }
                if (readChar == 13) scanf("%c", &readChar);

                vertRead++;
                horzRead = 0;
                firstChar = 1;

                //printf("\nRead: ");

                break;
            }

            if (vertRead == vertSize) {
                rebus = (char**) realloc(rebus, vertResizeC * sizeof (*rebus));
                vertSize = vertResizeC;
                vertResizeC *= 2;

                //printf("inc vert to %d\n", vertSize);

                for (i = vertRead; i < vertSize; i++) {
                    rebus[i] = (char*) malloc(horzSize * sizeof (**rebus));
                }
            }

            if (readChar != ' ' && readChar != '*') {
                return 0;
            }

            rebus[vertRead][horzRead++] = readChar;
            //printf("|%c|", readChar);
        }

        if (feof(stdin)) {
            return 0;
        }

        if (endOfInput) {
            //printf("End of borders.\n");

            break;
        }
    }

    for (i = vertRead; i < vertSize; i++) {
        free(rebus[i]);
    }

    *outRebus = rebus;
    *x = horzSize;
    *y = vertRead;

    if (vertRead > 16 || horzSize > 16) return 0;

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
    task = (char**) realloc(task, vertRead * sizeof (*task));


    *outTask = task;
    *y = vertRead;

    if (vertRead > 60) return 0;

    return 1;
}

int main(int argc, char** argv) {

    char ** rebus;
    char ** task;

    char *** refactored;
    int ** refWordCounts; // refWordCounts[i][j] - how many times was a word of length i on j-th position found
    int * refWords; // refWords[i] - How many unique words of length i was found

    int **startingMap;
    /* indicates where starts of words are and which directions have already been added
     * bit 0 (1) - horzStart
     * bit 1 (2) - vertStart
     * bit 2 (4) - horzWordFilled
     * bit 3 (8) - vertWordFilled
     * */

    //TSTARTPOS *startingPositions; // Holds all positions where words start
    //int startingPositionsCount;

    int refLen;

    int i, j;
    int rebusXLen, rebusYLen, taskLen;

    printf("Zadejte krizovku:\n");

    if (!readRebus(&rebus, &rebusXLen, &rebusYLen)) { // Freed OK
        printf(WRONG_INPUT);
        return 0;
    }


    if (!readTask(&task, &taskLen)) { // Freed OK
        printf(WRONG_INPUT);
        return 0;
    }

    refactored = refactorTask(&refWordCounts, &refWords, &refLen, task, taskLen);


    if (!checkTaskFits(refWords, refLen, refWordCounts, rebus, rebusXLen, rebusYLen)) {
        printf(WRONG_INPUT);
        return 0;
    }

    startingMap = initStartingMap(rebus, rebusXLen, rebusYLen);
    startingPositions = fillStartsArray(rebus, rebusXLen, rebusYLen, &startingPositionsCount);


    initLastSolution(rebusXLen, rebusYLen);

    fillCrossword(refactored, refWords, refWordCounts, refLen, rebus, rebusXLen, rebusYLen, startingMap, 0);



    if (solutionsCount == 1) {
        printf("Krizovka ma 1 reseni:\n");
        for (j = -1; j < rebusYLen + 1; j++) {
            for (i = -1; i < rebusXLen + 1; i++) {
                if (j == -1 || j == rebusYLen) {
                    printf("%c", (i == -1 || i == rebusXLen) ? '+' : '-');
                } else printf("%c", (i == -1 || i == rebusXLen) ? '|' : lastSolution[j][i]);
            }
            printf("\n");
        }
    } else if (solutionsCount == 0) printf("Krizovka nema reseni.\n");
    else printf("Celkem ruznych reseni: %d\n", solutionsCount);


    freeStartingMap(rebusYLen, &startingMap);
    freeLastSolution(rebusYLen);

    // Free rebus
    for (i = 0; i < rebusYLen; i++) {
        free(rebus[i]);
    }
    free(rebus);

    // Free task
    for (i = 0; i < taskLen; i++)
        free(task[i]);
    free(task);


    // Free refactored
    for (i = 0; i < refLen; i++) {
        for (j = 0; j < refWords[i]; j++) {
            free(refactored[i][j]);
        }
        free(refactored[i]);
        free(refWordCounts[i]);
    }
    free(refWords);
    free(refactored);
    free(refWordCounts);

    free(startingPositions);

    return (EXIT_SUCCESS);
}


