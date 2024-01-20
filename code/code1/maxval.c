//
// Created by 周鹏宇 on 9/14/23.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAXVAL 2144967295
#define MINVAL -2144967295

void BubbleSort(double arr[], int n) {
  int swapped;
  do {
    swapped = 0;
    for (int i = 1; i < n; i++) {
      if (arr[i - 1] > arr[i]) {
        double temp = arr[i - 1];
        arr[i - 1] = arr[i];
        arr[i] = temp;
        swapped = 1;
      }
    }
  } while (swapped);
}

// typedef struct bucket {
//     double data;
//     struct bucket *next;
// } bucket;

typedef struct bucket {
  double min;
  double max;
  int flag;
} bucket;

int main() {
  FILE *file;
  int numRandomNumbers;

  // 打开文件以读取模式
  file = fopen("input.txt", "r");

  // 检查文件是否成功打开
  if (file == NULL) {
    printf("Unable to open the file\n");
    return 1;
  }
  // 读取随机数的数量
  fscanf(file, "%d", &numRandomNumbers);

  // 声明一个数组来存储随机数
  double *randomNumbers = (double *)malloc(numRandomNumbers * sizeof(double));
  double max = MINVAL;
  double min = MAXVAL;
  // 读取随机数并存储到数组中，求出最大最小值
  for (int i = 0; i < numRandomNumbers; i++) {
    fscanf(file, "%lf", &randomNumbers[i]);
    max = MAX(max, randomNumbers[i]);
    min = MIN(min, randomNumbers[i]);
  }

  // 关闭文件
  fclose(file);

  // 求最大间隔的下界，并下取整
  double interval = (max - min) / (numRandomNumbers - 1);

  int numBuckets = numRandomNumbers;
  bucket *buckets = (bucket *)malloc(numBuckets * sizeof(bucket));

  for (int i = 0; i < numBuckets; ++i) {
    buckets[i].max = MINVAL;
    buckets[i].min = MAXVAL;
    buckets[i].flag = -1;
  }

  for (int i = 0; i < numRandomNumbers; ++i) {
    int BucketIdx = (int)((randomNumbers[i] - min) / interval);
    buckets[BucketIdx].min = MIN(buckets[BucketIdx].min, randomNumbers[i]);
    buckets[BucketIdx].max = MAX(buckets[BucketIdx].max, randomNumbers[i]);
    buckets[BucketIdx].flag = 1;
  }

  double result = 0.0;

  for (int i = 0; i < numBuckets;) {
    double bmax = MINVAL;
    double bmin = MAXVAL;
    while (buckets[i].flag == -1) {
      ++i;
    }
    bmax = buckets[i].max;
    ++i;
    while (buckets[i].flag == -1) {
      ++i;
    }

    if (i > numBuckets - 1) {
      break;
    }
    bmin = buckets[i].min;
    result = MAX(result, bmin - bmax);
  }

  //  //进行快排后得到结果进行比较
  //  BubbleSort(randomNumbers, numRandomNumbers);
  //  printf("run to here\n");

  //  double golden = 0;
  //  for (int i = 0; i < numRandomNumbers - 1; ++i) {
  //      golden = MAX(golden, randomNumbers[i + 1] - randomNumbers[i]);
  //  }

  //  // 打印数组中的随机数
  //  for (int i = 0; i < numRandomNumbers; i++) {
  //      printf("%.2lf\n", randomNumbers[i]);
  //  }

  //  printf("max is %2lf\n", result);

  //  if (result == golden) {
  //      printf("Right\n");
  //  } else {
  //      printf("False\n");
  //  }

  // 释放动态分配的内存
  free(randomNumbers);

  file = fopen("output.txt", "w");

  if (file == NULL) {
    printf("Unable to open the file\n");
    return 1;
  }

  fprintf(file, "%lf\n", result);

  fclose(file);

  return 0;
}
