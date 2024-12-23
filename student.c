#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student* head = NULL;  // 全局链表头指针

// 增加学生信息
void addStudent() {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("内存分配失败！\n");
        return;
    }

    printf("请输入学生学号: ");
    scanf("%d", &newStudent->studentNumber);
    getchar();  // 清除输入缓冲区
    printf("请输入学生姓名: ");
    fgets(newStudent->name, sizeof(newStudent->name), stdin);
    newStudent->name[strcspn(newStudent->name, "\n")] = '\0';
    printf("请输入学生性别 (M/F): ");
    scanf(" %c", &newStudent->gender);
    printf("请输入学生年龄: ");
    scanf("%d", &newStudent->age);
    getchar();  // 清除输入缓冲区
    printf("请输入学生专业: ");
    fgets(newStudent->specialty, sizeof(newStudent->specialty), stdin);
    newStudent->specialty[strcspn(newStudent->specialty, "\n")] = '\0';

    newStudent->next = NULL;

    if (head == NULL) {
        head = newStudent;
    } else {
        Student* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }

    printf("学生信息添加成功！\n");
}

// 删除学生信息
void deleteStudent() {
    if (head == NULL) {
        printf("没有学生信息。\n");
        return;
    }

    int studentNumber;
    printf("请输入要删除的学生学号: ");
    scanf("%d", &studentNumber);
    getchar();  // 清除输入缓冲区

    Student* current = head;
    Student* prev = NULL;

    while (current != NULL && current->studentNumber != studentNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("未找到学号为 %d 的学生。\n", studentNumber);
        return;
    }

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("学生信息删除成功！\n");
}

// 修改学生信息
void modify() {
    if (head == NULL) {
        printf("没有学生信息。\n");
        return;
    }

    int studentNumber;
    printf("请输入要修改的学生学号: ");
    scanf("%d", &studentNumber);
    getchar();

    Student* current = head;
    while (current != NULL && current->studentNumber != studentNumber) {
        current = current->next;
    }

    if (current == NULL) {
        printf("未找到学号为 %d 的学生。\n", studentNumber);
        return;
    }

    printf("请输入新的学生学号: ");
    scanf("%d", &current->studentNumber);
    getchar();
    printf("请输入新的学生性别 (M/F): ");
    scanf(" %c", &current->gender);
    printf("请输入新的学生年龄: ");
    scanf("%d", &current->age);
    getchar();
    printf("请输入新的学生专业: ");
    fgets(current->specialty, sizeof(current->specialty), stdin);
    current->specialty[strcspn(current->specialty, "\n")] = '\0';

    printf("学生信息修改成功！\n");
}

// 查询学生信息
void search() {
    if (head == NULL) {
        printf("没有学生信息。\n");
        return;
    }

    int choice;
    while (1) {  // 使用循环让用户可以继续查询
        printf("\n请选择查询方式:\n");
        printf("1. 按学号查询\n");
        printf("2. 按姓名查询\n");
        printf("3. 按专业查询\n");
        printf("4. 退出查询\n");
        printf("请输入你的选择（1/2/3/4）: ");
        scanf("%d", &choice);
        getchar();  // 读取缓冲区的换行符，防止影响后续输入

        if (choice == 4) {
            printf("退出查询。\n");
            break;  // 用户选择退出，结束查询循环
        }

        Student* current = head;
        int found = 0;

        switch (choice) {
            case 1: {
                // 按学号查询
                int studentNumber;
                printf("请输入学号: ");
                scanf("%d", &studentNumber);
                getchar();  // 读取换行符

                printf("\n--- 查询结果 ---\n");
                while (current != NULL) {
                    if (current->studentNumber == studentNumber) {
                        printf("学号: %d\n", current->studentNumber);
                        printf("姓名: %s\n", current->name);
                        printf("性别: %c\n", current->gender);
                        printf("年龄: %d\n", current->age);
                        printf("专业: %s\n", current->specialty);
                        printf("----------------\n");
                        found = 1;
                        break;  // 找到后退出循环
                    }
                    current = current->next;
                }
                break;
            }
            case 2: {
                // 按姓名查询
                char name[50];
                printf("请输入姓名: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';  // 去除换行符

                printf("\n--- 查询结果 ---\n");
                while (current != NULL) {
                    if (strcmp(current->name, name) == 0) {
                        printf("学号: %d\n", current->studentNumber);
                        printf("姓名: %s\n", current->name);
                        printf("性别: %c\n", current->gender);
                        printf("年龄: %d\n", current->age);
                        printf("专业: %s\n", current->specialty);
                        printf("----------------\n");
                        found = 1;
                        break;  // 找到后退出循环
                    }
                    current = current->next;
                }
                break;
            }
            case 3: {
                // 按专业查询
                char specialty[50];
                printf("请输入专业: ");
                fgets(specialty, sizeof(specialty), stdin);
                specialty[strcspn(specialty, "\n")] = '\0';  // 去除换行符

                printf("\n--- 查询结果 ---\n");
                while (current != NULL) {
                    if (strcmp(current->specialty, specialty) == 0) {
                        printf("学号: %d\n", current->studentNumber);
                        printf("姓名: %s\n", current->name);
                        printf("性别: %c\n", current->gender);
                        printf("年龄: %d\n", current->age);
                        printf("专业: %s\n", current->specialty);
                        printf("----------------\n");
                        found = 1;
                    }
                    current = current->next;
                }
                break;
            }
            default:
                printf("无效选择，请重新选择。\n");
                continue;  // 重新开始循环，防止出现不必要的输出
        }

        if (!found) {
            printf("没有符合条件的学生。\n");
        }
    }
}



// 显示所有学生信息
void display() {
    if (head == NULL) {
        printf("没有学生信息。\n");
        return;
    }

    // 按学号排序学生信息
    sortStudentsByNumber();

    Student* current = head;
    printf("\n--- 学生信息 ---\n");
    while (current != NULL) {
        printf("学号: %d\n", current->studentNumber);
        printf("姓名: %s\n", current->name);
        printf("性别: %c\n", current->gender);
        printf("年龄: %d\n", current->age);
        printf("专业: %s\n", current->specialty);
        printf("----------------\n");
        current = current->next;
    }
}

// 释放内存
void freeMemory() {
    Student* current = head;
    while (current != NULL) {
        Student* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}
