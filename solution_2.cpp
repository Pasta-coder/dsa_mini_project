#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define N 4  // Size of the maze

// Structure to store coordinates and path
struct Cell {
    int x, y;
    vector<pair<int, int>> path;
    
    Cell(int x, int y, vector<pair<int, int> > path) : x(x), y(y), path(path) {}
};

// Function to check if a position (x, y) is valid
bool isSafe(vector<vector<int> >& maze, vector<vector<bool> >& visited, int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y]);
}

// Function to print the path
void printPath(const vector<pair<int, int> >& path) {
    // Create a solution matrix
    vector<vector<int> > sol(N, vector<int>(N, 0));
    
    // Mark the path on the solution matrix
    for (auto& cell : path) {
        sol[cell.first][cell.second] = 1;
    }
    
    // Print the solution
    cout << "Solution Path (1 represents path): " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }
}

// Function to find the shortest path using BFS
bool solveMazeBFS(vector<vector<int> >& maze) {
    // If the source or destination is blocked
    if (maze[0][0] == 0 || maze[N-1][N-1] == 0)
        return false;
        
    // Initialize a visited array
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    
    // Create a queue for BFS
    queue<Cell> q;
    
    // Mark the source cell as visited and enqueue it
    visited[0][0] = true;
    vector<pair<int, int> > initialPath;
    initialPath.push_back({0, 0});
    q.push(Cell(0, 0, initialPath));
    
    // Define the possible moves (right and down)
    int dx[] = {1, 0};
    int dy[] = {0, 1};
    
    // BFS loop
    while (!q.empty()) {
        Cell current = q.front();
        q.pop();
        
        int x = current.x;
        int y = current.y;
        vector<pair<int, int> > path = current.path;
        
        // If we've reached the destination
        if (x == N-1 && y == N-1) {
            printPath(path);
            return true;
        }
        
        // Try all possible moves
        for (int i = 0; i < 2; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            
            if (isSafe(maze, visited, newX, newY)) {
                visited[newX][newY] = true;
                
                // Create a new path adding this cell
                vector<pair<int, int> > newPath = path;
                newPath.push_back({newX, newY});
                
                q.push(Cell(newX, newY, newPath));
            }
        }
    }
    
    // If we reach here, no path exists
    return false;
}

int main() {
    vector<vector<int> > maze(N, vector<int>(N, 0));  // Initialize with zeros

// Then manually set each value
maze[0][0] = 1; maze[0][1] = 0; maze[0][2] = 0; maze[0][3] = 0;
maze[1][0] = 1; maze[1][1] = 1; maze[1][2] = 0; maze[1][3] = 1;
maze[2][0] = 0; maze[2][1] = 1; maze[2][2] = 0; maze[2][3] = 0;
maze[3][0] = 1; maze[3][1] = 1; maze[3][2] = 1; maze[3][3] = 1;

    cout << "Maze:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    if (!solveMazeBFS(maze)) {
        cout << "Solution doesn't exist" << endl;
    }

    return 0;
}