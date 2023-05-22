#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdio.h>
#include <stdlib.h>

enum direction { LEFT, RIGHT };

typedef struct Heap {
    int no_nodes;
    struct Heap_Node *root;
} Heap;

typedef struct Heap_Node {
    struct Huff_Node *node;
    struct Heap_Node *left, *right, *parent;
} Heap_Node;

typedef struct Huff_Node {
    char ch;
    int val;
    struct Huff_Node *left, *right;
} Huff_Node;

Heap init();
void freeHeap(Heap_Node *node);
Heap_Node* newHeapNode(Huff_Node *node, Heap_Node *left, Heap_Node *right, Heap_Node *parent);
void insert(Heap *heap, Huff_Node *huffNode);
Huff_Node* remove_root(Heap *heap);
Huff_Node* newHuffNode(char ch, int val, Huff_Node *left, Huff_Node *right);

#endif