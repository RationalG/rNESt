import 
    os, streams, strutils, parseutils, hex, macros,
    cpu, rom, mem, ppu, screen

const 
    CONSOLE_ENABLED = false

var cycles : int

proc initRom(): void =
    var romFile : TFile
    assert open(romFile, paramStr(1))  
    nesRom = loadINes(romFile) 

proc run() =
    while true:
        cycles = fetchExecuteOpcode()

proc main() = 
    # power on NES components one by one
    #initScreen()
    initRom()
    initMem()
    initCpu()
    initPpu()

    # run CPU instruction step by step
    # enables command line tool for the user
    if CONSOLE_ENABLED == true:
        startDebugSession(false)

    # run the NES program
    run()

main()