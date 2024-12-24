#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 保存数据到文件
void saveToFile() {
  FILE *file = fopen("students.txt", "w");
  if (file == NULL) {
    printf("无法创建文件！\n");
    return;
  }

  Student *current = head;
  while (current != NULL) {
    // 将学生信息格式化为字符串并写入文件
    fprintf(file, "%s %s %c %d %s\n", current->studentNumber, current->name,
            current->gender, current->age, current->specialty);
    current = current->next;
  }

  fclose(file);
  printf("\033[32m[成功]\033[0m 数据已成功保存到文件！\n");
}

// 从文件加载数据
void loadFromFile() {
  FILE *file = fopen("students.txt", "r");
  if (file == NULL) {
    printf("没有找到数据文件，将创建新的数据文件。\n");
    return;
  }

  freeMemory(); // 释放之前的数据

  Student *last = NULL; // 用于记录链表尾部

  // 逐行读取数据
  Student temp;
  while (fscanf(file, "%s %s %c %d %s", temp.studentNumber, temp.name,
                &temp.gender, &temp.age, temp.specialty) == 5) {
    // 为每个学生创建一个新节点
    Student *newStudent = (Student *)malloc(sizeof(Student));
    if (newStudent == NULL) {
      printf("内存分配失败！\n");
      fclose(file);
      return;
    }

    // 复制临时变量的数据到新学生节点
    strcpy(newStudent->studentNumber, temp.studentNumber);
    strcpy(newStudent->name, temp.name);
    newStudent->gender = temp.gender;
    newStudent->age = temp.age;
    strcpy(newStudent->specialty, temp.specialty);

    newStudent->next = NULL;

    // 如果链表为空，初始化头指针
    if (head == NULL) {
      head = newStudent;
    } else {
      // 否则，找到链表尾部并插入新学生
      last->next = newStudent;
    }

    last = newStudent; // 更新尾指针
  }

  fclose(file);
  printf("\033[32m[成功]\033[0m 数据已成功加载。\n");
}
