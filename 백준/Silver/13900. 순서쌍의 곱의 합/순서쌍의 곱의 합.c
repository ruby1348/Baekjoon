#include <stdio.h>

int main(){
    int n;
    long long sum = 0, res = 0;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        int temp;
        scanf("%d", &temp);
        res += sum * temp;
        sum += temp;
    }
    
    printf("%lld", res);
}