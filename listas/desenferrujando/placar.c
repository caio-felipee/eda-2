#include <stdio.h>
#include <string.h>

int main() {
    int t = 0, n;
    while(scanf(" %d", &n) != EOF) {
        int grade = 100, tgrade;
        char name[21], tname[21];

        for(int i = 0; i < n; i++) {
            scanf(" %s %d", tname, &tgrade);

            if(tgrade < grade) {
                grade = tgrade;
                strcpy(name, tname);
            }
            else if(grade == tgrade) {
                int i = 0;
                while(tname[i] == name[i] && name[i] != 0 && tname[i] != 0) {
                    i++;
                }

                if(name[i] <= tname[i]) {
                    grade = tgrade;
                    strcpy(name, tname);
                }
            }
        }

        printf("Instancia %d\n", ++t);
        printf("%s\n", name);
    }
}