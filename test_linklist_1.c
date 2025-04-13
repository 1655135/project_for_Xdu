#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义链表节点结构
typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

// 获取链表长度
int getLength(ListNode* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

// 查找两个链表的相交节点
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;
    }
    
    // 获取两个链表的长度
    int lenA = getLength(headA);
    int lenB = getLength(headB);
    
    // 让较长的链表先走差值步
    int diff = abs(lenA - lenB);
    ListNode* longList = lenA > lenB ? headA : headB;
    ListNode* shortList = lenA > lenB ? headB : headA;
    
    while (diff > 0) {
        longList = longList->next;
        diff--;
    }
    
    // 两个链表同时遍历，找到相交点
    while (longList != NULL && shortList != NULL) {
        if (longList == shortList) {
            return longList;
        }
        longList = longList->next;
        shortList = shortList->next;
    }
    
    return NULL;
}

// 创建新节点
ListNode* createNode(int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// 释放链表内存
void freeList(ListNode* head, ListNode* intersection) {
    while (head != intersection && head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // 创建测试用例
    // 链表A: 4->1->8->4->5
    // 链表B: 5->0->1->8->4->5
    // 相交节点值为8
    
    ListNode* headA = createNode(4);
    headA->next = createNode(1);
    
    ListNode* headB = createNode(5);
    headB->next = createNode(0);
    headB->next->next = createNode(1);
    
    // 创建相交部分
    ListNode* intersection = createNode(8);
    intersection->next = createNode(4);
    intersection->next->next = createNode(5);
    
    // 连接相交部分
    headA->next->next = intersection;
    headB->next->next->next = intersection;
    
    // 打印查找前的链表结构
    printf("Before finding intersection:\n");
    printf("List A: ");
    ListNode* tempA = headA;
    while (tempA != NULL) {
        printf("%d -> ", tempA->val);
        tempA = tempA->next;
    }
    printf("NULL\n");
    
    printf("List B: ");
    ListNode* tempB = headB;
    while (tempB != NULL) {
        printf("%d -> ", tempB->val);
        tempB = tempB->next;
    }
    printf("NULL\n");

    // 查找相交节点
    ListNode* result = getIntersectionNode(headA, headB);
    
    // 输出结果
    if (result != NULL) {
        printf("\nFound intersection node with value: %d\n", result->val);
    } else {
        printf("\nNo intersection found\n");
    }

    // 打印查找后的链表结构，验证结构未被改变
    printf("\nAfter finding intersection:\n");
    printf("List A: ");
    tempA = headA;
    while (tempA != NULL) {
        printf("%d -> ", tempA->val);
        tempA = tempA->next;
    }
    printf("NULL\n");
    
    printf("List B: ");
    tempB = headB;
    while (tempB != NULL) {
        printf("%d -> ", tempB->val);
        tempB = tempB->next;
    }
    printf("NULL\n");
    
    // 释放内存
    freeList(headA, intersection);
    freeList(headB, intersection);
    freeList(intersection, NULL);
    
    // 等待用户输入后退出
    printf("Press Enter to exit...\n");
    getchar();
    
    return 0;
}