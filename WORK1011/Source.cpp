#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void dropBlock(char arr[][20], int x, int y) {
    for (int i = x; i > 0; i--) {
        if (arr[i - 1][y] == '#') {
            arr[i][y] = '-';
            break;
        }
        arr[i][y] = arr[i - 1][y];
        if (i == 1 && arr[i - 1][y] != '-') {
            arr[i - 1][y] = '-';
        }
    }
}
int move(char arr[][20], int x, int y, int direction) {
    int check = 0, score = 0;
    if (arr[x][y + direction] == '-' && arr[x][y] != '#' && arr[x][y] != '-') {
        arr[x][y + direction] = arr[x][y];
        arr[x][y] = '-';
        dropBlock(arr, x, y);
        if (arr[x][y] == arr[x + 1][y]) {
            arr[x][y] = '-';
            arr[x + 1][y] = '-';
            score += 10;
            dropBlock(arr, x, y);
            dropBlock(arr, x + 1, y);

        }
        y += direction;
        while (arr[x + 1][y] == '-') {
            arr[x + 1][y] = arr[x][y];
            arr[x][y] = '-';
            x += 1;
        }
        if (arr[x][y] == arr[x + 1][y]) {
            score += 5;
            check = 1;
            arr[x + 1][y] = '-';
        }
        if (arr[x][y] == arr[x][y - 1]) {
            score += 5;
            check = 1;
            dropBlock(arr, x, y - 1);
            if (arr[x][y - 1] == arr[x + 1][y - 1]) {
                score += 10;
                arr[x][y - 1] = '-';
                arr[x + 1][y - 1] = '-';
                dropBlock(arr, x, y - 1);
                dropBlock(arr, x + 1, y - 1);
            }
        }
        if (arr[x][y] == arr[x][y + 1]) {
            score += 5;
            check = 1;
            dropBlock(arr, x, y + 1);
            if (arr[x][y + 1] == arr[x + 1][y + 1]) {
                score += 10;
                arr[x][y + 1] = '-';
                arr[x + 1][y + 1] = '-';
                dropBlock(arr, x, y + 1);
                dropBlock(arr, x + 1, y + 1);
            }
        }
        if (check == 1) {
            arr[x][y] = '-';
            score += 5;
        }
    }
    else {
        score -= 5;
    }
    return score;
}
int main() {
    int row, column, count, moveAmount, x, y, score = 0;
    char board[20][20], direction;
    scanf("%d%d", &row, &column);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column * 2; j++)
            scanf("%c", &board[i][j]);
    for (int i = 0; i < row; i++) {
        count = 0;
        for (int j = 0; j < column * 2; j++)
            if (j % 2 == 1)
                board[i][count++] = board[i][j];
    }
    scanf("%d", &moveAmount);
    for (int i = 0; i < moveAmount; i++) {
        scanf("%d %d %c", &x, &y, &direction);
        switch (direction) {
        case 'L': score += move(board, x, y, -1); break;
        case 'R': score += move(board, x, y, 1); break;
        }
    }
    printf("%d\n", score);
    for (int k = 0; k < row; k++) {
        for (int j = 0; j < column; j++) {
            printf("%c ", board[k][j]);
        }
        printf("\n");
    }



}