import terminal, strutils, typetraits, typeinfo, queues

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
proc debug*[CPUObj](cpu: CPUObj, opcode, mode: string, value: int, mem, stack: Queue[int]): void =
    var res = "\t--CPU--"
    var table = "\n|--|--|--|"
    var partialMem = mem
    var partialStack = stack
    var memValuesChain, stackValuesChain = ""
    emitOutput(opcode & " " & mode & " "  & value.toHex(4))

    for name, value in cpu.fieldPairs:
        when value is int:
          res.add("\n\t" & name & " value is : " & value.toHex(4))
    echo res

    for i in 0..2:
        memValuesChain.add("|" & $dequeue(partialMem).toHex(2))
        stackValuesChain.add("|" & $dequeue(partialStack).toHex(2))

    echo table & "\nMEMORY\n" & memValuesChain & table

    pause()

# used to debug ppu & apu
proc debug*[T](processor: T): void =
    var res = "\t--PPU regs--" 
    for name, value in processor.fieldPairs:
        when value is int:
          res.add("\n\t" & name & " value is : " & $value)
    echo res

    pause()