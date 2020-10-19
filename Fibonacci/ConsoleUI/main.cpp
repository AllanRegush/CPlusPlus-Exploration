#include <iostream>


int fib1(int n) {
  if (n < 2) {
    return n;
  }
  return fib1(n - 2) + fib1(n - 1);
}

int fib2(int n) {
  if (n == 0) {
    return n;
  }
  int last = 0;
  int next = 1;
  for(int i = 1; i < n; ++i) {
    int temp = last;
    last = next;
    next = temp + next;
  }
  return next;
}

int main() {
  std::cout << fib1(10) << '\n';
  std::cout << fib2(10) << '\n';
  return 0;
}
