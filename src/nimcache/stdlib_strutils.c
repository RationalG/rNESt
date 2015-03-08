/* Generated by Nim Compiler v0.10.2 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, amd64, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nim\lib -o c:\users\simon\rationalnes_\rnes\src\nimcache\stdlib_strutils.o c:\users\simon\rationalnes_\rnes\src\nimcache\stdlib_strutils.c */
#define NIM_INTBITS 64
#include "nimbase.h"

#include <string.h>
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct valueerror3249 valueerror3249;
typedef struct Exception Exception;
typedef struct TNimObject TNimObject;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct tcell44933 tcell44933;
typedef struct tcellseq44949 tcellseq44949;
typedef struct tgcheap47016 tgcheap47016;
typedef struct tcellset44945 tcellset44945;
typedef struct tpagedesc44941 tpagedesc44941;
typedef struct tmemregion27210 tmemregion27210;
typedef struct tsmallchunk26440 tsmallchunk26440;
typedef struct tllchunk27204 tllchunk27204;
typedef struct tbigchunk26442 tbigchunk26442;
typedef struct tintset26417 tintset26417;
typedef struct ttrunk26413 ttrunk26413;
typedef struct tavlnode27208 tavlnode27208;
typedef struct tgcstat47014 tgcstat47014;
typedef struct tbasechunk26438 tbasechunk26438;
typedef struct tfreecell26430 tfreecell26430;
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
struct  Exception  {
  TNimObject Sup;
Exception* parent;
NCSTRING name;
NimStringDesc* message;
NimStringDesc* trace;
};
struct  valueerror3249  {
  Exception Sup;
};
struct  TNimNode  {
NU8 kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
struct  tcell44933  {
NI Refcount;
TNimType* Typ;
};
struct  tcellseq44949  {
NI Len;
NI Cap;
tcell44933** D;
};
struct  tcellset44945  {
NI Counter;
NI Max;
tpagedesc44941* Head;
tpagedesc44941** Data;
};
typedef tsmallchunk26440* TY27222[512];
typedef ttrunk26413* ttrunkbuckets26415[256];
struct  tintset26417  {
ttrunkbuckets26415 Data;
};
struct  tmemregion27210  {
NI Minlargeobj;
NI Maxlargeobj;
TY27222 Freesmallchunks;
tllchunk27204* Llmem;
NI Currmem;
NI Maxmem;
NI Freemem;
NI Lastsize;
tbigchunk26442* Freechunkslist;
tintset26417 Chunkstarts;
tavlnode27208* Root;
tavlnode27208* Deleted;
tavlnode27208* Last;
tavlnode27208* Freeavlnodes;
};
struct  tgcstat47014  {
NI Stackscans;
NI Cyclecollections;
NI Maxthreshold;
NI Maxstacksize;
NI Maxstackcells;
NI Cycletablesize;
NI64 Maxpause;
};
struct  tgcheap47016  {
void* Stackbottom;
NI Cyclethreshold;
tcellseq44949 Zct;
tcellseq44949 Decstack;
tcellset44945 Cycleroots;
tcellseq44949 Tempstack;
NI Recgclock;
tmemregion27210 Region;
tgcstat47014 Stat;
};
typedef NI TY26420[8];
struct  tpagedesc44941  {
tpagedesc44941* Next;
NI Key;
TY26420 Bits;
};
struct  tbasechunk26438  {
NI Prevsize;
NI Size;
NIM_BOOL Used;
};
struct  tsmallchunk26440  {
  tbasechunk26438 Sup;
tsmallchunk26440* Next;
tsmallchunk26440* Prev;
tfreecell26430* Freelist;
NI Free;
NI Acc;
NF Data;
};
struct  tllchunk27204  {
NI Size;
NI Acc;
tllchunk27204* Next;
};
struct  tbigchunk26442  {
  tbasechunk26438 Sup;
tbigchunk26442* Next;
tbigchunk26442* Prev;
NI Align;
NF Data;
};
struct  ttrunk26413  {
ttrunk26413* Next;
NI Key;
TY26420 Bits;
};
typedef tavlnode27208* TY27214[2];
struct  tavlnode27208  {
TY27214 Link;
NI Key;
NI Upperbound;
NI Level;
};
struct  tfreecell26430  {
tfreecell26430* Next;
NI Zerofield;
};
N_NOINLINE(void, raiseOverflow)(void);
N_NIMCALL(NimStringDesc*, nimIntToStr)(NI x);
static N_INLINE(NI, subInt)(NI a, NI b);
static N_INLINE(void, appendChar)(NimStringDesc* dest, NIM_CHAR c);
static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src);
N_NIMCALL(NimStringDesc*, rawNewString)(NI space);
static N_INLINE(NI, addInt)(NI a, NI b);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_18801)(void);
static N_INLINE(void, popFrame)(void);
N_NIMCALL(NimStringDesc*, mnewString)(NI len);
N_NIMCALL(NimStringDesc*, mnewString)(NI len);
N_NOINLINE(void, raiseIndexError)(void);
N_NIMCALL(NIM_CHAR, nsuToLowerChar)(NIM_CHAR c);
static N_INLINE(NI, chckRange)(NI i, NI a, NI b);
N_NOINLINE(void, raiseRangeError)(NI64 val);
N_NIMCALL(NI, npuParseInt)(NimStringDesc* s, NI* number, NI start);
N_NIMCALL(void*, newObj)(TNimType* typ, NI size);
static N_INLINE(void, asgnRefNoCycle)(void** dest, void* src);
static N_INLINE(tcell44933*, usrtocell_48646)(void* usr);
static N_INLINE(void, rtladdzct_50204)(tcell44933* c);
N_NOINLINE(void, addzct_48617)(tcellseq44949* s, tcell44933* c);
N_NIMCALL(void, raiseException)(Exception* e, NCSTRING ename);
static N_INLINE(NI64, addInt64)(NI64 a, NI64 b);
STRING_LITERAL(TMP434, "invalid integer: ", 17);
STRING_LITERAL(TMP731, "0123456789ABCDEF", 16);
extern TFrame* frameptr_16242;
extern TNimType NTI21601; /* ref ValueError */
extern TNimType NTI3249; /* ValueError */
extern tgcheap47016 gch_47044;

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

static N_INLINE(void, appendChar)(NimStringDesc* dest, NIM_CHAR c) {
	(*dest).data[((*dest).Sup.len)- 0] = c;
	(*dest).data[((NI64)((*dest).Sup.len + 1))- 0] = 0;
	(*dest).Sup.len += 1;
}

static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src) {
	memcpy(((NCSTRING) ((&(*dest).data[((*dest).Sup.len)- 0]))), ((NCSTRING) ((*src).data)), (NI64)((*src).Sup.len + 1));
	(*dest).Sup.len += (*src).Sup.len;
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

N_NIMCALL(NimStringDesc*, nsuIntToStr)(NI x, NI minchars) {
	NimStringDesc* result;
	nimfr("intToStr", "strutils.nim")
	result = 0;
	nimln(410, "strutils.nim");
	nimln(410, "strutils.nim");
	nimln(410, "strutils.nim");
	if (x == (IL64(-9223372036854775807) - IL64(1))) raiseOverflow();
	result = nimIntToStr((x > 0? (x) : -(x)));
	{
		NI i_96626;
		NI HEX3Atmp_96629;
		NI TMP185;
		NI res_96632;
		i_96626 = 0;
		HEX3Atmp_96629 = 0;
		nimln(411, "strutils.nim");
		nimln(411, "strutils.nim");
		nimln(411, "strutils.nim");
		TMP185 = subInt(minchars, result->Sup.len);
		HEX3Atmp_96629 = (NI64)(TMP185);
		nimln(1576, "system.nim");
		res_96632 = 1;
		{
			nimln(1577, "system.nim");
			while (1) {
				NimStringDesc* LOC4;
				nimln(1577, "system.nim");
				if (!(res_96632 <= HEX3Atmp_96629)) goto LA3;
				nimln(1576, "system.nim");
				i_96626 = res_96632;
				nimln(412, "strutils.nim");
				nimln(412, "strutils.nim");
				LOC4 = 0;
				LOC4 = rawNewString(result->Sup.len + 1);
appendChar(LOC4, 48);
appendString(LOC4, result);
				result = LOC4;
				nimln(1579, "system.nim");
				res_96632 = addInt(res_96632, 1);
			} LA3: ;
		}
	}
	nimln(413, "strutils.nim");
	{
		NimStringDesc* LOC9;
		nimln(413, "strutils.nim");
		if (!(x < 0)) goto LA7;
		nimln(414, "strutils.nim");
		nimln(414, "strutils.nim");
		LOC9 = 0;
		LOC9 = rawNewString(result->Sup.len + 1);
appendChar(LOC9, 45);
appendString(LOC9, result);
		result = LOC9;
	}
	LA7: ;
	popFrame();
	return result;
}

N_NIMCALL(NimStringDesc*, nsuRepeatChar)(NI count, NIM_CHAR c) {
	NimStringDesc* result;
	nimfr("repeatChar", "strutils.nim")
	result = 0;
	nimln(512, "strutils.nim");
	nimln(512, "strutils.nim");
	result = mnewString(count);
	{
		NI i_96993;
		NI HEX3Atmp_96995;
		NI TMP246;
		NI res_96998;
		i_96993 = 0;
		HEX3Atmp_96995 = 0;
		nimln(513, "strutils.nim");
		nimln(513, "strutils.nim");
		TMP246 = subInt(count, 1);
		HEX3Atmp_96995 = (NI64)(TMP246);
		nimln(1576, "system.nim");
		res_96998 = 0;
		{
			nimln(1577, "system.nim");
			while (1) {
				nimln(1577, "system.nim");
				if (!(res_96998 <= HEX3Atmp_96995)) goto LA3;
				nimln(1576, "system.nim");
				i_96993 = res_96998;
				nimln(513, "strutils.nim");
				if ((NU)(i_96993) > (NU)(result->Sup.len)) raiseIndexError();
				result->data[i_96993] = c;
				nimln(1579, "system.nim");
				res_96998 = addInt(res_96998, 1);
			} LA3: ;
		}
	}
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

N_NIMCALL(NIM_CHAR, nsuToLowerChar)(NIM_CHAR c) {
	NIM_CHAR result;
	nimfr("toLower", "strutils.nim")
	result = 0;
	nimln(69, "strutils.nim");
	{
		NI TMP288;
		nimln(69, "strutils.nim");
		if (!(((NU8)(c)) >= ((NU8)(65)) && ((NU8)(c)) <= ((NU8)(90)))) goto LA3;
		nimln(70, "strutils.nim");
		nimln(70, "strutils.nim");
		nimln(70, "strutils.nim");
		nimln(70, "strutils.nim");
		TMP288 = addInt(((NI) (((NU8)(c)))), 32);
		result = ((NIM_CHAR) (((NI)chckRange((NI64)(TMP288), 0, 255))));
	}
	goto LA1;
	LA3: ;
	{
		nimln(72, "strutils.nim");
		result = c;
	}
	LA1: ;
	popFrame();
	return result;
}

N_NIMCALL(NI, nsuCmpIgnoreStyle)(NimStringDesc* a, NimStringDesc* b) {
	NI result;
	NI i;
	NI j;
	nimfr("cmpIgnoreStyle", "strutils.nim")
	result = 0;
	i = 0;
	j = 0;
	{
		while (1) {
			NIM_CHAR aa;
			NIM_CHAR bb;
			{
				while (1) {
					if (!((NU8)(a->data[i]) == (NU8)(95))) goto LA4;
					i += 1;
				} LA4: ;
			}
			{
				while (1) {
					if (!((NU8)(b->data[j]) == (NU8)(95))) goto LA6;
					j += 1;
				} LA6: ;
			}
			aa = nsuToLowerChar(a->data[i]);
			bb = nsuToLowerChar(b->data[j]);
			result = (NI64)(((NI) (((NU8)(aa)))) - ((NI) (((NU8)(bb)))));
			{
				NIM_BOOL LOC9;
				LOC9 = 0;
				LOC9 = !((result == 0));
				if (LOC9) goto LA10;
				LOC9 = ((NU8)(aa) == (NU8)(0));
				LA10: ;
				if (!LOC9) goto LA11;
				goto LA1;
			}
			LA11: ;
			i += 1;
			j += 1;
		}
	} LA1: ;
	popFrame();
	return result;
}

static N_INLINE(tcell44933*, usrtocell_48646)(void* usr) {
	tcell44933* result;
	nimfr("usrToCell", "gc.nim")
	result = 0;
	nimln(118, "gc.nim");
	nimln(118, "gc.nim");
	nimln(118, "gc.nim");
	result = ((tcell44933*) ((NI)((NU64)(((NI) (usr))) - (NU64)(((NI)sizeof(tcell44933))))));
	popFrame();
	return result;
}

static N_INLINE(void, rtladdzct_50204)(tcell44933* c) {
	nimfr("rtlAddZCT", "gc.nim")
	nimln(199, "gc.nim");
	addzct_48617((&gch_47044.Zct), c);
	popFrame();
}

static N_INLINE(void, asgnRefNoCycle)(void** dest, void* src) {
	nimfr("asgnRefNoCycle", "gc.nim")
	nimln(251, "gc.nim");
	{
		tcell44933* c;
		nimln(251, "gc.nim");
		nimln(251, "gc.nim");
		if (!!((src == NIM_NIL))) goto LA3;
		nimln(252, "gc.nim");
		c = usrtocell_48646(src);
		nimln(169, "gc.nim");
		(*c).Refcount += 8;
	}
	LA3: ;
	nimln(254, "gc.nim");
	{
		tcell44933* c;
		nimln(254, "gc.nim");
		nimln(254, "gc.nim");
		if (!!(((*dest) == NIM_NIL))) goto LA7;
		nimln(255, "gc.nim");
		c = usrtocell_48646((*dest));
		nimln(256, "gc.nim");
		{
			nimln(167, "gc.nim");
			(*c).Refcount -= 8;
			nimln(168, "gc.nim");
			if (!((NU64)((*c).Refcount) < (NU64)(8))) goto LA11;
			nimln(257, "gc.nim");
			rtladdzct_50204(c);
		}
		LA11: ;
	}
	LA7: ;
	nimln(258, "gc.nim");
	(*dest) = src;
	popFrame();
}

N_NIMCALL(NI, nsuParseInt)(NimStringDesc* s) {
	NI result;
	NI l;
	nimfr("parseInt", "strutils.nim")
	result = 0;
	nimln(421, "strutils.nim");
	l = npuParseInt(s, (&result), 0);
	nimln(422, "strutils.nim");
	{
		NIM_BOOL LOC3;
		valueerror3249* e_96657;
		NimStringDesc* LOC7;
		nimln(422, "strutils.nim");
		LOC3 = 0;
		nimln(422, "strutils.nim");
		nimln(422, "strutils.nim");
		nimln(422, "strutils.nim");
		LOC3 = !((l == s->Sup.len));
		if (LOC3) goto LA4;
		nimln(422, "strutils.nim");
		LOC3 = (l == 0);
		LA4: ;
		if (!LOC3) goto LA5;
		e_96657 = 0;
		nimln(2149, "system.nim");
		e_96657 = (valueerror3249*) newObj((&NTI21601), sizeof(valueerror3249));
		(*e_96657).Sup.Sup.m_type = (&NTI3249);
		nimln(2150, "system.nim");
		nimln(423, "strutils.nim");
		LOC7 = 0;
		LOC7 = rawNewString(s->Sup.len + 17);
appendString(LOC7, ((NimStringDesc*) &TMP434));
appendString(LOC7, s);
		asgnRefNoCycle((void**) (&(*e_96657).Sup.message), LOC7);
		nimln(423, "strutils.nim");
		raiseException((Exception*)e_96657, "ValueError");
	}
	LA5: ;
	popFrame();
	return result;
}

static N_INLINE(NI64, addInt64)(NI64 a, NI64 b) {
	NI64 result;
	result = 0;
	result = (NI64)((NU64)(a) + (NU64)(b));
	{
		NIM_BOOL LOC3;
		LOC3 = 0;
		LOC3 = (IL64(0) <= (NI64)(result ^ a));
		if (LOC3) goto LA4;
		LOC3 = (IL64(0) <= (NI64)(result ^ b));
		LA4: ;
		if (!LOC3) goto LA5;
		goto BeforeRet;
	}
	LA5: ;
	raiseOverflow();
	BeforeRet: ;
	return result;
}

N_NIMCALL(NimStringDesc*, nsuToHex)(NI64 x, NI len) {
	NimStringDesc* result;
	NI64 shift;
	nimfr("toHex", "strutils.nim")
	result = 0;
	shift = 0;
	nimln(399, "strutils.nim");
	nimln(399, "strutils.nim");
	result = mnewString(len);
	{
		NI j_96588;
		NI HEX3Atmp_96592;
		NI TMP730;
		NI res_96595;
		j_96588 = 0;
		HEX3Atmp_96592 = 0;
		nimln(400, "strutils.nim");
		nimln(400, "strutils.nim");
		TMP730 = subInt(len, 1);
		HEX3Atmp_96592 = (NI64)(TMP730);
		nimln(1560, "system.nim");
		res_96595 = HEX3Atmp_96592;
		{
			nimln(1561, "system.nim");
			while (1) {
				NI64 TMP732;
				nimln(1561, "system.nim");
				if (!(0 <= res_96595)) goto LA3;
				nimln(1560, "system.nim");
				j_96588 = res_96595;
				nimln(401, "strutils.nim");
				if ((NU)(j_96588) > (NU)(result->Sup.len)) raiseIndexError();
				nimln(401, "strutils.nim");
				nimln(401, "strutils.nim");
				nimln(401, "strutils.nim");
				if ((NU)((NI32)(((NI32)(NU32)(NU64)((NI64)((NU64)(x) >> (NU64)(shift)))) & ((NI32) 15))) > (NU)(((NimStringDesc*) &TMP731)->Sup.len)) raiseIndexError();
				result->data[j_96588] = ((NimStringDesc*) &TMP731)->data[(NI32)(((NI32)(NU32)(NU64)((NI64)((NU64)(x) >> (NU64)(shift)))) & ((NI32) 15))];
				nimln(402, "strutils.nim");
				nimln(402, "strutils.nim");
				TMP732 = addInt64(shift, IL64(4));
				shift = (NI64)(TMP732);
				nimln(1563, "system.nim");
				res_96595 = subInt(res_96595, 1);
			} LA3: ;
		}
	}
	popFrame();
	return result;
}

N_NIMCALL(NI, nsuParseHexInt)(NimStringDesc* s) {
	NI result;
	NI i;
	nimfr("parseHexInt", "strutils.nim")
	result = 0;
	nimln(450, "strutils.nim");
	i = 0;
	nimln(451, "strutils.nim");
	{
		NIM_BOOL LOC3;
		NIM_BOOL LOC5;
		NI TMP738;
		NI TMP739;
		nimln(451, "strutils.nim");
		LOC3 = 0;
		nimln(451, "strutils.nim");
		if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
		LOC3 = ((NU8)(s->data[i]) == (NU8)(48));
		if (!(LOC3)) goto LA4;
		nimln(451, "strutils.nim");
		LOC5 = 0;
		nimln(451, "strutils.nim");
		nimln(451, "strutils.nim");
		TMP738 = addInt(i, 1);
		if ((NU)((NI64)(TMP738)) > (NU)(s->Sup.len)) raiseIndexError();
		LOC5 = ((NU8)(s->data[(NI64)(TMP738)]) == (NU8)(120));
		if (LOC5) goto LA6;
		nimln(451, "strutils.nim");
		nimln(451, "strutils.nim");
		TMP739 = addInt(i, 1);
		if ((NU)((NI64)(TMP739)) > (NU)(s->Sup.len)) raiseIndexError();
		LOC5 = ((NU8)(s->data[(NI64)(TMP739)]) == (NU8)(88));
		LA6: ;
		LOC3 = LOC5;
		LA4: ;
		if (!LOC3) goto LA7;
		nimln(451, "strutils.nim");
		i = addInt(i, 2);
	}
	goto LA1;
	LA7: ;
	{
		nimln(452, "strutils.nim");
		if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
		if (!((NU8)(s->data[i]) == (NU8)(35))) goto LA10;
		nimln(452, "strutils.nim");
		i = addInt(i, 1);
	}
	goto LA1;
	LA10: ;
	LA1: ;
	{
		nimln(453, "strutils.nim");
		while (1) {
			nimln(454, "strutils.nim");
			if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
			switch (((NU8)(s->data[i]))) {
			case 95:
			{
				nimln(455, "strutils.nim");
				i = addInt(i, 1);
			}
			break;
			case 48 ... 57:
			{
				NI TMP740;
				nimln(457, "strutils.nim");
				nimln(457, "strutils.nim");
				nimln(457, "strutils.nim");
				nimln(457, "strutils.nim");
				nimln(457, "strutils.nim");
				if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
				TMP740 = subInt(((NI) (((NU8)(s->data[i])))), 48);
				result = (NI)((NI)((NU64)(result) << (NU64)(4)) | ((NI) ((NI64)(TMP740))));
				nimln(458, "strutils.nim");
				i = addInt(i, 1);
			}
			break;
			case 97 ... 102:
			{
				NI TMP741;
				NI TMP742;
				nimln(460, "strutils.nim");
				nimln(460, "strutils.nim");
				nimln(460, "strutils.nim");
				nimln(460, "strutils.nim");
				nimln(460, "strutils.nim");
				nimln(460, "strutils.nim");
				if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
				TMP741 = subInt(((NI) (((NU8)(s->data[i])))), 97);
				TMP742 = addInt(((NI) ((NI64)(TMP741))), 10);
				result = (NI)((NI)((NU64)(result) << (NU64)(4)) | ((NI) ((NI64)(TMP742))));
				nimln(461, "strutils.nim");
				i = addInt(i, 1);
			}
			break;
			case 65 ... 70:
			{
				NI TMP743;
				NI TMP744;
				nimln(463, "strutils.nim");
				nimln(463, "strutils.nim");
				nimln(463, "strutils.nim");
				nimln(463, "strutils.nim");
				nimln(463, "strutils.nim");
				nimln(463, "strutils.nim");
				if ((NU)(i) > (NU)(s->Sup.len)) raiseIndexError();
				TMP743 = subInt(((NI) (((NU8)(s->data[i])))), 65);
				TMP744 = addInt(((NI) ((NI64)(TMP743))), 10);
				result = (NI)((NI)((NU64)(result) << (NU64)(4)) | ((NI) ((NI64)(TMP744))));
				nimln(464, "strutils.nim");
				i = addInt(i, 1);
			}
			break;
			case 0:
			{
				nimln(465, "strutils.nim");
				goto LA12;
			}
			break;
			default:
			{
				valueerror3249* e_96882;
				NimStringDesc* LOC20;
				e_96882 = 0;
				nimln(2149, "system.nim");
				e_96882 = (valueerror3249*) newObj((&NTI21601), sizeof(valueerror3249));
				(*e_96882).Sup.Sup.m_type = (&NTI3249);
				nimln(2150, "system.nim");
				nimln(466, "strutils.nim");
				LOC20 = 0;
				LOC20 = rawNewString(s->Sup.len + 17);
appendString(LOC20, ((NimStringDesc*) &TMP434));
appendString(LOC20, s);
				asgnRefNoCycle((void**) (&(*e_96882).Sup.message), LOC20);
				nimln(466, "strutils.nim");
				raiseException((Exception*)e_96882, "ValueError");
			}
			break;
			}
		}
	} LA12: ;
	popFrame();
	return result;
}
NIM_EXTERNC N_NOINLINE(void, stdlib_strutilsInit)(void) {
	nimfr("strutils", "strutils.nim")
	popFrame();
}

NIM_EXTERNC N_NOINLINE(void, stdlib_strutilsDatInit)(void) {
}

