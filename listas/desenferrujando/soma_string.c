#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    // 48 to 57
    for(int i = 0; i < n; i++) {
        int ans = 0, i = 0;
        char str[101];
        scanf(" %s", str);

        while(*(str + i) != '\0') {
            if(*(str + i) >= 48 && *(str + i) <= 57)
                ans += *(str + i) - '0';
            
            i++;
        }

        
        printf("%d\n", ans);
    }
}