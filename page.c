#include "utils.h"
#include <stdio.h>
// 显示logo
void displayLogo() {
  printf("\033[1;32m"); // 设置字体为绿色
  printf("\n");
  printf("                          --- 学生信息管理系统 ---    \n");
  printf("====================================================================="
         "===========\n");
  printf("                         ____  _             _      \n");
  printf("                        / ___|| |_   _ _ __ (_) ___ \n");
  printf("                        \\___ \\| | | | | '_ \\| |/ _ \\\n");
  printf("                         ___) | | |_| | | | | |  __/\n");
  printf("                        |____/|_|\\__,_|_| |_|_|\\___|\n");
  printf("\n");
  printf("                        欢迎来到学生信息管理系统！\n");
  printf("====================================================================="
         "===========\n");
  printf("\033[1;34m"); // 设置字体为绿色
  printf("回车进入系统~~~");
  getchar();
  clearScreen();
}

// 主菜单
void menu() {
  printf("\033[1;32m");
  printf("       ===========================================\n");
  printf("       ==     ** 学生信息管理系统操作栏 **      ==\n");
  printf("       ===========================================\n");
  printf("\033[0m"); // 重置为默认颜色
  printf("       ==             \033[34m1. 增加记录\033[0m               ==\n");
  printf("       ==             \033[34m2. 删除信息\033[0m               ==\n");
  printf("       ==             \033[34m3. 修改信息\033[0m               ==\n");
  printf("       ==             \033[34m4. 查询信息\033[0m               ==\n");
  printf("       ==             \033[34m5. 展示信息\033[0m               ==\n");
  printf("       ==             \033[34m6. 保存数据\033[0m               ==\n");
  printf("       ==             \033[34m7. 退出系统\033[0m               ==\n");
  printf("       ===========================================\n");
  printf("       ===========================================\n");
  printf("\033[34m请输入选择:\033[0m ");
}