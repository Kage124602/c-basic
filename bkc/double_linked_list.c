#include "double_linked_list.h"

#include <stdlib.h>

dll_node_t dll_create_node() {
  dll_node_t n = malloc(sizeof(struct dll_node_s));
  n->next = n->prev = NULL;
  return n;
}

void dll_free_node(dll_node_t node) {
  free(node);
}

dll_t dll_create_list() {
  dll_t list = malloc(sizeof(struct dll_s));
  list->front = list->back = NULL;
  return list;
}

void dll_free_list(dll_t list) {
  while (!dll_is_empty(list)) {
    dll_pop_front(list);
  }
  free(list);
}

void dll_push_back(dll_t list, dll_node_t nn) {
  if (list->back == NULL) {
    list->front = list->back = nn;
  } else {
    list->back->next = nn;
    nn->prev = list->back;
    list->back = nn;
  }
}

void dll_push_front(dll_t list, dll_node_t nn) {
  if (list->front == NULL) {
    list->front = list->back = nn;
  } else {
    list->front->prev = nn;
    nn->next = list->front;
    list->front = nn;
  }
}

void dll_pop_back(dll_t list) {
  if (dll_is_empty(list)) {
    return;
  }
  dll_node_t tmp = list->back;
  list->back = tmp->prev;
  if (list->back) {
    list->back->next = NULL;
  } else {
    list->front = NULL;
  }
  dll_free_node(tmp);
}

void dll_pop_front(dll_t list) {
  if (dll_is_empty(list)) {
    return;
  }
  dll_node_t tmp = list->front;
  list->front = tmp->next;
  if (list->front) {
    list->front->prev = NULL;
  } else {
    list->back = NULL;
  }
  dll_free_node(tmp);
}

dll_node_t dll_front(dll_t list) {
  return list->front;
}

dll_node_t dll_back(dll_t list) {
  return list->back;
}

/* insert nn after pos in list. push_back if pos == NULL */
dll_node_t dll_inserta(dll_t list, dll_node_t pos, dll_node_t nn) {
  if (pos) {
    dll_node_t tmp = pos->next;
    pos->next = nn;
    nn->prev = pos;
    nn->next = tmp;
    if (tmp) {
      tmp->prev = nn;
    } else {
      list->back = nn;
    }
  } else {
    dll_push_back(list, nn);
  }
  return nn;
}

/* insert nn before pos in list. push_front is pos == NULL */
dll_node_t dll_insertb(dll_t list, dll_node_t pos, dll_node_t nn) {
  if (pos) {
    dll_node_t tmp = pos->prev;
    pos->prev = nn;
    nn->next = pos;
    nn->prev = tmp;
    if (tmp) {
      tmp->next = nn;
    } else {
      list->front = nn;
    }
  } else {
    dll_push_front(list, nn);
  }
  return nn;
}

int dll_is_empty(dll_t list) {
  return list->front == NULL && list->back == NULL;
}

long dll_length(dll_t list) {
  long len = 0;
  dll_node_t n = dll_front(list);
  while (n) {
    ++len;
    n = n->next;
  }
  return len;
}

void dll_erase(dll_t list, dll_node_t pos) {
  if (pos == list->front) {
    dll_pop_front(list);
    return;
  }
  if (pos == list->back) {
    dll_pop_back(list);
    return;
  }

  // front < pos < back
  dll_node_t p1 = pos->prev,
             p2 = pos->next;
  p1->next = p2;
  p2->prev = p1;
  dll_free_node(pos);
}

void dll_clear(dll_t list) {
  while (!dll_is_empty(list)) {
    dll_pop_front(list);
  }
}