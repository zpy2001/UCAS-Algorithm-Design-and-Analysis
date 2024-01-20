#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义棋盘的最大大小
#define MAX_BOARD_SIZE 128

// 定义骨牌的形状，1表示覆盖，0表示空缺
int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

// 定义全局变量，表示骨牌的编号
int tile = 1;

// 函数声明
void chessboard(int tr, int tc, int dr, int dc, int size);
void printBoard(int size);

int main() {
    int n;
    
    printf("请输入棋盘大小的指数 n (2^n x 2^n)：");
    scanf("%d", &n);
    
    // 初始化棋盘为全0
    int boardSize = (int)pow(2, n);
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = 0;
        }
    }
    
    // 设置起始的缺失格子位置
    int startRow, startCol;
    printf("请输入起始的缺失格子位置（0 到 %d）：\n", boardSize - 1);
    printf("行号：");
    scanf("%d", &startRow);
    printf("列号：");
    scanf("%d", &startCol);
    
    // 调用棋盘覆盖算法
    chessboard(0, 0, startRow, startCol, boardSize);
    
    // 打印覆盖后的棋盘
    printf("棋盘覆盖结果：\n");
    printBoard(boardSize);
    
    return 0;
}

// 棋盘覆盖算法
void chessboard(int tr, int tc, int dr, int dc, int size) {
    if (size == 1) {
        return;
    }
    
    int t = tile++;
    int s = size / 2;
    
    // 左上角子棋盘
    if (dr < tr + s && dc < tc + s) {
        chessboard(tr, tc, dr, dc, s);
    } else {
        // 在左上角子棋盘中放置特殊骨牌
        board[tr + s - 1][tc + s - 1] = t;
        // 覆盖其他部分
        chessboard(tr, tc, tr + s - 1, tc + s - 1, s);
    }
    
    // 右上角子棋盘
    if (dr < tr + s && dc >= tc + s) {
        chessboard(tr, tc + s, dr, dc, s);
    } else {
        // 在右上角子棋盘中放置特殊骨牌
        board[tr + s - 1][tc + s] = t;
        // 覆盖其他部分
        chessboard(tr, tc + s, tr + s - 1, tc + s, s);
    }
    
    // 左下角子棋盘
    if (dr >= tr + s && dc < tc + s) {
        chessboard(tr + s, tc, dr, dc, s);
    } else {
        // 在左下角子棋盘中放置特殊骨牌
        board[tr + s][tc + s - 1] = t;
        // 覆盖其他部分
        chessboard(tr + s, tc, tr + s, tc + s - 1, s);
    }
    
    // 右下角子棋盘
    if (dr >= tr + s && dc >= tc + s) {
        chessboard(tr + s, tc + s, dr, dc, s);
    } else {
        // 在右下角子棋盘中放置特殊骨牌
        board[tr + s][tc + s] = t;
        // 覆盖其他部分
        chessboard(tr + s, tc + s, tr + s, tc + s, s);
    }
}

// 打印棋盘
void printBoard(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%2d\t", board[i][j]);
        }
        printf("\n");
    }
}

