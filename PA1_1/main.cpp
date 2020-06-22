#include <iostream>
#include <fstream>
#include <cstring>
#define MAX 5001
#define N 8
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    while(n--) {
        char a[MAX], b[MAX];
        scanf("%s %s", a, b);
        long long num1[625] = {0}, num2[625] = {0}, ans[1251] = {0};
        long long c[1251] = {0};
        int len_a = strlen(a);
        int r1 = len_a&0x07;
        int len_b = strlen(b);
        int r2 = len_b&0x07;
        int i, j, k, l;
        //开始存入num1
        for (l = len_a - N, k = 0; l >= 0; l -= N, k++) {
            i = -1;
            while (++i < N) {
                num1[k] *= 10;
                num1[k] += (a[l + i] - '0');
            }
        }
        i = -1;
        while (++i < r1) {
            num1[k] *= 10;
            num1[k] += (a[i] - '0');
        }
        if(i > 0)k++;
        len_a = k; //有这么多个数，比下标+1
        //开始存入num2
        for (l = len_b - N, k = 0; l >= 0; l -= N, k++) {
            i = -1;
            while (++i < N) {
                num2[k] *= 10;
                num2[k] += (b[l + i] - '0');
            }
        }
        i = -1;
        while (++i < r2) {
            num2[k] *= 10;
            num2[k] += (b[i] - '0');
        }
        if(i > 0)k++;
        len_b = k;
        for(i = 0; i < len_b; i++) {
            for (j = 0; j < len_a; j++) {
                c[i + j] += num2[i] * num1[j];
            }
        }
        for(k = 0; k <= i + j - 2; k++) {
            c[k + 1] += c[k] / 100000000;
        }
        for (k = 0; k <= i + j - 1; k++) {
            ans[k] = c[k] % 100000000;
        }
//        cout << ans[0] << endl;
        while(k>=0&&ans[k--] == 0);
        k++;
//        cout << "k=" << k << endl;
        printf("%lld", ans[k]);
        for (k--; k >= 0; k--) {
            printf("%08lld", ans[k]);
        }
        printf("\n");
    }
}


