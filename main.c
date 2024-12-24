#include "file.h"
#include "page.h"
#include "student.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h> // 用于 sleep 函数

int main() {
  int choice;

  displayLogo();
  showProgressBar(); // 添加进度条效果
  clearScreen();
  // 程序启动时加载数据
  loadFromFile();

  while (1) {
    menu();
    scanf("%d", &choice);
    getchar();

    switch (choice) {
    case 1:
      addStudent(); // 输入和增加学生信息的合并
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
    case 6: {
      // 退出前提示
      char confirm;
      printf("\033[33m[提示]\033[0m 你确定要退出吗？(Y/N): ");
      scanf(" %c", &confirm);
      getchar(); // 清除缓冲区

      if (confirm == 'Y' || confirm == 'y') {
        saveToFile(); // 退出前自动保存
        freeMemory();
        printf("\033[32m[成功]\033[0m 数据已保存，退出系统。\n");
        return 0;
      } else {
        printf("已取消退出。\n");
      }
      break;
    }
    default:
      printf("无效的选择，请重新输入。\n");
    }

    // 等待用户按回车键继续
    if (choice != 7) {
      printf("\n\033[34m按回车键继续...\033[0m");
      getchar();
      clearScreen();
    }
  }

  return 0;
}
