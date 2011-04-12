##########################################################################
#
#	Make include for lwIP/src/ports/lm3s
#	
#   Platform: MPOS rev.2.3
#
#   www.thumbos.com
#
##########################################################################

# local sources
local_as_src-y	:=
local_c_src-y 	:=
local_cpp_src-y	:=
local_h_src-y 	:=

local_c_src-y 	+= perf.c sys_arch.c 

local_cpp_src-y	+= lwip_drv.cpp

local_h_src-y 	+= lwip_drv.h

#updating global variables
as_sources 	+= $(call changepath,$(local_as_src-y))
c_sources  	+= $(call changepath,$(local_c_src-y))
cpp_sources += $(call changepath,$(local_cpp_src-y))
h_sources  	+= $(call changepath,$(local_h_src-y))


#add current directory to include path
inc_dirs += $(subdirectory)

#submodules
local_modules-y := include netif


sub_modules := $(call changepath,$(local_modules-y))
modules += $(sub_modules)

include $(addsuffix /module.mk,$(sub_modules))
