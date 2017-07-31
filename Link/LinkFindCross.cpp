#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <climits>
using namespace std;

/*给一个链表，是否末尾是环*/
struct Link {
    int val;
    Link *next;
    Link() {
        next = NULL;
    }
    Link(int v) {
        val = v;
        next = NULL;
    }
};

bool LinkFindCross(Link *link) {
    Link *a = link, *b = link;
    while(true) {
        if(a == NULL) return false;
        a = a->next;

        if(b == NULL) return false;
        b = b->next;
        if(b == NULL) return false;
        b = b->next;

        if(a == b) return true;
    }
}

void LinkPrint(Link *link) {
    while(link != NULL) {
        printf("%d, ", link->val);
        link = link->next;
    }
    printf("\n");
}
int randint(int l, int r) {
    return l + 1.0 * rand() / RAND_MAX * (r - l);
}

int main() {
    const int MAX = 20;

    Link link[MAX];
    for(int i = 0; i < 5; i++) {
        link[i].val = i;
        if(i == 4) link[i].next = &link[0];
        else link[i].next = &link[i + 1];
    }
    for(int i = 5; i <= 10; i++) {
        link[i].val = i;
        link[i].next = &link[i + 1];
    }
    link[10].next = &link[3];

    bool result = LinkFindCross(&link[7]);
    if(!result) {
        printf("the link have not cross.\n");
    } else {
        printf("ok...\n");
    }
    return 0;
}
