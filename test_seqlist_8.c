#include <stdio.h>
#include <stdlib.h>

#define MAX_STRINGS 10    // 最大字符串数量
#define MAX_LENGTH 100   // 每个字符串的最大长度

// 自定义字符串比较函数
int my_strcmp(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return *str1 - *str2;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// 自定义字符串复制函数
char* my_strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original_dest;
}

// 自定义字符串长度函数
int my_strlen(const char* str) {
    int len = 0;
    while (*str) {
        len++;
        str++;
    }
    return len;
}

// 查找字符串函数
int findString(char* strings[], const char* target) {
    for (int i = 0; i < MAX_STRINGS; i++) {
        if (strings[i] && my_strcmp(strings[i], target) == 0) {
            return i;
        }
    }
    return -1;
}

// 修改字符串函数
int modifyString(char* strings[], const char* old_str, const char* new_str) {
    int index = findString(strings, old_str);
    if (index == -1) {
        return 0;  // 未找到字符串
    }
    
    // 释放原有内存
    free(strings[index]);
    
    // 分配新内存并复制新字符串
    int len = my_strlen(new_str);
    strings[index] = (char*)malloc(len + 1);
    if (!strings[index]) {
        return 0;  // 内存分配失败
    }
    
    my_strcpy(strings[index], new_str);
    return 1;
}

// 删除字符串函数
int deleteString(char* strings[], const char* target) {
    int index = findString(strings, target);
    if (index == -1) {
        return 0;  // 未找到字符串
    }
    
    // 释放内存
    free(strings[index]);
    strings[index] = NULL;
    
    // 移动后续字符串
    for (int i = index; i < MAX_STRINGS - 1; i++) {
        strings[i] = strings[i + 1];
    }
    strings[MAX_STRINGS - 1] = NULL;
    
    return 1;
}

// 复制字符串函数
char* copyString(const char* source) {
    if (!source) {
        return NULL;
    }
    
    int len = my_strlen(source);
    char* new_str = (char*)malloc(len + 1);
    if (!new_str) {
        return NULL;
    }
    
    return my_strcpy(new_str, source);
}

int main() {
    // 初始化字符串数组
    char* strings[MAX_STRINGS] = {NULL};
    
    // 添加一些测试字符串
    const char* test_strings[] = {
        "Hello", "World", "Programming", "C Language",
        "Data Structure", "Algorithm", "String", "Array",
        "Pointer", "Function"
    };
    
    // 初始化数组
    for (int i = 0; i < MAX_STRINGS; i++) {
        strings[i] = copyString(test_strings[i]);
    }
    
    // 打印初始字符串
    printf("初始字符串列表：\n");
    for (int i = 0; i < MAX_STRINGS; i++) {
        if (strings[i]) {
            printf("%d: %s\n", i, strings[i]);
        }
    }
    
    // 测试查找功能
    const char* search_str = "Programming";
    int found_index = findString(strings, search_str);
    printf("\n查找字符串 \"%s\"：%s (索引: %d)\n",
           search_str,
           found_index != -1 ? "找到了" : "未找到",
           found_index);
    
    // 测试修改功能
    const char* old_str = "World";
    const char* new_str = "Universe";
    if (modifyString(strings, old_str, new_str)) {
        printf("\n成功将 \"%s\" 修改为 \"%s\"\n", old_str, new_str);
    }
    
    // 测试删除功能
    const char* del_str = "Array";
    if (deleteString(strings, del_str)) {
        printf("\n成功删除字符串 \"%s\"\n", del_str);
    }
    
    // 测试复制功能
    const char* copy_str = "Algorithm";
    char* copied = copyString(copy_str);
    if (copied) {
        printf("\n成功复制字符串 \"%s\"\n", copied);
        free(copied);  // 释放复制的内存
    }
    
    // 打印最终字符串列表
    printf("\n最终字符串列表：\n");
    for (int i = 0; i < MAX_STRINGS; i++) {
        if (strings[i]) {
            printf("%d: %s\n", i, strings[i]);
        }
    }
    
    // 清理内存
    for (int i = 0; i < MAX_STRINGS; i++) {
        free(strings[i]);
    }
    
    return 0;
}