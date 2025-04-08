#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define N 4 
void printSolution(vector<vector<int> >& sol) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }
}

bool isSafe(vector<vector<int> >& maze, int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}

bool solveMazeUtil(vector<vector<int> >& maze, int x, int y, vector<vector<int> >& sol) {
    if (x == N - 1 && y == N - 1) {
        sol[x][y] = 1;
        return true;
    }  
    if (isSafe(maze, x, y)) {
        sol[x][y] = 1;
        if (solveMazeUtil(maze, x + 1, y, sol))
            return true;
        if (solveMazeUtil(maze, x, y + 1, sol))
            return true;
        sol[x][y] = 0;
        return false;
    }
    return false;
}

void solveUsingBacktracking(vector<vector<int> >& maze) {
    vector<vector<int> > sol(N, vector<int>(N, 0));

    cout << "\n--- Backtracking Solution ---\n";
    
    if (maze[0][0] == 0) {
        cout << "Starting point is blocked. No solution exists.\n";
        return;
    }
    
    if (solveMazeUtil(maze, 0, 0, sol)) {
        cout << "Path found using backtracking:\n";
        printSolution(sol);
    } else {
        cout << "No solution exists using backtracking.\n";
    }
}

int rowMove[] = {1, 0};  
int colMove[] = {0, 1};  

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

bool isValid(int x, int y, vector<vector<int> >& maze, vector<vector<bool> >& visited) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y]);
}
void solveUsingBFS(vector<vector<int> >& maze) {
    cout << "\n--- BFS Solution ---\n";
    
    if (maze[0][0] == 0) {
        cout << "Starting point is blocked. No solution exists.\n";
        return;
    }
   
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    
    vector<vector<Point*> > parent(N, vector<Point*>(N, nullptr));
    
    queue<Point> q;
   
    visited[0][0] = true;
    q.push(Point(0, 0));
    
    bool foundPath = false;
    
    while (!q.empty() && !foundPath) {
        Point current = q.front();
        q.pop();
        
        if (current.x == N-1 && current.y == N-1) {
            foundPath = true;
            break;
        }
        
        for (int i = 0; i < 2; i++) {
            int newX = current.x + rowMove[i];
            int newY = current.y + colMove[i];
           
            if (isValid(newX, newY, maze, visited)) {
              
                visited[newX][newY] = true;
                q.push(Point(newX, newY));
                
                parent[newX][newY] = new Point(current.x, current.y);
            }
        }
    }
    
    if (foundPath) {
        cout << "Path found using BFS:\n";
        
        vector<vector<int> > path(N, vector<int>(N, 0));
        
        int x = N-1, y = N-1;
        path[x][y] = 1;
       
        while (!(x == 0 && y == 0)) {
            Point* p = parent[x][y];
            x = p->x;
            y = p->y;
            path[x][y] = 1;
            
        }
        printSolution(path);
    } else {
        cout << "No solution exists using BFS.\n";
    }
    
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (parent[i][j] != nullptr) {
                delete parent[i][j];
            }
        }
    }
}
int main() {
   
vector<vector<int> > maze(N, vector<int>(N, 0)); 
maze[0][0] = 1; maze[0][1] = 0; maze[0][2] = 0; maze[0][3] = 0;
maze[1][0] = 1; maze[1][1] = 1; maze[1][2] = 1; maze[1][3] = 1;
maze[2][0] = 0; maze[2][1] = 1; maze[2][2] = 1; maze[2][3] = 0;
maze[3][0] = 1; maze[3][1] = 1; maze[3][2] = 1; maze[3][3] = 1;

    cout << "Maze:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
    solveUsingBacktracking(maze);
    
    solveUsingBFS(maze);

    return 0;
}