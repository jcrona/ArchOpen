/*
* kernel/target/gfx/gui/main-menu.c
*
* MediOS project
* Copyright (c) 2005 by Christophe THOMAS
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*
*/

#include <sys_def/colordef.h>
#include <sys_def/font.h>
#include <sys_def/stddef.h>

#include <driver/hardware.h>
#include <driver/lcd.h>

#include <gui/status_line.h>

struct statusLine_data lineData = {
    x:0,y:0,
    w:SCREEN_REAL_WIDTH,
    bg_color:COLOR_LIGHT_BLUE,
    bat_x:293,
    bat_y:2,
    clk_x:135,
    clk_y:3,
    clk_color:COLOR_BLACK,
    has_date:1,
    logo_x:2,
    logo_y:2,
    ver_x:60,
    ver_y:3,  
    ver_color:COLOR_DARK_GREY,  
    module_x:242,
    module_y:4,
    pwr_x:278,
    pwr_y:4,
    usb_x:260,
    usb_y:4    
};
