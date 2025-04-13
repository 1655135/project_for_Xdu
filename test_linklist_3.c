#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

// 创建新节点
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// 反转链表
ListNode* reverseList(ListNode* head) {
    ListNode *prev = NULL;
    ListNode *curr = head;
    while (curr != NULL) {
        ListNode *nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

// 重排链表
void reorderList(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    // 1. 找到中点
    ListNode *slow = head;
    ListNode *fast = head;
    
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    ListNode *mid = slow->next;
    slow->next = NULL;

    // 2. 反转后半部分
    ListNode *l1 = head;
    ListNode *l2 = reverseList(mid);

    // 3. 合并两个链表
    while (l1 != NULL && l2 != NULL) {
        ListNode *l1_next = l1->next;
        ListNode *l2_next = l2->next;

        l1->next = l2;
        l2->next = l1_next;

        l1 = l1_next;
        l2 = l2_next;
    }
}

// 打印链表
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// 主函数用于测试
int main() {
    // 创建测试链表: 1->2->3->4->5
    ListNode* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    printf("原始链表: ");
    printList(head);

    reorderList(head);

    printf("重排后的链表: ");
    printList(head);

     // 等待用户输入后退出
     printf("按回车键退出...\n");
     getchar(); // 消耗掉之前的回车
     getchar();

    return 0;
}