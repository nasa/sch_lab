/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

#include "cfe_tbl_filedef.h" /* Required to obtain the CFE_TBL_FILEDEF macro definition */
#include "sch_lab_tbl.h"
#include "cfe_sb_api_typedefs.h" /* Required to use the CFE_SB_MSGID_WRAP_VALUE macro */

/* This is for the standard set of CFE core app MsgID values */
#include "cfe_msgids.h"

/*
** SCH Lab schedule table
** When populating this table:
**  1. The entire table is processed (SCH_LAB_MISSION_MAX_SCHEDULE_ENTRIES) but entries with a
**     packet rate of 0 are skipped
**  2. You can have commented out entries or entries with a packet rate of 0
**  3. If the table grows too big, increase SCH_LAB_MISSION_MAX_SCHEDULE_ENTRIES
*/

/*
** Cross-app SEND_HK MsgId values (numeric) to avoid cross-app include path issues.
** CMD base = 0x1800, OR'd with topic ID from each app's topicids.h
**
** TO_LAB:     SEND_HK topic=0x81 → CMD MID=0x1881
** CI_LAB:     SEND_HK topic=0x85 → CMD MID=0x1885
** SAMPLE_APP: SEND_HK topic=0x83 → CMD MID=0x1883
*/
#define NUMERIC_TO_LAB_SEND_HK_MID      0x1881
#define NUMERIC_CI_LAB_SEND_HK_MID      0x1885
#define NUMERIC_SAMPLE_APP_SEND_HK_MID  0x1883

SCH_LAB_ScheduleTable_t Schedule = {
    .TickRate = 100,
    .Config   = {
        /* cFE core HK wakeups - trigger each core service to send housekeeping */
        {CFE_SB_MSGID_WRAP_VALUE(CFE_ES_SEND_HK_MID), 100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_EVS_SEND_HK_MID), 100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_SB_SEND_HK_MID), 100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_TBL_SEND_HK_MID), 100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(CFE_TIME_SEND_HK_MID), 100, 0},

        /* Lab app HK wakeups */
        {CFE_SB_MSGID_WRAP_VALUE(NUMERIC_TO_LAB_SEND_HK_MID), 100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(NUMERIC_CI_LAB_SEND_HK_MID), 100, 0},
        {CFE_SB_MSGID_WRAP_VALUE(NUMERIC_SAMPLE_APP_SEND_HK_MID), 100, 0},

        /* End-of-table marker */
        {CFE_SB_MSGID_RESERVED, 0, 0},
    }
};

/*
** The macro below identifies:
**    1) the data structure type to use as the table image format
**    2) the name of the table to be placed into the cFE Table File Header
**    3) a brief description of the contents of the file image
**    4) the desired name of the table image binary file that is cFE compatible
*/
CFE_TBL_FILEDEF(Schedule, SCH_LAB.Schedule, Schedule Lab MsgID Table, sch_lab_table.tbl)
