from pwn import *

context.arch = 'powerpc'

loader_addr = 0x80004588
hook_addr   = 0x8006fe38

memcpy            = 0x8000519c
getMarioStDvdRoot = 0x80007388
__memFree         = 0x800300C4
__memAlloc        = 0x800300F0
fileAllocf        = 0x8018a61c
fileFree          = 0x8018a260
OSLink            = 0x8029A8E4
OSUnlink          = 0x8029AB40

def SYM(expr):
    return f'({expr} + __start - {loader_addr})'

def mk_code(SYM):
    return f"""
__start:
    ;# Initialize static values used for addresses
    lis r31,__start@ha

    ;# Open the mod.rel file
    bl {SYM(getMarioStDvdRoot)}
    mr r5, r3
    addi r4, r31, modRelPath@l
    li r3, 0
    crclr 4*cr1+eq
    bl {SYM(fileAllocf)}
    mr. r29, r3
    beq _fail

    ;# Allocate memory for rel file
    lwz r28, 0xA0(r29)
    lwz r3, 4(r28)
    bl malloc
    mr r30, r3

    ;# Copy into memory from file and free file object
    lwz r27, 0(r28)
    lwz r5, 4(r28)
    mr r4, r27
    bl {SYM(memcpy)}
    mr r3, r29
    bl {SYM(fileFree)}

    ;# Get the BSS Area size and allocate memory for it
    lwz r3,0x20(r27)
    bl malloc
    mr r29, r3

    ;# Link the functions in the REL
    mr r3, r30 ;# rel module
    mr r4, r29 ;# bss
    bl {SYM(OSLink)}
    cmpwi r3, 1
    bne _failFree

    ;# Store the BSS area and the module
    stw r29, 0x414c(r31) ;# Pointer to the BSS Area
    stw r30, 0x4150(r31) ;# Pointer to the REL module

    ;# Invoke REL module prolog
    lwz r30, 0x34(r30)
    mtctr r30
    bctrl
    b _exit

_failFree:
    mr r3, r30
    bl {SYM(OSUnlink)}
    mr r3, r30
    bl free
    mr r3, r29
    bl free

_fail:
    li r3, 0
    lwz r3, 0(r3) ;# Cause some segfault

_exit:
    ;# Add back in the overwritten instruction
    li r3,0
    b {SYM(hook_addr + 4)}

free:
    mr. r4, r3
    beq _freeDone
    li r3, 0 ;# Heap to use
    b {SYM(__memFree)}
_freeDone:
    blr

malloc:
    mr r4, r3
    li r3, 0 ;# Heap to use
    b {SYM(__memAlloc)}

modRelPath:
    .asciz "%s/rel/mod.rel"

__end:
"""

def mk_jmp_code(SYM):
    return f'__start: bl {SYM(loader_addr)}'

PATCHES = [
    (loader_addr, mk_code),
    (hook_addr, mk_jmp_code),
]

out = b'PATD' + p32(len(PATCHES))
for (addr, builder) in PATCHES:
    cur_addr = addr
    def SYM(expr):
        return f'({expr} + __start - {cur_addr})'
    code = asm(builder(SYM), vma=cur_addr)
    out += p32(addr) + p32(len(code)) + code

os.makedirs('mod/P-G8ME/sys', exist_ok = True)
with open('mod/P-G8ME/sys/main.dol.binpatch', 'wb') as f:
    f.write(out)
