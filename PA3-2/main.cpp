#include <iostream>
#include <limits>
//#include <bitset>
#include <cstring>
using namespace std;

const int split = 0xFF;
int pos = 0;   //读入串的长度
int ans, ans_len;

struct bitmap {
    char data[2097153];
    //不再使用数组因为没必要了，这个会应付所有情况，开到最大就好，这样初始化的事情也不用考虑了，最大开到2097153
    long long N;
    long long cases;
    void init(long long n) {
        cases = n;
        N=((cases)>>3)+1;   //这样改是为了保证，肯定是有0空出来的
        memset(data, 0, N);
    }
    void set(long long n) {
        if(test(n)) return;
        data[n>>3]|=(0x80>>(n&0x07));
    }
    bool test(long long n) {
        return data[n>>3]&(0x80>>(n&0x07));
    }
    //这个函数8个一查找，而不是逐个遍历，这是徐天行小教员的提示
    int search() {
        for(int i = 0; i < N; i++) {
            if(data[i]!=split) {
                auto bit = 0x80;
                for(int j = 0; j < 8; j++) {
                    if((data[i]&(bit))==0) {
                        //我们发现了第一个不满足的，但是可能是因为它本来就不在范围内
                        int tmp = (i<<3)+j;  //这是下标，从0开始
                        if(tmp>=cases) return -1;
                        //根本不需要什么进制转换了，这就是
                        return tmp;
                    }
                    bit>>=1;
                }
            }
        }
    }
};

bitmap str, exist;  //用位图存存在情况，是蒋林小教员的提示
//用getchar读入，是徐良钦小教员，徐天行小教员的提示
//用位图存字符串，是徐天行小教员的提示
void ReadBitString() {
    char ch = getchar();
    while(ch=='0'||ch=='1') {
        if(ch=='1') str.set(pos);
        pos++;   //这就是字串长度
        ch = getchar();
    }
}

//用位运算让写法上更漂亮，这是徐天行小教员的提示
bool judge(int len) {
    const auto all = (1<<(len-1))-1;
    exist.init(1<<len);//现在N有了合适的大小
    //先算出后len-1这么多，重复利用
    int tmp = 0;
    for(int i = 0; i < len; i++) {
        tmp<<=1;
        tmp|=str.test(i)?1:0;    //顺序不可颠倒，因为逻辑上是先继承上一次，再这一次
    }
    exist.set(tmp);
    for(int i = len; i < pos; i++) {
        tmp&=all;
        tmp<<=1;
        tmp|=str.test(i)?1:0;
        exist.set(tmp);
    }
    //现在要看是不是满了，找出第一个
    if((tmp = exist.search())!=-1) {   //-1就表示全都有了
        ans = tmp;
        ans_len = len;
        return false;   //意味不满
    }
    return true;   //意味着这个是满员的
}

//用位运算让写法上更漂亮，这是徐天行小教员的提示
void print() {  //将这个数，按01串输出
    int tmp =1<<(ans_len-1);
    for(int i = ans_len-1; i>=0; i--) {
        if((ans&tmp)!=0) putchar('1');
        else putchar('0');
        tmp>>=1;
    }
}

int main() {
//    freopen("/Users/quebec/Desktop/input.txt","r",stdin);
    ReadBitString();
    int left = 1;
    int right = min(24, pos);
    long long ans;
    int ans_len;
    //二分查找是徐天行小教员的提示
    while(left<=right) {   //双闭
        int mid = (left+right)>>1;
        if(judge(mid)) {
            //转向右边
            left = mid+1;
        } else {
            //这个是可能的，把它存起来
            right = mid - 1;
            //本来有个len很重要，但是
        }
    }
    print();
}