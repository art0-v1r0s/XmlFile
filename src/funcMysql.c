#include <stdio.h>
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

void name(char *id,FILE * fichier, MYSQL *con){
    char balise[6][20]={
        "<username>","</username>","<lastName>","</lastName>",
        "<firstName>","</firstName>"
    };
    char req[100];
    char * query = "SELECT USER.username, USER.last_name, USER.first_name FROM USER WHERE id_user='%s'";
    sprintf(req, query, id);
    if (mysql_query(con, req))
    {
      finish_with_error(con);
    }

    MYSQL_RES * queryResult = mysql_store_result(con);

    if (queryResult == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(queryResult);

    MYSQL_ROW line;
    while ((line= mysql_fetch_row(queryResult)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          char * name = line[i] ? line[i] : "NULL";
          switch (i) {
              case 0:
                fprintf(fichier,"\t\t\t%s %s %s\n",balise[0],name,balise[1]);
                break;
              case 1:  
                fprintf(fichier,"\t\t\t%s %s %s\n",balise[2],name,balise[3]);
                break;
              case 2:  
                fprintf(fichier,"\t\t\t%s %s %s\n",balise[4],name,balise[5]);
                break;
          }
      }
      mysql_free_result(queryResult);
  }
}



void insert(char * query, int i, FILE * fichier, MYSQL *con){
    char state[21] = {"NUll"};
    char balise[20][16] = {
        "<category>","</category>","<vendeurid>","</vendeurid>",
        "<name>","</name>","<Acheteur>","</idAcheteur>",
        "<price>","</price>","<mark>","</mark>",
        "<date_start>","</date_start>","<date_end>","</date_end>","<state>","</state>",
        "<validate>","</validate>"
    };

    switch (i) {   
    case 0:
        fprintf(fichier,"\t<produit id='%s' > \n",query );
        break;
    case 1:
        fprintf(fichier,"\t\t%s %s %s\n",balise[0],query,balise[1]);
        break;
    case 2:
        fprintf(fichier,"\t\t<propose id='%s'> \n",query);
        name(query,fichier,con);
        fprintf(fichier,"\t\t</propose> \n");
        break;
    case 3:
        fprintf(fichier,"\t\t%s %s %s\n",balise[4],query,balise[5]);
        break;
    case 4:
        fprintf(fichier,"\t\t<buyer id='%s'> \n",query);
        name(query,fichier,con);
        fprintf(fichier,"\t\t</buyer> \n");
        break;
    case 5:
        fprintf(fichier,"\t\t%s %s %s\n",balise[8],query,balise[9]);
        break;
    case 6:
        fprintf(fichier,"\t\t%s %s %s\n",balise[10],query,balise[11]);
        break;
    case 7:
        fprintf(fichier,"\t\t%s %s %s\n",balise[12],query,balise[13]);
        break;
    case 8:
        fprintf(fichier,"\t\t%s %s %s\n",balise[14],query,balise[15]);
        break;        
    case 10:
        if(strcmp(query,"0")==0){
            strcpy(state,"Rayure");
        }else if(strcmp(query,"1")==0){
            strcpy(state,"Bonne Condition");
        }else if (strcmp(query,"2")==0) {
            strcpy(state,"Très Bonne condition");
        }else if (strcmp(query,"3")==0) {
            strcpy(state,"Comme neuf");
        }
        fprintf(fichier,"\t\t%s %s %s\n",balise[16],state,balise[17]);
        break;
    case 11:
        if(strcmp(query,"0")==0){
            strcpy(state,"Non Validé");
        }else{
            strcpy(state,"Validé");
        }
        fprintf(fichier,"\t\t%s %s %s\n",balise[18],state,balise[19]);
        break;                    
    }

    
}


//Pour avoir un tableau des produits
void  * tab(MYSQL *con,  char * warehouse){
    char req[600];
    FILE* fichier = NULL;
    fichier = fopen("fileXml.xml", "w+");
    fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n", fichier);
    fprintf(fichier,"<entrepot id='%s'>\n",warehouse);
    char *query = "SELECT PRODUCT.id_product, CATEGORY.name, \
    PRODUCT.userpropose,PRODUCT.name,PRODUCT.userbuyer, PRODUCT.price, MARK.name, \
    PRODUCT.date_start, PRODUCT.date_end, PRODUCT.state, PRODUCT.validate \
    FROM PRODUCT INNER JOIN CATEGORY ON PRODUCT.category = CATEGORY.id_category \
    INNER JOIN MARK ON PRODUCT.mark = MARK.id_mark INNER JOIN WAREHOUSE ON \
    PRODUCT.warehouse = WAREHOUSE.id_warehouse  WHERE WAREHOUSE.name='%s'";
    sprintf(req, query, warehouse);
    printf("%s\n", req);
    if (mysql_query(con, req))
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
          char * query = row[i] ? row[i] : "NULL";
          insert(query,i, fichier, con);
      }
      fprintf(fichier,"\t</produit> \n" );
  }

    fputs("<entrepot>\n", fichier);
    mysql_free_result(result);
}
