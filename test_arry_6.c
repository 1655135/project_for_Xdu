#include <stdio.h>
#include <stdlib.h>

// 函数用于计算区间查询的异或结果
int* xorQuery(int* arr, int arrSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // 分配结果数组的内存空间
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
    
    // 处理每个查询
    for (int i = 0; i < queriesSize; i++) {
        int left = queries[i][0];   // 查询的左边界
        int right = queries[i][1];   // 查询的右边界
        int xorResult = arr[left];   // 初始化为区间第一个数
        
        // 计算区间异或结果
        for (int j = left + 1; j <= right; j++) {
            xorResult ^= arr[j];
        }
        
        result[i] = xorResult;  // 存储当前查询的结果
    }
    
    return result;
}

// 主函数
int main() {
    int arrSize;
    printf("请输入数组的大小：");
    scanf("%d", &arrSize);
    
    // 验证数组大小的有效性
    if (arrSize <= 0) {
        printf("错误：数组大小必须大于0\n");
        return 1;
    }
    
    // 动态分配数组内存
    int* arr = (int*)malloc(arrSize * sizeof(int));
    if (arr == NULL) {
        printf("错误：内存分配失败\n");
        return 1;
    }
    
    // 输入数组元素
    printf("请输入%d个数组元素：\n", arrSize);
    for (int i = 0; i < arrSize; i++) {
        scanf("%d", &arr[i]);
    }
    
    // 输入查询数量
    int queriesSize;
    printf("请输入查询的数量：");
    scanf("%d", &queriesSize);
    
    // 验证查询数量的有效性
    if (queriesSize <= 0) {
        printf("错误：查询数量必须大于0\n");
        free(arr);
        return 1;
    }
    
    // 动态分配查询数组内存
    int** queries = (int**)malloc(queriesSize * sizeof(int*));
    if (queries == NULL) {
        printf("错误：内存分配失败\n");
        free(arr);
        return 1;
    }
    
    for (int i = 0; i < queriesSize; i++) {
        queries[i] = (int*)malloc(2 * sizeof(int));
        if (queries[i] == NULL) {
            // 释放之前分配的内存
            for (int j = 0; j < i; j++) {
                free(queries[j]);
            }
            free(queries);
            free(arr);
            printf("错误：内存分配失败\n");
            return 1;
        }
    }
    
    // 输入查询区间
    printf("请输入%d个查询区间（每行输入两个数表示区间的左右边界）：\n", queriesSize);
    for (int i = 0; i < queriesSize; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
        
        // 验证查询区间的有效性
        if (queries[i][0] < 0 || queries[i][1] >= arrSize || queries[i][0] > queries[i][1]) {
            printf("错误：查询区间[%d, %d]无效\n", queries[i][0], queries[i][1]);
            // 释放所有分配的内存
            for (int j = 0; j < queriesSize; j++) {
                free(queries[j]);
            }
            free(queries);
            free(arr);
            return 1;
        }
    }
    
    int queriesColSize = 2;
    int returnSize;
    
    // 计算查询结果
    int* result = xorQuery(arr, arrSize, queries, queriesSize, &queriesColSize, &returnSize);
    
    // 打印结果
    printf("查询结果：\n");
    for (int i = 0; i < returnSize; i++) {
        printf("区间[%d, %d]的异或结果：%d\n", queries[i][0], queries[i][1], result[i]);
    }
    
    // 释放所有分配的内存
    for (int i = 0; i < queriesSize; i++) {
        free(queries[i]);
    }
    free(queries);
    free(arr);
    free(result);
    
    // 等待用户输入后退出
    printf("按回车键退出...\n");
    getchar(); // 消耗掉之前的回车
    getchar();
    return 0;
}