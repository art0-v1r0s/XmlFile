//gcc -Wall -fanalyzer -O6 -g main.c -o createFileXml
#include <mysql.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "funcMysql.c"

#define MAX_SIZE 80


int main(int argc, char *argv[])
{
    char warehouse[50];
    if(argv < 1){
        printf("Error");
        exit(EXIT_FAILURE);
    }else{
        strcpy(warehouse, argv[1]);
    }
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(con, ip, identifiant, password,bdd, 0, NULL, 0) == NULL){
        finish_with_error(con);
    }

    char filename[100]="/home/ari/Documents/entrepot/";
    time_t timestamp = time( NULL );
    struct tm * pTime = localtime( & timestamp );
    char day[ MAX_SIZE ];
    char mmaa[ MAX_SIZE ];
    strftime( day, MAX_SIZE, "%d", pTime );
    strftime( mmaa, MAX_SIZE, "%m%y", pTime );
    strcat( filename,day);
    strcat( filename,warehouse);
    strcat( filename,mmaa);
    strcat( filename,".xml");
    char  * product =  tab(con,  warehouse,filename);
    mysql_close(con);
    return 0;
}