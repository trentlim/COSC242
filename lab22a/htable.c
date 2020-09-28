#include <stdio.h>
#include <string.h>
#include "htable.h"
#include <stdlib.h>
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
};

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;

    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}



htable htable_new(int capacity) {


    htable table = emalloc(sizeof *table);
    table ->capacity = capacity;
    table -> num_keys =0;
    table -> keys = calloc(capacity, sizeof(char*));


    return table;

}

void htable_free(htable h) {
    int i;
    for(i=0; i < h->capacity; i++){
        if(h->keys[i] != NULL){
            free(h->keys[i]);
        }
    }
    free(h->keys);
    free(h);



}

int htable_insert(htable h, char *key) {

    int i = htable_word_to_int(key) %h->capacity;
    int col =0;

    while(col < h->capacity){
        if(h-> keys[i] == NULL){
            h->keys[i] = emalloc((strlen(key)+1) *sizeof key[0]);
            strcpy(h->keys[i],key);
            h->num_keys++;
            return 1;
        }
        if(!strcmp(h->keys[i],key)){
            return 1;
        }
        i++;
        col++;
        i = i % h->capacity;
    }
    return 0;
}

void htable_print(htable h, FILE *stream) {
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }

}
