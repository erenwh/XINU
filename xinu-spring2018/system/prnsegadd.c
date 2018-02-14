/**
  * Output should follow the exact format mentioned below (0x12121212 and XYZ should be replaced with the actual answers):
  "Start of Text at 0x12121212, end of Text at 0x12121212."
  "Start of Data at 0x12121212, end of Data at 0x12121212."
  "Start of Bss at 0x12121212, end of Bss at 0x12121212."
  "End of XINU at 0x12121212."
  "Text Length : XYZ bytes"
  "Data Length : XYZ bytes"
  "BSS Length : XYZ bytes"

  */
#include <xinu.h>
#include <stdio.h>

void prnsegadd() {
    kprintf("Start of Text at 0X%08X, end of Text at 0X%08X.\n", &text, &etext);
    kprintf("Start of Data at 0X%08X, end of Data at 0X%08X.\n", &data, &edata);
    kprintf("Start of Bss at 0X%08X, end of Bss at 0X%08X.\n", &bss, &ebss);
    kprintf("End of XINU at 0X%08X.\n", &end);
    kprintf("Text Length : %10d bytes\n", (uint32)&etext - (uint32)&text);
    kprintf("Data Length : %10d bytes\n", (uint32)&edata - (uint32)&data);
    kprintf("BSS Length : %10d bytes\n", (uint32)&ebss - (uint32)&bss);
    
}
