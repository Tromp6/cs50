#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>




int main(int argc, string argv[]){
    if(argc != 2) {
        printf("Not cool dude");
        return 1;
    }

    string key = argv[1];
    int countK = strlen(key);

    for (int i = 0;i<countK;i++){
    if((int)key[i]>47 && (int)key[i]<58){printf("error");return 1;}}

    string plain = get_string("plaintext:");

    int countP = strlen(plain);                  // string länge

    int zählerK =0;

   for (int i = 0;i<countK;i++){
    if((int)key[i]>47 && (int)key[i]<58){return 1;}}


    /*
    function max(int i){

         if( ((int)key[i]>65 &&(int)key[i]<91) ||  ((int)key[i]>96 &&(int)key[i]<123)  ) {

             if(isupper(key[i])){

             }


             if(islower(plain[i])){}



         }

    }

    */


    printf("ciphertext:");

    for(int i =0;i<countP;i++){

        if( ((int)plain[i]>64 &&(int)plain[i]<91) ||  ((int)plain[i]>96 &&(int)plain[i]<123)  ) {    //äuere
        int add =0;
        if(islower(key[zählerK])){add=((int)key[zählerK])-97;}else if(isupper(key[zählerK])){add=((int)key[zählerK])-65;}

        if(isupper(plain[i])){

            if( (int)plain[i]+add>90 ){
                int temp = ((int)plain[i]+add)-90;
                temp = 64+temp;

                 printf("%c",temp);



            }else{
              printf("%c",(int)plain[i]+add);
            }






          zählerK++;
          if(zählerK>countK-1){zählerK=0;}
        }//isupper if

        if(islower(plain[i])){


             if( (int)plain[i]+add>122 ){
                int temp = ((int)plain[i]+add)-122;
                temp = 96+temp;

                 printf("%c",temp);



            }else{
              printf("%c",(int)plain[i]+add);
            }



         zählerK++;
         if(zählerK>countK-1){zählerK=0;}
        }//islower if

        } else {printf("%c",(int)plain[i]);}// lange if
    }//for schleife

    printf("\n");
    return 0;



}//ende der function