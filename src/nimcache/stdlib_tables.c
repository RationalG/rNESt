/* Generated by Nim Compiler v0.10.2 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, amd64, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nim\lib -o c:\users\simon\rationalnes_\rnes\src\nimcache\stdlib_tables.o c:\users\simon\rationalnes_\rnes\src\nimcache\stdlib_tables.c */
#define NIM_INTBITS 64
#include "nimbase.h"

#include <string.h>
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct TY225211 TY225211;
typedef struct table225214 table225214;
typedef struct keyvaluepairseq225217 keyvaluepairseq225217;
typedef struct keyvaluepair225220 keyvaluepair225220;
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
typedef struct TY225803 TY225803;
typedef struct table225806 table225806;
typedef struct keyvaluepairseq225809 keyvaluepairseq225809;
typedef struct keyvaluepair225812 keyvaluepair225812;
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
typedef N_NIMCALL_PTR(void, TY224155) (NI vbyte);
struct TY225211 {
NimStringDesc* Field0;
TY224155 Field1;
};
struct keyvaluepair225220 {
NU8 Field0;
NimStringDesc* Field1;
TY224155 Field2;
};
struct  table225214  {
keyvaluepairseq225217* Data;
NI Counter;
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
typedef N_NIMCALL_PTR(NI, TY224853) (void);
struct TY225803 {
NimStringDesc* Field0;
TY224853 Field1;
};
struct keyvaluepair225812 {
NU8 Field0;
NimStringDesc* Field1;
TY224853 Field2;
};
struct  table225806  {
keyvaluepairseq225809* Data;
NI Counter;
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
struct keyvaluepairseq225217 {
  TGenericSeq Sup;
  keyvaluepair225220 data[SEQ_DECL_SIZE];
};
struct keyvaluepairseq225809 {
  TGenericSeq Sup;
  keyvaluepair225812 data[SEQ_DECL_SIZE];
};
static N_INLINE(NIM_BOOL, mustrehash_144302)(NI length, NI counter);
N_NIMCALL(void, failedassertimpl_86825)(NimStringDesc* msg);
N_NIMCALL(NI, mulInt)(NI a, NI b);
static N_INLINE(NI, subInt)(NI a, NI b);
N_NOINLINE(void, raiseOverflow)(void);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_18801)(void);
static N_INLINE(void, popFrame)(void);
static N_INLINE(NI, nexttry_144410)(NI h, NI maxhash);
static N_INLINE(NI, addInt)(NI a, NI b);
N_NIMCALL(void, inittable_225234)(NI initialsize_225239, table225214* Result);
N_NIMCALL(NIM_BOOL, ispoweroftwo_138518)(NI x);
N_NIMCALL(void, nimGCvisit)(void* d, NI op);
N_NIMCALL(void, TMP496)(void* p, NI op);
N_NIMCALL(void*, newSeq)(TNimType* typ, NI len);
N_NIMCALL(void, unsureAsgnRef)(void** dest, void* src);
N_NIMCALL(NI, nextpoweroftwo_138528)(NI x);
N_NOINLINE(void, chckNil)(void* p);
N_NIMCALL(void, genericReset)(void* dest, TNimType* mt);
N_NOINLINE(void, raiseIndexError)(void);
N_NIMCALL(void, HEX5BHEX5DHEX3D_225475)(table225214* t_225484, NimStringDesc* key_225488, TY224155 val_225490);
N_NIMCALL(NI, rawget_225493)(table225214 t_225500, NimStringDesc* key_225503);
N_NIMCALL(NI, hash_142842)(NimStringDesc* x);
static N_INLINE(NIM_BOOL, eqStrings)(NimStringDesc* a, NimStringDesc* b);
N_NIMCALL(void, enlarge_225550)(table225214* t_225559);
N_NIMCALL(void, rawinsert_225620)(table225214* t_225629, keyvaluepairseq225217** data_225637, NimStringDesc* key_225641, TY224155 val_225643);
N_NIMCALL(NimStringDesc*, copyStringRC1)(NimStringDesc* src);
static N_INLINE(void, nimGCunrefNoCycle)(void* p);
static N_INLINE(tcell44933*, usrtocell_48646)(void* usr);
static N_INLINE(void, rtladdzct_50204)(tcell44933* c);
N_NOINLINE(void, addzct_48617)(tcellseq44949* s, tcell44933* c);
N_NIMCALL(void, inittable_225826)(NI initialsize_225831, table225806* Result);
N_NIMCALL(void, TMP501)(void* p, NI op);
N_NIMCALL(void, HEX5BHEX5DHEX3D_226075)(table225806* t_226084, NimStringDesc* key_226088, TY224853 val_226090);
N_NIMCALL(NI, rawget_226093)(table225806 t_226100, NimStringDesc* key_226103);
N_NIMCALL(void, enlarge_226150)(table225806* t_226159);
N_NIMCALL(void, rawinsert_226220)(table225806* t_226229, keyvaluepairseq225809** data_226237, NimStringDesc* key_226241, TY224853 val_226243);
STRING_LITERAL(TMP322, "length > counter ", 17);
STRING_LITERAL(TMP491, "isPowerOfTwo(initialSize) ", 26);
extern TFrame* frameptr_16242;
TNimType NTI225220; /* KeyValuePair */
TNimType NTI144009; /* SlotEnum */
extern TNimType NTI149; /* string */
extern TNimType NTI224155; /* proc (int){.locks: 0.} */
TNimType NTI225217; /* KeyValuePairSeq */
TNimType NTI225214; /* Table */
extern TNimType NTI108; /* int */
extern tgcheap47016 gch_47044;
TNimType NTI225812; /* KeyValuePair */
extern TNimType NTI224853; /* proc (): int{.locks: 0.} */
TNimType NTI225809; /* KeyValuePairSeq */
TNimType NTI225806; /* Table */

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

static N_INLINE(NIM_BOOL, mustrehash_144302)(NI length, NI counter) {
	NIM_BOOL result;
	NIM_BOOL LOC5;
	NI TMP323;
	NI TMP324;
	NI TMP325;
	nimfr("mustRehash", "tables.nim")
	result = 0;
	nimln(120, "tables.nim");
	{
		nimln(120, "tables.nim");
		nimln(120, "tables.nim");
		if (!!((counter < length))) goto LA3;
		nimln(120, "tables.nim");
		failedassertimpl_86825(((NimStringDesc*) &TMP322));
	}
	LA3: ;
	nimln(121, "tables.nim");
	nimln(121, "tables.nim");
	LOC5 = 0;
	nimln(121, "tables.nim");
	nimln(121, "tables.nim");
	TMP323 = mulInt(length, 2);
	nimln(121, "tables.nim");
	TMP324 = mulInt(counter, 3);
	LOC5 = ((NI64)(TMP323) < (NI64)(TMP324));
	if (LOC5) goto LA6;
	nimln(121, "tables.nim");
	nimln(121, "tables.nim");
	TMP325 = subInt(length, counter);
	LOC5 = ((NI64)(TMP325) < 4);
	LA6: ;
	result = LOC5;
	popFrame();
	return result;
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

static N_INLINE(NI, nexttry_144410)(NI h, NI maxhash) {
	NI result;
	NI TMP326;
	NI TMP327;
	nimfr("nextTry", "tables.nim")
	result = 0;
	nimln(124, "tables.nim");
	nimln(124, "tables.nim");
	nimln(124, "tables.nim");
	nimln(124, "tables.nim");
	TMP326 = mulInt(5, h);
	TMP327 = addInt((NI64)(TMP326), 1);
	result = (NI)((NI64)(TMP327) & maxhash);
	popFrame();
	return result;
}
N_NIMCALL(void, TMP496)(void* p, NI op) {
	keyvaluepairseq225217* a;
	NI LOC1;
	a = (keyvaluepairseq225217*)p;
	LOC1 = 0;
	for (LOC1 = 0; LOC1 < a->Sup.len; LOC1++) {
	nimGCvisit((void*)a->data[LOC1].Field1, op);
	}
}

N_NIMCALL(void, inittable_225234)(NI initialsize_225239, table225214* Result) {
	nimfr("initTable", "tables.nim")
	nimln(229, "tables.nim");
	{
		NIM_BOOL LOC3;
		nimln(229, "tables.nim");
		nimln(229, "tables.nim");
		LOC3 = 0;
		LOC3 = ispoweroftwo_138518(initialsize_225239);
		if (!!(LOC3)) goto LA4;
		nimln(229, "tables.nim");
		failedassertimpl_86825(((NimStringDesc*) &TMP491));
	}
	LA4: ;
	nimln(230, "tables.nim");
	(*Result).Counter = 0;
	nimln(231, "tables.nim");
	unsureAsgnRef((void**) (&(*Result).Data), (keyvaluepairseq225217*) newSeq((&NTI225217), initialsize_225239));
	popFrame();
}

static N_INLINE(NIM_BOOL, eqStrings)(NimStringDesc* a, NimStringDesc* b) {
	NIM_BOOL result;
	NIM_BOOL LOC11;
	int LOC13;
	result = 0;
	{
		if (!(a == b)) goto LA3;
		result = NIM_TRUE;
		goto BeforeRet;
	}
	LA3: ;
	{
		NIM_BOOL LOC7;
		LOC7 = 0;
		LOC7 = (a == NIM_NIL);
		if (LOC7) goto LA8;
		LOC7 = (b == NIM_NIL);
		LA8: ;
		if (!LOC7) goto LA9;
		result = NIM_FALSE;
		goto BeforeRet;
	}
	LA9: ;
	LOC11 = 0;
	LOC11 = ((*a).Sup.len == (*b).Sup.len);
	if (!(LOC11)) goto LA12;
	LOC13 = 0;
	LOC13 = memcmp(((NCSTRING) ((*a).data)), ((NCSTRING) ((*b).data)), (NI64)((*a).Sup.len * 1));
	LOC11 = (LOC13 == ((NI32) 0));
	LA12: ;
	result = LOC11;
	goto BeforeRet;
	BeforeRet: ;
	return result;
}

N_NIMCALL(NI, rawget_225493)(table225214 t_225500, NimStringDesc* key_225503) {
	NI result;
	NI h;
	NI LOC1;
	nimfr("rawGet", "tables.nim")
	result = 0;
	nimln(127, "tables.nim");
	nimln(127, "tables.nim");
	nimln(127, "tables.nim");
	LOC1 = 0;
	LOC1 = hash_142842(key_225503);
	nimln(127, "tables.nim");
	h = (NI)(LOC1 & (t_225500.Data->Sup.len-1));
	{
		nimln(128, "tables.nim");
		while (1) {
			nimln(128, "tables.nim");
			nimln(128, "tables.nim");
			if ((NU)(h) >= (NU)(t_225500.Data->Sup.len)) raiseIndexError();
			if (!!((t_225500.Data->data[h].Field0 == ((NU8) 0)))) goto LA3;
			nimln(129, "tables.nim");
			{
				NIM_BOOL LOC6;
				nimln(129, "tables.nim");
				LOC6 = 0;
				nimln(129, "tables.nim");
				if ((NU)(h) >= (NU)(t_225500.Data->Sup.len)) raiseIndexError();
				LOC6 = eqStrings(t_225500.Data->data[h].Field1, key_225503);
				if (!(LOC6)) goto LA7;
				nimln(129, "tables.nim");
				if ((NU)(h) >= (NU)(t_225500.Data->Sup.len)) raiseIndexError();
				LOC6 = (t_225500.Data->data[h].Field0 == ((NU8) 1));
				LA7: ;
				if (!LOC6) goto LA8;
				nimln(130, "tables.nim");
				nimln(130, "tables.nim");
				result = h;
				goto BeforeRet;
			}
			LA8: ;
			nimln(131, "tables.nim");
			nimln(131, "tables.nim");
			h = nexttry_144410(h, (t_225500.Data->Sup.len-1));
		} LA3: ;
	}
	nimln(132, "tables.nim");
	result = -1;
	BeforeRet: ;
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

static N_INLINE(void, nimGCunrefNoCycle)(void* p) {
	tcell44933* c;
	nimfr("nimGCunrefNoCycle", "gc.nim")
	nimln(233, "gc.nim");
	c = usrtocell_48646(p);
	nimln(235, "gc.nim");
	{
		nimln(167, "gc.nim");
		(*c).Refcount -= 8;
		nimln(168, "gc.nim");
		if (!((NU64)((*c).Refcount) < (NU64)(8))) goto LA3;
		nimln(236, "gc.nim");
		rtladdzct_50204(c);
	}
	LA3: ;
	popFrame();
}

N_NIMCALL(void, rawinsert_225620)(table225214* t_225629, keyvaluepairseq225217** data_225637, NimStringDesc* key_225641, TY224155 val_225643) {
	NI h;
	NI LOC1;
	NimStringDesc* LOC4;
	nimfr("rawInsert", "tables.nim")
	nimln(135, "tables.nim");
	nimln(135, "tables.nim");
	nimln(135, "tables.nim");
	LOC1 = 0;
	LOC1 = hash_142842(key_225641);
	nimln(135, "tables.nim");
	h = (NI)(LOC1 & ((*data_225637)->Sup.len-1));
	{
		nimln(136, "tables.nim");
		while (1) {
			nimln(136, "tables.nim");
			if ((NU)(h) >= (NU)((*data_225637)->Sup.len)) raiseIndexError();
			if (!((*data_225637)->data[h].Field0 == ((NU8) 1))) goto LA3;
			nimln(137, "tables.nim");
			nimln(137, "tables.nim");
			h = nexttry_144410(h, ((*data_225637)->Sup.len-1));
		} LA3: ;
	}
	nimln(138, "tables.nim");
	if ((NU)(h) >= (NU)((*data_225637)->Sup.len)) raiseIndexError();
	LOC4 = 0;
	LOC4 = (*data_225637)->data[h].Field1; (*data_225637)->data[h].Field1 = copyStringRC1(key_225641);
	if (LOC4) nimGCunrefNoCycle(LOC4);
	nimln(139, "tables.nim");
	if ((NU)(h) >= (NU)((*data_225637)->Sup.len)) raiseIndexError();
	(*data_225637)->data[h].Field2 = val_225643;
	nimln(140, "tables.nim");
	if ((NU)(h) >= (NU)((*data_225637)->Sup.len)) raiseIndexError();
	(*data_225637)->data[h].Field0 = ((NU8) 1);
	popFrame();
}

N_NIMCALL(void, enlarge_225550)(table225214* t_225559) {
	keyvaluepairseq225217* n;
	NI TMP499;
	keyvaluepairseq225217* LOC8;
	nimfr("enlarge", "tables.nim")
	n = 0;
	nimln(178, "tables.nim");
	nimln(178, "tables.nim");
	nimln(178, "tables.nim");
	TMP499 = mulInt((*t_225559).Data->Sup.len, 2);
	n = (keyvaluepairseq225217*) newSeq((&NTI225217), (NI64)(TMP499));
	{
		NI i_225605;
		NI HEX3Atmp_225684;
		NI res_225687;
		i_225605 = 0;
		HEX3Atmp_225684 = 0;
		nimln(179, "tables.nim");
		nimln(179, "tables.nim");
		HEX3Atmp_225684 = ((*t_225559).Data->Sup.len-1);
		nimln(1569, "system.nim");
		res_225687 = 0;
		{
			nimln(1570, "system.nim");
			while (1) {
				nimln(1570, "system.nim");
				if (!(res_225687 <= HEX3Atmp_225684)) goto LA3;
				nimln(1569, "system.nim");
				i_225605 = res_225687;
				nimln(180, "tables.nim");
				{
					nimln(180, "tables.nim");
					if ((NU)(i_225605) >= (NU)((*t_225559).Data->Sup.len)) raiseIndexError();
					if (!((*t_225559).Data->data[i_225605].Field0 == ((NU8) 1))) goto LA6;
					nimln(180, "tables.nim");
					if ((NU)(i_225605) >= (NU)((*t_225559).Data->Sup.len)) raiseIndexError();
					if ((NU)(i_225605) >= (NU)((*t_225559).Data->Sup.len)) raiseIndexError();
					rawinsert_225620(t_225559, (&n), (*t_225559).Data->data[i_225605].Field1, (*t_225559).Data->data[i_225605].Field2);
				}
				LA6: ;
				nimln(1572, "system.nim");
				res_225687 = addInt(res_225687, 1);
			} LA3: ;
		}
	}
	nimln(181, "tables.nim");
	LOC8 = 0;
	LOC8 = (*t_225559).Data;
	unsureAsgnRef((void**) (&(*t_225559).Data), n);
	n = LOC8;
	popFrame();
}

N_NIMCALL(void, HEX5BHEX5DHEX3D_225475)(table225214* t_225484, NimStringDesc* key_225488, TY224155 val_225490) {
	NI index;
	nimfr("[]=", "tables.nim")
	nimln(189, "tables.nim");
	index = rawget_225493((*t_225484), key_225488);
	nimln(190, "tables.nim");
	{
		nimln(190, "tables.nim");
		if (!(0 <= index)) goto LA3;
		nimln(191, "tables.nim");
		if ((NU)(index) >= (NU)((*t_225484).Data->Sup.len)) raiseIndexError();
		(*t_225484).Data->data[index].Field2 = val_225490;
	}
	goto LA1;
	LA3: ;
	{
		nimln(184, "tables.nim");
		{
			NIM_BOOL LOC8;
			nimln(184, "tables.nim");
			nimln(184, "tables.nim");
			LOC8 = 0;
			LOC8 = mustrehash_144302((*t_225484).Data->Sup.len, (*t_225484).Counter);
			if (!LOC8) goto LA9;
			nimln(184, "tables.nim");
			enlarge_225550(t_225484);
		}
		LA9: ;
		nimln(185, "tables.nim");
		rawinsert_225620(t_225484, (&(*t_225484).Data), key_225488, val_225490);
		nimln(186, "tables.nim");
		(*t_225484).Counter = addInt((*t_225484).Counter, 1);
	}
	LA1: ;
	popFrame();
}

N_NIMCALL(void, totable_225196)(TY225211* pairs_225209, NI pairs_225209Len0, table225214* Result) {
	NI TMP497;
	NI LOC1;
	nimfr("toTable", "tables.nim")
	nimln(236, "tables.nim");
	nimln(236, "tables.nim");
	nimln(236, "tables.nim");
	nimln(236, "tables.nim");
	TMP497 = addInt(pairs_225209Len0, 10);
	LOC1 = 0;
	LOC1 = nextpoweroftwo_138528((NI64)(TMP497));
	chckNil((void*)Result);
	genericReset((void*)Result, (&NTI225214));
	inittable_225234(LOC1, Result);
	{
		NimStringDesc* key_225470;
		TY224155 val_225471;
		NI i_225750;
		key_225470 = 0;
		val_225471 = 0;
		nimln(1649, "system.nim");
		i_225750 = 0;
		{
			nimln(1650, "system.nim");
			while (1) {
				nimln(1650, "system.nim");
				nimln(1650, "system.nim");
				if (!(i_225750 < pairs_225209Len0)) goto LA4;
				nimln(1651, "system.nim");
				if ((NU)(i_225750) >= (NU)(pairs_225209Len0)) raiseIndexError();
				key_225470 = pairs_225209[i_225750].Field0;
				nimln(1651, "system.nim");
				if ((NU)(i_225750) >= (NU)(pairs_225209Len0)) raiseIndexError();
				val_225471 = pairs_225209[i_225750].Field1;
				nimln(237, "tables.nim");
				HEX5BHEX5DHEX3D_225475(Result, key_225470, val_225471);
				nimln(1652, "system.nim");
				i_225750 = addInt(i_225750, 1);
			} LA4: ;
		}
	}
	popFrame();
}
N_NIMCALL(void, TMP501)(void* p, NI op) {
	keyvaluepairseq225809* a;
	NI LOC1;
	a = (keyvaluepairseq225809*)p;
	LOC1 = 0;
	for (LOC1 = 0; LOC1 < a->Sup.len; LOC1++) {
	nimGCvisit((void*)a->data[LOC1].Field1, op);
	}
}

N_NIMCALL(void, inittable_225826)(NI initialsize_225831, table225806* Result) {
	nimfr("initTable", "tables.nim")
	nimln(229, "tables.nim");
	{
		NIM_BOOL LOC3;
		nimln(229, "tables.nim");
		nimln(229, "tables.nim");
		LOC3 = 0;
		LOC3 = ispoweroftwo_138518(initialsize_225831);
		if (!!(LOC3)) goto LA4;
		nimln(229, "tables.nim");
		failedassertimpl_86825(((NimStringDesc*) &TMP491));
	}
	LA4: ;
	nimln(230, "tables.nim");
	(*Result).Counter = 0;
	nimln(231, "tables.nim");
	unsureAsgnRef((void**) (&(*Result).Data), (keyvaluepairseq225809*) newSeq((&NTI225809), initialsize_225831));
	popFrame();
}

N_NIMCALL(NI, rawget_226093)(table225806 t_226100, NimStringDesc* key_226103) {
	NI result;
	NI h;
	NI LOC1;
	nimfr("rawGet", "tables.nim")
	result = 0;
	nimln(127, "tables.nim");
	nimln(127, "tables.nim");
	nimln(127, "tables.nim");
	LOC1 = 0;
	LOC1 = hash_142842(key_226103);
	nimln(127, "tables.nim");
	h = (NI)(LOC1 & (t_226100.Data->Sup.len-1));
	{
		nimln(128, "tables.nim");
		while (1) {
			nimln(128, "tables.nim");
			nimln(128, "tables.nim");
			if ((NU)(h) >= (NU)(t_226100.Data->Sup.len)) raiseIndexError();
			if (!!((t_226100.Data->data[h].Field0 == ((NU8) 0)))) goto LA3;
			nimln(129, "tables.nim");
			{
				NIM_BOOL LOC6;
				nimln(129, "tables.nim");
				LOC6 = 0;
				nimln(129, "tables.nim");
				if ((NU)(h) >= (NU)(t_226100.Data->Sup.len)) raiseIndexError();
				LOC6 = eqStrings(t_226100.Data->data[h].Field1, key_226103);
				if (!(LOC6)) goto LA7;
				nimln(129, "tables.nim");
				if ((NU)(h) >= (NU)(t_226100.Data->Sup.len)) raiseIndexError();
				LOC6 = (t_226100.Data->data[h].Field0 == ((NU8) 1));
				LA7: ;
				if (!LOC6) goto LA8;
				nimln(130, "tables.nim");
				nimln(130, "tables.nim");
				result = h;
				goto BeforeRet;
			}
			LA8: ;
			nimln(131, "tables.nim");
			nimln(131, "tables.nim");
			h = nexttry_144410(h, (t_226100.Data->Sup.len-1));
		} LA3: ;
	}
	nimln(132, "tables.nim");
	result = -1;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(void, rawinsert_226220)(table225806* t_226229, keyvaluepairseq225809** data_226237, NimStringDesc* key_226241, TY224853 val_226243) {
	NI h;
	NI LOC1;
	NimStringDesc* LOC4;
	nimfr("rawInsert", "tables.nim")
	nimln(135, "tables.nim");
	nimln(135, "tables.nim");
	nimln(135, "tables.nim");
	LOC1 = 0;
	LOC1 = hash_142842(key_226241);
	nimln(135, "tables.nim");
	h = (NI)(LOC1 & ((*data_226237)->Sup.len-1));
	{
		nimln(136, "tables.nim");
		while (1) {
			nimln(136, "tables.nim");
			if ((NU)(h) >= (NU)((*data_226237)->Sup.len)) raiseIndexError();
			if (!((*data_226237)->data[h].Field0 == ((NU8) 1))) goto LA3;
			nimln(137, "tables.nim");
			nimln(137, "tables.nim");
			h = nexttry_144410(h, ((*data_226237)->Sup.len-1));
		} LA3: ;
	}
	nimln(138, "tables.nim");
	if ((NU)(h) >= (NU)((*data_226237)->Sup.len)) raiseIndexError();
	LOC4 = 0;
	LOC4 = (*data_226237)->data[h].Field1; (*data_226237)->data[h].Field1 = copyStringRC1(key_226241);
	if (LOC4) nimGCunrefNoCycle(LOC4);
	nimln(139, "tables.nim");
	if ((NU)(h) >= (NU)((*data_226237)->Sup.len)) raiseIndexError();
	(*data_226237)->data[h].Field2 = val_226243;
	nimln(140, "tables.nim");
	if ((NU)(h) >= (NU)((*data_226237)->Sup.len)) raiseIndexError();
	(*data_226237)->data[h].Field0 = ((NU8) 1);
	popFrame();
}

N_NIMCALL(void, enlarge_226150)(table225806* t_226159) {
	keyvaluepairseq225809* n;
	NI TMP504;
	keyvaluepairseq225809* LOC8;
	nimfr("enlarge", "tables.nim")
	n = 0;
	nimln(178, "tables.nim");
	nimln(178, "tables.nim");
	nimln(178, "tables.nim");
	TMP504 = mulInt((*t_226159).Data->Sup.len, 2);
	n = (keyvaluepairseq225809*) newSeq((&NTI225809), (NI64)(TMP504));
	{
		NI i_226205;
		NI HEX3Atmp_226284;
		NI res_226287;
		i_226205 = 0;
		HEX3Atmp_226284 = 0;
		nimln(179, "tables.nim");
		nimln(179, "tables.nim");
		HEX3Atmp_226284 = ((*t_226159).Data->Sup.len-1);
		nimln(1569, "system.nim");
		res_226287 = 0;
		{
			nimln(1570, "system.nim");
			while (1) {
				nimln(1570, "system.nim");
				if (!(res_226287 <= HEX3Atmp_226284)) goto LA3;
				nimln(1569, "system.nim");
				i_226205 = res_226287;
				nimln(180, "tables.nim");
				{
					nimln(180, "tables.nim");
					if ((NU)(i_226205) >= (NU)((*t_226159).Data->Sup.len)) raiseIndexError();
					if (!((*t_226159).Data->data[i_226205].Field0 == ((NU8) 1))) goto LA6;
					nimln(180, "tables.nim");
					if ((NU)(i_226205) >= (NU)((*t_226159).Data->Sup.len)) raiseIndexError();
					if ((NU)(i_226205) >= (NU)((*t_226159).Data->Sup.len)) raiseIndexError();
					rawinsert_226220(t_226159, (&n), (*t_226159).Data->data[i_226205].Field1, (*t_226159).Data->data[i_226205].Field2);
				}
				LA6: ;
				nimln(1572, "system.nim");
				res_226287 = addInt(res_226287, 1);
			} LA3: ;
		}
	}
	nimln(181, "tables.nim");
	LOC8 = 0;
	LOC8 = (*t_226159).Data;
	unsureAsgnRef((void**) (&(*t_226159).Data), n);
	n = LOC8;
	popFrame();
}

N_NIMCALL(void, HEX5BHEX5DHEX3D_226075)(table225806* t_226084, NimStringDesc* key_226088, TY224853 val_226090) {
	NI index;
	nimfr("[]=", "tables.nim")
	nimln(189, "tables.nim");
	index = rawget_226093((*t_226084), key_226088);
	nimln(190, "tables.nim");
	{
		nimln(190, "tables.nim");
		if (!(0 <= index)) goto LA3;
		nimln(191, "tables.nim");
		if ((NU)(index) >= (NU)((*t_226084).Data->Sup.len)) raiseIndexError();
		(*t_226084).Data->data[index].Field2 = val_226090;
	}
	goto LA1;
	LA3: ;
	{
		nimln(184, "tables.nim");
		{
			NIM_BOOL LOC8;
			nimln(184, "tables.nim");
			nimln(184, "tables.nim");
			LOC8 = 0;
			LOC8 = mustrehash_144302((*t_226084).Data->Sup.len, (*t_226084).Counter);
			if (!LOC8) goto LA9;
			nimln(184, "tables.nim");
			enlarge_226150(t_226084);
		}
		LA9: ;
		nimln(185, "tables.nim");
		rawinsert_226220(t_226084, (&(*t_226084).Data), key_226088, val_226090);
		nimln(186, "tables.nim");
		(*t_226084).Counter = addInt((*t_226084).Counter, 1);
	}
	LA1: ;
	popFrame();
}

N_NIMCALL(void, totable_225788)(TY225803* pairs_225801, NI pairs_225801Len0, table225806* Result) {
	NI TMP502;
	NI LOC1;
	nimfr("toTable", "tables.nim")
	nimln(236, "tables.nim");
	nimln(236, "tables.nim");
	nimln(236, "tables.nim");
	nimln(236, "tables.nim");
	TMP502 = addInt(pairs_225801Len0, 10);
	LOC1 = 0;
	LOC1 = nextpoweroftwo_138528((NI64)(TMP502));
	chckNil((void*)Result);
	genericReset((void*)Result, (&NTI225806));
	inittable_225826(LOC1, Result);
	{
		NimStringDesc* key_226070;
		TY224853 val_226071;
		NI i_226350;
		key_226070 = 0;
		val_226071 = 0;
		nimln(1649, "system.nim");
		i_226350 = 0;
		{
			nimln(1650, "system.nim");
			while (1) {
				nimln(1650, "system.nim");
				nimln(1650, "system.nim");
				if (!(i_226350 < pairs_225801Len0)) goto LA4;
				nimln(1651, "system.nim");
				if ((NU)(i_226350) >= (NU)(pairs_225801Len0)) raiseIndexError();
				key_226070 = pairs_225801[i_226350].Field0;
				nimln(1651, "system.nim");
				if ((NU)(i_226350) >= (NU)(pairs_225801Len0)) raiseIndexError();
				val_226071 = pairs_225801[i_226350].Field1;
				nimln(237, "tables.nim");
				HEX5BHEX5DHEX3D_226075(Result, key_226070, val_226071);
				nimln(1652, "system.nim");
				i_226350 = addInt(i_226350, 1);
			} LA4: ;
		}
	}
	popFrame();
}

N_NIMCALL(TY224853, HEX5BHEX5D_226659)(table225806 t_226666, NimStringDesc* key_226669) {
	TY224853 result;
	NI index;
	nimfr("[]", "tables.nim")
	result = 0;
	nimln(150, "tables.nim");
	index = rawget_226093(t_226666, key_226669);
	nimln(151, "tables.nim");
	{
		nimln(151, "tables.nim");
		if (!(0 <= index)) goto LA3;
		nimln(151, "tables.nim");
		if ((NU)(index) >= (NU)(t_226666.Data->Sup.len)) raiseIndexError();
		result = t_226666.Data->data[index].Field2;
	}
	LA3: ;
	popFrame();
	return result;
}

N_NIMCALL(TY224155, HEX5BHEX5D_226692)(table225214 t_226699, NimStringDesc* key_226702) {
	TY224155 result;
	NI index;
	nimfr("[]", "tables.nim")
	result = 0;
	nimln(150, "tables.nim");
	index = rawget_225493(t_226699, key_226702);
	nimln(151, "tables.nim");
	{
		nimln(151, "tables.nim");
		if (!(0 <= index)) goto LA3;
		nimln(151, "tables.nim");
		if ((NU)(index) >= (NU)(t_226699.Data->Sup.len)) raiseIndexError();
		result = t_226699.Data->data[index].Field2;
	}
	LA3: ;
	popFrame();
	return result;
}
NIM_EXTERNC N_NOINLINE(void, stdlib_tablesInit)(void) {
	nimfr("tables", "tables.nim")
	popFrame();
}

NIM_EXTERNC N_NOINLINE(void, stdlib_tablesDatInit)(void) {
static TNimNode* TMP492[3];
static TNimNode* TMP493[3];
NI TMP495;
static char* NIM_CONST TMP494[3] = {
"seEmpty", 
"seFilled", 
"seDeleted"};
static TNimNode* TMP498[2];
static TNimNode* TMP500[3];
static TNimNode* TMP503[2];
static TNimNode TMP313[18];
NTI225220.size = sizeof(keyvaluepair225220);
NTI225220.kind = 18;
NTI225220.base = 0;
NTI225220.flags = 2;
TMP492[0] = &TMP313[1];
NTI144009.size = sizeof(NU8);
NTI144009.kind = 14;
NTI144009.base = 0;
NTI144009.flags = 3;
for (TMP495 = 0; TMP495 < 3; TMP495++) {
TMP313[TMP495+2].kind = 1;
TMP313[TMP495+2].offset = TMP495;
TMP313[TMP495+2].name = TMP494[TMP495];
TMP493[TMP495] = &TMP313[TMP495+2];
}
TMP313[5].len = 3; TMP313[5].kind = 2; TMP313[5].sons = &TMP493[0];
NTI144009.node = &TMP313[5];
TMP313[1].kind = 1;
TMP313[1].offset = offsetof(keyvaluepair225220, Field0);
TMP313[1].typ = (&NTI144009);
TMP313[1].name = "Field0";
TMP492[1] = &TMP313[6];
TMP313[6].kind = 1;
TMP313[6].offset = offsetof(keyvaluepair225220, Field1);
TMP313[6].typ = (&NTI149);
TMP313[6].name = "Field1";
TMP492[2] = &TMP313[7];
TMP313[7].kind = 1;
TMP313[7].offset = offsetof(keyvaluepair225220, Field2);
TMP313[7].typ = (&NTI224155);
TMP313[7].name = "Field2";
TMP313[0].len = 3; TMP313[0].kind = 2; TMP313[0].sons = &TMP492[0];
NTI225220.node = &TMP313[0];
NTI225217.size = sizeof(keyvaluepairseq225217*);
NTI225217.kind = 24;
NTI225217.base = (&NTI225220);
NTI225217.flags = 2;
NTI225217.marker = TMP496;
NTI225214.size = sizeof(table225214);
NTI225214.kind = 18;
NTI225214.base = 0;
NTI225214.flags = 2;
TMP498[0] = &TMP313[9];
TMP313[9].kind = 1;
TMP313[9].offset = offsetof(table225214, Data);
TMP313[9].typ = (&NTI225217);
TMP313[9].name = "data";
TMP498[1] = &TMP313[10];
TMP313[10].kind = 1;
TMP313[10].offset = offsetof(table225214, Counter);
TMP313[10].typ = (&NTI108);
TMP313[10].name = "counter";
TMP313[8].len = 2; TMP313[8].kind = 2; TMP313[8].sons = &TMP498[0];
NTI225214.node = &TMP313[8];
NTI225812.size = sizeof(keyvaluepair225812);
NTI225812.kind = 18;
NTI225812.base = 0;
NTI225812.flags = 2;
TMP500[0] = &TMP313[12];
TMP313[12].kind = 1;
TMP313[12].offset = offsetof(keyvaluepair225812, Field0);
TMP313[12].typ = (&NTI144009);
TMP313[12].name = "Field0";
TMP500[1] = &TMP313[13];
TMP313[13].kind = 1;
TMP313[13].offset = offsetof(keyvaluepair225812, Field1);
TMP313[13].typ = (&NTI149);
TMP313[13].name = "Field1";
TMP500[2] = &TMP313[14];
TMP313[14].kind = 1;
TMP313[14].offset = offsetof(keyvaluepair225812, Field2);
TMP313[14].typ = (&NTI224853);
TMP313[14].name = "Field2";
TMP313[11].len = 3; TMP313[11].kind = 2; TMP313[11].sons = &TMP500[0];
NTI225812.node = &TMP313[11];
NTI225809.size = sizeof(keyvaluepairseq225809*);
NTI225809.kind = 24;
NTI225809.base = (&NTI225812);
NTI225809.flags = 2;
NTI225809.marker = TMP501;
NTI225806.size = sizeof(table225806);
NTI225806.kind = 18;
NTI225806.base = 0;
NTI225806.flags = 2;
TMP503[0] = &TMP313[16];
TMP313[16].kind = 1;
TMP313[16].offset = offsetof(table225806, Data);
TMP313[16].typ = (&NTI225809);
TMP313[16].name = "data";
TMP503[1] = &TMP313[17];
TMP313[17].kind = 1;
TMP313[17].offset = offsetof(table225806, Counter);
TMP313[17].typ = (&NTI108);
TMP313[17].name = "counter";
TMP313[15].len = 2; TMP313[15].kind = 2; TMP313[15].sons = &TMP503[0];
NTI225806.node = &TMP313[15];
}

