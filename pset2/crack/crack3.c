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

    int c1 = 0, c2 = -1, c3= -1, c4= -1, c5= -1;
    int hacker(int m);
    char salt;

int main(int argc, string argv[]){

    if(argc<2) {
        printf("yo dude wtf????????");
        return 1;
    }


    string hashInput = argv[1];
    salt = hashInput[0];
    //atoi(hashInput[0])*10+atoi(hashInput[1]);


    //Die frage ist jetzt wie generiere ich jetzt den Key mit maximal einer for schleife und mit möglichst geringer Laufzeit

    //möglichkeiten statt for schleife selbst aufrufende Function

    //eine äußere Schleife um zu iterrieren der der wievielten Buchstaben kombination man ist

    /*

    Also die Fuction ruft sich selbst auf aber was iteriere ich in der for schleife und was in der function

    */



    //hacker(c1);

}

    int hacker(int m){

        if(m == -1) {return 0;}else{

         if ( (65 + m)> 90){
             m= m+6; //um aufs kleine Alphabet zu kommen
         }else if( (65+m)>122 ){

         }

         String RESULT =



         //crypt(w,w);


            hacker(c1);
            hacker(c2);
            hacker(c3);
            hacker(c4);
            hacker(c5);

        };



    return 1;
    }


