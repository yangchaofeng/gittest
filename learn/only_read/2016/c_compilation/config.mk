# 指定库的运行平台
DEVICETYPE = EM_ODM_A091

ifeq ($(DEVICETYPE),EM_ODM_A01)
CFG_YANG_TEST=y
CPUARCH = AT91SAM9G20
CFG_USART_LIB=y
CFG_ADC_LIB=y
CFG_GPIO_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_TEMPER_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
CFG_USERGPIO_LIB=y
else ifeq ($(DEVICETYPE),EM_BJHTFD_ODM)
CPUARCH = AT91SAM9G45
CFG_USART_LIB=y
CFG_ADC_LIB=y
CFG_USERGPIO_LIB=y
CFG_DAC_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_HIGHTIMER_LIB=y
CFG_TEMPER_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
CFG_KBD_LIB=y
else ifeq ($(DEVICETYPE),EM_EC2012)
CPUARCH = AT91SAM9G20
CFG_USART_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_HIGHTIMER_LIB=y
CFG_TEMPER_LIB=y
CFG_SERIALID_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
#
else ifeq ($(DEVICETYPE),EM_EC4210)
CPUARCH = AT91SAM9G20
CFG_USART_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_TEMPER_LIB=y
CFG_SERIALID_LIB=y
CFG_USERGPIO_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
#
else ifeq ($(DEVICETYPE),EM_EC2212_EX)
CPUARCH = AT91SAM9G20
CFG_USART_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_TEMPER_LIB=y
CFG_SERIALID_LIB=y
CFG_GPIO_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
#
else ifeq ($(DEVICETYPE),EM_BJTKY_ODM)
CPUARCH = AT91SAM9263
CFG_USART_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_GPIO_LIB=y
CFG_USERGPIO_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
else ifeq ($(DEVICETYPE),EM_BEIJZJ_ODM)
CPUARCH = AT91SAM9G20
CFG_USART_LIB=y
CFG_ADC_LIB=y
CFG_USERGPIO_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
else ifeq ($(DEVICETYPE),EM_BEIJQL_ODM)
CPUARCH = AT91SAM9X5
CFG_USART_LIB=y
CFG_GPIO_LIB=y
CFG_USERGPIO_LIB=y
CFG_DATETIM_LIB=y
CFG_TIMER_LIB=y
CFG_WDG_LIB=y
CFG_MISCS_LIB=y
CFG_TEMPER_LIB=y
CFG_HIGHTIMER_LIB=y
CFG_SPI_ADC_LIB=y
CFG_DAC_LIB=y
else
#串口操作支持函数
CFG_USART_LIB=y
#ADC操作支持函数
CFG_ADC_LIB=y
#用户层IO操作支持函数
CFG_USERGPIO_LIB=y
endif
