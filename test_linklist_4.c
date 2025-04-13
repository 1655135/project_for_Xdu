#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

// 创建新节点的辅助函数
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// 插入排序函数
ListNode* insertionSortList(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 创建哨兵节点作为已排序部分的头节点
    ListNode* dummy = createNode(0);
    ListNode* curr = head;
    
    while (curr != NULL) {
        // 保存下一个待处理的节点
        ListNode* next = curr->next;
        
        // 在已排序部分找到插入位置
        ListNode* prev = dummy;
        while (prev->next != NULL && prev->next->val < curr->val) {
            prev = prev->next;
        }
        
        // 插入当前节点
        curr->next = prev->next;
        prev->next = curr;
        
        // 移动到下一个待排序节点
        curr = next;
    }
    
    return dummy->next;
}

// 打印链表的辅助函数
void printList(ListNode* head) {
    ListNode* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
}

// 释放链表内存的辅助函数
void freeList(ListNode* head) {
    ListNode* curr = head;
    while (curr != NULL) {
        ListNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// 主函数用于测试
int main() {
    // 创建测试链表: 4->2->1->3
    ListNode* head = createNode(4);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(3);

    printf("原始链表: ");
    printList(head);

    // 执行插入排序
    head = insertionSortList(head);

    printf("排序后链表: ");
    printList(head);

    // 释放内存
    freeList(head);

    // 等待用户输入后退出
    printf("按回车键退出...\n");
    getchar(); // 消耗掉之前的回车
    getchar();
    
    return 0;
}