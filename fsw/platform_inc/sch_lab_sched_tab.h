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
** File: sch_lab_sched_tab.h
**
** Purpose: 
**  This file contains the schedule tables for the SCH Lab app.
**  It is intended to go in the platform include directory so the SCH_LAB
**  app source code does not have to be modified.
**
** Notes:
**
*************************************************************************/


#include "cfe_msgids.h"

/*
** Include headers for message IDs here
*/
#include "ci_lab_msgids.h"
#include "to_lab_msgids.h"

#include "sample_app_msgids.h"

#if 0
#include "sc_msgids.h"
#include "hs_msgids.h"
#include "fm_msgids.h"
#include "ds_msgids.h"
#include "lc_msgids.h"
#endif

/*
** Defines
*/
#define SCH_LAB_END_OF_TABLE          0
#define SCH_LAB_MAX_SCHEDULE_ENTRIES  32

/*
** Typedefs
*/
typedef struct
{
    CFE_SB_MsgId_t  MessageID;  /* Message ID for the table entry */
    uint32          PacketRate; /* Rate: Send packet every N seconds */
    uint32          Counter;    /* Counter used to send packet */
     
} SCH_LAB_ScheduleTable_t;


/*
** SCH Lab schedule table
** When populating this table:
**  1. Make sure the table is terminated by the SCH_LAB_END_OF_TABLE entry
**  2. You can have commented out entries, but a zero MID will terminate the table processing, 
**      skipping the remaining entries.
**  3. If the table grows too big, increase SCH_LAB_MAX_SCHEDULE_ENTRIES
*/
SCH_LAB_ScheduleTable_t SCH_LAB_ScheduleTable[SCH_LAB_MAX_SCHEDULE_ENTRIES] = 
{ 
     { CFE_ES_SEND_HK_MID,   4, 0 },  /* Housekeeping requests go out every 4 seconds */
     { CFE_EVS_SEND_HK_MID,  4, 0 },
     { CFE_TIME_SEND_HK_MID, 4, 0 },
     { CFE_SB_SEND_HK_MID,   4, 0 },
     { CFE_TBL_SEND_HK_MID,  4, 0 },
     
     { CI_LAB_SEND_HK_MID,   4, 0 },
     { TO_LAB_SEND_HK_MID,   4, 0 },
     { SAMPLE_APP_SEND_HK_MID,   4, 0 },

#if 0
     { SC_SEND_HK_MID,       4, 0 },
     { SC_1HZ_WAKEUP_MID,    1, 0 },  /* Example of a 1hz packet */
     { HS_SEND_HK_MID,       4, 0 },
     { FM_SEND_HK_MID,       4, 0 },
     { DS_SEND_HK_MID,       4, 0 },
     { LC_SEND_HK_MID,       4, 0 },

#endif

     { SCH_LAB_END_OF_TABLE, 0, 0 }
};

