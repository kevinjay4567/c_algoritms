#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *BINARY_FLAG = "--binary";
const char *BINARY_SHORT_FLAG = "-b";

short get_bit(uint16_t number, uint index) {
  uint16_t result = number & (1 << index);

  if (result == 0)
    return 0;
  return 1;
}

void convert(uint16_t number) {
  for (int i = 0; i < 16; i++) {
    printf("%d\n", get_bit(number, i));
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("bcd <binary with b prefix / decimal>\n");
    return 0;
  }

  if (strcmp(argv[1], BINARY_FLAG) == 0 ||
      strcmp(argv[1], BINARY_SHORT_FLAG) == 0) {
  } else {
    /*for (int i = 0; i < (int)strlen(argv[1]); i++) {
      if (!isdigit(argv[1][i])) {
        const char *INVALID_FORMAT_MESSAGE = "Formato invalido: ";
        printf("%s%s\n", INVALID_FORMAT_MESSAGE, argv[1]);
        printf("%*c no es un numero\n", (int) (strlen(INVALID_FORMAT_MESSAGE) +
    i + 1), '^'); return -1;
      }
    }*/

    int digit = atoi(argv[1]);
    if (digit < 0) {
      printf("Error: el numero ingresado debe ser positivo\n");
      return -1;
    }
    printf("Decimal: %d\n", digit);
    printf("Binario: %b\n", digit);
    convert(digit);
  }
  return 0;
}
