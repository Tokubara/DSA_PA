#include <iostream>
using namespace std;

int A[] = {9,3,2,7,10,4,6,0,1,8,5};

inline void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void compare(int a, int b, int c, int *max, int *min) {
    if(A[a]>=A[b]&&A[a]>=A[c]&&A[b]>=A[c]) {
        *max = a;
        *min = c;
        return;
    }
    if(A[a]>=A[b]&&A[a]>=A[c]&&A[c]>=A[b]) {
        *max = a;
        *min = b;
        return;
    }
    if(A[b]>=A[a]&&A[b]>=A[c]&&A[a]>=A[c]) {
        *max = b;
        *min = c;
        return;
    }
    if(A[b]>=A[a]&&A[b]>=A[c]&&A[c]>=A[a]) {
        *max = b;
        *min = a;
        return;
    }
    if(A[c]>=A[a]&&A[c]>=A[b]&&A[a]>=A[b]) {
        *max = c;
        *min = b;
        return;
    }
    if(A[c]>=A[a]&&A[c]>=A[b]&&A[b]>=A[a]) {
        *max = c;
        *min = a;
        return;
    }
}

bool less_than(int a, int b) {
    int max, min;
    compare(a, a, b, &max, &min);
    return max == b;
}

int arr[1000010];

void MergeSort(int a[], int n) {
    if(n<2) return;
    if(n == 2) {
        if(!less_than(a[0], a[1])) swap(a[0], a[1]);
        return;
    }
    int max, min;
    if(n == 3) {
        compare(a[0], a[1], a[2], &max, &min);
        a[1] = a[0] + a[1] + a[2] - max - min;
        a[0] = min;
        a[2] = max;
        return;
    }
    int tmp = n>>2;
    int len[4] = {tmp, tmp, tmp, tmp};
    tmp = n%4;
    for(int i = 0; i < tmp; i++) {
        len[i]++;
    }
    //len补完了
    int left[4] = {0, len[0], len[0]+len[1], len[0]+len[1]+len[2]};
    int right[4] = {left[1], left[2], left[3], n};
    //区间初始化完毕
    //递归使这四段分别有序
    for(int i = 0; i < 4; i++) {
        MergeSort(a+left[i], len[i]);
    }
    int num;
    int pivot = 0;  //这就是要存左边的指标了
    while(pivot<n) {
        int mi;  //这个后面再用，在四路情况中保存最小的
        int deal[4] = {-1,-1,-1,-1};
        //首先需要统计是作几路归并
        num = 0;
        for(int i = 0; i < 4; i++) {
            if(left[i]!=right[i]) num++;
        }
        //先搞清楚是谁
        switch(num) {
            case 1:{
                for(int i = 0; i < 4; i++) {
                    if(left[i]!=right[i]) {
                        deal[0] = i;
                        break;
                    }
                }
                while(left[deal[0]]<right[deal[0]]) {
                    arr[pivot++] = a[left[deal[0]]++];
                }
                break;
            }
            case 2:{
                for(int i = 0; i < 4; i++) {
                    if(left[i]!=right[i]) {
                        (deal[0]==-1?deal[0]:deal[1]) = i;
                    }
                }
                //这就是普通的二路归并
                while(left[deal[0]]<right[deal[0]]&&left[deal[1]]<right[deal[1]]) {
                    arr[pivot++]=(less_than(a[left[deal[0]]], a[left[deal[1]]])?a[left[deal[0]]++]:a[left[deal[1]]++]);
                }
                break;
                //但是我们不需要再做下一步了，因为while会解决
            }
            case 3:{
                for(int i = 0; i < 4; i++) {
                    if(left[i]!=right[i]) {
                        (deal[0]==-1?deal[0]:(deal[1]==-1?deal[1]:deal[2])) = i;
                    }
                }
                while(left[deal[0]]<right[deal[0]]&&left[deal[1]]<right[deal[1]]&&left[deal[2]]<right[deal[2]]) {
                    compare(a[left[deal[0]]], a[left[deal[1]]], a[left[deal[2]]], &max, &min);
                    arr[pivot++]=(min==a[left[deal[0]]]?a[left[deal[0]]++]:(min==a[left[deal[1]]]?a[left[deal[1]]++]:a[left[deal[2]]++]));
                }
                break;
            }
            case 4:{
                //这一段可以直接用case3的
                for(int i = 0; i < 3; i++) {
                    if(left[i]!=right[i]) {
                        (deal[0]==-1?deal[0]:(deal[1]==-1?deal[1]:deal[2])) = i;
                    }
                }
                deal[3] = 6-deal[0]-deal[1]-deal[2];
                compare(a[left[deal[0]]], a[left[deal[1]]], a[left[deal[2]]], &max, &min);
                //tmp存最大的那个
                tmp = (a[left[deal[0]]]==max?0:(a[left[deal[1]]]==max?1:2));
                while(left[deal[0]]<right[deal[0]]&&left[deal[1]]<right[deal[1]]&&left[deal[2]]<right[deal[2]]&&left[deal[3]]<right[deal[3]]) {
                    switch(tmp) {   //这里面存的是谁是max，max是不用参加比较的
                        //下面四个其实代码基本都一样，就是改了下数
                        case 0:{
                            compare(a[left[deal[1]]], a[left[deal[2]]], a[left[deal[3]]], &max, &min);
                            mi = (a[left[deal[1]]]==min?1:(a[left[deal[2]]]==min?2:3));
                            tmp = (a[left[deal[1]]]==max?1:(a[left[deal[2]]]==max?2:3));
                            arr[pivot++] = a[left[deal[mi]]++];
                            break;
                        }
                        case 1:{
                            compare(a[left[deal[0]]], a[left[deal[2]]], a[left[deal[3]]], &max, &min);
                            mi = (a[left[deal[0]]]==min?0:(a[left[deal[2]]]==min?2:3));
                            tmp = (a[left[deal[0]]]==max?0:(a[left[deal[2]]]==max?2:3));
                            arr[pivot++] = a[left[deal[mi]]++];
                            break;
                        }
                        case 2:{
                            compare(a[left[deal[0]]], a[left[deal[1]]], a[left[deal[3]]], &max, &min);
                            mi = (a[left[deal[0]]]==min?0:(a[left[deal[1]]]==min?1:3));
                            tmp = (a[left[deal[0]]]==max?0:(a[left[deal[1]]]==max?1:3));
                            arr[pivot++] = a[left[deal[mi]]++];
                            break;
                        }
                        case 3:{
                            compare(a[left[deal[0]]], a[left[deal[1]]], a[left[deal[2]]], &max, &min);
                            mi = (a[left[deal[0]]]==min?0:(a[left[deal[1]]]==min?1:2));
                            tmp = (a[left[deal[0]]]==max?0:(a[left[deal[1]]]==max?1:2));
                            arr[pivot++] = a[left[deal[mi]]++];
                            break;
                        }
                    }
                }
            }
        }
    }
    //最后拷贝到a
    for(int i = 0; i < n; i++) {
        a[i] = arr[i];
    }
}

void sort(int n, int limit, int *a) {
    MergeSort(a, n);
}

int main() {
     int res[] = {0,1,2,3,4,5,6,7,8,9,10};
     sort(11,10000, res);
     for(int i = 0; i < 5; i++) {
         if(A[res[i]]!=i) {
             cout << "wrong";
             return 0;
         }
     }
     cout << "right";
}