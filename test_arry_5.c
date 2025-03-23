#include <stdio.h>
#include <string.h>

// 排序函数，对字符数组进行升序排序
void sort(char arr[], int length) {
    int i, j;
    char temp;
    
    // 使用插入排序算法
    for (i = 1; i < length; i++) {
        temp = arr[i]; // 保存当前要插入的元素
        j = i - 1;
        
        // 将大于temp的元素向后移动
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        
        // 在正确的位置插入temp
        arr[j + 1] = temp;
    }
}

int main() {
    // 定义一个字符数组并初始化
    char charArray[] = "Hello World! 123";
    int length = strlen(charArray);
    
    // 输出排序前的数组
    printf("排序前的字符数组: %s\n", charArray);
    
    // 按字符打印，更清晰地展示每个字符
    printf("排序前的字符（按字符打印）: ");
    for (int i = 0; i < length; i++) {
        printf("%c ", charArray[i]);
    }
    printf("\n");
    
    // 调用排序函数
    sort(charArray, length);
    
    // 输出排序后的数组
    printf("排序后的字符数组: %s\n", charArray);
    
    // 按字符打印，更清晰地展示每个字符
    printf("排序后的字符（按字符打印）: ");
    for (int i = 0; i < length; i++) {
        printf("%c ", charArray[i]);
    }
    printf("\n");
    
    // 等待用户输入后退出
    printf("按回车键退出...\n");
    getchar();
    
    return 0;
}