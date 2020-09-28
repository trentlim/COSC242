#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#include "queue.h"

#define ARRAY_MAX 5

struct queue{
    double *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new(){
    int default_size = 7;
    queue result = emalloc(sizeof *result);
    result->capacity = default_size;
    result->head = 0;
    result->num_items = 0;
    result->items = emalloc(result->capacity *sizeof result->items[0]);
    return result;
}

void enqueue(queue q, double item){
    if (q->num_items < q->capacity){
        q->items[(q->head+q->num_items++) % q->capacity] = item;
        return;
    }
    return;
}

double dequeue(queue q){
    double dequeue;
    if (q->num_items > 0){
        dequeue = q->items[q->head];
        q->head++;
        q->num_items--;
        return dequeue;
    } else {
        return EXIT_FAILURE;
    }
}

void queue_print(queue q){
    int i = q->head;
    do{
        printf("%.2f\n", q->items[i]);
        i = (i+1)%q->capacity;
    } while (i!=(q->head + q->num_items)%q->capacity);
    return;
}

void queue_print_info(queue q) {
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity,
           q->num_items, q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q){
    return q->num_items;
}

queue queue_free(queue q){
    free(q->items);
    free(q);
    return q;
}
