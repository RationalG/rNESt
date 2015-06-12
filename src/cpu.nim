import strutils, macros, queues, tables
import mem, debug

type
    CPUObj* = object of RootObj
        a, x, y, s, pc, ps: int      
        procCycles, signal : int
        addrAcc, addrImm : bool

const
    NMI_SIGNAL = 0x0A04
    IRQ_SIGNAL = 0x0A05
    VECTOR_NMI = 0xFFFA
    VECTOR_IRQ = 0xFFFE
    VECTOR_RST = 0xFFFC
    DEBUGGER_ENABLED = true

var nesCpu* : CPUObj

proc pushOnStackRegister(value: int): void =
    mmioWrite(nesCpu.s, value)
    nesCpu.s -= 1

proc pullFromStackRegister(): int =
    result = mmioRead(nesCpu.s + 1)
    mmioWrite(nesCpu.s + 1, 0)
    nesCpu.s += 1

proc storeReturnAddress(address: int, minus = 0): void =
    var lowByte = (address) and 0xFF
    var highByte = (address) shr 8
    pushOnStackRegister(lowByte - minus)
    pushOnStackRegister(highByte)

proc interruptNMI(): void =
    storeReturnAddress(nesCpu.pc)
    nesCpu.pc = getMemoryShortAt(VECTOR_NMI)

proc interruptIRQ(): void =
    storeReturnAddress(nesCpu.pc)
    nesCpu.pc = getMemoryShortAt(VECTOR_IRQ)

proc interruptReset(): void =
    nesCpu.pc = getMemoryShortAt(VECTOR_RST)

proc handleSignal(signal: int): void =
    case signal:
        of NMI_SIGNAL: 
            interruptNMI()
        of IRQ_SIGNAL: 
            interruptIRQ()
        else: 
            return

proc evaluateZero(value: int): void =
    if value == 0:
        nesCpu.ps = nesCpu.ps or (1 shl 1)
    else:
        nesCpu.ps = nesCpu.ps and not (1 shl 1)

proc evaluateNegative(value: int): void = 
    if (value and 0x80) == 0x80:
        nesCpu.ps = nesCpu.ps or (1 shl 7)
    else:
        nesCpu.ps = nesCpu.ps and not (1 shl 7)

proc evaluateCarry(value: int): void =
    if (value and 0x100) == 0x80:
        nesCpu.ps = nesCpu.ps or (1 shl 0)
    else:
        nesCpu.ps = nesCpu.ps and not (1 shl 0)

proc evaluateOverflow(regValue, memValue, sum: int): void =
    if ((not(regValue xor memValue)) and (nesCpu.a xor sum) and 0x80) == 0x80:
        nesCpu.ps = nesCpu.ps or (1 shl 6)
    else:
        nesCpu.ps = nesCpu.ps and not (1 shl 7)


proc opBrk(vByte: int): void =
    storeReturnAddress(nesCpu.pc - 1)
    pushOnStackRegister(nesCpu.ps)
    nesCpu.ps = nesCpu.ps or (1 shl 4)
    nesCpu.pc = getMemoryShortAt(VECTOR_IRQ)

proc opSec(vByte: int): void =
    nesCpu.ps = nesCpu.ps or (1 shl 0)

proc opSed(vByte: int): void =
    nesCpu.ps = nesCpu.ps or (1 shl 3)

proc opCld(vByte: int): void =
    nesCpu.ps = nesCpu.ps and not (1 shl 3)

proc opSei(vByte: int): void =
    nesCpu.ps = nesCpu.ps or (1 shl 2)

proc opCli(vByte: int): void =
    nesCpu.ps = nesCpu.ps and not (1 shl 2)

proc opClc(vByte: int): void =
    nesCpu.ps = nesCpu.ps and not (1 shl 0)

proc opClv(vByte: int): void =
    nesCpu.ps = nesCpu.ps and not (1 shl 6)

proc opNop(vByte: int): void =
    return

proc opLda(vByte: int): void =
    if nesCpu.addrImm:   
        nesCpu.a = vByte
    else:
        nesCpu.a = mmioRead(vByte)

    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opLdx(vByte: int): void =
    if nesCpu.addrImm:   
        nesCpu.x = vByte
    else:
        nesCpu.x = mmioRead(vByte)

    evaluateZero(nesCpu.x)
    evaluateNegative(nesCpu.x)

proc opLdy(vByte: int): void =
    if nesCpu.addrImm:   
        nesCpu.y = vByte
    else:
        nesCpu.y = mmioRead(vByte)

    evaluateZero(nesCpu.y)
    evaluateNegative(nesCpu.y)

proc opSta(vByte: int): void =
    mmioWrite(vByte, nesCpu.a)

proc opStx(vByte: int): void =
    mmioWrite(vByte, nesCpu.x)

proc opSty(vByte: int): void =
    mmioWrite(vByte, nesCpu.y)

proc opTax(vByte: int): void =
    nesCpu.x = nesCpu.a
    evaluateZero(nesCpu.x)
    evaluateNegative(nesCpu.x)

proc opTay(vByte: int): void =
    nesCpu.y = nesCpu.a
    evaluateZero(nesCpu.y)
    evaluateNegative(nesCpu.y)

proc opTsx(vByte: int): void =
    nesCpu.x = pullFromStackRegister()

proc opTxs(vByte: int): void =
    pushOnStackRegister(nesCpu.x)

proc opTxa(vByte: int): void =
    nesCpu.a = nesCpu.x
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opDec(vByte: int): void =
    var value = mmioRead(vByte) - 1
    mmioWrite(vByte, value)
    evaluateZero(value)
    evaluateNegative(value)

proc opDex(vByte: int): void =
    nesCpu.x -= 1
    evaluateZero(nesCpu.x)   
    evaluateNegative(nesCpu.x)

proc opDey(vByte: int): void =
    nesCpu.y -= 1
    evaluateZero(nesCpu.y)
    evaluateNegative(nesCpu.y)

proc opBcc(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 0) and 1
    if bitValue == 0:
        nesCpu.pc += unsigned

proc opBcs(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 0) and 1
    if bitValue != 0:
        nesCpu.pc += unsigned

proc opBeq(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 1) and 1
    if bitValue != 0:
        nesCpu.pc += unsigned

proc opBmi(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 7) and 1
    if bitValue != 0:
        nesCpu.pc += unsigned

proc opBne(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 1) and 1
    if bitValue == 0:
        nesCpu.pc += unsigned

proc opBpl(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 7) and 1
    if bitValue == 0:
        nesCpu.pc += unsigned    

proc opBvc(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 6) and 1
    if bitValue == 0:
        nesCpu.pc += unsigned

proc opBvs(vByte: int): void =
    var unsigned : int8 = cast[int8](vByte)
    var bitValue = (nesCpu.ps shr 6) and 1
    if bitValue != 0:
        nesCpu.pc += unsigned

proc opJmp(vByte: int): void =
    nes_cpu.pc = vByte

proc opJsr(vByte: int): void =
    storeReturnAddress(nesCpu.pc - 1, 1)
    nesCpu.pc = vByte

proc opCpx(vByte: int): void =
    if nesCpu.x >= vByte:
        nesCpu.ps = nesCpu.ps or (1 shl 1)
    else: 
        nesCpu.ps = nesCpu.ps and not (1 shl 1)

    evaluateZero(nesCpu.x)
    evaluateNegative(nesCpu.x)

proc opCpy(vByte: int): void =
    if nesCpu.y >= vByte:
        nesCpu.ps = nesCpu.ps or (1 shl 1)
    else: 
        nesCpu.ps = nesCpu.ps and not (1 shl 1)

    evaluateZero(nesCpu.y)
    evaluateNegative(nesCpu.y)

proc opTya(vByte: int): void =
    nesCpu.a = nesCpu.y
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opCmp(vByte: int): void =
    if nesCpu.a >= vByte:
        nesCpu.ps = nesCpu.ps or (1 shl 1)
    else: 
        nesCpu.ps = nesCpu.ps and not (1 shl 1)

    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opPha(vByte: int): void =
    pushOnStackRegister(nesCpu.a)

proc opPhp(vByte: int): void =
    pushOnStackRegister(nesCpu.ps)

proc opPla(vByte: int): void =
    nesCpu.a = pullFromStackRegister().toU8
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opPlp(vByte: int): void =
    nesCpu.ps = mmioRead(nesCpu.s)
    
proc opRti(vByte: int): void =
    nesCpu.ps = pullFromStackRegister()
    var highByte = pullFromStackRegister()
    var lowByte = pullFromStackRegister() - 1
    nesCpu.pc = (highByte shl 8) or lowByte

proc opRts(vByte: int): void =
    var highByte = pullFromStackRegister()
    var lowByte = pullFromStackRegister() - 1
    nesCpu.pc = (highByte shl 8) or lowByte
    nesCpu.pc += 3

proc opInc(vByte: int): void =
    var value = mmioRead(vByte) + 1
    mmioWrite(vByte, value)
    evaluateZero(value)
    evaluateNegative(value)

proc opInx(vByte: int): void =
    nesCpu.x += 1
    evaluateZero(nesCpu.x)
    evaluateNegative(nesCpu.x)

proc opIny(vByte: int): void =
    nesCpu.y += 1
    evaluateZero(nesCpu.y)
    evaluateNegative(nesCpu.y)

proc opBit(vByte: int): void =
    var value = mmioRead(vByte)
    var mask = nesCpu.a and value
    evaluateZero(mask)
    var nBit = (value shr 6) and 1
    var oBit = (value shr 7) and 1
    nesCpu.ps = nesCpu.ps xor (-nBit xor nesCpu.ps) and (1 shl 6)
    nesCpu.ps = nesCpu.ps xor (-oBit xor nesCpu.ps) and (1 shl 7)

proc opAsl(vByte: int): void =
    var flagTrigger : int

    if nesCpu.addrAcc:
        var carry = (nesCpu.a shr 7) and 1
        nesCpu.ps = nesCpu.ps xor (-carry xor nesCpu.ps) and (1 shl 0)
        nesCpu.a = nesCpu.a shl 1
        nesCpu.a = nesCpu.a or (1 shl 0)
        flagTrigger = nesCpu.a
    else:
        var value = mmioRead(vByte)
        var carry = (value shr 7) and 1
        nesCpu.ps = nesCpu.ps xor (-carry xor nesCpu.ps) and (1 shl 0)
        value = value shl 1
        value = value or (1 shl 0)
        flagTrigger = value

    evaluateZero(flagTrigger)
    evaluateNegative(flagTrigger)
    
proc opEor(vByte: int): void =
    var value = mmioRead(vByte)
    nesCpu.a = nesCpu.a xor value
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opOra(vByte: int): void =
    var value = mmioRead(vByte)
    nesCpu.a = nesCpu.a or value
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opAnd(vByte: int): void =
    var value = mmioRead(vByte)
    nesCpu.a = nesCpu.a and value
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opSbc(vByte: int): void =
    var value = mmioRead(vByte)
    var carry = (nesCpu.ps shr 0) and 1
    var temp = nesCpu.a - value - (1 - carry)
    evaluateCarry(temp)
    evaluateOverflow(nesCpu.a, value, temp)
    nesCpu.a = temp and 0xFF   
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opAdc(vByte: int): void =
    var value = mmioRead(vByte)
    var carry = (nesCpu.ps shr 0) and 1
    var temp = nesCpu.a + value + carry
    evaluateCarry(temp)
    evaluateOverflow(nesCpu.a, value, temp)
    nesCpu.a = temp and 0xFF   
    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc opRol(vByte: int): void =
    var temp, carry, oldBit, result : int

    if nesCpu.addrAcc:
        oldBit = (nesCpu.a shr 7) and 1
        temp = nesCpu.a shl 1 
        carry = (nesCpu.ps shl 0) and 1
        temp = temp xor (-carry xor temp) and (1 shl 0)
        nesCpu.ps = nesCpu.ps xor ((-oldBit xor nesCpu.ps) and (1 shl 0))
        nesCpu.a = temp and 0xFF
        result = nesCpu.a
    else:
        var value = mmioRead(vByte)
        oldBit = (value shr 7) and 1
        temp = value shl 1 
        carry = (nesCpu.ps shl 0) and 1
        temp = temp xor (-carry xor temp) and (1 shl 0)
        nesCpu.ps = nesCpu.ps xor ((-oldBit xor nesCpu.ps) and (1 shl 0))
        value = temp and 0xFF
        mmioWrite(vByte, value)
        result = value

    evaluateZero(result)
    evaluateNegative(result)


proc opRor(vByte: int): void =
    var temp, oldBit, result, carry : int

    if nesCpu.addrAcc:
        oldBit = (nesCpu.a shr 0) and 1
        temp = nesCpu.a shr 1 
        carry = (nesCpu.ps shl 0) and 1
        temp = temp xor (-carry xor temp) and (1 shl 7)
        nesCpu.ps = nesCpu.ps xor ((-oldBit xor nesCpu.ps) and (1 shl 0))
        nesCpu.a = temp and 0xFF
        result = nesCpu.a
    else:
        var value = mmioRead(vByte)
        oldBit = (value shr 0) and 1
        temp = value shr 1 
        carry = (nesCpu.ps shl 0) and 1
        temp = temp xor (-carry xor temp) and (1 shl 7)
        nesCpu.ps = nesCpu.ps xor ((-oldBit xor nesCpu.ps) and (1 shl 0))
        value = temp and 0xFF
        mmioWrite(vByte, value)
        result = value

    evaluateZero(result)
    evaluateNegative(result)

proc opLsr(vByte: int): void =
    var carry : int
    if nesCpu.addrAcc:
        carry = nesCpu.a and 1
        nesCpu.ps = nesCpu.ps xor ((-carry xor nesCpu.ps) and (1 shl 0))
        nesCpu.a = nesCpu.a shr 1
        nesCpu.a = nesCpu.a and 0xFF
    else:
        var value = mmioRead(vByte)
        carry = value and 1
        nesCpu.ps = nesCpu.ps xor ((-carry xor nesCpu.ps) and (1 shl 0))
        nesCpu.a = value shr 1
        value = value and 0xFF
        mmioWrite(vByte, value)

    evaluateZero(nesCpu.a)
    evaluateNegative(nesCpu.a)

proc zeropage(): int {.discardable.} =
    result = mmioRead(nesCpu.pc + 1)
    nes_cpu.pc += 2

proc zeropageIndexedX(): int {.discardable.} =
    var address : int8
    address = getMemoryShortAt(nesCpu.pc + 1).toU8
    address += nesCpu.x.toU8
    result = address.toU32

proc zeropageIndexedY(): int {.discardable.} =
    var address : int8
    address = getMemoryShortAt(nesCpu.pc + 1).toU8
    address += nesCpu.y.toU8
    result = address.toU32

proc absolute(): int {.discardable.} =
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
    result = 0
    nesCpu.pc += 1   

proc accumulator(): int {.discardable.} =
    nesCpu.addrAcc = true
    result = 0
    nesCpu.pc += 1

proc relative(): int {.discardable.} =
    result = mmioRead(nesCpu.pc + 1)
    nesCpu.pc += 2

proc immediate(): int {.discardable.} =
    nesCpu.addrImm = true
    result = mmioRead(nesCpu.pc + 1)
    nesCpu.pc += 2

let 
    # 6502 MOS instructions set
    procsDispatcher =
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

    # 6502 MOS addressing modes
    addrModesDispatcher =
        {"/**":zeropage, "*/*":zeropageIndexedX, "**/":zeropageIndexedY,
         "@**":absolute, "*@*":absoluteIndexedX, "**@":absoluteIndexedY,
         "~**":indirect, "*~*":indirectIndexedX, "**~":indirectIndexedY,
         "~/@":implicit, "@/~":accumulator, "@~/":relative, "***":immediate}.toTable
    
    # is accessed by specifying an proc as index  
    instructionsTable = 
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
          "@~/", "**~", "???", "???", "???", "*/*", "*/*", "???", #30-37
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #38-3F
          "~/@", "*~*", "???", "???", "???", "/**", "/**", "???", #40-47
          "~/@", "***", "@/~", "???", "@**", "@**", "@**", "???", #48-4F
          "@~/", "**~", "???", "???", "???", "*/*", "*/*", "???", #50-57
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #58-5F
          "~/@", "*~*", "???", "???", "???", "/**", "/**", "???", #60-67
          "~/@", "***", "@/~", "???", "~**", "@**", "@**", "???", #68-6F
          "@~/", "**~", "???", "???", "???", "*/*", "*/*", "???", #70-77
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #78-7F
          "???", "*~*", "???", "???", "/**", "/**", "/**", "???", #80-87
          "~/@", "???", "~/@", "???", "@**", "@**", "@**", "???", #88-8F
          "@~/", "**~", "???", "???", "*/*", "*/*", "**/", "???", #90-97
          "~/@", "**@", "~/@", "???", "???", "*@*", "???", "???", #98-9F
          "***", "*~*", "***", "???", "/**", "/**", "/**", "???", #A0-A7
          "~/@", "***", "~/@", "???", "@**", "@**", "@**", "???", #A8-AF
          "@~/", "**~", "???", "???", "*/*", "*/*", "**/", "???", #B0-B7
          "~/@", "**@", "~/@", "???", "*@*", "*@*", "**@", "???", #B8-BF
          "***", "*~*", "???", "???", "/**", "/**", "/**", "???", #C0-C7
          "~/@", "***", "~/@", "???", "@**", "@**", "@**", "???", #C8-CF
          "@~/", "**~", "???", "???", "???", "*/*", "*/*", "???", #D0-D7
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???", #D8-DF
          "***", "*~*", "???", "???", "/**", "/**", "/**", "???", #E0-07
          "~/@", "***", "~/@", "???", "@**", "@**", "@**", "???", #E8-EF
          "@~/", "**~", "???", "???", "???", "*/*", "*/*", "???", #F0-F7    
          "~/@", "**@", "???", "???", "???", "*@*", "*@*", "???"] #F8-FF

    # instructions cycles consumption
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
    nesCpu.s = 0x1FD
    interruptReset()
    nesCpu.addrAcc = false
    nesCpu.addrImm = false

proc update*(cpuCycles, divisor: int): void =
    var cycles = (cpuCycles/divisor).toInt
    
    var signal = getNmiSignal()
    if signal != 0 : 
        handleSignal(signal)

    while cycles > 0:
        var opcode = mmioRead(nesCpu.pc)
        var operation = instructionsTable[opcode]
        var mode = addrModes[opcode]  
        var fetchedByte = addrModesDispatcher[mode]()
        procsDispatcher[operation](fetchedByte)
        nesCpu.procCycles += cyclesTable[opcode]
        nesCpu.addrAcc = false
        nesCpu.addrImm = false
        cycles -= cyclesTable[opcode]

        if DEBUGGER_ENABLED == true :
            var partialMem, partialStack : Queue[int]
            partialMem = initQueue[int]()
            partialStack = initQueue[int]()
            for i in 0..2:
                partialMem.add(mmioRead(nesCpu.pc - i))
                partialStack.add(mmioRead(nesCpu.s + i))
            nesCpu.debug(operation, mode, fetchedByte, partialMem, partialStack)
        if cycles <= 0 :
            echo "cpu phase terminated"