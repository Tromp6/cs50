#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE       /* See feature_test_macros(7) */
#include <unistd.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <crypt.h>


/*
crypt(key/salt)
salt is the two first characters of the hashed password

Also ich generiere random wörter verschlüssele diese und gleiche das versclüsselte mit dem verschlüsseltem Passwort
vom User wenns richtig ist nehme ich den key als Lösung also das ist dann das Passwort vom User

Das Passwort an sich ist maximal 5 Buchstaben lang kann aber auch weniger es sind aber nur Buchstaben

Aber was ist mit dem Salt wie lange ist das


*/


int main(int argc, string argv[]){

    if(argc<2) {
        printf("yo dude wtf????????");
        return 1;
    }

    char salt[3];
    string hashInput = argv[1];
    salt[0] = hashInput[0];
    salt[1] = hashInput[1];
    salt[2] = '\0';

    //atoi(hashInput[0])*10+atoi(hashInput[1]);


    //Die frage ist jetzt wie generiere ich jetzt den Key mit maximal einer for schleife und mit möglichst geringer Laufzeit

    //möglichkeiten statt for schleife selbst aufrufende Function

    //eine äußere Schleife um zu iterrieren der der wievielten Buchstaben kombination man ist

    /*

    Also die Fuction ruft sich selbst auf aber was iteriere ich in der for schleife und was in der function

    */

    int zähler1 =0,zähler2=0,zähler3=0,zähler4=0,zähler5=1;
    char result[6];


    //{"","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
    //"q", "r", "s", "t", "u", "v", "w", "x", "y", "z"}

    char alph[]= "\0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    //array of counting variables
    int count[]={0,0,0,0,0};

   while(true){



       if(zähler5>53){
           zähler4++;
           zähler5=1;

       }if(zähler4>53){
           zähler3++;
           zähler4=1;

        }if(zähler3>53){
           zähler2++;
           zähler3=1;

        }if(zähler2>53){
           zähler1++;
           zähler2=1;

        }if(zähler1>53){
           printf("Impossible");
           break;

        }
        /*

        for(int i =1;i< 5;i++){
            if(count[i]>53){
                count[i-1]++;
                count[i] = 1;

            }

        }
        if (count[0]>53){
            printf("not found");
            return 0;

        }

        result[0]=alph[count[0]];
        result[1]=alph[count[1]];
        result[2]=alph[count[2]];
        result[3]=alph[count[3]];
        result[4]=alph[count[4]];
        result[5] = '\0';
*/
        result[0]=alph[zähler5];
        result[1]=alph[zähler4];
        result[2]=alph[zähler3];
        result[3]=alph[zähler2];
        result[4]=alph[zähler1];
        result[5] = '\0';


        printf("%s",result);
        string max = crypt(result,salt);

        //also das Problem ist dass er mit von crypt nicht das richtige zurück gibt
       int r = strcmp(hashInput, crypt(result,salt));
        if (r==0){

            printf("\n");
            return 1;

        };

        zähler5++;


}//for schleife



}