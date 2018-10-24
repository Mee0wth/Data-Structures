#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))


/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    char* word = nextWord(file);

    while (word != 0)
    {
        hashMapPut(map, word, 1);
        free (word);
        word = nextWord(file);
    }
    free(word);

}

int levenshteinDistance(char *s1, char *s2) {
     unsigned int s1len, s2len, x, y, lastdiag, olddiag;
     s1len = strlen(s1);
     s2len = strlen(s2);
     unsigned int * column = malloc((s1len + 1) * sizeof(int));
     for (y = 1; y <= s1len; y++)
          column[y] = y;
     for (x = 1; x <= s2len; x++) {
          column[0] = x;
          for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
               olddiag = column[y];
               column[y] = MIN3(column[y] + 1, column[y - 1] + 1, lastdiag + (s1[y - 1] == s2[x - 1] ? 0 : 1));
               lastdiag = olddiag;
          }
     }
     return(column[s1len]);
}
// CITATION: https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(1000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char userInput[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word to search or type \"quit\" to exit:\n ");
        scanf("%s", userInput);
        // makes input lowercase
        for (int i = 0; i < 256; i++)
        {
            userInput[i] = tolower(userInput[i]);
        }

        if(strcmp(userInput, "quit") == 0)
        {
            quit = 1;
        } 
        else if(hashMapContainsKey(map, userInput))
        {
            printf("The inputted word %s", userInput);
            printf(" is spelled correctly\n");
            printf("\n");
        }
        else
        {
            char* alternatives[5];
            int idx = 0;
            HashLink* curr = map->table[idx];

            int levD = -1;
            int preD = 1;
            int count = 0;
            int altIndex = 0;
            while(idx < hashMapCapacity(map) && count < 5)
            {
                while(curr)
                {
                    levD = levenshteinDistance(userInput, curr->key);
                    if(levD > 0 && levD <= preD)
                    {
                       
                        alternatives[altIndex] = curr->key;
                        altIndex++;
                        if(count < 5) {count++;}
                        if(altIndex >= 5){altIndex = 0;}
                    }
                    curr = curr->next;
                    levD = -1;
                }
                idx++;
                if(idx >= hashMapCapacity(map) && count < 6)
                {
                    idx = 0;
                    preD++;
                }

                curr = map->table[idx];
         
            }

            printf("The inputted word %s ", userInput);
            printf("is spelled incorrectly.\n");
            printf("\n");
            printf("Did you mean: \n");
            
            for (int i = 0; i < 5; i++) {
                printf("%s\n", alternatives[i]);
            }
        }
           
    }
    
    hashMapDelete(map);
    return 0;
}