import terminal, strutils, typetraits, typeinfo

# print opcode & addressing mode of the current instruction
proc emitOutput*(message: string): void =
    echo message & "\n"

# allow step-by-step execution
proc pause(): void = 
    var step = false
    while step == false:
        var cmd = readLine(stdin)
        if cmd != "" :
            step = false
        else :
            step = true

# restricted to cpu
proc debug*[CPUObj](cpu: CPUObj, opcode: string, mode: string): void =
    emitOutput(opcode & " " & mode)

    var res = "\t--CPU--" 
    for name, value in cpu.fieldPairs:
        when value is int:
          res.add("\n\t" & name & " value is : " & value.toHex(4))
    echo res

    pause()

# used to debug ppu & apu
proc debug*[T](processor: T): void =
    var res = "\t--PPU regs--" 
    for name, value in processor.fieldPairs:
        when value is int:
          res.add("\n\t" & name & " value is : " & $value)
    echo res

    pause()

