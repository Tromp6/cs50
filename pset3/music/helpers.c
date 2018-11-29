// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
// Fraction ist sowas wie 1/8 oder 1/4
//die funktion soll dem user übergeben wie lange die nOte geht
//wir geben die länge in 1/8 an also bei fraction 1/8 wäre es 1
// bei 1/4 wäre es 2
//erster char im string ist 1 letzte positions im string ist 8
int duration(string fraction)
{
    // TODO

    char n = fraction[0];
    int numinator = n-'0';

    char d = fraction[2];
    int denuminator = d-'0';

    int temp = 8/denuminator;
    int temp2 = temp * numinator;


    return temp2;


   // sprintf(numinator, "%i", fraction);
}

// Calculates frequency (in Hz) of a note
//Note ist sowas wie A#4
//als erstes gucken was die oktave ist und was die note is
//also die function kriegt sowas wie A4 und muss dann die frequenzy zurückgeben
int frequency(string note)
{
    const string NOTE[] = {"C", "C#", "D", "D#", "E", "F",
                        "F#", "G", "G#", "A", "A#", "B"
                       };

     char pureNote[4];


    int okt;
    //char end = '\0';




    if(strlen(note)>2){
      sprintf(pureNote, "%c%c", note[0], note[1]);
     okt = note[2]-'0';




    }else{
    sprintf(pureNote, "%c", note[0]);
    okt = note[1]-'0';
    }



    //muss noch umschreiben weil der string nich immer gleich lang ist
    //hängt ab ob da noch b oder # drin steckt

    // muss dass noch in ne IF reintun weils sein kann dass etwas eine Oktave entfernt ist
    //von 3 bis 4 aber nicht eine volle Oktave dazwischen ist
    int oktTemp = okt -4;

    //to make it positive

    int oktDiff = sqrt(oktTemp*oktTemp);


    //jetzt berechne ich die Different innherhalb der Oktabe
    //dafür brauche ich postiton der gesuchten Note
    /*
    Problem ist ich muss erst die Note umwandeln die übergeben wird im array
    finden wo die Note im Array ist
    und dann die note umwandeln

    Sagen wir ich finde die Note
    dann kann ich ja einfach i anpassen

    Ok ich kann nicht einfach nur den abstand  anpassen
    den ich prüfe ja gleich ob zah

    */
    int a =0;
    if('b'==pureNote[1]){
       sprintf(pureNote,"%c",pureNote[0]);
       a = 1;

    }



    int i;
    for(i=0;i<11;i++){
        int found = strcmp(pureNote,NOTE[i]);
        if(found==0){break;};

    }



   if(a==1){
        i=i-1;

    }




    int differenz = sqrt((9-i)*(9-i));

    /*
    Das problem ist dass die differenz nich minus 9 ist wenn die

     "A#", "B"
    "C", "C#", "D", "D#", "E", "F",
                        "F#", "G", "G#", "A", "A#", "B"
    */




    if (i<9 && okt>4){
        oktDiff=oktDiff -1;

        differenz=3+i;

    };

    if (i>9 && okt<4){
        oktDiff=oktDiff -1;

        differenz=11-i+10;

    };

    int resultDiff= oktDiff * 12 + differenz;

    // berechnung der frequenz
//problem wenn es in selber okave ist macht dass minus1 keinen sinn
    float result;

    if (okt>4 || (okt == 4 && i > 9)){
        result = 440 * pow(2.0,resultDiff/12.0);

    }else{
        result = 440 / pow(2.0,resultDiff/12.0);
    }



    result = roundf(result);
    int intResult = (int)result;

    return intResult;


}

// Determines whether a string represents a rest gucken ob da ein rest vom String ist von dem der übergeben wurde
//takes a string return a bool
//rest ist die abwesenheit einer note quasi die pause die länge (duration) ist abhängig von der form des rests
//eine blank line = 1/8 pause
//richtig runden
//also wenn note flat ist dann geteilt durch 2 hoch 1/12
//oder wenn es sharp ist dann mal 2 hoch 1/12
//erst alles in der ersten oktave machen und dann mal um zur gewüschnten oktave zu kommen
//muss kalkulieren wie weit die semitone voneinander weg sind
//oktaven beginne nbei c4
bool is_rest(string s)
{
    int test = strcmp("", s);
    if (test ==0){
        return true;
    }else{
        return false;
    }
}
