#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "middleware.h"

mov(void * src_start,void * dst_start, int size)
{
    printf("\n\nDireccion src_start: %p", src_start);
    printf("\nDireccion dst_start: %p", dst_start);
    
    const unsigned int *vectors_src = src_start;
    unsigned int *vectors_dst;
    vectors_dst = (unsigned int *)dst_start;

    int i=0;
    while(i < size>>2)
    {
        printf("\ni[%d] ",i);
        *vectors_dst++ = *vectors_src++;
        i++;
    }
    *vectors_dst++ = *vectors_src++;
}

//end atod implementation
void initDataTopic(Datos *xxxPackMsg)
{
    xxxPackMsg->StringDato = "\0";
    xxxPackMsg->IntDato = 0;
    xxxPackMsg->DoubleDato = 0;
    xxxPackMsg->FloatDato = 0;
    xxxPackMsg->LongIntDato = 0;
}

void showDataTopic(Datos xxxPackMsg)
{
    printf("\n\t<<<Datos>>>\n");
    printf("xxxPackMsg.String_Data            = %s\n",xxxPackMsg.StringDato);
    printf("xxxPackMsg.Int_Data               = %d\n",xxxPackMsg.IntDato);
    printf("xxxPackMsg.Double_Data            = %3.15f\n",xxxPackMsg.DoubleDato);
    printf("xxxPackMsg.Float_Data             = %f\n",xxxPackMsg.FloatDato);
    printf("xxxPackMsg.LongInt_Data           = %lu",xxxPackMsg.LongIntDato);
    printf("\n");
}


void pintar (uDDS_GDS_node *nodo)
{
    int i=0;
    if(nodo->uDDS_node_type == 0)
        printf("\nPUB");
    else
        printf("\nSUB");
    printf("\nDominio:%d", nodo->uDDS_DomainID);
    printf("\nId: \t%d", nodo->uDDS_node_typeID);
    printf("\nTopic: \t%d\nDatos: \t", nodo->topicID);
    /*while(nodo->uDDS_Serial_data[i] != '$')
        printf("%c", nodo->uDDS_Serial_data[i++]);
    printf("%c", nodo->uDDS_Serial_data[i++]);*/
    printf("\n");
}


void pintar_GDS(struct GDS * gds)
{
    int d,t,p,s,f;
    int i;
    d=t=p=s=0;
    f=gds->dom[d].topic[t].salida;
    while(gds->dom[d].id > 0)
    {
        printf("\nD:%d",gds->dom[d].id);
        while(gds->dom[d].topic[t].id > 0)
        {
            printf("\tT:%d\t",gds->dom[d].topic[t].id);
            while(gds->dom[d].topic[t].pub[p].idPUB > 0)
            {
                printf("-P:%d",gds->dom[d].topic[t].pub[p].idPUB);
                p++;
            }
            p=0;
            printf("\t");
            while(gds->dom[d].topic[t].sub[s].idSUB > 0)
            {
                printf("-S:%d",gds->dom[d].topic[t].sub[s].idSUB);
                s++;
            }
            s=0;
            printf("\nE: %d, S, %d",gds->dom[d].topic[t].entrada,gds->dom[d].topic[t].salida);
            printf("\tdatos: ");
            i=0;
            while(i < MAXFIFO)
            {
                if(gds->dom[d].topic[t].fifo[i].dato == '#')
                    printf("\n");
                printf("\t[%d] %c",i,gds->dom[d].topic[t].fifo[i].dato);
                i++;
                f++;
            }
            f=gds->dom[d].topic[t].salida;

            printf("\n");
            t++;
        }
        //printf("\nLa de: %d",d);
        t=0;
        d++;
    }
    printf("\n");
}

void init_GDS(struct GDS * gds)
{
    int d,t,p,s,f;
    int i;
    d=t=p=s=0;
    f=gds->dom[d].topic[t].salida;
    while(gds->dom[d].id > 0)
    {
        while(gds->dom[d].topic[t].id > 0)
        {
            while(gds->dom[d].topic[t].pub[p].idPUB > 0)
            {
                p++;
            }
            p=0;
            while(gds->dom[d].topic[t].sub[s].idSUB > 0)
            {
                s++;
            }
            s=0;
            i=0;
            while(i < MAXFIFO)
            {
                gds->dom[d].topic[t].fifo[i].dato=0;
                i++;
                f++;
            }
            f=gds->dom[d].topic[t].salida;
            t++;
        }
        //printf("\nLa de: %d",d);
        t=0;
        d++;
    }
    printf("\n");
}

void copiar(char *serial, char *mensaje, int len)
{
    int i=0;
    while(i <= len)
    {
        serial[i]=*(mensaje+i);
        i++;
    }
}

void encolar( struct Topicos *q, char valor )
{
    //printf("\nE: %d, S: %d, MAX: %d, valor: %c",q->entrada,q->salida, MAXFIFO, valor);
    if(q->entrada >= MAXFIFO) //FIFO entrada llega al final
    {
        q->entrada = 0;
        //revisar si hay espacio al inicio de la FIFO
        if(q->salida > 0)
        {
            q->fifo[q->entrada].dato = valor;
        }
        else if(q->salida == 0)
        {
            q->salida++;
        }
        q->fifo[q->entrada].dato = valor;
    }
    else
    {
        if(q->salida == q->entrada+1)
        {
            q->fifo[q->entrada].dato = valor;
            q->entrada++;
            q->salida++;
            if(q->salida >= MAXFIFO)
                q->salida = 0;
        }
        else
        {
            q->fifo[q->entrada].dato = valor;
            q->entrada++;
            if(q->entrada >= MAXFIFO)
            {
                q->entrada = 0;
                if(q->salida == 0)
                {
                    q->salida++;
                }
            }
        }
    }
}

char desencolar( struct Topicos *q ) //falta vlidar cola vacia y tamaño fijo de la cola!
{
    //printf("\nE: %d, S: %d, MAX: %d",q->entrada,q->salida, MAXFIFO);
    char valor;
    valor = q->fifo[q->salida].dato;
    q->salida++;
    if(q->salida >= MAXFIFO)
        q->salida = 0;
    return valor;
}

void escribir(int D, int T, int P, void *inicio, int size, struct GDS * gds)
{    
    if (size < MAXFIFO)
    {
        mov(inicio, &gds->dom[D].topic[T].fifo[0].dato, size);
        
    }
    else
        printf("\nNo hay suficiente espacio (incremente MAXFIFO o ingrese menos datos)");
}

int leer(int D, int T, int P, void *inicio, int size, struct GDS * gds)
{

    if(gds->dom[D].topic[T].entrada != gds->dom[D].topic[T].salida)
    {

        if (size < MAXFIFO)
        {
            mov(&gds->dom[D].topic[T].fifo[0].dato, inicio, size);
            gds->dom[D].topic[T].salida += size;
        }
        else
            printf("\nNo hay suficiente espacio (incremente MAXFIFO o ingrese menos datos)");
    }
    else
    {
        printf("\nYa no hay datos");
        return -1;
    }
}

void publicar(struct uDDS_GDS_node_s *nodo, struct GDS * gds)
{
    if(nodo->uDDS_node_type == PUB)
    {
        int d,t,p,s,f;
        d=t=p=s=f=0;
        int D,T,P,S,F;
        D=T=P=S=F=-1;
        printf("\nAnalizando...%d",nodo->uDDS_node_typeID);
        while(gds->dom[d].id > 0)
        {
            while(gds->dom[d].topic[t].id > 0)
            {
                while(gds->dom[d].topic[t].pub[p].idPUB > 0)
                {
                    if(gds->dom[d].id == nodo->uDDS_DomainID &&
                        gds->dom[d].topic[t].id == nodo->topicID &&
                        gds->dom[d].topic[t].pub[p].idPUB == nodo->uDDS_node_typeID)
                    {
                        D=d;
                        T=t;
                        P=p;
                        //printf("\nPUB: %d Dato: \"%s\" en D: %d, T: %d, P: %d",nodo->uDDS_node_typeID,nodo->uDDS_Serial_data,D,T,P);
                    }
                    p++;
                }
                p=0;
                t++;
            }
            t=0;
            d++;
        }
        if(D >= 0 && T >= 0 && P >= 0)
        {
            escribir(D, T, P, nodo->inicio, nodo->size, gds);
        }
    }
    else
        printf("\nNo es un publicador");
}





void subscribir(struct uDDS_GDS_node_s *nodo, struct GDS * gds)
{
    if(nodo->uDDS_node_type == SUB)
    {
        printf("\nAqui llega");
        int d,t,p,s,f;
        d=t=p=s=f=0;
        int D,T,P,S,F;
        D=T=P=S=F=-1;
        printf("\nAnalizando...%d",nodo->uDDS_node_typeID);
        while(gds->dom[d].id > 0)
        {
            printf("\nDominio: %d",gds->dom[d].id);
            while(gds->dom[d].topic[t].id > 0)
            {
                printf("\nTopic: %d",gds->dom[d].topic[0].id);
                while(gds->dom[d].topic[t].sub[s].idSUB > 0)
                {
                    printf("\nSub: %d",gds->dom[d].topic[t].sub[s].idSUB);
                    if(gds->dom[d].id == nodo->uDDS_DomainID &&
                        gds->dom[d].topic[t].id == nodo->topicID &&
                        gds->dom[d].topic[t].sub[s].idSUB == nodo->uDDS_node_typeID)
                    {
                        D=d;
                        T=t;
                        S=s;
                        printf("\nPUB: %d D: %d, T: %d, P: %d",nodo->uDDS_node_typeID,D,T,P);
                    }
                    s++;
                }
                s=0;
                t++;
            }
            t=0;
            d++;
        }
        printf("\nDominio: %d",gds->dom[d].id);
        if(D >= 0 && T >= 0 && S >= 0)
        {
            printf("\nAqui llega");
            if(leer(D, T, S, nodo->inicio, nodo->size, gds) == -1)
                copiar(nodo->uDDS_error,"Ya no hay datos",15);       
        }
    }
    else
        printf("\nNo es un subscriptor");
}




















