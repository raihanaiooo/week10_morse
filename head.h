#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct MorseNode {
    char symbol;
    struct MorseNode *dot;
    struct MorseNode *dash;
} MorseNode;

MorseNode* createNode(char symbol);
void insert(MorseNode* root, const char* code, char symbol);
void buildTree(MorseNode* root);
void inorder(MorseNode* root);
int findCode(MorseNode* root, char symbol, char* buffer, int depth);
void encodeText(MorseNode* root, const char* text, FILE* out);
void decodeCode(MorseNode* root, const char* code, FILE* out);
void decodeMorse(MorseNode* root, const char* morse, FILE* out);
void convertTxt(MorseNode* root, const char* inputFile, const char* outputFile);