document.addEventListener('DOMContentLoaded', function() {
    const generateButton = document.getElementById('generateButton');
    const mazeElement = document.getElementById('maze');
    
   
    const mazeSize = 20;
    
   
    generateMaze();
    

    generateButton.addEventListener('click', generateMaze);
    
    function generateMaze() {
        
        mazeElement.innerHTML = '';
        
       
        mazeElement.style.gridTemplateColumns = `repeat(${mazeSize}, 20px)`;
        
        
        for (let i = 0; i < mazeSize; i++) {
            for (let j = 0; j < mazeSize; j++) {
                const cell = document.createElement('div');
                cell.classList.add('cell');
                
               
                if (i === 0 || j === 0 || i === mazeSize - 1 || j === mazeSize - 1) {
                    cell.classList.add('wall');
                } else {
                   
                    const isWall = Math.random() < 0.3;
                    cell.classList.add(isWall ? 'wall' : 'path');
                }
                
                mazeElement.appendChild(cell);
            }
        }
    }
});