#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MX = 1e7 + 5;

int A[MX];

void Maintain(int A[], int p, int n) {
    while(p <= n / 2) {
        int l = p * 2, r = p * 2 + 1, choice;
        if(r <= n) {
            int who_max = A[l] > A[r] ? l : r;
            if(A[who_max] > A[p]) choice = who_max;
            else break;
        } else {
            if(A[l] > A[p]) choice = l;
            else break;
        }
        swap(A[p], A[choice]);
        p = choice;
    }
}
void TreapSort(int A[], int n) {
    // 建最大堆
    for(int i = n / 2; i >= 1; i--) {
        Maintain(A, i, n);
    }

    /*
    当前有i个节点，现在把根节点的值取出来，此时为第i大值，然后与A[i]交换。
    此时A[i]位置就排序好了，那么还剩下了1~i-1这些节点，然后因为有一个新增加的节点在根，
    还需要重新调整一次树的形状
    */
    for(int i = n; i >= 1; i--) {
        swap(A[1], A[i]);
        Maintain(A, 1, i - 1);
    }
}

int main() {
    int n = 1e7;
    for(int i = 1; i <= n; i++) A[i] = i;
    random_shuffle(A + 1, A + 1 + n);
    TreapSort(A, n);

    for(int i = 1; i <= 10; i++) {
        printf("%d%c", A[i], i == n ? '\n' : ' ');
    }
    return 0;
}