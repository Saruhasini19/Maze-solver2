
#include <stdio.h>

#define ROW 5
#define COL 5
#define MAX 100

int maze[ROW][COL] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0}
};

int visited[ROW][COL] = {0};
int parentR[ROW][COL];
int parentC[ROW][COL];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

typedef struct {
    int r, c;
} Point;

Point queue[MAX];

int bfs(int sr, int sc, int er, int ec) {
    int front = 0, rear = 0;

    queue[rear++] = (Point){sr, sc};
    visited[sr][sc] = 1;

    while (front < rear) {
        Point current = queue[front++];

        if (current.r == er && current.c == ec)
            return 1;

        for (int i = 0; i < 4; i++) {
            int nr = current.r + dr[i];
            int nc = current.c + dc[i];

            if (nr >= 0 && nr < ROW &&
                nc >= 0 && nc < COL &&
                maze[nr][nc] == 0 &&
                !visited[nr][nc]) {

                visited[nr][nc] = 1;
                parentR[nr][nc] = current.r;
                parentC[nr][nc] = current.c;

                queue[rear++] = (Point){nr, nc};
            }
        }
    }

    return 0;
}

void displayMaze(int sr, int sc, int er, int ec) {
    printf("\nMaze Solution:\n\n");

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == sr && j == sc)
                printf("S ");
            else if (i == er && j == ec)
                printf("E ");
            else if (maze[i][j] == 1)
                printf("# ");
            else if (maze[i][j] == 2)
                printf("* ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

int main() {
    int sr = 0, sc = 0;
    int er = 4, ec = 4;

    printf("Maze Solver using BFS\n");
    printf("S = Start, E = End, # = Wall\n");
    printf("* = Path, . = Open space\n");

    if (bfs(sr, sc, er, ec)) {
        int r = er, c = ec;

        while (r != sr || c != sc) {
            maze[r][c] = 2;

            int pr = parentR[r][c];
            int pc = parentC[r][c];

            r = pr;
            c = pc;
        }

        displayMaze(sr, sc, er, ec);
        printf("\nPath found successfully!\n");
    } else {
        displayMaze(sr, sc, er, ec);
        printf("\nNo path found!\n");
    }

    return 0;
}
