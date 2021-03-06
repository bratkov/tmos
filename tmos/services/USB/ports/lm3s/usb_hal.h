
#ifndef USB_HAL_H_
#define USB_HAL_H_

#include <tmos.h>
#include <usb_opt.h>
#include <usb_lm3s.h>
#include <usb_drv.h>


#define ENTPOINT_FIFO(hw_base, eptnum) &hw_base->USBFIFO[eptnum]

/**
 * Indicates if the device is running in high or full-speed. Always returns 0
 * since UDP does not support high-speed mode.
 */
#define usb_hal_IsHighSpeed() 0

extern "C" void usb_drv_event(USB_DRV_INFO drv_info, USB_EVENT event);
void usb_drv_reset(USB_DRV_INFO drv_info);
void usb_drv_cancel_hnd(USB_DRV_INFO drv_info, HANDLE hnd);
void usb_drv_start_tx(USB_DRV_INFO drv_info, HANDLE hnd);
void usb_drv_start_rx(USB_DRV_INFO drv_info, HANDLE hnd);
void usb_drv_end_transfers(Endpoint* endpoint, unsigned int status);

bool usb_hal_get_ep_status(USB_DRV_INFO drv_info, uint8_t ept_num, uint16_t* data);
void usb_hal_stall(USB_Type* hw_base, unsigned int ept_num);
void usb_hal_stall_clear(USB_Type* hw_base, unsigned int ept_num);
void usb_hal_device_start(USB_DRV_INFO drv_info);
void usb_hal_ept_reset(USB_DRV_INFO drv_info, unsigned int eptnum);
void usb_hal_ept_config(USB_DRV_INFO drv_info, const USBGenericDescriptor* pDescriptor, unsigned int rindx=0);
void usb_hal_config_fifo(USB_DRV_INFO drv_info);
#if USB_ENABLE_HOST
RES_CODE usb_hal_host_start(USB_DRV_INFO drv_info);
RES_CODE usb_hal_host_bus_reset(USB_DRV_INFO drv_info);
void usb_hal_host_resume(USB_DRV_INFO drv_info);
void usb_hal_host_ept_cfg(USB_DRV_INFO drv_info, const USBEndpointDescriptor* pDescriptor);
#endif

void usb_otg_set_flags(USB_DRV_INFO drv_info, uint32_t flags);
void usb_otg_clr_flags(USB_DRV_INFO drv_info, uint32_t flags);

#endif /* USB_HAL_H_ */
