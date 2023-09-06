# My-Shell
This is a versatile shell project implemented in the C programming language. It offers a range of essential features for command-line interaction. Users can perform fundamental tasks such as changing directories (using 'cd'), listing directory contents ('ls'), and executing any command accessible within the system's PATH environment variable. In addition to these core functionalities, the shell maintains a comprehensive command history, making it easy for users to access and review their prior commands by typing 'history'.

In addition, I made it more appealing with different bash scripts:

## First Script - GCC Find
"gccfind.sh" is a script designed for compiling C files selectively based on specific keywords or patterns. When executed in a terminal, it offers flexibility through three essential parameters:

* Directory Path: The path to the target directory where the script searches for C files containing the specified word or pattern.
* Keyword or Pattern: The word or pattern that serves as the search criterion. The script identifies and compiles C files that match this criterion.
* Recursion Flag: An optional flag that, when enabled, instructs the script to search recursively within subdirectories of the specified path, ensuring a comprehensive search across the entire directory structure.

This script streamlines the compilation process by allowing users to compile only those C files that meet their specific criteria, making it a valuable tool for developers and programmers.

## Second Script - Tennis Game
"tennis.sh" is a script that emulates an engaging two-player board game. At the outset, each player possesses a starting score of 50 points. The game unfolds in rounds, with players making strategic choices by inputting a number between 0 and their remaining score.

![image](https://github.com/DanSaada/My-Shell/assets/112869076/9650773d-1ef0-4d72-b767-e9c4612dd44c)


Here's an overview of the game rules:

* Initial Scores: Both players begin with 50 points.

* First Round: At the commencement of the first round, a token is positioned in the middle column.

* Turn Sequence: Players take alternating turns, selecting a number within the range of 0 to their available score.

* Token Movement: The player who opts for the lower number shifts the token to his side of the board by one column.

* Victory Conditions: The game concludes if any of the following scenarios occur:
   * A player's score dwindles to 0, resulting in their loss.
   * The token reaches an extreme position, either column -3 or 3, declaring the player on the opposite side as the victor.
   * Both players' scores reach 0 simultaneously, and the winner is determined by the token's position (Whoever maintains that the token is closer to his extreme column loses).

This script offers an interactive and dynamic board game experience, where strategic decision-making and a bit of luck play pivotal roles in determining the ultimate winner.

Gameplay Example:

```bash

 Player 1: 50         Player 2: 50 
 --------------------------------- 
 |       |       #       |       | 
 |       |       #       |       | 
 |       |       O       |       | 
 |       |       #       |       | 
 |       |       #       |       | 
 --------------------------------- 
PLAYER 1 PICK A NUMBER: 30
PLAYER 2 PICK A NUMBER: 20

       Player 1 played: 30
       Player 2 played: 20

 Player 1: 20         Player 2: 30 
 --------------------------------- 
 |       |       #       |       | 
 |       |       #       |       | 
 |       |       #   O   |       | 
 |       |       #       |       | 
 |       |       #       |       | 
 --------------------------------- 
PLAYER 1 PICK A NUMBER: 20
PLAYER 2 PICK A NUMBER: 30

       Player 1 played: 20
       Player 2 played: 30

 Player 1: 0         Player 2: 20 
 --------------------------------- 
 |       |       #       |       | 
 |       |       #       |       | 
 |       |       #       |   O   | 
 |       |       #       |       | 
 |       |       #       |       | 
 --------------------------------- 
PLAYER 1 PICK A NUMBER: 0
PLAYER 2 PICK A NUMBER: 20

       Player 1 played: 0
       Player 2 played: 20

 Player 1: 0         Player 2: 0 
 --------------------------------- 
 |       |       #       |       | 
 |       |       #       |       | 
 |       |       #       |       | 
 |       |       #       |       | 
 |       |       #       |       | 
 --------------------------------- 

Player 2 Wins!

```


## Installing And Executing
    
To clone and run this application, you'll need [Git](https://git-scm.com) installed on your computer.
  
From your command line:

  
```bash
# Clone this repository.
$ git clone https://github.com/DanSaada/My-Shell

# Go into the repository.
$ cd My-Shell

# Compile.
$ gcc -o myShell.out MyShell.c

# Run the program.
 ./myShell.out
```

## Author
- [Dan Saada](https://github.com/DanSaada)
