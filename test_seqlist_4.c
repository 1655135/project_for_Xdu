#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

// 定义顺序表结构体
typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// 初始化顺序表
void initList(SeqList *list) {
    list->length = 0;
}

// 输入整数序列到顺序表
void inputNumbers(SeqList *list) {
    int num;
    printf("请输入整数序列（输入-1结束）：\n");
    while (1) {
        scanf("%d", &num);
        if (num == -1 || list->length >= MAX_SIZE) {
            break;
        }
        list->data[list->length++] = num;
    }
}

// 调整数字顺序
void adjustOrder(SeqList *list) {
    int even[MAX_SIZE], odd[MAX_SIZE];
    int evenCount = 0, oddCount = 0;
    
    // 分离偶数和奇数
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] % 2 == 0) {
            even[evenCount++] = list->data[i];
        } else {
            odd[oddCount++] = list->data[i];
        }
    }
    
    // 对偶数部分进行升序排序
    for (int i = 0; i < evenCount - 1; i++) {
        for (int j = 0; j < evenCount - 1 - i; j++) {
            if (even[j] > even[j + 1]) {
                int temp = even[j];
                even[j] = even[j + 1];
                even[j + 1] = temp;
            }
        }
    }
    
    // 对奇数部分进行升序排序
    for (int i = 0; i < oddCount - 1; i++) {
        for (int j = 0; j < oddCount - 1 - i; j++) {
            if (odd[j] > odd[j + 1]) {
                int temp = odd[j];
                odd[j] = odd[j + 1];
                odd[j + 1] = temp;
            }
        }
    }
    
    // 合并回原顺序表
    int k = 0;
    // 先放偶数
    for (int i = 0; i < evenCount; i++) {
        list->data[k++] = even[i];
    }
    // 再放奇数
    for (int i = 0; i < oddCount; i++) {
        list->data[k++] = odd[i];
    }
}

// 打印顺序表
void printList(SeqList *list) {
    printf("调整后的序列：\n");
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main() {
    SeqList list;
    initList(&list);
    inputNumbers(&list);
    adjustOrder(&list);
    printList(&list);
    return 0;
}