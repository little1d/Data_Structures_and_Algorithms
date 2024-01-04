#ifndef DATA_STRUCTURES_AND_ALGORITHMS_HUFTREE_GENERATE_H
#define DATA_STRUCTURES_AND_ALGORITHMS_HUFTREE_GENERATE_H

#include<stdio.h>
#include<stdlib.h>

// Huffman tree node structure definition
typedef struct HuffmanNode{
    char character;
    char frequency;
    struct HuffmanNode* left;
    struct HuffmanNode* right;
}HuffmanNode;

// Function declaration
HuffmanNode* generateHuffmanTree(int n);
void printHuffmanTree(HuffmanNode* root,int depth);
void encodeCharacters(HuffmanNode* root,char* code,int top);

#endif //DATA_STRUCTURES_AND_ALGORITHMS_HUFTREE_GENERATE_H
