![Static Analysis](https://github.com/nasa/sch_lab/workflows/Static%20Analysis/badge.svg)
![Format Check](https://github.com/nasa/sch_lab/workflows/Format%20Check/badge.svg)

# Core Flight System : Framework : App : Scheduler Lab

This repository contains NASA's Scheduler Lab (sch_lab), which is a framework component of the Core Flight System.

This lab application is a non-flight packet scheduler application for the cFS Bundle. It is intended to be located in the `apps/sch_lab` subdirectory of a cFS Mission Tree. The Core Flight System is bundled at <https://github.com/nasa/cFS> (which includes sch_lab as a submodule), which includes build and execution instructions.

sch_lab is a simple packet scheduler application with a one second resoluton.

To change the list of packets that sch_lab sends out, edit the schedule table located in the platform include file: fsw/platform_inc/sch_lab_sched_tab.h

## Version History

### Development Build: v2.4.0-rc1+dev32

- Removes app registration call, `CFE_ES_RegisterApp()` since applications do not need to register themselves.
- See <https://github.com/nasa/sch_lab/pull/76>

### Development Build: v2.4.0-rc1+dev26

- Fix #67, Update sequence count in transmitted messages
- Fix #69, Add Testing Tools to the Security Policy
- See <https://github.com/nasa/sch_lab/pull/71>

### Development Build: 2.4.0-rc1+dev12

- Aligns messages according to changes in cFE <https://github.com/nasa/cFE/issues/1009>. Uses the "raw" message cmd/tlm types in definition
- See <https://github.com/nasa/sch_lab/pull/59>

### Development Build: 2.4.0-rc1+dev9

- Update to use MSG module. Replaces deprecated SB APIs with MSG
- See <https://github.com/nasa/sch_lab/pull/58>

### Development Build: 2.4.0-rc1+dev6

- Adds header guard (the other warning on the ticket was already resolved)
- See <https://github.com/nasa/sch_lab/pull/53>

### Development Build: 2.4.0-rc1+dev2

- Reorganize the sch_lab table so it matches the sample_app usage and format.
- See <https://github.com/nasa/sch_lab/pull/52>

### Development Build: 2.3.0+dev37

- Fixes schedule table documentation
- Add baseline and build number to version reporting
- See <https://github.com/nasa/sch_lab/pull/48>

### Development Build: 2.3.7

- Apply the CFE_SB_MsgIdToValue() and CFE_SB_ValueToMsgId() routines where compatibility with an integer MsgId is necessary - syslog prints, events, compile-time MID #define values.
- See <https://github.com/nasa/sch_lab/pull/41>

### Development Build: 2.3.6

- Apply the CFE_SB_MsgIdToValue() and CFE_SB_ValueToMsgId() routines where compatibility with an integer MsgId is necessary - syslog prints, events, compile-time MID #define values.
- See <https://github.com/nasa/sch_lab/pull/39>

### Development Build: 2.3.5

- Improved table handling
- sch_lab now builds on Raspbian OS
- Minor updates (see <https://github.com/nasa/sch_lab/pull/36>)

### Development Build: 2.3.4

- Fix for clean build with OMIT_DEPRECATED
- Minor updates (see <https://github.com/nasa/sch_lab/pull/35>)

  ### Development Build: 2.3.3

- Minor updates (see <https://github.com/nasa/sch_lab/pull/28>)

  ### Development Build: 2.3.2

- Table definition include update (see <https://github.com/nasa/sch_lab/pull/18>)

  ### Development Build: 2.3.1

- Minor updates (see <https://github.com/nasa/sch_lab/pull/16>)

### _**OFFICIAL RELEASE: 2.3.0 - Aquila**_

- Minor updates (see <https://github.com/nasa/sch_lab/pull/13>)
- Not backwards compatible with OSAL 4.2.1
- Released as part of cFE 6.7.0, Apache 2.0

### _**OFFICIAL RELEASE: 2.2.0a**_

- Released as part of cFE 6.6.0a, Apache 2.0

## Known issues

As a lab application, extensive testing is not performed prior to release and only minimal functionality is included.

## Getting Help

For best results, submit issues:questions or issues:help wanted requests at <https://github.com/nasa/cFS>.

Official cFS page: <http://cfs.gsfc.nasa.gov>
