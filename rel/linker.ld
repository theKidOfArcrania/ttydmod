/* Symbols for us to be able to call global constructors and destructors */
SECTIONS {
  .init :  { }
  .text :  {
    *(.text)
    *(.text.*)
  }
  .ctors : {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  }
  .dtors : {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  }
  .rodata :{ *(.rodata*) }
  .data :  { *(.data*) *(extabindex) *(extab) }
  .bss :   { *(.bss*) }
}

_ctors_start = ADDR(.ctors);
_ctors_end = _ctors_start + SIZEOF(.ctors);
_dtors_start = ADDR(.dtors);
_dtors_end = _dtors_start + SIZEOF(.dtors);
