#ifndef TODO_H
#define TODO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <unistd.h>

#define MAX_TASKS 100
#define GLITCH_CHANCE 10

typedef struct {
    int id;
    char description[256];
    int priority;
} Task;

void glitchEffect();
void animatedLogo();
void typewriterEffect(const char *text, int delay);
void loadingAnimation(const char *text);
void shakeEffect(const char *text);
void addTask(Task tasks[], int *task_count);
void viewTasks(Task tasks[], int task_count);
void deleteTask(Task tasks[], int *task_count);
void editTask(Task tasks[], int task_count);
void saveTasksToFile(const char *filename, Task tasks[], int task_count);
void loadTasksFromFile(const char *filename, Task tasks[], int *task_count);
void sortTasksByPriority(Task tasks[], int task_count);
void filterTasksByPriority(Task tasks[], int task_count, int priority);
void printHeader();
void clearScreen();

#endif