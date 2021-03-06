//==========================================================================
// This file is part of TMOS Operating System.
// Copyright (C) 2007-2008 Informa Ltd.
//
// TMOS is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 3 or (at your option) any later version.
//
// TMOS is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
//==========================================================================
//
// Author(s):     Miroslav Kostadinov
// Date:          2008-Apr-03
// Description:   SWI table definition
//
//
//========================================================================

#define usr_task_suspend_swi		1
#define usr_send_signal_swi			2
#define usr_task_schedule_swi		3
#define tsk_sleep_swi				4
#define tsk_try_signal_swi			5
#define tsk_get_signal_swi			6
#define tsk_wait_signal_swi			7
#define tsk_resume_wait_signal_swi	8
#define usr_drv_hcontrol_swi		9
#define usr_drv_icontrol_swi		10
#define tsk_start_handle_swi		11
#define usr_HND_SET_STATUS_swi		12
#define tsk_start_and_wait_swi		13

#ifndef __ASSEMBLY__

typedef void (* SWI_FUNC)(void);
extern SWI_FUNC const SWI_TABLE[];

#endif


