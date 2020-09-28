#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"

struct htablerec{
    int capacity;
    int num_keys;
    char **keys;
};

static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;

    while (*word != '\0'){
        result = (*word++ + 31 * result);
    }
    return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key){
    return i_key % h->capacity;
}

htable htable_new(int capacity){
    int i;
    htable result = emalloc(sizeof * result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);

    for (i = capacity; i < capacity; i++){
        result->keys[i] = NULL;
    }
    return result;
}

void htable_free(htable h){
    int i;
    for (i = 0; i < h->capacity; i++){
        if (h->keys[i] != NULL){
            free(h->keys[i]);
        }
    }
    free(h->keys);
    free(h);
}

int htable_insert (htable h, char *str){
    unsigned int word, pos, i;

    word = htable_word_to_int(str);
    pos = htable_hash(h, word);
    i = pos;

    do{
        if (h->keys[i] == NULL){
            h->keys[i] = emalloc((strlen(str)+1) * sizeof (char));
            strcpy(h->keys[i], str);
            h->num_keys++;
            return 1;
        } else if (strcmp(h->keys[i], str) == 0){
            return 0;
        }
        i = (i+1)%h->capacity;
    } while (i != pos);
    return 0;
}


void htable_print(htable h, FILE *stream){
    int i;

    for (i = 0; i < h->capacity; i++){
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}
