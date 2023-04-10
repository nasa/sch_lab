cmake_minimum_required(VERSION 3.5)
project(CFS_SCH_LAB C)

# These references are specifically needed for the table build
# it is easiest to add them as directory properties so they won't
# be considered include directories for SCH_LAB itself.
include_directories(
    $<TARGET_PROPERTY:ci_lab,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:to_lab,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:sample_app,INTERFACE_INCLUDE_DIRECTORIES>
)

# Create the app module
add_cfe_app(sch_lab fsw/src/sch_lab_app.c)
add_cfe_tables(sch_lab fsw/tables/sch_lab_table.c)

target_include_directories(sch_lab PUBLIC
    fsw/mission_inc
    fsw/platform_inc
)
