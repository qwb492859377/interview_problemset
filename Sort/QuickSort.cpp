#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MX = 1e7 + 5;

int A[MX];

//普通的快速排序
void QuickSort1(int A[], int l, int r) {
    if(r - l + 1 <= 1) return;
    int cmp = A[l], pl = l, pr = r;
    while(pl < pr) {
        while(pl < pr && A[pr] >= cmp) pr--;
        A[pl] = A[pr];
        while(pl < pr && A[pl] <= cmp) pl++;
        A[pr] = A[pl];
    }
    A[pl] = cmp;
    QuickSort1(A, l, pl - 1);
    QuickSort1(A, pl + 1, r);
}


// 随机值优化的快速排序
void QuickSort2(int A[], int l, int r) {
    if(r - l + 1 <= 1) return;
    int pos = rand() % (r - l + 1) + l;
    swap(A[l], A[pos]);

    int cmp = A[l], pl = l, pr = r;
    while(pl < pr) {
        while(pl < pr && A[pr] >= cmp) pr--;
        A[pl] = A[pr];
        while(pl < pr && A[pl] <= cmp) pl++;
        A[pr] = A[pl];
    }
    A[pl] = cmp;
    QuickSort2(A, l, pl - 1);
    QuickSort2(A, pl + 1, r);
}

void InsertSort(int A[], int l, int r) {
    for(int i = l; i <= r; i++) {
        for(int j = i; j > l && A[j - 1] > A[j]; j--) {
            swap(A[j - 1], A[j]);
        }
    }
}

// 随机值优化的以及部分插入的快速排序
void QuickSort3(int A[], int l, int r) {
    int len = r - l + 1;
    if(len <= 1) return;
    if(len <= 60) {
        InsertSort(A, l, r);
        return;
    }

    int pos = rand() % (r - l + 1) + l;
    swap(A[l], A[pos]);

    int cmp = A[l], pl = l, pr = r;
    while(pl < pr) {
        while(pl < pr && A[pr] >= cmp) pr--;
        A[pl] = A[pr];
        while(pl < pr && A[pl] <= cmp) pl++;
        A[pr] = A[pl];
    }
    A[pl] = cmp;
    QuickSort3(A, l, pl - 1);
    QuickSort3(A, pl + 1, r);
}

int main() {
    int n = 1e5;
    for(int i = 1; i <= n; i++) A[i] = i;
    // random_shuffle(A + 1, A + 1 + n);
    QuickSort3(A, 1, n);

    for(int i = 1; i <= 10; i++) {
        // printf("%d%c", A[i], i == n ? '\n' : ' ');
    }
    return 0;
}