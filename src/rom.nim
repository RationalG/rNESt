import os, streams, strutils, parseutils, hex

proc c_memcmp(a, b: cstring, size: int): cint {.header: "<string.h>", noSideEffect, importc: "memcmp".}

const 
    HEADER_SIZE = 16
    SIGNATURE_SIZE = 4
    CHR_PAGE_SIZE = 8192
    PRG_PAGE_SIZE = 16384

type
    ROMObj* = object of RootObj 
        header: array[HEADER_SIZE, char]     
        prgBytes*: seq[char]
        chrBytes*: seq[char]
    HeaderObj* = object of RootObj
        signature: string
        prgSize: int
        chrSize: int
        mmByte : byte
        mapperBits: int
        mirrorBits: int

var nes_rom* : ROMObj

proc loadINes*(romFile: File): ROMObj =  
    var r : ROMObj
    var h : HeaderObj

    discard readBuffer(romFile, addr(r.header), HEADER_SIZE)

    h.signature = seqToString(r.header[0..3])
    h.prgSize = cast[int](r.header[4])*PRG_PAGE_SIZE
    h.chrSize = cast[int](r.header[5])*CHR_PAGE_SIZE
    h.mmByte = cast[byte](r.header[6])
    h.mapperBits = ((cast[int](h.mmbyte) shr 4) and 0xF)
    h.mirrorBits = (cast[int](h.mmbyte) and 0xF)

    if c_memcmp(cstring(h.signature), cstring("NES\x1A"), SIGNATURE_SIZE) ==  0 :
        echo("iNES format recognized !!!")
        echo("PRG size : ", h.prgSize/%PRG_PAGE_SIZE, " x 16kb pages : ", h.prgSize)
        echo("CHR size : ", h.chrSize/%CHR_PAGE_SIZE, " x 8kb pages :  ", h.chrSize)
    else :
        echo("Error : unknown ROM format")
        return

    r.prgBytes = newSeq[char](h.prgSize)
    r.chrBytes = newSeq[char](h.chrSize)

    discard readBuffer(romFile, addr(r.prgBytes[0]), h.prgSize)
    discard readBuffer(romFile, addr(r.chrBytes[0]), h.chrSize)

    return r