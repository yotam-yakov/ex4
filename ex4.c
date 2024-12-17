/******************
Name: Yotam Yakov
ID: 207918822
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>

void task1RobotPaths();
void task2HumanPyramid();
void task3ParenthesisValidator();
void task4QueensBattle();
void task5CrosswordGenerator();

int main()
{
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

void task1RobotPaths() {
    // Todo
}

void task2HumanPyramid() {
    // Todo
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
