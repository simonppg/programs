#if !defined (_MIDDLEWARE_H_)
#define _MIDDLEWARE_H_

typedef struct Datos_s
{
    char    *StringDato;//ya lo revise y asi esta bien aun que no paresca :S
    int     IntDato;
    double  DoubleDato;
    float   FloatDato;
    long int LongIntDato;
    char fin;
}Datos;



#define TIMEOUT 100  //--TIMEOUT in micro-sec
#define LENGHTMAX 256

#define MAXLENGHTMSG 20
#define LENGHTMSGTOPACK 255 //este valor es critico
#define MAXNUMSUBMSG 30

//const char *xxxTYPENAME = "uDDS_MsgPackage"; //Nombre de la estructura de datos

typedef enum {
               GENERAL=1,CONTROL,MSGOK
             } uDDS_MsgType; //GENERAL=1, CONTROL=2, MSGOK=3

//Message Header
typedef struct {
    uDDS_MsgType MsgType;
} uDDS_MsgHeader;


//Message package
typedef struct {
  uDDS_MsgHeader uDDS_MsgHeader;

  char String_Data[MAXLENGHTMSG];
  int Int_Data;
  float Float_Data;
  double Double_Data;
  long int LongInt_Data;
} uDDS_MsgPackage;


static int serial_fd = 0; //-- Descriptor de puerto serial
char data[LENGHTMAX];    //-- The received command


char* Serialize(char* buffer, Datos xxxPackMsg);
Datos deSerialize(char *MsgtoReceive);
void DataWriter_write(uDDS_MsgPackage instance_data);



//reverse:  reverse string s in place *
void strreverse(char* begin, char* end);
  
void itoa(int value, char* str, int base);

//ltoa implementation **************
#define INT_DIGITOS 63
static char buf[INT_DIGITOS + 2];
// Buffer para INT_DIGITS dígitos, signo - y fin de string '\0' **/

char * ltoa(long int i, unsigned int base);
char* substring(const char* cadena, int inicio, int chars);
char * dtoa (double value, int ndigits, char *buf);
char *ftoa(float f, int ndigits);
double atod(const char* s, char** endptr);
void showDataTopic(Datos xxxPackMsg);





char* IntMsgtoPack(char* buffer, int int_subMsgtoPack);
char* StrMsgtoPack(char* buffer, char* char_subMsgtoPack);
char * FloatMsgtoPack(char* buffer, float float_subMsgtoPack, int ndigits);
char * DoubleMsgtoPack(char* buffer, double double_subMsgtoPack, int ndigits);
char * LongIntMsgtoPack(long int longint_subMsgtoPack);












////////////////////////// middleware
typedef enum uDDSPS{PUB, SUB}  uDDS_NODE_TYPE;
typedef enum uDDSDATAPUB{NOT_AVAILABLE,AVAILABLE} uDDS_ON_DATA_AVAILABLE;
typedef enum uDDSDATAPUBSEND{NOT_SEND,SEND} uDDS_ON_DATA_SEND; //flags for Publishers
typedef enum uDDSDATASUB{RECEIVED,NOT_RECEIVED} uDDS_ON_DATA_RECEIVED; //flags for Subscribers


typedef struct Topic_s {
    int    		topicID;
    struct Topic_s *next;
}Topic;

typedef struct DomainParticipan_s {
    int    		uDDS_DomainID;
    //Topic		topic;
    struct DomainParticipan_s *next;
}DomainParticipan;

//typedef DomainParticipan *dNodo;

typedef struct uDDS_GDS_node_s {
    uDDS_NODE_TYPE 	uDDS_node_type; //Publisher or Subscriber
    int    		uDDS_DomainID; 
    int    		uDDS_node_typeID;//Publisher ID or Subscriber ID
    int 		topicID;
    void        *inicio;
    int         size;
    char      uDDS_error[255];
}uDDS_GDS_node;


/////////////////hipervisor

typedef struct _nodo {
   char *valor;
   struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;

/* Funciones con colas: */

void Anadir(pNodo *primero, pNodo *ultimo, char *v);
char* Leer(pNodo *primero, pNodo *ultimo);
int nomain();








#define MAX 50
#define MAXFIFO 500

typedef enum FIFOS{VACIA, MEDIO, LLENA}  Estado;

struct Publicador {
    int idPUB;
};

struct Subscriptor {
  int idSUB;
};

struct Fifo {
  char dato;
};

struct Topicos {
    int id;
    struct Publicador pub[MAX];
    struct Subscriptor  sub[MAX];
    struct Fifo fifo[MAXFIFO];
    int entrada;
    int salida;
    Estado estado;
};

struct Dominios {
  int id;
  struct Topicos topic[MAX];
};

struct  GDS {
  struct Dominios dom[MAX];
};



#endif