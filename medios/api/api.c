/*
*   kernel/lib/api.c
*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*/

#include <api.h>
#include <kernel/swi.h>
#include <sys_def/errors.h>

unsigned int api_getFctPtr(char * name)    { swi_call(nAPI_INIAPI); }

/* libfloat stuff */

long __modsi3(long a, long b) { return float_modsi3(a,b); }
long __umodsi3(long a, long b) { return float_umodsi3(a,b); }
long __divsi3(long a, long b) { return float_divsi3(a,b); }
long __udivsi3(long a, long b) { return float_udivsi3(a,b); }
long long __divdi3(long long a,long long b) { return float_divdi3(a,b); }

long long __fixsfdi (float a) {return float_fixsfdi(a); }
long long __moddi3(long long  a, long long  b) {return float_moddi3(a,b);}
long long __ashrdi3(long long  a, unsigned int b) {return float_ashrdi3(a,b);}
long long __ashldi3(long long  a, unsigned int b) {return float_ashldi3(a,b);}

float __addsf3 (float a, float b) { return float_addsf3(a,b); }
float __subsf3 (float a, float b) { return float_subsf3(a,b); }
float __mulsf3 (float a, float b) { return float_mulsf3(a,b); }
float __divsf3 (float a, float b) { return float_divsf3(a,b); }
double __floatsidf (register long a) { return float_floatsidf(a); }
double __floatdidf (register long long a) { return float_floatdidf(a); }
float __floatsisf (register long  a) { return float_floatsisf(a); }
float __floatdisf (register long long  a) { return float_floatdisf(a); }
float __negsf2 (float a) { return float_negsf2(a); }
double __negdf2 (double a) { return float_negdf2(a); }
double __extendsfdf2 (float a) { return float_extendsfdf2(a); }
float __truncdfsf2 (double a) { return float_truncdfsf2(a); }
long __fixsfsi (float a) { return float_fixsfsi(a); }
long __fixdfsi (double a) { return float_fixdfsi(a); }
long long __fixdfdi (double a) { return float_fixdfdi(a); }
unsigned long __fixunsdfsi (double a) { return float_fixunsdfsi(a); }
unsigned long long __fixunsdfdi (double a) { return float_fixunsdfdi(a); }
double __adddf3 (double a, double b) { return float_adddf3(a,b); }
double __subdf3 (double a, double b) { return float_subdf3(a,b); }
double __muldf3 (double a, double b) { return float_muldf3(a,b); }
double __divdf3 (double a, double b) { return float_divdf3(a,b); }
int __gtdf2 (double a, double b) { return float_gtdf2(a,b); }
int __gedf2 (double a, double b) { return float_gedf2(a,b); }
int __ltdf2 (double a, double b) { return float_ltdf2(a,b); }
int __ledf2 (double a, double b) { return float_ledf2(a,b); }
int __eqdf2 (double a, double b) { return float_eqdf2(a,b); }
int __nedf2 (double a, double b) { return float_nedf2(a,b); }
int __gtsf2 (float a, float b) { return float_gtsf2(a,b); }
int __gesf2 (float a, float b) { return float_gesf2(a,b); }
int __ltsf2 (float a, float b) { return float_ltsf2(a,b); }
int __lesf2 (float a, float b) { return float_lesf2(a,b); }
int __eqsf2 (float a, float b) { return float_eqsf2(a,b); }
int __nesf2 (float a, float b) { return float_nesf2(a,b); }

double cos(double a) { return math_cos(a); }
double sqrt(double a) { return math_sqrt(a); }
double tan(double a) { return math_tan(a); }

unsigned char * _ctype;

void ini_api(void)
{
    _ctype = (char*)api_getFctPtr("_ctype");
    malloc=(void*(*)(long size))api_getFctPtr("malloc");
    realloc=(void*(*)(void *buffer, long newsize))api_getFctPtr("realloc");
    free=(void(*)(void *buf))api_getFctPtr("free");
    kfree=(void(*)(void *buf))api_getFctPtr("kfree");
    calloc=(void*(*)(unsigned int nmemb,unsigned int size))api_getFctPtr("calloc");
    lang_getStr=(char*(*)(int id))api_getFctPtr("lang_getStr");
    tmr_getTick=(unsigned int(*)(void))api_getFctPtr("tmr_getTick");
    tmr_getMicroTick=(unsigned int(*)(void))api_getFctPtr("tmr_getMicroTick");
    time_get=(MED_RET_T(*)(struct med_tm * valTime))api_getFctPtr("time_get");
    time_set=(MED_RET_T(*)(struct med_tm * newTime))api_getFctPtr("time_set");
    udelay=(void(*)(unsigned long usecs))api_getFctPtr("udelay");
    mdelay=(void(*)(unsigned long msecs))api_getFctPtr("mdelay");
    uart_in=(int(*)(unsigned char * data,int uartNum))api_getFctPtr("uart_in");
    uart_out=(void(*)(unsigned char data,int uartNum))api_getFctPtr("uart_out");
    uart_outString=(void(*)(unsigned char * data,int uartNum))api_getFctPtr("uart_outString");
    uart_changeSpeed=(void(*)(int speed,int uart_num))api_getFctPtr("uart_changeSpeed");
    set_timer_status=(void(*)(int timer_type,int power_mode,int status))api_getFctPtr("set_timer_status");
    set_timer_delay=(void(*)(int timer_type,int power_mode,int delay))api_getFctPtr("set_timer_delay");
    get_timer_status=(int(*)(int timer_type,int power_mode))api_getFctPtr("get_timer_status");
    get_timer_delay=(int(*)(int timer_type,int power_mode))api_getFctPtr("get_timer_delay");
    halt_disableTimer=(void(*)(int disable))api_getFctPtr("halt_disableTimer");
    DC_isConnected=(int(*)(void))api_getFctPtr("DC_isConnected");
    batLevel=(int(*)(void))api_getFctPtr("batLevel");
    lcd_setBrightness=(void(*)(int br))api_getFctPtr("lcd_setBrightness");
    lcd_getBrightness=(int(*)(void))api_getFctPtr("lcd_getBrightness");
    usb_isConnected=(int(*)(void))api_getFctPtr("usb_isConnected");
    FW_isConnected=(int(*)(void))api_getFctPtr("FW_isConnected");
    evt_getHandler=(int(*)(unsigned int mask))api_getFctPtr("evt_getHandler");
    evt_freeHandler=(MED_RET_T(*)(int num_evt_pipe))api_getFctPtr("evt_freeHandler");
    evt_getStatus=(int(*)(int num_evt_pipe))api_getFctPtr("evt_getStatus");
    evt_getFullStatus=(MED_RET_T(*)(int num_evt_pipe, struct evt_t * evt))api_getFctPtr("evt_getFullStatus");
    evt_getStatusBlocking=(int(*)(int num_evt_pipe))api_getFctPtr("evt_getStatusBlocking");
    getBtnName=(const char *(*)(int btn))api_getFctPtr("getBtnName");
    btn_readState=(int(*)(void))api_getFctPtr("btn_readState");
    halt_device=(void(*)(void))api_getFctPtr("halt_device");
    reload_firmware=(void(*)(void))api_getFctPtr("reload_firmware");
    printf=(void(*)(char *fmt, ...))api_getFctPtr("printf");
    print_data=(void(*)(char * data,int length))api_getFctPtr("print_data");
    do_bkpt=(void(*)(void))api_getFctPtr("do_bkpt");
    getArch=(int(*)(void))api_getFctPtr("getArch");
    getArchName=(char *(*)(void))api_getFctPtr("getArchName");
    getResolution=(void(*)(int * width,int * height))api_getFctPtr("getResolution");
    getErrno=(MED_RET_T(*)(void))api_getFctPtr("getErrno");
    float_modsi3=(long(*)(long a, long b ))api_getFctPtr("float_modsi3");
    float_umodsi3=(long(*)(long a, long b))api_getFctPtr("float_umodsi3");
    float_divsi3=(long(*)(long a, long b))api_getFctPtr("float_divsi3");
    float_udivsi3=(long(*)(long a, long b))api_getFctPtr("float_udivsi3");
    float_divdi3=(long long(*)(long long a, long long b))api_getFctPtr("float_divdi3");
    float_fixsfdi=(long long(*)(float a))api_getFctPtr("float_fixsfdi");
    float_moddi3=(long long(*)(long long a, long long b))api_getFctPtr("float_moddi3");
    float_ashrdi3=(long long(*)(long long a, unsigned int b))api_getFctPtr("float_ashrdi3");
    float_ashldi3=(long long(*)(long long a, unsigned int b))api_getFctPtr("float_ashldi3");
    float_addsf3=(float(*)(float a, float b))api_getFctPtr("float_addsf3");
    float_subsf3=(float(*)(float a, float b))api_getFctPtr("float_subsf3");
    float_mulsf3=(float(*)(float a, float b))api_getFctPtr("float_mulsf3");
    float_divsf3=(float(*)(float a, float b))api_getFctPtr("float_divsf3");
    float_floatsidf=(double(*)(register long a))api_getFctPtr("float_floatsidf");
    float_floatdidf=(double(*)(register long long a))api_getFctPtr("float_floatdidf");
    float_floatsisf=(float(*)(register long  a))api_getFctPtr("float_floatsisf");
    float_floatdisf=(float(*)(register long long  a))api_getFctPtr("float_floatdisf");
    float_negsf2=(float(*)(float a))api_getFctPtr("float_negsf2");
    float_negdf2=(double(*)(double a))api_getFctPtr("float_negdf2");
    float_extendsfdf2=(double(*)(float a))api_getFctPtr("float_extendsfdf2");
    float_truncdfsf2=(float(*)(double a))api_getFctPtr("float_truncdfsf2");
    float_fixsfsi=(long(*)(float a))api_getFctPtr("float_fixsfsi");
    float_fixdfsi=(long(*)(double a))api_getFctPtr("float_fixdfsi");
    float_fixdfdi=(long long(*)(double a))api_getFctPtr("float_fixdfdi");
    float_fixunsdfsi=(unsigned long(*)(double a))api_getFctPtr("float_fixunsdfsi");
    float_fixunsdfdi=(unsigned long long(*)(double a))api_getFctPtr("float_fixunsdfdi");
    float_adddf3=(double(*)(double a, double b))api_getFctPtr("float_adddf3");
    float_subdf3=(double(*)(double a, double b))api_getFctPtr("float_subdf3");
    float_muldf3=(double(*)(double a, double b))api_getFctPtr("float_muldf3");
    float_divdf3=(double(*)(double a, double b))api_getFctPtr("float_divdf3");
    float_gtdf2=(int(*)(double a, double b))api_getFctPtr("float_gtdf2");
    float_gedf2=(int(*)(double a, double b))api_getFctPtr("float_gedf2");
    float_ltdf2=(int(*)(double a, double b))api_getFctPtr("float_ltdf2");
    float_ledf2=(int(*)(double a, double b))api_getFctPtr("float_ledf2");
    float_eqdf2=(int(*)(double a, double b))api_getFctPtr("float_eqdf2");
    float_nedf2=(int(*)(double a, double b))api_getFctPtr("float_nedf2");
    float_gtsf2=(int(*)(float a, float b))api_getFctPtr("float_gtsf2");
    float_gesf2=(int(*)(float a, float b))api_getFctPtr("float_gesf2");
    float_ltsf2=(int(*)(float a, float b))api_getFctPtr("float_ltsf2");
    float_lesf2=(int(*)(float a, float b))api_getFctPtr("float_lesf2");
    float_eqsf2=(int(*)(float a, float b))api_getFctPtr("float_eqsf2");
    float_nesf2=(int(*)(float a, float b))api_getFctPtr("float_nesf2");
    math_cos=(double(*)(double a))api_getFctPtr("math_cos");
    math_sqrt=(double(*)(double a))api_getFctPtr("math_sqrt");
    math_tan=(double(*)(double a))api_getFctPtr("math_tan");
    open=(int(*)(const char* pathname, int flags))api_getFctPtr("open");
    close=(int(*)(int fdesc))api_getFctPtr("close");
    fsync=(int(*)(int fdesc))api_getFctPtr("fsync");
    read=(int(*)(int fdesc, void *buf, int count))api_getFctPtr("read");
    lseek=(int(*)(int fdesc, int offset, int whence))api_getFctPtr("lseek");
    write=(int(*)(int fdesc, const void *buf, int count))api_getFctPtr("write");
    truncate=(int(*)(int fdesc, int length))api_getFctPtr("truncate");
    filesize=(int(*)(int fdesc))api_getFctPtr("filesize");
    ftell=(int(*)(int fdesc))api_getFctPtr("ftell");
    opendir=(DIR*(*)(const char* name))api_getFctPtr("opendir");
    closedir=(int(*)(DIR* dir))api_getFctPtr("closedir");
    readdir=(struct dirent*(*)(DIR* dir))api_getFctPtr("readdir");
    mkdir=(int(*)(const char *name, int mode))api_getFctPtr("mkdir");
    fs_pwd=(MED_RET_T(*)(char * name))api_getFctPtr("fs_pwd");
    fs_cd=(MED_RET_T(*)(char * name))api_getFctPtr("fs_cd");
    gfx_openGraphics=(void(*)(void))api_getFctPtr("gfx_openGraphics");
    gfx_initGraphics=(void(*)(void))api_getFctPtr("gfx_initGraphics");
    gfx_closeGraphics=(void(*)(void))api_getFctPtr("gfx_closeGraphics");
    gfx_setPlane=(void(*)(int vplane))api_getFctPtr("gfx_setPlane");
    gfx_getPlane=(int(*)(void))api_getFctPtr("gfx_getPlane");
    gfx_planeHide=(void(*)(int vplane))api_getFctPtr("gfx_planeHide");
    gfx_planeShow=(void(*)(int vplane))api_getFctPtr("gfx_planeShow");
    gfx_planeIsShown=(int(*)(int vplane))api_getFctPtr("gfx_planeIsShown");
    gfx_planeSetState=(void(*)(int vplane,int state))api_getFctPtr("gfx_planeSetState");
    gfx_planeGetState=(int(*)(int vplane))api_getFctPtr("gfx_planeGetState");
    gfx_planeSetSize=(void(*)(int vplane,int width,int height,int bitsPerPixel,int mode))api_getFctPtr("gfx_planeSetSize");
    gfx_planeGetSize=(void(*)(int vplane,int * width,int * height,int * bitsPerPixel))api_getFctPtr("gfx_planeGetSize");
    gfx_planeSetPos=(void(*)(int vplane,int x,int y))api_getFctPtr("gfx_planeSetPos");
    gfx_planeGetPos=(void(*)(int vplane,int * x,int * y))api_getFctPtr("gfx_planeGetPos");
    gfx_planeGetBufferOffset=(void*(*)(int vplane))api_getFctPtr("gfx_planeGetBufferOffset");
    gfx_planeSetBufferOffset=(void(*)(int vplane, void * offset))api_getFctPtr("gfx_planeSetBufferOffset");
    gfx_setRectCursorColor=(void(*)(int color,int ram_palette))api_getFctPtr("gfx_setRectCursorColor");
    gfx_setRectCursorBorder=(void(*)(int horiz,int verti))api_getFctPtr("gfx_setRectCursorBorder");
    gfx_enableRectCursor=(void(*)(int state))api_getFctPtr("gfx_enableRectCursor");
    gfx_setRectCursorPos=(void(*)(int x,int y))api_getFctPtr("gfx_setRectCursorPos");
    gfx_setRectCursorSize=(void(*)(int width,int height))api_getFctPtr("gfx_setRectCursorSize");
    gfx_clearScreen=(void(*)(unsigned int color))api_getFctPtr("gfx_clearScreen");
    gfx_drawPixel=(void(*)(unsigned int color,int x, int y))api_getFctPtr("gfx_drawPixel");
    gfx_readPixel=(unsigned int(*)(int x, int y))api_getFctPtr("gfx_readPixel");
    gfx_drawRect=(void(*)(unsigned int color, int x, int y, int width, int height))api_getFctPtr("gfx_drawRect");
    gfx_fillRect=(void(*)(unsigned int color, int x, int y, int width, int height))api_getFctPtr("gfx_fillRect");
    gfx_drawLine=(void(*)(unsigned int color, int x1, int y1, int x2, int y2))api_getFctPtr("gfx_drawLine");
    gfx_putS=(void(*)(unsigned int color, unsigned int bg_color, int x, int y, unsigned char *s))api_getFctPtr("gfx_putS");
    gfx_putnS=(void(*)(unsigned int color, unsigned int bg_color, int x, int y, int n, unsigned char *s))api_getFctPtr("gfx_putnS");
    gfx_getStringSize=(void(*)(unsigned char *str, int *w, int *h))api_getFctPtr("gfx_getStringSize");
    gfx_putC=(void(*)(unsigned int color, unsigned int bg_color, int x, int y, unsigned char s))api_getFctPtr("gfx_putC");
    gfx_drawSprite=(void(*)(unsigned int * palette, SPRITE * sprite, int x, int y))api_getFctPtr("gfx_drawSprite");
    gfx_drawBitmap=(void(*)(BITMAP * bitmap, int x, int y))api_getFctPtr("gfx_drawBitmap");
    gfx_drawResizedBitmap=(void(*)(BITMAP * bitmap, int x, int y,int width,int height,int mode))api_getFctPtr("gfx_drawResizedBitmap");
    gfx_scrollWindowVert=(void(*)(unsigned int bgColor, int x, int y, int width, int height, int scroll, int UP))api_getFctPtr("gfx_scrollWindowVert");
    gfx_scrollWindowHoriz=(void(*)(unsigned int bgColor, int x, int y, int width, int height, int scroll, int RIGHT))api_getFctPtr("gfx_scrollWindowHoriz");
    gfx_setPalletteRGB=(void(*)(int r, int g, int b, int index))api_getFctPtr("gfx_setPalletteRGB");
    gfx_setEntirePalette=(void(*)(int palette[256][3],int size))api_getFctPtr("gfx_setEntirePalette");
    gfx_fontSet=(void(*)(int font_nb))api_getFctPtr("gfx_fontSet");
    gfx_fontGet=(int(*)(void))api_getFctPtr("gfx_fontGet");
    gfx_loadBmp_toPlane_center=(MED_RET_T(*)(char * filename,int plane))api_getFctPtr("gfx_loadBmp_toPlane_center");
    gfx_loadBmp_toPlane_coord=(MED_RET_T(*)(char * filename,int plane,int x,int y))api_getFctPtr("gfx_loadBmp_toPlane_coord");
    gfx_loadBmp_toMem_center=(MED_RET_T(*)(char * filename,char * dest,int w,int h,int output_mode))api_getFctPtr("gfx_loadBmp_toMem_center");
    gfx_loadBmp_toMem_coord=(MED_RET_T(*)(char * filename,char * dest,int w,int h,int output_mode,int x,int y))api_getFctPtr("gfx_loadBmp_toMem_coord");
    strlwr=(void(*)(char *s))api_getFctPtr("strlwr");
    qsort=(void(*)(void* __base, size_t __nmemb, size_t __size, int(*_compar)(const void*, const void*)))api_getFctPtr("qsort");
    atoi=(int(*)(const char *str))api_getFctPtr("atoi");
    strdup=(char *(*)(const char * s))api_getFctPtr("strdup");
    strcasecmp=(int(*)(const char *s1, const char *s2))api_getFctPtr("strcasecmp");
    strncasecmp=(int(*)(const char *s1, const char *s2, size_t n))api_getFctPtr("strncasecmp");
    strpbrk=(char *(*)(const char *,const char *))api_getFctPtr("strpbrk");
    strtok=(char *(*)(char *,const char *))api_getFctPtr("strtok");
    strtok_r=(char *(*)(char *ptr, const char *sep, char **end))api_getFctPtr("strtok_r");
    strsep=(char *(*)(char **,const char *))api_getFctPtr("strsep");
    strspn=(size_t(*)(const char *,const char *))api_getFctPtr("strspn");
    strcpy=(char *(*)(char *,const char *))api_getFctPtr("strcpy");
    strncpy=(char *(*)(char *,const char *, size_t))api_getFctPtr("strncpy");
    strcat=(char *(*)(char *, const char *))api_getFctPtr("strcat");
    strncat=(char *(*)(char *, const char *, size_t))api_getFctPtr("strncat");
    strcmp=(int(*)(const char *,const char *))api_getFctPtr("strcmp");
    strncmp=(int(*)(const char *,const char *,size_t))api_getFctPtr("strncmp");
    strnicmp=(int(*)(const char *, const char *, size_t))api_getFctPtr("strnicmp");
    strchr=(char *(*)(const char *,int))api_getFctPtr("strchr");
    strrchr=(char *(*)(const char *,int))api_getFctPtr("strrchr");
    strstr=(char *(*)(const char *,const char *))api_getFctPtr("strstr");
    strlen=(size_t(*)(const char *))api_getFctPtr("strlen");
    strnlen=(size_t(*)(const char *,size_t))api_getFctPtr("strnlen");
    memset=(void *(*)(void *,int,size_t))api_getFctPtr("memset");
    memcpy=(void *(*)(void *,const void *,size_t))api_getFctPtr("memcpy");
    memmove=(void *(*)(void *,const void *,size_t))api_getFctPtr("memmove");
    memscan=(void *(*)(void *,int,size_t))api_getFctPtr("memscan");
    memcmp=(int(*)(const void *,const void *,size_t))api_getFctPtr("memcmp");
    memchr=(void *(*)(const void *,int,size_t))api_getFctPtr("memchr");
    vsnprintf=(int(*)(char *buf, size_t size, const char *fmt, va_list args))api_getFctPtr("vsnprintf");
    snprintf=(int(*)(char * buf, size_t size, const char *fmt, ...))api_getFctPtr("snprintf");
    vsprintf=(int(*)(char *buf, const char *fmt, va_list args))api_getFctPtr("vsprintf");
    sprintf=(int(*)(char * buf, const char *fmt, ...))api_getFctPtr("sprintf");
    vsscanf=(int(*)(const char * buf, const char * fmt, va_list args))api_getFctPtr("vsscanf");
    sscanf=(int(*)(const char * buf, const char * fmt, ...))api_getFctPtr("sscanf");
    atof=(double(*)(char * str))api_getFctPtr("atof");
    strtod=(double(*)(char * str, char ** ptr))api_getFctPtr("strtod");
    srand=(void(*)(unsigned int seed))api_getFctPtr("srand");
    rand=(int(*)(void))api_getFctPtr("rand");
    widget_create=(WIDGET(*)(void))api_getFctPtr("widget_create");
    checkbox_create=(CHECKBOX(*)(void))api_getFctPtr("checkbox_create");
    trackbar_create=(TRACKBAR(*)(void))api_getFctPtr("trackbar_create");
    chooser_create=(CHOOSER(*)(void))api_getFctPtr("chooser_create");
    button_create=(BUTTON(*)(void))api_getFctPtr("button_create");
    menu_create=(MENU(*)(void))api_getFctPtr("menu_create");
    menuItem_create=(MENU_ITEM(*)(void))api_getFctPtr("menuItem_create");
    textMenu_create=(TEXTMENU(*)(void))api_getFctPtr("textMenu_create");
    textMenuItem_create=(TEXTMENU_ITEM(*)(void))api_getFctPtr("textMenuItem_create");
    widgetMenu_create=(WIDGETMENU(*)(void))api_getFctPtr("widgetMenu_create");
    widgetMenuItem_create=(WIDGETMENU_ITEM(*)(void))api_getFctPtr("widgetMenuItem_create");
    widgetMenuCheckbox_create=(WIDGETMENU_CHECKBOX(*)(void))api_getFctPtr("widgetMenuCheckbox_create");
    widgetMenuTrackbar_create=(WIDGETMENU_TRACKBAR(*)(void))api_getFctPtr("widgetMenuTrackbar_create");
    widgetMenuChooser_create=(WIDGETMENU_CHOOSER(*)(void))api_getFctPtr("widgetMenuChooser_create");
    iconMenu_create=(ICONMENU(*)(void))api_getFctPtr("iconMenu_create");
    iconMenuItem_create=(ICONMENU_ITEM(*)(void))api_getFctPtr("iconMenuItem_create");
    widgetList_create=(WIDGETLIST(*)(void))api_getFctPtr("widgetList_create");
    label_create=(LABEL(*)(void))api_getFctPtr("label_create");
    browser_simpleBrowse=(int(*)(char * path,char * res))api_getFctPtr("browser_simpleBrowse");
    icon_load=(ICON(*)(char * filename))api_getFctPtr("icon_load");
    icon_add=(ICON(*)(char * name,unsigned char * data,int w,int h))api_getFctPtr("icon_add");
    icon_get=(ICON(*)(char * name))api_getFctPtr("icon_get");
    msgBox_show=(int(*)(unsigned char* caption, unsigned char* msg, int type, int icon,int evt_hanlder))api_getFctPtr("msgBox_show");
    msgBox_info=(void(*)(unsigned char* msg))api_getFctPtr("msgBox_info");
    virtKbd=(void(*)(int evt_hanlder, char * str))api_getFctPtr("virtKbd");
    cfg_clear=(void(*)(CFG_DATA * data))api_getFctPtr("cfg_clear");
    cfg_newFile=(CFG_DATA *(*)(void))api_getFctPtr("cfg_newFile");
    cfg_readFile=(CFG_DATA *(*)(char * filename))api_getFctPtr("cfg_readFile");
    cfg_writeFile=(bool(*)(CFG_DATA * data, char * filename))api_getFctPtr("cfg_writeFile");
    cfg_rewindItems=(void(*)(CFG_DATA * data))api_getFctPtr("cfg_rewindItems");
    cfg_nextItem=(bool(*)(CFG_DATA * data, char * * name,char * * value))api_getFctPtr("cfg_nextItem");
    cfg_itemExists=(bool(*)(CFG_DATA * data, char * name))api_getFctPtr("cfg_itemExists");
    cfg_readString=(char *(*)(CFG_DATA * data, char * name))api_getFctPtr("cfg_readString");
    cfg_readInt=(int(*)(CFG_DATA * data, char * name))api_getFctPtr("cfg_readInt");
    cfg_readBool=(bool(*)(CFG_DATA * data, char * name))api_getFctPtr("cfg_readBool");
    cfg_writeString=(void(*)(CFG_DATA * data, char * name,char * value))api_getFctPtr("cfg_writeString");
    cfg_writeInt=(void(*)(CFG_DATA * data, char * name,int value))api_getFctPtr("cfg_writeInt");
    cfg_writeBool=(void(*)(CFG_DATA * data, char * name,bool value))api_getFctPtr("cfg_writeBool");
    cfg_addDummyLine=(void(*)(CFG_DATA * data, char * text))api_getFctPtr("cfg_addDummyLine");
    cfg_deleteItem=(bool(*)(CFG_DATA * data, char * name))api_getFctPtr("cfg_deleteItem");
    cfg_printItems=(void(*)(CFG_DATA * data))api_getFctPtr("cfg_printItems");
    csv_newFile=(MED_RET_T(*)(char * filename))api_getFctPtr("csv_newFile");
    csv_end=(MED_RET_T(*)(void))api_getFctPtr("csv_end");
    csv_line2Array=(MED_RET_T(*)(int nbItem,char ** item_array,char sepChar))api_getFctPtr("csv_line2Array");
    csv_readLine=(MED_RET_T(*)(void * data,char * formatStr,char sepChar))api_getFctPtr("csv_readLine");
    speaker_enable=(void(*)(int enable))api_getFctPtr("speaker_enable");
    speaker_state=(int(*)(void))api_getFctPtr("speaker_state");
    speaker_available=(int(*)(void))api_getFctPtr("speaker_available");
    codec_mustSeek=(bool(*)(int * time))api_getFctPtr("codec_mustSeek");
    codec_setElapsed=(void(*)(int elapsed))api_getFctPtr("codec_setElapsed");
    codec_seekDone=(void(*)(void))api_getFctPtr("codec_seekDone");
    codec_mustContinue=(bool(*)(void))api_getFctPtr("codec_mustContinue");
    output_write=(void(*)(void * buffer, int size))api_getFctPtr("output_write");
    output_outputParamsChanged=(void(*)(void))api_getFctPtr("output_outputParamsChanged");
    buffer_seek=(int(*)(int offset,int whence))api_getFctPtr("buffer_seek");
    buffer_read=(int(*)(void * buf,int count))api_getFctPtr("buffer_read");
    buffer_getActiveItem=(PLAYLIST_ITEM *(*)(void))api_getFctPtr("buffer_getActiveItem");
    irq_changeHandler=(void(*)(int irq_num,void(*fct)(int irq,struct pt_regs * regs)))api_getFctPtr("irq_changeHandler");
    irq_enable=(void(*)(int irq))api_getFctPtr("irq_enable");
    irq_disable=(void(*)(int irq))api_getFctPtr("irq_disable");
    yield=(unsigned long(*)(void))api_getFctPtr("yield");
    osd_getTrspBit=(int(*)(void))api_getFctPtr("osd_getTrspBit");
    osd_getBlendFactorBit=(int(*)(int factor))api_getFctPtr("osd_getBlendFactorBit");
    mas_chgMode=(MED_RET_T(*)(int mode))api_getFctPtr("mas_chgMode");
    mas_mp3LaunchDecode=(void(*)(void))api_getFctPtr("mas_mp3LaunchDecode");
    mas_setMp3Buffer=(void(*)(struct mas_sound_buffer * b1,struct mas_sound_buffer * b2))api_getFctPtr("mas_setMp3Buffer");
    mas_mp3DecodeState=(int(*)(void))api_getFctPtr("mas_mp3DecodeState");
    mas_mp3StopDecode=(void(*)(void))api_getFctPtr("mas_mp3StopDecode");
    mas_i2sChgSRate=(void(*)(int))api_getFctPtr("mas_i2sChgSRate");
    mas_clearMp3Buffer=(void(*)(void))api_getFctPtr("mas_clearMp3Buffer");
}
