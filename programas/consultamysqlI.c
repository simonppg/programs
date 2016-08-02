//gcc programa.c -o programa -std=c99 `mysql_config --cflags --libs`
#include <my_global.h>
#include <mysql.h>

char *SERVIDOR = "localhost";
char *USUARIO = "root";
char *CONTRASENA = "root";
char *BASEDEDATOS = "bioReactor";

char *Datos;
char *full;
int cantidadDeMuestras = 3;

void finish_with_error(MYSQL * con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
}

void Consulta(char *Consulta)
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
	}

	if (mysql_real_connect
	    (con, SERVIDOR, USUARIO, CONTRASENA, BASEDEDATOS, 0, NULL,
	     0) == NULL)
		finish_with_error(con);

	if (mysql_query(con, Consulta))
		finish_with_error(con);
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
		finish_with_error(con);

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result))) {
		for (int i = 0; i < num_fields; i++)
			asprintf(&Datos, "%s", row[i] ? row[i] : "NULL");
	}
	mysql_free_result(result);
	mysql_close(con);
}

void Update(char *Consulta)
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
	}

	if (mysql_real_connect
	    (con, SERVIDOR, USUARIO, CONTRASENA, BASEDEDATOS, 0, NULL,
	     0) == NULL)
		finish_with_error(con);

	if (mysql_query(con, Consulta))
		finish_with_error(con);
	mysql_close(con);
}

void estado_BioReactor(int arc, char **argv)
{
	printf("\nLectura de sensores");
	int i;
	char *full;
	srand(time(NULL));
	for (i = 0; i < arc; i++) {
		asprintf(&full, "Muestas = %d", (rand() % 11));
		argv[i] = full;
	}
}

void *dinamica(void *args)
{
	int i = 0, j = 0;

	char **Muestras = malloc(cantidadDeMuestras);
	for (i = 0; i < cantidadDeMuestras; i++) {
		Muestras[i] = malloc(1024 * sizeof(char));
		Muestras[i][0] = '\0';
	}
	for (i = 0; i < cantidadDeMuestras; i++) {
		Muestras[i] = "hola";
	}
	for (i = 0; i < cantidadDeMuestras; i++) {
		printf("\n%s", Muestras[i]);
	}

	while (1) {
		printf("\n\nIteracion = %d", j);
		estado_BioReactor(cantidadDeMuestras, Muestras);
		for (i = 0; i < cantidadDeMuestras; i++) {
			printf("\n%s", Muestras[i]);
		}

		Consulta("SELECT ph FROM muestras");
		printf("\nPH = %s", Datos);

		if (Datos[0] == '1') {
			//printf("encender");
			Update("UPDATE muestras set ph=0");
		} else {
			//printf("apagar");
			Update("UPDATE muestras set ph=1");
		}
		sleep(1);
		fflush(stdout);
		j++;
	}
}

int main(int argc, char **argv)
{
	pthread_t thread1;
	pthread_create(&thread1, NULL, dinamica, NULL);
	pthread_join(thread1, NULL);
}
