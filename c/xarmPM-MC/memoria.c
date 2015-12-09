#include <stdio.h>
#define MEMORY_SIZE 262144

unsigned int memoria[MEMORY_SIZE];

typedef unsigned int _alineacion;

typedef union head{
    struct {
        unsigned int size;
        union head *sig;
    }head;
    _alineacion _alineacion;
}Head;

static Head *base = (Head *)&memoria;
static Head *mlibre = NULL;

void *Xmalloc(unsigned int nbytes)
{
	Head *p, *p_ant = mlibre;
	unsigned int n_unidades;
	n_unidades = (nbytes+sizeof(Head)-1)/sizeof(Head)+1;
	printf("\n\nReserva: %d u, %d bytes",n_unidades, nbytes);

	if (p_ant == NULL)
	{
		base->head.sig = mlibre = p_ant = base;
		base->head.size = (MEMORY_SIZE+sizeof(Head)-1)/sizeof(Head)+1;
	}
	printf("\np_ant: %p", p_ant->head.sig);

	for(p = p_ant->head.sig; ; p_ant = p, p = p->head.sig){
		if (p->head.size>= n_unidades)
		{
			if (p->head.size == n_unidades)
				p_ant->head.sig = p->head.sig;
			else
			{
				p->head.size -= n_unidades;
				p +=p->head.size;
				p->head.size = n_unidades;
			}
			mlibre =p_ant;
			return (void *)(p + 1);
		}
		if (p == mlibre)
			//if ((p = masmem(n_unidades)) == NULL)
				return NULL;
	}
}

void lista()
{
	//Head *ptr = mlibre;
	Head *p, *p_ant = mlibre;
	int cont = 1;
	printf("\n\nBloques y tamaño");
    if (base->head.size == (MEMORY_SIZE+sizeof(Head)-1)/sizeof(Head)+1)
    {
    	printf("\nMemoria libre: %ld", (MEMORY_SIZE+sizeof(Head)-1)/sizeof(Head)+1);
    }
    else
    {
    	/*while(ptr != NULL)
        {
            printf("\nDominio [%d]",ptr->head.size);
            ptr = ptr->head.sig;
        }*/

        for(p = p_ant->head.sig; ; p_ant = p, p = p->head.sig)
        {
			printf("\nBloque [%d] ,tamaño: %d",cont,p->head.size);
			cont++;
			if (p == mlibre)
				break;
		}
    }
}
void Xfree(void **mem)
{
	printf("\n\nLibera: %p",*mem);
	Head *bloque = (Head *)*mem-1, *p;
	for (p = mlibre; bloque < p || bloque > p->head.sig; p = p->head.sig)
		if (p >= p->head.sig)
			break;

	if (bloque + bloque->head.size == p->head.sig)
	{
		bloque->head.size += p->head.sig->head.size;
		bloque->head.sig = p->head.sig->head.sig;
	}
	else
		bloque->head.sig = p->head.sig;

	if (p + p->head.size == bloque)
	{
		p->head.size += bloque->head.size;
		p->head.sig = bloque->head.sig;
	}
	else
		p->head.sig = bloque;

	mlibre = p;
	*mem = NULL;
}


int main(int argc, char const *argv[])
{
	//original
	base->head.size = (MEMORY_SIZE+sizeof(Head)-1)/sizeof(Head)+1;
	//com 1byte regresa 2 unidades
	//base->head.size = ((MEMORY_SIZE*8)+sizeof(Head)-1)/sizeof(Head)+1;
	printf("\nMemoria Disponible.");
	void *dir[2];
	dir[0] = &memoria[0];
	dir[1] = &memoria[MEMORY_SIZE];
	//original
	printf("\nDirI: %p, DirF: %p, size: %ldM",dir[0], dir[1], (((dir[1] - dir[0])/1024)/1024)>>2);
	printf("\nDirI: %p, DirF: %p, size: %ldBytes o %ldKBytes o %ldMBytes",dir[0], dir[1], 
		dir[1] - dir[0],
		(dir[1] - dir[0])/1024,
		(dir[1] - dir[0])/1024/1024);
	printf("\nDirI: %p, DirF: %p, size: %ldBits o %ldKBits o %ldMBits",dir[0], dir[1], 
		(dir[1] - dir[0])*8,
		((dir[1] - dir[0])/1024*8),
		(dir[1] - dir[0])/1024/1024*8);
	printf("\nTamaño de la head: %ld, TotalDir: %ldKbits", sizeof(Head), sizeof(Head)>>2);
	printf("\nTamaño de la head: %dunidades", base->head.size);


	printf("\nbaseDir: %p",&memoria);

	lista();
	void *a;
	void *b;
	void *c;
	void *d;
	void *e;
	void *f;
	void *g;
	a = (unsigned int *)Xmalloc(sizeof(unsigned int *));
	lista();
	b = (unsigned int *)Xmalloc(sizeof(unsigned int *));
	lista();
	c = (unsigned int *)Xmalloc(sizeof(unsigned int *));
	lista();
	Xfree(&a);
	lista();
	d = (unsigned int *)Xmalloc(sizeof(unsigned int *));
	lista();
	e = (unsigned int *)Xmalloc(sizeof(unsigned int *));
	lista();
	f = (unsigned int *)Xmalloc(sizeof(unsigned int *));
	lista();
	g = (unsigned int *)Xmalloc(sizeof(unsigned int *));
	lista();

	printf("\naDir: %p, bDir: %p, cDir: %p, dDir: %p, eDir: %p, fDir: %p, gDir: %p", a,b,c,d,e,f,g);

	printf("\n");
	return 0;
}