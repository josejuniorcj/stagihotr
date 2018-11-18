/*********************************************************
 **
 ** File  Main_UA_1.c
 **
 ** Automatically generated by SCADE Suite UA Adaptor
 ** Version 19.2 (build 20180628)
 ** 
 ** Date of generation: 2018-11-17T00:35:36
 ** Command line: C:/Program Files/ANSYS Inc/v192/SCADE/SCADE/bin/uaadaptor.exe -sdy C:\Users\Scade\Downloads\stagihotr-master\stagihotr-master\Time_1\ExoSkeleton_Display\UserApplication\UserApplication.sdy -n C:\Program Files\ANSYS Inc\v192\SCADE\SCADE Display\config\a661_description\a661.xml -outdir C:/Users/Scade/Downloads/stagihotr-master/stagihotr-master/Time_1/ExoSkeleton_Display/UserApplication/Simulation -k C:/Users/Scade/Downloads/stagihotr-master/stagihotr-master/Time_1/ExoSkeleton_Display/UserApplication/Simulation/kcg_trace.xml -o Main_UA_1 -i UserApplication_interface.h -encoding ASCII C:\Users\Scade\Downloads\stagihotr-master\stagihotr-master\Time_1\ExoSkeleton_Display\DefinitionFile\exoSkeleton.sgfx
 *********************************************************/
#include "kcg_sensors.h"
#include "Main_UA_1.h"
#include "Main_UA_1_constants.h"
#include "Main_UA_1_private.h"

/********************************************************************************************
 * Send messages to the A661 server                                                         *
 ********************************************************************************************/
 uaa_size Main_UA_1_send(buffer_el msg[], 
  outC_Main* scade_ctx,  extern_out_ctx_t * extern_ctx){
  uaa_size offset = 0;
  
  offset = offset + a661_com_layer_1(msg + offset, scade_ctx, extern_ctx);
  return offset ;
}

/********************************************************************************************
 * Receive notifications from the A661 server                                               *
 ********************************************************************************************/
uaa_size Main_UA_1_receive(buffer_el buffer[],  uaa_size buffer_size, 
  inC_Main* scade_ctx,  extern_in_ctx_t * extern_ctx){
  uaa_size EvtString_byte_size = 0;
  uaa_size widget_event_structure_current_size = 0;
  uaa_size A661_Run_Time_Command_limit = 0;
  uaa_size root_current_size = 0;
  uaa_size n = 0;
  uaa_size next_n = 0;
  /*  type root */
  switch (buffer[ n ]){
    case A661_BEGIN_BLOCK : 
      root_current_size = READ_ULONG(( buffer + ( 4 + n ) ));
      next_n = ( ( n + root_current_size ) - 4 );
      /*  LayerIdent */
      switch (buffer[ ( 1 + n ) ]){
        case 1 : 
          /*  root */
          n = ( 8 + n );
          A661_Run_Time_Command_limit = ( ( n + root_current_size ) - 12 );
          while(( n < A661_Run_Time_Command_limit )){
            /*  type A661_Run_Time_Command */
            switch (READ_USHORT(( buffer + n ))){
              case A661_NOTIFY_WIDGET_EVENT : 
                widget_event_structure_current_size = READ_USHORT(( buffer + ( 2 + n ) ));
                next_n = ( n + widget_event_structure_current_size );
                /*  WidgetIdent */
                switch (READ_USHORT(( buffer + ( 4 + n ) ))){
                  case 12 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SELECTION : 
                        /*  PushButton_A661_EVT_SELECTION */
                        /*  Notify */
                        scade_ctx->raiseStart = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 11 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_STRING_CONFIRMED : 
                        EvtString_byte_size = READ_USHORT(( buffer + ( 4 + n ) ));
                        /*  EditBoxNumeric_A661_EVT_STRING_CONFIRMED */
                        /*  Notify */
                        scade_ctx->MagnitudeNotification = kcg_true;
                        /*  EvtString */
                        LAYER("  ");
                        WIDGET("  ");
                        PARAMETER(" EvtString ");
                        CHECK_STRING_SIZE(" scade_ctx->walkMagnitude ",
                          EvtString_byte_size,
                          sizeof(scade_ctx->walkMagnitude));
                        a661_assign_string(scade_ctx->walkMagnitude,
                          ( buffer + ( 6 + n ) ), EvtString_byte_size);
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 10 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_STRING_CONFIRMED : 
                        EvtString_byte_size = READ_USHORT(( buffer + ( 4 + n ) ));
                        /*  EditBoxNumeric_A661_EVT_STRING_CONFIRMED */
                        /*  Notify */
                        scade_ctx->StepsNotification = kcg_true;
                        /*  EvtString */
                        LAYER("  ");
                        WIDGET("  ");
                        PARAMETER(" EvtString ");
                        CHECK_STRING_SIZE(" scade_ctx->walkSteps ",
                          EvtString_byte_size, sizeof(scade_ctx->walkSteps));
                        a661_assign_string(scade_ctx->walkSteps,
                          ( buffer + ( 6 + n ) ), EvtString_byte_size);
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 8 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SELECTION : 
                        /*  PushButton_A661_EVT_SELECTION */
                        /*  Notify */
                        scade_ctx->sitStart = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 7 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SELECTION : 
                        /*  PushButton_A661_EVT_SELECTION */
                        /*  Notify */
                        scade_ctx->walkStop = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 6 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SELECTION : 
                        /*  PushButton_A661_EVT_SELECTION */
                        /*  Notify */
                        scade_ctx->walkStart = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  default : break;
                }
                break;
              default : 
                next_n = ( n + READ_USHORT(( buffer + ( 2 + n ) )) );
                n = next_n;
                break;
            }
            n = next_n;
          }
          n = ( 4 + n );
          break;
        default : break;
      }
      break;
    default : break;
  }
  return n ;
}

/********************************************************************************************
 * Clear notifications                                                                      *
 ********************************************************************************************/
void Main_UA_1_receive_clear(inC_Main* scade_ctx, 
  extern_in_ctx_t * extern_ctx){
  scade_ctx->walkStart = kcg_false;
  scade_ctx->walkStop = kcg_false;
  scade_ctx->sitStart = kcg_false;
  scade_ctx->StepsNotification = kcg_false;
  scade_ctx->MagnitudeNotification = kcg_false;
  scade_ctx->raiseStart = kcg_false;
}

/*********************************************************
 ** End of file
 ** End of generation: 2018-11-17T00:35:36
 *********************************************************/

