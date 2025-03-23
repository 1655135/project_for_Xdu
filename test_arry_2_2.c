#include <stdio.h>

int main()
{
    int array[30]; // 定义长度不超过30的一维int数组
    int n, i, j, temp;
    
    // 输入数组长度
    printf("Please enter a positive integer N (not exceeding 30): ");
    scanf("%d", &n);
    
    // 确保n不超过数组最大长度
    if (n <= 0 || n > 30) {
        printf("Invalid N, should be between 1 and 30\n");
        return 1;
    }
    
    // 输入n个整数
    printf("Please enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    
    // 输出原始数组
    printf("Original array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // 使用插入排序算法对数组进行排序
    for (i = 1; i < n; i++) {
        temp = array[i]; // 保存当前要插入的元素
        j = i - 1;
        
        // 将大于temp的元素向后移动
        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            j--;
        }
        
        // 在正确的位置插入temp
        array[j + 1] = temp;
    }

    // 输出排序后的数组
    printf("Array reordered: ");
    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    while (1);
   
    return 0;
}
    

