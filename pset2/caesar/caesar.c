#include <stdio.h>
#include <string.h>
#include <cs50.h>





int main(int argc, string argv[]){
    if(argc != 2) {
        printf("Not cool dude type in just one positive Integer");
        return 1;
    }

    int k = atoi(argv[1]);
    if (k<0){
        return 1;
    }



    string plain = get_string("plaintext:");
    int count = strlen(plain);



    printf("ciphertext:");

    for(int i = 0;i<count;i++){
         int t = k%26;
        if(64<(int)plain[i] && 91 > (int)plain[i]  ){



            if((int)plain[i]+t>90){

                int bla = ((int)plain[i]+t)-90;
                int er = 64+bla;

// w

           printf("%c", er);


        }else{printf("%c",(int)plain[i]+t);}}

         int test2 = (int)plain[i];
   if(96<(int)plain[i] && 123 > (int)plain[i]){
       int test = (int)plain[i];
       if((int)plain[i]+t>122){
            int u = k%26;


               int bl = ((int)plain[i]+t)-90;
                int re = 64+bl;


           printf("%c", re);


       }else{printf("%c",(int)plain[i]+t);

       }





}

if(( 90 < (int)plain[i] && 97> (int)plain[i]) || (65>(int)plain[i] || (int)plain[i] > 122) ) {
    printf("%c",(int)plain[i]);

}
}
printf("\n");
return 0;
}
