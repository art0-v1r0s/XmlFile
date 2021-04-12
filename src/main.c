//gcc -Wall -fanalyzer -O6 -g main.c -o createFileXml
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>

#define ip "localhost"
#define identifiant "ari"
#define password "ari"
#define bdd "predfackers"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

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

    if (mysql_query(con, "SELECT * FROM PRODUCT"))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for(int i = 0; i < num_fields; i++)
        {
            //printf("%s ", row[i] ? row[i] : "NULL");
            data[i]=row[i] ? row[i] : "NULL";

        }

        printf("\n");
    }

    for (int i = 0; i < 11; i++)
    {
        printf("%s",data[i]);
    }
    

    

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

    mysql_free_result(result);
    mysql_close(con);

    return 0;
}