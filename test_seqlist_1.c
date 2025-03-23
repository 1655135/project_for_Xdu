#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100  // 定义最大表长

typedef struct {
    int data[MAX_SIZE];  // 存储数据的数组
    int length;          // 当前顺序表长度
} SeqList;

// 初始化顺序表
void initList(SeqList* list) {
    list->length = 0;
}

// create函数：创建并初始化顺序表
void create(SeqList* list) {
    int n;
    printf("请输入表长（不超过%d）：", MAX_SIZE);
    scanf("%d", &n);
    
    if (n <= 0 || n > MAX_SIZE) {
        printf("表长无效，应在1到%d之间\n", MAX_SIZE);
        return;
    }
    
    printf("请输入%d个整数：\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &list->data[i]);
    }
    list->length = n;
}

// insert函数：根据index表的值将num表的数据插入target表
void insert(SeqList* num, SeqList* index, SeqList* target) {
    // 检查num和index表长是否相等
    if (num->length != index->length) {
        printf("错误：num表和index表的长度不相等\n");
        return;
    }
    
    // 初始化target表
    initList(target);
    
    // 遍历num和index表
    for (int i = 0; i < num->length; i++) {
        int pos = index->data[i];  // 获取插入位置
        int value = num->data[i];  // 获取要插入的值
        
        // 检查插入位置是否有效
        if (pos < 0 || pos >= MAX_SIZE) {
            printf("错误：位置%d超出有效范围\n", pos);
            continue;
        }
        
        // 如果插入位置超过当前target表长度，则将target表扩展到该位置
        if (pos >= target->length) {
            target->length = pos + 1;
        }
        
        // 在指定位置插入数据
        target->data[pos] = value;
    }
}

// 打印顺序表
void printList(SeqList* list) {
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main() {
    SeqList num, index, target;  // 定义三个顺序表
    
    // 初始化顺序表
    initList(&num);
    initList(&index);
    initList(&target);
    
    // 创建num表
    printf("创建num表:\n");
    create(&num);
    
    // 创建index表
    printf("\n创建index表:\n");
    create(&index);
    
    // 执行插入操作
    insert(&num, &index, &target);
    
    // 输出结果
    printf("\n插入结果:\n");
    printList(&target);
    
    while(1);
    return 0;
}