/*
 * heap.cc
 *
 *  Created on: Mar 10, 2021
 *      your implementation of the max-heap in the file heap.cc,
 */
#ifndef HEAP_H_
#define HEAP_H_

#include <cmath>
#include <iostream>
#include "bst.cc"
using namespace std;

float calculate_max(float *heap) {
  float max = heap[0];
  if (max < 0.01)
    max = 0.0;
  return max;
}

void max_heapify(float *heap, int ind, int size) {
  int left_no_element = left(ind) - 1;
  int right_no_element = right(ind) - 1;
  ind--;
  int largest = ind;
  if (left_no_element <= size && heap[left_no_element] > heap[largest]) {
    largest = left_no_element;
  }
  if (right_no_element <= size && heap[right_no_element] > heap[largest]) {
    largest = right_no_element;
  }
  if (largest != ind && heap[largest] >= 0.01) {
    float temp = heap[ind];
    heap[ind] = heap[largest];
    heap[largest] = temp;
    max_heapify(heap, largest + 1, size);
  }
}

float* build_heap(float *heap, int size) {
  int first_root = floor(size / 2);
  for (int i = first_root; i > 0; i--) {
    max_heapify(heap, i, size);
  }
  return heap;
}

#endif /* HEAP_H_ */
