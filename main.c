// Creator: TrojiGareer
#include "todo.h"

#define MAX_TASKS 100

Task tasks[MAX_TASKS];
int task_count = 0;

int main() {
    int choice;
    glitchEffect();
    printHeader();
    do {
        printf("\n\033[1;36m===== Main Menu =====\033[0m\n");
        printf("%-2s %-20s\n", "\033[1;33m1\033[0m", "\033[1;32mAdd\033[0m a task");
        printf("%-2s %-20s\n", "\033[1;33m2\033[0m", "\033[1;32mView\033[0m tasks");
        printf("%-2s %-20s\n", "\033[1;33m3\033[0m", "\033[1;31mDelete\033[0m a task");
        printf("%-2s %-20s\n", "\033[1;33m4\033[0m", "\033[1;33mEdit\033[0m a task");
        printf("%-2s %-20s\n", "\033[1;33m5\033[0m", "\033[1;32mSave\033[0m tasks to file");
        printf("%-2s %-20s\n", "\033[1;33m6\033[0m", "\033[1;36mLoad\033[0m tasks from file");
        printf("%-2s %-20s\n", "\033[1;33m7\033[0m", "\033[1;35mSort\033[0m tasks by \033[1;35mpriority\033[0m");
        printf("%-2s %-20s\n", "\033[1;33m8\033[0m", "\033[1;35mFilter\033[0m tasks by \033[1;35mpriority\033[0m");
        printf("%-2s %-20s\n", "\033[1;33m9\033[0m", "\033[1;31mExit\033[0m");
        printf("\033[1;32mEnter\033[0m your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                clearScreen();
                addTask(tasks, &task_count);
                break;
            case 2:
                clearScreen();
                viewTasks(tasks, task_count);
                break;
            case 3:
                clearScreen();
                deleteTask(tasks, &task_count);
                break;
            case 4:
                clearScreen();
                editTask(tasks, task_count);
                break;
            case 5:
                clearScreen();
                loadingAnimation("Saving tasks...");
                saveTasksToFile("tasks.txt", tasks, task_count);
                break;
            case 6:
                clearScreen();
                loadingAnimation("Loading tasks...");
                loadTasksFromFile("tasks.txt", tasks, &task_count);
                break;
            case 7:
                clearScreen();
                sortTasksByPriority(tasks, task_count);
                break;
            case 8: {
                clearScreen();
                int priority;
                while (1) {
                    printf("\033[1;32mEnter\033[0m the priority to filter by (\033[1;35m1-5\033[0m, or \033[1;32m0\033[0m to \033[1;31mcancel\033[0m): ");
                    if (scanf("%d", &priority) != 1) {
                        printf("\033[1;31mInvalid priority! Try again.\033[0m\n");
                        while (getchar() != '\n');
                        continue;
                    }

                    if (priority == 0) {
                        printf("\033[1;33mFiltering by priority cancelled.\033[0m\n");
                        break;
                    }

                    if (priority >= 1 && priority <= 5) {
                        filterTasksByPriority(tasks, task_count, priority);
                        break;
                    } else {
                        printf("\033[1;31mPriority must be between 1 and 5! Try again.\033[0m\n");
                    }
                }
                break;
            }
            case 9:
                loadingAnimation("Exiting...");
                break;
            default:
                shakeEffect("Invalid choice! Try again.");
        }
    } while (choice != 9);

    return 0;
}