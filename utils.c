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

