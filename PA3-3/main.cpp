#include <iostream>
#include <cstdio>
#include "crc.h"
#include <cstring>
#include <cmath>
using namespace std;

int head;   //弱口令的位置
char weak[7];
const char ch[] = "0123456789tsinghua";

struct hashNode {
    unsigned int key;
    int value = -1;   //-1未插入，-2重复
};

class HashTable {
public:
    hashNode nodes[10000019];
    const int capacity = 10000019;
    int hash(unsigned int key) {
        return key%capacity;
    }
    void insert(unsigned int key, int value) {
        auto h = hash(key);
        while(nodes[h].value!=-1&&nodes[h].key!=key) {
            h++;
            h%=capacity;
        }
        if(nodes[h].value==-1) {
            nodes[h].key = key;
            nodes[h].value = value;
        } else {
            nodes[h].value = -2;
        }
    }
    int search(unsigned int key) {
        auto h = hash(key);
        while(nodes[h].value!=-1) {
            if(nodes[h].key==key) {
                    return nodes[h].value;
                }
                h++;
                h%=capacity;
        }
        return -1;  //表示没搜到
    }
};

HashTable ht;

void NumToPassword(char* password, int n) {   //修改传过来的password
    password[0] = ch[n%19-1];
    weak[head]=password[0];
    head=(head+1)%7;
    n/=19;
    int i = 1;
    while(n>0) {
        password[i] =  ch[n%19-1];
        n/=19;
        i++;
    }
    password[i]='\0';
}

//用数来存密码以减少空间和时间，这是蒋林小教员的提示
//函数效率上的提高，具体来说是不再调用pow函数，尽量少地进行乘法，这是姚洋的提示
int PasswordToNum(const char* password, int len) {   //只有在成功搜索到才会调用
    int ans = 0;
    int tmp = 1;
    for(int i = 0; i < len; i++) {
        if(isdigit(password[i])) {
            ans+=(password[i]-'0'+1)*tmp;
        } else {
            switch(password[i]) {
                case 't':ans+=11*tmp;break;
                case 's':ans+=12*tmp;break;
                case 'i':ans+=13*tmp;break;
                case 'n':ans+=14*tmp;break;
                case 'g':ans+=15*tmp;break;
                case 'h':ans+=16*tmp;break;
                case 'u':ans+=17*tmp;break;
                case 'a':ans+=18*tmp;break;
            }
        }
        tmp*=19;
    }
    return ans;
}

void getAllPassword(char* salt) {
    //对于长度为1
    int len = strlen(salt);
    for(int i = 0; i < 18; i++) {
        char password[10];
        password[0]=ch[i];
        strcpy(password+1,salt);
        ht.insert(crc32((unsigned char*)password, len+1), PasswordToNum(password,1));
    }
    for(int i = 0; i <18; i++) {
        char password[10];
        password[0] = ch[i];
        for(int j = 0; j < 18; j++) {
            password[1] = ch[j];
            strcpy(password+2,salt);
            ht.insert(crc32((unsigned char*)password, len+2), PasswordToNum(password,2));
        }
    }
    for(int i = 0; i <18; i++) {
        char password[10];
        password[0] = ch[i];
        for(int j = 0; j < 18; j++) {
            password[1] = ch[j];
            for(int k = 0; k <18; k++) {
                password[2] = ch[k];
                strcpy(password+3,salt);
                ht.insert(crc32((unsigned char*)password, len+3), PasswordToNum(password,3));
            }
        }
    }
    for(int i = 0; i <18; i++) {
        char password[10];
        password[0] = ch[i];
        for(int j = 0; j < 18; j++) {
            password[1] = ch[j];
            for(int k = 0; k <18; k++) {
                password[2] = ch[k];
                for(int l = 0; l < 18; l++) {
                    password[3] = ch[l];
                    strcpy(password+4,salt);
                    ht.insert(crc32((unsigned char*)password, len+4), PasswordToNum(password,4));
                }
            }
        }
    }
    for(int i = 0; i <18; i++) {
        char password[11];
        password[0] = ch[i];
        for(int j = 0; j < 18; j++) {
            password[1] = ch[j];
            for(int k = 0; k <18; k++) {
                password[2] = ch[k];
                for(int l = 0; l < 18; l++) {
                    password[3] = ch[l];
                    for(int m = 0; m < 18; m++) {
                        password[4] = ch[m];
                        strcpy(password+5,salt);
                        ht.insert(crc32((unsigned char*)password, len+5), PasswordToNum(password,5));
                    }
                }
            }
        }
    }

}

//弱口令简单地用一个长度为7的数组，循环的思想是姚洋的提示
int main(){//哈希表的和插入,用线性探索法解决冲突
//    freopen("/Users/quebec/Desktop/input.txt","r",stdin);
    int n;
    scanf("%d", &n);
    char salt[6];
    scanf("%s", salt);
    //先得到所有的密码
    auto salt_len = strlen(salt);
    getAllPassword(salt);
    while(n--) {
        int x;
        unsigned int y;
        scanf("%d", &x);
        if(x==0) {
            char password[8];
                scanf("%u", &y);
            int tmp = ht.search(y);
            switch(tmp) {
                case -1:printf("No\n"); break;
                case -2:printf("duplicate\n"); break;
                default:NumToPassword(password, ht.search(y));printf("%s\n", password);
            }
        } else {
            char password[13];
            strcpy(password+7, salt);
            for(int i = 0; i < 7; i++) {
                password[i]=weak[head];
                head=(head+1)%7;
            }
            strcpy(password+7, salt);
            ht.insert(crc32((unsigned char*)password, 7+salt_len), PasswordToNum(password,7));
        }
    }
}