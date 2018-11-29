#include <stdio.h>
#include <cs50.h>

int main(void) {

    float m;
    int n;

    int quarter =0;
    int dimes=0;
    int nickels=0;
    int pennies=0;


    do{
        m = get_float("Type in Change: ");
        m = m *100;
        //n = m;
        n= round(m);

     // n = int(m);
    }
    while(m<0);

    while (n!=0) {

        if ( n > 25) {quarter = n/25 + quarter;
                        n   = n%25;

        } else if (n>10 ^ n <25) {
            dimes = n/10 + dimes;
                        n   = n%10;

        } else if (n>5 ^ n< 10){
            nickels = n/5+nickels;
                        n   = n%5;

        }else if (n>1 ^ n< 5) {
             pennies = n/1+pennies;
                        n   = n%1;
        }



    }

        printf("Change: Quarters = %i Dimes = %i  Nickels = %i  Pennies = %i  ", quarter,dimes,nickels,pennies);
}