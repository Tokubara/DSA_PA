//#include "kth.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

static int *a;
static int *b;
static int *c;
static int n;


int compare(int x, int y, int z, int u, int v, int w) {
    if (x < 1 || x > n || y < 1 || y > n || z < 1 || z > n) {
        printf("不在范围1\n");
        puts("Wrong Answer --- invalid parameters");
        exit(0);
    }
    if (u < 1 || u > n || v < 1 || v > n || w < 1 || w > n) {
        printf("不在范围2\n");
        puts("Wrong Answer --- invalid parameters");
        exit(0);
    }
    return a[x] + b[y] + c[z] < a[u] + b[v] + c[w];
}

int compare_a(const void* a, const void* b) {
    if(compare((*(int*)a),1,1,(*(int*)b),1,1)) return -1;
    return 1;
}

int compare_b(const void* a, const void* b) {
    if(compare(1,(*(int*)a),1,1,(*(int*)b),1)) return -1;
    return 1;
}

int compare_c(const void* a, const void* b) {
    if(compare(1,1,(*(int*)a),1,1,(*(int*)b))) return -1;
    return 1;
}

int assist_a[5000001];
int assist_b[5000001];
int assist_c[5000001];

struct node {
    int x, y, z;
    bool operator<(const node& ano) {
        return (bool)compare(assist_a[x],assist_b[y],assist_c[z],assist_a[ano.x],assist_b[ano.y],assist_c[ano.z]);
    }
    node(int x, int y, int z) : x(x), y(y), z(z) {;}
    node()=default;
};

node nodes[6100000];

class Heap {

    int len = 0;
public:
    void push(node b) {
        nodes[++len] = b;
        int son = len;
        int tmp;
        while(son>>1>=1&&(nodes[son]<nodes[(tmp=son>>1)])) {
            swap(nodes[tmp], nodes[son]);
            son = tmp;
        }
    }
    node pop() {
        auto ans = nodes[1];
        nodes[1]=nodes[len];
        len--;
        int parent = 1, son;
        bool stop = false;
        while((parent<<1<=len)&&(!stop)) {
            son = ((parent<<1|1)>len||nodes[parent<<1]<nodes[parent<<1|1])?parent<<1:parent<<1|1;
            if(nodes[son]<nodes[parent]) {
                swap(nodes[parent], nodes[son]);
                parent=son;
            } else {
                stop= true;
            }
        }
        return ans;
    }
    node top() {
        return nodes[1];
    }
};

void get_kth(int n, int k, int *x, int *y, int *z) {
    for(int i = 1; i <= n; i++) {
        assist_a[i]=i;
    }

    qsort(assist_a+1, n, 4, compare_a);
    for(int i = 1; i <= n; i++) {
        cout << assist_a[i] << ' ';
    }
    cout << endl;
    for(int i = 1; i <= n; i++) {
        assist_b[i]=i;
    }
    qsort(assist_b+1, n, 4, compare_b);
    for(int i = 1; i <= n; i++) {
        cout << assist_b[i] << ' ';
    }
    cout << endl;
    for(int i = 1; i <= n; i++) {
        assist_c[i]=i;
    }
    qsort(assist_c+1, n, 4, compare_c);
    for(int i = 1; i <= n; i++) {
        cout << assist_c[i] << ' ';
    }
    cout << endl;
//    printf("一切很好\n");
    Heap h;
    printf("n=%d\n", n);
    h.push(node(1,1,1));
    node tmp2;  //存上一次弹出的
    while(k>0) {
        tmp2=h.pop();
//        printf("tmp2.x=%d,tmp2.y=%d,tmp2.z=%d\n", tmp2.x,tmp2.y,tmp2.z);
        k--;
        if(tmp2.x==1&&tmp2.y==1) {
            if((tmp2.x+1)<=n) h.push(node(tmp2.x+1,tmp2.y,tmp2.z));
            if((tmp2.y+1)<=n) h.push(node(tmp2.x,tmp2.y+1,tmp2.z));
            if((tmp2.z+1)<=n) h.push(node(tmp2.x,tmp2.y,tmp2.z+1));
        } else if(tmp2.x==1) {
            if((tmp2.x+1)<=n) h.push(node(tmp2.x+1,tmp2.y,tmp2.z));
            if((tmp2.y+1)<=n) h.push(node(tmp2.x,tmp2.y+1,tmp2.z));
        } else {
            if((tmp2.x+1)<=n) h.push(node(tmp2.x+1,tmp2.y,tmp2.z));
        }
    }
    *x=assist_a[tmp2.x];
    *y=assist_b[tmp2.y];
    *z=assist_c[tmp2.z];
}

int main() {
    freopen("/Users/quebec/Desktop/input.txt", "r", stdin);
    int n, k;
    scanf("%d%d", &n, &k);
    ::n = n;

    a = new int[n + 1];
    b = new int[n + 1];
    c = new int[n + 1];

    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", b + i);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i);
    }

    int x = -1, y = -1, z = -1;
//    printf("一切很好\n");
    get_kth(n, k, &x, &y, &z);
//    printf("一切很好\n");
    if (x < 1 || x > n || y < 1 || y > n || z < 1 || z > n) {
        puts("Wrong Answer --- invalid answer");
        return 0;
    }

    printf("%d\n", a[x] + b[y] + c[z]);
}
