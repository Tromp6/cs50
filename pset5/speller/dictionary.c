// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#include "dictionary.h"

//writing stuff outside the scope (functions) makes it global

int wordCounter =0;
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
node;
node* array[50];
//https://codereview.stackexchange.com/questions/85556/simple-string-hashing-algorithm-implementation
static size_t hash(const char* source)
{
    size_t length = strlen(source);
    size_t hash = 0;
    for(size_t i = 0; i < length; i++) {
        char c = source[i];
        int a = c - '0';
        hash = (hash * 10) + a;
    }

    return hash;
}

// Returns true if word is in dictionary else false
bool check(const char *wordCheck)
{

    int mm = strlen(wordCheck);
        char test[LENGTH+1];
      //  int tt = strlen(test);
        for(int i = 0;i< mm; i++){
        test[i] = tolower(*wordCheck);
        wordCheck++;
        }
        test[mm]='\0';

    int index =(int) hash(test);
    index = abs(index);
    index = index%50;

    node* cursor = array[index];
//hab das problem das er nicht das ganze hashen soll
  // const char* del = wordCheck;
    while(cursor != NULL){


//I cant copy with = one string to another cause string are here pointers
//strcpy takes to pointer and follows them and iterate trough the memory

//??? Ok wieso kann ich keine flexibele array lengths machen aber den wert einer return function dazu benutzen


       // printf("--wordcheck:%s______test:%s   ---Länge von test=%i---- Länge von mm=%i----",del,test,tt,mm);
        if(strcmp(cursor->word,test)==0){
            return true;
        }else{
        cursor = cursor->next;
        }
    }
/*
ok meine load function geht also korrekt aber meine check function nicht
*/
    // TODO
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

if(dictionary==NULL){
        return false;
    }
//aus irgendeinem grund wird einfach das wort dictionary in dictonary geladen




//array = pointer


    char word2[LENGTH+1];
    //warum geht das hier !!!!!!!!!!!!!!!!!!!!!!!
    //strlen nimmt die adresse
     FILE *outptr = fopen(dictionary, "r");
// du hättest dir auch die schleifen sparen können strlen gibt dir das richtige ende zurück weil es bei der 0
// terminierung aufhört mein ganzer ansatz geht aber in die hose sollte die fscanf function kein /0 ranhängen

     while(fscanf(outptr,"%s",word2)!=EOF){
     int i =0;

     int o =0;
     while(o<46){
         if(word2[o]=='\0')
         {
            /* char word[i];

              */
                 break;
             }
            i++;
            o++;
         }

       //ok warum kann ich wenn ich word declariere keine variable als länge reintun aber einzelne zahlen
       //ok vlt weil i noch durch die schleife entsteht und der compiler das vlt vorher wissen muss

       //warum geht das ich bekomme hier ne adresse zurück char* word = malloc
       //ok weiß es jetzt der stern bei word ist quasi einfach nur der datensatz es bedeutet nicht dasselbe wie *word

       char* word3=NULL;
       word3 = malloc(sizeof(char)*(i+1));

       char* word=NULL;
       word = malloc(sizeof(char)*(i+1));
//also in word3 ist jetzt quasi der gekürzte string drin von word2 um memory zu sparen
       strncpy(word3,word2,i);
       //diesen pointer mach ich um am ende von word3 die terminerung \0 ran zu machen
       char* pointer = word3;
       pointer +=i;
       *pointer = '\0';
       //temp2 is da um den verkleinerten buchstaben dem normalen word zuzuweisen
       //ich kann bei, word nicht mit [] durch iterieren weils kein normaler array ist
       char* temp2 = NULL;
       temp2=word;

       char* toDelete = word3;

        for(int p = 0;p< i+1; p++){
            //vergiss nicht den Stern auf die richtige Seite zusetzen word* ging nicht
        *temp2 = tolower(*word3);
        temp2++;
        word3++;


        }












      int hasher = hash(word);
      hasher = abs(hasher);
      int index = hasher%50;

      node* temp = malloc(sizeof(node));

      temp->next=array[index];
      array[index] = temp;

      strcpy(temp->word,word);


      free(word);
      free(toDelete);



    wordCounter++;

     }

      //problem muss array noch derefferencen und den ort wo der array am anfang hinzeigt zu NULL machen

        //frage wo ist die adresse des struct im pointer gespeichert bei in y* weiß man das in y die adresse ist
     /* Das Problem ist wenn jetzt ein neuer node hinzugefügt wird dann muss ich den node aus dem array
     auf den neuen node zeigen und denn neuen node auf den alten node
     mit dem neuen node mach ich das so neuer node zeigt aufsselbe wie arraynode

     */


    //ende der for
    fclose(outptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for(int i=0;i<50;i++){
    node *cursor = array[i];
    while(cursor != NULL){
        node *temp=cursor;
        cursor = cursor->next;
        free(temp);
    }

    }
    return true;
}
