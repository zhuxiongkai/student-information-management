#ifndef STUDENT_H
#define STUDENT_H

// 学生结构体
typedef struct Student {
    int studentNumber;        // 学号
    char name[50];            // 姓名
    char gender;              // 性别
    int age;                  // 年龄
    char specialty[50];       // 专业
    struct Student* next;     // 链表指针
} Student;

// 全局变量 head
extern Student* head;  // 声明 head 变量，确保其他文件可以访问

// 学生管理操作的函数声明
void addStudent();           // 增加学生信息
void deleteStudent();        // 删除学生信息
void modify();               // 修改学生信息
void search();               // 查询学生信息
void display();              // 显示学生信息
void freeMemory();           // 释放学生信息内存
void sortStudentsByNumber(); // 按学号排序学生信息

#endif // STUDENT_H
