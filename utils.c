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

// 按学号排序学生信息
void sortStudentsByNumber() {
    if (head == NULL || head->next == NULL) {
        return;
    }

    Student* i = head;
    Student* j = NULL;
    int tempNumber;
    char tempName[50];
    char tempGender;
    int tempAge;
    char tempSpecialty[50];

    while (i != NULL) {
        j = i->next;
        while (j != NULL) {
            if (i->studentNumber > j->studentNumber) {
                tempNumber = i->studentNumber;
                i->studentNumber = j->studentNumber;
                j->studentNumber = tempNumber;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                tempGender = i->gender;
                i->gender = j->gender;
                j->gender = tempGender;

                tempAge = i->age;
                i->age = j->age;
                j->age = tempAge;

                strcpy(tempSpecialty, i->specialty);
                strcpy(i->specialty, j->specialty);
                strcpy(j->specialty, tempSpecialty);
            }
            j = j->next;
        }
        i = i->next;
    }
}
