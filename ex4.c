/******************
Name: Yotam Yakov
ID: 207918822
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

#define PYRAMID_LEVELS 5

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();

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

        if (scanf("%d", &task)) {
            switch (task) {
            case 6:
                printf("Goodbye!\n");
                break;
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
            default:
                printf("Please choose a task number from the list.\n");
                break;
            }
        } else {
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
        for(int j = 0; j <= i; j++)
        scanf("%f", &pyramid[i][j]);
    }

    for(int i = 0; i < PYRAMID_LEVELS; i++) {
        for(int j = 0; j <= i; j++) {
            float posWeight = pyramidWeight(pyramid, PYRAMID_LEVELS, i, j);
            weights[i][j] = posWeight;
            printf("%.2f ", weights[i][j]);
        }
        printf("\n");
    }
}

void task3ParenthesisValidator() {
    // Todo
}

void task4QueensBattle() {
    // Todo
}

void task5CrosswordGenerator() {
    // Todo
}
