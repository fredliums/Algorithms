#ifndef __BASE_H__
#define __BASE_H__

void print(int *A, int n);
void swap(int *a, int *b);

int bubble_sort(int *A, int n);
int insert_sort(int *A, int n);
int select_sort(int *A, int n);
int merge_sort(int *A, int n);
int heap_sort(int *A, int n);
int quick_sort(int *A, int n);
int shell_sort(int *A, int n);
int shell_sort_b(int *A, int n);

#endif
