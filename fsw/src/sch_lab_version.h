#ifndef SCH_LAB_VERSION_H
#define SCH_LAB_VERSION_H

/**
 * @file
 *  The SCH Lab Application header file containing version information
 */

/* Development Build Macro Definitions */
#define SCH_LAB_BUILD_NUMBER 16 /*!< Development Build: Number of commits since baseline */
#define SCH_LAB_BUILD_BASELINE \
    "v2.5.0-rc4" /*!< Development Build: git tag that is the base for the current development */

/* Version Macro Definitions */

#define SCH_LAB_MAJOR_VERSION 2 /*!< @brief ONLY APPLY for OFFICIAL releases. Major version number. */
#define SCH_LAB_MINOR_VERSION 3 /*!< @brief ONLY APPLY for OFFICIAL releases. Minor version number. */
#define SCH_LAB_REVISION      0 /*!< @brief ONLY APPLY for OFFICIAL releases. Revision version number. */

/*!
 * @brief Mission revision.
 *
 * Set to 0 on OFFICIAL releases, and set to 255 (0xFF) on development versions.
 * Values 1-254 are reserved for mission use to denote patches/customizations as needed.
 */
#define SCH_LAB_MISSION_REV 0xFF

#define SCH_LAB_STR_HELPER(x) #x /*!< @brief Helper function to concatenate strings from integer macros */
#define SCH_LAB_STR(x)        SCH_LAB_STR_HELPER(x) /*!< @brief Helper function to concatenate strings from integer macros */

/*! @brief Development Build Version Number.
 * @details Baseline git tag + Number of commits since baseline. @n
 * See @ref cfsversions for format differences between development and release versions.
 */
#define SCH_LAB_VERSION SCH_LAB_BUILD_BASELINE "+dev" SCH_LAB_STR(SCH_LAB_BUILD_NUMBER)

/*! @brief Development Build Version String.
 * @details Reports the current development build's baseline, number, and name. Also includes a note about the latest
 * official version. @n See @ref cfsversions for format differences between development and release versions.
 */
#define SCH_LAB_VERSION_STRING                    \
    " SCH Lab DEVELOPMENT BUILD " SCH_LAB_VERSION \
    ", Last Official Release: v2.3.0" /* For full support please use this version */

#endif
