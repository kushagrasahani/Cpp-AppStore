/*
 * hash.cc
 *
 *  Created on: Mar 10, 2021
 *      your implementation of the hash table in the file hash.cc
 */

#ifndef HASH_H_
#define HASH_H_


#include <iostream>
#include <cstring>
#include <cmath>
#include "prime.cc"
#include "defn.h"

int size_of_hash(hash_table_entry *head) {
  int size = 0;
  while (head != NULL) {
    size++;
    head = head->next;
  }
  return size;
}

int count_hash_with_length(hash_table_entry **table, int table_size, int length) {
  int count = 0;
  for (int i = 0; i < table_size; i++) {
    if (size_of_hash(table[i]) == length)
      count++;
  }
  return count;
}

int calculate_hash_table_size(int m) {
  int k = get_first_prime(2 * m);
  return k;
}


int hash_value(const char *name, int m) {
  int sum = 0;
  int i = 0;
  char c = name[i];
  while (c != '\0') {
    int val = c;
    sum += val;
    i++;
    c = name[i];
  }
  return (int) fmod(sum, m);
}

void insert_bst_to_hash(hash_table_entry **table, bst *bst_tree, int size) {
  int ind = hash_value(bst_tree->record.app_name, size);
  hash_table_entry *new_table = new hash_table_entry[sizeof(hash_table_entry)];
  new_table->app_node = bst_tree;
  strcpy(new_table->app_name, bst_tree->record.app_name);
  new_table->next = NULL;
  if (table[ind] == NULL) {
    table[ind] = new_table;
  } else {
    new_table->next = table[ind];
    table[ind] = new_table;
  }
}

bst* search_bst_with_name(hash_table_entry **table, const char *name, int table_size) {
  int ind = hash_value(name, table_size);
  if (table[ind] == NULL)
    return NULL;
  else {
    hash_table_entry *found = table[ind];
    while (found != NULL && strcmp(found->app_name, name) != 0) {
      found = found->next;
    }
    if (found == NULL)
      return NULL;
    else {
      return found->app_node;
    }
  }
}

bool delete_table(hash_table_entry **table, int table_size, const char *name,
                 const char *category) {
  int ind = hash_value(name, table_size);
  hash_table_entry *found_table = table[ind];
  if (found_table == NULL)
    return false;
  else if (strcmp(found_table->app_name, name) == 0
      && strcmp(found_table->app_node->record.category, category) == 0) {
    table[ind] = found_table->next;
    delete[] found_table;
    return true;
  } else {
    while (found_table->next != NULL
        && !(strcmp(found_table->next->app_name, name) == 0
            && strcmp(found_table->next->app_node->record.category, category) == 0)) {
      found_table = found_table->next;
    }
    if (found_table->next == NULL)
      return false;
    else {
      hash_table_entry *next_table = found_table->next;
      found_table->next = next_table->next;
      delete[] next_table;
      next_table = NULL;
      return true;
    }
  }
}

void print_table(hash_table_entry **table, int ind) {
  hash_table_entry *table_ind = table[ind];
  while (table_ind != NULL) {
    std::cout << table_ind->app_name << std::endl;
    table_ind = table_ind->next;
  }
}

#endif /* HASH_H_ */
