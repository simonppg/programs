#include <stdio.h>

#define INICIO 0xaaaa;
#define FIN 0xffff;

struct Datos
{
	int inicio;
	int a;
	int b;
	int c;
	char d[255];
	int fin;
};

struct Datos dato =
	{
		.a = 10,
		.b = 11,
		.c = 12,
		.d = "Hola esto es una trama muy larga"
	};
struct Datos dato1 =
	{
		.a = 100,
		.b = 110,
		.c = 120,
		.d = "si"
	};

void pintar(struct Datos *ptr)
{
	printf("\n\nInicio: %x", ptr->inicio);
	printf("\na: %d", ptr->a);
	printf("\nb: %d", ptr->b);
	printf("\nc: %d", ptr->c);
	printf("\nd: %s", ptr->d);
	printf("\nFin: %x", ptr->fin);
}

void dirDato(void * ptr)
{
	printf("\nDireccion ptr: %p", ptr);
}

mover(void * src_start, void * src_end, void * dst_start)
{    
    const unsigned int *start_src = src_start;
    const unsigned int *end_src = src_end;
    unsigned int *vectors_dst;
    vectors_dst = (unsigned int *)dst_start;

    printf("\n\nDireccion src_start: %p", src_start);
    printf("\nTamaño: %lu bytes", src_end - src_start);
    printf("\nDireccion dst_start: %p", dst_start);

    while(start_src < end_src)
    {
        *vectors_dst++ = *start_src++;
    }
    *vectors_dst++ = *start_src++;
}

void main()
{
	dato.inicio = INICIO;
	dato.fin = FIN;
	dato1.inicio = INICIO;
	dato1.fin = 1234567;
	pintar(&dato);
	pintar(&dato1);

	dirDato(&dato);
	dirDato(&dato1);
	mover(&dato.inicio,&dato.fin,&dato1.inicio);

	pintar(&dato);
	pintar(&dato1);

	void * ptr = &dato1.inicio;
	int * intp = (int *)ptr;
	printf("\nDatos");
	printf("\nInicio %d", *intp);


	printf("\n");
}



void copy_vectors(void)
{
    /*extern const uint32_t _vectors_start;
    extern const uint32_t _vectors_end;
    uint32_t *vectors_dst;
    const uint32_t *vectors_src = &_vectors_start;
    
    vectors_dst = (uint32_t *)0x00000000;
    while(vectors_src < &_vectors_end)
    {
        *vectors_dst++ = *vectors_src++;
    }*/
}