import 
    os, streams, strutils, parseutils, hex, macros,
    cpu, rom, mem, ppu

const 
    CONSOLE_ENABLED = true

proc initializeRom(): void =
    var romFile : TFile
    assert open(romFile, paramStr(1))  
    nesRom = loadINes(romFile)  

proc main() = 
    initializeRom()
    initializeMemory()
    initializeCpu()
    #initializePpu()

    if CONSOLE_ENABLED == true:
        startDebugSession(false)
        
    fetchExecuteOpcode()

main()
