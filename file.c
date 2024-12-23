#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // 添加字符串操作函数
#include "student.h"

// 保存数据到文件
void saveToFile() {
    FILE* file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("无法创建文件！\n");
        return;
    }

    Student* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Student), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("数据已成功保存到文件！\n");
}

// 从文件加载数据
void loadFromFile() {
    FILE* file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("没有找到数据文件，将创建新的数据文件。\n");
        return;
    }

    freeMemory();

    Student temp;
    Student* last = NULL;

    while (fread(&temp, sizeof(Student), 1, file) == 1) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (newStudent == NULL) {
            printf("内存分配失败！\n");
            fclose(file);
            return;
        }

        newStudent->studentNumber = temp.studentNumber;
        strcpy(newStudent->name, temp.name);
        newStudent->gender = temp.gender;
        newStudent->age = temp.age;
        strcpy(newStudent->specialty, temp.specialty);
        newStudent->next = NULL;

        if (head == NULL) {
            head = newStudent;
        } else {
            last->next = newStudent;
        }
        last = newStudent;
    }

    fclose(file);
    // printf("数据加载成功！\n");
}
