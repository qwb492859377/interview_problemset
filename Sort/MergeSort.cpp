#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MX = 1e7 + 5;

int A[MX], B[MX];

void MergeSort(int A[], int l, int r) {
    int len = r - l + 1;
    if(len <= 1) return;

    int mid = (l + r) >> 1;
    MergeSort(A, l, mid);
    MergeSort(A, mid + 1, r);

    int now = l, pl = l, pr = mid + 1;
    while(pl <= mid || pr <= r) {
        if(pl > mid) B[now++] = A[pr++];
        else if(pr > r) B[now++] = A[pl++];
        else if(A[pl] < A[pr]) B[now++] = A[pl++];
        else B[now++] = A[pr++];
    }
    for(int i = l; i <= r; i++) A[i] = B[i];
}

int main() {
    int n = 1e7;
    for(int i = 1; i <= n; i++) A[i] = i;
    random_shuffle(A + 1, A + 1 + n);
    MergeSort(A, 1, n);

    for(int i = 1; i <= 10; i++) {
        printf("%d%c", A[i], i == n ? '\n' : ' ');
    }
    return 0;
}
