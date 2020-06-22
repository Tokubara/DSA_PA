#include <iostream>
#include <fstream>
using namespace std;

long long points_x[200001], points_y[200001];  //为了二分查找的时候可以不用拷贝，提高效率

inline int ToLeft(long long x, long long y, long long a, long long b) {  //要判断的是c是不是在ab左边，如果在左边就为0，否则为1（包括在右边和在线段上两种情况）
    return x*(b-y)+a*y>=0;
}

//int binary_search(long long point_x, long long point_y, int areas) {  //左闭右开   //sort默认是升序  areas表示的是区域数
//    int l = 1, r = areas-1;   //搜索范围先缩小
//    int s;
//    while(l<r) {   //这个l,r是对于points_x和points_y数组而言的
//        int mid = l + (r - l) / 2;
//        s = ToLeft(points_x[mid-1], points_y[mid-1], point_x, point_y) +
//                ToLeft(points_x[mid], points_y[mid], point_x, point_y);
//        if (s == 0) {
//            r = mid;   //mid代表的是下标，但是要的是个数
//        } else if (s == 2) {  //那就是在左
//            l = mid + 1;
//        } else {  //那就是过掉了2个
//            return mid;
//        }
//    }
//    //是不是在0区域
//    s = ToLeft(points_x[0], points_y[0], point_x, point_y);
//    if(s) return areas-1;
//    else return 0;
//}

//inline int min(int a, int b) {
//    return a<b?a:b;
//}

//按升序排列
void MergeSort(long long arr[], int len) {
    auto a = arr;
    long long *b = new long long[len];
    for(int seg = 1; seg < len; seg*=2) {
        for(int l = 0; l < len; l+=2*seg) {
            int left = l, mid = min(seg+l, len), right = min(2*seg+l, len);
            int l1 = l, r1 = mid;
            int l2 = mid, r2 = right;
            int k = left;
            while(l1<r1&&l2<r2) {
                b[k++] = a[l1]<a[l2]?a[l1++]:a[l2++];
            }
            while(l1<r1) {
                b[k++] = a[l1++];
            }
            while(l2<r2) {
                b[k++] = a[l2++];
            }
        }
        swap(a,b);
    }
    if(a != arr) {
        for(int i = 0; i < len; i++) {
            b[i] = a[i];
        }
        b = a;
    }
    delete[] b;
}


int main() {
//    ifstream cin("/Users/quebec/Desktop/input.txt");
    int n,m;
    long long a,b;   //a,b是输入的临时变量
    scanf("%d", &n);
    //如果存成points，那是对内存的浪费，存20万个0有意思么？
    // 这是存到时候要判断的点，每输入一个就处理，所以没必要存成数组，浪费内存
    for(int i = 0; i < n; i++) {
        scanf("%lld", &points_x[i]);
    }
    MergeSort(points_x, n);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &points_y[i]);
    }
    MergeSort(points_y, n);
    points_x[n] = 0;
    points_y[n] = 0;
//    cout << points_x[4];
    //现在x轴和y轴上的点处理完毕
    scanf("%d", &m);
//    cout << m;
    for(int i = 0; i < m; i++) {
        scanf("%lld %lld", &a, &b);
        //函数的主体都应该在这里完成
        int l = 1, r = n;   //搜索范围先缩小
        int s;
        while(l<r) {   //这个l,r是对于points_x和points_y数组而言的
            int mid = l + (r - l) / 2;
            s = ToLeft(points_x[mid-1], points_y[mid-1], a, b) +
                ToLeft(points_x[mid], points_y[mid], a, b);
            if (s == 0) {
                r = mid;   //mid代表的是下标，但是要的是个数
            } else if (s == 2) {  //那就是在左
                l = mid + 1;
            } else {  //那就是过掉了2个
                printf("%d\n", mid);
                goto label;
            }
        }
        //是不是在0区域
        s = ToLeft(points_x[0], points_y[0], a, b);
        if(s) printf("%d\n", n);
        else printf("0\n");
        label:;
    }
}