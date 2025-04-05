#include "stdio.h"

#define MAX_SIZE 50

typedef struct {
    int num[MAX_SIZE];
    int length;
} SeqList;

// 初始化顺序表
void initList(SeqList* list) {
    list->length = 0;
}

// 输入数据到顺序表
void inputList(SeqList* list, int n) {
    printf("请输入%d个有序整数：\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &list->num[i]);
    }
    list->length = n;
}

// 合并两个有序数组
void merge(SeqList* nums1, int m, SeqList* nums2, int n) {
    int i = m - 1;    // nums1的末尾索引
    int j = n - 1;    // nums2的末尾索引
    int k = m + n - 1;  // 合并后的末尾索引

    // 从后向前比较并合并
    while (j >= 0) {
        if (i >= 0 && nums1->num[i] > nums2->num[j]) {
            nums1->num[k] = nums1->num[i];
            i--;
        } else {
            nums1->num[k] = nums2->num[j];
            j--;
        }
        k--;
    }
    nums1->length = m + n;
}

// 打印顺序表
void printList(SeqList* list) {
    printf("合并后的数组：\n");
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->num[i]);
    }
    printf("\n");
}

int main() {
    SeqList nums1, nums2;
    int m, n;

    // 初始化顺序表
    initList(&nums1);
    initList(&nums2);

    // 输入第一个数组的长度和元素
    printf("请输入第一个数组的长度：");
    scanf("%d", &m);
    inputList(&nums1, m);

    // 输入第二个数组的长度和元素
    printf("请输入第二个数组的长度：");
    scanf("%d", &n);
    inputList(&nums2, n);

    // 合并数组
    merge(&nums1, m, &nums2, n);

    // 打印结果
    printList(&nums1);

     // 等待用户输入后退出
     printf("按回车键退出...\n");
     getchar(); // 消耗掉之前的回车
     getchar();

    return 0;
}
