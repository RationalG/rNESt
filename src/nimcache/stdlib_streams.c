/* Generated by Nim Compiler v0.10.2 */
/*   (c) 2014 Andreas Rumpf */
/* The generated code is subject to the original license. */
/* Compiled for: Windows, amd64, gcc */
/* Command for C compiler:
   gcc.exe -c  -w  -IC:\Nim\lib -o c:\users\simon\rationalnes_\rnes\src\nimcache\stdlib_streams.o c:\users\simon\rationalnes_\rnes\src\nimcache\stdlib_streams.c */
#define NIM_INTBITS 64
#include "nimbase.h"

#include <string.h>

#include <stdio.h>
typedef struct ioerror3231 ioerror3231;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct systemerror3229 systemerror3229;
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
typedef struct streamobj129035 streamobj129035;
typedef struct stringstreamobj129587 stringstreamobj129587;
typedef struct filestreamobj129742 filestreamobj129742;
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
struct  systemerror3229  {
  Exception Sup;
};
struct  ioerror3231  {
  systemerror3229 Sup;
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
typedef N_NIMCALL_PTR(void, TY129036) (streamobj129035* s);
typedef N_NIMCALL_PTR(NIM_BOOL, TY129040) (streamobj129035* s);
typedef N_NIMCALL_PTR(void, TY129044) (streamobj129035* s, NI pos);
typedef N_NIMCALL_PTR(NI, TY129049) (streamobj129035* s);
typedef N_NIMCALL_PTR(NI, TY129053) (streamobj129035* s, void* buffer, NI buflen);
typedef N_NIMCALL_PTR(void, TY129059) (streamobj129035* s, void* buffer, NI buflen);
typedef N_NIMCALL_PTR(void, TY129065) (streamobj129035* s);
struct  streamobj129035  {
  TNimObject Sup;
TY129036 Closeimpl;
TY129040 Atendimpl;
TY129044 Setpositionimpl;
TY129049 Getpositionimpl;
TY129053 Readdataimpl;
TY129059 Writedataimpl;
TY129065 Flushimpl;
};
struct  stringstreamobj129587  {
  streamobj129035 Sup;
NimStringDesc* Data;
NI Pos;
};
struct  filestreamobj129742  {
  streamobj129035 Sup;
FILE* F;
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
N_NIMCALL(ioerror3231*, neweio_129005)(NimStringDesc* msg);
N_NIMCALL(void*, newObj)(TNimType* typ, NI size);
N_NIMCALL(NimStringDesc*, copyStringRC1)(NimStringDesc* src);
static N_INLINE(void, nimGCunrefNoCycle)(void* p);
static N_INLINE(tcell44933*, usrtocell_48646)(void* usr);
static N_INLINE(void, nimFrame)(TFrame* s);
N_NOINLINE(void, stackoverflow_18801)(void);
static N_INLINE(void, popFrame)(void);
static N_INLINE(void, rtladdzct_50204)(tcell44933* c);
N_NOINLINE(void, addzct_48617)(tcellseq44949* s, tcell44933* c);
N_NIMCALL(void, flush_129077)(streamobj129035* s);
N_NIMCALL(void, close_129093)(streamobj129035* s);
N_NIMCALL(void, close_129109)(streamobj129035* s, streamobj129035* unused);
N_NIMCALL(NIM_BOOL, atend_129119)(streamobj129035* s);
N_NIMCALL(NIM_BOOL, atend_129129)(streamobj129035* s, streamobj129035* unused);
N_NIMCALL(void, setposition_129140)(streamobj129035* s, NI pos);
N_NIMCALL(void, setposition_129150)(streamobj129035* s, streamobj129035* unused, NI pos);
N_NIMCALL(NI, getposition_129161)(streamobj129035* s);
N_NIMCALL(NI, getposition_129171)(streamobj129035* s, streamobj129035* unused);
N_NIMCALL(NI, readdata_129182)(streamobj129035* s, void* buffer, NI buflen);
N_NIMCALL(NI, readdata_129194)(streamobj129035* s, streamobj129035* unused, void* buffer, NI buflen);
N_NIMCALL(void, writedata_129207)(streamobj129035* s, void* buffer, NI buflen);
N_NIMCALL(void, writedata_129218)(streamobj129035* s, streamobj129035* unused, void* buffer, NI buflen);
N_NIMCALL(void, write_129241)(streamobj129035* s, NimStringDesc* x);
N_NIMCALL(void, writeln_129251)(streamobj129035* s, NimStringDesc** args, NI argsLen0);
N_NOINLINE(void, raiseIndexError)(void);
static N_INLINE(NI, addInt)(NI a, NI b);
N_NOINLINE(void, raiseOverflow)(void);
N_NIMCALL(NIM_CHAR, readchar_129298)(streamobj129035* s);
N_NIMCALL(void, read_129315)(streamobj129035* s_129319, NIM_BOOL* result_129323);
N_NIMCALL(void, raiseException)(Exception* e, NCSTRING ename);
N_NIMCALL(NIM_BOOL, readbool_129309)(streamobj129035* s);
N_NIMCALL(void, read_129346)(streamobj129035* s_129350, NI8* result_129354);
N_NIMCALL(NI8, readint8_129340)(streamobj129035* s);
N_NIMCALL(void, read_129377)(streamobj129035* s_129381, NI16* result_129385);
N_NIMCALL(NI16, readint16_129371)(streamobj129035* s);
N_NIMCALL(void, read_129408)(streamobj129035* s_129412, NI32* result_129416);
N_NIMCALL(NI32, readint32_129402)(streamobj129035* s);
N_NIMCALL(void, read_129439)(streamobj129035* s_129443, NI64* result_129447);
N_NIMCALL(NI64, readint64_129433)(streamobj129035* s);
N_NIMCALL(void, read_129470)(streamobj129035* s_129474, NF32* result_129478);
N_NIMCALL(NF32, readfloat32_129464)(streamobj129035* s);
N_NIMCALL(void, read_129501)(streamobj129035* s_129505, NF* result_129509);
N_NIMCALL(NF, readfloat64_129495)(streamobj129035* s);
N_NIMCALL(NimStringDesc*, readstr_129526)(streamobj129035* s, NI length);
N_NIMCALL(NimStringDesc*, mnewString)(NI len);
N_NIMCALL(NimStringDesc*, mnewString)(NI len);
N_NIMCALL(NimStringDesc*, setLengthStr)(NimStringDesc* s, NI newlen);
N_NIMCALL(NIM_BOOL, readline_129541)(streamobj129035* s, NimStringDesc** line);
N_NIMCALL(NimStringDesc*, addChar)(NimStringDesc* s, NIM_CHAR c);
N_NIMCALL(NimStringDesc*, readline_129564)(streamobj129035* s);
N_NIMCALL(NimStringDesc*, copyString)(NimStringDesc* src);
N_NIMCALL(NIM_BOOL, ssatend_129598)(streamobj129035* s_129600);
N_NIMCALL(void, chckObj)(TNimType* obj, TNimType* subclass);
N_NIMCALL(NI, clamp_129615)(NI x_129619, NI a_129621, NI b_129623);
N_NIMCALL(void, sssetposition_129609)(streamobj129035* s_129611, NI pos);
N_NIMCALL(NI, ssgetposition_129636)(streamobj129035* s_129638);
N_NIMCALL(NI, ssreaddata_129647)(streamobj129035* s_129649, void* buffer, NI buflen);
static N_INLINE(NI, subInt)(NI a, NI b);
N_NIMCALL(void, sswritedata_129677)(streamobj129035* s_129679, void* buffer, NI buflen);
N_NIMCALL(void, ssclose_129703)(streamobj129035* s_129705);
N_NIMCALL(stringstreamobj129587*, newstringstream_129713)(NimStringDesc* s);
N_NIMCALL(void, nimGCvisit)(void* d, NI op);
N_NIMCALL(void, TMP280)(void* p, NI op);
N_NIMCALL(void, fsclose_129746)(streamobj129035* s);
N_NIMCALL(void, fsflush_129769)(streamobj129035* s);
N_NIMCALL(NIM_BOOL, fsatend_129775)(streamobj129035* s);
N_NIMCALL(NIM_BOOL, endoffile_12830)(FILE* f);
N_NIMCALL(void, fssetposition_129782)(streamobj129035* s, NI pos);
N_NIMCALL(void, setfilepos_13051)(FILE* f, NI64 pos);
N_NIMCALL(NI, fsgetposition_129789)(streamobj129035* s);
N_NIMCALL(NI64, getfilepos_13055)(FILE* f);
N_NIMCALL(NI, fsreaddata_129797)(streamobj129035* s, void* buffer, NI buflen);
N_NIMCALL(NI, readbuffer_13027)(FILE* f, void* buffer, NI len);
N_NIMCALL(void, fswritedata_129806)(streamobj129035* s, void* buffer, NI buflen);
N_NIMCALL(NI, writebuffer_13046)(FILE* f, void* buffer, NI len);
N_NIMCALL(filestreamobj129742*, newfilestream_129814)(FILE* f);
N_NIMCALL(void, TMP282)(void* p, NI op);
N_NIMCALL(filestreamobj129742*, newfilestream_129837)(NimStringDesc* filename, NU8 mode);
N_NIMCALL(NIM_BOOL, open_12603)(FILE** f, NimStringDesc* filename, NU8 mode, NI bufsize);
STRING_LITERAL(TMP273, "\015\012", 2);
STRING_LITERAL(TMP274, "cannot read from stream", 23);
STRING_LITERAL(TMP275, "", 0);
STRING_LITERAL(TMP281, "cannot write to stream", 22);
extern TNimType NTI12801; /* ref IOError */
extern TNimType NTI3231; /* IOError */
extern TFrame* frameptr_16242;
extern tgcheap47016 gch_47044;
extern TNimType NTI3211; /* RootObj */
TNimType NTI129035; /* StreamObj */
TNimType NTI129036; /* proc (Stream){.gcsafe.} */
TNimType NTI129040; /* proc (Stream): bool{.gcsafe.} */
TNimType NTI129044; /* proc (Stream, int){.gcsafe.} */
TNimType NTI129049; /* proc (Stream): int{.gcsafe.} */
TNimType NTI129053; /* proc (Stream, pointer, int): int{.gcsafe.} */
TNimType NTI129059; /* proc (Stream, pointer, int){.gcsafe.} */
TNimType NTI129065; /* proc (Stream){.gcsafe.} */
TNimType NTI129587; /* StringStreamObj */
extern TNimType NTI149; /* string */
extern TNimType NTI108; /* int */
TNimType NTI129585; /* StringStream */
TNimType NTI129742; /* FileStreamObj */
extern TNimType NTI12404; /* File */
TNimType NTI129740; /* FileStream */

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

N_NIMCALL(ioerror3231*, neweio_129005)(NimStringDesc* msg) {
	ioerror3231* result;
	NimStringDesc* LOC1;
	nimfr("newEIO", "streams.nim")
	result = 0;
	nimln(18, "streams.nim");
	result = (ioerror3231*) newObj((&NTI12801), sizeof(ioerror3231));
	(*result).Sup.Sup.Sup.m_type = (&NTI3231);
	nimln(19, "streams.nim");
	LOC1 = 0;
	LOC1 = (*result).Sup.Sup.message; (*result).Sup.Sup.message = copyStringRC1(msg);
	if (LOC1) nimGCunrefNoCycle(LOC1);
	popFrame();
	return result;
}

N_NIMCALL(void, flush_129077)(streamobj129035* s) {
	nimfr("flush", "streams.nim")
	nimln(42, "streams.nim");
	{
		nimln(42, "streams.nim");
		nimln(42, "streams.nim");
		if (!!((*s).Flushimpl == 0)) goto LA3;
		nimln(42, "streams.nim");
		(*s).Flushimpl(s);
	}
	LA3: ;
	popFrame();
}

N_NIMCALL(void, close_129093)(streamobj129035* s) {
	nimfr("close", "streams.nim")
	nimln(46, "streams.nim");
	{
		nimln(46, "streams.nim");
		nimln(46, "streams.nim");
		if (!!((*s).Closeimpl == 0)) goto LA3;
		nimln(46, "streams.nim");
		(*s).Closeimpl(s);
	}
	LA3: ;
	popFrame();
}

N_NIMCALL(void, close_129109)(streamobj129035* s, streamobj129035* unused) {
	nimfr("close", "streams.nim")
	nimln(50, "streams.nim");
	(*s).Closeimpl(s);
	popFrame();
}

N_NIMCALL(NIM_BOOL, atend_129119)(streamobj129035* s) {
	NIM_BOOL result;
	nimfr("atEnd", "streams.nim")
	result = 0;
	nimln(55, "streams.nim");
	result = (*s).Atendimpl(s);
	popFrame();
	return result;
}

N_NIMCALL(NIM_BOOL, atend_129129)(streamobj129035* s, streamobj129035* unused) {
	NIM_BOOL result;
	nimfr("atEnd", "streams.nim")
	result = 0;
	nimln(60, "streams.nim");
	result = (*s).Atendimpl(s);
	popFrame();
	return result;
}

N_NIMCALL(void, setposition_129140)(streamobj129035* s, NI pos) {
	nimfr("setPosition", "streams.nim")
	nimln(64, "streams.nim");
	(*s).Setpositionimpl(s, pos);
	popFrame();
}

N_NIMCALL(void, setposition_129150)(streamobj129035* s, streamobj129035* unused, NI pos) {
	nimfr("setPosition", "streams.nim")
	nimln(68, "streams.nim");
	(*s).Setpositionimpl(s, pos);
	popFrame();
}

N_NIMCALL(NI, getposition_129161)(streamobj129035* s) {
	NI result;
	nimfr("getPosition", "streams.nim")
	result = 0;
	nimln(72, "streams.nim");
	result = (*s).Getpositionimpl(s);
	popFrame();
	return result;
}

N_NIMCALL(NI, getposition_129171)(streamobj129035* s, streamobj129035* unused) {
	NI result;
	nimfr("getPosition", "streams.nim")
	result = 0;
	nimln(76, "streams.nim");
	result = (*s).Getpositionimpl(s);
	popFrame();
	return result;
}

N_NIMCALL(NI, readdata_129182)(streamobj129035* s, void* buffer, NI buflen) {
	NI result;
	nimfr("readData", "streams.nim")
	result = 0;
	nimln(80, "streams.nim");
	result = (*s).Readdataimpl(s, buffer, buflen);
	popFrame();
	return result;
}

N_NIMCALL(NI, readdata_129194)(streamobj129035* s, streamobj129035* unused, void* buffer, NI buflen) {
	NI result;
	nimfr("readData", "streams.nim")
	result = 0;
	nimln(85, "streams.nim");
	result = (*s).Readdataimpl(s, buffer, buflen);
	popFrame();
	return result;
}

N_NIMCALL(void, writedata_129207)(streamobj129035* s, void* buffer, NI buflen) {
	nimfr("writeData", "streams.nim")
	nimln(90, "streams.nim");
	(*s).Writedataimpl(s, buffer, buflen);
	popFrame();
}

N_NIMCALL(void, writedata_129218)(streamobj129035* s, streamobj129035* unused, void* buffer, NI buflen) {
	nimfr("writeData", "streams.nim")
	nimln(96, "streams.nim");
	(*s).Writedataimpl(s, buffer, buflen);
	popFrame();
}

N_NIMCALL(void, write_129241)(streamobj129035* s, NimStringDesc* x) {
	nimfr("write", "streams.nim")
	nimln(111, "streams.nim");
	nimln(111, "streams.nim");
	writedata_129207(s, ((void*) (x->data)), x->Sup.len);
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

N_NIMCALL(void, writeln_129251)(streamobj129035* s, NimStringDesc** args, NI argsLen0) {
	nimfr("writeln", "streams.nim")
	{
		NimStringDesc* str_129267;
		NI i_129271;
		str_129267 = 0;
		nimln(1649, "system.nim");
		i_129271 = 0;
		{
			nimln(1650, "system.nim");
			while (1) {
				nimln(1650, "system.nim");
				nimln(1650, "system.nim");
				if (!(i_129271 < argsLen0)) goto LA3;
				nimln(1651, "system.nim");
				if ((NU)(i_129271) >= (NU)(argsLen0)) raiseIndexError();
				str_129267 = args[i_129271];
				nimln(116, "streams.nim");
				write_129241(s, str_129267);
				nimln(1652, "system.nim");
				i_129271 = addInt(i_129271, 1);
			} LA3: ;
		}
	}
	nimln(117, "streams.nim");
	write_129241(s, ((NimStringDesc*) &TMP273));
	popFrame();
}

N_NIMCALL(NIM_CHAR, readchar_129298)(streamobj129035* s) {
	NIM_CHAR result;
	nimfr("readChar", "streams.nim")
	result = 0;
	nimln(127, "streams.nim");
	{
		NI LOC3;
		nimln(127, "streams.nim");
		nimln(127, "streams.nim");
		nimln(127, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s, ((void*) ((&result))), 1);
		if (!!((LOC3 == 1))) goto LA4;
		nimln(127, "streams.nim");
		result = 0;
	}
	LA4: ;
	popFrame();
	return result;
}

N_NIMCALL(void, read_129315)(streamobj129035* s_129319, NIM_BOOL* result_129323) {
	nimfr("read", "streams.nim")
	nimln(121, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s_129319, ((void*) (result_129323)), 1);
		if (!!((LOC3 == 1))) goto LA4;
		nimln(122, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP274));
		nimln(122, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(NIM_BOOL, readbool_129309)(streamobj129035* s) {
	NIM_BOOL result;
	nimfr("readBool", "streams.nim")
	result = 0;
	nimln(131, "streams.nim");
	read_129315(s, (&result));
	popFrame();
	return result;
}

N_NIMCALL(void, read_129346)(streamobj129035* s_129350, NI8* result_129354) {
	nimfr("read", "streams.nim")
	nimln(121, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s_129350, ((void*) (result_129354)), 1);
		if (!!((LOC3 == 1))) goto LA4;
		nimln(122, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP274));
		nimln(122, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(NI8, readint8_129340)(streamobj129035* s) {
	NI8 result;
	nimfr("readInt8", "streams.nim")
	result = 0;
	nimln(135, "streams.nim");
	read_129346(s, (&result));
	popFrame();
	return result;
}

N_NIMCALL(void, read_129377)(streamobj129035* s_129381, NI16* result_129385) {
	nimfr("read", "streams.nim")
	nimln(121, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s_129381, ((void*) (result_129385)), 2);
		if (!!((LOC3 == 2))) goto LA4;
		nimln(122, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP274));
		nimln(122, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(NI16, readint16_129371)(streamobj129035* s) {
	NI16 result;
	nimfr("readInt16", "streams.nim")
	result = 0;
	nimln(139, "streams.nim");
	read_129377(s, (&result));
	popFrame();
	return result;
}

N_NIMCALL(void, read_129408)(streamobj129035* s_129412, NI32* result_129416) {
	nimfr("read", "streams.nim")
	nimln(121, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s_129412, ((void*) (result_129416)), 4);
		if (!!((LOC3 == 4))) goto LA4;
		nimln(122, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP274));
		nimln(122, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(NI32, readint32_129402)(streamobj129035* s) {
	NI32 result;
	nimfr("readInt32", "streams.nim")
	result = 0;
	nimln(143, "streams.nim");
	read_129408(s, (&result));
	popFrame();
	return result;
}

N_NIMCALL(void, read_129439)(streamobj129035* s_129443, NI64* result_129447) {
	nimfr("read", "streams.nim")
	nimln(121, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s_129443, ((void*) (result_129447)), 8);
		if (!!((LOC3 == 8))) goto LA4;
		nimln(122, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP274));
		nimln(122, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(NI64, readint64_129433)(streamobj129035* s) {
	NI64 result;
	nimfr("readInt64", "streams.nim")
	result = 0;
	nimln(147, "streams.nim");
	read_129439(s, (&result));
	popFrame();
	return result;
}

N_NIMCALL(void, read_129470)(streamobj129035* s_129474, NF32* result_129478) {
	nimfr("read", "streams.nim")
	nimln(121, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s_129474, ((void*) (result_129478)), 4);
		if (!!((LOC3 == 4))) goto LA4;
		nimln(122, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP274));
		nimln(122, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(NF32, readfloat32_129464)(streamobj129035* s) {
	NF32 result;
	nimfr("readFloat32", "streams.nim")
	result = 0;
	nimln(151, "streams.nim");
	read_129470(s, (&result));
	popFrame();
	return result;
}

N_NIMCALL(void, read_129501)(streamobj129035* s_129505, NF* result_129509) {
	nimfr("read", "streams.nim")
	nimln(121, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		nimln(121, "streams.nim");
		LOC3 = 0;
		LOC3 = readdata_129182(s_129505, ((void*) (result_129509)), 8);
		if (!!((LOC3 == 8))) goto LA4;
		nimln(122, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP274));
		nimln(122, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}

N_NIMCALL(NF, readfloat64_129495)(streamobj129035* s) {
	NF result;
	nimfr("readFloat64", "streams.nim")
	result = 0;
	nimln(155, "streams.nim");
	read_129501(s, (&result));
	popFrame();
	return result;
}

N_NIMCALL(NimStringDesc*, readstr_129526)(streamobj129035* s, NI length) {
	NimStringDesc* result;
	NI l;
	nimfr("readStr", "streams.nim")
	result = 0;
	nimln(160, "streams.nim");
	nimln(160, "streams.nim");
	result = mnewString(length);
	nimln(161, "streams.nim");
	if ((NU)(0) > (NU)(result->Sup.len)) raiseIndexError();
	l = readdata_129182(s, ((void*) ((&result->data[0]))), length);
	nimln(162, "streams.nim");
	{
		nimln(162, "streams.nim");
		nimln(162, "streams.nim");
		if (!!((l == length))) goto LA3;
		nimln(162, "streams.nim");
		result = setLengthStr(result, l);
	}
	LA3: ;
	popFrame();
	return result;
}

N_NIMCALL(NIM_BOOL, readline_129541)(streamobj129035* s, NimStringDesc** line) {
	NIM_BOOL result;
	nimfr("readLine", "streams.nim")
	result = 0;
	nimln(171, "streams.nim");
	(*line) = setLengthStr((*line), 0);
	{
		nimln(172, "streams.nim");
		while (1) {
			NIM_CHAR c;
			nimln(173, "streams.nim");
			c = readchar_129298(s);
			nimln(174, "streams.nim");
			{
				nimln(174, "streams.nim");
				if (!((NU8)(c) == (NU8)(13))) goto LA5;
				nimln(175, "streams.nim");
				c = readchar_129298(s);
				nimln(176, "streams.nim");
				goto LA1;
			}
			goto LA3;
			LA5: ;
			{
				nimln(177, "streams.nim");
				if (!((NU8)(c) == (NU8)(10))) goto LA8;
				nimln(177, "streams.nim");
				goto LA1;
			}
			goto LA3;
			LA8: ;
			{
				nimln(178, "streams.nim");
				if (!((NU8)(c) == (NU8)(0))) goto LA11;
				nimln(179, "streams.nim");
				{
					nimln(179, "streams.nim");
					nimln(179, "streams.nim");
					if (!(0 < (*line)->Sup.len)) goto LA15;
					nimln(179, "streams.nim");
					goto LA1;
				}
				goto LA13;
				LA15: ;
				{
					nimln(180, "streams.nim");
					nimln(180, "streams.nim");
					result = NIM_FALSE;
					goto BeforeRet;
				}
				LA13: ;
			}
			goto LA3;
			LA11: ;
			LA3: ;
			nimln(181, "streams.nim");
			(*line) = addChar((*line), c);
		}
	} LA1: ;
	nimln(182, "streams.nim");
	result = NIM_TRUE;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(NimStringDesc*, readline_129564)(streamobj129035* s) {
	NimStringDesc* result;
	nimfr("readLine", "streams.nim")
	result = 0;
	nimln(187, "streams.nim");
	result = copyString(((NimStringDesc*) &TMP275));
	{
		nimln(188, "streams.nim");
		while (1) {
			NIM_CHAR c;
			nimln(189, "streams.nim");
			c = readchar_129298(s);
			nimln(190, "streams.nim");
			{
				nimln(190, "streams.nim");
				if (!((NU8)(c) == (NU8)(13))) goto LA5;
				nimln(191, "streams.nim");
				c = readchar_129298(s);
				nimln(192, "streams.nim");
				goto LA1;
			}
			LA5: ;
			nimln(193, "streams.nim");
			{
				NIM_BOOL LOC9;
				nimln(193, "streams.nim");
				LOC9 = 0;
				nimln(193, "streams.nim");
				LOC9 = ((NU8)(c) == (NU8)(10));
				if (LOC9) goto LA10;
				nimln(193, "streams.nim");
				LOC9 = ((NU8)(c) == (NU8)(0));
				LA10: ;
				if (!LOC9) goto LA11;
				nimln(194, "streams.nim");
				goto LA1;
			}
			goto LA7;
			LA11: ;
			{
				nimln(196, "streams.nim");
				result = addChar(result, c);
			}
			LA7: ;
		}
	} LA1: ;
	popFrame();
	return result;
}

N_NIMCALL(NIM_BOOL, ssatend_129598)(streamobj129035* s_129600) {
	NIM_BOOL result;
	stringstreamobj129587* s;
	nimfr("ssAtEnd", "streams.nim")
	result = 0;
	nimln(207, "streams.nim");
	if (s_129600) chckObj((*s_129600).Sup.m_type, (&NTI129587));
	s = ((stringstreamobj129587*) (s_129600));
	nimln(208, "streams.nim");
	nimln(208, "streams.nim");
	nimln(208, "streams.nim");
	nimln(208, "streams.nim");
	result = ((*s).Data->Sup.len <= (*s).Pos);
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(void, sssetposition_129609)(streamobj129035* s_129611, NI pos) {
	stringstreamobj129587* s;
	nimfr("ssSetPosition", "streams.nim")
	nimln(211, "streams.nim");
	if (s_129611) chckObj((*s_129611).Sup.m_type, (&NTI129587));
	s = ((stringstreamobj129587*) (s_129611));
	nimln(212, "streams.nim");
	nimln(212, "streams.nim");
	(*s).Pos = clamp_129615(pos, 0, ((*s).Data->Sup.len-1));
	popFrame();
}

N_NIMCALL(NI, ssgetposition_129636)(streamobj129035* s_129638) {
	NI result;
	stringstreamobj129587* s;
	nimfr("ssGetPosition", "streams.nim")
	result = 0;
	nimln(215, "streams.nim");
	if (s_129638) chckObj((*s_129638).Sup.m_type, (&NTI129587));
	s = ((stringstreamobj129587*) (s_129638));
	nimln(216, "streams.nim");
	nimln(216, "streams.nim");
	result = (*s).Pos;
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
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

N_NIMCALL(NI, ssreaddata_129647)(streamobj129035* s_129649, void* buffer, NI buflen) {
	NI result;
	stringstreamobj129587* s;
	NI TMP278;
	nimfr("ssReadData", "streams.nim")
	result = 0;
	nimln(219, "streams.nim");
	if (s_129649) chckObj((*s_129649).Sup.m_type, (&NTI129587));
	s = ((stringstreamobj129587*) (s_129649));
	nimln(220, "streams.nim");
	nimln(220, "streams.nim");
	nimln(220, "streams.nim");
	nimln(220, "streams.nim");
	TMP278 = subInt((*s).Data->Sup.len, (*s).Pos);
	result = ((buflen <= (NI64)(TMP278)) ? buflen : (NI64)(TMP278));
	nimln(221, "streams.nim");
	{
		nimln(221, "streams.nim");
		if (!(0 < result)) goto LA3;
		nimln(222, "streams.nim");
		if ((NU)((*s).Pos) > (NU)((*s).Data->Sup.len)) raiseIndexError();
		memcpy(buffer, ((void*) ((&(*s).Data->data[(*s).Pos]))), result);
		nimln(223, "streams.nim");
		(*s).Pos = addInt((*s).Pos, result);
	}
	LA3: ;
	popFrame();
	return result;
}

N_NIMCALL(void, sswritedata_129677)(streamobj129035* s_129679, void* buffer, NI buflen) {
	stringstreamobj129587* s;
	nimfr("ssWriteData", "streams.nim")
	nimln(226, "streams.nim");
	if (s_129679) chckObj((*s_129679).Sup.m_type, (&NTI129587));
	s = ((stringstreamobj129587*) (s_129679));
	nimln(227, "streams.nim");
	{
		NI TMP279;
		nimln(227, "streams.nim");
		if (!(0 < buflen)) goto LA3;
		nimln(228, "streams.nim");
		nimln(228, "streams.nim");
		nimln(228, "streams.nim");
		TMP279 = addInt((*s).Data->Sup.len, buflen);
		(*s).Data = setLengthStr((*s).Data, (NI64)(TMP279));
		nimln(229, "streams.nim");
		if ((NU)((*s).Pos) > (NU)((*s).Data->Sup.len)) raiseIndexError();
		memcpy(((void*) ((&(*s).Data->data[(*s).Pos]))), buffer, buflen);
		nimln(230, "streams.nim");
		(*s).Pos = addInt((*s).Pos, buflen);
	}
	LA3: ;
	popFrame();
}

N_NIMCALL(void, ssclose_129703)(streamobj129035* s_129705) {
	stringstreamobj129587* s;
	NimStringDesc* LOC1;
	nimfr("ssClose", "streams.nim")
	nimln(233, "streams.nim");
	if (s_129705) chckObj((*s_129705).Sup.m_type, (&NTI129587));
	s = ((stringstreamobj129587*) (s_129705));
	nimln(234, "streams.nim");
	LOC1 = 0;
	LOC1 = (*s).Data; (*s).Data = copyStringRC1(NIM_NIL);
	if (LOC1) nimGCunrefNoCycle(LOC1);
	popFrame();
}
N_NIMCALL(void, TMP280)(void* p, NI op) {
	stringstreamobj129587* a;
	a = (stringstreamobj129587*)p;
	nimGCvisit((void*)(*a).Data, op);
}

N_NIMCALL(stringstreamobj129587*, newstringstream_129713)(NimStringDesc* s) {
	stringstreamobj129587* result;
	NimStringDesc* LOC1;
	nimfr("newStringStream", "streams.nim")
	result = 0;
	nimln(238, "streams.nim");
	result = (stringstreamobj129587*) newObj((&NTI129585), sizeof(stringstreamobj129587));
	(*result).Sup.Sup.m_type = (&NTI129587);
	nimln(239, "streams.nim");
	LOC1 = 0;
	LOC1 = (*result).Data; (*result).Data = copyStringRC1(s);
	if (LOC1) nimGCunrefNoCycle(LOC1);
	nimln(240, "streams.nim");
	(*result).Pos = 0;
	nimln(241, "streams.nim");
	(*result).Sup.Closeimpl = ssclose_129703;
	nimln(242, "streams.nim");
	(*result).Sup.Atendimpl = ssatend_129598;
	nimln(243, "streams.nim");
	(*result).Sup.Setpositionimpl = sssetposition_129609;
	nimln(244, "streams.nim");
	(*result).Sup.Getpositionimpl = ssgetposition_129636;
	nimln(245, "streams.nim");
	(*result).Sup.Readdataimpl = ssreaddata_129647;
	nimln(246, "streams.nim");
	(*result).Sup.Writedataimpl = sswritedata_129677;
	popFrame();
	return result;
}

N_NIMCALL(void, fsclose_129746)(streamobj129035* s) {
	nimfr("fsClose", "streams.nim")
	nimln(257, "streams.nim");
	{
		nimln(257, "streams.nim");
		nimln(257, "streams.nim");
		if (s) chckObj((*s).Sup.m_type, (&NTI129742));
		if (!!(((*((filestreamobj129742*) (s))).F == NIM_NIL))) goto LA3;
		nimln(258, "streams.nim");
		if (s) chckObj((*s).Sup.m_type, (&NTI129742));
		fclose((*((filestreamobj129742*) (s))).F);
		nimln(259, "streams.nim");
		if (s) chckObj((*s).Sup.m_type, (&NTI129742));
		(*((filestreamobj129742*) (s))).F = NIM_NIL;
	}
	LA3: ;
	popFrame();
}

N_NIMCALL(void, fsflush_129769)(streamobj129035* s) {
	nimfr("fsFlush", "streams.nim")
	nimln(260, "streams.nim");
	if (s) chckObj((*s).Sup.m_type, (&NTI129742));
	fflush((*((filestreamobj129742*) (s))).F);
	popFrame();
}

N_NIMCALL(NIM_BOOL, fsatend_129775)(streamobj129035* s) {
	NIM_BOOL result;
	nimfr("fsAtEnd", "streams.nim")
	result = 0;
	nimln(261, "streams.nim");
	nimln(261, "streams.nim");
	if (s) chckObj((*s).Sup.m_type, (&NTI129742));
	result = endoffile_12830((*((filestreamobj129742*) (s))).F);
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(void, fssetposition_129782)(streamobj129035* s, NI pos) {
	nimfr("fsSetPosition", "streams.nim")
	nimln(262, "streams.nim");
	if (s) chckObj((*s).Sup.m_type, (&NTI129742));
	setfilepos_13051((*((filestreamobj129742*) (s))).F, ((NI64) (pos)));
	popFrame();
}

N_NIMCALL(NI, fsgetposition_129789)(streamobj129035* s) {
	NI result;
	NI64 LOC1;
	nimfr("fsGetPosition", "streams.nim")
	result = 0;
	nimln(263, "streams.nim");
	nimln(263, "streams.nim");
	nimln(263, "streams.nim");
	if (s) chckObj((*s).Sup.m_type, (&NTI129742));
	LOC1 = 0;
	LOC1 = getfilepos_13055((*((filestreamobj129742*) (s))).F);
	result = ((NI) (LOC1));
	goto BeforeRet;
	BeforeRet: ;
	popFrame();
	return result;
}

N_NIMCALL(NI, fsreaddata_129797)(streamobj129035* s, void* buffer, NI buflen) {
	NI result;
	nimfr("fsReadData", "streams.nim")
	result = 0;
	nimln(266, "streams.nim");
	if (s) chckObj((*s).Sup.m_type, (&NTI129742));
	result = readbuffer_13027((*((filestreamobj129742*) (s))).F, buffer, buflen);
	popFrame();
	return result;
}

N_NIMCALL(void, fswritedata_129806)(streamobj129035* s, void* buffer, NI buflen) {
	nimfr("fsWriteData", "streams.nim")
	nimln(269, "streams.nim");
	{
		NI LOC3;
		ioerror3231* LOC6;
		nimln(269, "streams.nim");
		nimln(269, "streams.nim");
		nimln(269, "streams.nim");
		if (s) chckObj((*s).Sup.m_type, (&NTI129742));
		LOC3 = 0;
		LOC3 = writebuffer_13046((*((filestreamobj129742*) (s))).F, buffer, buflen);
		if (!!((LOC3 == buflen))) goto LA4;
		nimln(270, "streams.nim");
		LOC6 = 0;
		LOC6 = neweio_129005(((NimStringDesc*) &TMP281));
		nimln(270, "streams.nim");
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
	popFrame();
}
N_NIMCALL(void, TMP282)(void* p, NI op) {
	filestreamobj129742* a;
	a = (filestreamobj129742*)p;
}

N_NIMCALL(filestreamobj129742*, newfilestream_129814)(FILE* f) {
	filestreamobj129742* result;
	nimfr("newFileStream", "streams.nim")
	result = 0;
	nimln(274, "streams.nim");
	result = (filestreamobj129742*) newObj((&NTI129740), sizeof(filestreamobj129742));
	(*result).Sup.Sup.m_type = (&NTI129742);
	nimln(275, "streams.nim");
	(*result).F = f;
	nimln(276, "streams.nim");
	(*result).Sup.Closeimpl = fsclose_129746;
	nimln(277, "streams.nim");
	(*result).Sup.Atendimpl = fsatend_129775;
	nimln(278, "streams.nim");
	(*result).Sup.Setpositionimpl = fssetposition_129782;
	nimln(279, "streams.nim");
	(*result).Sup.Getpositionimpl = fsgetposition_129789;
	nimln(280, "streams.nim");
	(*result).Sup.Readdataimpl = fsreaddata_129797;
	nimln(281, "streams.nim");
	(*result).Sup.Writedataimpl = fswritedata_129806;
	nimln(282, "streams.nim");
	(*result).Sup.Flushimpl = fsflush_129769;
	popFrame();
	return result;
}

N_NIMCALL(filestreamobj129742*, newfilestream_129837)(NimStringDesc* filename, NU8 mode) {
	filestreamobj129742* result;
	FILE* f;
	nimfr("newFileStream", "streams.nim")
	result = 0;
	f = 0;
	nimln(289, "streams.nim");
	{
		NIM_BOOL LOC3;
		nimln(289, "streams.nim");
		LOC3 = 0;
		LOC3 = open_12603(&f, filename, mode, -1);
		if (!LOC3) goto LA4;
		nimln(289, "streams.nim");
		result = newfilestream_129814(f);
	}
	LA4: ;
	popFrame();
	return result;
}
NIM_EXTERNC N_NOINLINE(void, stdlib_streamsInit)(void) {
	nimfr("streams", "streams.nim")
	popFrame();
}

NIM_EXTERNC N_NOINLINE(void, stdlib_streamsDatInit)(void) {
static TNimNode* TMP276[7];
static TNimNode* TMP277[2];
static TNimNode TMP271[12];
NTI129035.size = sizeof(streamobj129035);
NTI129035.kind = 17;
NTI129035.base = (&NTI3211);
NTI129035.flags = 1;
TMP276[0] = &TMP271[1];
NTI129036.size = sizeof(TY129036);
NTI129036.kind = 25;
NTI129036.base = 0;
NTI129036.flags = 3;
TMP271[1].kind = 1;
TMP271[1].offset = offsetof(streamobj129035, Closeimpl);
TMP271[1].typ = (&NTI129036);
TMP271[1].name = "closeImpl";
TMP276[1] = &TMP271[2];
NTI129040.size = sizeof(TY129040);
NTI129040.kind = 25;
NTI129040.base = 0;
NTI129040.flags = 3;
TMP271[2].kind = 1;
TMP271[2].offset = offsetof(streamobj129035, Atendimpl);
TMP271[2].typ = (&NTI129040);
TMP271[2].name = "atEndImpl";
TMP276[2] = &TMP271[3];
NTI129044.size = sizeof(TY129044);
NTI129044.kind = 25;
NTI129044.base = 0;
NTI129044.flags = 3;
TMP271[3].kind = 1;
TMP271[3].offset = offsetof(streamobj129035, Setpositionimpl);
TMP271[3].typ = (&NTI129044);
TMP271[3].name = "setPositionImpl";
TMP276[3] = &TMP271[4];
NTI129049.size = sizeof(TY129049);
NTI129049.kind = 25;
NTI129049.base = 0;
NTI129049.flags = 3;
TMP271[4].kind = 1;
TMP271[4].offset = offsetof(streamobj129035, Getpositionimpl);
TMP271[4].typ = (&NTI129049);
TMP271[4].name = "getPositionImpl";
TMP276[4] = &TMP271[5];
NTI129053.size = sizeof(TY129053);
NTI129053.kind = 25;
NTI129053.base = 0;
NTI129053.flags = 3;
TMP271[5].kind = 1;
TMP271[5].offset = offsetof(streamobj129035, Readdataimpl);
TMP271[5].typ = (&NTI129053);
TMP271[5].name = "readDataImpl";
TMP276[5] = &TMP271[6];
NTI129059.size = sizeof(TY129059);
NTI129059.kind = 25;
NTI129059.base = 0;
NTI129059.flags = 3;
TMP271[6].kind = 1;
TMP271[6].offset = offsetof(streamobj129035, Writedataimpl);
TMP271[6].typ = (&NTI129059);
TMP271[6].name = "writeDataImpl";
TMP276[6] = &TMP271[7];
NTI129065.size = sizeof(TY129065);
NTI129065.kind = 25;
NTI129065.base = 0;
NTI129065.flags = 3;
TMP271[7].kind = 1;
TMP271[7].offset = offsetof(streamobj129035, Flushimpl);
TMP271[7].typ = (&NTI129065);
TMP271[7].name = "flushImpl";
TMP271[0].len = 7; TMP271[0].kind = 2; TMP271[0].sons = &TMP276[0];
NTI129035.node = &TMP271[0];
NTI129587.size = sizeof(stringstreamobj129587);
NTI129587.kind = 17;
NTI129587.base = (&NTI129035);
TMP277[0] = &TMP271[9];
TMP271[9].kind = 1;
TMP271[9].offset = offsetof(stringstreamobj129587, Data);
TMP271[9].typ = (&NTI149);
TMP271[9].name = "data";
TMP277[1] = &TMP271[10];
TMP271[10].kind = 1;
TMP271[10].offset = offsetof(stringstreamobj129587, Pos);
TMP271[10].typ = (&NTI108);
TMP271[10].name = "pos";
TMP271[8].len = 2; TMP271[8].kind = 2; TMP271[8].sons = &TMP277[0];
NTI129587.node = &TMP271[8];
NTI129585.size = sizeof(stringstreamobj129587*);
NTI129585.kind = 22;
NTI129585.base = (&NTI129587);
NTI129585.marker = TMP280;
NTI129742.size = sizeof(filestreamobj129742);
NTI129742.kind = 17;
NTI129742.base = (&NTI129035);
NTI129742.flags = 1;
TMP271[11].kind = 1;
TMP271[11].offset = offsetof(filestreamobj129742, F);
TMP271[11].typ = (&NTI12404);
TMP271[11].name = "f";
NTI129742.node = &TMP271[11];
NTI129740.size = sizeof(filestreamobj129742*);
NTI129740.kind = 22;
NTI129740.base = (&NTI129742);
NTI129740.marker = TMP282;
}
