// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "dictionary.h"

// declare and initialize global struct, defined as "node"
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// array of 26 pointers to struct
node *hash[26];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash the word to determine appropriate list to check
    char letter = tolower(word[0]);
    int key = (int)letter - 97;

    // Returns true if word is in dictionary else false
    for (node *ptr = hash[key]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[46];
    FILE *file = fopen(dictionary, "r");
    char letter = ' ';

    // read a word from file; repeat until EOF
    while (fscanf(file, "%s", word) != EOF)
    {
        // make new node and check if there was enough memory to create node
        node *newnode = calloc(sizeof(node), 1);
        if (newnode == NULL)
        {
            unload();
            return false;
        }

        // assign word to struct and set "next" to NULL
        strcpy(newnode->word, word);

        int key = tolower(word[0]) - 97;

        // if start of new alphabet point hash[key] to the first word starting with next alphabet
        if (word[0] != letter)
        {
            letter = word[0];
            newnode->next = NULL;
            hash[key] = newnode;
        }
        // insert new word to the beginning of that linked list
        else
        {
            newnode->next = hash[key];
            hash[key] = newnode;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int total = 0;
    for (int i = 0; i < 26; i++)
    {
        for (node *ptr = hash[i]; ptr != NULL; ptr = ptr->next)
        {
            // if at end of list, break out of loop and go to next in the linked list
            if (ptr->next == NULL)
            {
                if (strlen(ptr->word) >= 1)
                {
                    total++;
                }
                break;
            }
            else
            {
                total++;
            }
        }
    }
    return total;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *ptr = hash[i];
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}