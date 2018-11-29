#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    //Make sure that I have one command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Enter Image\n");
        return 1;
    }


    FILE *inpointer = fopen(argv[1], "r");

    //If the file does not exist, throw an error
    if (inpointer == NULL)
    {
        fprintf(stderr, "Couldnt open the Image.\n");
        return 2;
    }



   unsigned char buffer[512];
   FILE *jpegFile = NULL;

   char filename[6];
   int i =0;
   bool marker = false;

   while(fread(buffer, 512, 1, inpointer)==1){

//ok ein fehler ist hier dass dass ich zwar diesen einen block einlese aber zu einem jpeg file
//gehören mehrere blöcke und ers wenn jeder block eingespeichert wurde darf ich das alte closen
   if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0)==0xe0){
        sprintf(filename,"%03i.jpg",i);
        jpegFile = fopen(filename,"w");
        marker = true;
        i++;
   }//end if
    if(marker)  {

        fwrite(buffer,512,1,jpegFile);

      }//if marker


   }//ende der while




    fclose(jpegFile);
    fclose(inpointer);
    return 0;






}