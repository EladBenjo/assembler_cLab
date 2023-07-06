#include <stdio.h>
#include <string.h>
#include "util.h"
#include "macro_table.h"

/* first read: counting amount of macros and create a suitble hash table
 * second read: store all the macros and their content
 * third read: replace macro tags with the content
 */

void mcroUnfold(FILE* file)
{
    const char delims[1] = " "; /* need to figure out what should be ditched out of every line */ TODO
    bool openMcro = flase; /* will switch to true when mcro identified, return to false when encounter endmcro */
    int counter = 0;
    unsigned long hash;
    char* token;

    char line[81]; /* need to add a checker for max 80 excluding \n */

    /* the loop below counts the amount of macros in the file to initialize and efficient table*/
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
            if (strcmp(token, mcro) == 0)
            {
                counter++;
            }
            token = strtok(null, delims);
        }
    }

    macroTable* MACROS = createMacroTable(counter);

    /* the loop below read the file and insert new macros to the hash table*/
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
            if (strcmp(token, mcro) == 0)
            {
                if (searchMacro(MACROS, token))
                {
                    /* error macro exist already*/
                }
                else
                hash = mcroHash(counter, token);
                macroItem* newMacro = createMacro(token, hash);
                insertMacro(MACROS, newMacro, token, hash);
            }
            token = strtok(null, delims);
        }
    }

    /* the loop below re-write the source file with the macros content */
}