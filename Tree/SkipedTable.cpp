#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

// 感觉我的跳跃表慢的出翔。。
class SkipedTable {
private:
    static const int MAX_HEIGHT = 30;
    const int INF = INT_MAX;
    const double P = 0.25;

    struct Node {
        int val;
        Node *up, *down;
        Node *left, *right;
        Node(int _val) {
            val = _val;
            up = down = NULL;
            left = right = NULL;
        }
    };

    Node *head[MAX_HEIGHT];

    int min(int a, int b) {
        return a < b ? a : b;
    }
    int get_random_height() {
        int ret = 1;
        while(true) {
            double p = 1.0 * rand() / RAND_MAX;
            if(p <= P) ret++;
            else break;
        }
        return min(ret, MAX_HEIGHT - 1);
    }

public:
    int height;

    SkipedTable() {
        // srand(time(NULL));
        for(int i = 1; i < MAX_HEIGHT; i++) {
            head[i] = NULL;
        }

        height = 1;
        Node *a = new Node(-INF), *b = new Node(INF);
        a->right = b; b->left = a; head[height] = a;
    }

    void insert(int x) {
        Node *now = head[height];
        for(int i = height; i >= 1; i--) {
            while(now->right->val < x) {
                now = now->right;
            }
            if (i != 1) {
                now = now->down;
            }
        }

        Node *end_inf = head[height];
        while(end_inf->right != NULL) {
            end_inf = end_inf->right;
        }

        int h = get_random_height();
        for(int i = height + 1; i <= h; i++) {
            Node *a = new Node(-INF), *b = new Node(INF);
            a->right = b; b->left = a; head[i] = a;
            a->down = head[i - 1]; head[i - 1]->up = a;
            b->down = end_inf; end_inf->up = b;
            end_inf = b;
        }

        Node *last = NULL;
        height = max(height, h);
        for(int i = 1; i <= height; i++) {
            Node *temp = new Node(x);
            if(last != NULL) {
                temp->down = last;
                last->up = temp;
            }
            last = temp;

            temp->right = now->right;
            now->right->left = temp;
            temp->left = now;
            now->right = temp;

            if(i != height) {
                while(now->up == NULL) {
                    now = now->left;
                }
                now = now->up;
            }
        }
    }
    bool exists(int x) {
        Node *now = head[height];
        now = head[height];
        for(int i = height; i >= 1; i--) {
            while(now->right->val < x) {
                now = now->right;
            }
            if(now->right->val == x) {
                return true;
            }
            if(i != 1) {
                now = now->down;
            }
        }
        return false;
    }
};


const int MX = 2e4;
int A[MX];


int main() {
    SkipedTable set;
    for(int i = 0; i < MX; i++) {
        A[i] = i;
    }
    random_shuffle(A, A + MX);
    for(int i = 0; i < MX; i++) {
        set.insert(A[i]);
    }
    printf("%d\n", set.height);
    return 0;
}