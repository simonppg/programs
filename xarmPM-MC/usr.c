#include <stdlib.h>
#include <stdio.h>

typedef struct Datos_Usuario_s
{
    int     IntDato;
    double  DoubleDato;
    float   FloatDato;
    long int LongIntDato;
}Datos_Usuario;


//Definiciones
typedef struct Duration_t 
{
        int sec;
    unsigned int nanosec;
}Duration_t;

typedef struct Time_t
{
        int sec; 
        unsigned int nanosec; 
}Time_t;

//----------------------------------------------------------------------------
//                   Principales objetos DDS                               
//----------------------------------------------------------------------------
  typedef struct _DomainParticipantFactory  * DDS_DomainParticipantFactory;
  typedef struct _Entity                    * DDS_Entity;
  //typedef struct _DomainParticipant         * DDS_DomainParticipant;
  //typedef struct _Publisher                 * DDS_Publisher;
  //typedef struct _Subscriber                * DDS_Subscriber;
  typedef struct _DataReader                * DDS_DataReader;
  //typedef struct _DataWriter                * DDS_DataWriter;
  //typedef struct _TopicDescription          * DDS_TopicDescription;
  //typedef struct _Topic                     * DDS_Topic;
  //typedef struct _TypeSupport               * DDS_TypeSupport;
// ---------------------------------------------------------------------------
//                            QoS
// ---------------------------------------------------------------------------

/*
const char * DEADLINE_QOS_POLICY_NAME              = "Deadline";
const char * TIMEBASEDFILTER_QOS_POLICY_NAME       = "TimeBasedFilter";
const char * RELIABILITY_QOS_POLICY_NAME           = "Reliability";
const char * HISTORY_QOS_POLICY_NAME               = "History";
const char * RESOURCELIMITS_QOS_POLICY_NAME        = "ResourceLimits";
 */
typedef struct DeadlineQosPolicy {
Duration_t * period;
}DeadlineQosPolicy;

typedef struct TimeBasedFilterQosPolicy {
Duration_t minimum_separation;
}TimeBasedFilterQosPolicy;

typedef enum ReliabilityQosPolicyKind {
BEST_EFFORT_RELIABILITY_QOS,
RELIABLE_RELIABILITY_QOS
}ReliabilityQosPolicyKind;

typedef struct ReliabilityQosPolicy {
ReliabilityQosPolicyKind kind;
Duration_t max_blocking_time;
}ReliabilityQosPolicy;

typedef enum HistoryQosPolicyKind {
KEEP_LAST_HISTORY_QOS,
KEEP_ALL_HISTORY_QOS
}HistoryQosPolicyKind;

typedef struct HistoryQosPolicy {
HistoryQosPolicyKind kind;
int depth;
}HistoryQosPolicy;

typedef struct ResourceLimitsQosPolicy {
int max_samples;
int max_instances;
int max_samples_per_instance;
}ResourceLimitsQosPolicy;

typedef struct EntityFactoryQosPolicy {
//unsigned char autoenable_created_entities;
}EntityFactoryQosPolicy;

//-----------
typedef struct DomainParticipantFactoryQos {
//EntityFactoryQosPolicy entity_factory;
}DomainParticipantFactoryQos;

typedef struct DomainParticipantQos {
//UserDataQosPolicy  user_data;
//EntityFactoryQosPolicy entity_factory;
}DomainParticipantQos;

typedef struct TopicQos {
        
DeadlineQosPolicy                    deadline;
ReliabilityQosPolicy                 reliability;
HistoryQosPolicy                     history;
ResourceLimitsQosPolicy              resource_limits;
}TopicQos;

typedef struct DataWriterQos {

DeadlineQosPolicy                    * deadline;        
ReliabilityQosPolicy                 reliability;
HistoryQosPolicy                     history;
ResourceLimitsQosPolicy              resource_limits;
}DataWriterQos;

typedef struct PublisherQos {
//PresentationQosPolicy                presentation;
//PartitionQosPolicy                   partition;
//GroupDataQosPolicy                   group_data;
//EntityFactoryQosPolicy               entity_factory;
}PublisherQos;

typedef struct DataReaderQos {
DeadlineQosPolicy                    deadline;
ReliabilityQosPolicy                 reliability;
HistoryQosPolicy                     history;
ResourceLimitsQosPolicy              resource_limits;
TimeBasedFilterQosPolicy             time_based_filter;
}DataReaderQos;

typedef struct SubscriberQos {
//PresentationQosPolicy                presentation;
//PartitionQosPolicy                   partition;
//GroupDataQosPolicy                   group_data;
//EntityFactoryQosPolicy               entity_factory;
}SubscriberQos;

 
//DCPS IMPLEMETATION

typedef int DDS_ReturnCode_t;
typedef unsigned int  DDS_DomainId_t;
typedef unsigned int  DDS_TopicId_t;
typedef unsigned int  DDS_PublisherId_t;
typedef unsigned int  DDS_SubscriberId_t;
typedef unsigned int  DDS_DataWriterId_t;
typedef unsigned int  DDS_StatusMask;
typedef unsigned long  DDS_InstanceHandle_t;
typedef struct  _DDS_DomainParticipantListener * DDS_DomainParticipantListener;
typedef struct  _DDS_PublisherListener * DDS_PublisherListener;
typedef struct  _DDS_TopicListener * DDS_TopicListener;
typedef struct  _DDS_DataWriterListener * DDS_DataWriterListener;
typedef struct  _DDS_SubscriberListener * DDS_SubscriberListener;

DDS_ReturnCode_t DDS_RETCODE_OK; 
DDS_ReturnCode_t DDS_RETCODE_ERROR;

#define DDS_PUBLISHER_QOS_DEFAULT 0

typedef struct _DomainParticipant {
    DDS_DomainId_t domain_id;
    //struct _DomainParticipant *sig;
}DDS_DomainParticipant;

typedef struct _Publisher{
DDS_PublisherId_t publisher_id;
DDS_DomainId_t domain_id;
}DDS_Publisher;

typedef struct _TypeSupport{
char * type_name;
DDS_ReturnCode_t return_code;
}DDS_TypeSupport;

typedef struct _Topic{
DDS_TopicId_t topic_id;
DDS_DomainId_t domain_id;
char * topic_name;
char * type_name;
DDS_TopicListener * listener;
DDS_StatusMask mask;
}DDS_Topic;

typedef struct _DataWriter{
DDS_DataWriterId_t dw_id;
DDS_DomainId_t domain_id;
DDS_TopicId_t topic_id;
DDS_PublisherId_t publisher_id;
DataWriterQos * qos;
}DDS_DataWriter;

typedef struct _Subscriber{
DDS_SubscriberId_t subscriber_id;
DDS_DomainId_t domain_id;
}DDS_Subscriber;

typedef struct _TopicDescription{
char *name; 
char *type_name;
DDS_Topic *topic;
}DDS_TopicDescription;

DDS_DomainParticipant  *domain;
DDS_Publisher          *publisher;
DDS_Topic              *topic;
DDS_DataWriter         *dw;

typedef long _alineacion;

typedef union cabecera{
    struct {
        unsigned longitud;
        union cabecera *sig;
    }cab;
    _alineacion _alineacion;
}Cabecera;

#define DDS_PARTICIPANT_QOS_DEFAULT 0
#define DDS_TOPIC_QOS_DEFAULT 0
#define DDS_DATAWRITER_QOS_DEFAULT 0
//#define NULL 0

//GDS (espacio globar de datos)
struct Publicador {
    int idPUB;
};

/*struct Subscriptor {
    int idSUB;
    int dataReader;
};

struct Fifo {
  char dato;
};

struct Topicos {
    int id;
    struct Fifo fifo[MAXFIFO];
    int entrada;
    int salida;
    Estado estado;
};
*/
struct Dominios {
    int id;
    //struct Topicos topic[MAX];
    struct Publicador *entrada, *salida;
    //struct Subscriptor  sub[MAX];
    struct Dominios *sig, *ant;
};

struct  GDS {
    struct Dominios *inicio, *fin;
};

struct GDS *uDDS;
//GDS (espacio globar de datos)


//Domain Participant Factory
/*DDS_DomainParticipant *DDS_DomainParticipantFactory_create_participant_original(unsigned int domain_id, int qos, DDS_DomainParticipantListener * listener, DDS_StatusMask mask)
{
    int agregar = 1;
    DDS_DomainParticipant *domain;
    domain = malloc(sizeof(DDS_DomainParticipant));

    //Es el pimer dominio
    if (uDDS->entrada == NULL)
    {
        if(domain != NULL )
        {
            if (domain_id >= 0)
            {
                domain->domain_id = domain_id;
                domain->sig = NULL;
                uDDS->entrada = uDDS->salida = domain;
                printf("\nAdd: %d", domain->domain_id);
            }
            else
            {
                free(domain);
                return NULL;
            }
        }
    }
    //Revisa si ya existe
    else
    {
        if (domain_id >= 0) //dominio valido
        {
            DDS_DomainParticipant *buscador = uDDS->salida;
            while(buscador != NULL)
            {
                if(buscador->domain_id == domain_id)
                {
                    printf("\nEl dominio ya existe.");
                    agregar = -1;
                    break;
                }
                buscador = buscador->sig;
            }

            if (agregar != -1)
            {
                domain->domain_id = domain_id;
                domain->sig = NULL;
                uDDS->entrada->sig = domain;
                uDDS->entrada = domain;
                printf("\nAdd: %d", domain->domain_id);
            }
        }
        else
        {
            free(domain);
            return NULL;
        }
    }

    return domain;
}*/
//Domain Participant Factory
DDS_DomainParticipant *DDS_DomainParticipantFactory_create_participant(unsigned int domain_id, int qos, DDS_DomainParticipantListener * listener, DDS_StatusMask mask)
{
    int agregar = 1;
    DDS_DomainParticipant *domain = malloc(sizeof(DDS_DomainParticipant));
    struct Dominios *domainGDS = malloc(sizeof(struct Dominios));

    //Es el pimer dominio
    if (uDDS->inicio == NULL)
    {
        if(domain != NULL )
        {
            if (domain_id >= 0)
            {
                domainGDS->id = domain->domain_id = domain_id;
                domainGDS->sig = NULL;
                uDDS->inicio = uDDS->fin = domainGDS;
                printf("\nAdd: %d", domain->domain_id);
            }
            else
            {
                free(domain);
                return NULL;
            }
        }
    }
    //Revisa si ya existe
    else
    {
        if (domain_id >= 0) //dominio valido
        {
            struct Dominios *buscador = uDDS->fin;
            while(buscador != NULL)
            {
                if(buscador->id == domain_id)
                {
                    printf("\nEl dominio ya existe.");
                    agregar = -1;
                    break;
                }
                buscador = buscador->sig;
            }

            if (agregar != -1)
            {
                domainGDS->id = domain->domain_id = domain_id;
                domainGDS->sig = NULL;
                uDDS->inicio->sig = domainGDS;
                uDDS->inicio = domainGDS;
                printf("\nAdd: %d", domain->domain_id);
            }
        }
        else
        {
            free(domain);
            return NULL;
        }
    }

    return domain;
}


//Domain Participant Crear Publisher
DDS_Publisher *DDS_DomainParticipant_create_publisher(
                                        DDS_DomainParticipant *domain,
                                        DDS_PublisherId_t publisher_id,
                                        int qos,
                                        DDS_PublisherListener * listener,
                                        DDS_StatusMask mask)
{
    DDS_Publisher * publisher = malloc(sizeof(DDS_Publisher));
    /*if(publisher_id != NULL ) {
        publisher->publisher_id=publisher_id;
        publisher->domain_id=domain->domain_id; 
    }
    else {
        publisher=NULL;
    }*/
    return publisher;
}

//Interfaz de tipo de dato
DDS_ReturnCode_t TypeSupport_register_type(
                                        DDS_DomainParticipant *domain,
                                        char * type_name)
{
    DDS_TypeSupport * TypeSupport=malloc(sizeof(DDS_TypeSupport));

    /*if(type_name != NULL) {
        TypeSupport->type_name=type_name;
        TypeSupport->return_code=DDS_RETCODE_OK;    
    }
    else {
        TypeSupport->return_code=DDS_RETCODE_ERROR;
    }*/
    return TypeSupport->return_code;
}

//Crear Topic
DDS_Topic *DDS_DomainParticipant_create_topic(
                                        DDS_DomainParticipant *domain,
                                        DDS_TopicId_t topic_id,
                                        char * topic_name,
                                        char * type_name,
                                        int qos,
                                        DDS_TopicListener * listener,
                                        DDS_StatusMask mask)
{
    DDS_Topic * topic=malloc(sizeof(DDS_Topic));
    /*if(topic_id != NULL) {
        topic->topic_id=topic_id;
        topic->domain_id= domain->domain_id;
        topic->topic_name =topic_name;
        topic->type_name= type_name;
    }
    else {
        topic=NULL; 
    }*/
    return topic;
}

//Crear Datawriter
DDS_DataWriter * DDS_Publisher_create_datawriter(DDS_Publisher *publisher, DDS_DataWriterId_t dw_id, DDS_Topic * topic, int qos, DDS_DataWriterListener * listener, DDS_StatusMask mask)
{
    DDS_DataWriter * dw=malloc(sizeof(DDS_DataWriter));
    /*if(dw_id != NULL) {
        //Asignación parámetros DataWriter 
        dw->domain_id = topic->domain_id;
        dw->topic_id = topic->topic_id;
        dw->publisher_id = publisher->publisher_id;
        
        //DEADLINE QOS
        dw->qos=malloc(sizeof(DataWriterQos));
        dw->qos->deadline=malloc(sizeof(DeadlineQosPolicy));
        dw->qos->deadline->period=malloc(sizeof(Duration_t));
        dw->qos->deadline->period->sec=1;
    }
    else {
        dw=NULL;    
    }*/
    return dw;
}

/*listar_dominios()
{
    if (uDDS->entrada == NULL)
        printf("\nNo hay dominios");
    else
    {
        DDS_DomainParticipant *buscador = uDDS->fin;
        while(buscador != NULL)
        {
            printf("\nDominio [%d]",buscador->domain_id);
            buscador = buscador->sig;
        }
    }
}*/

listar_dominios()
{
    if (uDDS->inicio == NULL)
        printf("\nNo hay dominios");
    else
    {
        struct Dominios *buscador = uDDS->fin;
        while(buscador != NULL)
        {
            printf("\nDominio [%d]",buscador->id);
            buscador = buscador->sig;
        }
    }
}

int main(int argc, char * argv[])
{
    Datos_Usuario Datos1;
    uDDS = malloc(sizeof(struct GDS));
    uDDS->inicio = uDDS->fin = NULL;

    //Crear DomainParticipant
    domain = DDS_DomainParticipantFactory_create_participant(1,DDS_PARTICIPANT_QOS_DEFAULT,NULL,0);
    domain = DDS_DomainParticipantFactory_create_participant(2,DDS_PARTICIPANT_QOS_DEFAULT,NULL,0);
    domain = DDS_DomainParticipantFactory_create_participant(3,DDS_PARTICIPANT_QOS_DEFAULT,NULL,0);
    domain = DDS_DomainParticipantFactory_create_participant(4,DDS_PARTICIPANT_QOS_DEFAULT,NULL,0);
    domain = DDS_DomainParticipantFactory_create_participant(2,DDS_PARTICIPANT_QOS_DEFAULT,NULL,0);
    listar_dominios();
    if ( domain == NULL )
    {
        printf("ERROR creando DomainParticipant.\n");
        return -1;
    }

    //Crear Publisher
    publisher = DDS_DomainParticipant_create_publisher(domain, 1, DDS_PUBLISHER_QOS_DEFAULT, NULL,0 );
    if ( publisher == NULL )
    {
    	printf("ERROR creando Publisher.\n");
        return -1;
    }
#if 0
    //Registrar tipo de datos
    /*if (TypeSupport_register_type( domain, sizeof(struct Datos_Usuario_s)) != DDS_RETCODE_OK)
    {
    	printf("ERROR registrando tipo de datos\n");
        return -1;
    }*/
        
    //Crear topic
    /*topic = DDS_DomainParticipant_create_topic(
                                        domain,
                                        1,
                                        &Datos1,
                                        sizeof(struct Datos_Usuario_s),
                                        DDS_TOPIC_QOS_DEFAULT,
                                        NULL,
                                        0);*/
    topic = DDS_DomainParticipant_create_topic(domain, 1, "HolaMundo", "cadena", DDS_TOPIC_QOS_DEFAULT, NULL, 0);
 
    if ( topic == NULL )
    {
    	printf("ERROR creando Topic.\n");
        return -1;
    }

    //Crear DataWriter  
    dw = DDS_Publisher_create_datawriter(publisher, 1, topic, DDS_DATAWRITER_QOS_DEFAULT, NULL, 0 );
    if (dw == NULL)
    {
        printf("ERROR creando DataWriter\n");
        return -1;
    }

    //Registrar participante en el DDS
    //config(domain->domain_id, topic->topic_id, publisher->publisher_id, dw->dw_id);

    //Publicar Datos
    //while(1)
    {
    	//Asignar nuevos valores a los datos	y despues publicar
    	//DDS_DataWriter_write(dw);
    }
#endif
    printf("\n");
}


/*

for GDS->dominio.id == dw.domId;

    for GDS->dominio->publicador.id == dw.pubID;

        for GDS->dominio->topico.id == dw.topID;

            publicar(GDS->dominio->topico.fifo, dw.dato);
            */