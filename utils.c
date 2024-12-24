#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include <stdio.h>
#include <unistd.h>  // 用于 sleep 函数

// 清屏函数
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// 比较两个学号的数字大小
int compareStudentNumbers(const char *num1, const char *num2) {
    // 跳过前导零（如果有的话）
    while (*num1 == '0' && *num1 != '\0') num1++;
    while (*num2 == '0' && *num2 != '\0') num2++;

    // 如果长度不同，长的学号更大
    size_t len1 = strlen(num1);
    size_t len2 = strlen(num2);
    if (len1 != len2) {
        return len1 - len2;
    }

    // 如果长度相同，逐位比较
    return strcmp(num1, num2);
}

void sortStudentsByNumber(Student *head) {
    if (head == NULL) return;  // 空链表直接返回

    Student *i, *j;
    char tempNumber[20];  // 存储学号的临时变量
    char tempName[50];    // 存储姓名的临时变量
    char tempSpecialty[50]; // 存储专业的临时变量
    int tempAge;
    char tempGender;

    // 遍历链表进行排序
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            // 按学号数字大小比较
            if (compareStudentNumbers(i->studentNumber, j->studentNumber) > 0) {
                // 交换学生学号
                strcpy(tempNumber, i->studentNumber);
                strcpy(i->studentNumber, j->studentNumber);
                strcpy(j->studentNumber, tempNumber);

                // 交换学生姓名
                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                // 交换学生专业
                strcpy(tempSpecialty, i->specialty);
                strcpy(i->specialty, j->specialty);
                strcpy(j->specialty, tempSpecialty);

                // 交换学生性别
                tempGender = i->gender;
                i->gender = j->gender;
                j->gender = tempGender;

                // 交换学生年龄
                tempAge = i->age;
                i->age = j->age;
                j->age = tempAge;
            }
        }
    }
}

// 显示进度条
void showProgressBar() {
  const int total = 50; // 总进度条的字符数
  int progress = 0;

  printf("\n\033[32m[加载中]\033[0m 请稍候...\n");

  // 模拟加载进度
  for (progress = 0; progress <= total; progress++) {
    int i;
    // 打印进度条，绿色部分
    printf("\r\033[32m[");  // 设置进度条开始部分为绿色
    for (i = 0; i < total; i++) {
      if (i < progress) {
        printf("=");  // 已完成部分显示为 "="
      } else {
        printf(" ");  // 未完成部分显示为空格
      }
    }
    printf("]\033[32m %d%%\033[0m", (progress * 100) / total);  // 进度百分比和进度条结束部分为绿色
    fflush(stdout);  // 强制刷新输出
    usleep(50000);  // 每次更新之间暂停50ms，使进度条看起来更平滑
  }

  printf("\n\n");  // 完成后换行
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

