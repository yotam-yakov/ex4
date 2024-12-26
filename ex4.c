/******************
Name: Yotam Yakov
ID: 207918822
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

#define PYRAMID_LEVELS 5
#define MAX_BOARD_SIZE 20
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
int placeQueens(int board[][MAX_BOARD_SIZE], char regions[][MAX_BOARD_SIZE], char occupied[MAX_BOARD_SIZE], int size, int row);
int fillGrid(char grid[][MAX_GRID], struct Slot slots[MAX_SLOTS], char words[][MAX_WORD], int usedWords[MAX_SLOTS], int gridSize, int slotsSize, int wordsSize, int word);

int main() {
    int task = -1;
    do {
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf(" %d", &task)) {
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
            scanf("%*[^\n]");
            scanf("%*s");
        }
    } while (task != 6);
}

int robotPaths(int r, int c) {
    if (r == 0 && c == 0) {
        return 1;
    } else if (r < 0 || c < 0) {
        return 0;
    }
    
    return robotPaths(r - 1, c) + robotPaths(r, c - 1);
}

void task1RobotPaths() {
    int row, column;
    printf("Please enter the coordinates of the robot (column, row):\n");
    scanf("%d %d", &row, &column);

    printf("The total number of paths the robot can take to reach home is: %d\n", robotPaths(row, column));

}

float pyramidWeight(float pyramid[][PYRAMID_LEVELS], int pyramidSize, int lvl, int pos) {
    if(lvl < 0 || pos < 0 || pos > pyramidSize) {
        return 0;
    }
    
    float left = pyramidWeight(pyramid, pyramidSize, lvl - 1, pos - 1);
    float right = pyramidWeight(pyramid, pyramidSize, lvl - 1, pos);

    return (left / 2) + (right / 2) + pyramid[lvl][pos];
}

void task2HumanPyramid() {
    float pyramid[PYRAMID_LEVELS][PYRAMID_LEVELS] = {0};
    float weights[PYRAMID_LEVELS][PYRAMID_LEVELS] = {0};
    

    printf("Please enter the weights of the cheerleaders: \n");
    for(int i = 0; i < PYRAMID_LEVELS; i++) {
        for(int j = 0; j <= i; j++) {
            scanf("%f", &pyramid[i][j]);
            if(pyramid[i][j] < 0) {
                printf("Negative weights are not supported.\n");
                return;
            }
        }
        
    }

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

int isStringBalanced(char p) {
    char c;
    scanf("%c", &c);

    if(c == '\n') {
        return p == 0;
    }

    if(c == '(' || c == '[' || c == '{' || c == '<') {
        if(!isStringBalanced(c)) {
            return 0;
        }
    }

    if((c == ')' && p == '(') || (c == '}' && p == '{') ||\
       (c == ']' && p == '[') || (c == '>' && p == '<')) {
        return 1;
    }

    if((c == ')' && p != '(') || (c == '}' && p != '{') ||\
       (c == ']' && p != '[') || (c == '>' && p != '<')) {
        return 0;
    }

    return isStringBalanced(p);
}

void task3ParenthesisValidator() {
    printf("Please enter a term for validation:\n");


    char p = 0;
    if(isStringBalanced(p)) {
        printf("The parentheses are balanced correctly.\n");
    } else {
        printf("The parentheses are not balanced correctly.\n");
    }
}

void printBoard(int board[][MAX_BOARD_SIZE], int size) {
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

int isColumnClear(int board[][MAX_BOARD_SIZE], int row, int column) {
    if(row < 0) {
        return 1;
    }

    if(board[row][column]) {
        return 0;
    }

    return isColumnClear(board, row - 1, column);
}

int isRegionClear(char occupied[MAX_BOARD_SIZE], char region, int index, int size) {
    if(index > size) {
        return 1;
    } else if(region == occupied[index]) {
        return 0;
    }

    return isRegionClear(occupied, region, index + 1, size);
}

int isAreaClear(int board[][MAX_BOARD_SIZE], char regions[][MAX_BOARD_SIZE], char occupied[MAX_BOARD_SIZE], int size, int row, int column) {
    int isQueenNotClose;
    if(row == 0) {
        isQueenNotClose = 1;
    } else if (column == 0) {
        isQueenNotClose = !board[row - 1][column] && !board[row - 1][column + 1];
    } else if (column == size) {
        isQueenNotClose = !board[row - 1][column - 1] && !board[row - 1][column];
    } else {
        isQueenNotClose = !board[row - 1][column - 1] && !board[row - 1][column] && !board[row - 1][column + 1];
    }
    int isClearColumn = isColumnClear(board, row - 1, column);
    int isClearRegion = isRegionClear(occupied, regions[row][column], 0, size);

    return isQueenNotClose && isClearColumn && isClearRegion;
}

int placeRow(int board[][MAX_BOARD_SIZE], char regions[][MAX_BOARD_SIZE], char occupied[MAX_BOARD_SIZE], int size, int row, int column) {
    if(column >= size) {
        return 0;
    }

    if(isAreaClear(board, regions, occupied, size, row, column)) {
        board[row][column] = 1;
        occupied[row] = regions[row][column];

        if(placeQueens(board, regions, occupied, size, row + 1)) {
            return 1;
        }

        board[row][column] = 0;
        occupied[row] = '0';
    }

    return placeRow(board, regions, occupied, size, row, column + 1);
}

int placeQueens(int board[][MAX_BOARD_SIZE], char regions[][MAX_BOARD_SIZE], char occupied[MAX_BOARD_SIZE], int size, int row) {
    if(row >= size) {
        return 1;
    }
    
    return placeRow(board, regions, occupied, size, row, 0);
}

void task4QueensBattle() {

    int size;
    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {0};
    char regions[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    char occupied[MAX_BOARD_SIZE];

    printf("Please enter the board dimensions:\n");
    scanf("%d", &size);
    printf("Please enter a %d*%d puzzle board:\n", size, size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            scanf(" %c", &regions[i][j]);
        }
    }
    
    // int result = placeQueens(board, regions, occupied, size, 0);
    if(placeQueens(board, regions, occupied, size, 0)) {
        printBoard(board, size);
    } else {
        printf("This puzzle cannot be solved.\n");
    }
}

void printGrid(char grid[][MAX_GRID], int gridSize) {
    for(int i = 0; i < gridSize; i++) {
        for(int j = 0; j < gridSize; j++) {
            printf("| %c ", grid[i][j] ? grid[i][j] : '#');
        }
        printf("|\n");
    }
}

void clearWord(char grid[][MAX_GRID], struct Slot slot, int position) {
    if(position < 0) {
        return;
    }

    int gridX = slot.x;
    int gridY = slot.y;

    if(slot.direction == 'H') {
        gridY += position;
    } else if(slot.direction == 'V') {
        gridX += position;
    }

    grid[gridX][gridY] = 0;

    return clearWord(grid, slot, position - 1);
}

int doesWordFit(char grid[][MAX_GRID], struct Slot slot, char words[][MAX_WORD], int usedWords[MAX_SLOTS], int word, int position) {
    int wordLength = strlen(words[word]);

    if(position >= wordLength) {
        usedWords[word] = 1;
        return 1;
    }

    int gridX = slot.x;
    int gridY = slot.y;

    if(slot.direction == 'H') {
        gridY += position;
    } else if(slot.direction == 'V') {
        gridX += position;
    }

    if(grid[gridX][gridY] && (grid[gridX][gridY] == '#' || grid[gridX][gridY] != words[word][position]) ) {
        usedWords[word] = 0;
        clearWord(grid, slot, position - 1);
        return 0;
    }

    grid[gridX][gridY] = words[word][position];

    return doesWordFit(grid, slot, words, usedWords, word, position + 1);
}

int fillWord(char grid[][MAX_GRID], struct Slot slots[MAX_SLOTS], char words[][MAX_WORD], int usedWords[MAX_SLOTS], int gridSize, int slotsSize, int wordsSize, int slot, int word) {
    if(word >= wordsSize){
        return 0;
    }

    int wordLength = strlen(words[word]);

    if(usedWords[word] == 1 || wordLength != slots[slot].length || !doesWordFit(grid, slots[slot], words, usedWords, word, 0)) {
        return fillWord(grid, slots, words, usedWords, gridSize, slotsSize, wordsSize, slot, word + 1);
    }

    if(fillGrid(grid, slots, words, usedWords, gridSize, slotsSize, wordsSize, slot + 1)) {
        return 1;
    }

    usedWords[word] = 0;
    clearWord(grid, slots[slot], wordLength);

    return fillWord(grid, slots, words, usedWords, gridSize, slotsSize, wordsSize, slot, word + 1);
}

int fillGrid(char grid[][MAX_GRID], struct Slot slots[MAX_SLOTS], char words[][MAX_WORD], int usedWords[MAX_SLOTS], int gridSize, int slotsSize, int wordsSize, int slot) {
    if(slot >= slotsSize) {
        return 1;
    }

    return fillWord(grid, slots, words, usedWords, gridSize, slotsSize, wordsSize, slot, 0);
}

void task5CrosswordGenerator() {
    char grid[MAX_GRID][MAX_GRID] = {""};
    struct Slot slots[MAX_SLOTS];
    char words[MAX_SLOTS][MAX_WORD] = {""};
    int usedWords[MAX_SLOTS] = {0};
    int gridSize, slotsSize, wordsSize;

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
    
    if(fillGrid(grid, slots, words, usedWords, gridSize, slotsSize, wordsSize, 0)) {
        printGrid(grid, gridSize);
    } else {
        printf("This crossword cannot be solved.\n");
    }

}
