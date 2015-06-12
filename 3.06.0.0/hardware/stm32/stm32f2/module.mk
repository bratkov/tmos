##########################################################################
#
#	Make include for hardware/stm32/stm32f2
#	
#   Platform: MPOS rev.3.0	
#
#
##########################################################################

# local sources
local_as_src-y	:=  
local_c_src-y 	:= 
local_cpp_src-y	:= 
local_h_src-y 	:= 

local_cpp_src-y	+= gpio_f2.cpp rcc_f2.cpp usart_f2.cpp dma_f2.cpp rtc_f2.cpp
 
local_h_src-y 	+= series_inc.h series_cpp.h gpio_f2.h rcc_f2.h flash_f2.h
local_h_src-y 	+= dbgmcu_f2.h usart_f2.h dma_f2.h pwr_f2.h rtc_f2.h adc_f2.h
local_h_src-y 	+= tim_f2.h

#updating global variables
as_sources 	+= $(call changepath,$(local_as_src-y))
c_sources  	+= $(call changepath,$(local_c_src-y))
cpp_sources += $(call changepath,$(local_cpp_src-y))
h_sources  	+= $(call changepath,$(local_h_src-y))

#add current directory to include path
inc_dirs += $(subdirectory) 

#submodules
local_modules-y :=  $(CFG_MCU)

sub_modules := $(call changepath,$(local_modules-y))
modules += $(sub_modules)

include $(addsuffix /module.mk,$(sub_modules))