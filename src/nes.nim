import 
    os, streams, strutils, parseutils, hex, macros,
    cpu, rom, mem, ppu, debug

var cycles : int

proc initRom(): void =
    var romFile : File
    #assuming we haven't any file error
    assert open(romFile, paramStr(1))  
    #nesRom is imported from rom.nim
    nesRom = loadINes(romFile) 

proc run() =
    while true:
        cycles = fetchExecuteOpcode()

proc main() = 
    #initScreen()
    initRom()
    initPpu()
    initMem()
    initCpu()
    

    # run the NES program
    run()

main()