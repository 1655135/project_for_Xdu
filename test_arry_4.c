#include <stdio.h>
#include <stdlib.h>

// 定义三元组结构体
typedef struct {
    int row;    // 行下标
    int col;    // 列下标
    int value;  // 元素值
} Triple;

// 定义稀疏矩阵结构体
typedef struct {
    Triple data[100];  // 三元组表，假设最多存储100个非零元素
    int num;           // 非零元素个数
    int rows;          // 矩阵行数
    int cols;          // 矩阵列数
} SparseMatrix;

// 打印普通矩阵
void print_matrix(int matrix[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 将普通矩阵转换为三元组表示
void convert_to_sparse(int matrix[10][10], SparseMatrix* sparse) {
    sparse->rows = 10;
    sparse->cols = 10;
    sparse->num = 0;
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (matrix[i][j] != 0) {
                sparse->data[sparse->num].row = i;
                sparse->data[sparse->num].col = j;
                sparse->data[sparse->num].value = matrix[i][j];
                sparse->num++;
            }
        }
    }
}

// 打印三元组
void print_sparse(SparseMatrix* sparse) {
    printf("非零元素个数: %d\n", sparse->num);
    printf("行数: %d, 列数: %d\n", sparse->rows, sparse->cols);
    printf("行下标\t列下标\t值\n");
    for (int i = 0; i < sparse->num; i++) {
        printf("%d\t%d\t%d\n", 
               sparse->data[i].row,
               sparse->data[i].col,
               sparse->data[i].value);
    }
    printf("\n");
}

// 将三元组转换回普通矩阵
void convert_to_normal(SparseMatrix* sparse, int matrix[10][10]) {
    // 初始化矩阵为0
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = 0;
        }
    }
    
    // 填充非零元素
    for (int i = 0; i < sparse->num; i++) {
        matrix[sparse->data[i].row][sparse->data[i].col] = sparse->data[i].value;
    }
}

// 转置稀疏矩阵
void transpose_sparse(SparseMatrix* source, SparseMatrix* dest) {
    dest->rows = source->cols;
    dest->cols = source->rows;
    dest->num = source->num;
    
    if (source->num == 0) return;
    
    int* col_counts = (int*)calloc(source->cols, sizeof(int));
    int* col_starts = (int*)calloc(source->cols, sizeof(int));
    
    // 统计每一列的非零元素个数
    for (int i = 0; i < source->num; i++) {
        col_counts[source->data[i].col]++;
    }
    
    // 计算每一列的起始位置
    col_starts[0] = 0;
    for (int i = 1; i < source->cols; i++) {
        col_starts[i] = col_starts[i-1] + col_counts[i-1];
    }
    
    // 执行转置
    for (int i = 0; i < source->num; i++) {
        int j = col_starts[source->data[i].col]++;
        dest->data[j].row = source->data[i].col;
        dest->data[j].col = source->data[i].row;
        dest->data[j].value = source->data[i].value;
    }
    
    free(col_counts);
    free(col_starts);
}

// 矩阵加法
void add_sparse_matrices(SparseMatrix* matrix1, SparseMatrix* matrix2, SparseMatrix* result) {
    result->rows = matrix1->rows;
    result->cols = matrix1->cols;
    result->num = 0;
    
    int i = 0, j = 0;
    while (i < matrix1->num && j < matrix2->num) {
        int row1 = matrix1->data[i].row;
        int col1 = matrix1->data[i].col;
        int row2 = matrix2->data[j].row;
        int col2 = matrix2->data[j].col;
        
        if (row1 < row2 || (row1 == row2 && col1 < col2)) {
            result->data[result->num] = matrix1->data[i];
            result->num++;
            i++;
        } else if (row2 < row1 || (row1 == row2 && col2 < col1)) {
            result->data[result->num] = matrix2->data[j];
            result->num++;
            j++;
        } else { // 相同位置的元素相加
            result->data[result->num].row = row1;
            result->data[result->num].col = col1;
            result->data[result->num].value = matrix1->data[i].value + matrix2->data[j].value;
            if (result->data[result->num].value != 0) { // 只存储非零元素
                result->num++;
            }
            i++;
            j++;
        }
    }
    
    // 处理剩余元素
    while (i < matrix1->num) {
        result->data[result->num] = matrix1->data[i];
        result->num++;
        i++;
    }
    while (j < matrix2->num) {
        result->data[result->num] = matrix2->data[j];
        result->num++;
        j++;
    }
}

int main() {
    // 初始化10x10稀疏矩阵
    int matrix[10][10] = {
        {0, 0, 3, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 4, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 7, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 6, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 4, 0},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
    printf("原始矩阵:\n");
    print_matrix(matrix);
    
    // 转换为三元组表示
    SparseMatrix sparse1;
    convert_to_sparse(matrix, &sparse1);
    printf("三元组表示:\n");
    print_sparse(&sparse1);
    
    // 转置矩阵
    SparseMatrix transposed;
    transpose_sparse(&sparse1, &transposed);
    printf("转置矩阵的三元组表示:\n");
    print_sparse(&transposed);
    
    // 将转置后的三元组转换回普通矩阵并打印
    int transposed_matrix[10][10];
    convert_to_normal(&transposed, transposed_matrix);
    printf("转置后的矩阵:\n");
    print_matrix(transposed_matrix);
    
    // 执行矩阵加法
    SparseMatrix sum;
    add_sparse_matrices(&sparse1, &transposed, &sum);
    printf("矩阵加法结果的三元组表示:\n");
    print_sparse(&sum);
    
    // 将加法结果转换回普通矩阵并打印
    int sum_matrix[10][10];
    convert_to_normal(&sum, sum_matrix);
    printf("矩阵加法结果:\n");
    print_matrix(sum_matrix);
    
     // 防止程序立即退出
     printf("Press any key to exit...\n");
     getchar(); // 消耗之前输入的回车
     getchar();
    return 0;
}