#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 统计文件中的字符数
void countCharacters(const char* filename) {
    FILE* file = fopen(filename, "r");  // 以只读模式打开文件
    if (file == NULL) {  // 如果文件打开失败
        printf("Could not open file %s\n", filename);  // 输出错误信息
        return;
    }
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {  // 逐个读取文件中的字符
        count++;  // 统计字符数
    }
    fclose(file);  // 关闭文件
    printf("字符数：%d\n", count);
}

// 统计文件中的单词数
void countWords(const char* filename) {
    FILE* file = fopen(filename, "r");  // 以只读模式打开文件
    if (file == NULL) {  // 如果文件打开失败
        printf("Could not open file %s\n", filename);  // 输出错误信息
        return;
    }
    int count = 0;
    char c;
    int inWord = 0;  // 标志当前是否在单词中
    while ((c = fgetc(file)) != EOF) {  // 逐个读取文件中的字符
        if (isspace(c) || c == ',') {  // 如果当前字符是空白字符或逗号
            if (inWord) {  // 如果之前在单词中
                count++;  // 单词计数加一
                inWord = 0;  // 重置单词标志
            }
        }
        else {
            inWord = 1;  // 标记进入单词
        }
    }
    if (inWord) {  // 如果文件以单词结束
        count++;  // 单词计数加一
    }
    fclose(file);  // 关闭文件
    printf("单词数：%d\n", count);
}

// 解析命令行参数并调用相应的统计函数
int main(int argc, char* argv[]) {
    // 设置控制台输出为UTF-8
    SetConsoleOutputCP(CP_UTF8);

    if (argc != 3) {  // 检查命令行参数的数量
        printf("Usage: %s -c|-w filename\n", argv[0]);  // 输出使用说明
        return 1;
    }
    if (strcmp(argv[1], "-c") == 0) {  // 如果参数是-c
        countCharacters(argv[2]);  // 调用统计字符数函数
    }
    else if (strcmp(argv[1], "-w") == 0) {  // 如果参数是-w
        countWords(argv[2]);  // 调用统计单词数函数
    }
    else {
        printf("Invalid option %s\n", argv[1]);  // 输出错误信息
        return 1;
    }
    return 0;
}
