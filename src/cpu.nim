import strutils, macros, queues, tables
import mem, debug

type
    CPUObj* = object of RootObj
        a, x, y, s, pc: int
        i, z, c, b, d, n, v : int
        opcodeCycles : int
        zeropage : bool

const
    VECTOR_NMI = 0xFFFA
    VECTOR_IRQ = 0xFFFE
    VECTOR_RESET = 0xFFFC
    # output : addressing mode, opcode
    DEBUGGER_ENABLED = true

var nesCpu* : CPUObj

proc pushOnStackRegister(value: int): void =
    mmioWrite(nesCpu.s, value)
    nesCpu.s -= 1

proc pullFromStackRegister(): int =
    result = mmioRead(nesCpu.s)
    mmioWrite(nesCpu.s, 0)
    nesCpu.s += 1

#################################################
#        6502 MOS PROCESSOR INSTRUCTIONS        #
#################################################

proc opBrk(vByte: int): void =
    # remember: a memory location can't hold
    # more than 8 bits, so we must divide the 16-bits
    # absolute address in two parts
    var lowByte = (nesCpu.pc - 1) and 0xFF
    var highByte = (nesCpu.pc - 1) shl 8
    # save the return address by pushing it onto the
    # stack. since it is divided in two parts, we must
    # perform two writings
    pushOnStackRegister(lowByte)
    pushOnStackRegister(highByte)
    # push also status register on the stack
    var status = nesCpu.c + nesCpu.z + nesCpu.i +
        nesCpu.d + nesCpu.v + nesCpu.n + nesCpu.b
    pushOnStackRegister(status)
    # enable break command
    nesCpu.b = 1
    # set program counter specified at
    # IRQ vector ($FFFE)
    nesCpu.pc = getMemoryShortAt(VECTOR_IRQ)

proc opCld(vByte: int): void =
    # clear decimal flag
    nesCpu.d = 0

proc opSei(vByte: int): void =
    # set interrupt flag
    nesCpu.i = 1

proc opCli(vByte: int): void =
    # clear interrupt flag
    nesCpu.i = 0

proc opClc(vByte: int): void =
    # clear carry flag
    nesCpu.c = 0

proc opClv(vByte: int): void =
    # clear overflow flag
    nesCpu.v = 0

proc opNop(vByte: int): void =
    # does nothing
    return

proc opLda(vByte: int): void =
    # store pure value or value located at specified
    # memory address into A register
    if vByte < 0x100 and nesCpu.zeropage == true:
        nesCpu.a = vByte
    else:
        nesCpu.a = mmioRead(vByte)
    # set zero flag as appropriate
    if nesCpu.a == 0: 
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.a and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opLdx(vByte: int): void =
    # store pure value or value located at specified
    # memory address into A register
    if vByte < 0x100:
        nesCpu.x = vByte
    else:
        nesCpu.x = mmioRead(vByte)
    # set zero flag as appropriate
    if nesCpu.x == 0: 
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.x and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opLdy(vByte: int): void =
    # store pure value or value located at specified
    # memory address into Y register
    if vByte < 0x100:
        nesCpu.y = vByte
    else:
        nesCpu.y = mmioRead(vByte)
    # set zero flag as appropriate
    if nesCpu.y == 0: 
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.y and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opSta(vByte: int): void =
    # store A register value into memory
    mmioWrite(vByte, nesCpu.a)

proc opStx(vByte: int): void =
    # store X register value into memory
    mmioWrite(vByte, nesCpu.x)

proc opSty(vByte: int): void =
    # store Y register value into memory
    mmioWrite(vByte, nesCpu.y)

proc opTax(vByte: int): void =
    # copy the content of Accumulator to X register
    nesCpu.x = nesCpu.a
    # set zero flag as appropriate
    if nesCpu.x == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.x and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opTay(vByte: int): void =
    # copy the content of Accumulator to Y register
    nesCpu.y = nesCpu.a
    # set zero flag as appropriate
    if nesCpu.y == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.y and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opTsx(vByte: int): void =
    # pull the value from the stack pointer location
    # pointed by S register and copy it to X register
    nesCpu.x = pullFromStackRegister()

proc opTxs(vByte: int): void =
    # add X register value on top of the stack pointer
    pushOnStackRegister(nesCpu.x)

proc opTxa(vByte: int): void =
    # copy X register value into A register
    nesCpu.a = nesCpu.x
    # set zero flag as appropriate
    if nesCpu.a == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.a and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opAdc(vByte: int): void =
    echo "ADC"
    # var unsigned = mmioRead(vByte)
    # nesCpu.a += unsigned + nesCpu.c

proc opDec(vByte: int): void =
    var value = mmioRead(vByte) - 1
    mmioWrite(vByte, value)
    # set zero flag as appropriate
    if value == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (value and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opDex(vByte: int): void =
    # decrements X register value by one
    nesCpu.x -= 1
    # set zero flag as appropriate
    if nesCpu.x == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.x and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opDey(vByte: int): void =
    # decrements Y register value by one
    nesCpu.y -= 1
    # set zero flag as appropriate
    if nesCpu.y == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.y and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opBcc(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.c == 0:
        nesCpu.pc += unsigned

proc opBcs(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.c != 0:
        nesCpu.pc += unsigned

proc opBeq(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.z != 0:
        nesCpu.pc += unsigned

proc opBmi(vByte: int): void =
    # if negative flag is set add target value to the
    # program counter
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.n != 0:
        nesCpu.pc += unsigned

proc opBne(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.z == 0:
        nesCpu.pc += unsigned

proc opBpl(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.n == 0:
        nesCpu.pc += unsigned    

proc opBvc(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.v == 0:
        nesCpu.pc += unsigned

proc opBvs(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    if nesCpu.v != 0:
        nesCpu.pc += unsigned

proc opJmp(vByte: int): void =
    #jump to the target address
    nes_cpu.pc = vByte

proc opJsr(vByte: int): void =
    # remember: a memory location can't hold
    # more than 8 bits, so we must divide the 16-bits
    # absolute address in two parts
    var lowByte = (nesCpu.pc - 1) and 0xFF
    var highByte = (nesCpu.pc - 1) shl 8
    # save the return address by pushing it onto the
    # stack. since it is divided in two parts, we must
    # perform two writings
    pushOnStackRegister(lowByte)
    pushOnStackRegister(highByte)
    # jump to the target address
    nesCpu.pc = vByte

proc opCpx(vByte: int): void =
    # compare accumulator content with value
    # or memory content
    # set carry flag as appropriate
    if nesCpu.x >= vByte:
        nesCpu.c = 1
    else: 
        nesCpu.c = 0

    # set zero flag as appropriate
    if nesCpu.x == vByte:
        nesCpu.z = 1
    else:
        nesCpu.z = 0

    # set negative flag as appropriate
    if (nesCpu.x and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opCpy(vByte: int): void =
    # compare accumulator content with value
    # or memory content
    # set carry flag as appropriate
    if nesCpu.y >= vByte:
        nesCpu.c = 1
    else: 
        nesCpu.c = 0
    # set zero flag as appropriate
    if nesCpu.y == vByte:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.y and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opSec(vByte: int): void =
    # set carry flag
    nesCpu.c = 1

proc opSed(vByte: int): void =
    # set decimal flag
    nesCpu.d = 1

proc opTya(vByte: int): void =
    # copies the content of Y register to A register
    nesCpu.a = nesCpu.y
    # set zero flag as appropriate
    if nesCpu.a == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.a and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opCmp(vByte: int): void =
    # compare accumulator content with value
    # or memory content
    # set carry flag as appropriate
    if nesCpu.a >= vByte:
        nesCpu.c = 1
    else: 
        nesCpu.c = 0
    # set zero flag as appropriate
    if nesCpu.a == vByte:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.a and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opPha(vByte: int): void =
    # push accumulator content on stack
    pushOnStackRegister(nesCpu.a)

proc opPhp(vByte: int): void =
    # push status register value on stack
    var status = nesCpu.c + nesCpu.z + nesCpu.i +
        nesCpu.d + nesCpu.v + nesCpu.n + nesCpu.b
    pushOnStackRegister(status)

proc opPla(vByte: int): void =
    # pull 8-bit value from stack
    nesCpu.a = pullFromStackRegister()
    # set zero flag as appropriate
    if nesCpu.a == 0:
        nesCpu.z = 1
    else:
        nesCpu.z = 0
    # set negative flag as appropriate
    if (nesCpu.a and 0x80) == 0x80:
        nesCpu.n = 1
    else:
        nesCpu.n = 0

proc opPlp(vByte: int): void =
    # pull 8-bit value from stack and store it
    # as the new status register value
    var value = mmioRead(nesCpu.s)
    nesCpu.c = value and 1
    nesCpu.z = (value shr 1) and 1
    nesCpu.i = (value shr 2) and 1
    nesCpu.d = (value shr 3) and 1
    nesCpu.v = (value shr 6) and 1
    nesCpu.n = (value shr 7) and 1

#TODO
proc opRti(vByte: int): void =
    echo "RTI"

#TODO
proc opRts(vByte: int): void =
    echo "RTS"

#TODO
proc opInc(vByte: int): void =
    echo "INC"

#TODO
proc opInx(vByte: int): void =
    echo "INX"

#TODO
proc opIny(vByte: int): void =
    echo "INY"

#TODO
proc opSbc(vByte: int): void =
    echo "SBC"

#TODO
proc opAsl(vByte: int): void =
    echo "ASL"

#TODO
proc opBit(vByte: int): void =
    echo "BIT"

#TODO
proc opEor(vByte: int): void =
    echo "EOR"

#TODO
proc opLsr(vByte: int): void =
    echo "LSR"

#TODO
proc opOra(vByte: int): void =
    echo "ORA"

#TODO
proc opRol(vByte: int): void =
    echo "ROL"

#TODO
proc opRor(vByte: int): void =
    echo "ROR"

#TODO
proc opAnd(vByte: int): void =
    echo "AND"

#################################################
#            6502 MOS ADDRESSING MODES          #
#################################################

proc zeropage(): int {.discardable.} =
    # notify zero page addressing to the CPU
    # so it can write to a memory location that is
    # less than 8-bit
    nesCpu.zeropage = true
    # return the next byte after current byte
    result = mmioRead(nesCpu.pc + 1)
    nes_cpu.pc += 2

proc zeropageIndexedX(): int {.discardable.} =
    # see zeropage proc above
    nesCpu.zeropage = true
    # only treats 8-bit values so can't go above $FF
    var address : int8
    address = getMemoryShortAt(nesCpu.pc + 1).toU8
    address += nesCpu.x.toU8
    result = address.toU32

proc zeropageIndexedY(): int {.discardable.} =
    # see zeropage proc above
    nesCpu.zeropage = true
    # only treats 8-bit values so can't go above $FF
    var address : int8
    address = getMemoryShortAt(nesCpu.pc + 1).toU8
    address += nesCpu.y.toU8
    result = address.toU32

proc absolute(): int {.discardable.} =
    # return the two next bytes after current byte
    # we must revert them, get_memory_short_at does the work
    result = getMemoryShortAt(nesCpu.pc + 1)
    nesCpu.pc += 3

proc absoluteIndexedX(): int {.discardable.} =
    var address = getMemoryShortAt(nesCpu.pc + 1)
    result = address + nesCpu.x
    nesCpu.pc += 3

proc absoluteIndexedY(): int {.discardable.} =
    var address = getMemoryShortAt(nesCpu.pc + 1)
    result = address + nesCpu.y
    nesCpu.pc += 3

proc indirect(): int {.discardable.} =
    result = getMemoryShortAt(nesCpu.pc + 1)
    nesCpu.pc += 3

proc indirectIndexedX(): int {.discardable.} =
    var address = mmioRead(nesCpu.pc + 1)
    result = address + nesCpu.x
    nesCpu.pc += 2

proc indirectIndexedY(): int {.discardable.} =
    var address = mmioRead(nesCpu.pc + 1)
    result = address + nesCpu.y
    nesCpu.pc += 2

proc implicit(): int {.discardable.} =
    # this addressing mode does not return any value
    result = 0
    nesCpu.pc += 1   

#TODO
proc accumulator(): int {.discardable.} =
    echo "accumulator"

proc relative(): int {.discardable.} =
    # return the next byte after the current byte
    result = mmioRead(nesCpu.pc + 1)
    nesCpu.pc += 2

proc immediate(): int {.discardable.} =
    # return the next 8-bit value 
    result = mmioRead(nesCpu.pc + 1)
    nesCpu.pc += 2

#################################################
#                    TABLES                     #
#################################################

let 
    opcodesDispatcher =
        {"LDA":opLda, "LDX":opLdx, "LDY":opLdy, "STA":opSta, 
         "STY":opSty, "TAX":opTax, "TAY":opTay, "TSX":opTsx,
         "ADC":opAdc, "DEC":opDec, "DEX":opDex, "DEY":opDey, 
         "INC":opInc, "INX":opInx, "INY":opIny, "SBC":opSbc, 
         "BRK":opBrk, "ASL":opAsl, "BIT":opBit, "EOR":opEor,
         "LSR":opLsr, "ORA":opOra, "ROL":opRol, "ROR":opRor, 
         "BCC":opBcc, "BCS":opBcs, "BEQ":opBeq, "BMI":opBmi, 
         "BNE":opBne, "BPL":opBpl, "BVC":opBvc, "BVS":opBvs,
         "JMP":opJmp, "JSR":opJsr, "RTI":opRti, "RTS":opRts, 
         "CLC":opClc, "CLD":opCld, "CLI":opCli, "CLV":opClv,
         "CPX":opCpx, "CPY":opCpy, "SEC":opSec, "SED":opSed, 
         "PHA":opPha, "PHP":opPhp, "PLA":opPla, "PLP":opPlp,
         "STX":opStx, "TYA":opTya, "CMP":opCmp, "SEI":opSei, 
         "TXS":opTxs, "NOP":opNop, "AND":opAnd, "TXA":opTxa}.toTable

    addrModesDispatcher =
        {"/**":zeropage, "*/*":zeropageIndexedX, "**/":zeropageIndexedY,
         "@**":absolute, "*@*":absoluteIndexedX, "**@":absoluteIndexedY,
         "~**":indirect, "*~*":indirectIndexedX, "**~":indirectIndexedY,
         "~/@":implicit, "@/~":accumulator, "@~/":relative, "***":immediate}.toTable
         
    opcodesTable = 
        @["BRK", "ORA", "???", "???", "???", "ORA", "ASL", "???", # 00-07
          "PHP", "ORA", "ASL", "???", "???", "ORA", "ASL", "???", # 08-0F
          "BPL", "ORA", "???", "???", "???", "ORA", "ASL", "???", # 10-17
          "CLC", "ORA", "???", "???", "???", "ORA", "ASL", "???", # 18-1F
          "JSR", "AND", "???", "???", "BIT", "AND", "ROL", "???", # 20-27
          "PLP", "AND", "ROL", "???", "BIT", "AND", "ROL", "???", # 28-2F
          "BMI", "AND", "???", "???", "???", "AND", "ROL", "???", # 30-37
          "SEC", "AND", "???", "???", "???", "AND", "ROL", "???", # 38-3F
          "RTI", "EOR", "???", "???", "???", "EOR", "LSR", "???", # 40-47
          "PHA", "EOR", "LSR", "???", "JMP", "EOR", "LSR", "???", # 48-4F
          "BVC", "EOR", "???", "???", "???", "EOR", "LSR", "???", # 50-57
          "CLI", "EOR", "???", "???", "???", "EOR", "LSR", "???", # 58-5F
          "RTS", "ADC", "???", "???", "???", "ADC", "ROR", "???", # 60-67
          "PLA", "ADC", "ROR", "???", "JMP", "ADC", "ROR", "???", # 68-6F
          "BVS", "ADC", "???", "???", "???", "ADC", "ROR", "???", # 70-77
          "SEI", "ADC", "???", "???", "???", "ADC", "ROR", "???", # 78-7F
          "???", "STA", "???", "???", "STY", "STA", "STX", "???", # 80-87
          "DEY", "???", "TXA", "???", "STY", "STA", "STX", "???", # 88-8F
          "BCC", "STA", "???", "???", "STY", "STA", "STX", "???", # 90-97
          "TYA", "STA", "TXS", "???", "???", "STA", "???", "???", # 98-9F
          "LDY", "LDA", "LDX", "???", "LDY", "LDA", "LDX", "???", # A0-A7
          "TAY", "LDA", "TAX", "???", "LDY", "LDA", "LDX", "???", # A8-AF
          "BCS", "LDA", "???", "???", "LDY", "LDA", "LDX", "???", # B0-B7
          "CLV", "LDA", "TSX", "???", "LDY", "LDA", "LDX", "???", # B8-BF
          "CPY", "CMP", "???", "???", "CPY", "CMP", "DEC", "???", # C0-C7
          "INY", "CMP", "DEX", "???", "CPY", "CMP", "DEC", "???", # C8-CF
          "BNE", "CMP", "???", "???", "???", "CMP", "DEC", "???", # D0-D7
          "CLD", "CMP", "???", "???", "???", "CMP", "DEC", "???", # D8-DF
          "CPX", "SBC", "???", "???", "CPX", "SBC", "INC", "???", # E0-07
          "INX", "SBC", "NOP", "???", "CPX", "SBC", "INC", "???", # E8-EF
          "BEQ", "SBC", "???", "???", "???", "SBC", "INC", "???", # F0-F7
          "SED", "SBC", "???", "???", "???", "SBC", "INC", "???"] # F8-FF
    # addressing modes
    # /** (zero-page), */* (zero-page X), **/ (zero-page Y)
    # @** (absolute), *@* (absolute X), **@ (absolute Y)
    # ~** (indirect), *~* (indirect X), **~ (indirect Y)
    # @/~ (accumulator), @~/ (relative), ~/@ (implicit), ***(immediate) 
    addrModes = 
        @["~/@", "*~*", "???", "???", "???", "/**", "/**", "???", #00-07
          "~/@", "~/@", "@/~", "???", "???", "@**", "@**", "???", #08-0F
          "@~/", "**~", "???", "???", "???", "*/*", "*/*", "???", #10-17
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #18-1F
          "@**", "*~*", "???", "???", "/**", "/**", "/**", "???", #20-27
          "~/@", "***", "@/~", "???", "@**", "@**", "@**", "???", #28-2F
          "~/@", "**~", "???", "???", "???", "*/*", "*/*", "???", #30-37
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #38-3F
          "~/@", "*~*", "???", "???", "???", "/**", "/**", "???", #40-47
          "~/@", "***", "@/~", "???", "@**", "@**", "@**", "???", #48-4F
          "~/@", "**~", "???", "???", "???", "*/*", "*/*", "???", #50-57
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #58-5F
          "~/@", "*~*", "???", "???", "???", "/**", "/**", "???", #60-67
          "~/@", "***", "@/~", "???", "~**", "@**", "@**", "???", #68-6F
          "~/@", "**~", "???", "???", "???", "*/*", "*/*", "???", #70-77
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #78-7F
          "???", "*~*", "???", "???", "/**", "/**", "/**", "???", #80-87
          "~/@", "???", "~/@", "???", "@**", "@**", "@**", "???", #88-8F
          "~/@", "**~", "???", "???", "*/*", "*/*", "**/", "???", #90-97
          "~/@", "**@", "~/@", "???", "???", "*@*", "???", "???", #98-9F
          "***", "*~*", "***", "???", "/**", "/**", "/**", "???", #A0-A7
          "~/@", "***", "~/@", "???", "@**", "@**", "@**", "???", #A8-AF
          "@~/", "**~", "???", "???", "*/*", "*/*", "**/", "???", #B0-B7
          "~/@", "**@", "~/@", "???", "*@*", "*@*", "**@", "???", #B8-BF
          "***", "*~*", "???", "???", "/**", "/**", "/**", "???", #C0-C7
          "~/@", "***", "~/@", "???", "@**", "@**", "@**", "???", #C8-CF
          "~/@", "**~", "???", "???", "???", "*/*", "*/*", "???", #D0-D7
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #D8-DF
          "***", "*~*", "???", "???", "/**", "/**", "/**", "???", #E0-07
          "~/@", "***", "~/@", "???", "@**", "@**", "@**", "???", #E8-EF
          "~/@", "**~", "???", "???", "???", "*/*", "*/*", "???", #F0-F7    
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???"] #F8-FF

    cyclesTable = 
        @[7, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 0, 5, 6, 0,
          2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
          6, 6, 0, 0, 3, 3, 5, 0, 4, 2, 2, 0, 4, 4, 6, 0,
          2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
          6, 6, 0, 0, 0, 3, 5, 0, 3, 2, 2, 0, 3, 4, 6, 0,
          2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
          6, 6, 0, 0, 0, 3, 5, 0, 4, 2, 2, 0, 5, 4, 6, 0,
          2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
          0, 6, 0, 0, 3, 3, 3, 0, 2, 0, 2, 0, 4, 4, 4, 0,
          2, 6, 0, 0, 4, 4, 4, 0, 2, 5, 2, 0, 0, 5, 0, 0,
          2, 6, 2, 0, 3, 3, 3, 0, 2, 2, 2, 0, 4, 4, 4, 0,
          2, 5, 0, 0, 4, 4, 4, 0, 2, 4, 2, 0, 4, 4, 4, 0,
          2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
          2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0,
          2, 6, 0, 0, 3, 3, 5, 0, 2, 2, 2, 0, 4, 4, 6, 0,
          2, 5, 0, 0, 0, 4, 6, 0, 2, 4, 0, 0, 0, 4, 7, 0]

proc initCpu*(): void =
    # the stack pointer size is 256 bytes
    # it is accessible between $0100 & $01FF memory location
    # S register always points towards the next free location
    nesCpu.s = 0x1FD
    # start at reset vector (defined in the rom program)
    nesCpu.pc = getMemoryShortAt(VECTOR_RESET)
    # disable zero page mode
    nesCpu.zeropage = false

proc update*(cpuCycles, divisor: int): void =
    var cycles = (cpuCycles/divisor).toInt

    while cycles > 0:
        # fetch opcode from memory
        var opcode = mmioRead(nesCpu.pc)
        # use opcode to retrieve addressing mode & matching instruction
        var operation = opcodesTable[opcode]
        var mode = addrModes[opcode]  
        # use tables to make function calls
        var fetchedByte = addrModesDispatcher[mode]()
        opcodesDispatcher[operation](fetchedByte)
        nesCpu.opcodeCycles += cyclesTable[opcode]
        # reset zeropage hander
        nesCpu.zeropage = false
        # needed for cpu/ppu sync
        cycles -= cyclesTable[opcode]
        # debugger for step by step execution
        if DEBUGGER_ENABLED == true :
            nesCpu.debug(operation, mode)
        if cycles <= 0 :
            echo "cpu phase terminated"
