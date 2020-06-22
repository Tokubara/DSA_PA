#include <iostream>
#include <cmath>
using namespace std;



class SegmentTree {
    int* st;
    int* arr;
    int size_;   //这存的是树的最大规模
    int capacity;
    inline int mid_(int left, int right) {return left+(right-left)/2;}
    void addRecursive(int ss, int se, int si, int i, int dx) {   //i是用来确定该不该背锅的
        if(i<ss||i>se) return;
        st[si]+=dx;
        if(ss!=se) {
            auto mid = mid_(ss, se);
            addRecursive(ss, mid, 2*si+1, i, dx);
            addRecursive(mid+1, se, 2*si+2, i, dx);
        }
    }
    int construct(int ss, int se, int si) {   //当然目的不是要返回什么，而是为了这个函数本身递归实现
        if(ss==se) {
            st[si] = arr[se];
            return st[si];
        }
        auto mid = mid_(ss, se);
        st[si] = construct(ss, mid, 2*si+1) + construct(mid+1, se, 2*si+2);
        return st[si];
    }
    int sumRecursive(int ss, int se, int si, int query_x, int query_y) {
        if(ss>=query_x&&se<=query_y) {
            return st[si];
        }
        if(query_x>se||query_y<ss) return 0;
        auto mid = mid_(ss, se);
        return sumRecursive(ss, mid, 2*si+1, query_x, query_y) + sumRecursive(mid+1, se, 2*si+2, query_x, query_y);
    }

public:
    void display() {
        for(int i = 0; i < capacity; i++) {
            cout << st[i] << ' ';
        }
        cout << endl;
    }
    SegmentTree() = default;
    SegmentTree(int a[], int n) {
        arr = a;
        size_ = n;
        int x = (int)ceil(log2(n))+1;
        capacity  = pow(2,x)-1;
        st = new int[capacity];
        construct(0, size_-1, 0);
    }
    ~SegmentTree() {
        delete[](st);
    }
    void change(int i, int x) {   //x是要修改成为的值，不是差值
        addRecursive(0, size_-1, 0, i, x-arr[i]);
        arr[i] = x;
    }
    int sum(int query_x, int query_y) {
        int x =  sumRecursive(0, size_-1, 0, query_x, query_y);
        return x;
    }
};


int main() {
    int m, n;
    scanf("%d %d", &n, &m);

//    cout << n << endl;
    int ori[500001];
    for(int i = 0; i<n; i++) {
        scanf("%d", &ori[i]);
//        cout << "ori[i]=" << ori[i] << endl;
    }
    SegmentTree sg(ori, n);
    for(int i = 0; i<n; i++) {
        sg.change(i, ori[i]);
    }
    while(m--) {
        int type;
        int x, y;
        scanf("%d %d %d", &type, &x, &y);
        if(type == 0) {
            sg.change(x-1, y);
            ori[x-1]=y;
        } else {
            printf("%d\n", sg.sum(x-1, y-1));
        }
    }

}