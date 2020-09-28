#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "bst.h"

struct bst_node{
    char *key;
    bst left;
    bst right;
};

void bst_inorder(bst b, void f(char *key)){
    if (b == NULL){
        return;
    }
    bst_inorder(b->left, f);
    f(b->key);
    bst_inorder(b->right, f);
}

bst bst_insert(bst b, char *key){
    if (b == NULL){
        b = emalloc(sizeof *b);
        b->key = emalloc(strlen(key)+1);
        strcpy(b->key, key);
    } else if (strcmp(b->key, key) < 0){
        b->right = bst_insert(b->right, key);
    } else if (strcmp(b->key, key) > 0){
        b->left = bst_insert(b->left, key);
    }
    return b;
}

bst bst_new(){
    return NULL;
}

void bst_preorder(bst b, void f(char *key)){
    if (b == NULL){
        return;
    }
    f(b->key);
    bst_preorder(b->left, f);
    bst_preorder(b->right, f);
}

int bst_search(bst b, char *key){
    if (b == NULL){
        return 0;
    }
    if (strcmp(b->key, key) == 0){
        return 1;
    } else if (strcmp(b->key, key) < 0){
        return bst_search(b->right, key);
    } else {
        return bst_search(b->left, key);
    }
    return 0;
}

bst bst_free(bst b){
    if (b == NULL){
        return b;
    }
    b->right = bst_free(b->right);
    b->left = bst_free(b->left);
    free(b->key);
    free(b);
    return b;
}
