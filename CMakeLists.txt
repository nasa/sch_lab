cmake_minimum_required(VERSION 3.5)
project(CFS_SCH_LAB C)

include_directories(fsw/inc)
include_directories(${ci_lab_MISSION_DIR}/fsw/inc)
include_directories(${to_lab_MISSION_DIR}/fsw/inc)
include_directories(${sample_app_MISSION_DIR}/fsw/inc)

# Create the app module
add_cfe_app(sch_lab fsw/src/sch_lab_app.c)
add_cfe_tables(sch_lab_table fsw/tables/sch_lab_table.c)
