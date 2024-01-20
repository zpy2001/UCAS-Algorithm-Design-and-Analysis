//
//  main.c
//  rmdigit.c
//
//  Created by 周鹏宇 on 10/24/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printdigit(char n[], unsigned long len) {
  int Lzero = 0;
  while (Lzero < len && n[Lzero] == '0') {
    Lzero++;
  }
  if (Lzero == len) {
    printf("0");
  } else {
    for (size_t i = Lzero; i < len; i++) {
      printf("%c", n[i]);
    }
  }
  printf("\n");
  return;
}

void rmdigit(char n[], int s) {
  unsigned long len = strlen(n);
  int i = 0;
  while (s > 0) {
    if (n[i] > n[i + 1]) {
      for (size_t j = i; j < len - 1; j++) {
        n[j] = n[j + 1];
      }
      len--;
      s--;
      if (i > 0) {
        i--;
      }
    } else {
      i++;
    }
  }

  printdigit(n, len);

  return;
}

int main() {
  char *n = (char *)malloc(sizeof(char) *
                           256);
  printf("Enter your number: ");
  scanf("%s", n);
  printf("Enter your remove count: ");
  int s;
  scanf("%d", &s);
  rmdigit(n, s);
  free(n);
  return 0;
}
