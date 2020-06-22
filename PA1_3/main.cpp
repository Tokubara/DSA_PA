#include <iostream>
#include <fstream>
#define MAX 501001
#define M 101
using namespace std;

unsigned char f[MAX][202];


int main() {
//    ifstream cin("/Users/quebec/Desktop/input.txt");
    char a[MAX], b[MAX];
    int len_a, len_b, limit, start, end;
    //名义上的读入
    scanf("%d %d %d", &len_a, &len_b, &limit);
    scanf("%s %s", a, b);
    //实际上
//    cin >> len_a >> len_b >> limit;
//    cin >> a >> b;
//    cin >> a >> b >> limit;
//    len_a = strlen(a);
//    len_b = strlen(b);
    //初始化
    //f[0][j]实际上对应b的前j-limit个字符

    for(int i = 0; i <= len_a; i++) {
        start = max(0, limit+1-i);
        end = min(2*limit, limit+len_b-i);
        for(int j = 0; j < start; j++) {
            f[i][j] = M;
        }
        for(int j = end+1; j <= end+10; j++) {
            f[i][j] = M;
        }
    }
    for(int j = 0; j <= 2*limit; j++) {
        f[0][j] = j-limit;
    }
    for(int i = 0; i <= len_a; i++) {
        f[i][limit-i] = i;  //这个对应b为空串的情况
    }
//    cout << "f[1][4]=" << f[1][4] << endl;
    for(int i = 1; i <= len_a; i++) {   //a的前i个
        start = max(0, limit+1-i);
        end = min(2*limit, limit+len_b-i);
//        printf("========start=%d ,end=%d=======\n", start, end);
        for(int j = start; j <= end; j++) {  //b的前i+j-limit个
//            printf("小循环：i+j-limit=%d\n", i+j-limit);
            if(a[i-1]==b[i+j-limit-1]) {
                f[i][j] = f[i-1][j];
//                printf("case1:f[%d][%d]=%d, f[%d][%d]=%d\n", i-1, j, f[i-1][j], i, j, f[i][j]);
            } else {
//                if(j+1>end) f[i-1][j+1]=M;
//                if(j-1<start) f[i][j-1]=M;
                f[i][j] = 1+min(f[i-1][j+1], f[i][j-1]);
//                printf("case2:f[%d][%d]=%d, f[%d][%d]=%d, f[%d][%d]=%d\n", i-1, j+1, f[i-1][j+1], i, j-1, f[i][j-1], i, j, f[i][j]);
            }
        }
    }
//    cout << "f[1][4]=" << f[1][4] << endl;
//    printf("%d\n", f[len_a-1][len_b-len_a+limit+1]);
//    printf("%d\n", f[len_a][len_b-len_a+limit]);
//    cin.close();
    if(f[len_a][len_b+limit-len_a]<=limit)
        printf("%d", f[len_a][len_b+limit-len_a]);
    else {
        printf("-1");
    }
}
