#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// 清屏函数
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void sortStudentsByNumber(Student *head) {
    if (head == NULL) return;  // 空链表直接返回

    Student *i, *j;
    char tempNumber[10];  // 存储学号的临时变量
    char tempName[50];    // 存储姓名的临时变量
    char tempSpecialty[50]; // 存储专业的临时变量
    int tempAge;
    char tempGender;

    // 遍历链表进行排序
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            // 按学号比较
            if (strcmp(i->studentNumber, j->studentNumber) > 0) {
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

