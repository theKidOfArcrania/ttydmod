CC=wine ~/git/ttyd_source/tools/mwcc_compiler/GC/2.6/mwcceppc.exe
CPPFLAGS=-gccincludes -I../include -w on,nounused -enum int -fp_contract on

COMMON_FLAGS=-msgstyle gcc -sdata 0 -sdata2 0 -fp hard
LDFLAGS=$(COMMON_FLAGS) -m _prolog -r1 -lcf ../ldscript.lcf
CFLAGS=$(COMMON_FLAGS) -rostr -multibyte -use_lmw_stmw on -inline auto,deferred -Cpp_exceptions off -O4,p
LD=wine ~/git/ttyd_source/tools/mwcc_compiler/GC/2.6/mwldeppc.exe

MODROOT=../..
MOD_MANAGER= ../../ttyd-mod-manager

export MWCIncludes=
export MWLibraries=
export MWLibraryFiles=

all: aaa.rel
	cp $^ $(MODROOT)/mod/P-G8ME/files/rel/
	$(MOD_MANAGER) -r $(MODROOT) build

clean:
	rm -f *.o *.pelf aaa

aaa_00.c: aaa_00.h aaa.h
aaa.c: aaa_00.h aaa.h

aaa.elf: aaa_00.o aaa.o
	$(LD) $(LDFLAGS) -o $@ $^

%.rel: %.elf $(MOD_MANAGER)
	$(MOD_MANAGER) -L -r $(MODROOT) make-rel -o $@ --symdb ../../config/G8ME/us_symbols.csv $<
