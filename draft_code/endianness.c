#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  int32_t value = 0x12345678;
  char str[] = "bye";
  char str2[] = "hello";
  int16_t short_val = 0xaabb;
  printf("%d %s %s, %d\n", value, str, str2, short_val);

  return 0;
}
