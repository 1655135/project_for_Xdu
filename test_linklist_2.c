#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义链表节点结构
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

// 检测链表是否有环
bool hasCycle(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;          // 慢指针每次移动一步
        fast = fast->next->next;    // 快指针每次移动两步
        
        if (slow == fast) {         // 如果两个指针相遇，说明存在环
            return true;
        }
    }
    
    return false;  // 如果快指针到达链表尾部，说明不存在环
}

// 创建一个带环的链表用于测试
ListNode* createCycleList(int pos) {
    ListNode* head = createNode(3);
    ListNode* node1 = createNode(2);
    ListNode* node2 = createNode(0);
    ListNode* node3 = createNode(-4);
    
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    
    if (pos >= 0) {
        // 根据pos创建环
        ListNode* cycleNode = head;
        for (int i = 0; i < pos; i++) {
            cycleNode = cycleNode->next;
        }
        node3->next = cycleNode;  // 创建环
    } else {
        node3->next = NULL;      // 不创建环
    }
    
    return head;
}

// 释放链表内存（无环的情况）
void freeList(ListNode* head) {
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
        if(head->val == NULL){
            break;
        }
    }
}

// 打印链表内容（限制最大打印节点数，避免有环链表无限循环）
void printList(ListNode* head) {
    printf("链表内容：");
    ListNode* current = head;
    int count = 0;
    int maxNodes = 10; // 设置最大打印节点数
    
    while (current != NULL && count < maxNodes) {
        printf("%d -> ", current->val);
        current = current->next;
        count++;
    }
    
    if (count >= maxNodes) {
        printf("...（为避免无限循环，仅显示前%d个节点）", maxNodes);
    } else {
        printf("NULL");
    }
    printf("\n");
}

int main() {
    // 测试用例1：有环的链表
    ListNode* cycleList = createCycleList(1);  // 创建一个在位置1处有环的链表
    printf("测试用例1（有环）:\n");
    printList(cycleList);
    printf("是否有环: %s\n\n", hasCycle(cycleList) ? "true" : "false");
    
    // 测试用例2：无环的链表
    ListNode* noCycleList = createCycleList(-1);  // 创建一个无环的链表
    printf("测试用例2（无环）:\n");
    printList(noCycleList);
    printf("是否有环: %s\n\n", hasCycle(noCycleList) ? "true" : "false");
    
    // 释放无环链表的内存
    freeList(noCycleList);
    freeList(cycleList);
    
    
    // 等待用户输入后退出
    printf("按回车键退出...\n");
    getchar(); // 消耗掉之前的回车
    getchar();
    
    return 0;
}