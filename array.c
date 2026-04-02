#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t length;
  size_t element_size;
  void *data;
} Array;

Array create_list(size_t element_size) {
  Array list = {1, element_size, calloc(element_size, element_size)};

  return list;
}

void *get(Array list, u_int index) {
  if (index >= list.length) {
    printf("Error: fuera de rango");
    exit(1);
  }

  return list.data + (index * list.element_size);
}

void add(Array *list, void *value) {
	size_t n_len = list->length + 1;

	void *n_data = realloc(list->data, (list->length * list->element_size));
	if (n_data == NULL) return;

	list->data = n_data;

	memcpy(list->data + (list->length * list->element_size), value, list->element_size);

	list->length = n_len;
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
  Array letters = create_list(sizeof(char));
  int *p;
  char n = 'k';
  add(&letters, &n);
  n = 'e';
  add(&letters, &n);
  n = 'v';
  add(&letters, &n);
  n = 'i';
  add(&letters, &n);
  n = 'n';
  add(&letters, &n);

  for (int i = 0; i < (int)letters.length; i++) {
    printf("%c\n", (*(char *)get(letters, i)));
  }

  delete(&letters);

  return 0;
}
