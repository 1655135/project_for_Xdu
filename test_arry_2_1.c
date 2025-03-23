#include <stdio.h>

int main()
{
    int array[30]; // 定义长度不超过30的一维int数组
    int n, i, m, key, pos = -1 ,num=1 ;
    
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
    
    // 输入关键字
    printf("Please enter the key to search: ");
    scanf("%d", &key);
   
        // 查找关键字
        
        for (i = 0; i < n; i++) {
            m=num;
            if (array[i] == key) {
                pos = i;
                printf("Key %d found at position: %d\n",key,pos+num);
              // 删除元素（后续元素前移）
                for (int c = pos; c < n - 1; c++) {
                    array[c] = array[c + 1];
                } 
                n--;
                num++;
            }
            if (num-m==1){
                i--;
            }                                   
         }
        if (pos==-1) {
            printf("Key %d not found\n", key);
         }

     // 输出删除后的数组
     printf("Array after deletion: ");
     for (i = 0; i < n; i++) {
         printf("%d ", array[i]);
     }
     printf("\n");
    while (1);
    
    return 0;
}