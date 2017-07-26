#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <climits>
using namespace std;

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

Link *LinkMerge(Link *linka, Link *linkb) {
    Link *link;
    if(linka->val < linkb->val) {
        link = linka; linka = linka->next;
    } else {
        link = linkb; linkb = linkb->next;
    }
    Link *link_begin = link;

    while(linka != NULL || linkb != NULL) {
        bool use_a;
        if(linka == NULL) use_a = false;
        else if(linkb == NULL) use_a = true;
        else {
            if(linka->val < linkb->val) use_a = true;
            else use_a = false;
        }

        if(use_a) {
            link->next = linka;
            linka = linka->next;
            link = link->next;
        } else {
            link->next = linkb;
            linkb = linkb->next;
            link = link->next;
        }
    }
    return link_begin;
}
Link *LinkSort(Link *link) {
    int len = 0;
    Link *link_new, *temp = link;
    for(; temp != NULL; temp = temp->next) len++;
    if(len <= 1) return link;

    temp = link;

    int mid = len >> 1;
    for(int i = 1; i < mid; i++) temp = temp->next;
    link_new = temp->next;
    temp->next = NULL;

    link = LinkSort(link);
    link_new = LinkSort(link_new);
    return LinkMerge(link, link_new);
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
    srand(time(NULL));
    const int MAX = 20;

    Link link[MAX];
    for(int i = MAX - 1; i >= 0; i--) {
        link[i].val = randint(1, 100);
        if(i + 1 < MAX) {
            link[i].next = &link[i + 1];
        }
    }

    Link *link_ptr = &link[0];
    LinkPrint(link_ptr);

    link_ptr = LinkSort(link_ptr);
    LinkPrint(link_ptr);
    return 0;
}
