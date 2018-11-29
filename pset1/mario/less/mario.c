#include <stdio.h>
#include <cs50.h>
int main(void){
    int n;

    do{
        n = get_int("positiven Integer eingeben: ");
     }
    while(n<0 || n > 23);

    for (int i =0;i<n;i++) {

        for (int u = 0;u<=i;u++){
            printf("#");
        }
      printf("\n");
    }

}
