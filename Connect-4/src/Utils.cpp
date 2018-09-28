#include "Utils.hpp"

int toDigit(char c) {
  if (!isdigit(c))
    return -1;
  return c-'0';
}

int getMin(int a, int b) {
  if (a < b)
    return a;
  return b;
}

int getMax(int a, int b) {
  if (a > b)
    return a;
  return b;
}
