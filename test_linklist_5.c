#include <stdio.h>
#include <stdlib.h>

// 定义双向循环链表节点结构
typedef struct Node {
    char data;
    struct Node *prev;
    struct Node *next;
} Node;

// 创建头结点
Node* createList() {
    Node *head = (Node*)malloc(sizeof(Node));
    if (head == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    head->prev = head;
    head->next = head;
    return head;
}

// 头插法建立链表
void insertAtHead(Node *head, char data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = head->next;
    newNode->prev = head;
    head->next->prev = newNode;
    head->next = newNode;
}

// 尾插法建立链表
void insertAtTail(Node *head, char data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = head;
    newNode->prev = head->prev;
    head->prev->next = newNode;
    head->prev = newNode;
}

// 查找节点
Node* findNode(Node *head, char data) {
    Node *current = head->next;
    while (current != head) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 删除节点
void deleteNode(Node *node) {
    if (node == NULL) return;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}

// 按升序插入节点
void insertInOrder(Node *head, char data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->data = data;
    
    Node *current = head->next;
    while (current != head && current->data < data) {
        current = current->next;
    }
    
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
}

// 降序排序链表
void sortDescending(Node *head) {
    Node *i, *j;
    char temp;
    for (i = head->next; i != head; i = i->next) {
        for (j = i->next; j != head; j = j->next) {
            if (i->data < j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// 合并两个链表
void mergeLists(Node *list1, Node *list2) {
    Node *last1 = list1->prev;
    Node *first2 = list2->next;
    Node *last2 = list2->prev;
    
    last1->next = first2;
    first2->prev = last1;
    last2->next = list1;
    list1->prev = last2;
    
    // 释放list2的头结点
    free(list2);
}

// 打印链表
void printList(Node *head) {
    Node *current = head->next;
    while (current != head) {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    // 1) 创建两个链表
    Node *list1 = createList();
    Node *list2 = createList();
    
    // 使用头插法建立第一个链表
    char str1[] = "ABCEFG";
    for (int i = 0; str1[i] != '\0'; i++) {
        insertAtHead(list1, str1[i]);
    }
    printf("链表1（头插法）：");
    printList(list1);
    
    // 使用尾插法建立第二个链表
    char str2[] = "HJIKOMLN";
    for (int i = 0; str2[i] != '\0'; i++) {
        insertAtTail(list2, str2[i]);
    }
    printf("链表2（尾插法）：");
    printList(list2);
    
    // 2) 从链表2中删除'O'
    Node *nodeO = findNode(list2, 'O');
    if (nodeO != NULL) {
        deleteNode(nodeO);
        printf("删除'O'后的链表2：");
        printList(list2);
    }
    
    // 3) 在链表1中按升序插入'D'
    insertInOrder(list1, 'D');
    printf("插入'D'后的链表1：");
    printList(list1);
    
    // 4) 将链表2按降序重新排列
    sortDescending(list2);
    printf("降序排列后的链表2：");
    printList(list2);
    
    // 5) 合并两个链表
    mergeLists(list1, list2);
    printf("合并后的链表：");
    printList(list1);
    
    return 0;
}