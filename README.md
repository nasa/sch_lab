# Core Flight System : Framework : App : Scheduler Lab

This repository contains NASA's Scheduler Lab (sch_lab), which is a framework component of the Core Flight System.

This lab application is a non-flight packet scheduler application for the cFS Bundle. It is intended to be located in the `apps/sch_lab` subdirectory of a cFS Mission Tree.  The Core Flight System is bundled at https://github.com/nasa/cFS (which includes sch_lab as a submodule), which includes build and execution instructions.

sch_lab is a simple packet scheduler application with a one second resoluton.

To change the list of packets that sch_lab sends out, edit the schedule table located in the platform include file:
fsw/platform_inc/sch_lab_sched_tab.h

## Release Notes

sch_lab version 2.2.0a is released as part of cFE 6.6.0a under the Apache 2.0 license, see [LICENSE](LICENSE-18128-Apache-2_0.pdf).

Note the old GSFC Build toolset is deprecated (fsw/for_build/Makefile) in favor of cmake (CMakeLists.txt)

## Known issues

As a lab application, extensive testing is not performed prior to release and only minimal functionality is included.

## Getting Help

For best results, submit issues:questions or issues:help wanted requests at https://github.com/nasa/cFS.

Official cFS page: http://cfs.gsfc.nasa.gov

Auto build status: [![Build Status](https://travis-ci.com/travis-r-wheatley/sch_lab.svg?branch=master)](https://travis-ci.com/travis-r-wheatley/sch_lab)
