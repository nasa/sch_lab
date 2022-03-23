/**
 * @file
 *  This file contains the schedule tables for the SCH Lab app.
 *  It is intended to go in the platform include directory so the SCH_LAB
 *  app source code does not have to be modified.
 */
#ifndef SCH_LAB_TABLE_H
#define SCH_LAB_TABLE_H

#include "cfe_sb_extern_typedefs.h" /* for CFE_SB_MsgId_t */
#include "cfe_msg_api_typedefs.h"   /* For CFE_MSG_FcnCode_t */
#include "cfe_msgids.h"

/*
** Defines
*/
#define SCH_LAB_END_OF_TABLE         0
#define SCH_LAB_MAX_SCHEDULE_ENTRIES 32
#define SCH_TBL_DEFAULT_FILE         "/cf/sch_lab_table.tbl"

/*
** Typedefs
*/
typedef struct
{
    CFE_SB_MsgId_t    MessageID;  /* Message ID for the table entry */
    uint32            PacketRate; /* Rate: Send packet every N ticks */
    CFE_MSG_FcnCode_t FcnCode;    /* Command/Function code to set */
} SCH_LAB_ScheduleTableEntry_t;

typedef struct
{
    uint32                       TickRate; /* Ticks per second to configure for timer (0=default) */
    SCH_LAB_ScheduleTableEntry_t Config[SCH_LAB_MAX_SCHEDULE_ENTRIES];
} SCH_LAB_ScheduleTable_t;

#endif
