#include "student.h"
#include "ctype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student *head = NULL; // 全局链表头指针

Student *findStudent(void *key) {
  Student *current = head;
  char *studentNumber = (char *)key;

  while (current != NULL) {
    if (strcmp(current->studentNumber, studentNumber) == 0) {
      return current; // 找到匹配的学号，返回该学生
    }
    current = current->next; // 移动到下一个学生
  }
  return NULL; // 没有找到匹配的学生
}

// 根据专业查找多个学生
Student *findStudentsBySpecialty(const char *specialty) {
  Student *current = head;
  Student *resultHead = NULL; // 用于存储匹配的学生
  Student *resultTail = NULL; // 用于指向新链表的最后一个元素

  while (current != NULL) {
    Student *nextStudent = current->next; // 保存下一个节点，以便后续操作

    if (strcmp(current->specialty, specialty) == 0) {
      // 创建新节点，并将当前学生添加到结果链表
      Student *newStudent = (Student *)malloc(sizeof(Student));
      if (newStudent == NULL) {
        printf("\033[31m[错误]\033[0m 内存分配失败！\n");
        return NULL;
      }
      *newStudent = *current; // 复制当前学生的信息

      if (resultHead == NULL) {
        resultHead = resultTail = newStudent; // 初始化结果链表
      } else {
        resultTail->next = newStudent; // 将新学生加入到结果链表
        resultTail = newStudent;
      }
      resultTail->next = NULL; // 确保新链表的最后节点的 next 为 NULL
    }

    current = nextStudent; // 移动到下一个学生
  }

  return resultHead; // 返回匹配的学生链表
}

// 根据姓名查找多个学生
Student *findStudentsByName(const char *name) {
  Student *current = head;
  Student *resultHead = NULL; // 用于存储匹配的学生
  Student *resultTail = NULL; // 用于指向新链表的最后一个元素

  while (current != NULL) {
    Student *nextStudent = current->next; // 保存下一个节点，以便后续操作

    if (strcmp(current->name, name) == 0) {
      // 创建新节点，并将当前学生添加到结果链表
      Student *newStudent = (Student *)malloc(sizeof(Student));
      if (newStudent == NULL) {
        printf("\033[31m[错误]\033[0m 内存分配失败！\n");
        return NULL;
      }
      *newStudent = *current; // 复制当前学生的信息

      if (resultHead == NULL) {
        resultHead = resultTail = newStudent; // 初始化结果链表
      } else {
        resultTail->next = newStudent; // 将新学生加入到结果链表
        resultTail = newStudent;
      }
      resultTail->next = NULL; // 确保新链表的最后节点的 next 为 NULL
    }

    current = nextStudent; // 移动到下一个学生
  }

  return resultHead; // 返回匹配的学生链表
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

    // 检查学号长度是否为12位
    if (strlen(newStudent->studentNumber) != 12) {
      printf("\033[33m[提示]\033[0m 学号必须是12位数字，请重新输入。\n");
      continue;
    }

    // 检查学号是否已存在
    if (findStudent(newStudent->studentNumber) != NULL) {
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
    if (strlen(input) == 2 &&
        (toupper(input[0]) == 'M' || toupper(input[0]) == 'F') &&
        input[1] == '\n') {
      newStudent->gender = toupper(input[0]); // 转换为大写
      break;
    } else {
      printf("\033[33m[提示]\033[0m 性别必须是单个字符 M 或 F，请重新输入。\n");
    }
  }

  // 年龄输入检查：不能为负数，且不能大于200
  while (1) {
    printf("\033[34m[输入]\033[0m 请输入学生年龄: ");
    if (scanf("%d", &newStudent->age) != 1) {
      printf("\033[33m[提示]\033[0m 输入无效，请输入一个有效的年龄。\n");
      getchar(); // 清除缓冲区
      continue;
    }

    if (newStudent->age < 0 || newStudent->age > 200) {
      printf("\033[33m[提示]\033[0m 年龄必须在0到200之间，请重新输入。\n");
      continue;
    }
    getchar(); // 清除输入缓冲区
    break;
  }

  // 专业输入检查：字数不超过8个字
  while (1) {
    printf("\033[34m[输入]\033[0m 请输入学生专业: ");
    fgets(newStudent->specialty, sizeof(newStudent->specialty), stdin);
    newStudent->specialty[strcspn(newStudent->specialty, "\n")] =
        '\0'; // 去除换行符

    if (strlen(newStudent->specialty) > 16) {
      printf("\033[33m[提示]\033[0m 专业名称不能超过8个字，请重新输入。\n");
      continue;
    }

    break;
  }

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
  saveToFile();
  printf("\033[32m[成功]\033[0m 学生信息添加成功！\n");
}

// 删除学生信息
void deleteStudent() {
  if (head == NULL) {
    printf("\033[33m[提示]\033[0m 没有学生信息。\n");
    return;
  }

  char studentNumber[20]; // 修改为字符串类型
  while (1) {
    printf("\033[34m[输入]\033[0m 请输入要删除的学生学号: ");
    fgets(studentNumber, sizeof(studentNumber), stdin);
    studentNumber[strcspn(studentNumber, "\n")] = '\0'; // 去除换行符

    // 检查学号是否为纯数字
    int isValid = 1;
    for (int i = 0; studentNumber[i] != '\0'; i++) {
      if (!isdigit(studentNumber[i])) {
        isValid = 0;
        break;
      }
    }

    // 检查学号长度是否为12位
    if (!isValid) {
      printf("\033[33m[提示]\033[0m 学号必须是纯数字，请重新输入。\n");
      continue;
    }

    if (strlen(studentNumber) != 12) {
      printf("\033[33m[提示]\033[0m 学号必须是12位数字，请重新输入。\n");
      continue;
    }

    // 查找学生
    Student *current = findStudent(studentNumber);
    if (current == NULL) {
      printf("\033[33m[提示]\033[0m 未找到学号为 %s 的学生。\n", studentNumber);
      return;
    }

    // 删除学生
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
    saveToFile();
    printf("\033[32m[成功]\033[0m 学生信息删除成功！\n");
    break;
  }
}

// 修改学生信息的函数
void modify() {
  if (head == NULL) {
    printf("\033[33m[提示]\033[0m 没有学生信息。\n");
    return;
  }

  char studentNumber[13]; // 学号长度应为12，留一个位置给'\0'
  while (1) {
    printf("\033[34m[输入]\033[0m 请输入要修改的学生学号: ");
    fgets(studentNumber, sizeof(studentNumber), stdin);
    studentNumber[strcspn(studentNumber, "\n")] = '\0'; // 去除换行符

    // 检查学号长度是否为12位
    if (strlen(studentNumber) != 12) {
      printf("\033[33m[提示]\033[0m 学号必须是12位数字，请重新输入。\n");
      continue;
    }

    // 检查学号是否为纯数字
    int isValid = 1;
    for (int i = 0; studentNumber[i] != '\0'; i++) {
      if (!isdigit(studentNumber[i])) {
        isValid = 0;
        break;
      }
    }

    if (!isValid) {
      printf("\033[33m[提示]\033[0m 学号必须是纯数字，请重新输入。\n");
      continue;
    }

    // 查找学生
    Student *current = findStudent(studentNumber);
    if (current == NULL) {
      printf("\033[33m[提示]\033[0m 未找到学号为 %s 的学生。\n", studentNumber);
      getchar();
      continue;
    }

    // 修改学生信息
    printf("\033[34m[输入]\033[0m 请输入新的学生姓名: ");
    scanf("%s", current->name);

    while (1) {
      printf("\033[34m[输入]\033[0m 请输入新的学生性别 (M/F): ");
      char genderInput[2];
      scanf("%s", genderInput);
      getchar(); // 清除输入缓冲区

      if (strlen(genderInput) == 1 &&
          (toupper(genderInput[0]) == 'M' || toupper(genderInput[0]) == 'F')) {
        current->gender = toupper(genderInput[0]); // 转换为大写
        break;
      } else {
        printf("\033[33m[提示]\033[0m 性别必须是 M 或 F，请重新输入。\n");
      }
    }

    while (1) {
      printf("\033[34m[输入]\033[0m 请输入新的学生年龄: ");
      if (scanf("%d", &current->age) != 1 || current->age <= 0 ||
          current->age > 200) {
        printf("\033[33m[提示]\033[0m "
               "年龄输入无效，必须是1到200之间的数字，请重新输入。\n");
        while (getchar() != '\n') // 清空输入缓冲区;
        continue;
      }
      break;
    }
getchar();
    // 专业输入检查：字数不超过8个字
    while (1) {
      printf("\033[34m[输入]\033[0m 请输入学生专业: ");
      fgets(current->specialty, sizeof(current->specialty), stdin);
      current->specialty[strcspn(current->specialty, "\n")] =
          '\0'; // 去除换行符

      if (strlen(current->specialty) > 16) {
        printf("\033[33m[提示]\033[0m 专业名称不能超过8个字，请重新输入。\n");
        continue;
      }

      break;
    }
    // 打印修改成功信息
    printf("\033[32m[成功]\033[0m 学生信息修改成功！\n");

    saveToFile(); // 修改成功后保存数据
    break;
  }
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
    printf("\033[34m1. 学号查询\033[0m\n");
    printf("\033[34m2. 姓名查询\033[0m\n");
    printf("\033[34m3. 专业查询\033[0m\n");
    printf("\033[34m4. 退出查询\033[0m\n");
    printf("----------------\n");
    printf("\033[34m[输入]\033[0m 请输入你的选择（1/2/3/4）: ");
    scanf("%d", &choice);
    getchar(); // 清除输入缓冲区

    if (choice == 4) {
      printf("\033[33m[提示]\033[0m 退出查询\n");
      break;
    }

    void *key;
    char strKey[50];
    int intKey;

    Student *results = NULL;

    if (choice == 1) {
      while (1) {
        printf("\033[34m[输入]\033[0m 请输入学号: ");
        scanf("%s", strKey);
        getchar();
        key = strKey;

        // 检查学号是否为纯数字
        int isValid = 1;
        for (int i = 0; strKey[i] != '\0'; i++) {
          if (!isdigit(strKey[i])) {
            isValid = 0;
            break;
          }
        }

        // 检查学号长度是否为12位
        if (!isValid) {
          printf("\033[33m[提示]\033[0m 学号必须是纯数字，请重新输入。\n");
          continue;
        }

        if (strlen(strKey) != 12) {
          printf("\033[33m[提示]\033[0m 学号必须是12位数字，请重新输入。\n");
          continue;
        }

        results = findStudent(key); // 学号查询保持不变
        break;                      // 验证通过后跳出循环
      }
    } else if (choice == 2) {
      printf("\033[34m[输入]\033[0m 请输入姓名: ");
      fgets(strKey, sizeof(strKey), stdin);
      strKey[strcspn(strKey, "\n")] = '\0';
      key = strKey;
      results = findStudentsByName(key); // 使用新的函数查找姓名
    } else if (choice == 3) {
      printf("\033[34m[输入]\033[0m 请输入专业: ");
      fgets(strKey, sizeof(strKey), stdin);
      strKey[strcspn(strKey, "\n")] = '\0';
      key = strKey;
      results = findStudentsBySpecialty(key); // 使用新的函数查找专业
    } else {
      printf("\033[33m[提示]\033[0m 无效选择，请重新选择。\n");
      continue;
    }

    if (results) {
      printf("\n-- \033[32m[查询成功]\033[0m --\n");
      printf("----------------\n");
      Student *temp = results;
      while (temp != NULL) {
        printf("学号: %s\n", temp->studentNumber);
        printf("姓名: %s\n", temp->name);
        printf("性别: %c\n", temp->gender);
        printf("年龄: %d\n", temp->age);
        printf("专业: %s\n", temp->specialty);
        printf("----------------\n");
        if (choice == 1)
          break;
        temp = temp->next; // 移动到下一个匹配的学生
      }
    } else {
      printf("\033[33m[提示]\033[0m 没有符合条件的学生。\n");
    }
  }
}

void display() {
  if (head == NULL) {
    printf("\033[33m[提示]\033[0m 没有学生信息。\n");
    return;
  }
  sortStudentsByNumber(head); // 使用正确的排序函数
  Student *current = head;

  // 打印表头
  printf("\n--------------------------- \033[32m[学生信息]\033[0m "
         "--------------------------\n");
  printf("%-17s %-18s %-10s %-9s %-15s\n", "学号", "姓名", "性别", "年龄",
         "专业");
  printf("-----------------------------------------------------------------\n");

  // 打印学生信息
  while (current != NULL) {
    printf("%-15s %-20s %-8c %-6d %-15s\n", current->studentNumber,
           current->name, current->gender, current->age, current->specialty);
    current = current->next;
  }
  printf("-----------------------------------------------------------------\n");
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
  // printf("\033[32m[成功]\033[0m 内存释放完成。\n");
}