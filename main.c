#include "file.h"
#include "page.h"
#include "student.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>  // 用于 sleep 函数

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
    case 6:
      saveToFile();
      break;
    case 7: {
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
