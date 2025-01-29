#include "todo.h"

void glitchEffect() {
    const char *logo =
    " ██   ██  █████  ███    ███  █████  \n"
    " ██   ██ ██   ██ ████  ████ ██   ██ \n"
    "  ██ ██  ███████ ██ ████ ██ ███████ \n"
    "   ███   ██   ██ ██  ██  ██ ██   ██ \n"
    "    █    ██   ██ ██      ██ ██   ██ \n"
    "    █    ██   ██ ██      ██ ██   ██ \n";
    char buffer[500];
    srand(time(NULL));

    for (int g = 0; g < 10; g++) {
        int len = 0;
        for (const char *p = logo; *p; p++) {
            if (rand() % 100 < GLITCH_CHANCE && *p != ' ' && *p != '\n') {
                buffer[len++] = (char)(33 + rand() % 94);
            } else {
                buffer[len++] = *p;
            }
        }
        buffer[len] = '\0';
        printf("\033[1;31m%s\033[0m\n", buffer);
        fflush(stdout);
        usleep(200000);
        printf("\033[2J\033[H");
    }
    loadingAnimation("Repairing system...");
    typewriterEffect(logo, 8);
}

void typewriterEffect(const char *text, int delay) {
    for (int i = 0; text[i] != '\0'; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(delay * 1000);
    }
}

void printHeader() {
    printf("\033[1;32m**********************************\n");
    typewriterEffect("*        Welcome to To-Do        *\n", 50);
    printf("**********************************\n\033[0m");
}

void loadingAnimation(const char *text) {
    char spinner[] = {'|', '/', '-', '\\'};
    for (int i = 0; i < 20; i++) {
        printf("\r\033[1;31m%s %c\033[0m", text, spinner[i % 4]);
        fflush(stdout);
        usleep(100000);
    }
    printf("\r\033[2K");
}

void shakeEffect(const char *text) {
    for (int i = 0; i < 3; i++) {
        printf("\r\033[1;31m%s \033[0m", text);
        fflush(stdout);
        usleep(100000);
        printf("\r \033[1;31m%s\033[0m ", text);
        fflush(stdout);
        usleep(100000);
    }
    printf("\n");
}

void addTask(Task tasks[], int *task_count) {
    if (*task_count >= MAX_TASKS) {
        printf("\033[1;31mMaximum task limit reached!\033[0m\n");
        return;
    }

    Task new_task;
    new_task.id = *task_count + 1;
    printf("\033[1;32mEnter\033[0m the task description: ");
    fgets(new_task.description, sizeof(new_task.description), stdin);
    new_task.description[strcspn(new_task.description, "\n")] = '\0';
    printf("\033[1;32mEnter\033[0m the task priority (\033[1;35m1-5\033[0m): ");
    
    if (scanf("%d", &new_task.priority) != 1 || new_task.priority < 1 || new_task.priority > 5) {
        printf("\033[1;31mInvalid priority! Task not added.\033[0m\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    tasks[(*task_count)++] = new_task;
    printf("\033[1;32mTask added successfully!\033[0m\n");
}

void viewTasks(Task tasks[], int task_count) {
    if (task_count == 0) {
        printf("\033[1;31mNo tasks available.\033[0m\n");
        return;
    }

    printf("\n\033[1;34m===== Task List =====\033[0m\n");
    for (int i = 0; i < task_count; i++) {
        printf("\033[1;33m%d.\033[0m \033[1;36m%s\033[0m (Priority: \033[1;32m%d\033[0m)\n", 
               tasks[i].id, 
               tasks[i].description, 
               tasks[i].priority);

        printf("\033[1;32mPriority bar: \033[0m");
        for (int j = 0; j < tasks[i].priority; j++) {
            printf("*");
        }
        printf("\n\033[1;34m-----------------------------------\033[0m\n");
    }
}

void deleteTask(Task tasks[], int *task_count) {
    if (*task_count == 0) {
        printf("\033[1;31mThere are no tasks to delete!\033[0m\n");
        return;
    }

    int id;
    printf("Enter the \033[1;33mID\033[0m of the task to delete: ");
    scanf("%d", &id);
    getchar();

    int found = 0;
    for (int i = 0; i < *task_count; i++) {
        if (tasks[i].id == id) {
            found = 1;
            for (int j = i; j < *task_count - 1; j++) {
                tasks[j] = tasks[j + 1];
                tasks[j].id--;
            }
            (*task_count)--;
            printf("Task with \033[1;33mID\033[0m \033[1;36m%d\033[0m deleted successfully!\n", id);
            break;
        }
    }

    if (!found) {
        printf("Task with \033[1;33mID\033[0m \033[1;31m%d\033[0m not found!\n", id);
    }
}

void editTask(Task tasks[], int task_count) {
    if (task_count == 0) {
        printf("\033[1;31mThere are no tasks to edit!\033[0m\n");
        return;
    }

    int id;
    printf("\033[1;32mEnter\033[0m the \033[1;33mID\033[0m of the task to edit: ");
    scanf("%d", &id);
    getchar();

    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            found = 1;

            printf("\033[1;32mEnter\033[0m the new task description: ");
            fgets(tasks[i].description, sizeof(tasks[i].description), stdin);
            tasks[i].description[strcspn(tasks[i].description, "\n")] = '\0';

            printf("\033[1;32mEnter\033[0m the new task priority (\033[1;35m1-5\033[0m): ");
            if (scanf("%d", &tasks[i].priority) != 1) {
                printf("\033[1;31mInvalid priority! Task not edited.\033[0m\n");
                while (getchar() != '\n');
                return;
            }

            getchar();

            printf("Task with \033[1;33mID\033[0m \033[1;36m%d\033[0m edited successfully!\n", id);
            break;
        }
    }

    if (!found) {
        printf("Task with \033[1;33mID\033[0m \033[1;31m%d\033[0m not found!\n", id);
    }
}

void saveTasksToFile(const char *filename, Task tasks[], int task_count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("\033[1;31mError opening file for writing!\033[0m\n");
        return;
    }

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%d;%s;%d\n", tasks[i].id, tasks[i].description, tasks[i].priority);
    }

    fclose(file);
    printf("\033[1;32mTasks saved successfully to %s.\033[0m\n", filename);
}

void loadTasksFromFile(const char *filename, Task tasks[], int *task_count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("\033[1;31mError opening file for reading!\033[0m\n");
        return;
    }

    *task_count = 0;

    while (fscanf(file, "%d;%255[^;];%d\n", 
                  &tasks[*task_count].id, 
                  tasks[*task_count].description, 
                  &tasks[*task_count].priority) == 3) {
        (*task_count)++;
        if (*task_count >= MAX_TASKS) {
            printf("\033[1;31mMaximum task limit reached. Some tasks may not have been loaded.\033[0m\n");
            break;
        }
    }

    fclose(file);
    printf("\033[1;32mTasks loaded successfully from %s.\033[0m\n", filename);
}

void sortTasksByPriority(Task tasks[], int task_count) {
    if (task_count == 0) {
        printf("\033[1;31mNo tasks to sort!\033[0m\n");
        return;
    }

    for (int i = 0; i < task_count - 1; i++) {
        for (int j = i + 1; j < task_count; j++) {
            if (tasks[i].priority < tasks[j].priority) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
    printf("\033[1;32mTasks sorted successfully by priority!\033[0m\n");
}

void filterTasksByPriority(Task tasks[], int task_count, int priority) {
    int found = 0;
    printf("\033[1;34m===== Tasks with Priority %d =====\033[0m\n", priority);
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].priority == priority) {
            
            printf("\033[1;33m%d.\033[0m \033[1;36m%s\033[0m (Priority: \033[1;32m%d\033[0m)\n", tasks[i].id, tasks[i].description, tasks[i].priority);
            printf("\033[1;32mPriority bar: \033[0m");
            for (int j = 0; j < tasks[i].priority; j++) {
                printf("*");
            }
            printf("\n\033[1;34m-----------------------------------\033[0m\n");
            found = 1;
        }
    }
    if (!found) {
        printf("\033[1;31mNo tasks found with priority %d.\033[0m\n", priority);
    }
}

void clearScreen() {
    printf("\033[2J\033[1;1H");
}
