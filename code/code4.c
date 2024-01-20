#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a > b) ? (a) : (b))

/*
*由于动态规划一旦找到递推关系，实现和解释起来都十分简单，因此直接在本文件中
*解释，不再单独写README文档。
*本算法的核心在于找到动态规划的数据变化规律，即连续子序列的最大值必然由如下方程给出
*dp[i]=dp[i-1]+a[i]或dp[i]=a[i]
*前者意味着之前累计的子序列和同当前元素相加后仍然大于当前元素，因此可以继续累加；
*后者则意味着之前累计的子序列和不如当前元素的大小，故重新开始计算子序列和。
*/

int maxSubArray(int *nums, int numsSize) {
  int dp[numsSize];
  dp[0] = 0;
  int result = dp[0];
  for (size_t i = 1; i < numsSize + 1; i++) {
    int j = i - 1;
    dp[i] = MAX(dp[i - 1] + nums[j], nums[j]);
    result = MAX(result, dp[i]);
  }
  return result;
}

int main() {
  int *nums = NULL;
  int numsSize = 0;

  printf("请输入整数序列 (以-114514结束):\n");

  while (1) {
    int num;
    scanf("%d", &num);

    if (num == -114514) {
      break;
    }

    int *temp = (int *)realloc(nums, (numsSize + 1) * sizeof(int));
    if (temp == NULL) {
      printf("内存分配失败\n");
      exit(1);
    }
    nums = temp;

    nums[numsSize] = num;
    numsSize++;
  }

  int result = maxSubArray(nums, numsSize);

  printf("最大连续子序列和: %d\n", result);

  free(nums);

  return 0;
}
