#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 定义顺序表结构
typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// 初始化顺序表
void initList(SeqList *list) {
    list->length = 0;
}

// 输入数据
void inputNumbers(SeqList *list) {
    int num;
    printf("请输入升序排列的整数序列（输入-1结束）：\n");
    while (1) {
        scanf("%d", &num);
        if (num == -1 || list->length >= MAX_SIZE) {
            break;
        }
        list->data[list->length++] = num;
    }
}

// 查找两数之和等于目标值的下标
void findTwoSum(SeqList *list, int target, int *index1, int *index2) {
    int left = 0;
    int right = list->length - 1;
    
    while (left < right) {
        int sum = list->data[left] + list->data[right];
        if (sum == target) {
            *index1 = left + 1;  // 返回的下标从1开始
            *index2 = right + 1;
            return;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    // 如果没有找到符合条件的数对
    *index1 = -1;
    *index2 = -1;
}

int main() {
    SeqList list;
    int target, index1, index2;
    
    initList(&list);
    inputNumbers(&list);
    
    printf("请输入目标数：");
    scanf("%d", &target);
    
    findTwoSum(&list, target, &index1, &index2);
    
    if (index1 != -1 && index2 != -1) {
        printf("输出: [%d,%d]\n", index1, index2);
        printf("解释: %d 与 %d 之和等于目标数 %d。\n", 
               list.data[index1-1], list.data[index2-1], target);
    } else {
        printf("未找到符合条件的两个数。\n");
    }
    
    
     // 等待用户输入后退出
     printf("按回车键退出...\n");
     getchar(); // 消耗掉之前的回车
     getchar();
     
    return 0;
}