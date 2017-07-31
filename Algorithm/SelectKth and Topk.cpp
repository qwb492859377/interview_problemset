#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MX = 1e7 + 5;

int A[MX], B[MX];

// 选出第k大，平均复杂度O(n),因为加了随机化不会不会退化到O(n^2)
int SelectKth(int A[], int k, int l, int r) {
    int len = r - l + 1;
    if(len <= 1) return A[l];

    int rand_pos = rand() % (r - l + 1) + l;
    swap(A[l], A[rand_pos]); //保证不会退化到O(n^2)
    int s = A[l], pl = l, pr = r;
    while(pl < pr) {
        while(pl < pr && A[pr] >= s) pr--;
        A[pl] = A[pr];
        while(pl < pr && A[pl] <= s) pl++;
        A[pr] = A[pl];
    }
    A[pl] = s;

    int now = pl - l + 1; //当前[l, r]中的第几个
    if(now == k) return A[pl];
    else if(now < k) return SelectKth(A, k - now, pl + 1, r);
    return SelectKth(A, k, l, pl - 1);
}

// Topk问题，复杂度O(n+klogk)
void TopK(int A[], int k, int n) {
    SelectKth(A, k, 1, n);
    sort(A + 1, A + k);
}

int main() {
    int n = 1e5;
    for(int i = 1; i <= n; i++) A[i] = i;
    random_shuffle(A + 1, A + 1 + n);

    TopK(A, 10, n);
    for(int i = 1; i <= 10; i++) {
        printf("%d%c", A[i], i == 10 ? '\n' : ' ');
    }
    return 0;
}