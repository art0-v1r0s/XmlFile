//gcc -Wall -fanalyzer -O6 -g main.c -o createFileXml
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "funcMysql.c"

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

    long nbligne = numberLigne(con, warehouse);
     //SELECT * FROM PRODUCT
    char  * product =  tab(con, nbligne, warehouse);
    mysql_close(con);
    return 0;
}