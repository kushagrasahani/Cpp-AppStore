
/*
 * bst.cc
 *
 *  Created on: Mar 10, 2021
 *      your implementation of the BST in the file bst.cc
 */

#ifndef BST_H_
#define BST_H_

#include <cmath>
#include <iostream>
#include <cstring>
#include "defn.h"
using namespace std;

bst* append_bts_with_other(bst *root, bst *other) {
  if (root == NULL) {
    root = other;
    return root;
  }
  if (strcmp(other->record.app_name, root->record.app_name) > 0) {
    root->right = append_bts_with_other(root->right, other);
  } else {
    root->left = append_bts_with_other(root->left, other);
  }
  return root;
}

int size_of_bst(bst *root) {
  if (root == NULL)
    return 0;
  int left_size = 0;
  if (!root->left)
    left_size = size_of_bst(root->left);
  int right_size = 0;
  if (!root->right)
    right_size = size_of_bst(root->right);
  return (1 + left_size + right_size);
}

bst* free_bst(bst *root) {
  if (root == NULL)
    return NULL;
  root->right = free_bst(root->right);
  root->left = free_bst(root->left);
  delete[] root;
  root = NULL;
  return root;
}

bst* find_min_node(bst *root) {
  if (root->left == NULL)
    return root;
  return find_min_node(root->left);
}

bst* find_max_node(bst *root) {
  if (root->right == NULL)
    return root;
  return find_max_node(root->right);
}

bst* successor(bst *root) {
  if (root->right != NULL)
    return find_min_node(root->right);
  else {
    return root;
  }
  return find_min_node(root->right);
}

bst* predecessor(bst *root) {
  if (root->left != NULL)
    return find_max_node(root->left);
  else {
    return root;
  }
}

bst* remove_node(const char *node_key, bst *root) {
  if (root == NULL)
    return NULL;
  else if (strcmp(node_key, root->record.app_name) > 0)
    root->right = remove_node(node_key, root->right);
  else if (strcmp(node_key, root->record.app_name) < 0)
    root->left = remove_node(node_key, root->left);
  else {
    if (root->left == NULL) {
      bst *root_candidate = root->right;
      delete[] root;
      root = NULL;
      return root_candidate;
    } else if (root->right == NULL) {
      bst *root_candidate = root->left;
      delete[] root;
      root = NULL;
      return root_candidate;
    } else {
      bst *pred = predecessor(root);
      root->record = pred->record;
      root->left = remove_node(pred->record.app_name, root->left);
    }
  }
  return root;
}

bst* search_node(char *node_key, bst *root) {
  if (root == NULL)
    return NULL;
  else if (strcmp(node_key, root->record.app_name) == 0)
    return root;
  else if (strcmp(node_key, root->record.app_name) < 0)
    return search_node(node_key, root->left);
  else
    return search_node(node_key, root->right);
}

int get_height_bst(bst *root) {
  if (root == NULL)
    return 0;
  int left_height = 0;
  int right_height = 0;
  if (root->left != NULL)
    left_height = 1 + get_height_bst(root->left);
  if (root->right != NULL)
    right_height = 1 + get_height_bst(root->right);
  if (left_height > right_height)
    return left_height;
  return right_height;
}

int left(int p) {
  return 2 * p;
}

int right(int p) {
  return 2 * p + 1;
}

int parent(int p) {
  return floor(p / 2);
}

#endif /* BST_H_ */
