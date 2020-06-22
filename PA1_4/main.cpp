#include <iostream>
#include <cstring>
#define Node  ListNode<T>
using namespace std;
//列表是邓老师所教，但是不是复制的，是默写的
template<class T>
struct ListNode {
    T data;
    Node* pred;
    Node* succ;
    ListNode()=default;
    ListNode(T data, Node* pred, Node* succ):data(data),pred(pred),succ(succ){;}
    Node* insertAsPred(const T& data) {
        Node* x = new Node(data, pred, this);
        pred->succ = x;
        pred = x;
        return x;
    }
};

template<class T>
class List {
    int size;
    Node* header;
    Node* tailer;
public:
    List() {
        init();
    }
    void init() {
        size = 0;
        header = new Node;
        tailer = new Node;
        header->succ = tailer;
        tailer->pred = header;
    }
    T remove (Node* p ) {
        T e = p->data;
        p->pred->succ = p->succ; p->succ->pred = p->pred;
        delete p; size--;
        return e;
    }
    Node* insertAsLast(const T &e) {
        size++;
        return tailer->insertAsPred(e);
    }
    bool empty() {
        return !size;
    }
    Node* last() {
        return tailer->pred;
    }
    Node* first() {
        return header->succ;
    }
};

template<class T>
class Deque:public List<T> {
public:
    void push(T d) {
        this->insertAsLast(d);
    }
    T pop_back() {
        return this->remove(this->last());
    }
    T pop_front() {
        return this->remove(this->first());
    }
    T front() {
        return this->first()->data;
    }
    T back() {
        return this->last()->data;
    }
};

template<class T>
class Monoqueue{
    Deque<T> mono, ori;
public:
    void push(T d) {
        ori.push(d);
        while(!mono.empty()&&mono.back()<d) mono.pop_back();
        mono.push(d);
    }
    void pop() {
        if(ori.pop_front()==mono.front()) mono.pop_front();
    }
    T top() {
        return mono.front();
    }

};


int main() {
    freopen("/Users/quebec/Desktop/input.txt", "r", stdin);
    int N;
    scanf("%d", &N);
    N<<=1;
    Monoqueue<long long> Stock;
    char ch; //用于判断是两个输入还是一个
    long long res = 0;
    long long a[2];
    memset(a, 0, sizeof(a));
    while(N--) {
        scanf("%lld%c", &a[0], &ch);  //对于输入两个还是一个，这是章志宇同学的提示
        if(ch==' ') {  //入市
            scanf("%lld", &a[1]);
            res+=Stock.top()*a[0];
            Stock.push(a[1]);
        } else {
            res+=Stock.top()*a[0];
            Stock.pop();
        }
    }
    printf("%lld\n", res);
}