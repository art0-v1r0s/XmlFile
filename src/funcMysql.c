
#define ip "localhost"
#define identifiant "predfackers"
#define password "predfackers"
#define bdd "predfackers"


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

//Pour savoir le nombre de produit dans la base de données
long  numberLigne(MYSQL *con){
    long  number = 0;
    char * endPtr;
    if (con == NULL){
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

        
    if (mysql_query(con, "SELECT COUNT(*) FROM PRODUCT"))
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
        for(int i = 0; i < num_fields; i++){
            number = row[i];


        }
        number = strtol( row[0], &endPtr,0);
    }
    return number;
}

//Pour avoir un tableau des produits
void  * tab(MYSQL *con, long nbligne){
    
    char  tabProduct[nbligne][11][400];
    //strcpy(tabProduct, "");
    //strcpy(tabProduct, " ");

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

    int x = 0;
    int y = 0;
    char test[400]=" ";
    while ((row = mysql_fetch_row(result)))
  {
      //printf("%d",num_fields);
      for(int i = 0; i < num_fields; i++)
      {

          //strcpy(test," ");
          //printf("y=%d et i=%d  ",y,i);
          //strcpy(test,row[i]);
          //strcpy(tabProduct[i],test);
          printf("%s", test);  
          fprintf(,<produit>);   
          //printf("%s  ", row[i] ? row[i] : "NULL");
      }
      y++;
      printf("\n");
  }  
    mysql_free_result(result);
    //return tabProduct;
}
