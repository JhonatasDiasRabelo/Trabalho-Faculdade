#include <stdio.h>
#include <stdbool.h>

#define EMPTY '.'

char board[8][8];

bool onBoard(int r, int c) {
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}

bool isWhite(char p) { return (p >= 'A' && p <= 'Z'); }
bool isBlack(char p) { return (p >= 'a' && p <= 'z'); }

bool isEnemy(char p, char color) {
    if (color == 'w') return isBlack(p);
    return isWhite(p);
}

void knightMoves(int r, int c, char color) {
    int moves[8][2] = {
        {2,1},{2,-1},{-2,1},{-2,-1},
        {1,2},{1,-2},{-1,2},{-1,-2}
    };

    printf("Cavalo (%d,%d) pode mover para:\n", r, c);
    for (int i = 0; i < 8; i++) {
        int nr = r + moves[i][0];
        int nc = c + moves[i][1];
        if (onBoard(nr, nc)) {
            char p = board[nr][nc];
            if (p == EMPTY || isEnemy(p, color))
                printf("  -> (%d,%d)\n", nr, nc);
        }
    }
}

// ------------------ Peão ---------------------

void pawnMoves(int r, int c, char color) {
    int dir = (color == 'w') ? -1 : +1;
    int startRow = (color == 'w') ? 6 : 1;

    printf("Peão (%d,%d) pode mover para:\n", r, c);

    // 1 casa
    if (onBoard(r+dir, c) && board[r+dir][c] == EMPTY)
        printf("  -> (%d,%d)\n", r+dir, c);

    // 2 casas
    if (r == startRow && board[r+dir][c] == EMPTY && board[r+2*dir][c] == EMPTY)
        printf("  -> (%d,%d)\n", r+2*dir, c);

    // capturas
    int dc[2] = {-1, +1};
    for (int i=0;i<2;i++) {
        int nr = r+dir, nc = c+dc[i];
        if (onBoard(nr,nc) && isEnemy(board[nr][nc], color))
            printf("  -> (%d,%d) (captura)\n", nr,nc);
    }
}

// ------------------ Movimentos deslizantes (bispo/torre/rainha) ---------------------

void slide(int r, int c, char color, int dr, int dc) {
    int nr = r + dr;
    int nc = c + dc;

    while (onBoard(nr,nc)) {
        char p = board[nr][nc];

        if (p == EMPTY) {
            printf("  -> (%d,%d)\n", nr, nc);
        } else {
            if (isEnemy(p, color))
                printf("  -> (%d,%d) (captura)\n", nr, nc);
            break;
        }

        nr += dr;
        nc += dc;
    }
}

void bishopMoves(int r, int c, char color) {
    printf("Bispo (%d,%d) pode mover para:\n", r, c);
    slide(r,c,color, 1,1);
    slide(r,c,color, 1,-1);
    slide(r,c,color,-1,1);
    slide(r,c,color,-1,-1);
}

void rookMoves(int r, int c, char color) {
    printf("Torre (%d,%d) pode mover para:\n", r, c);
    slide(r,c,color, 1,0);
    slide(r,c,color,-1,0);
    slide(r,c,color, 0,1);
    slide(r,c,color, 0,-1);
}

void queenMoves(int r, int c, char color) {
    printf("Rainha (%d,%d) pode mover para:\n", r, c);
    bishopMoves(r,c,color);
    rookMoves(r,c,color);
}

// ------------------ Rei ---------------------

void kingMoves(int r, int c, char color) {
    printf("Rei (%d,%d) pode mover para:\n", r, c);

    int m[8][2] = {
        {1,0},{-1,0},{0,1},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    for(int i=0;i<8;i++){
        int nr = r + m[i][0];
        int nc = c + m[i][1];

        if (onBoard(nr,nc)) {
            char p = board[nr][nc];
            if (p == EMPTY || isEnemy(p, color))
                printf("  -> (%d,%d)\n", nr, nc);
        }
    }
}

// ------------------ Identificação da peça ---------------------

void getMoves(int r, int c) {
    char p = board[r][c];

    if (p == EMPTY) {
        printf("Nenhuma peça na posição.\n");
        return;
    }

    char color = isWhite(p) ? 'w' : 'b';

    switch (p) {
        case 'P': case 'p': pawnMoves(r,c,color); break;
        case 'N': case 'n': knightMoves(r,c,color); break;
        case 'B': case 'b': bishopMoves(r,c,color); break;
        case 'R': case 'r': rookMoves(r,c,color); break;
        case 'Q': case 'q': queenMoves(r,c,color); break;
        case 'K': case 'k': kingMoves(r,c,color); break;
    }
}

// ------------------ Programa principal ---------------------

void initBoard() {
    // Tabuleiro inicial simplificado 
    char temp[8][8] = {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}
    };

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            board[i][j] = temp[i][j];
}

int main() {
    initBoard();

    int r, c;

    printf("Digite a linha e coluna da peça (0 a 7): ");
    scanf("%d %d", &r, &c);

    getMoves(r, c);

    return 0;
}
