// Autor: Kfouri baseado no codigo de Marcelo Paiva
// Data: 26/10/2018
// Objetivo: Integracao do CDS SCADE R18 com o Kafka, topico: erlun

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kcg_types.h"

int send2Kafka( char *Send )
{
    char cmd[4], cmdKafka[200]="python E:\\Projetos\\stagihotr\Time_1\\ExoSkeleton_Display\\Integration\\send2Bridge.py";
    strncpy(cmd, Send, 4);
    if(strncmp(cmd, " ", 1) != 0)
    {
	    strcat(cmdKafka, cmd);
	    system(cmdKafka);	    
    }
    return 0;
}
