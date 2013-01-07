/*
 * usb_svc.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: miro
 */

#include <tmos.h>
#include <usb_svc.h>
#include <usb_hal.h>

void usb_svc_stall_hook(USB_DRV_INFO drv_info, HANDLE hnd)
{
	unsigned char eptnum = hnd->mode0;
    Endpoint *endpoint = &drv_info->drv_data->endpoints[eptnum];

    eptnum |= 0x80; // ENDPOINT_DIRECTION_IN

    // Check that endpoint is in Idle state
    if (endpoint->epd_in.epd_state != ENDPOINT_STATE_IDLE)
    {
    	TRACE_USB(" Stall(%d): locked", eptnum);
    } else
    {
	    TRACE_USB(" Stall(%d)", eptnum);
	    usb_hal_stall(drv_info->hw_base, eptnum);
    }

}

/**
 * Causes the given endpoint to acknowledge the next packet it receives
 * with a STALL handshake
*/
void usb_svc_stall(HANDLE hnd)
{
	// note: Stall will be performed for the last endpoint used by this handle!!
	hnd->dst.as_voidptr = (void*)usb_svc_stall_hook;
	hnd->hcontrol(DCR_HANDLE);
}

//-----------------------------------------------------------------------------
void usb_svc_setconfiguration_hook(USB_DRV_INFO drv_info, HANDLE hnd)
{
	USB_DRIVER_DATA* drv_data = drv_info->drv_data;
	unsigned char cfgnum = hnd->src.as_int;

	TRACE_USB(" SetCfg(%d)", cfgnum);

    // If the configuration number if non-zero, the device enters the
    // Configured state
    if (cfgnum != 0)
    {
        drv_data->usb_state = USB_STATE_CONFIGURED;
    }
    // If the configuration number is zero, the device goes back to the Address
    // state
    else
    {
        drv_data->usb_state = USB_STATE_ADDRESS;

        // Abort all transfers
    	for(int i= 1; i<USB_NUMENDPOINTS; i++)
    	{
    		usb_ept_reset(drv_info, i);
    	}
    }
	drv_data->device.cfgnum = cfgnum;
}

/**
 * Sets the current device configuration
*/
void usb_svc_setconfiguration(HANDLE hnd, unsigned int cfg)
{
	// note: Stall will be performed for the last endpoint used by this handle!!
	hnd->dst.as_voidptr = (void*)usb_svc_setconfiguration_hook;
	hnd->src.as_int = cfg;
	hnd->hcontrol(DCR_HANDLE);
}

//-----------------------------------------------------------------------------
void usb_svc_configendpoints_hook(USB_DRV_INFO drv_info, HANDLE hnd)
{
	const USBGenericDescriptor* endpoint;


	endpoint = (const USBGenericDescriptor*)hnd->src.as_int;

	usb_hal_ept_config(drv_info, endpoint);
}

/**
 * Sets the current device configuration
*/
void usb_svc_configendpoint(HANDLE hnd, const USBGenericDescriptor* ds)
{
	// note: Stall will be performed for the last endpoint used by this handle!!
	hnd->dst.as_voidptr = (void*)usb_svc_configendpoints_hook;
	hnd->src.as_cvoidptr = ds;
	hnd->hcontrol(DCR_HANDLE);
}

//-----------------------------------------------------------------------------
void usb_svc_setaddress_hook(USB_DRV_INFO drv_info, HANDLE hnd)
{
	USB_DRIVER_DATA* drv_data = drv_info->drv_data;
	uint32_t address = hnd->src.as_int;
	USB_TypeDef* otg = drv_info->hw_base;

	TRACE_USB(" SetAddr(%02X)", address);

    // If the address is 0, the device returns to the Default state
    if (address == 0)
    {

        drv_data->usb_state = USB_STATE_DEFAULT;
    }
    // If the address is non-zero, the device enters the Address state
    else
    {
        drv_data->usb_state = USB_STATE_ADDRESS;
    }

	otg->device_regs.DCFG = (otg->device_regs.DCFG & ~ OTG_DCFG_DAD_Msk) | OTG_DCFG_DAD(address);

}

/**
 * Sets the current device configuration
*/
void usb_svc_setaddress(HANDLE hnd, unsigned int adr)
{
//	tsk_sleep(10);
	// note: Stall will be performed for the last endpoint used by this handle!!
	hnd->dst.as_voidptr = (void*)usb_svc_setaddress_hook;
	hnd->src.as_int = adr;
	hnd->hcontrol(DCR_HANDLE);
}
//-----------------------------------------------------------------------------
void usb_svc_halt_hook(USB_DRV_INFO drv_info, HANDLE hnd)
{
	ep_dir_state_t* epdir;
	unsigned int eptnum = hnd->src.as_int;
    Endpoint *endpoint = &drv_info->drv_data->endpoints[eptnum & 0xF];

	TRACE_USB(" Halt(%d)", eptnum);

	if(eptnum & 0x80)
		epdir = &endpoint->epd_in;
	else
		epdir = &endpoint->epd_out;

    // Check that endpoint is enabled and not already in Halt state
    if ((epdir->epd_state != ENDPOINT_STATE_DISABLED)
        && (epdir->epd_state != ENDPOINT_STATE_HALTED))
   	{
        // Abort the current transfer if necessary
    	usb_end_transfers(epdir, USBD_STATUS_ABORTED);

    	epdir->epd_state = ENDPOINT_STATE_HALTED;

        // Put endpoint into Halt state
    	usb_hal_stall(drv_info->hw_base, eptnum);

    }

}

/**
 * Sets the current device configuration
*/
void usb_svc_halt(HANDLE hnd, unsigned int eptnum)
{
	// note: Stall will be performed for the last endpoint used by this handle!!
	hnd->dst.as_voidptr = (void*)usb_svc_halt_hook;
	hnd->src.as_int = eptnum;
	hnd->hcontrol(DCR_HANDLE);
}

//-----------------------------------------------------------------------------
void usb_svc_unhalt_hook(USB_DRV_INFO drv_info, HANDLE hnd)
{
	unsigned char eptnum = hnd->src.as_int;
    Endpoint *endpoint = &drv_info->drv_data->endpoints[eptnum & 0xF];
	ep_dir_state_t* epdir;

	TRACE_USB(" Unhalt(%d)", eptnum);

	if(eptnum & 0x80)
		epdir = &endpoint->epd_in;
	else
		epdir = &endpoint->epd_out;
    if (epdir->epd_state == ENDPOINT_STATE_HALTED)
    {
        // Return endpoint to Idle state
    	epdir->epd_state = ENDPOINT_STATE_IDLE;

        // Clear FORCESTALL flag
        usb_hal_stall_clear(drv_info->hw_base, eptnum);
    }
}

/**
 * Sets the current device configuration
*/
void usb_svc_unhalt(HANDLE hnd, unsigned int eptnum)
{
	// note: Stall will be performed for the last endpoint used by this handle!!
	hnd->dst.as_voidptr = (void*)usb_svc_unhalt_hook;
	hnd->src.as_int = eptnum;
	hnd->hcontrol(DCR_HANDLE);
}


