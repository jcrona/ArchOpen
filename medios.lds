ENTRY(entry_code)

MEMORY
{
   DRAM : ORIGIN = 0x00900000,    LENGTH = 0x1000000
   IRAM : ORIGIN = 0x00000004,    LENGTH = 0x7c00-0x4
}

SECTIONS
{
    .text 0x00900000:
    {
        _code_start = .;
        *(.text.init.arch)
        *(.text.init)
        *(.text)
        *(.glue_7t)
        *(.glue_7)
    } > DRAM

    .rodata :
    {
        *(.rodata)
        *(.rodata.str1.4)
    } > DRAM

    .data :
    {
        *(.data)
        *(.got)
        *(.got.*)
        _real_iram_start = .;
    } > DRAM

    .iram 0x00000004 : AT ( _real_iram_start )
    {
        _iram_start = .;
        *(.vectors)
        *(.core)
        *(.cored)
        _iram_end = .;
    } > IRAM

    .sdend 0x00900000+0x1000000-0x2ec : AT ( _real_iram_start + SIZEOF(.iram) )
    {
        _sdend_start = .;
        *(.fwuncomp_code)
        *(.fwuncomp_data)
        _sdend_end = .;
    } > DRAM

    .bss _real_iram_start (NOLOAD) : AT ( _real_iram_start )
    {
        _bss_start = .;
        *(.bss)
        _bss_end = ALIGN(0x04);
    } > DRAM

    .common :
    {
        *(.common)
        _end_kernel = . ;
    } > DRAM
}