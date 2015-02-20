import cpu, mem, terminal, strutils

proc checkMemoryAt*(address: string): int =
    echo "trying memory check at " & address
    try: 
        var strAddr = address.parseInt
        result = checkFromDebug(strAddr)
    except ValueError: 
        echo "ValueError: memory address needed"
        result = -1      

proc emitOutput*(message: string): void =
    echo message & "\n"

proc debug*[CPUObj](cpu: CPUObj, opcode: string, mode: string): void =
    emitOutput(opcode & " " & mode)
    
    var step = false
    var res = "\t--CPU--" 
    for name, value in cpu.fieldPairs:
        when value is int:
          res.add("\n\t" & name & " value is : " & $value)
    echo res

    while step == false:
        var cmd = readLine(stdin)
        if cmd != "" :
            echo checkMemoryAt(cmd)
        else :
            step = true

