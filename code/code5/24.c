#include <stdio.h>

//Data structure for a step, especially for printing the solution
typedef struct {
  int num1;
  int num2;
  char op;
  int result;
} Step;

int cards[4];
char ops[4] = {'+', '-', '*', '/'};


//Calculate the result of a operation
int calculate(int a, int b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  }
  return 0;
}

//Judge whether the operation is valid, especially for division
int valid(int a, int b, char op) {
  if (op == '/' && (b == 0 || a % b != 0))
    return 0;
  return 1;
}

void print_solution(Step steps[3]) {
  for (int i = 0; i < 3; ++i) {
    printf("%d %c %d = %d\n", steps[i].num1, steps[i].op, steps[i].num2,
           steps[i].result);
  }
}

int find_solution() {
  Step steps[3];
  //Enumerate all possible numbers
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
    //Make sure no repeated numbers
      if (i != j) {
        //First operation
        for (int k = 0; k < 4; ++k) {
          if (ops[k] == '/' && cards[i] % cards[j] != 0)
            continue;
          int result1 = calculate(cards[i], cards[j], ops[k]);
          //Second number
          for (int m = 0; m < 4; ++m) {
            if (m != i && m != j) {
            //Second operation
              for (int n = 0; n < 4; ++n) {
                if (valid(result1, cards[m], ops[n])) {
                  int result2 = calculate(result1, cards[m], ops[n]);
                  //Third number
                  for (int p = 0; p < 4; ++p) {
                    if (p != i && p != j && p != m) {
                    //Third operation
                      for (int q = 0; q < 4; ++q) {
                        if (valid(result2, cards[p], ops[q]) &&
                            calculate(result2, cards[p], ops[q]) == 24) {
                          steps[0] =
                              (Step){cards[i], cards[j], ops[k], result1};
                          steps[1] = (Step){result1, cards[m], ops[n], result2};
                          steps[2] = (Step){result2, cards[p], ops[q], 24};
                          print_solution(steps);
                          return 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

int main() {
  printf("Enter the numbers on the cards (four integers between 1 and 9): ");
  for (int i = 0; i < 4; ++i) {
    scanf("%d", &cards[i]);
  }

  if (!find_solution()) {
    printf("No Answer!\n");
  }

  return 0;
}