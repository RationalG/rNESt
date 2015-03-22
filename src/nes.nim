import os, streams, strutils, parseutils, macros
import rom, cpu, ppu, mem, screen

const
    SCANLINES_PER_FRAME = 262
    CYCLES_PER_SCANLINE = 1364
    NTSC_DIVISOR = 12
    
var cycles : int

# take charge of rom & its data before it gets transfered
# into NES memory
proc initRom(): void =
    var romFile : File
    assert open(romFile, paramStr(1))  
    nesRom = loadINes(romFile) 

# execution loop
proc run() =
    while true:
        var scanlines = SCANLINES_PER_FRAME
        while scanlines > 0:
            #screen.update()
            cpu.update(CYCLES_PER_SCANLINE, NTSC_DIVISOR)
            ppu.update()  
            scanlines -= 1

# initialize all NES components & SDL screen
proc main() = 
    #initScreen()
    initRom()
    initPpu()
    initMem()
    initCpu()
    run()

main()
