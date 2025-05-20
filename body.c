#include "head.h"
#include "stdio.h"

MorseNode* createNode(char symbol) {
    MorseNode* node = (MorseNode*)malloc(sizeof(MorseNode));
    node->symbol = symbol;
    node->dot = node->dash = NULL;
    return node;
}

void insert(MorseNode* root, const char* code, char symbol) {
    MorseNode* current = root;
    while (*code) {
        if (*code == '.') {
            if (current->dot == NULL)
                current->dot = createNode('\0');
            current = current->dot;
        } else if (*code == '-') {
            if (current->dash == NULL)
                current->dash = createNode('\0');
            current = current->dash;
        }
        code++;
    }
    current->symbol = symbol;
}

void buildTree(MorseNode* root) {
    struct { char symbol; const char* code; } table[] = {
        {'A', "."},   {'B', ".."}, {'C', ".-"}, {'D', "..."},
        {'E', "..-"},    {'F', ".-."}, {'G', ".--"},  {'H', "...."},
        {'I', "...-"},   {'J', "..-."}, {'K', ".-.."},  {'L', ".--."},
        {'M', ".---"},   {'N', "-"},   {'O', "-."},  {'P', "--"},
        {'Q', "-.."}, {'R', "-.-"},  {'S', "--."},  {'T', "---"},
        {'U', "-..."},  {'V', "-..-"}, {'W', "-.-."},  {'X', "-.--"},
        {'Y', "--.."}, {'Z', "--.-"},
        {'1', ".----"},{'2', "..---"},{'3', "...--"},{'4', "....-"},
        {'5', "....."},{'6', "-...."},{'7', "--..."},{'8', "---.."},
        {'9', "----."},{'0', "-----"}, {' ', ".-..-."}
    };

    int size = sizeof(table) / sizeof(table[0]);
    for (int i = 0; i < size; i++) {
        insert(root, table[i].code, table[i].symbol);
    }
}

void inorder(MorseNode* root) {
    if (!root) return;
    inorder(root->dot);
    if (root->symbol) printf("%c ", root->symbol);
    inorder(root->dash);
}

int findCode(MorseNode* root, char symbol, char* buffer, int depth) {
    if (!root) return 0;
    if (root->symbol == symbol) {
        buffer[depth] = '\0';
        return 1;
    }

    buffer[depth] = '.';
    if (findCode(root->dot, symbol, buffer, depth + 1)) return 1;

    buffer[depth] = '-';
    if (findCode(root->dash, symbol, buffer, depth + 1)) return 1;

    return 0;
}

void encodeText(MorseNode* root, const char* text, FILE* out) {
    char code[10];
    while (*text) {
        if (*text == ' ') {
            fprintf(out, ".-..-. ");
        } else {
            char upper = toupper(*text);
            if (findCode(root, upper, code, 0)) {
                fprintf(out, "%s ", code);
            }
        }
        text++;
    }
}

void decodeCode(MorseNode* root, const char* code, FILE* out) {
    MorseNode* current = root;
    while (*code) {
        if (*code == '.') current = current->dot;
        else if (*code == '-') current = current->dash;
        else break;
        code++;
    }
    if (current && current->symbol)
        fprintf(out, "%c", current->symbol);
}

void decodeMorse(MorseNode* root, const char* morse, FILE* output) {
    char morseCopy[1024];
    strcpy(morseCopy, morse);  // supaya strtok tidak mengubah string asli

    char* token = strtok(morseCopy, " ");
    while (token) {
        if (strcmp(token, "/") == 0) {
            fputc(' ', output);  // pemisah kata
        } else {
            MorseNode* current = root;
            for (int i = 0; token[i]; i++) {
                if (token[i] == '.')
                    current = current->dot;
                else if (token[i] == '-')
                    current = current->dash;

                if (!current) break;
            }

            if (current && current->symbol)
                fputc(current->symbol, output);
            else
                fputc('?', output);  // simbol tak dikenal
        }

        token = strtok(NULL, " ");
    }
}

void convertTxt(MorseNode* root, const char* inputFile, const char* outputFile) {
    FILE* input = fopen(inputFile, "r");
    FILE* output = fopen(outputFile, "w");

    if (!input || !output) {
        printf("Gagal membuka file %s atau %s.\n", inputFile, outputFile);
        if (input) fclose(input);
        if (output) fclose(output);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), input)) {
        line[strcspn(line, "\n")] = 0;

        encodeText(root, line, output);
        fprintf(output, "\n");
    }

    fclose(input);
    fclose(output);

    printf("Konversi berhasil. Hasil disimpan di %s\n", outputFile);
}
