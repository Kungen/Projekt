/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-9    
 * Generated C linker script file for LM3S6965 
 * (created from lmi_cm3_c.ld (v3.3.7 (201005201503)) on Tue Mar 01 12:45:26 CET 2011)
*/

INCLUDE "lcd_driver_Debug_lib.ld"
INCLUDE "lcd_driver_Debug_mem.ld"

ENTRY(ResetISR)

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text*)
		*(.rodata*)

	} > MFlash_256


	/* for exception handling/unwind - some Newlib functions (in common with C++ and STDC++) use this. */
	
	.ARM.extab : 
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > MFlash_256

	__exidx_start = .;
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > MFlash_256
	__exidx_end = .;

	_etext = .;
		
	.data :
	{
		_data = .;
		*(vtable)
		*(.data*)
		_edata = .;
	} > RAM_64 AT>MFlash_256

	/* zero initialized data */
	.bss :
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		_ebss = .;
	} > RAM_64
	
	/* Where we put the heap with cr_clib */
	.cr_heap :
	{
		end = .;
		_pvHeapStart = .;
	} > RAM_64

/*
	Note: (ref: M0000066)
	Moving the stack down by 16 is to work around a GDB bug.
	This space can be reclaimed for Production Builds.
*/	
	_vRamTop = __top_RAM_64 ;
	_vStackTop = _vRamTop - 16;
}
