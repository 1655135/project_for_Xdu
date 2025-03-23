#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1000  // 定义顺序表的最大容量

typedef struct {
    char* words[MAX_SIZE];  // 存储单词的指针数组，每个元素指向一个动态分配的字符串
    int length;            // 实际存储的单词数量
} SeqList;


void initSeqList(SeqList* list) {
    list->length = 0;
}

/*
清理顺序表中的内存
list 指向顺序表的指针
 释放所有动态分配的单词内存，并将顺序表长度重置为0
 */
void cleanupSeqList(SeqList* list) {
    for (int i = 0; i < list->length; i++) {
        free(list->words[i]);  // 释放每个单词占用的内存
    }
    list->length = 0;  // 重置顺序表长度
}

/*
 去除字符串首尾的空格
 需要处理的字符串
 返回处理后的字符串（去除首尾空格）
 此函数会修改原字符串，返回的是去除首尾空格后的字符串指针
 */
char* trim(char* str) {
    char* end;
    
    // 跳过开头的所有空格，移动指针直到遇到非空格字符
    while (*str == ' ') str++;
    
    // 如果字符串全是空格，直接返回
    if (*str == 0) return str;
    
    // 找到字符串的最后一个非空格字符
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;
    
    // 在最后一个非空格字符后添加字符串结束符
    *(end + 1) = 0;
    
    return str;
}

/*
  分割字符串并存储到顺序表中
  list 指向顺序表的指针
  str 要分割的字符串
  根据空格分割字符串，将每个单词动态分配内存后存储到顺序表中
 */
void splitAndStore(SeqList* list, char* str) {
    char* start = str;    // 指向当前单词的起始位置
    char* current = str;  // 用于遍历字符串的指针
    
    // 遍历整个字符串
    while (*current != '\0') {
        if (*current == ' ') {  // 遇到空格，表示找到一个单词
            if (current > start) {  // 确保单词长度大于0
                int len = current - start;  // 计算单词长度
                char* word = (char*)malloc(len + 1);  // 为单词分配内存（包括结束符）
                strncpy(word, start, len);  // 复制单词内容
                word[len] = '\0';  // 添加字符串结束符
                list->words[list->length++] = word;  // 将单词存入顺序表
            }
            while (*current == ' ') current++;  // 跳过连续的空格
            start = current;  // 更新下一个单词的起始位置
        } else {
            current++;  // 继续向后遍历
        }
    }
    
    // 处理最后一个单词（如果存在）
    if (current > start) {
        int len = current - start;
        char* word = (char*)malloc(len + 1);
        strncpy(word, start, len);
        word[len] = '\0';
        list->words[list->length++] = word;
    }
}

/**
 * 反转顺序表中的单词顺序
 * @param list 指向顺序表的指针
 * @note 使用双指针法交换单词位置，实现句子的反转
 */
void reverseWords(SeqList* list) {
    int left = 0;                 // 左指针，从前向后移动
    int right = list->length - 1; // 右指针，从后向前移动
    
    // 使用双指针法交换单词位置
    while (left < right) {
        char* temp = list->words[left];
        list->words[left] = list->words[right];
        list->words[right] = temp;
        left++;
        right--;
    }
}

/**
 * 打印顺序表中的单词
 * @param list 指向顺序表的指针
 * @note 按顺序打印所有单词，单词之间用空格分隔
 */
void printWords(SeqList* list) {
    if (list->length == 0) {  // 处理空顺序表的情况
        printf("\n");
        return;
    }
    
    // 打印第一个单词（不需要前导空格）
    printf("%s", list->words[0]);
    // 打印剩余单词（每个单词前加一个空格）
    for (int i = 1; i < list->length; i++) {
        printf(" %s", list->words[i]);
    }
    printf("\n");
}

/**
  主函数
 程序的入口点，实现英文句子单词顺序的反转功能
 */
int main() {
    char input[MAX_SIZE];  // 用于存储用户输入的字符串
    SeqList list;          // 定义顺序表结构
    
    // 初始化顺序表
    initSeqList(&list);
    
    // 获取用户输入的英文句子
    printf("请输入一个英文句子：\n");
    fgets(input, MAX_SIZE, stdin);
    
    // 去除输入字符串末尾的换行符
    input[strcspn(input, "\n")] = 0;
    
    // 处理输入的字符串：去除首尾空格，分割单词并存储
    char* trimmed = trim(input);
    splitAndStore(&list, trimmed);
    
    // 反转单词顺序
    reverseWords(&list);
    
    // 输出反转后的结果
    printf("反转后的句子：\n");
    printWords(&list);
    
    // 清理动态分配的内存
    cleanupSeqList(&list);
    while (1);
    
    return 0;
}