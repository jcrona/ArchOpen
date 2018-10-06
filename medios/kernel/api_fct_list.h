/*
*   kernel/core/api_fct_list.h
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*/

#ifndef __API_FCT_LIST_H
#define __API_FCT_LIST_H

#include <sys_def/stddef.h>
#include <kernel/swi.h>

/* needed for ctype pointeur def */
#include <sys_def/ctype.h>

/* include needed by api functions */
#include <sys_def/errors.h>
#include <kernel/malloc.h>
#include <kernel/lang.h>
#include <kernel/timer.h>
#include <driver/time.h>
#include <kernel/delay.h>
#include <driver/uart.h>
#include <driver/energy.h>
#include <driver/batDc.h>
#include <driver/lcd.h>
#include <driver/usb_fw.h>
#include <kernel/evt.h>
#include <driver/buttons.h>
#include <init/exit.h>
#include <kernel/kernel.h>
#include <lib/libfloat.h>
#include <lib/libmath.h>
#include <fs/stdfs.h>
#include <gfx/graphics.h>
#include <gfx/bmp.h>
#include <lib/random.h>
#include <gui/widget.h>
#include <gui/checkbox.h>
#include <gui/trackbar.h>
#include <gui/chooser.h>
#include <gui/button.h>
#include <gui/menu.h>
#include <gui/textmenu.h>
#include <gui/widgetmenu.h>
#include <gui/iconmenu.h>
#include <gui/widgetlist.h>
#include <gui/label.h>
#include <gui/file_browser.h>
#include <gui/icons.h>
#include <gui/msgBox.h>
#include <gui/virtKbd.h>
#include <fs/cfg_file.h>
#include <fs/csv_file.h>
#include <driver/speaker.h>
#include <snd/codec.h>
#include <snd/output.h>
#include <snd/buffer.h>
#include <kernel/irq.h>
#include <kernel/thread.h>
#include <driver/osd.h>
#include <driver/mas.h>

struct user_fct_t fct_array[] = {
    { "_ctype",
      (unsigned int)&_ctype
    },
    { "malloc",
      (unsigned int)malloc
    },
    { "realloc",
      (unsigned int)realloc
    },
    { "free",
      (unsigned int)free
    },
    { "kfree",
      (unsigned int)kfree
    },
    { "calloc",
      (unsigned int)calloc
    },
    { "lang_getStr",
      (unsigned int)lang_getStr
    },
    { "tmr_getTick",
      (unsigned int)tmr_getTick
    },
    { "tmr_getMicroTick",
      (unsigned int)tmr_getMicroTick
    },
    { "time_get",
      (unsigned int)time_get
    },
    { "time_set",
      (unsigned int)time_set
    },
    { "udelay",
      (unsigned int)udelay
    },
    { "mdelay",
      (unsigned int)mdelay
    },
    { "uart_in",
      (unsigned int)uart_in
    },
    { "uart_out",
      (unsigned int)uart_out
    },
    { "uart_outString",
      (unsigned int)uart_outString
    },
    { "uart_changeSpeed",
      (unsigned int)uart_changeSpeed
    },
    { "set_timer_status",
      (unsigned int)set_timer_status
    },
    { "set_timer_delay",
      (unsigned int)set_timer_delay
    },
    { "get_timer_status",
      (unsigned int)get_timer_status
    },
    { "get_timer_delay",
      (unsigned int)get_timer_delay
    },
    { "halt_disableTimer",
      (unsigned int)halt_disableTimer
    },
    { "DC_isConnected",
      (unsigned int)DC_isConnected
    },
    { "batLevel",
      (unsigned int)batLevel
    },
    { "lcd_setBrightness",
      (unsigned int)lcd_setBrightness
    },
    { "lcd_getBrightness",
      (unsigned int)lcd_getBrightness
    },
    { "usb_isConnected",
      (unsigned int)usb_isConnected
    },
    { "FW_isConnected",
      (unsigned int)FW_isConnected
    },
    { "evt_getHandler",
      (unsigned int)evt_getHandler
    },
    { "evt_freeHandler",
      (unsigned int)evt_freeHandler
    },
    { "evt_getStatus",
      (unsigned int)evt_getStatus
    },
    { "evt_getFullStatus",
      (unsigned int)evt_getFullStatus
    },
    { "evt_getStatusBlocking",
      (unsigned int)evt_getStatusBlocking
    },
    { "getBtnName",
      (unsigned int)getBtnName
    },
    { "btn_readState",
      (unsigned int)btn_readState
    },
    { "halt_device",
      (unsigned int)halt_device
    },
    { "reload_firmware",
      (unsigned int)reload_firmware
    },
    { "printf",
      (unsigned int)printf
    },
    { "print_data",
      (unsigned int)print_data
    },
    { "do_bkpt",
      (unsigned int)do_bkpt
    },
    { "getArch",
      (unsigned int)getArch
    },
    { "getArchName",
      (unsigned int)getArchName
    },
    { "getResolution",
      (unsigned int)getResolution
    },
    { "getErrno",
      (unsigned int)getErrno
    },
    { "float_modsi3",
      (unsigned int)float_modsi3
    },
    { "float_umodsi3",
      (unsigned int)float_umodsi3
    },
    { "float_divsi3",
      (unsigned int)float_divsi3
    },
    { "float_udivsi3",
      (unsigned int)float_udivsi3
    },
    { "float_divdi3",
      (unsigned int)float_divdi3
    },
    { "float_fixsfdi",
      (unsigned int)float_fixsfdi
    },
    { "float_moddi3",
      (unsigned int)float_moddi3
    },
    { "float_ashrdi3",
      (unsigned int)float_ashrdi3
    },
    { "float_ashldi3",
      (unsigned int)float_ashldi3
    },
    { "float_addsf3",
      (unsigned int)float_addsf3
    },
    { "float_subsf3",
      (unsigned int)float_subsf3
    },
    { "float_mulsf3",
      (unsigned int)float_mulsf3
    },
    { "float_divsf3",
      (unsigned int)float_divsf3
    },
    { "float_floatsidf",
      (unsigned int)float_floatsidf
    },
    { "float_floatdidf",
      (unsigned int)float_floatdidf
    },
    { "float_floatsisf",
      (unsigned int)float_floatsisf
    },
    { "float_floatdisf",
      (unsigned int)float_floatdisf
    },
    { "float_negsf2",
      (unsigned int)float_negsf2
    },
    { "float_negdf2",
      (unsigned int)float_negdf2
    },
    { "float_extendsfdf2",
      (unsigned int)float_extendsfdf2
    },
    { "float_truncdfsf2",
      (unsigned int)float_truncdfsf2
    },
    { "float_fixsfsi",
      (unsigned int)float_fixsfsi
    },
    { "float_fixdfsi",
      (unsigned int)float_fixdfsi
    },
    { "float_fixdfdi",
      (unsigned int)float_fixdfdi
    },
    { "float_fixunsdfsi",
      (unsigned int)float_fixunsdfsi
    },
    { "float_fixunsdfdi",
      (unsigned int)float_fixunsdfdi
    },
    { "float_adddf3",
      (unsigned int)float_adddf3
    },
    { "float_subdf3",
      (unsigned int)float_subdf3
    },
    { "float_muldf3",
      (unsigned int)float_muldf3
    },
    { "float_divdf3",
      (unsigned int)float_divdf3
    },
    { "float_gtdf2",
      (unsigned int)float_gtdf2
    },
    { "float_gedf2",
      (unsigned int)float_gedf2
    },
    { "float_ltdf2",
      (unsigned int)float_ltdf2
    },
    { "float_ledf2",
      (unsigned int)float_ledf2
    },
    { "float_eqdf2",
      (unsigned int)float_eqdf2
    },
    { "float_nedf2",
      (unsigned int)float_nedf2
    },
    { "float_gtsf2",
      (unsigned int)float_gtsf2
    },
    { "float_gesf2",
      (unsigned int)float_gesf2
    },
    { "float_ltsf2",
      (unsigned int)float_ltsf2
    },
    { "float_lesf2",
      (unsigned int)float_lesf2
    },
    { "float_eqsf2",
      (unsigned int)float_eqsf2
    },
    { "float_nesf2",
      (unsigned int)float_nesf2
    },
    { "math_cos",
      (unsigned int)math_cos
    },
    { "math_sqrt",
      (unsigned int)math_sqrt
    },
    { "math_tan",
      (unsigned int)math_tan
    },
    { "open",
      (unsigned int)open
    },
    { "close",
      (unsigned int)close
    },
    { "fsync",
      (unsigned int)fsync
    },
    { "read",
      (unsigned int)read
    },
    { "lseek",
      (unsigned int)lseek
    },
    { "write",
      (unsigned int)write
    },
    { "truncate",
      (unsigned int)truncate
    },
    { "filesize",
      (unsigned int)filesize
    },
    { "ftell",
      (unsigned int)ftell
    },
    { "opendir",
      (unsigned int)opendir
    },
    { "closedir",
      (unsigned int)closedir
    },
    { "readdir",
      (unsigned int)readdir
    },
    { "mkdir",
      (unsigned int)mkdir
    },
    { "fs_pwd",
      (unsigned int)fs_pwd
    },
    { "fs_cd",
      (unsigned int)fs_cd
    },
    { "gfx_openGraphics",
      (unsigned int)gfx_openGraphics
    },
    { "gfx_initGraphics",
      (unsigned int)gfx_initGraphics
    },
    { "gfx_closeGraphics",
      (unsigned int)gfx_closeGraphics
    },
    { "gfx_setPlane",
      (unsigned int)gfx_setPlane
    },
    { "gfx_getPlane",
      (unsigned int)gfx_getPlane
    },
    { "gfx_planeHide",
      (unsigned int)gfx_planeHide
    },
    { "gfx_planeShow",
      (unsigned int)gfx_planeShow
    },
    { "gfx_planeIsShown",
      (unsigned int)gfx_planeIsShown
    },
    { "gfx_planeSetState",
      (unsigned int)gfx_planeSetState
    },
    { "gfx_planeGetState",
      (unsigned int)gfx_planeGetState
    },
    { "gfx_planeSetSize",
      (unsigned int)gfx_planeSetSize
    },
    { "gfx_planeGetSize",
      (unsigned int)gfx_planeGetSize
    },
    { "gfx_planeSetPos",
      (unsigned int)gfx_planeSetPos
    },
    { "gfx_planeGetPos",
      (unsigned int)gfx_planeGetPos
    },
    { "gfx_planeGetBufferOffset",
      (unsigned int)gfx_planeGetBufferOffset
    },
    { "gfx_planeSetBufferOffset",
      (unsigned int)gfx_planeSetBufferOffset
    },
    { "gfx_setRectCursorColor",
      (unsigned int)gfx_setRectCursorColor
    },
    { "gfx_setRectCursorBorder",
      (unsigned int)gfx_setRectCursorBorder
    },
    { "gfx_enableRectCursor",
      (unsigned int)gfx_enableRectCursor
    },
    { "gfx_setRectCursorPos",
      (unsigned int)gfx_setRectCursorPos
    },
    { "gfx_setRectCursorSize",
      (unsigned int)gfx_setRectCursorSize
    },
    { "gfx_clearScreen",
      (unsigned int)gfx_clearScreen
    },
    { "gfx_drawPixel",
      (unsigned int)gfx_drawPixel
    },
    { "gfx_readPixel",
      (unsigned int)gfx_readPixel
    },
    { "gfx_drawRect",
      (unsigned int)gfx_drawRect
    },
    { "gfx_fillRect",
      (unsigned int)gfx_fillRect
    },
    { "gfx_drawLine",
      (unsigned int)gfx_drawLine
    },
    { "gfx_putS",
      (unsigned int)gfx_putS
    },
    { "gfx_putnS",
      (unsigned int)gfx_putnS
    },
    { "gfx_getStringSize",
      (unsigned int)gfx_getStringSize
    },
    { "gfx_putC",
      (unsigned int)gfx_putC
    },
    { "gfx_drawSprite",
      (unsigned int)gfx_drawSprite
    },
    { "gfx_drawBitmap",
      (unsigned int)gfx_drawBitmap
    },
    { "gfx_drawResizedBitmap",
      (unsigned int)gfx_drawResizedBitmap
    },
    { "gfx_scrollWindowVert",
      (unsigned int)gfx_scrollWindowVert
    },
    { "gfx_scrollWindowHoriz",
      (unsigned int)gfx_scrollWindowHoriz
    },
    { "gfx_setPalletteRGB",
      (unsigned int)gfx_setPalletteRGB
    },
    { "gfx_setEntirePalette",
      (unsigned int)gfx_setEntirePalette
    },
    { "gfx_fontSet",
      (unsigned int)gfx_fontSet
    },
    { "gfx_fontGet",
      (unsigned int)gfx_fontGet
    },
    { "gfx_loadBmp_toPlane_center",
      (unsigned int)gfx_loadBmp_toPlane_center
    },
    { "gfx_loadBmp_toPlane_coord",
      (unsigned int)gfx_loadBmp_toPlane_coord
    },
    { "gfx_loadBmp_toMem_center",
      (unsigned int)gfx_loadBmp_toMem_center
    },
    { "gfx_loadBmp_toMem_coord",
      (unsigned int)gfx_loadBmp_toMem_coord
    },
    { "strlwr",
      (unsigned int)strlwr
    },
    { "qsort",
      (unsigned int)qsort
    },
    { "atoi",
      (unsigned int)atoi
    },
    { "strdup",
      (unsigned int)strdup
    },
    { "strcasecmp",
      (unsigned int)strcasecmp
    },
    { "strncasecmp",
      (unsigned int)strncasecmp
    },
    { "strpbrk",
      (unsigned int)strpbrk
    },
    { "strtok",
      (unsigned int)strtok
    },
    { "strtok_r",
      (unsigned int)strtok_r
    },
    { "strsep",
      (unsigned int)strsep
    },
    { "strspn",
      (unsigned int)strspn
    },
    { "strcpy",
      (unsigned int)strcpy
    },
    { "strncpy",
      (unsigned int)strncpy
    },
    { "strcat",
      (unsigned int)strcat
    },
    { "strncat",
      (unsigned int)strncat
    },
    { "strcmp",
      (unsigned int)strcmp
    },
    { "strncmp",
      (unsigned int)strncmp
    },
    { "strnicmp",
      (unsigned int)strnicmp
    },
    { "strchr",
      (unsigned int)strchr
    },
    { "strrchr",
      (unsigned int)strrchr
    },
    { "strstr",
      (unsigned int)strstr
    },
    { "strlen",
      (unsigned int)strlen
    },
    { "strnlen",
      (unsigned int)strnlen
    },
    { "memset",
      (unsigned int)memset
    },
    { "memcpy",
      (unsigned int)memcpy
    },
    { "memmove",
      (unsigned int)memmove
    },
    { "memscan",
      (unsigned int)memscan
    },
    { "memcmp",
      (unsigned int)memcmp
    },
    { "memchr",
      (unsigned int)memchr
    },
    { "vsnprintf",
      (unsigned int)vsnprintf
    },
    { "snprintf",
      (unsigned int)snprintf
    },
    { "vsprintf",
      (unsigned int)vsprintf
    },
    { "sprintf",
      (unsigned int)sprintf
    },
    { "vsscanf",
      (unsigned int)vsscanf
    },
    { "sscanf",
      (unsigned int)sscanf
    },
    { "atof",
      (unsigned int)atof
    },
    { "strtod",
      (unsigned int)strtod
    },
    { "srand",
      (unsigned int)srand
    },
    { "rand",
      (unsigned int)rand
    },
    { "widget_create",
      (unsigned int)widget_create
    },
    { "checkbox_create",
      (unsigned int)checkbox_create
    },
    { "trackbar_create",
      (unsigned int)trackbar_create
    },
    { "chooser_create",
      (unsigned int)chooser_create
    },
    { "button_create",
      (unsigned int)button_create
    },
    { "menu_create",
      (unsigned int)menu_create
    },
    { "menuItem_create",
      (unsigned int)menuItem_create
    },
    { "textMenu_create",
      (unsigned int)textMenu_create
    },
    { "textMenuItem_create",
      (unsigned int)textMenuItem_create
    },
    { "widgetMenu_create",
      (unsigned int)widgetMenu_create
    },
    { "widgetMenuItem_create",
      (unsigned int)widgetMenuItem_create
    },
    { "widgetMenuCheckbox_create",
      (unsigned int)widgetMenuCheckbox_create
    },
    { "widgetMenuTrackbar_create",
      (unsigned int)widgetMenuTrackbar_create
    },
    { "widgetMenuChooser_create",
      (unsigned int)widgetMenuChooser_create
    },
    { "iconMenu_create",
      (unsigned int)iconMenu_create
    },
    { "iconMenuItem_create",
      (unsigned int)iconMenuItem_create
    },
    { "widgetList_create",
      (unsigned int)widgetList_create
    },
    { "label_create",
      (unsigned int)label_create
    },
    { "browser_simpleBrowse",
      (unsigned int)browser_simpleBrowse
    },
    { "icon_load",
      (unsigned int)icon_load
    },
    { "icon_add",
      (unsigned int)icon_add
    },
    { "icon_get",
      (unsigned int)icon_get
    },
    { "msgBox_show",
      (unsigned int)msgBox_show
    },
    { "msgBox_info",
      (unsigned int)msgBox_info
    },
    { "virtKbd",
      (unsigned int)virtKbd
    },
    { "cfg_clear",
      (unsigned int)cfg_clear
    },
    { "cfg_newFile",
      (unsigned int)cfg_newFile
    },
    { "cfg_readFile",
      (unsigned int)cfg_readFile
    },
    { "cfg_writeFile",
      (unsigned int)cfg_writeFile
    },
    { "cfg_rewindItems",
      (unsigned int)cfg_rewindItems
    },
    { "cfg_nextItem",
      (unsigned int)cfg_nextItem
    },
    { "cfg_itemExists",
      (unsigned int)cfg_itemExists
    },
    { "cfg_readString",
      (unsigned int)cfg_readString
    },
    { "cfg_readInt",
      (unsigned int)cfg_readInt
    },
    { "cfg_readBool",
      (unsigned int)cfg_readBool
    },
    { "cfg_writeString",
      (unsigned int)cfg_writeString
    },
    { "cfg_writeInt",
      (unsigned int)cfg_writeInt
    },
    { "cfg_writeBool",
      (unsigned int)cfg_writeBool
    },
    { "cfg_addDummyLine",
      (unsigned int)cfg_addDummyLine
    },
    { "cfg_deleteItem",
      (unsigned int)cfg_deleteItem
    },
    { "cfg_printItems",
      (unsigned int)cfg_printItems
    },
    { "csv_newFile",
      (unsigned int)csv_newFile
    },
    { "csv_end",
      (unsigned int)csv_end
    },
    { "csv_line2Array",
      (unsigned int)csv_line2Array
    },
    { "csv_readLine",
      (unsigned int)csv_readLine
    },
    { "speaker_enable",
      (unsigned int)speaker_enable
    },
    { "speaker_state",
      (unsigned int)speaker_state
    },
    { "speaker_available",
      (unsigned int)speaker_available
    },
    { "codec_mustSeek",
      (unsigned int)codec_mustSeek
    },
    { "codec_setElapsed",
      (unsigned int)codec_setElapsed
    },
    { "codec_seekDone",
      (unsigned int)codec_seekDone
    },
    { "codec_mustContinue",
      (unsigned int)codec_mustContinue
    },
    { "output_write",
      (unsigned int)output_write
    },
    { "output_outputParamsChanged",
      (unsigned int)output_outputParamsChanged
    },
    { "buffer_seek",
      (unsigned int)buffer_seek
    },
    { "buffer_read",
      (unsigned int)buffer_read
    },
    { "buffer_getActiveItem",
      (unsigned int)buffer_getActiveItem
    },
    { "irq_changeHandler",
      (unsigned int)irq_changeHandler
    },
    { "irq_enable",
      (unsigned int)irq_enable
    },
    { "irq_disable",
      (unsigned int)irq_disable
    },
    { "yield",
      (unsigned int)yield
    },
    { "osd_getTrspBit",
      (unsigned int)osd_getTrspBit
    },
    { "osd_getBlendFactorBit",
      (unsigned int)osd_getBlendFactorBit
    },
    { "mas_chgMode",
      (unsigned int)mas_chgMode
    },
    { "mas_mp3LaunchDecode",
      (unsigned int)mas_mp3LaunchDecode
    },
    { "mas_setMp3Buffer",
      (unsigned int)mas_setMp3Buffer
    },
    { "mas_mp3DecodeState",
      (unsigned int)mas_mp3DecodeState
    },
    { "mas_mp3StopDecode",
      (unsigned int)mas_mp3StopDecode
    },
    { "mas_i2sChgSRate",
      (unsigned int)mas_i2sChgSRate
    },
    { "mas_clearMp3Buffer",
      (unsigned int)mas_clearMp3Buffer
    },
    { NULL,
      0
    }
};

#endif
