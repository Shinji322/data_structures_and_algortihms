// Implements a dictionary's functionality
// frick my life 
// fscanf literally returns EOF, not a string with EOF but literally just EOF 
// you have no idea how much time. all my logic was right. i want to die.
// how the heck am i supposed to know that from the docs 

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "dictionary.h"
// A hash table is an array of linked lists

// Represents a node in a hash table
typedef struct node
{
    // LENGTH is the maximum length
    // + 1 for trailing null
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
/* const unsigned int N = 26; */
const unsigned int N = 100000;
unsigned int size_dict = 0; // a counter variable

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // for case insensitivity, let's get the lowercase version of the input
    int length = strlen(word);
    char lower_word[length];
    for (int i = 0; i < length; i++)
    {
        lower_word[i] = tolower(word[i]);
    }

    // let's lookup the hash
    int hashed = hash(word);
    // store that array node in cur node
    node *cur_node = table[hashed];

    // check all values in that linked list
    while (cur_node != NULL)
    {
        if (strcmp(lower_word, cur_node->word) == 0)
        {
            return true;
        }
        cur_node = cur_node->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // the word may have alphabetical characters or an apostrophe
    // output: a num between 0 and N-1, inclusive
    // if output > n { return output % N; }
    long output = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        output += toupper(word[i]) * i;
    }

    return output % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        return false;
    }

    // inclusive of trailing null
    char cur_word[LENGTH + 1];

    // we'll keep on iterating until cur_word == EOF
    // to continue, we'll scan a new line from the file dict_file
    while (fscanf(dict_file, "%s", cur_word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        // cur_node->word = cur_word
        strcpy(new_node->word, cur_word);

        // let's get the hash
        unsigned int hashed_num = hash(cur_word);

        new_node->next = table[hashed_num];
        table[hashed_num] = new_node;
        size_dict++;
    }
    fclose(dict_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (size_dict > 0)
    {
        return size_dict;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cur_node = table[i];

        // let's free all values in this list
        // let's get to the last item in the list
        while (cur_node != NULL)
        {
            // let's create a temp value for the current node
            node *tmp = cur_node;
            // let's move our current node to the next one
            cur_node = cur_node->next;

            // let's free up the node we started this list with
            free(tmp);
        }

        // let's free this array
        free(cur_node);
    }

    return true;
}
