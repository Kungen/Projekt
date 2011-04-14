/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-9
 * Generated linker script include file for 
 * (created from LinkMemoryTemplate (v3.3.7 (201005201503)) on Mon Mar 07 09:53:27 CET 2011)
*/

MEMORY
{
  /* Define each memory region */
  MFlash_256 (rx) : ORIGIN = 0x0, LENGTH = 0x40000 /* 256k */
  RAM_64 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x10000 /* 64k */

}
  /* Define a symbol for the top of each memory region */
  __top_MFlash_256 = 0x0 + 0x40000;
  __top_RAM_64 = 0x20000000 + 0x10000;

