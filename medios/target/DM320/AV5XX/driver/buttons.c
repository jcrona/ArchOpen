/*
*   kernel/target/arch_AV4XX/buttons.c
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*/

#include <sys_def/stddef.h>

#include <kernel/io.h>

#include <driver/gio.h>
#include <driver/hardware.h>
#include <driver/cpld.h>
#include <driver/buttons.h>

int btn_mask[NB_BUTTONS] =
{
BTMASK_UP ,      /*BTN_UP*/
BTMASK_DOWN,     /*BTN_DOWN*/
BTMASK_LEFT,     /*BTN_LEFT*/
BTMASK_RIGHT,    /*BTN_RIGHT*/
BTMASK_F1,       /*BTN_F1*/
BTMASK_F2,       /*BTN_F2*/
BTMASK_F3,       /*BTN_F3*/
0,               /*BTN_F4*/
BTMASK_BTN1,     /*BTN_1*/
BTMASK_BTN2,     /*BTN_2*/
BTMASK_BTN3,     /*BTN_3*/
0,               /*BTN_4*/
BTMASK_ON,       /*BTN_ON*/
BTMASK_OFF,      /*BTN_OFF*/
0,               /*BT_FAST_DIR*/
0
};

const char * btn_name [] =
{
    "UP",
    "DOWN",
    "LEFT",
    "RIGHT",
    "F1",
    "F2",
    "F3",
    " ",
    "B1",
    "B2",
    "LCD_SWITCH",
    " ",
    "ON",
    "OFF"
};

int arch_btn_readHardware(void){
    int i,val;
    int dir,fn,bt,on_off;
    int P1,P2,P3;
    
    P1 =  (~inw(BUTTON_PORT0))&0xF;
    for(i=0;i<16;++i); // delay
    P2  = (~inw(BUTTON_PORT1))&0xF;
    for(i=0;i<16;++i); // delay
    P3  = (~inw(BUTTON_PORT2))&0xF;
   

    dir=fn=bt=on_off=0;

    dir=P1;
    fn=P2&0x7;
    bt=(P3&0x3) | ((P2>>1)&0x4);

    /* ON, OFF keys */

    if(!GIO_IS_SET(GIO_ON_BTN))  on_off |= 0x1;
    if(!GIO_IS_SET(GIO_OFF_BTN)) on_off |= 0x2;

    val = (dir|(fn<<4)|(bt<<8)|(on_off<<12))&0xFFFF;

    return val;
}
