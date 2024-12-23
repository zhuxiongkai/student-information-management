#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Student *head = NULL; // 全局链表头指针

// 修改后的findStudent函数
Student *findStudent(int searchType, void *key) {
    Student *current = head;
    while (current != NULL) {
        switch (searchType) {
        case 1: // 按学号查找
            if (strcmp(current->studentNumber, (char *)key) == 0) {
                return current;
            }
            break;
        case 2: // 按姓名查找
            if (strcmp(current->name, (char *)key) == 0) {
                return current;
            }
            break;
        case 3: // 按专业查找
            if (strcmp(current->specialty, (char *)key) == 0) {
                return current;
            }
            break;
        default:
            printf("\033[31m[错误]\033[0m 无效的查找类型！\n");
            return NULL;
        }
        current = current->next;
    }
    return NULL; // 未找到匹配节点
}


// 增加学生信息
void addStudent() {
  Student *newStudent = (Student *)malloc(sizeof(Student));
  if (newStudent == NULL) {
    printf("\033[31m[错误]\033[0m 内存分配失败！\n");
    return;
  }

  while (1) {
    printf("\033[34m[输入]\033[0m 请输入学生学号: ");
    fgets(newStudent->studentNumber, sizeof(newStudent->studentNumber), stdin);
    newStudent->studentNumber[strcspn(newStudent->studentNumber, "\n")] = '\0';

    // 检查学号是否为纯数字
    int isValid = 1;
    for (int i = 0; newStudent->studentNumber[i] != '\0'; i++) {
      if (!isdigit(newStudent->studentNumber[i])) {
        isValid = 0;
        break;
      }
    }

    if (!isValid) {
      printf("\033[33m[提示]\033[0m 学号必须是纯数字，请重新输入。\n");
      continue;
    }

    // 检查学号是否已存在
    if (findStudent(1, newStudent->studentNumber) != NULL) {
      printf("\033[33m[提示]\033[0m 该学号已存在，请重新输入。\n");
      continue;
    }

    break;
  }

  printf("\033[34m[输入]\033[0m 请输入学生姓名: ");
  fgets(newStudent->name, sizeof(newStudent->name), stdin);
  newStudent->name[strcspn(newStudent->name, "\n")] = '\0';

while (1) {
    printf("\033[34m[输入]\033[0m 请输入学生性别 (M/F): ");
    char input[10]; // 用来接收输入
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("\033[33m[提示]\033[0m 输入错误，请重新输入。\n");
        continue;
    }

    // 检查输入是否仅为单个字符 'M' 或 'F'
    if (strlen(input) == 2 && (toupper(input[0]) == 'M' || toupper(input[0]) == 'F') && input[1] == '\n') {
        newStudent->gender = toupper(input[0]); // 转换为大写
        break;
    } else {
        printf("\033[33m[提示]\033[0m 性别必须是单个字符 M 或 F，请重新输入。\n");
    }
}


  printf("\033[34m[输入]\033[0m 请输入学生年龄: ");
  scanf("%d", &newStudent->age);
  getchar(); // 清除输入缓冲区

  printf("\033[34m[输入]\033[0m 请输入学生专业: ");
  fgets(newStudent->specialty, sizeof(newStudent->specialty), stdin);
  newStudent->specialty[strcspn(newStudent->specialty, "\n")] = '\0';

  newStudent->next = NULL;

  if (head == NULL) {
    head = newStudent;
  } else {
    Student *current = head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newStudent;
  }

  printf("\033[32m[成功]\033[0m 学生信息添加成功！\n");
}



// 删除学生信息
void deleteStudent() {
    if (head == NULL) {
        printf("\033[33m[提示]\033[0m 没有学生信息。\n");
        return;
    }

    int studentNumber;
    printf("\033[34m[输入]\033[0m 请输入要删除的学生学号: ");
    scanf("%d", &studentNumber);
    getchar();

    Student *current = findStudent(1, &studentNumber);
    if (current == NULL) {
        printf("\033[33m[提示]\033[0m 未找到学号为 %d 的学生。\n", studentNumber);
        return;
    }

    if (current == head) {
        head = current->next;
    } else {
        Student *prev = head;
        while (prev->next != current) {
            prev = prev->next;
        }
        prev->next = current->next;
    }

    free(current);
    printf("\033[32m[成功]\033[0m 学生信息删除成功！\n");
}

// 修改后的modify函数
void modify() {
    if (head == NULL) {
        printf("\033[33m[提示]\033[0m 没有学生信息。\n");
        return;
    }

    char studentNumber[10];
    printf("\033[34m[输入]\033[0m 请输入要修改的学生学号: ");
    fgets(studentNumber, sizeof(studentNumber), stdin);
    studentNumber[strcspn(studentNumber, "\n")] = '\0'; // 移除换行符

    Student *current = findStudent(1, studentNumber);
    if (current == NULL) {
        printf("\033[33m[提示]\033[0m 未找到学号为 %s 的学生。\n", studentNumber);
        return;
    }

    printf("\033[34m[输入]\033[0m 请输入新的学生姓名: ");
    fgets(current->name, sizeof(current->name), stdin);
    current->name[strcspn(current->name, "\n")] = '\0';
    printf("\033[34m[输入]\033[0m 请输入新的学生性别 (M/F): ");
    scanf(" %c", &current->gender);
    printf("\033[34m[输入]\033[0m 请输入新的学生年龄: ");
    scanf("%d", &current->age);
    getchar(); // 清除输入缓冲区
    printf("\033[34m[输入]\033[0m 请输入新的学生专业: ");
    fgets(current->specialty, sizeof(current->specialty), stdin);
    current->specialty[strcspn(current->specialty, "\n")] = '\0';

    printf("\033[32m[成功]\033[0m 学生信息修改成功！\n");
}


// 查询学生信息
void search() {
    if (head == NULL) {
        printf("\033[33m[提示]\033[0m 没有学生信息。\n");
        return;
    }

    int choice;
    while (1) {
        printf("\n--- \033[32m查询方式\033[0m ---\n");
        printf("----------------\n");
        printf("1. 学号查询\n");
        printf("2. 姓名查询\n");
        printf("3. 专业查询\n");
        printf("4. 退出查询\n");
        printf("----------------\n");
        printf("\033[34m[输入]\033[0m 请输入你的选择（1/2/3/4）: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 4) {
            printf("\033[33m[提示]\033[0m 退出查询\n");
            break;
        }

        void *key;
        char strKey[50];
        int intKey;

        if (choice == 1) {
            printf("\033[34m[输入]\033[0m 请输入学号: ");
            scanf("%d", &intKey);
            getchar();
            key = &intKey;
        } else if (choice == 2) {
            printf("\033[34m[输入]\033[0m 请输入姓名: ");
            fgets(strKey, sizeof(strKey), stdin);
            strKey[strcspn(strKey, "\n")] = '\0';
            key = strKey;
        } else if (choice == 3) {
            printf("\033[34m[输入]\033[0m 请输入专业: ");
            fgets(strKey, sizeof(strKey), stdin);
            strKey[strcspn(strKey, "\n")] = '\0';
            key = strKey;
        } else {
            printf("\033[33m[提示]\033[0m 无效选择，请重新选择。\n");
            continue;
        }

        Student *result = findStudent(choice, key);

        if (result) {
            printf("\n-- \033[32m[查询成功]\033[0m --\n");
            printf("----------------\n");
            printf("学号: %d\n", result->studentNumber);
            printf("姓名: %s\n", result->name);
            printf("性别: %c\n", result->gender);
            printf("年龄: %d\n", result->age);
            printf("专业: %s\n", result->specialty);
            printf("----------------\n");
        } else {
            printf("\033[33m[提示]\033[0m 没有符合条件的学生。\n");
        }
    }
}

// 显示所有学生信息
void display() {
    if (head == NULL) {
        printf("\033[33m[提示]\033[0m 没有学生信息。\n");
        return;
    }

    Student *current = head;
    printf("\n-- \033[32m[学生信息]\033[0m --\n");
    while (current != NULL) {
        printf("学号: %s\n", current->studentNumber);
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
    Student *current = head;
    while (current != NULL) {
        Student *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    printf("\033[32m[成功]\033[0m 内存释放完成。\n");
}