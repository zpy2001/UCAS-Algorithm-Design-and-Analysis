#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int numRandomNumbers; // 随机数的数量
  FILE *file;

  printf("Random number size is：");
  scanf("%d", &numRandomNumbers);

  // 打开文件以写入模式
  file = fopen("input.txt", "w");

  // 检查文件是否成功打开
  if (file == NULL) {
    printf("无法打开文件。\n");
    return 1;
  }

  // 使用当前时间作为随机数生成器的种子
  srand(time(NULL));

  // 写入随机数数量到文件的第一行
  fprintf(file, "%d\n", numRandomNumbers);

  // 生成并写入随机实数到文件中
  for (int i = 0; i < numRandomNumbers; i++) {
    double randomValue =
        ((double)rand() / RAND_MAX) * 100.0; // 在0到100之间生成随机实数
    fprintf(file, "%.2lf\n", randomValue);   // 保留两位小数
  }

  // 关闭文件
  fclose(file);

  return 0;
}
