#include <stdio.h>

// 打印3x6矩阵
void print_matrix_3x6(int matrix[3][6], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 打印6x3矩阵
void print_matrix_6x3(int matrix[6][3], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 矩阵转置：将3x6矩阵转换为6x3矩阵
void transpose(int source[3][6], int dest[6][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            dest[j][i] = source[i][j];
        }
    }
}

// 矩阵加法：将两个3x6矩阵相加
void add_matrices(int matrix1[3][6], int matrix2[3][6], int result[3][6]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// 矩阵乘法：将3x6矩阵与6x3矩阵相乘，结果为3x3矩阵
void multiply_matrices(int matrix1[3][6], int matrix2[6][3], int result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 6; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// 打印3x3矩阵
void print_matrix_3x3(int matrix[3][3], const char* name) {
    printf("%s:\n", name);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 打印内存布局信息
void print_memory_layout(int matrix[3][6], const char* name) {
    printf("%s Memory Layout:\n", name);
    printf("Matrix Start Address: %p\n", (void*)matrix);
    
    // 打印每行的起始地址和元素地址
    for (int i = 0; i < 3; i++) {
        printf("Row %d Start Address: %p\n", i+1, (void*)&matrix[i][0]);
        for (int j = 0; j < 6; j++) {
            printf("Element [%d][%d] Address: %p, Value: %d\n", 
                   i, j, (void*)&matrix[i][j], matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // 定义并初始化第一个3x6矩阵
    int matrix1[3][6] = {
        {1, 2, 3, 4, 5, 6},
        {7, 8, 9, 10, 11, 12},
        {13, 14, 15, 16, 17, 18}
    };
    
    // 定义第二个3x6矩阵（通过用户输入）
    int matrix2[3][6];
    
    // 定义6x3矩阵（用于存储转置结果）
    int transposed[6][3];
    
    // 定义3x6矩阵（用于存储加法结果）
    int sum[3][6];
    
    // 定义3x3矩阵（用于存储乘法结果）
    int product[3][3];
    
    // 打印第一个矩阵
    print_matrix_3x6(matrix1, "Matrix 1 (Initialized)");
    
    // 用户输入第二个矩阵
    printf("Please input elements for the second 3x6 matrix (enter 6 integers per row):\n");
    for (int i = 0; i < 3; i++) {
        printf("Enter 6 integers for row %d: ", i+1);
        for (int j = 0; j < 6; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }
    
    // 打印第二个矩阵
    print_matrix_3x6(matrix2, "Matrix 2 (User Input)");
    
    // 观察内存布局
    print_memory_layout(matrix2, "Matrix 2");
    
    // 矩阵转置
    transpose(matrix2, transposed);
    print_matrix_6x3(transposed, "Transpose of Matrix 2");
    
    // 矩阵加法
    add_matrices(matrix1, matrix2, sum);
    print_matrix_3x6(sum, "Matrix 1 + Matrix 2");
    
    // 矩阵乘法
    multiply_matrices(sum, transposed, product);
    print_matrix_3x3(product, "(Matrix 1 + Matrix 2) × Transposed Matrix");
    
    // 防止程序立即退出
    printf("Press any key to exit...\n");
    getchar(); // 消耗之前输入的回车
    getchar();
    
    return 0;
}