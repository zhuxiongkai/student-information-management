#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        fwrite(current, sizeof(Student), 1, file); // 写入学生信息
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

    freeMemory(); // 释放之前的数据

    Student temp;
    Student* last = NULL;

    while (fread(&temp, sizeof(Student), 1, file) == 1) {
        // 为每个学生创建一个新节点
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (newStudent == NULL) {
            printf("内存分配失败！\n");
            fclose(file);
            return;
        }

        // 正确复制数据
        strcpy(newStudent->studentNumber, temp.studentNumber);  // 复制学号
        strcpy(newStudent->name, temp.name);  // 复制姓名
        newStudent->gender = temp.gender;
        newStudent->age = temp.age;
        strcpy(newStudent->specialty, temp.specialty);  // 复制专业
        newStudent->next = NULL;

        // 将新学生节点添加到链表
        if (head == NULL) {
            head = newStudent;
        } else {
            last->next = newStudent;
        }
        last = newStudent;  // 更新last指针，指向最后一个学生节点
    }

    fclose(file);
    printf("数据加载成功！\n");
}
