#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

// 顺序表结构定义
typedef struct {
    int data[MAXSIZE];
    int length;
} SeqList;

// 初始化顺序表
void initList(SeqList *L) {
    L->length = 0;
}

// 插入元素
int insert(SeqList *L, int x) {
    if (L->length >= MAXSIZE) {
        printf("顺序表已满！\n");
        return 0;
    }
    L->data[L->length++] = x;
    return 1;
}

// 比较函数，用于降序排序
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// 计算数组元素和
int sum(int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

// 找到满足条件的最小子序列
SeqList findSubsequence(SeqList *L) {
    SeqList result;
    initList(&result);
    
    // 对原数组进行降序排序
    qsort(L->data, L->length, sizeof(int), compare);
    
    int totalSum = sum(L->data, L->length);
    int subSum = 0;
    
    // 从大到小选择元素，直到子序列和大于剩余元素和
    for (int i = 0; i < L->length; i++) {
        subSum += L->data[i];
        insert(&result, L->data[i]);
        
        // 检查是否满足条件：子序列和严格大于剩余元素和
        if (subSum > (totalSum - subSum)) {
            break;
        }
    }
    
    return result;
}

int main() {
    SeqList L, result;
    initList(&L);
    int n, x;
    
    printf("请输入数组长度：");
    scanf("%d", &n);
    
    printf("请输入数组元素：\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        insert(&L, x);
    }
    
    result = findSubsequence(&L);
    
    printf("满足条件的最小子序列（按非递增顺序）：");
    for (int i = 0; i < result.length; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");
    
   // 等待用户输入后退出
   printf("按回车键退出...\n");
   getchar(); // 消耗掉之前的回车
   getchar();
   
    return 0;
}