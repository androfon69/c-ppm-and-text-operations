#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap init() {
    Heap heap;

    heap.no_nodes = 0;
    heap.root = NULL;

    return heap;
}

void freeHeap(Heap_Node *node) {
    if (node != NULL) {
        freeHeap(node->left);
        freeHeap(node->right);
        free(node);
    }
}

Heap_Node* newHeapNode(Huff_Node *node, Heap_Node *left, Heap_Node *right, Heap_Node *parent) {
    Heap_Node *temp = malloc(sizeof(Heap_Node));

    temp->node = node;
    temp->left = left;
    temp->right = right;
    temp->parent = parent;

    return temp;
}

void insert(Heap *heap, Huff_Node *huffNode) {
    int direction[64], binLen = 0, i;
    heap->no_nodes++;

    if (heap->no_nodes == 1) {
        heap->root = newHeapNode(huffNode, NULL, NULL, NULL);

        return;
    }

    int nrNodes = heap->no_nodes;
    Heap_Node *newNode = heap->root;

    while (nrNodes) {
        direction[binLen++] = nrNodes % 2;
        nrNodes /= 2;
    }

    for (i = binLen - 2; i > 0; i--) {
        if (direction[i] == LEFT) {
            newNode = newNode->left;
        }
        else {
            newNode = newNode->right;
        }
    }

    if (direction[0] == LEFT) {
        newNode->left = newHeapNode(huffNode, NULL, NULL, newNode);

        newNode = newNode->left;
    }
    else {
        newNode->right = newHeapNode(huffNode, NULL, NULL, newNode);

        newNode = newNode->right;
    }

    while (newNode != heap->root && newNode->parent->node->val > newNode->node->val) {
        Huff_Node *temp = newNode->node;
        newNode->node = newNode->parent->node;
        newNode->parent->node = temp;

        newNode = newNode->parent;
    }
}

Huff_Node* remove_root(Heap *heap) {
    if (heap == NULL || heap->root == NULL) {
        return 0;
    }

    Huff_Node *result = heap->root->node;

    if (heap->no_nodes == 1) {
        free(heap->root);
        heap->no_nodes--;
        return result;
    }

    int direction[64], binLen = 0, i;
    int nrNodes = heap->no_nodes;
    Heap_Node *delNode = heap->root;

    while (nrNodes) {
        direction[binLen++] = nrNodes % 2;
        nrNodes /= 2;
    }

    for (i = binLen - 2; i >= 0; i--) {
        if (direction[i] == LEFT) {
            delNode = delNode->left;
        }
        else {
            delNode = delNode->right;
        }
    }

    if (direction[0] == LEFT) {
        delNode->parent->left = NULL;
    }
    else {
        delNode->parent->right = NULL;
    }

    heap->root->node = delNode->node;
    free(delNode);
    heap->no_nodes--;

    delNode = heap->root;

    Huff_Node *aux;

    while (delNode->left != NULL || delNode->right != NULL) {
        if (delNode->right == NULL) {
            if (delNode->node->val > delNode->left->node->val) {
                aux = delNode->node;
                delNode->node = delNode->left->node;
                delNode->left->node = aux;
            }

            break;
        }

        if (delNode->right->node->val < delNode->node->val || delNode->left->node->val < delNode->node->val) {
            if (delNode->right->node->val < delNode->left->node->val) {
                aux = delNode->node;
                delNode->node = delNode->right->node;
                delNode->right->node = aux;

                delNode = delNode->right;
            }
            else {
                aux = delNode->node;
                delNode->node = delNode->left->node;
                delNode->left->node = aux;

                delNode = delNode->left;
            }
        }
        else {
            break;
        }
    }

    return result;
}

Huff_Node* newHuffNode(char ch, int val, Huff_Node *left, Huff_Node *right) {
    Huff_Node *node = malloc(sizeof(Huff_Node));

    node->ch = ch;
    node->val = val;
    node->left = left;
    node->right = right;

    return node;
}