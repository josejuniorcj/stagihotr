/*********************************************************
 **
 ** File  Main_UA_1_LAY_1.c
 **
 ** Automatically generated by SCADE Suite UA Adaptor
 ** Version 19.2 (build 20180628)
 ** 
 ** Date of generation: 2018-11-21T23:06:35
 ** Command line: E:/SCADE/Suite/SCADE/bin/uaadaptor.exe -sdy E:\Projetos\stagiho-tr\Time_1\ExoSkeleton_Display\UserApplication\UserApplication.sdy -n E:\SCADE\Suite\SCADE Display\config\a661_description\a661.xml -outdir E:/Projetos/stagiho-tr/Time_1/ExoSkeleton_Display/UserApplication/Simulation -k E:/Projetos/stagiho-tr/Time_1/ExoSkeleton_Display/UserApplication/Simulation/kcg_trace.xml -o Main_UA_1 -i UserApplication_interface.h -encoding ASCII E:\Projetos\stagiho-tr\Time_1\ExoSkeleton_Display\DefinitionFile\exoSkeleton.sgfx
 *********************************************************/
#include "kcg_sensors.h"
#include "Main_UA_1.h"
#include "Main_UA_1_constants.h"
#include "Main_UA_1_private.h"

/* Perform UA Request for layer 1 */
A661_INTERNAL uaa_size a661_com_A661_CMD_UA_REQUEST_layer_1(buffer_el msg[], 
  outC_Main* scade_ctx,  extern_out_ctx_t * extern_ctx){
  uaa_size offset = 0;
  return offset ;
}

/* Pack messages for layer 1 */
 uaa_size a661_com_layer_1(buffer_el msg[], 
  outC_Main* scade_ctx,  extern_out_ctx_t* extern_ctx){
  uaa_size offset = 0;
  if (scade_ctx->Out_Protocol_OutCMD.Emit2DF ||
  scade_ctx->OutImageReference.Emit2DF){
    LAYER("a661_layer#1");
    offset = 8;
    a661_msg_cmd_header(msg, 1, Main_UA_1_DEFAULT_CONTEXT_NUMBER);
    if (scade_ctx->Out_Protocol_OutCMD.Emit2DF){
      WIDGET("Label1#1");
      offset = offset + a661_com_csp_widget_Label(msg + offset, 1,
        scade_ctx->Out_Protocol_OutCMD.Emit2DF, 10,
        scade_ctx->Out_Protocol_OutCMD.value,
        scade_ctx->Out_Protocol_OutCMD.string_size);
    }
    if (scade_ctx->OutImageReference.Emit2DF){
      WIDGET("pStatic#9");
      offset = offset + a661_com_csp_widget_Picture(msg + offset, 9,
        scade_ctx->OutImageReference.Emit2DF,
        scade_ctx->OutImageReference.Reference);
    }
    WRITE_ULONG(msg + offset, A661_END_BLOCK);
    offset = offset + 4;
    WRITE_ULONG(msg + 4, offset);
  }
  return offset ;
}

/*********************************************************
 ** End of file
 ** End of generation: 2018-11-21T23:06:35
 *********************************************************/

