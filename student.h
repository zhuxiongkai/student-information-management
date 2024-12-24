#ifndef STUDENT_H
#define STUDENT_H

// 学生结构体定义
typedef struct Student {
    char studentNumber[20]; // 学号
    char name[50];          // 姓名
    char gender;            // 性别
    int age;                // 年龄
    char specialty[50];     // 专业
    struct Student* next;   // 链表指针
} Student;

// 函数声明
void addStudent();
void deleteStudent();
void modify();
void search();
void display();
void saveToFile();
void loadFromFile();
void sortStudentsByNumber(Student *head); // 在展示前对学生信息按学号排序
Student* findStudent( void *key);

extern Student* head;

#endif // STUDENT_H
