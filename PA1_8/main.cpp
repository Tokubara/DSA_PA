#include <iostream>
//#include <stack>
#include <cstring>
#define MAX 100005
#define Node ListNode
using namespace std;

//template<class char>
struct ListNode {
    long long data;
    Node* pred;
    Node* succ;
    ListNode()=default;
    ListNode(long long data, Node* pred, Node* succ):data(data), pred(pred), succ(succ) {;}
    Node* insertAsPred(long long d) {
        auto x= new ListNode(d, pred, this);
        pred->succ=x;
        pred=x;
        return x;
    }
    Node* insertAsSucc(long long d) {
        auto x= new ListNode(d, this, succ);
        succ->pred=x;
        succ=x;
        return x;
    }
};

//template<class char>
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
        header = new ListNode;
        tailer = new ListNode;
        header->succ = tailer;
        tailer->pred = header;
    }
    void copyNodes(Node* p, int n) {
        init();
        while(n--) {
            header->insertAsSucc(p->data);
            p=p->succ;
        }
    }
    char remove(Node* p) {
        auto old = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p;
        size--;
        return old;
    }
    Node* insertAsFirst(const char &e) {
        size++;
        return header->insertAsSucc(e);
    }
    Node* insertAsLast(const char &e) {
        size++;
        return tailer->insertAsPred(e);
    }
    Node* insertAsPred(Node* obj, const char &e) {
        size++;
        return obj->insertAsPred(e);
    }
    Node* insertAsSucc(Node* obj, const char &e) {
        size++;
        return obj->insertAsSucc(e);
    }
    int Size() {
        return size;
    }
    Node* last() {
        return tailer->pred;
    }
};

//template<class char>
class Stack: public List {
public:
    void push(char& obj) {
        insertAsLast(obj);
    }
    char pop() {
        return remove(last());
    }
    char top() {
        return last()->data;
    }
    bool empty() {
        return !Size();
    }
};

int main() {
    freopen("/Users/quebec/Desktop/input.txt", "r", stdin);
    int T;

    scanf("%d", &T);
    char str[MAX];
    char ch;

    while(T--) {
        Stack s;
        scanf("%s", str);
//        cout << "str=" << str << endl;
//        cout << "str[7]" << str[7] << endl;
        int i = 0;
        int len = strlen(str);
        while(i<len) {
//            cout << "处理字符为：" << ch << endl;
            switch( ch=str[i++]) {
                case '(':
                case '[':
                case '{':s.push(ch);break;
                case ')':if(s.top()=='(')s.pop();else{goto label;}break;
                case ']':if(s.top()=='[')s.pop();else{goto label;}break;
                case '}':if(s.top()=='{')s.pop();else{goto label;}break;
            }
        }

        if(s.empty()) printf("Yes\n");
        else {label:
            printf("No\n");}
    }
    return 0;
}