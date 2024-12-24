#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveToFile() {
  FILE *file =
      fopen("students.txt", "w"); // "w" 模式会覆盖文件，使用 "a" 可以追加
  if (file == NULL) {
    printf("\033[31m[错误]\033[0m 无法打开文件保存数据！\n");
    return;
  }

  Student *current = head;
  while (current != NULL) {
    fprintf(file, "%s\n%s\n%c\n%d\n%s\n", current->studentNumber, current->name,
            current->gender, current->age, current->specialty);
    current = current->next;
  }
  printf("\033[32m[成功]\033[0m 数据保存成功\n");
  fclose(file);
}

void loadFromFile() {
  FILE *file = fopen("students.txt", "r");
  if (file == NULL) {
    printf("\033[33m[提示]\033[0m 未找到学生数据文件，初始化为空。\n");
    return;
  }

  while (!feof(file)) {
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
      printf("\033[31m[错误]\033[0m 内存分配失败！\n");
      fclose(file);
      return;
    }

    if (fscanf(file, "%s\n", newStudent->studentNumber) == 1 &&
        fscanf(file, "%s\n", newStudent->name) == 1 &&
        fscanf(file, " %c\n", &newStudent->gender) == 1 &&
        fscanf(file, "%d\n", &newStudent->age) == 1 &&
        fscanf(file, "%s\n", newStudent->specialty) == 1) {

      newStudent->next = head;
      head = newStudent; // 添加到链表的头部
    } else {
      free(newStudent); // 如果读取失败，释放内存
    }
  }

  fclose(file);
}
