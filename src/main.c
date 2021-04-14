//gcc -Wall -fanalyzer -O6 -g main.c -o createFileXml
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "funcMysql.c"

int main(int argc, char *argv[])
{
    char data[11][255]={""};
    char balise[24][15] = {
        "<produit>","</produit>","<id-product>","</id-product>",
        "<category>","</category>","<warehouse>","</warehouse>",
        "<name>","</name>","<description>","</description>",
        "<price>","</price>","<mark>","</mark>",
        "<date_start>","</date_start>","<date_end>","</date_end>","<state>","</state>","<validate>","</validate>"
    };

    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, ip, identifiant, password,bdd, 0, NULL, 0) == NULL){
        finish_with_error(con);
    }

    long nbligne = numberLigne(con);
     //SELECT * FROM PRODUCT
    char  * product =  tab(con, nbligne);
    FILE* fichier = NULL;

    fichier = fopen("fileXml.xml", "w+");



    if (fichier != NULL)
    {
        // On lit et on écrit dans le fichier
        fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n", fichier);
        // ...
        fprintf(fichier,"%s\n",balise[0]);

        for(int i=2;i<=24;i=i+2){
            fprintf(fichier,"\t%s %s\n",balise[i],balise[i+1]);
        }

        fprintf(fichier,"%s\n",balise[1]);

        fclose(fichier); // On ferme le fichier qui a été ouvert
    }

    
    mysql_close(con);
    return 0;
}