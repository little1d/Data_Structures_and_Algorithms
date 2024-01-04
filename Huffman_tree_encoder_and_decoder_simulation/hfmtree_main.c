#include "huftree_generate.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
    char character;
    char code[100];
} CodeMap;

void freeHuffmanTree(HuffmanNode* root) {
    if (root == NULL) {
        return;
    }
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    free(root);
}

int main() {

    int n = 0;
    printf("Enter the number of characters: ");
    scanf("%d", &n);

    HuffmanNode* root = generateHuffmanTree(n);

    printf("Huffman Tree:\n");
    printHuffmanTree(root, 0);

    char codeb[100];
    printf("Huffman Codes:\n");
    encodeCharacters(root, codeb, 0);


    FILE* file = fopen("hfmtree", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    CodeMap map[27]; // Assuming 27 characters including space
    int mapSize = 0;
    char ch[2];
    char code[100];

    while (fscanf(file, "%s: %s\n", ch, code) == 2) {
        if (strcmp(ch, ":") == 0) { // Handle the space character
            map[mapSize].character = ' ';
            strcpy(map[mapSize].code, code);
        } else {
            map[mapSize].character = ch[0];
            strcpy(map[mapSize].code, code);
        }
        mapSize++;
    }
    fclose(file);

    // Encode "THIS PROGRAM IS MY FAVORITE"
    const char* message = "THIS PROGRAM IS MY FAVORITE";
    printf("Encoded message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        for (int j = 0; j < mapSize; j++) {
            if (map[j].character == message[i]) {
                printf("%s", map[j].code);
                break;
            }
        }
    }
    printf("\n");

    // Decoding
    printf("Decoded message: ");
    char encodedMessage[1000] = "1101000101100011100001001010011000100010101011001001100011110010100011110011101011000001001001001101101010"; // The encoded message goes here
    decodeHuffmanTree(root, encodedMessage);

    freeHuffmanTree(root);

    return 0;
}
