/******************
Name: Yotam Yakov
ID: 207918822
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

#define PYRAMID_LEVELS 5
#define MAX_BOARD 20
#define MAX_GRID 30
#define MAX_SLOTS 100
#define MAX_WORD 15

typedef struct Slot
{
    int x;
    int y;
    int length;
    char direction;
}Slot;

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();
int placeQueens(int board[][MAX_BOARD], char regions[][MAX_BOARD], char occupied[MAX_BOARD], int size, int row);
int fillSlot(char grid[][MAX_GRID],\
            struct Slot slots[MAX_SLOTS],\
            char words[][MAX_WORD],\
            int usedWords[MAX_SLOTS],\
            int slotsSize,\
            int wordsSize,\
            int word);

// Main function
int main() {
    int task = -1;
    do {
        // Print menu
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task)) {
            switch (task) {
            case 1:
                task1RobotPaths();
                break;
            case 2:
                task2HumanPyramid();
                break;
            case 3:
                task3ParenthesisValidator();
                break;
            case 4:
                task4QueensBattle();
                break;
            case 5:
                task5CrosswordGenerator();
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        } else {
            // Clean buffer
            scanf("%*s");
        }
    } while (task != 6);
}

// TASK 1
// Recursive function to calculate paths
int robotPaths(int r, int c) {
    // Base case 
    if (r == 0 && c == 0) {
        return 1;
    } else if (r < 0 || c < 0) {
        return 0;
    }
    
    // Recursion call
    return robotPaths(r - 1, c) + robotPaths(r, c - 1);
}

// Task 1 main function
void task1RobotPaths() {
    // Get input
    int row, column;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &row, &column);

    // Print result
    printf("The total number of paths the robot can take to reach home is: %d\n", robotPaths(row, column));

}

// TASK 2
// Recursive function to calculate weights
float pyramidWeight(float pyramid[][PYRAMID_LEVELS], int pyramidSize, int lvl, int pos) {
    // Base case
    if(lvl < 0 || pos < 0 || pos > pyramidSize) {
        return 0;
    }
    
    // Calculate position
    float left = pyramidWeight(pyramid, pyramidSize, lvl - 1, pos - 1);
    float right = pyramidWeight(pyramid, pyramidSize, lvl - 1, pos);

    // Recursion call
    return (left / 2) + (right / 2) + pyramid[lvl][pos];
}

// Task 2 main function
void task2HumanPyramid() {
    // Initialize pyramids
    float pyramid[PYRAMID_LEVELS][PYRAMID_LEVELS] = {0};
    float weights[PYRAMID_LEVELS][PYRAMID_LEVELS] = {0};
    
    // Get input
    printf("Please enter the weights of the cheerleaders: \n");
    for(int i = 0; i < PYRAMID_LEVELS; i++) {
        for(int j = 0; j <= i; j++) {
            scanf("%f", &pyramid[i][j]);
            // Validate
            if(pyramid[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
        
    }

    // Print result
    printf("The total weight on each cheerleader is:\n");
    for(int i = 0; i < PYRAMID_LEVELS; i++) {
        for(int j = 0; j <= i; j++) {
            float posWeight = pyramidWeight(pyramid, PYRAMID_LEVELS, i, j);
            weights[i][j] = posWeight;
            printf("%.2f ", weights[i][j]);
        }
        printf("\n");
    }
}

// TASK 3
// Scan rest of buffer
void clearBuffer() {
    char c;
    scanf("%c", &c);

    if(c == '\n') {
        return;
    }
    clearBuffer();
}

// Check balance
int isStringBalanced(char p) {
    char c;
    scanf("%c", &c);

    // Base cases
    // End of string
    if(c == '\n') {
        return p == 0;
    }

    // New parenthesis opened
    if(c == '(' || c == '[' || c == '{' || c == '<') {
        if(!isStringBalanced(c)) {
            return 0;
        }
    }

    // Check if open parenthesis closed
    if((c == ')' && p == '(') || (c == '}' && p == '{') ||\
       (c == ']' && p == '[') || (c == '>' && p == '<')) {
        return 1;
    }

    // Check if parenthesis closed wrong
    if((c == ')' && p != '(') || (c == '}' && p != '{') ||\
       (c == ']' && p != '[') || (c == '>' && p != '<')) {
        clearBuffer();
        return 0;
    }

    // Recursion call
    return isStringBalanced(p);
}

// Task 3 main function
void task3ParenthesisValidator() {
    printf("Please enter a term for validation:\n");
    scanf("%*c");

    char p = 0;
    int balance = isStringBalanced(p);

    // Print results
    if(balance) {
        printf("The parentheses are balanced correctly.\n");
        return;
    }

    printf("The parentheses are not balanced correctly.\n");
}

// TASK 4
// print solution board
void printBoard(int board[][MAX_BOARD], int size) {
    printf("Solution:\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j]) {
                printf("X ");
            } else {
                printf("* ");
            }
        }
        printf("\n");
    }
}

// Check if column is clear
int isColumnClear(int board[][MAX_BOARD], int row, int column) {
    // Base case
    // Column is clear
    if(row < 0) {
        return 1;
    }

    // Column is not clear
    if(board[row][column]) {
        return 0;
    }

    // Recursion call
    return isColumnClear(board, row - 1, column);
}

// Check if region is cleaar
int isRegionClear(char occupied[MAX_BOARD], char region, int index, int size) {
    // Base case
    // Region is clear
    if(index > size) {
        return 1;
    }
    
    // Region not clear
    if(region == occupied[index]) {
        return 0;
    }

    // Recursion call
    return isRegionClear(occupied, region, index + 1, size);
}

// Check if area is clear
int isAreaClear(int board[][MAX_BOARD], int size, int row, int column) {
    // Check 3 squares above location
    if(row == 0) {
        return 1;
    } else if (column == 0) {
        return !board[row - 1][column] && !board[row - 1][column + 1];
    } else if (column == size) {
        return !board[row - 1][column - 1] && !board[row - 1][column];
    } else {
        return !board[row - 1][column - 1] && !board[row - 1][column] && !board[row - 1][column + 1];
    }
}

// Iterate columns in Nth row
int placeRow(\
    int board[][MAX_BOARD],\
    char regions[][MAX_BOARD],\
    char occupied[MAX_BOARD],\
    int size,\
    int row,\
    int column) {
        
    // Base case
    if(column >= size) {
        return 0;
    }

    // Check if square available
    int isSquareClear = isAreaClear(board, size, row, column) &&\
                        isColumnClear(board, row - 1, column) &&\
                        isRegionClear(occupied, regions[row][column], 0, size);

    if(isSquareClear) {
        // Place queen
        board[row][column] = 1;
        occupied[row] = regions[row][column];

        // Iterate to next
        if(placeQueens(board, regions, occupied, size, row + 1)) {
            return 1;
        }

        // Backtracking if failed
        board[row][column] = 0;
        occupied[row] = '0';
    }

    // Recursion call
    return placeRow(board, regions, occupied, size, row, column + 1);
}

// Iterate rows
int placeQueens(int board[][MAX_BOARD], char regions[][MAX_BOARD], char occupied[MAX_BOARD], int size, int row) {
    // Base case
    if(row >= size) {
        return 1;
    }
    
    // Check if row available
    return placeRow(board, regions, occupied, size, row, 0);
}

// Task 4 main function
void task4QueensBattle() {
    int size;
    int board[MAX_BOARD][MAX_BOARD] = {0};
    char regions[MAX_BOARD][MAX_BOARD];
    char occupied[MAX_BOARD];

    // Get input
    printf("Please enter the board dimensions:\n");
    scanf("%d", &size);
    printf("Please enter a %d*%d puzzle board:\n", size, size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            scanf(" %c", &regions[i][j]);
        }
    }
    
    // Print results
    if(placeQueens(board, regions, occupied, size, 0)) {
        printBoard(board, size);
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}

// TASK 5
// Print solution grid
void printGrid(char grid[][MAX_GRID], int gridSize) {
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            printf("| %c ", grid[i][j] ? grid[i][j] : '#');
        }
        printf("|\n");
    }
}

// Clear word from grid
void clearWord(char grid[][MAX_GRID], struct Slot slot, int position) {
    // Base case
    if(position < 0) {
        return;
    }

    // Initialize point
    int gridX = slot.x;
    int gridY = slot.y;

    // Offset by position
    if(slot.direction == 'H') {
        gridY += position;
    } else if(slot.direction == 'V') {
        gridX += position;
    }

    // Clear
    grid[gridX][gridY] = 0;

    // Recursion call
    return clearWord(grid, slot, position - 1);
}

// Check if word fit slot
int doesWordFit(char grid[][MAX_GRID],\
    struct Slot slot, char words[][MAX_WORD],\
    int usedWords[MAX_SLOTS],\
    int word,\
    int position) {

    int wordLength = strlen(words[word]);

    // Base case
    // Word finished
    if(position >= wordLength) {
        usedWords[word] = 1;
        return 1;
    }

    // Initialize point
    int gridX = slot.x;
    int gridY = slot.y;

    // Offset by position
    if(slot.direction == 'H') {
        gridY += position;
    } else if(slot.direction == 'V') {
        gridX += position;
    }

    // Check if square available
    if(grid[gridX][gridY] && (grid[gridX][gridY] == '#' || grid[gridX][gridY] != words[word][position]) ) {
        usedWords[word] = 0;
        // Clear if word failed
        clearWord(grid, slot, position - 1);
        return 0;
    }

    // Fill grid
    grid[gridX][gridY] = words[word][position];

    // Recursion call
    return doesWordFit(grid, slot, words, usedWords, word, position + 1);
}

// Try to place word in slot
int fillWord(char grid[][MAX_GRID],\
            struct Slot slots[MAX_SLOTS],\
            char words[][MAX_WORD],\
            int usedWords[MAX_SLOTS],\
            int slotsSize, int wordsSize,\
            int slot, int word) {
    // Base case
    // Out of words to try
    if(word >= wordsSize){
        return 0;
    }

    int wordLength = strlen(words[word]);

    // If word can't fit try next
    if(usedWords[word] == 1\
        || wordLength != slots[slot].length\
        || !doesWordFit(grid, slots[slot], words, usedWords, word, 0)) {
        return fillWord(grid, slots, words, usedWords, slotsSize, wordsSize, slot, word + 1);
    }

    // If word fir try next
    if(fillSlot(grid, slots, words, usedWords, slotsSize, wordsSize, slot + 1)) {
        return 1;
    }

    // If word can't solve grid clear it
    usedWords[word] = 0;
    clearWord(grid, slots[slot], wordLength);

    // Recursion call
    return fillWord(grid, slots, words, usedWords, slotsSize, wordsSize, slot, word + 1);
}

// Try to fill slot
int fillSlot(char grid[][MAX_GRID],\
            struct Slot slots[MAX_SLOTS],\
            char words[][MAX_WORD],\
            int usedWords[MAX_SLOTS],\
            int slotsSize,\
            int wordsSize,\
            int slot) {
    // Base case
    if(slot >= slotsSize) {
        return 1;
    }

    // Recursion call
    return fillWord(grid, slots, words, usedWords, slotsSize, wordsSize, slot, 0);
}

void task5CrosswordGenerator() {
    char grid[MAX_GRID][MAX_GRID] = {""};
    struct Slot slots[MAX_SLOTS];
    char words[MAX_SLOTS][MAX_WORD] = {""};
    int usedWords[MAX_SLOTS] = {0};
    int gridSize, slotsSize, wordsSize;

    // Get input
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf(" %d", &gridSize);
    printf("Please enter the number of slots in the crossword:\n");
    scanf(" %d", &slotsSize);
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    for(int i = 0; i < slotsSize; i++) {
        scanf(" %d", &slots[i].x);
        scanf(" %d", &slots[i].y);
        scanf(" %d", &slots[i].length);
        scanf(" %c", &slots[i].direction);
    }
    printf("Please enter the number of words in the dictionary:\n");
    scanf("%d", &wordsSize);
    while (wordsSize < slotsSize) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", slotsSize);
        scanf("%d", &wordsSize);
    };
    
    printf("Please enter the words for the dictionary:\n");
    for(int i = 0; i < wordsSize; i++) {
        scanf("%s", words[i]);
    }
    
    // Print results
    if(fillSlot(grid, slots, words, usedWords, slotsSize, wordsSize, 0)) {
        printGrid(grid, gridSize);
    } else {
        printf("This crossword cannot be solved.\n");
    }

}
