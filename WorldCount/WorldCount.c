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

// 统计文件中的字符数，包括空格、制表符和换行符
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

// 统计文件中的单词数，单词由空格或逗号分隔
int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[1024]; // 假设没有超过1024字符的行
    int wordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        char *word = strtok(line, " ,\t\n"); // 使用空格或逗号作为分隔符
        while (word) {
            wordCount++;
            word = strtok(NULL, " ,\t\n");
        }
    }
    fclose(file);
    return wordCount;
}
