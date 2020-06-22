#include "sort.h"

inline void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

bool compare(int a, int b) {
    int max, min;
    compare(a, a, b, &max, &min);
    return max == b;
}

int arr[1000010];

void MergeSort(int *a,int n){
    if(n<2) return;
    if(n == 2) {
        if(!compare(a[0], a[1])) swap(a[0], a[1]);
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
    while(pivot<n){
        int num = 0;
        for(int i=0;i<4;i++)if(left[i]<right[i])num++;
        int x,y,z,Max,Min,laleftMin,laleftMid,laleftMax;
        switch(num){
            case 1:
                for(int i=0;i<4;i++)if(left[i]<right[i])x = i;
                while(left[x]<right[x])arr[pivot++] = a[left[x]++];
                break;
            case 2:
                x = y = -1;
                for(int i=0;i<4;i++)
                    if(left[i]<right[i]){
                        if(x==-1)x = i;	else y = i;
                    }
                while(left[x]<right[x]&&left[y]<right[y]){
                    if(compare(a[left[x]],a[left[y]]))
                        arr[pivot++] = a[left[x]++];
                    else
                        arr[pivot++] = a[left[y]++];
                }
                break;
            case 3:
                x = y = z = -1;
                for(int i=0;i<4;i++)
                    if(left[i]<right[i]){
                        if(x==-1) x = i; else if(y==-1) y=i;else if(z==-1) z = i;
                    }
                while(left[x]<right[x]&&left[y]<right[y]&&left[z]<right[z]){
                    compare(a[left[x]],a[left[y]],a[left[z]],&Max,&Min);
                    if(Min==a[left[x]])
                        arr[pivot++] = a[left[x]++];
                    else if(Min==a[left[y]])
                        arr[pivot++] = a[left[y]++];
                    else
                        arr[pivot++] = a[left[z]++];
                }
                break;
            case 4:
                compare(a[left[0]],a[left[1]],a[left[2]],&Max,&Min);
                if(Min == a[left[0]]) laleftMin = 0;else if(Min == a[left[1]])laleftMin = 1;else laleftMin = 2;
                if(Max == a[left[0]]) laleftMax = 0;else if(Max == a[left[1]])laleftMax = 1;else laleftMax = 2;
                laleftMid = 0+1+2-laleftMin-laleftMax;
                compare(a[left[laleftMin]],a[left[laleftMid]],a[left[3]],&Max,&Min);
                if(Min == a[left[3]])
                    laleftMax = laleftMid,laleftMid = laleftMin,laleftMin = 3;
                else if(Max == a[left[laleftMid]])
                    laleftMax = laleftMid,laleftMid = 3;
                else
                    laleftMax = 3;
                arr[pivot++] = a[left[laleftMin]++];
                while(left[0]<right[0]&&left[1]<right[1]&&left[2]<right[2]&&left[3]<right[3]){
                    compare(a[left[laleftMin]],a[left[laleftMid]],a[left[0+1+2+3-laleftMin-laleftMid-laleftMax]],&Max,&Min);
                    int newMin,newMax,newMid;
                    if(Min==a[left[laleftMin]])newMin = laleftMin;else if(Min==a[left[laleftMid]])newMin = laleftMid;else newMin = 0+1+2+3-laleftMin-laleftMid-laleftMax;
                    if(Max==a[left[laleftMin]])newMax = laleftMin;else if(Max==a[left[laleftMid]])newMax = laleftMid;else newMax = 0+1+2+3-laleftMin-laleftMid-laleftMax;
                    newMid = 0+1+2+3-laleftMax-newMin-newMax;
                    laleftMin = newMin;laleftMid = newMid;laleftMax = newMax;
                    arr[pivot++]=a[left[laleftMin]++];
                }
                break;
        }
    }
    for(int i=0;i<n;i++)
        a[i]=arr[i];
}


void sort(int n, int limit, int *a) {

    MergeSort(a,n);

}