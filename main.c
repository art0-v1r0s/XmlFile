//gcc -Wall -fanalyzer -O6 -g main.c -o createFileXml
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* fichier = NULL;

    fichier = fopen("fileXml.xml", "w+");

    char balise[32][15] = {
        "<produit>","</produit>","<id-product>","</id-product>",
        "<category>","</category>","<warehouse>","</warehouse>",
        "<name>","</name>","<description>","</description>",
        "<price>","</price>","<heigth>","</heigth>","<length>","</length>",
        "<width>","</width>","<weight>","</weight>","<mark>","</mark>",
        "<date_start>","</date_start>","<date_end>","</date_end>","<state>","</state>","<validate>","</validate>"
    };

    if (fichier != NULL)
    {
        // On lit et on écrit dans le fichier
        fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n", fichier);
        // ...
        fprintf(fichier,"%s\n",balise[0]);

        for(int i=2;i<=31;i=i+2){
            fprintf(fichier,"\t%s %s\n",balise[i],balise[i+1]);
        }



        fprintf(fichier,"%s\n",balise[1]);

        fclose(fichier); // On ferme le fichier qui a été ouvert
    }

    return 0;
}