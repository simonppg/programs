#include "middleware.h"
#include <stdio.h>

struct GDS gds = 
    {
        .dom =
        {
            [0] =
            {
                .id = 1,
                .topic =
                {
                    [0] =
                    {
                        .id = 1,
                        .pub =
                        {
                            [0] =
                            {
                                .idPUB = 1
                            },
                        },
                        .sub =
                        {
                            [0] =
                            {
                                .idSUB = 2
                            },

                        },
                    },
                },
            },
        },
    };

int main(int argc, char *argv[])
{

    Datos DatosDom1, DatosDom2;
    initDataTopic(&DatosDom1);
    initDataTopic(&DatosDom2);

    DatosDom1.StringDato = "DatosDom1";
    DatosDom1.IntDato = 1;
    DatosDom1.DoubleDato = 8.655896589651253585525;
    DatosDom1.FloatDato = 145.655896999;
    DatosDom1.LongIntDato = 1234567891; //no sirve con signo '-' (negativo) al serializar revisar

    struct uDDS_GDS_node_s pub, sub;
    pub.uDDS_node_type = PUB;
    pub.uDDS_DomainID = 1; 
    pub.uDDS_node_typeID = 1;
    pub.topicID = 1;
    pub.inicio = &DatosDom1;
    pub.size = sizeof(struct Datos_s);

    sub.uDDS_node_type = SUB;
    sub.uDDS_DomainID = 1;
    sub.uDDS_node_typeID = 2;
    sub.topicID = 1;
    sub.inicio = &DatosDom2;
    sub.size = sizeof(struct Datos_s);
    
    init_GDS(&gds);


    publicar(&pub,&gds);
    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    //pintar_GDS(&gds);

    //showDataTopic(DatosDom1);
//    showDataTopic(DatosDom2);


    /*
    pintar_GDS(&gds);
    DatosDom1.IntDato = 2;

    showDataTopic(DatosDom1);
    showDataTopic(DatosDom2);

    publicar(&pub,&gds);
    pintar_GDS(&gds);
    DatosDom1.IntDato = 3;

    showDataTopic(DatosDom1);
    showDataTopic(DatosDom2);

    publicar(&pub,&gds);
    pintar_GDS(&gds);
    
    pintar_GDS(&gds);
    DatosDom1.IntDato = 4;
    
    showDataTopic(DatosDom1);
    showDataTopic(DatosDom2);


    subscribir(&sub,&gds);
    pintar_GDS(&gds);
    showDataTopic(DatosDom1);
    showDataTopic(DatosDom2);

   publicar(&pub,&gds);

    subscribir(&sub,&gds);
    pintar_GDS(&gds);*/
    showDataTopic(DatosDom1);
    showDataTopic(DatosDom2);

    printf("\nError: %s",sub.uDDS_error);









/*


    pintar_GDS(&gds);
    printf("\n");

    struct uDDS_GDS_node_s pub,sub;
    ////////////////////////////// publicadores
    pub.uDDS_node_type = PUB;
    pub.uDDS_DomainID = 1; 
    pub.uDDS_node_typeID = 1;
    pub.topicID = 1;

    sub.uDDS_node_type = SUB;
    sub.uDDS_DomainID = 1;
    sub.uDDS_node_typeID = 7;
    sub.topicID = 1;

    subscribir(&sub,&gds);
    pintar(&sub);

    copiar(pub.uDDS_Serial_data,"#111$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);
    copiar(pub.uDDS_Serial_data,"#222$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);
    copiar(pub.uDDS_Serial_data,"#333$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);
    copiar(pub.uDDS_Serial_data,"#444$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);
    copiar(pub.uDDS_Serial_data,"#555$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);
    copiar(pub.uDDS_Serial_data,"#666$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);
    copiar(pub.uDDS_Serial_data,"#777$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);*/

/*
    subscribir(&sub,&gds);
    pintar(&sub);
    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);
    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);
    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);
    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);

    copiar(pub.uDDS_Serial_data,"#111$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);

    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);



    copiar(pub.uDDS_Serial_data,"#222$",5);
    publicar(&pub,&gds);
    pintar_GDS(&gds);

    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);

    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);
    pintar_GDS(&gds);
    subscribir(&sub,&gds);
    pintar(&sub);*/

    /*pub.uDDS_node_type = PUB;
    pub.uDDS_DomainID = 1; 
    pub.uDDS_node_typeID = 2;
    pub.uDDS_Serial_data = "#pub_2$";
    pub.topicID = 2;
    publicar(&pub,&gds);
    pub.uDDS_Serial_data = "#pub_2_valor$";
    publicar(&pub,&gds);

    pub.uDDS_node_type = PUB;
    pub.uDDS_DomainID = 1; 
    pub.uDDS_node_typeID = 3;
    pub.uDDS_Serial_data = "#pub 3$";
    pub.topicID = 3;
    publicar(&pub,&gds);

    pub.uDDS_node_type = PUB;
    pub.uDDS_DomainID = 2; 
    pub.uDDS_node_typeID = 4;
    pub.uDDS_Serial_data = "#pub 4$";
    pub.topicID = 1;
    publicar(&pub,&gds);

    pub.uDDS_node_type = PUB;
    pub.uDDS_DomainID = 2; 
    pub.uDDS_node_typeID = 5;
    pub.uDDS_Serial_data = "#pub 5$";
    pub.topicID = 2;
    publicar(&pub,&gds);

    pub.uDDS_node_type = PUB;
    pub.uDDS_DomainID = 2; 
    pub.uDDS_node_typeID = 6;
    pub.uDDS_Serial_data = "#pub 6$";
    pub.topicID = 3;
    publicar(&pub,&gds);*/
    

    //////////////////////////////// subscriptores
    
    /*subscribir(&sub,&gds);
    pintar(&sub);
    subscribir(&sub,&gds);
    pintar(&sub);
    subscribir(&sub,&gds);
    pintar(&sub);
    subscribir(&sub,&gds);
    pintar(&sub);
    subscribir(&sub,&gds);
    pintar(&sub);
    subscribir(&sub,&gds);
    pintar(&sub);
    subscribir(&sub,&gds);
    pintar(&sub);
    subscribir(&sub,&gds);
    pintar(&sub);*/
    //subscribir(&sub,&gds);
    //pintar(&sub);
    //subscribir(&sub,&gds);
    //pintar(&sub);

    //pintar_GDS(&gds);
    printf("\n");
    return 0;
}


