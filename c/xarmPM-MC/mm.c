#include <stdio.h>
#include <ctype.h>

typedef long _alineacion;

typedef union cabecera{
    struct {
        unsigned longitud;
        union cabecera *sig;
    }cab;
    _alineacion _alineacion;
}Cabecera;

#define size 100
char a[size];

void * ptr = &a;
	//int * intp = (int *)ptr;
static Cabecera *base = (Cabecera*) &a;
static Cabecera *mlibre;

static Cabecera *masmem (unsigned);

void *rmem(unsigned nbytes)
{
	Cabecera *p, *p_ant = mlibre;
	unsigned n_unidades;

	if (p_ant == NULL)
	{
		base->cab.sig = mlibre = p_ant = base;
		base->cab.longitud = (size+sizeof(Cabecera)-1)/sizeof(Cabecera)+1;
	}

	n_unidades = (nbytes+sizeof(Cabecera)-1)/sizeof(Cabecera)+1;

	for(p = p_ant->cab.sig; ; p_ant = p, p = p->cab.sig){
		if (p->cab.longitud>= n_unidades)
		{
			if (p->cab.longitud == n_unidades)
				p_ant->cab.sig = p->cab.sig;
			else
			{
				p->cab.longitud -= n_unidades;
				p +=p->cab.longitud;
				p->cab.longitud = n_unidades;
			}
			mlibre =p_ant;
			return (void *)(p + 1);
		}
		if (p == mlibre)
			//if ((p = masmem(n_unidades)) == NULL)
				return NULL;
	}
}

static Cabecera *masmem(unsigned n_unidades)
{
	printf("\nMAS MEMORIA");
	#define MIN_MEMORIA 1024
	Cabecera *p;
	void lmem();

	if (n_unidades < MIN_MEMORIA)
		n_unidades = MIN_MEMORIA;
	
	if ((p = (Cabecera *) sbrk(n_unidades*sizeof(Cabecera))) == (Cabecera *) -1)
		return NULL;

	p->cab.longitud = n_unidades;
	lmem ((void *)(p + 1));

	return mlibre;
}

void lmem(void *mem)
{
	Cabecera *bloque = (Cabecera *)mem-1, *p;
	for (p = mlibre; bloque < p || bloque > p->cab.sig; p = p->cab.sig)
		if (p >= p->cab.sig)
			break;

	if (bloque + bloque->cab.longitud == p->cab.sig)
	{
		bloque->cab.longitud += p->cab.sig->cab.longitud;
		bloque->cab.sig = p->cab.sig->cab.sig;
	}
	else
		bloque->cab.sig = p->cab.sig;

	if (p + p->cab.longitud == bloque)
	{
		p->cab.longitud += bloque->cab.longitud;
		p->cab.sig = bloque->cab.sig;
	}
	else
		p->cab.sig = bloque;

	mlibre = p;
}

#define MAX 256
#define EQ(str1, str2) (strcmp((str1), (str2)) == 0)

struct mensaje {
	char* contenido;
	struct mensaje *siguiente;
};

struct cola_mensajes {
	struct mensaje *entrada, *salida;
};

void enviar_mensaje();
struct mensaje *recibir_mensaje();
struct mensaje *crear_mensaje();
void liberar_mensaje();

int main(int argc, char const *argv[])
{
	char str[MAX];
	struct mensaje *mensaje;
	struct cola_mensajes cola = {NULL, NULL};

	while (!0) {
		printf("< ");
		scanf("%s", str);
		if (EQ(str, "enviar")) {
			scanf("%s", str);
			enviar_mensaje(&cola, str);
		}else if (EQ(str, "recibir")) {
			mensaje = recibir_mensaje(&cola);
			if (mensaje) {
				printf("> %s\n", mensaje->contenido);
				liberar_mensaje(mensaje);
			}else
				printf("No hay mas mensajes.\n");
		}else if (EQ(str, "salir"))
			exit (-1);
		else
			fprintf(stderr, "[%s] desconocido.\n", str);
	}
	return 0;
}

void enviar_mensaje (struct cola_mensajes *cola, char *str)
{
	struct mensaje *m;

	m = crear_mensaje (str);
	if(m == NULL)
		return;
	else
		printf("\nmDir: %p",&m);

	if (cola->entrada == NULL)
		cola->entrada = cola->salida = m;
	else {
		cola->entrada->siguiente = m;
		cola->entrada = m;
	}
}

struct mensaje *recibir_mensaje(struct cola_mensajes * cola)
{
	struct mensaje *m = cola->salida;

	if (cola->salida == NULL)
		cola->entrada = NULL;
	else
		cola->salida = cola->salida->siguiente;
	return m;
}

struct mensaje *crear_mensaje(char *str)
{
	void *rmem();
	struct mensaje *m = (struct mensaje *) rmem (sizeof(struct mensaje));

	if (m== NULL)
	{
		perror("enviar_mensaje");
		printf("\nNo pudo crear mensaje.\n");
		return NULL;
		//exit(-1);
	}
	if ((m->contenido = (char*) rmem((strlen(str)+1)*sizeof(char))) == NULL)
	{
		perror("enviar_mensaje");
		printf("\nNo pudo crear mensaje->contenido.\n");
		return NULL;
		//exit(-1);
	}

	strcpy(m->contenido, str);
	m->siguiente = NULL;

	return m;
}

void liberar_mensaje(struct mensaje *m)
{
	void lmem();
	if (m)
	{
		lmem(m->contenido);
		lmem(m);
	}
}