/* Generated by Nim Compiler v0.10.2 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, amd64, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nim\lib -o c:\users\simon\rationalnes_\rnes\src\nimcache\nes.o c:\users\simon\rationalnes_\rnes\src\nimcache\nes.c */
#define NIM_INTBITS 64
#include "nimbase.h"

#include <stdio.h>
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct romobj137027 romobj137027;
typedef struct TNimObject TNimObject;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct TY131128 TY131128;
struct  TGenericSeq  {
NI len;
NI reserved;
};
struct  NimStringDesc  {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef N_NIMCALL_PTR(void, TY3089) (void* p, NI op);
typedef N_NIMCALL_PTR(void*, TY3094) (void* p);
struct  TNimType  {
NI size;
NU8 kind;
NU8 flags;
TNimType* base;
TNimNode* node;
void* finalizer;
TY3089 marker;
TY3094 deepcopy;
};
struct  TNimObject  {
TNimType* m_type;
};
typedef NIM_CHAR TY137030[16];
struct  romobj137027  {
  TNimObject Sup;
TY137030 Header;
TY131128* Prgbytes;
TY131128* Chrbytes;
};
struct  TNimNode  {
NU8 kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
struct TY131128 {
  TGenericSeq Sup;
  NIM_CHAR data[SEQ_DECL_SIZE];
};
N_NIMCALL(void, initrom_242017)(void);
N_NIMCALL(NIM_BOOL, open_12603)(FILE** f, NimStringDesc* filename, NU8 mode, NI bufsize);
N_NIMCALL(NimStringDesc*, nosparamStr)(NI i);
N_NIMCALL(void, failedassertimpl_86825)(NimStringDesc* msg);
N_NIMCALL(void, loadines_137051)(FILE* romfile, romobj137027* Result);
N_NOINLINE(void, chckNil)(void* p);
N_NIMCALL(void, genericReset)(void* dest, TNimType* mt);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_18801)(void);
static N_INLINE(void, popFrame)(void);
N_NIMCALL(void, run_242209)(void);
N_NIMCALL(void, update_227648)(NI cpucycles, NI divisor);
N_NIMCALL(void, update_223821)(void);
static N_INLINE(NI, subInt)(NI a, NI b);
N_NOINLINE(void, raiseOverflow)(void);
N_NIMCALL(void, main_242245)(void);
N_NIMCALL(void, initppu_223729)(void);
N_NIMCALL(void, initmem_224187)(void);
N_NIMCALL(void, initcpu_227639)(void);
static N_INLINE(void, initStackBottomWith)(void* locals);
N_NOINLINE(void, setStackBottom)(void* thestackbottom);
NIM_EXTERNC N_NOINLINE(void, systemInit)(void);
NIM_EXTERNC N_NOINLINE(void, systemDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_parseutilsInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_parseutilsDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_strutilsInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_strutilsDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_winleanInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_winleanDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_timesInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_timesDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_osInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_osDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_streamsInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_streamsDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_hexInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_hexDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_macrosInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_macrosDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_romInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_romDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_mathInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_mathDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_queuesInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_queuesDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_hashesInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_hashesDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_tablesInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_tablesDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_windowsInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_windowsDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_terminalInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_terminalDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_typetraitsInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_typetraitsDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_typeinfoInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_typeinfoDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_debugInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_debugDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_ppuInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_ppuDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_memInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_memDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_cpuInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_cpuDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_unsignedInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_unsignedDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_sdlInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_sdlDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_colorsInit)(void);
NIM_EXTERNC N_NOINLINE(void, stdlib_colorsDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_screenInit)(void);
NIM_EXTERNC N_NOINLINE(void, HEX00_screenDatInit)(void);
NIM_EXTERNC N_NOINLINE(void, nesInit)(void);
NIM_EXTERNC N_NOINLINE(void, nesDatInit)(void);
STRING_LITERAL(TMP774, "open(romFile, paramStr(1)) ", 27);
NI cycles_242012;
extern romobj137027 nesrom_137046;
extern TNimType NTI137027; /* ROMObj */
extern TFrame* frameptr_16242;

static N_INLINE(void, nimFrame)(TFrame* s) {
	NI LOC1;
	LOC1 = 0;
	{
		if (!(frameptr_16242 == NIM_NIL)) goto LA4;
		LOC1 = 0;
	}
	goto LA2;
	LA4: ;
	{
		LOC1 = ((NI) ((NI16)((*frameptr_16242).calldepth + ((NI16) 1))));
	}
	LA2: ;
	(*s).calldepth = ((NI16) (LOC1));
	(*s).prev = frameptr_16242;
	frameptr_16242 = s;
	{
		if (!((*s).calldepth == ((NI16) 2000))) goto LA9;
		stackoverflow_18801();
	}
	LA9: ;
}

static N_INLINE(void, popFrame)(void) {
	frameptr_16242 = (*frameptr_16242).prev;
}

N_NIMCALL(void, initrom_242017)(void) {
	FILE* romfile;
	nimfr("initRom", "nes.nim")
	romfile = 0;
	nimln(14, "nes.nim");
	{
		NimStringDesc* LOC3;
		NIM_BOOL LOC4;
		nimln(14, "nes.nim");
		nimln(14, "nes.nim");
		nimln(14, "nes.nim");
		LOC3 = 0;
		LOC3 = nosparamStr(1);
		LOC4 = 0;
		LOC4 = open_12603(&romfile, LOC3, ((NU8) 0), -1);
		if (!!(LOC4)) goto LA5;
		nimln(14, "nes.nim");
		failedassertimpl_86825(((NimStringDesc*) &TMP774));
	}
	LA5: ;
	nimln(16, "nes.nim");
	chckNil((void*)(&nesrom_137046));
	genericReset((void*)(&nesrom_137046), (&NTI137027));
	nesrom_137046.Sup.m_type = (&NTI137027);
	loadines_137051(romfile, (&nesrom_137046));
	popFrame();
}

static N_INLINE(NI, subInt)(NI a, NI b) {
	NI result;
	result = 0;
	result = (NI)((NU64)(a) - (NU64)(b));
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (0 <= (NI)(result ^ a));
		if (LOC3) goto LA4;
		LOC3 = (0 <= (NI)(result ^ (NI)((NU64) ~(b))));
		LA4: ;
		if (!LOC3) goto LA5;
		goto BeforeRet;
	}
	LA5: ;
	raiseOverflow();
	BeforeRet: ;
	return result;
}

N_NIMCALL(void, run_242209)(void) {
	nimfr("run", "nes.nim")
	{
		nimln(19, "nes.nim");
		while (1) {
			NI scanlines;
			nimln(21, "nes.nim");
			scanlines = 262;
			{
				nimln(23, "nes.nim");
				while (1) {
					nimln(23, "nes.nim");
					if (!(0 < scanlines)) goto LA4;
					nimln(25, "nes.nim");
					update_227648(1364, 12);
					nimln(26, "nes.nim");
					update_223821();
					nimln(27, "nes.nim");
					scanlines = subInt(scanlines, 1);
				} LA4: ;
			}
		}
	}
	popFrame();
}

N_NIMCALL(void, main_242245)(void) {
	nimfr("main", "nes.nim")
	nimln(34, "nes.nim");
	initrom_242017();
	nimln(35, "nes.nim");
	initppu_223729();
	nimln(36, "nes.nim");
	initmem_224187();
	nimln(37, "nes.nim");
	initcpu_227639();
	nimln(39, "nes.nim");
	run_242209();
	popFrame();
}

static N_INLINE(void, initStackBottomWith)(void* locals) {
	setStackBottom(locals);
}
void PreMainInner() {
	systemInit();
	stdlib_parseutilsDatInit();
	stdlib_strutilsDatInit();
	stdlib_winleanDatInit();
	stdlib_timesDatInit();
	stdlib_osDatInit();
	stdlib_streamsDatInit();
	HEX00_hexDatInit();
	stdlib_macrosDatInit();
	HEX00_romDatInit();
	stdlib_mathDatInit();
	stdlib_queuesDatInit();
	stdlib_hashesDatInit();
	stdlib_tablesDatInit();
	stdlib_windowsDatInit();
	stdlib_terminalDatInit();
	stdlib_typetraitsDatInit();
	stdlib_typeinfoDatInit();
	HEX00_debugDatInit();
	HEX00_ppuDatInit();
	HEX00_memDatInit();
	HEX00_cpuDatInit();
	stdlib_unsignedDatInit();
	stdlib_sdlDatInit();
	stdlib_colorsDatInit();
	HEX00_screenDatInit();
	nesDatInit();
	stdlib_parseutilsInit();
	stdlib_strutilsInit();
	stdlib_winleanInit();
	stdlib_timesInit();
	stdlib_osInit();
	stdlib_streamsInit();
	HEX00_hexInit();
	stdlib_macrosInit();
	HEX00_romInit();
	stdlib_mathInit();
	stdlib_queuesInit();
	stdlib_hashesInit();
	stdlib_tablesInit();
	stdlib_windowsInit();
	stdlib_terminalInit();
	stdlib_typetraitsInit();
	stdlib_typeinfoInit();
	HEX00_debugInit();
	HEX00_ppuInit();
	HEX00_memInit();
	HEX00_cpuInit();
	stdlib_unsignedInit();
	stdlib_sdlInit();
	stdlib_colorsInit();
	HEX00_screenInit();
}

void PreMain() {
	void (*volatile inner)();
	systemDatInit();
	inner = PreMainInner;
	initStackBottomWith((void *)&inner);
	(*inner)();
}

int cmdCount;
char** cmdLine;
char** gEnv;
N_CDECL(void, NimMainInner)(void) {
	nesInit();
}

N_CDECL(void, NimMain)(void) {
	void (*volatile inner)();
	PreMain();
	inner = NimMainInner;
	initStackBottomWith((void *)&inner);
	(*inner)();
}

int main(int argc, char** args, char** env) {
	cmdLine = args;
	cmdCount = argc;
	gEnv = env;
	NimMain();
	return nim_program_result;
}

NIM_EXTERNC N_NOINLINE(void, nesInit)(void) {
	nimfr("nes", "nes.nim")
	nimln(41, "nes.nim");
	main_242245();
	popFrame();
}

NIM_EXTERNC N_NOINLINE(void, nesDatInit)(void) {
}
