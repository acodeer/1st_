#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int con_tree(int arr[], int start, int end, int *seg_tree, int current)
{
    if(start == end) //분할 시 남은 노드가 하나일 때
    {
        seg_tree[current] = arr[start]; //리프 노드에 값을 넣어줌
        return arr[start];
    }
    int mid = (start + end)/2;
    int child = 2*current;
    seg_tree[current] = con_tree(arr, start, mid, seg_tree, child+1)
                       + con_tree(arr, mid+1, end, seg_tree, child+2);
    return seg_tree[current];
}

int* con_seg_tree(int arr[], int n)
{
    int height = (int)(ceil(log2(n)));
    int size = 2*(int)pow(2, height) - 1;
    int *seg_tree = (int *)malloc(size*sizeof(int));
    con_tree(arr, 0, n-1, seg_tree, 0);
    return seg_tree;
}
int query_sum(int *seg_tree, int start, int end, int qs, int qe, int current)
{
    if(qs <= start && qe >= end)
        return seg_tree[current];
    if(end < qs || start > qe)
        return 0;
    int mid = (start + end)/2;
    return query_sum(seg_tree, start, mid, qs, qe, 2*current+1)
           + query_sum(seg_tree, mid+1, end, qs, qe, 2*current+2);
}
int Get_query(int *seg_tree, int n, int qs, int qe)
{
    if(qs < 0 || qe > n-1 || qs > qe)
    {
        printf("Invalid Input");
        return -1;
    }
    int sum= 0;
    sum = query_sum(seg_tree, 0, n-1, qs, qe, 0);
    return sum;
}
void seg_tree_update(int *seg_tree, int start, int end, int i, int value, int current)
{
    if(i < start || i > end)
        return;
    seg_tree[current] += value;
    if(start != end)
    {
        int mid = (start + end)/2;
        seg_tree_update(seg_tree, start, mid, i, value, 2*current+1);
        seg_tree_update(seg_tree, mid+1, end, i, value, 2*current+2);
    }
}
void get_value(int *seg_tree, int start, int end, int i, int current)
{
    if(i < start || i > end)
        return;
    
}
int main()
{
    int arr[] = {21, 7, 8, 19, 2, 9, 6, 10};
    int n = sizeof(arr)/sizeof(arr[0]);
    int *seg_tree = con_seg_tree(arr, n);
    int qs = 0;
    int qe = 3;
    printf("Sum of values in given range = %d\n", Get_query(seg_tree, n, qs, qe));
    for(int i = 0; i < 15; i++)
    {
        printf("%d ", seg_tree[i]);
    }
    printf("\n");
    seg_tree_update(seg_tree, 0, n-1, 3, 10, 0);
    for(int i = 0; i < 15; i++)
    {
        printf("%d ", seg_tree[i]);
    }
}