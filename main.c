#include <stdio.h>
#include "page.h"
#include "student.h"
#include "file.h"
#include "utils.h"

int main() {
    int choice;

    displayLogo();  

    // 程序启动时加载数据
    loadFromFile();

    while (1) {
       menu();
        printf("请输入选择: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                addStudent();  // 输入和增加学生信息的合并
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                modify();
                break;
            case 4:
                search();
                break;
            case 5:
                display();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                saveToFile();  // 退出前自动保存
                freeMemory();
                printf("数据已保存，退出系统。\n");
                return 0;
            default:
                printf("无效的选择，请重新输入。\n");
        }

        // 等待用户按回车键继续
        if(choice != 7) {
            printf("\n按回车键继续...");
            getchar();
            clearScreen();
        }
    }

    return 0;
}
