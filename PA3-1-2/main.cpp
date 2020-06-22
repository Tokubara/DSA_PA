#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int infinity = -1000000001;

//关于用线段树维护区间最大连续和，参考了https://blog.csdn.net/wu_tongtong/article/details/73385029
//其实这道题我并没有思考太多，所做的事主要是把博客看懂，省去了没有必要维护的量sum和ans_l，不过我保证我是完全理解后记忆下之后自己写的


struct Node {
    int max_s, max_ls, max_rs, sum;
    int left, right;
    Node(int d, int l, int r) {
        max_s = d;
        max_ls = d;
        max_rs = d;
        sum = d;
        left = l;
        right = r;
    }
    Node()= default;
};

Node nodes[1048576];
int arr[500001];

void refresh(int x) {
    nodes[x].sum = nodes[x<<1].sum + nodes[x<<1|1].sum;
    nodes[x].max_ls = max(nodes[x<<1].max_ls, nodes[x<<1].sum + nodes[x<<1|1].max_ls);
    nodes[x].max_rs = max(nodes[x<<1|1].max_rs, nodes[x<<1|1].sum + nodes[x<<1].max_rs);
    nodes[x].max_s = max(nodes[x<<1].max_s, nodes[x<<1|1].max_s);
    nodes[x].max_s = max(nodes[x].max_s, nodes[x<<1].max_rs+nodes[x<<1|1].max_ls);
}

void build(int rank, int left, int right) {
    nodes[rank].left = left;
    nodes[rank].right = right;
    if(left==right) {
        nodes[rank] = Node(arr[left], left, right);
        return;
    }
    int mid = (left+right)>>1;
    build(rank<<1, left, mid);
    build(rank<<1|1, mid+1, right);
    refresh(rank);
}

void update(int rank, int pos, int new_v) {
    //这里应该有两种写法都试一下
    int left = nodes[rank].left;
    int right = nodes[rank].right;
    if(left==right) {
        nodes[rank]=Node(new_v, left, right);
        return;
    }
    int mid = (left+right)>>1;
    if(pos<=mid) update(rank<<1, pos, new_v);
    else update(rank<<1|1, pos, new_v);
    refresh(rank);
}

void query(int rank, int query_x, int query_y, int& max_r, int& max_range) {
    int left = nodes[rank].left;
    int right = nodes[rank].right;
    if(left>query_y||right<query_x) return;
    if(left>=query_x&&right<=query_y) {
        max_range = max(max_range, nodes[rank].max_s);
        max_range = max(max_range, max_r+nodes[rank].max_ls);
        max_r = max(max_r+nodes[rank].sum, nodes[rank].max_rs);
        max_range = max(max_range, max_r);
        return;
    }
    query(rank<<1, query_x, query_y, max_r, max_range);
    query(rank<<1|1, query_x, query_y, max_r, max_range);
}



int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    build(1, 1, n);
    while(m--) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if(x==0) {
            update(1, y, z);
        } else {
            int ans = infinity;
            int sum = 0;
            int max_r = infinity;
            query(1, y, z, max_r, ans);
            if(ans<0) ans=0;
            printf("%d\n", ans);
        }
    }
}