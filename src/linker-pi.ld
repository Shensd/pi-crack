SECTIONS
{
	. = 0x00;
	.text.boot : { *(.text.boot) }
	.text : { *(.text) }
	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss*) } 
	bss_end = .;
	rodata_begin = .;
	.rodata : { *(.rodata) }
	rodata_end = .;
	data_begin = .;
	.data : { *(.data) }
	data_end = .;
}
