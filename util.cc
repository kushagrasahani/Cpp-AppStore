/*
 * util.cc
 *
 *  Created on: Mar 10, 2021
 *      your implementation of any utility functions in the file util.cc.
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <iostream>
#include <cstdio>
#include <string>
#include "bst.cc"
#include "heap.cc"
using namespace std;

void print_app_info(app_info info) {
  cout << "\t\tCategory: " << info.category << endl;
  cout << "\t\tApp Name: " << info.app_name << endl;
  cout << "\t\tVersion: " << info.version << endl;
  cout << "\t\tSize: " << info.size << endl;
  cout << "\t\tUnits: " << info.units << endl;
  printf("\t\tPrice: $%.2f\n", info.price);
}

void order_print_app_by_name(bst *root) {
  if (root->left != NULL)
    order_print_app_by_name(root->left);
  cout << "\t\t" << root->record.app_name << endl;
  if (root->right != NULL)
    order_print_app_by_name(root->right);
}

void print_the_query(bst *root) {
  if (root == NULL)
    return;
  else
    order_print_app_by_name(root);
}

int copy_value_to_heap(float *heap, int size, int ind, bst *root) {
  if (root->left != NULL) {
    ind = copy_value_to_heap(heap, size, ind, root->left);
  }
  if (root->record.price < 0.01)
    heap[ind] = 0;
  else
    heap[ind] = root->record.price;
  ind++;
  if (root->right != NULL) {
    ind = copy_value_to_heap(heap, size, ind, root->right);
  }
  return ind;
}

void print_app_name_with_price(bst *root, float price) {
  if (root->left != NULL)
    print_app_name_with_price(root->left, price);
  if (root->record.price == price)
    cout << "\t\t" << root->record.app_name << endl;
  if (root->right != NULL)
    print_app_name_with_price(root->right, price);
}

void find_max_price(bst *root) {
  if (root == NULL)
    return;
  else {
    int c = size_of_bst(root);
    float *heap = new float[c];
    copy_value_to_heap(heap, c, 0, root);
    build_heap(heap, c);
    float maxPrice = calculate_max(heap);
    char price[10] = "";
    //sscanf(price, "%.2f", maxPrice);
    sscanf(price, "%f", &maxPrice);
    delete[] heap;
    print_app_name_with_price(root, maxPrice);
  }
}

void order_print_app_name_in_range_price(bst *root, float low, float high) {
  if (root->left != NULL && root->left->record.price >= low)
    order_print_app_name_in_range_price(root->left, low, high);
  cout << "\t\t" << root->record.app_name << endl;
  if (root->right != NULL && root->right->record.price <= high)
    order_print_app_name_in_range_price(root->right, low, high);
}

bool print_app_name_in_range_price(bst *root, float low, float high) {
  bool is_valid_range;
  if (root == NULL) {
    is_valid_range = true;
  } else if (root->record.price > high) {
    is_valid_range = print_app_name_in_range_price(root->left, low, high);
  } else if (root->record.price < low) {
    is_valid_range = print_app_name_in_range_price(root->right, low, high);
  } else {
    is_valid_range = false;
    cout << "\tApplications in Price Range (";
    printf("$%.2f", low);
    cout << ", ";
    printf("$%.2f", high);
    cout << ") in Category: " << root->record.category << endl;
    order_print_app_name_in_range_price(root, low, high);
  }
  return is_valid_range;
}

void order_print_app_name_in_range_name(bst *root, char low, char high) {
  if (root->left != NULL && root->left->record.app_name[0] >= low)
    order_print_app_name_in_range_name(root->left, low, high);
  cout << "\t\t" << root->record.app_name << endl;
  if (root->right != NULL && root->right->record.app_name[0] <= high)
    order_print_app_name_in_range_name(root->right, low, high);
}

bool print_app_name_in_range_name(bst *root, char low, char high) {
  bool is_valid_range;
  if (root == NULL) {
    is_valid_range = true;
  } else if (root->record.app_name[0] > high) {
    is_valid_range = print_app_name_in_range_name(root->left, low, high);
  } else if (root->record.app_name[0] < low) {
    is_valid_range = print_app_name_in_range_name(root->right, low, high);
  } else {
    is_valid_range = false;
    cout << "\tApplications in Range (" << low << ", " << high
         << ") in Category: " << root->record.category << endl;
    order_print_app_name_in_range_name(root, low, high);
  }
  return is_valid_range;
}

int type_of_query(string query) {
  int ind_str;
  int length = query.length();
  ind_str = query.find("find app");
  if (ind_str > -1 && ind_str < length)
    return 1;
  ind_str = query.find("find max price apps");
  if (ind_str > -1 && ind_str < length)
    return 2;
  ind_str = query.find("print-apps category");
  if (ind_str > -1 && ind_str < length)
    return 3;
  ind_str = query.find("find price free");
  if (ind_str > -1 && ind_str < length)
    return 4;
  ind_str = query.find("range");
  if (ind_str > -1 && ind_str < length) {
    ind_str = query.find("price");
    if (ind_str > -1 && ind_str < length)
      return 5;
    else
      return 6;
  }
  ind_str = query.find("delete");
  if (ind_str > -1 && ind_str < length)
    return 7;
  ind_str = query.find("report");
  if (ind_str > -1 && ind_str < length) {
    ind_str = query.find("no");
    if (ind_str > -1 && ind_str < length)
      return 8;
    else
      return 9;
  }
  // invalid rang
  return -1;
}

#endif
