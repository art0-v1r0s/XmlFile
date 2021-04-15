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

void insert(char * query, int i, FILE * fichier){
    char state[21] = {"NUll"};
    char balise[18][15] = {
        "<category>","</category>","<name>","</name>","<description>","</description>",
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
        fprintf(fichier,"\t\t%s %s %s\n",balise[2],query,balise[3]);
        break;
    case 3:
        fprintf(fichier,"\t\t%s %s %s\n",balise[4],query,balise[5]);
        break;
    case 4:
        fprintf(fichier,"\t\t%s %s %s\n",balise[6],query,balise[7]);
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
        if(strcmp(query,"0")==0){
            strcpy(state,"Rayure");
        }else if(strcmp(query,"1")==0){
            strcpy(state,"Bonne Condition");
        }else if (strcmp(query,"2")==0) {
            strcpy(state,"Très Bonne condition");
        }else if (strcmp(query,"3")==0) {
            strcpy(state,"Comme neuf");
        }
        fprintf(fichier,"\t\t%s %s %s\n",balise[14],state,balise[15]);
        break;
    case 9:
        if(strcmp(query,"0")==0){
            strcpy(state,"Non Validé");
        }else{
            strcpy(state,"Validé");
        }
        fprintf(fichier,"\t\t%s %s %s\n",balise[16],state,balise[17]);
        break;                    
    }

    
}

//Pour savoir le nombre de produit dans la base de données
long  numberLigne(MYSQL *con, char *warehouse){
    char req[172];
    long  number = 0;
    char * endPtr;
    char * query = "SELECT COUNT(*) FROM PRODUCT INNER JOIN WAREHOUSE \
     ON PRODUCT.warehouse = WAREHOUSE.id_warehouse WHERE WAREHOUSE.name = '%s'";
    sprintf(req, query, warehouse);
    if (con == NULL){
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

        
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
        for(int i = 0; i < num_fields; i++){
            number = row[i];


        }
        number = strtol( row[0], &endPtr,0);
    }
    return number;
}

//Pour avoir un tableau des produits
void  * tab(MYSQL *con, long nbligne, char * warehouse){
    char req[500];
    FILE* fichier = NULL;
    fichier = fopen("fileXml.xml", "w+");
    fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n", fichier);
    fprintf(fichier,"<entrepot id='%s'>\n",warehouse);
    char  tabProduct[nbligne][11][400];
    char *query = "SELECT PRODUCT.id_product, CATEGORY.name, PRODUCT.name,PRODUCT.description, PRODUCT.price, MARK.name, PRODUCT.date_start, PRODUCT.date_end, PRODUCT.state, PRODUCT.validate \
    FROM PRODUCT INNER JOIN CATEGORY ON PRODUCT.category = CATEGORY.id_category \
    INNER JOIN MARK ON PRODUCT.mark = MARK.id_mark INNER JOIN WAREHOUSE ON \
    PRODUCT.warehouse = WAREHOUSE.id_warehouse WHERE WAREHOUSE.name='%s'";
    sprintf(req, query, warehouse);
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
          insert(query,i, fichier);
      }
      fprintf(fichier,"\t</produit> \n" );
  }

    fputs("<entrepot>\n", fichier);
    mysql_free_result(result);
}
