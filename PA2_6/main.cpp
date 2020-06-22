#include <iostream>
#include <limits>
using namespace std;
#define MAX 1300

int arr[MAX][MAX] = {0};

int cur[MAX][MAX] = {0};


int M, N;   //M代表行数，N代表列数

int lowbit(int x) {
    return x&(-x);
}

void add(int x, int y, int dx) {
    for(int i = x; i <= M; i+=lowbit(i)) {
        for(int j = y; j <= N; j+=lowbit(j)) {
            arr[i][j]+=dx;
        }
    }
}

int query(int x, int y) {
    int ans = 0;
    for(int i = x; i > 0; i-=lowbit(i)) {
        for(int j = y; j > 0; j-=lowbit(j)) {
            ans+=arr[i][j];
        }
    }
    return ans;
}


void init(int n, int m, int** temp) {
    M = n;
    N = m;
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
            add(i, j, temp[i][j]);
            cur[i][j] = temp[i][j];
        }
    }
}

int query(int x1, int y1, int x2, int y2) {
    int area = (x2-x1+1)*(y2-y1+1);
    return (query(x2, y2) - query(x1-1, y2)-query(x2, y1-1)+query(x1-1,y1-1))/area;
}

void change(int x, int y, int temp) {
    int dx = temp - cur[x][y];
    cur[x][y] = temp;
    add(x, y, dx);
}

int main() {
    freopen("/Users/mac/Documents/input.txt","r",stdin);
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    int **a = new int *[n + 1];
    for (int i = 1; i <= n; i++) {
        a[i] = new int[m + 1];
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    }

    init(n, m, a);

    for (int i = 0; i < k; i++) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int x, y, temp;
            scanf("%d%d%d", &x, &y, &temp);
            change(x, y, temp);
        } else {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            printf("%d\n", query(x1, y1, x2, y2));
        }
    }

    cout << M << ' ' << N;
    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= N; j++) {
//            ans+=arr[i][j];
            cout << cur[i][j] << ' ';
        }
        cout << endl;
    }

    for (int i = 1; i <= n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
