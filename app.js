document.addEventListener('DOMContentLoaded', function() {
    const generateButton = document.getElementById('generateButton');
    const mazeElement = document.getElementById('maze');
    
    // Default maze size
    const mazeSize = 20;
    
    // Generate maze when page loads
    generateMaze();
    
    // Add event listener for generate button
    generateButton.addEventListener('click', generateMaze);
    
    function generateMaze() {
        // Clear previous maze
        mazeElement.innerHTML = '';
        
        // Set grid layout
        mazeElement.style.gridTemplateColumns = `repeat(${mazeSize}, 20px)`;
        
        // Create maze grid with random walls and paths
        for (let i = 0; i < mazeSize; i++) {
            for (let j = 0; j < mazeSize; j++) {
                const cell = document.createElement('div');
                cell.classList.add('cell');
                
                // Add border cells as walls
                if (i === 0 || j === 0 || i === mazeSize - 1 || j === mazeSize - 1) {
                    cell.classList.add('wall');
                } else {
                    // Randomly determine if cell is wall or path (30% chance of wall)
                    const isWall = Math.random() < 0.3;
                    cell.classList.add(isWall ? 'wall' : 'path');
                }
                
                mazeElement.appendChild(cell);
            }
        }
    }
});