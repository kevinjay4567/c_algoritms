#include <iso646.h>
#include <sys/types.h>
#define LINKEDLIST_IMPLEMENTATION_H
#include "linkedlist.h"

int main() {
  LinkedList list;

  linked_list_add(&list, 5);
  linked_list_add(&list, 9);
  linked_list_add(&list, 3);

  print_linked_list(list);

  linked_list_remove(&list, 2);

  print_linked_list(list);

  linked_list_insert(&list, 67, 2);

  print_linked_list(list);

  linked_list_insert(&list, 4, 10);

  print_linked_list(list);

  return 0;
}
