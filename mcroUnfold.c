#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "macro_table.h"
#define ROW_MAX_LENGTH 81;
/*TODO: add define with words like mcro,endmcro etc...*/

/* first read: counting amount of macros and create a suitble hash table
 * second read: store all the macros and their content
 * third read: replace macro tags with the content
 */

void mcroUnfold(FILE* file)
{
    const char delims[1] = " "; /* TODO: figure out what should be ditched out of every line */
    bool openMacro = false; /* will switch to true when mcro identified, return to false when encounter endmcro */
    bool newMacro = false;
    int counter = 0;
    int macroLength = 0;
    unsigned long hash = 0;
    char* token = NULL;
    filePtr = fseek(file, 0, SEEK_SET);

    char line[ROW_MAX_LENGTH]; /* TODO: add a checker for max 80 excluding \n */

    /* the loop below counts the amount of macros in the file to initialize and efficient table */
    while (!readLine(line)) 
    {
        if (strlen(line) > 80)
        {
            /* add error to errors file*/ TODO
                continue;
        }

        token = strtok(line, delims);
        while (token != null)
        {
            if (strcmp(token, "endmcro"))
            {
                openMacro = false;
            }

            if (openMacro)
            {
                macroLength++;
            }

            if (strcmp(token, "mcro") == 0)
            {
                openMacro = true;
                counter++;
            }
            token = strtok(null, delims);
        }
    }
    rewind(file);

    /* initialize new table and a suitble string for macros contnet*/
    macroTable* MACROS = createMacroTable(counter);
    char* macroContent[macroLength];

    /* the loop below read the file and insert new macros to the hash table */
    while (!readLine(line))
    {
        if (strlen(line) > ROW_MAX_LENGTH)
        {
            /* TODO: add error to errors file */
            continue;
        }

        token = strtok(line, delims);
        while (token != null)
        {
            /* endmcro: submit the contnet in and reset the string*/
            if (strcmp(token, "endmcro"))
            {
                newMacro->text = macroContent;
                openMacro = false;
                macroContent = NULL;
            }

            /* openMacro: add new words to content buffer*/
            if (openMacro)
            {
                strcat(macroContent, " ");
                strcat(macroContent, token);
            }

            /* newMacro: when flag is true consume the next word - the macro tag and store in table */
            if (newMacro)
            {
                if (searchMacro(MACROS, token))
                {
                    /* error macro exist already */
                }
                else

                hash = mcroHash(counter, token);
                macroItem* newMacro = createMacro(token, hash);
                insertMacro(MACROS, newMacro, token, hash);

                openMacro = true; /*flag for next iterations to gather macro content*/
                newMacro = false;
            }

            /* macro is declared - next iteration will create it */
            if (strcmp(token, "mcro") == 0)
            {
                newMacro = true;
            }
            

            token = strtok(null, delims);
        }
    }
    rewind(file);

    /* the loop below re-write the source file with the macros content */

}
