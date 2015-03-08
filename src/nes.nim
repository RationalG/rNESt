import os, streams, strutils, parseutils, macros
import rom, cpu, ppu, mem, screen

const
    SCANLINES_PER_FRAME = 262
    CYCLES_PER_SCANLINE = 1364
    NTSC_DIVISOR = 12

var cycles : int

proc initRom(): void =
    var romFile : File
    #assuming we haven't any file error
    assert open(romFile, paramStr(1))  
    #nesRom is imported from rom.nim
    nesRom = loadINes(romFile) 

proc run() =
    while true:
        # 262 scanlines per frame
        var scanlines = SCANLINES_PER_FRAME
        # run CPU & PPU
        while scanlines > 0:
            #screen.update()
            cpu.update(CYCLES_PER_SCANLINE, NTSC_DIVISOR)
            ppu.update()  
            scanlines -= 1
            

proc main() = 
    # initialize SDL
    #initScreen()
    # initialize NES components
    initRom()
    initPpu()
    initMem()
    initCpu()
    # run the NES program
    run()

main()