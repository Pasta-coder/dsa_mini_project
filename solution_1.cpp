//Brute Force Solution: Backtracking Approach

//This approach uses backtracking 
//(a depth-first search variant) that explores all possible paths 
//until it either finds a valid path or exhausts all possibilities.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define N 4  // Size of the maze

// Backtracking Solution
// Function to print the solution matrix
void printSolution(vector<vector<int> >& sol) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << sol[i][j] << " ";
        cout << endl;
    }
}

// Function to check if a position (x, y) is valid for backtracking
bool isSafe(vector<vector<int> >& maze, int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}

// Recursive function to solve the maze using backtracking
bool solveMazeUtil(vector<vector<int> >& maze, int x, int y, vector<vector<int> >& sol) {
    // Base case: If reached the destination
    if (x == N - 1 && y == N - 1) {
        sol[x][y] = 1;
        return true;
    }

    // Check if current cell is valid
    if (isSafe(maze, x, y)) {
        // Mark current cell as part of solution
        sol[x][y] = 1;

        // Try moving right
        if (solveMazeUtil(maze, x + 1, y, sol))
            return true;

        // Try moving down
        if (solveMazeUtil(maze, x, y + 1, sol))
            return true;

        // If neither right nor down leads to solution, backtrack
        sol[x][y] = 0;
        return false;
    }

    return false;
}

// Function to solve maze using backtracking
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

// BFS Solution
// Direction arrays for 4 directions
int rowMove[] = {1, 0};  // Down, Right
int colMove[] = {0, 1};  

// Structure to store cell coordinates and distance
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

// Function to check if a cell is valid for BFS
bool isValid(int x, int y, vector<vector<int> >& maze, vector<vector<bool> >& visited) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y]);
}

// Function to solve maze using BFS
void solveUsingBFS(vector<vector<int> >& maze) {
    cout << "\n--- BFS Solution ---\n";
    
    if (maze[0][0] == 0) {
        cout << "Starting point is blocked. No solution exists.\n";
        return;
    }
    
    // Initialize visited array
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    
    // Initialize parent matrix to track path
    vector<vector<Point*> > parent(N, vector<Point*>(N, nullptr));
    
    // Create a queue for BFS
    queue<Point> q;
    
    // Mark source as visited and enqueue it
    visited[0][0] = true;
    q.push(Point(0, 0));
    
    bool foundPath = false;
    
    // Standard BFS loop
    while (!q.empty() && !foundPath) {
        Point current = q.front();
        q.pop();
        
        // If we reached destination
        if (current.x == N-1 && current.y == N-1) {
            foundPath = true;
            break;
        }
        
        // Try all four directions
        for (int i = 0; i < 2; i++) {
            int newX = current.x + rowMove[i];
            int newY = current.y + colMove[i];
            
            // If valid cell
            if (isValid(newX, newY, maze, visited)) {
                // Mark as visited and enqueue
                visited[newX][newY] = true;
                q.push(Point(newX, newY));
                
                // Save parent for path reconstruction
                parent[newX][newY] = new Point(current.x, current.y);
            }
        }
    }
    
    if (foundPath) {
        cout << "Path found using BFS:\n";
        
        // Reconstruct and print path
        vector<vector<int> > path(N, vector<int>(N, 0));
        
        // Mark the destination
        int x = N-1, y = N-1;
        path[x][y] = 1;
        
        // Backtrack using parent pointers
        while (!(x == 0 && y == 0)) {
            Point* p = parent[x][y];
            x = p->x;
            y = p->y;
            path[x][y] = 1;
            delete p; // Free memory
        }
        
        // Print the path
        printSolution(path);
    } else {
        cout << "No solution exists using BFS.\n";
    }
    
    // Clean up any remaining allocated Points
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (parent[i][j] != nullptr) {
                delete parent[i][j];
            }
        }
    }
}

// Main function to solve the maze problem
int main() {
    // Example maze

// Use this approach instead:
vector<vector<int> > maze(N, vector<int>(N, 0));  // Initialize with zeros

// Then manually set each value
maze[0][0] = 1; maze[0][1] = 0; maze[0][2] = 0; maze[0][3] = 0;
maze[1][0] = 1; maze[1][1] = 1; maze[1][2] = 0; maze[1][3] = 1;
maze[2][0] = 0; maze[2][1] = 1; maze[2][2] = 0; maze[2][3] = 0;
maze[3][0] = 1; maze[3][1] = 1; maze[3][2] = 1; maze[3][3] = 1;


    // cout << "Maze:\n";
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++)
    //         cout << maze[i][j] << " ";
    //     cout << endl;
    // }

    // Solve using backtracking
    solveUsingBacktracking(maze);
    
    // Solve using BFS
    solveUsingBFS(maze);

    return 0;
}