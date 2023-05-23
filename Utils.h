#pragma once

#include <iostream>
#include <cstring>
#include <math.h>

// Various utilities, except there's just one here 
struct Utils {
  // Check if a string is equal to a certain command 
  static bool chkcmd(const char* a, const char* b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    if (lenA != lenB) return false;
    for (int i = 0; i < lenA; i++) {
      if (a[i] != b[i]) return false;
    }
    return true;
  }
};