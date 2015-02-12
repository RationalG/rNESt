/* Generated by Nimrod Compiler v0.9.6 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, amd64, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nimrod\lib -o c:\users\simon\rationalnes_\rnes\nimcache\terminal.o c:\users\simon\rationalnes_\rnes\nimcache\terminal.c */
#define NIM_INTBITS 64
#include "nimbase.h"

#include <string.h>

#include <stdio.h>

#include <io.h>
typedef struct TY187006 TY187006;
typedef struct tconsolescreenbufferinfo147715 tconsolescreenbufferinfo147715;
typedef struct coord147703 coord147703;
typedef struct smallrect147709 smallrect147709;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef N_STDCALL_PTR(NI, TY168624) (NI32 nstdhandle);
typedef N_STDCALL_PTR(NI32, TY168701) (NI hsourceprocesshandle, NI hsourcehandle, NI htargetprocesshandle, NI* lptargethandle, NI32 dwdesiredaccess, NI32 binherithandle, NI32 dwoptions);
typedef N_STDCALL_PTR(NI, TY168216) (void);
struct TY187006 {
NI Field0;
NI Field1;
};
struct  coord147703  {
NI16 X;
NI16 Y;
};
struct  smallrect147709  {
NI16 Left;
NI16 Top;
NI16 Right;
NI16 Bottom;
};
struct  tconsolescreenbufferinfo147715  {
coord147703 Dwsize;
coord147703 Dwcursorposition;
NI16 Wattributes;
smallrect147709 Srwindow;
coord147703 Dwmaximumwindowsize;
};
typedef N_STDCALL_PTR(NI32, TY174363) (NI hconsoleoutput, tconsolescreenbufferinfo147715* lpconsolescreenbufferinfo);
typedef N_STDCALL_PTR(NI32, TY174415) (NI hconsoleoutput, coord147703 dwcursorposition);
typedef N_STDCALL_PTR(NI32, TY167456) (NI hconsoleoutput, NIM_CHAR ccharacter, NI32 nlength, coord147703 dwwritecoord, NI32* lpnumberofcharswritten);
typedef N_STDCALL_PTR(NI32, TY174339) (NI hconsoleoutput, NI16 wattribute, NI32 nlength, coord147703 dwwritecoord, NI32* lpnumberofattrswritten);
typedef N_STDCALL_PTR(NI32, TY174438) (NI hconsoleoutput, NI16 wattributes);
struct  TGenericSeq  {
NI len;
NI reserved;
};
struct  NimStringDesc  {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef NI TY190404[8];
typedef NI TY190605[8];
N_NIMCALL(void, oserror_110035)(NI32 errorcode);
N_NIMCALL(NI32, oslasterror_110067)(void);
N_NIMCALL(TY187006, getcursorpos_187004)(void);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_17801)(void);
static N_INLINE(void, popFrame)(void);
N_NIMCALL(NI16, getattributes_187019)(void);
N_NIMCALL(void, setcursorpos_187212)(NI x, NI y);
static N_INLINE(NI, chckRange)(NI i, NI a, NI b);
N_NOINLINE(void, raiseRangeError)(NI64 val);
N_NIMCALL(void, setcursorxpos_187409)(NI x);
N_NIMCALL(void, setcursorypos_187612)(NI y);
N_NIMCALL(void, cursorup_188004)(NI count);
static N_INLINE(NI, subInt)(NI a, NI b);
N_NOINLINE(void, raiseOverflow)(void);
N_NIMCALL(void, cursordown_188220)(NI count);
static N_INLINE(NI, addInt)(NI a, NI b);
N_NIMCALL(void, cursorforward_188420)(NI count);
N_NIMCALL(void, cursorbackward_188620)(NI count);
N_NIMCALL(void, eraseline_189004)(void);
N_NIMCALL(NI, mulInt)(NI a, NI b);
N_NIMCALL(void, erasescreen_189218)(void);
N_NOCONV(void, resetattributes_189417)(void);
N_NIMCALL(void, setstyle_189801)(NU8 style);
N_NIMCALL(void, writestyled_190060)(NimStringDesc* txt, NU8 style);
N_NIMCALL(void, write_12065)(FILE* f, NimStringDesc* s);
N_NIMCALL(void, setforegroundcolor_190233)(NU8 fg, NIM_BOOL bright);
N_NOINLINE(void, raiseIndexError)(void);
N_NIMCALL(void, setbackgroundcolor_190415)(NU8 bg, NIM_BOOL bright);
N_NIMCALL(NIM_BOOL, isatty_190619)(FILE* f);
N_NIMCALL(void, styledechoprocessarg_190813)(NimStringDesc* s);
N_NIMCALL(void, styledechoprocessarg_190824)(NU8 style);
N_NIMCALL(void, styledechoprocessarg_190834)(NU8 style);
N_NIMCALL(void, styledechoprocessarg_190844)(NU8 color);
N_NIMCALL(void, styledechoprocessarg_190853)(NU8 color);
NIM_CONST TY190404 lookup_190403 = {0,
4,
2,
6,
1,
5,
3,
7}
;
NIM_CONST TY190605 lookup_190604 = {0,
64,
32,
96,
16,
80,
48,
112}
;
NI conhandle_187001;
extern TY168624 Dl_168623;
extern TY168701 Dl_168700;
extern TY168216 Dl_168215;
extern TY174363 Dl_174362;
extern TFrame* frameptr_15242;
NI16 oldattr_187028;
extern TY174415 Dl_174414;
extern TY167456 Dl_167455;
extern TY174339 Dl_174338;
extern TY174438 Dl_174437;

static N_INLINE(void, nimFrame)(TFrame* s) {
	NI LOC1;
	LOC1 = 0;
	{
		if (!(frameptr_15242 == NIM_NIL)) goto LA4;
		LOC1 = 0;
	}
	goto LA2;
	LA4: ;
	{
		LOC1 = ((NI) ((NI16)((*frameptr_15242).calldepth + ((NI16) 1))));
	}
	LA2: ;
	(*s).calldepth = ((NI16) (LOC1));
	(*s).prev = frameptr_15242;
	frameptr_15242 = s;
	{
		if (!((*s).calldepth == ((NI16) 2000))) goto LA9;
		stackoverflow_17801();
	}
	LA9: ;
}

static N_INLINE(void, popFrame)(void) {
	frameptr_15242 = (*frameptr_15242).prev;
}

N_NIMCALL(TY187006, getcursorpos_187004)(void) {
	TY187006 result;
	tconsolescreenbufferinfo147715 c;
	nimfr("getCursorPos", "terminal.nim")
	memset((void*)&result, 0, sizeof(result));
	memset((void*)&c, 0, sizeof(c));
	nimln(34, "terminal.nim");
	{
		NI32 LOC3;
		NI32 LOC6;
		nimln(34, "terminal.nim");
		nimln(34, "terminal.nim");
		LOC3 = 0;
		LOC3 = Dl_174362(conhandle_187001, &c);
		if (!(LOC3 == ((NI32) 0))) goto LA4;
		nimln(34, "terminal.nim");
		nimln(34, "terminal.nim");
		LOC6 = 0;
		LOC6 = oslasterror_110067();
		oserror_110035(LOC6);
	}
	LA4: ;
	nimln(35, "terminal.nim");
	nimln(35, "terminal.nim");
	result.Field0 = ((NI) (c.Dwcursorposition.X));
	result.Field1 = ((NI) (c.Dwcursorposition.Y));
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(NI16, getattributes_187019)(void) {
	NI16 result;
	tconsolescreenbufferinfo147715 c;
	nimfr("getAttributes", "terminal.nim")
	result = 0;
	memset((void*)&c, 0, sizeof(c));
	nimln(40, "terminal.nim");
	{
		NI32 LOC3;
		nimln(40, "terminal.nim");
		nimln(40, "terminal.nim");
		nimln(40, "terminal.nim");
		LOC3 = 0;
		LOC3 = Dl_174362(conhandle_187001, &c);
		if (!!((LOC3 == ((NI32) 0)))) goto LA4;
		nimln(41, "terminal.nim");
		nimln(41, "terminal.nim");
		result = c.Wattributes;
		goto BeforeRet;
	}
	LA4: ;
	nimln(42, "terminal.nim");
	nimln(42, "terminal.nim");
	result = ((NI16) 112);
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

static N_INLINE(NI, chckRange)(NI i, NI a, NI b) {
	NI result;
	result = 0;
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (a <= i);
		if (!(LOC3)) goto LA4;
		LOC3 = (i <= b);
		LA4: ;
		if (!LOC3) goto LA5;
		result = i;
		goto BeforeRet;
	}
	goto LA1;
	LA5: ;
	{
		raiseRangeError(((NI64) (i)));
	}
	LA1: ;
	BeforeRet: ;
	return result;
}

N_NIMCALL(void, setcursorpos_187212)(NI x, NI y) {
	coord147703 c;
	nimfr("setCursorPos", "terminal.nim")
	memset((void*)&c, 0, sizeof(c));
	nimln(52, "terminal.nim");
	c.X = ((NI16)chckRange(x, ((NI16) -32768), ((NI16) 32767)));
	nimln(53, "terminal.nim");
	c.Y = ((NI16)chckRange(y, ((NI16) -32768), ((NI16) 32767)));
	nimln(54, "terminal.nim");
	{
		NI32 LOC3;
		NI32 LOC6;
		nimln(54, "terminal.nim");
		nimln(54, "terminal.nim");
		LOC3 = 0;
		LOC3 = Dl_174414(conhandle_187001, c);
		if (!(LOC3 == ((NI32) 0))) goto LA4;
		nimln(54, "terminal.nim");
		nimln(54, "terminal.nim");
		LOC6 = 0;
		LOC6 = oslasterror_110067();
		oserror_110035(LOC6);
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(void, setcursorxpos_187409)(NI x) {
	tconsolescreenbufferinfo147715 scrbuf;
	NI hstdout;
	coord147703 origin;
	nimfr("setCursorXPos", "terminal.nim")
	memset((void*)&scrbuf, 0, sizeof(scrbuf));
	nimln(63, "terminal.nim");
	hstdout = conhandle_187001;
	nimln(64, "terminal.nim");
	{
		NI32 LOC3;
		NI32 LOC6;
		nimln(64, "terminal.nim");
		nimln(64, "terminal.nim");
		LOC3 = 0;
		LOC3 = Dl_174362(hstdout, &scrbuf);
		if (!(LOC3 == ((NI32) 0))) goto LA4;
		nimln(64, "terminal.nim");
		nimln(64, "terminal.nim");
		LOC6 = 0;
		LOC6 = oslasterror_110067();
		oserror_110035(LOC6);
	}
	LA4: ;
	nimln(65, "terminal.nim");
	origin = scrbuf.Dwcursorposition;
	nimln(66, "terminal.nim");
	origin.X = ((NI16)chckRange(x, ((NI16) -32768), ((NI16) 32767)));
	nimln(67, "terminal.nim");
	{
		NI32 LOC9;
		NI32 LOC12;
		nimln(67, "terminal.nim");
		nimln(67, "terminal.nim");
		LOC9 = 0;
		LOC9 = Dl_174414(conhandle_187001, origin);
		if (!(LOC9 == ((NI32) 0))) goto LA10;
		nimln(67, "terminal.nim");
		nimln(67, "terminal.nim");
		LOC12 = 0;
		LOC12 = oslasterror_110067();
		oserror_110035(LOC12);
	}
	LA10: ;
	popFrame();
}

N_NIMCALL(void, setcursorypos_187612)(NI y) {
	tconsolescreenbufferinfo147715 scrbuf;
	NI hstdout;
	coord147703 origin;
	nimfr("setCursorYPos", "terminal.nim")
	memset((void*)&scrbuf, 0, sizeof(scrbuf));
	nimln(77, "terminal.nim");
	hstdout = conhandle_187001;
	nimln(78, "terminal.nim");
	{
		NI32 LOC3;
		NI32 LOC6;
		nimln(78, "terminal.nim");
		nimln(78, "terminal.nim");
		LOC3 = 0;
		LOC3 = Dl_174362(hstdout, &scrbuf);
		if (!(LOC3 == ((NI32) 0))) goto LA4;
		nimln(78, "terminal.nim");
		nimln(78, "terminal.nim");
		LOC6 = 0;
		LOC6 = oslasterror_110067();
		oserror_110035(LOC6);
	}
	LA4: ;
	nimln(79, "terminal.nim");
	origin = scrbuf.Dwcursorposition;
	nimln(80, "terminal.nim");
	origin.Y = ((NI16)chckRange(y, ((NI16) -32768), ((NI16) 32767)));
	nimln(81, "terminal.nim");
	{
		NI32 LOC9;
		NI32 LOC12;
		nimln(81, "terminal.nim");
		nimln(81, "terminal.nim");
		LOC9 = 0;
		LOC9 = Dl_174414(conhandle_187001, origin);
		if (!(LOC9 == ((NI32) 0))) goto LA10;
		nimln(81, "terminal.nim");
		nimln(81, "terminal.nim");
		LOC12 = 0;
		LOC12 = oslasterror_110067();
		oserror_110035(LOC12);
	}
	LA10: ;
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

N_NIMCALL(void, cursorup_188004)(NI count) {
	TY187006 p;
	nimfr("cursorUp", "terminal.nim")
	nimln(88, "terminal.nim");
	p = getcursorpos_187004();
	nimln(89, "terminal.nim");
	p.Field1 = subInt(p.Field1, count);
	nimln(90, "terminal.nim");
	setcursorpos_187212(p.Field0, p.Field1);
	popFrame();
}

static N_INLINE(NI, addInt)(NI a, NI b) {
	NI result;
	result = 0;
	result = (NI)((NU64)(a) + (NU64)(b));
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (0 <= (NI)(result ^ a));
		if (LOC3) goto LA4;
		LOC3 = (0 <= (NI)(result ^ b));
		LA4: ;
		if (!LOC3) goto LA5;
		goto BeforeRet;
	}
	LA5: ;
	raiseOverflow();
	BeforeRet: ;
	return result;
}

N_NIMCALL(void, cursordown_188220)(NI count) {
	TY187006 p;
	nimfr("cursorDown", "terminal.nim")
	nimln(97, "terminal.nim");
	p = getcursorpos_187004();
	nimln(98, "terminal.nim");
	p.Field1 = addInt(p.Field1, count);
	nimln(99, "terminal.nim");
	setcursorpos_187212(p.Field0, p.Field1);
	popFrame();
}

N_NIMCALL(void, cursorforward_188420)(NI count) {
	TY187006 p;
	nimfr("cursorForward", "terminal.nim")
	nimln(106, "terminal.nim");
	p = getcursorpos_187004();
	nimln(107, "terminal.nim");
	p.Field0 = addInt(p.Field0, count);
	nimln(108, "terminal.nim");
	setcursorpos_187212(p.Field0, p.Field1);
	popFrame();
}

N_NIMCALL(void, cursorbackward_188620)(NI count) {
	TY187006 p;
	nimfr("cursorBackward", "terminal.nim")
	nimln(115, "terminal.nim");
	p = getcursorpos_187004();
	nimln(116, "terminal.nim");
	p.Field0 = subInt(p.Field0, count);
	nimln(117, "terminal.nim");
	setcursorpos_187212(p.Field0, p.Field1);
	popFrame();
}

N_NIMCALL(void, eraseline_189004)(void) {
	tconsolescreenbufferinfo147715 scrbuf;
	NI32 numwrote;
	NI hstdout;
	coord147703 origin;
	NI16 ht;
	NI TMP322;
	NI16 wt;
	NI TMP323;
	nimfr("eraseLine", "terminal.nim")
	memset((void*)&scrbuf, 0, sizeof(scrbuf));
	numwrote = 0;
	nimln(157, "terminal.nim");
	hstdout = conhandle_187001;
	nimln(158, "terminal.nim");
	{
		NI32 LOC3;
		NI32 LOC6;
		nimln(158, "terminal.nim");
		nimln(158, "terminal.nim");
		LOC3 = 0;
		LOC3 = Dl_174362(hstdout, &scrbuf);
		if (!(LOC3 == ((NI32) 0))) goto LA4;
		nimln(158, "terminal.nim");
		nimln(158, "terminal.nim");
		LOC6 = 0;
		LOC6 = oslasterror_110067();
		oserror_110035(LOC6);
	}
	LA4: ;
	nimln(159, "terminal.nim");
	origin = scrbuf.Dwcursorposition;
	nimln(160, "terminal.nim");
	origin.X = ((NI16) 0);
	nimln(161, "terminal.nim");
	{
		NI32 LOC9;
		NI32 LOC12;
		nimln(161, "terminal.nim");
		nimln(161, "terminal.nim");
		LOC9 = 0;
		LOC9 = Dl_174414(conhandle_187001, origin);
		if (!(LOC9 == ((NI32) 0))) goto LA10;
		nimln(161, "terminal.nim");
		nimln(161, "terminal.nim");
		LOC12 = 0;
		LOC12 = oslasterror_110067();
		oserror_110035(LOC12);
	}
	LA10: ;
	nimln(162, "terminal.nim");
	nimln(162, "terminal.nim");
	TMP322 = subInt(scrbuf.Dwsize.Y, origin.Y);
	if (TMP322 < -32768 || TMP322 > 32767) raiseOverflow();
	ht = (NI16)(TMP322);
	nimln(163, "terminal.nim");
	nimln(163, "terminal.nim");
	TMP323 = subInt(scrbuf.Dwsize.X, origin.X);
	if (TMP323 < -32768 || TMP323 > 32767) raiseOverflow();
	wt = (NI16)(TMP323);
	nimln(164, "terminal.nim");
	{
		NI TMP324;
		NI32 LOC15;
		NI32 LOC18;
		nimln(165, "terminal.nim");
		nimln(164, "terminal.nim");
		nimln(164, "terminal.nim");
		TMP324 = mulInt(ht, wt);
		if (TMP324 < -32768 || TMP324 > 32767) raiseOverflow();
		LOC15 = 0;
		LOC15 = Dl_167455(hstdout, 32, ((NI32) ((NI16)(TMP324))), origin, &numwrote);
		if (!(LOC15 == ((NI32) 0))) goto LA16;
		nimln(166, "terminal.nim");
		nimln(166, "terminal.nim");
		LOC18 = 0;
		LOC18 = oslasterror_110067();
		oserror_110035(LOC18);
	}
	LA16: ;
	nimln(167, "terminal.nim");
	{
		NI TMP325;
		NI32 LOC21;
		NI32 LOC24;
		nimln(168, "terminal.nim");
		nimln(167, "terminal.nim");
		nimln(167, "terminal.nim");
		TMP325 = mulInt(ht, wt);
		if (TMP325 < -32768 || TMP325 > 32767) raiseOverflow();
		LOC21 = 0;
		LOC21 = Dl_174338(hstdout, scrbuf.Wattributes, ((NI32) ((NI16)(TMP325))), scrbuf.Dwcursorposition, &numwrote);
		if (!(LOC21 == ((NI32) 0))) goto LA22;
		nimln(169, "terminal.nim");
		nimln(169, "terminal.nim");
		LOC24 = 0;
		LOC24 = oslasterror_110067();
		oserror_110035(LOC24);
	}
	LA22: ;
	popFrame();
}

N_NIMCALL(void, erasescreen_189218)(void) {
	tconsolescreenbufferinfo147715 scrbuf;
	NI32 numwrote;
	coord147703 origin;
	NI hstdout;
	nimfr("eraseScreen", "terminal.nim")
	memset((void*)&scrbuf, 0, sizeof(scrbuf));
	numwrote = 0;
	memset((void*)&origin, 0, sizeof(origin));
	nimln(180, "terminal.nim");
	hstdout = conhandle_187001;
	nimln(181, "terminal.nim");
	{
		NI32 LOC3;
		NI32 LOC6;
		nimln(181, "terminal.nim");
		nimln(181, "terminal.nim");
		LOC3 = 0;
		LOC3 = Dl_174362(hstdout, &scrbuf);
		if (!(LOC3 == ((NI32) 0))) goto LA4;
		nimln(181, "terminal.nim");
		nimln(181, "terminal.nim");
		LOC6 = 0;
		LOC6 = oslasterror_110067();
		oserror_110035(LOC6);
	}
	LA4: ;
	nimln(182, "terminal.nim");
	{
		NI TMP326;
		NI32 LOC9;
		NI32 LOC12;
		nimln(183, "terminal.nim");
		nimln(182, "terminal.nim");
		nimln(182, "terminal.nim");
		TMP326 = mulInt(scrbuf.Dwsize.X, scrbuf.Dwsize.Y);
		if (TMP326 < -32768 || TMP326 > 32767) raiseOverflow();
		LOC9 = 0;
		LOC9 = Dl_167455(hstdout, 32, ((NI32) ((NI16)(TMP326))), origin, &numwrote);
		if (!(LOC9 == ((NI32) 0))) goto LA10;
		nimln(184, "terminal.nim");
		nimln(184, "terminal.nim");
		LOC12 = 0;
		LOC12 = oslasterror_110067();
		oserror_110035(LOC12);
	}
	LA10: ;
	nimln(185, "terminal.nim");
	{
		NI TMP327;
		NI32 LOC15;
		NI32 LOC18;
		nimln(187, "terminal.nim");
		nimln(185, "terminal.nim");
		nimln(186, "terminal.nim");
		TMP327 = mulInt(scrbuf.Dwsize.X, scrbuf.Dwsize.Y);
		if (TMP327 < -32768 || TMP327 > 32767) raiseOverflow();
		LOC15 = 0;
		LOC15 = Dl_174338(hstdout, scrbuf.Wattributes, ((NI32) ((NI16)(TMP327))), origin, &numwrote);
		if (!(LOC15 == ((NI32) 0))) goto LA16;
		nimln(188, "terminal.nim");
		nimln(188, "terminal.nim");
		LOC18 = 0;
		LOC18 = oslasterror_110067();
		oserror_110035(LOC18);
	}
	LA16: ;
	nimln(189, "terminal.nim");
	setcursorxpos_187409(0);
	popFrame();
}

N_NOCONV(void, resetattributes_189417)(void) {
	NI32 LOC1;
	nimfr("resetAttributes", "terminal.nim")
	nimln(197, "terminal.nim");
	nimln(197, "terminal.nim");
	LOC1 = 0;
	LOC1 = Dl_174437(conhandle_187001, oldattr_187028);
	popFrame();
}

N_NIMCALL(void, setstyle_189801)(NU8 style) {
	NI16 a;
	NI32 LOC17;
	nimfr("setStyle", "terminal.nim")
	nimln(220, "terminal.nim");
	a = ((NI16) 0);
	nimln(221, "terminal.nim");
	{
		nimln(221, "terminal.nim");
		if (!((style &(1<<(((((NU8) 1)- 1))&7)))!=0)) goto LA3;
		nimln(221, "terminal.nim");
		nimln(221, "terminal.nim");
		a = (NI16)(a | ((NI16) 8));
	}
	LA3: ;
	nimln(222, "terminal.nim");
	{
		nimln(222, "terminal.nim");
		if (!((style &(1<<(((((NU8) 5)- 1))&7)))!=0)) goto LA7;
		nimln(222, "terminal.nim");
		nimln(222, "terminal.nim");
		a = (NI16)(a | ((NI16) 128));
	}
	LA7: ;
	nimln(223, "terminal.nim");
	{
		nimln(223, "terminal.nim");
		if (!((style &(1<<(((((NU8) 7)- 1))&7)))!=0)) goto LA11;
		nimln(223, "terminal.nim");
		nimln(223, "terminal.nim");
		a = (NI16)(a | ((NI16) 16384));
	}
	LA11: ;
	nimln(224, "terminal.nim");
	{
		nimln(224, "terminal.nim");
		if (!((style &(1<<(((((NU8) 4)- 1))&7)))!=0)) goto LA15;
		nimln(224, "terminal.nim");
		nimln(224, "terminal.nim");
		a = (NI16)(a | ((NI16) -32768));
	}
	LA15: ;
	nimln(225, "terminal.nim");
	nimln(225, "terminal.nim");
	LOC17 = 0;
	LOC17 = Dl_174437(conhandle_187001, a);
	popFrame();
}

N_NIMCALL(void, writestyled_190060)(NimStringDesc* txt, NU8 style) {
	NI16 old;
	NI32 LOC1;
	nimfr("writeStyled", "terminal.nim")
	nimln(233, "terminal.nim");
	old = getattributes_187019();
	nimln(234, "terminal.nim");
	setstyle_189801(style);
	nimln(235, "terminal.nim");
	write_12065(stdout, txt);
	nimln(236, "terminal.nim");
	nimln(236, "terminal.nim");
	LOC1 = 0;
	LOC1 = Dl_174437(conhandle_187001, old);
	popFrame();
}

N_NIMCALL(void, setforegroundcolor_190233)(NU8 fg, NIM_BOOL bright) {
	NI16 old;
	NI16 LOC1;
	NI32 LOC6;
	nimfr("setForegroundColor", "terminal.nim")
	nimln(270, "terminal.nim");
	nimln(270, "terminal.nim");
	nimln(270, "terminal.nim");
	LOC1 = 0;
	LOC1 = getattributes_187019();
	old = (NI16)(LOC1 & ((NI16) -8));
	nimln(271, "terminal.nim");
	{
		if (!bright) goto LA4;
		nimln(272, "terminal.nim");
		nimln(272, "terminal.nim");
		old = (NI16)(old | ((NI16) 8));
	}
	LA4: ;
	nimln(282, "terminal.nim");
	nimln(282, "terminal.nim");
	nimln(282, "terminal.nim");
	nimln(282, "terminal.nim");
	if (fg < 30 || fg > 37) raiseIndexError();
	LOC6 = 0;
	LOC6 = Dl_174437(conhandle_187001, ((NI16)(NU16)(NU)((NI)(((NI) (old)) | lookup_190403[(fg)- 30]))));
	popFrame();
}

N_NIMCALL(void, setbackgroundcolor_190415)(NU8 bg, NIM_BOOL bright) {
	NI16 old;
	NI16 LOC1;
	NI32 LOC6;
	nimfr("setBackgroundColor", "terminal.nim")
	nimln(291, "terminal.nim");
	nimln(291, "terminal.nim");
	nimln(291, "terminal.nim");
	LOC1 = 0;
	LOC1 = getattributes_187019();
	old = (NI16)(LOC1 & ((NI16) -113));
	nimln(292, "terminal.nim");
	{
		if (!bright) goto LA4;
		nimln(293, "terminal.nim");
		nimln(293, "terminal.nim");
		old = (NI16)(old | ((NI16) 128));
	}
	LA4: ;
	nimln(303, "terminal.nim");
	nimln(303, "terminal.nim");
	nimln(303, "terminal.nim");
	nimln(303, "terminal.nim");
	if (bg < 40 || bg > 47) raiseIndexError();
	LOC6 = 0;
	LOC6 = Dl_174437(conhandle_187001, ((NI16)(NU16)(NU)((NI)(((NI) (old)) | lookup_190604[(bg)- 40]))));
	popFrame();
}

N_NIMCALL(NIM_BOOL, isatty_190619)(FILE* f) {
	NIM_BOOL result;
	int LOC1;
	int LOC2;
	nimfr("isatty", "terminal.nim")
	result = 0;
	nimln(318, "terminal.nim");
	nimln(318, "terminal.nim");
	nimln(318, "terminal.nim");
	nimln(318, "terminal.nim");
	nimln(318, "terminal.nim");
	LOC1 = 0;
	LOC1 = fileno(f);
	LOC2 = 0;
	LOC2 = _isatty(LOC1);
	result = !((LOC2 == ((NI32) 0)));
	popFrame();
	return result;
}

N_NIMCALL(void, styledechoprocessarg_190813)(NimStringDesc* s) {
	nimfr("styledEchoProcessArg", "terminal.nim")
	nimln(320, "terminal.nim");
	write_12065(stdout, s);
	popFrame();
}

N_NIMCALL(void, styledechoprocessarg_190824)(NU8 style) {
	NU8 LOC1;
	nimfr("styledEchoProcessArg", "terminal.nim")
	nimln(321, "terminal.nim");
	LOC1 = 0;
	LOC1 |=(1<<((NI8)((style- 1))%(sizeof(NI8)*8)));
	setstyle_189801(LOC1);
	popFrame();
}

N_NIMCALL(void, styledechoprocessarg_190834)(NU8 style) {
	nimfr("styledEchoProcessArg", "terminal.nim")
	nimln(322, "terminal.nim");
	setstyle_189801(style);
	popFrame();
}

N_NIMCALL(void, styledechoprocessarg_190844)(NU8 color) {
	nimfr("styledEchoProcessArg", "terminal.nim")
	nimln(323, "terminal.nim");
	setforegroundcolor_190233(color, NIM_FALSE);
	popFrame();
}

N_NIMCALL(void, styledechoprocessarg_190853)(NU8 color) {
	nimfr("styledEchoProcessArg", "terminal.nim")
	nimln(324, "terminal.nim");
	setbackgroundcolor_190415(color, NIM_FALSE);
	popFrame();
}
N_NOINLINE(void, HEX00_terminalInit)(void) {
	nimfr("terminal", "terminal.nim")
	{
		NI htemp;
		nimln(27, "terminal.nim");
		htemp = Dl_168623(((NI32) -11));
		nimln(28, "terminal.nim");
		{
			NI LOC4;
			NI LOC5;
			NI32 LOC6;
			NI32 LOC9;
			nimln(29, "terminal.nim");
			nimln(28, "terminal.nim");
			nimln(28, "terminal.nim");
			LOC4 = 0;
			LOC4 = Dl_168215();
			nimln(28, "terminal.nim");
			LOC5 = 0;
			LOC5 = Dl_168215();
			LOC6 = 0;
			LOC6 = Dl_168700(LOC4, htemp, LOC5, &conhandle_187001, ((NI32) 0), ((NI32) 1), ((NI32) 2));
			if (!(LOC6 == ((NI32) 0))) goto LA7;
			nimln(30, "terminal.nim");
			nimln(30, "terminal.nim");
			LOC9 = 0;
			LOC9 = oslasterror_110067();
			oserror_110035(LOC9);
		}
		LA7: ;
	}
	nimln(45, "terminal.nim");
	oldattr_187028 = getattributes_187019();
	popFrame();
}

N_NOINLINE(void, HEX00_terminalDatInit)(void) {
}

