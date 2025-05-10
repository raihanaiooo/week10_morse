#include <stdio.h>
#include "head.h"

int main() {
    MorseNode* root = createNode('\0');
    buildTree(root);

    int choice;
    char input[256];

    printf("Hasil Traversal Inorder\n");
    inorder(root);
    printf("\nMORSE CODE CONVERTER\n");
    printf("1. Encode (Text to Morse)\n");
    printf("2. Decode (Morse to Text)\n");
    printf("Pilih opsi (1/2): ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Masukkan teks: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        printf("Kode Morse: ");
        encodeText(root, input, stdout);
        printf("\n");
    } else if (choice == 2) {
        printf("Masukkan kode Morse: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        printf("Hasil Decode: ");
        decodeMorse(root, input, stdout);
        printf("\n");
    } else {
        printf("Pilihan tidak valid.\n");
    }

    return 0;
}
