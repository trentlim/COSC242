#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "tree.h"
#include <string.h>

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/* holds type value passed to tree constructor */
static type_t tree_type;

/**
 * key: the node of the tree
 * colour: colour of the node in an RBT
 * frequency: frequency of duplicates in the tree
 * left/right: left and right nodes of the tree
 */
struct tree_node {
    char *key;
    tree_colour colour;
    tree left;
    tree right;
    int frequency;
};

/**
 * Rotates RBT parent node right.
 * @param r the parent node to rotate on.
 * @return r the resulting parent node after rotation.
 */
static tree right_rotate(tree t){
    tree temp;
    temp = t;
    t = temp->left;

    temp->left = t->right;
    t->right = temp;
    return t;
}

/**
 * Rotates RBT parent node left.
 * @param r the parent node to rotate on.
 * @return r the resulting parent node after rotation.
 */
static tree left_rotate(tree t){
    tree temp;
    temp = t;
    t = temp->right;

    temp->right = t->left;
    t->left = temp;
    return t;
}

/**
 * Ensures the root of the RBT is black
 * @param t the tree to be modified
 * @return r the modified RBT
 */
static tree set_root_black(tree t){
    if(IS_RED(t)){
        t->colour = BLACK;
    }
    return t;
}

/**
 * Balances the RBT to satisfy the requirements of a RBT
 * @param r the tree to be fixed
 * @return r the fixed RBT
 */
static tree rbt_fix(tree t){
    if(IS_RED(t->left) && IS_RED(t->left->left)){
        if(IS_RED(t->right)){
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else {
            t = right_rotate(t);
            t->colour = BLACK;
            t->right->colour = RED;
        }
    } else if(IS_RED(t->left) && IS_RED(t->left->right)){
        if(IS_RED(t->right)){
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else {
            t->left = left_rotate(t->left);
            t = right_rotate(t);
            t->colour = BLACK;
            t->right->colour = RED;
        }
    } else if(IS_RED(t->right) && IS_RED(t->right->left)){
        if(IS_RED(t->left)){
            t->colour = RED;
            t->left->colour = BLACK;
            t->right->colour = BLACK;
        } else {
            t->right = right_rotate(t->right);
            t = left_rotate(t);
            t->colour = BLACK;
            t->left->colour = RED;
        }
    } else if(IS_RED(t->right) && IS_RED(t->right->right)){
        if(IS_RED(t->left)){
            t->colour = RED;
            t->right->colour = BLACK;
            t->left->colour = BLACK;
        } else {
            t = left_rotate(t);
            t->colour = BLACK;
            t->left->colour = RED;
        }
    }
    t = set_root_black(t);
    return t;
}

/**
 * Creates a new root with a null value to start the tree and sets tree_type
 * to the type of tree being created.
 * @param type tree type which could either be RBT or BST.
 * @return null. returns new null space.
 */
tree tree_new(type_t type){
    tree_type = type;
    return NULL;
}


/**
 * Frees memory associated with given tree.
 * @param b the tree to free.
 * @return b the freed tree.
 */
tree tree_free(tree t){
    if(NULL == t){
        return t;
    }

    tree_free(t->left);

    tree_free(t->right);
    free(t->key);
    free(t);

    return t;
}

/**
 * Inserts a key into given tree, if the tree is RBT then rbt_fix is
 * called after insertion.
 * @param b the tree that the key will be inserted into.
 * @param str the key used to add to the tree.
 * @return b the tree after insertion.
 */
tree tree_insert(tree t, char *str){
    if(t == NULL){
        t = emalloc(sizeof *t);
        if(tree_type == RBT){
            t->colour = RED;
        }
        t->left = NULL;
        t->right = NULL;
        t->key = NULL;
    }
    if(t->key == NULL){
        t->key = emalloc((strlen(str)+1)*sizeof (char));
        strcpy(t->key, str);
    }
    /* if duplicate item added, increment frequency */
    if(strcmp(t->key, str) == 0){
        t->frequency += 1;
    }
    /* if str is smaller, go left */
    if(strcmp(str, t->key) < 0){
        t->left = tree_insert(t->left, str);
    }
    /* if str is bigger, go right */
    if(strcmp(str, t->key) > 0){
        t->right = tree_insert(t->right, str);
    }
    /* if tree is RBT fix after insert */
    if(tree_type == RBT){
        t = rbt_fix(t);
    }
    return t;
}


/**
 * Applies function to each key in pre-order traversal.
 * @param b the tree to traverse.
 * @param f the function to be applied to each key.
 * @param str the key to apply function to.
 */
void tree_preorder(tree t, void f(int freq, char *str)){
    if(NULL == t){
        return;
    }
    f(t->frequency, t->key);
    tree_preorder(t->left, f);
    tree_preorder(t->right,f);
}

/**
 * Applies the given function to each key in in-order traversal.
 * @param b Tree to traverse.
 * @param f the function to be applied to each individual key.
 * @param str the key which is applied to the function.
 * @param c the colour of the node the key is in if the tree is an RBT.
 */
void tree_inorder(tree t, void f(int freq, char *str)){
    if(NULL == t){
        return;
    }
    f(t->frequency, t->key);
    tree_inorder(t->left, f);
    tree_inorder(t->right,f);
}

/**
 * Searches tree for given key.
 * @param b the tree to be searched.
 * @param str the key to search for.
 * @return 1 if key is null or 0 if key is found.
 */
int tree_search(tree t, char *str){
    if(t == NULL){
        return 0;
    }
    if(strcmp(str, t->key) == 0){
        return 1;
    }
    if(strcmp(str, t->key) < 0){
        return tree_search(t->left, str);
    }
    if(strcmp(str, t->key) > 0){
        return tree_search(t->right, str);
    }
    return 0;
}

/**
 * Calculates the length of the longest path between
 * the root node and the furthest leaf node.
 * @param b the tree which we find the depth of
 * @return depth of the tree, or zero if tree is null.
 */
int tree_depth(tree t){
    if(t == NULL){
        return 0;
    }
    if(t->left == NULL && t->right == NULL) return 0;
    if(tree_depth(t->left) > tree_depth(t->right)){
        return (tree_depth(t->left) + 1);
    }
    return (tree_depth(t->right) + 1);
}

/**
 * Traverses the tree writing a DOT description about connections, and
 * possibly colours, to the given output stream.
 *
 * @param t the tree to output a DOT description of.
 * @param out the stream to write the DOT output to.
 */
void tree_output_dot_aux(tree t, FILE *out) {
   if(t->key != NULL) {
      fprintf(out, "\"%s\"[label=\"{<f0>%s:%d|{<f1>|<f2>}}\"color=%s];\n",
              t->key, t->key, t->frequency,
              (RBT == tree_type && RED == t->colour) ? "red":"black");
   }
   if(t->left != NULL) {
      tree_output_dot_aux(t->left, out);
      fprintf(out, "\"%s\":f1 -> \"%s\":f0;\n", t->key, t->left->key);
   }
   if(t->right != NULL) {
      tree_output_dot_aux(t->right, out);
      fprintf(out, "\"%s\":f2 -> \"%s\":f0;\n", t->key, t->right->key);
   }
}


/**
 * Output a DOT description of this tree to the given output stream.
 * DOT is a plain text graph description language (see www.graphviz.org).
 * You can create a viewable graph with the command
 *
 *    dot -Tpdf < graphfile.dot > graphfile.pdf
 *
 * You can also use png, ps, jpg, svg... instead of pdf
 *
 * @param t the tree to output the DOT description of.
 * @param out the stream to write the DOT description to.
 */
void tree_output_dot(tree t, FILE *out) {
   fprintf(out, "digraph tree {\nnode [shape = Mrecord, penwidth = 2];\n");
   tree_output_dot_aux(t, out);
   fprintf(out, "}\n");
}
