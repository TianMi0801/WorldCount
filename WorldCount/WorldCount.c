#include <stdio.h>
#include <ctype.h> // for isspace, isalnum
#include <string.h> // for strtok

int countCharacters(const char *filename);
int countWords(const char *filename);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] input_file_name\n", argv[0]);
        return 1;
    }

    const char *param = argv[1];
    const char *filename = argv[2];

    if (strcmp(param, "-c") == 0) {
        printf("Characters: %d\n", countCharacters(filename));
    } else if (strcmp(param, "-w") == 0) {
        printf("Words: %d\n", countWords(filename));
    } else {
        fprintf(stderr, "Invalid parameter. Use -c for characters or -w for words.\n");
        return 1;
    }

    return 0;
}

// ͳ���ļ��е��ַ����������ո��Ʊ���ͻ��з�
int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

// ͳ���ļ��еĵ������������ɿո�򶺺ŷָ�
int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[1024]; // ����û�г���1024�ַ�����
    int wordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        char *word = strtok(line, " ,\t\n"); // ʹ�ÿո�򶺺���Ϊ�ָ���
        while (word) {
            wordCount++;
            word = strtok(NULL, " ,\t\n");
        }
    }
    fclose(file);
    return wordCount;
}
