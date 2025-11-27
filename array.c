#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t length;
  size_t element_size;
  void *data;
} Array;

Array create_list(u_int size, size_t element_size) {
  Array list = {size, element_size, calloc(element_size * size, element_size)};

  return list;
}

void *get(Array list, u_int index) {
  if (index >= list.length) {
    printf("Error: fuera de rango");
    exit(1);
  }

  return list.data + (index * list.element_size);
}

void set(Array *list, u_int index, void *value) {
  if (index >= list->length) {
    printf("Error: fuera de rango");
  }
  void *dest = list->data + (index * list->element_size);
  memcpy(dest, value, list->element_size);
}

void delete(Array *list) { free(list->data); }

int main() {
  Array letters = create_list(5, sizeof(char));
  char n = 'k';
  set(&letters, 0, &n);
    n = 'e';
  set(&letters, 1, &n);
    n = 'v';
  set(&letters, 2, &n);
    n = 'i';
  set(&letters, 3, &n);
    n = 'n';
  set(&letters, 4, &n);

  for (int i = 0; i < (int)letters.length; i++) {
    printf("%c\n", (*(char *)get(letters, i)));
  }

  delete(&letters);
  return 0;
}
