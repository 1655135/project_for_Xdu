#include <stdio.h>
#include <stdlib.h>

// 定义顺序表结构
typedef struct {
    int* data;
    int length;
    int capacity;
} SeqList;

// 初始化顺序表
SeqList* initSeqList(int capacity) {
    SeqList* list = (SeqList*)malloc(sizeof(SeqList));
    list->data = (int*)malloc(sizeof(int) * capacity);
    list->length = 0;
    list->capacity = capacity;
    return list;
}

// 在指定位置插入元素
void insert(SeqList* list, int index, int value) {
    if (index < 0 || index > list->length) return;
    for (int i = list->length; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = value;
    list->length++;
}

// 删除并返回指定位置的元素
int removeAt(SeqList* list, int index) {
    if (index < 0 || index >= list->length) return -1;
    int value = list->data[index];
    for (int i = index; i < list->length - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->length--;
    return value;
}

// 释放顺序表内存
void freeSeqList(SeqList* list) {
    free(list->data);
    free(list);
}

// 求解卡牌排序问题
int* deckRevealedIncreasing(int* deck, int deckSize) {
    // 对原数组进行排序
    for (int i = 0; i < deckSize - 1; i++) {
        for (int j = 0; j < deckSize - 1 - i; j++) {
            if (deck[j] > deck[j + 1]) {
                int temp = deck[j];
                deck[j] = deck[j + 1];
                deck[j + 1] = temp;
            }
        }
    }

    // 初始化顺序表
    SeqList* list = initSeqList(deckSize);
    int* result = (int*)malloc(sizeof(int) * deckSize);

    // 从后向前模拟过程
    for (int i = deckSize - 1; i >= 0; i--) {
        if (list->length > 0) {
            // 将最后一个元素移到开头
            int value = removeAt(list, list->length - 1);
            insert(list, 0, value);
        }
        // 将当前牌放入开头
        insert(list, 0, deck[i]);
    }

    // 将顺序表中的牌复制到结果数组
    for (int i = 0; i < deckSize; i++) {
        result[i] = list->data[i];
    }

    // 释放顺序表内存
    freeSeqList(list);
    return result;
}

// 主函数用于测试
int main() {
    int deckSize;
    printf("请输入卡牌数量: ");
    if (scanf("%d", &deckSize) != 1 || deckSize <= 0) {
        printf("输入无效，请输入一个正整数\n");
        return 1;
    }

    int* deck = (int*)malloc(sizeof(int) * deckSize);
    if (deck == NULL) {
        printf("内存分配失败\n");
        return 1;
    }

    printf("请依次输入%d个整数:\n", deckSize);
    for (int i = 0; i < deckSize; i++) {
        if (scanf("%d", &deck[i]) != 1) {
            printf("输入无效，请确保输入的是整数\n");
            free(deck);
            return 1;
        }
    }

    int* result = deckRevealedIncreasing(deck, deckSize);

    printf("输出结果: ");
    for (int i = 0; i < deckSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(deck);
    free(result);
    // 等待用户输入后退出
    printf("按回车键退出...\n");
    getchar();
    getchar();
    return 0;
}