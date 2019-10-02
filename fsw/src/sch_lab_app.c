/************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.6"
**
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
** File: sch_lab_app.c
**
** Purpose: 
**  This file contains the source code for the SCH lab application
**
** Notes:
**
*************************************************************************/

/*
** Include Files
*/
#include "cfe.h"
#include "cfe_sb.h"
#include "osapi.h"
#include "cfe_es.h"
#include "cfe_error.h"

#include "sch_lab_perfids.h"
#include "sch_lab_version.h"

/*
** SCH Lab Schedule table from the platform inc directory
*/
#include "sch_lab_sched_tab.h"

/*
** Global Variables
*/
CFE_SB_CmdHdr_t          SCH_CmdHeaderTable[SCH_LAB_MAX_SCHEDULE_ENTRIES];
CFE_TBL_Handle_t         TblHandles;
SCH_LAB_ScheduleTable_t  *MySchTBL;

CFE_SB_Msg_t             *SCH_CmdPipePktPtr;
CFE_SB_PipeId_t          SCH_CmdPipe;

/*
** AppMain
*/
void SCH_Lab_AppMain(void)
{
    int              i;
    uint32           SCH_OneHzPktsRcvd = 0;
    uint32           Status = CFE_SUCCESS;
    uint32           RunStatus = CFE_ES_APP_RUN;

    CFE_ES_PerfLogEntry(SCH_MAIN_TASK_PERF_ID);

    CFE_ES_RegisterApp();

    Status = SCH_LAB_AppInit();
    if ( Status != CFE_SUCCESS )
    {
        CFE_ES_WriteToSysLog("SCHEULE APP: Error Initializing RC = 0x%08X\n", Status);

    } 
   
    /*
    ** Manage Table 
    */
    Status = CFE_TBL_Manage(TblHandles);  
    if ( Status != CFE_SUCCESS )
    {
        CFE_ES_WriteToSysLog("SCHEULE APP: Error managing table  RC = 0x%08X\n", Status);
        CFE_TBL_ReleaseAddress(TblHandles);

    }  

    /* Loop Forever */
    while (CFE_ES_RunLoop(&RunStatus) == TRUE)
    {
        CFE_ES_PerfLogExit(SCH_MAIN_TASK_PERF_ID);

        /* Pend on receipt of 1Hz packet */
        Status = CFE_SB_RcvMsg(&SCH_CmdPipePktPtr,SCH_CmdPipe,CFE_SB_PEND_FOREVER);

        CFE_ES_PerfLogEntry(SCH_MAIN_TASK_PERF_ID);

        if(Status == CFE_SUCCESS)
        {
            SCH_OneHzPktsRcvd++;
            /*
            ** Process table every second, sending packets that are ready 
            */
            for (i = 0; i < SCH_LAB_MAX_SCHEDULE_ENTRIES; i++) 
            {
                if ( MySchTBL->MessageID[i] != SCH_LAB_END_OF_TABLE )
                { 
                      MySchTBL->Counter[i]++;
                      if (MySchTBL->Counter[i] >= MySchTBL->PacketRate[i] )
                      {
                          MySchTBL->Counter[i] = 0;
                          CFE_SB_SendMsg((CFE_SB_MsgPtr_t)&SCH_CmdHeaderTable[i]);
                      }
                } 
                else
                {
                   break;
                }
            }
        }

    }/* end while */
    
    /*
    ** Release the table
    */
    Status = CFE_TBL_ReleaseAddress(TblHandles);
    if ( Status != CFE_SUCCESS )
    {
        CFE_ES_WriteToSysLog("SCHEULE APP: Error Releasing Table \
                              SCH_LAB_SchTbl, RC = 0x%08X\n", Status);

    }

    CFE_ES_ExitApp( Status );
    
}/* end SCH_Lab_AppMain */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
/*                                                                 */ 
/* SCH_LAB_AppInit() -- initialization                                     */ 
/*                                                                 */ 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SCH_LAB_AppInit(void)
{ 
    int              i;
    int32            Status;

    /*
    ** Register tables with cFE and load default data
    */
    Status = CFE_TBL_Register(&TblHandles, 
                              "SCH_LAB_SchTbl",
                              sizeof(SCH_LAB_ScheduleTable_t), 
                              CFE_TBL_OPT_DEFAULT, 
                              &SCH_LAB_TblValidation);
    if ( Status != CFE_SUCCESS )
    {
        CFE_ES_WriteToSysLog("SCHEULE APP: Error Registering \
                              SCH_LAB_SchTbl, RC = 0x%08X\n", Status);

        return ( Status );
    }
    else
    {
        /*
        ** Loading Table
        */
        Status = CFE_TBL_Load(TblHandles, CFE_TBL_SRC_FILE, SCH_TBL_DEFAULT_FILE);
        if ( Status != CFE_SUCCESS )
        {
            CFE_ES_WriteToSysLog("SCHEULE APP: Error Loading Table \
                                  SCH_LAB_SchTbl, RC = 0x%08X\n", Status);
            CFE_TBL_ReleaseAddress(TblHandles);

            return ( Status );
        }
    }

    /*
    ** Get Table Address
    */ 
    Status = CFE_TBL_GetAddress((void **)&MySchTBL, TblHandles);
    if ( Status != CFE_TBL_INFO_UPDATED )
    {
        CFE_ES_WriteToSysLog("SCHEULE APP: Error Getting Table's Address \
                              SCH_LAB_SchTbl, RC = 0x%08X\n", Status);

        return ( Status );
    }
    
    /*
    ** Initialize the command headers
    */
    for (i = 0; i < SCH_LAB_MAX_SCHEDULE_ENTRIES; i++) 
    {
         if ( MySchTBL->MessageID[i] != SCH_LAB_END_OF_TABLE )
         {   
              CFE_SB_InitMsg(&SCH_CmdHeaderTable[i],
                              MySchTBL->MessageID[i],
                              sizeof(CFE_SB_CmdHdr_t), TRUE);
         } 
         else
         {
              break;
         }
    }

    /* Create pipe and subscribe to the 1Hz pkt */
    Status = CFE_SB_CreatePipe(&SCH_CmdPipe,8,"SCH_LAB_CMD_PIPE");
    if ( Status != CFE_SUCCESS )
    {
       OS_printf("SCH Error creating pipe!\n");
    }
       
    Status = CFE_SB_Subscribe(CFE_TIME_1HZ_CMD_MID,SCH_CmdPipe);
    if ( Status != CFE_SUCCESS )
    {
       OS_printf("SCH Error subscribing to 1hz!\n");
    }
    
    OS_printf ("SCH Lab Initialized.  Version %d.%d.%d.%d\n",
                SCH_LAB_MAJOR_VERSION,
                SCH_LAB_MINOR_VERSION, 
                SCH_LAB_REVISION, 
                SCH_LAB_MISSION_REV);

    return( CFE_SUCCESS );    

}/*End of AppInit*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
/*                                                                 */ 
/* SCH_LAB_TblValidation() - Validate Table                             */ 
/*                                                                 */ 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 SCH_LAB_TblValidation(void *MySchTBL)
{

    /*Write Validation Code Here*/

    return( CFE_SUCCESS );
}/*End of SchTblValidation*/

