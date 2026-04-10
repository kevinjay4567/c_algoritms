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
  return (Array) {
    .length = 0,
    .element_size = element_size,
    .data = malloc(element_size)
  };
}

void *get(Array list, u_int index) {
  if (index >= list.length) {
    printf("Error: fuera de rango");
    exit(1);
  }

  return list.data + (index * list.element_size);
}

void add(Array *list, void *value) {
  if (list->length == 0) {
    memcpy(list->data, value, list->element_size);
    list->length += 1;
    return;
  }

	size_t n_len = list->length + 1;

	void *n_data = realloc(list->data, (list->length * list->element_size));
	if (n_data == NULL) return;

	list->data = n_data;

	memcpy(list->data + (list->length * list->element_size), value, list->element_size);

	list->length = n_len;
}

void set(Array *list, u_int index, void *value) {
  if (index >= list->length) {
    printf("Error: fuera de rango\n");
  }
  void *dest = list->data + (index * list->element_size);
  memcpy(dest, value, list->element_size);
}

void delete(Array *list, u_int index) {
  if (index >= list->length) {
    printf("Error: fuera de rango\n");
  }

  list->length = list->length - 1;

  for (int i = index; i < list->length; i++) {
    void *dest = list->data + i;
    void *value = list->data + i + 1;
    memcpy(dest, value, list->element_size);
  }

  list->data = realloc(list->data, list->length);
}

void free_array(Array *list) {
  free(list->data);
}


int main() {
  Array letters = create_list(sizeof(char));
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

  delete(&letters, 0);

  for (int i = 0; i < (int)letters.length; i++) {
    printf("%c\n", (*(char *)get(letters, i)));
  }

  free_array(&letters);

  return 0;
}
