#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void printHuffCodes(Huff_Node *node, int level, char *code) {
    if (node != NULL) {
        if (node->ch) {
            printf("%c ", node->ch);
            for (int i = 0; i <= level; i++) {
                printf("%c", code[i]);
            }
            printf("\n");
        }

        level++;

        code[level] = '0';
        printHuffCodes(node->left, level, code);

        code[level] = '1';
        printHuffCodes(node->right, level, code);
    }
}

void freeHuff(Huff_Node *node) {
    if (node != NULL) {
        freeHuff(node->left);
        freeHuff(node->right);
        free(node);
    }
}

void generateHuffCodes(Huff_Node **huffLeaves, int N) {
    Heap huffHeap = init();

    for (int i = 0; i < N; ++i) {
        insert(&huffHeap, huffLeaves[i]);
    }

    Huff_Node *firstNode, *secondNode, *newNode;

    while (huffHeap.no_nodes > 1) {
        firstNode = remove_root(&huffHeap);
        secondNode = remove_root((&huffHeap));

        newNode = newHuffNode(0, firstNode->val + secondNode->val, firstNode, secondNode);
        insert(&huffHeap, newNode);
    }

    char code[16];

    printHuffCodes(newNode, 0, code);

    if (huffHeap.no_nodes != 0) {
        freeHeap(huffHeap.root);
    }

    freeHuff(newNode);
}

int main() {
    FILE *inputFile = fopen("huff.in", "r");

    int N, freq;
    char ch, buff[32] = { '\0' };

    fscanf(inputFile, "%d\n", &N);

    Huff_Node **huffLeaves = malloc(N * sizeof(Huff_Node *));

    for (int i = 0; i < N; ++i) {
        fgets(buff, 32, inputFile);

        ch = buff[0];
        freq = atoi(buff + 2);

        huffLeaves[i] = newHuffNode(ch, freq, NULL, NULL);
    }

    generateHuffCodes(huffLeaves, N);

    free(huffLeaves);

    fclose(inputFile);
	return 0;
}
