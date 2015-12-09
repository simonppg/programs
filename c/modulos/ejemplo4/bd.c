#include <my_global.h>
#include <mysql.h>

#include "bd.h"

char *SERVIDOR = "localhost";
char *USUARIO = "root";
char *CONTRASENA = "root";
char *BASEDEDATOS = "bioReactor";

void actializarBD(int arc, char **argv)
{
  char *full;
  asprintf(&full,"INSERT INTO muestras VALUES (\'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\', \'%s\')",
    argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
  //printf("\n%s", full);
  Update(full);
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
}

void Consulta(char *Consulta)
{
  int i;
  MYSQL *con = mysql_init(NULL);
  if (con == NULL)
  {
    fprintf(stderr, "mysql_init() failed\n");
  }  

  if (mysql_real_connect(con, SERVIDOR, USUARIO, CONTRASENA, BASEDEDATOS, 0, NULL, 0) == NULL) 
      finish_with_error(con);

  if (mysql_query(con, Consulta))
      finish_with_error(con);
  MYSQL_RES *result = mysql_store_result(con);
  if (result == NULL)
      finish_with_error(con);

  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result)))
  {
    for(i = 0; i < num_fields; i++)
      asprintf(&Datos, "%s", row[i] ? row[i] : "NULL");
  }
  mysql_free_result(result);
  mysql_close(con);
}

void Update(char *Consulta)
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
    fprintf(stderr, "mysql_init() failed\n");
  }  

  if (mysql_real_connect(con, SERVIDOR, USUARIO, CONTRASENA, BASEDEDATOS, 0, NULL, 0) == NULL) 
      finish_with_error(con);

  if (mysql_query(con, Consulta))
      finish_with_error(con);
  mysql_close(con);
}
