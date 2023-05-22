#include <stdio.h>
#include <stdlib.h>

typedef struct CharCode {
    char value;
    int frequency;
} CharCode;

int isInCodes(CharCode *codes, int nrCodes, char value) {
    for (int i = 0; i < nrCodes; ++i) {
        if (value == codes[i].value) {
            codes[i].frequency++;
            return 1;
        }
    }

    return 0;
}

int compareChar(const void *a, const void *b) {
    CharCode *firstChar = (CharCode*)a;
    CharCode *secondChar = (CharCode*)b;

    if (firstChar->frequency == secondChar->frequency) {
        return firstChar->value - secondChar->value;
    }

    return secondChar->frequency - firstChar->frequency;
}

CharCode* getHuffFreq(char *fileName, int *nrChars) {
    FILE *inputFile = fopen(fileName, "r");
    CharCode *codes = malloc(256 * sizeof(CharCode));
    *nrChars = 0;

    char c = fgetc(inputFile);

    while (c != EOF) {
        if (isInCodes(codes, *nrChars, c) == 0) {
            codes[*nrChars].value = c;
            codes[*nrChars].frequency = 1;
            (*nrChars)++;
        }

        c = fgetc(inputFile);
    }

    qsort(codes, *nrChars, sizeof(CharCode), compareChar);

    fclose(inputFile);

    return codes;
}

int main() {
    int nrChars = 0;
    CharCode *codes = getHuffFreq("test.txt", &nrChars);

    for (int i = 0; i < nrChars; ++i) {
        printf("%hhd %d\n", codes[i].value, codes[i].frequency);
    }

    free(codes);

	return 0;
}
