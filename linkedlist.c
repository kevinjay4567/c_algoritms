#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct {
  int val;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *first;
  Node *last;
} LinkedList;

void print_linked_list(LinkedList list) {
  Node *node = list.first;

  while (node->next) {
    printf("%d -> ", node->val);

    node = (Node *)node->next;
  }

  printf("%d\n", list.last->val);
}

Node *create_node(int val) {
  Node *node = malloc(sizeof *node);

  if (!node) {
    return NULL;
  }

  node->val = val;

  return node;
}

void linked_list_add(LinkedList *list, int in) {
  Node *node = create_node(in);

  if (!node) {
    return;
  }

  if (!list->first) {
    list->first = node;
    list->last = node;
    return;
  }

  if (!list->first->next) {
    list->first->next = (struct Node *)node;
  }

  node->prev = (struct Node *)list->last;
  list->last->next = (struct Node *)node;
  list->last = node;
}

void linked_list_insert(LinkedList *list, int val, int index) {
  if (index < 0) {
    printf("Error: El indice debe ser positivo\n");
    return;
  }
  Node *node = create_node(val);

  if (!node) {
    return;
  }

  if (index == 0) {
    Node *target = list->first;
    target->prev = (struct Node *)node;
    list->first = node;
    list->first->next = (struct Node *)target;
    return;
  }

  Node *pivot = (Node *)list->first->next;
  int count = 1;
  while (pivot->next) {
    if (count == index) {
      Node *target_prev = (Node *)pivot->prev;
      target_prev->next = (struct Node *)node;
      pivot->prev = (struct Node *)node;
      return;
    }

    pivot = (Node *)pivot->next;
    count++;
  }

  if (count == index) {
    Node *target = list->last;
    Node *target_prev = (Node *)list->last->prev;
    target_prev->next = (struct Node *)node;
    target->prev = (struct Node *)node;
    node->prev = (struct Node *)target_prev;
    node->next = (struct Node *)target;
    return;
  }

  if ((count + 1) == index) {
    Node *target = list->last;
    target->next = (struct Node *)node;
    list->last = node;
    node->prev = (struct Node *)target;
    return;
  }

  printf("Error: Indice fuera de rango\n");
}

void linked_list_remove(LinkedList *list, int index) {
  if (index < 0) {
    return;
  }
  if (!list->first) {
    return;
  }

  if (!list->first->next) {
    list->first = NULL;
    list->last = NULL;
    free(list->first);
    return;
  }

  Node *node = list->first;
  int count = 0;
  while (node->next) {

    if (count == index) {

      if (!node->prev) {
        list->first = (Node *)list->first->next;
        list->first->prev = NULL;
        free(node);
        return;
      }

      Node *target_prev = (Node *)node->prev;
      target_prev->next = node->next;
      Node *target_next = (Node *)node->next;
      target_next->prev = node->prev;
      free(node);
      return;
    }

    node = (Node *)node->next;
    count++;
  }

  if (count == index) {
    Node *target_prev = (Node *)list->last->prev;
    Node *target = list->last;

    list->last = target_prev;
    target_prev->next = NULL;

    free(target);
  }
}

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
