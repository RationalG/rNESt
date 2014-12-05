import nes, cpu, rom

const 
    # cpu memory map sections sizes
    WRAM_SIZE = 0x800
    SRAM_SIZE = 0x2000
    PROG_SIZE = 0x8000
    PPUREGS_SIZE = 0x0008
    APUREGS_SIZE = 0x0020
    
    # access points of internal cpu
    # can be used also as offsets for memory access
    WRAM_ADDRESS = 0x0000
    SRAM_ADDRESS = 0x6000
    PROG_ADDRESS = 0x8000
    
    # ppu registers
    PPUCTRL_ADDRESS = 0x2000
    PPUMASK_ADDRESS = 0x2001
    PPUSTATUS_ADDRESS = 0x2002
    OAMADDR_ADDRESS = 0x2003
    OAMDATA_ADDRESS = 0x2004
    PPUSCROLL_ADDRESS = 0x2005
    PPUADDR_ADDRESS = 0x2006
    PPUDATA_ADDRESS = 0x2007
    
    # apu registers
    APUREGS_ADDRESS = 0x4000
    
type
    PCPUMEM* = ref TCPUMEM 
    TCPUMEM* = object of TObject
        wram: seq[int]
        sram: seq[int]
        prog: seq[int]
        ppuRegisters: seq[int]
        apuRegisters: seq[int]

var cpuMemory* : PCPUMEM

proc setProgram*(bank: pointer): void =
    var temporaryBank = newSeq[char](PROG_SIZE)
    copyMem(addr(temporaryBank[0]), bank, PROG_SIZE)
    for i, value in temporaryBank:
        cpuMemory.prog[i] = cast[int](value)

proc initializeMemory*(): void = 
    new(cpuMemory)
    cpuMemory.wram = newSeq[int](WRAM_SIZE)
    cpuMemory.sram = newSeq[int](SRAM_SIZE)
    cpuMemory.prog = newSeq[int](PROG_SIZE)
    cpuMemory.ppuRegisters = newSeq[int](PPUREGS_SIZE)
    setProgram(addr(nesRom.prgBytes[0]))

proc setMemoryValueAt*(address, value: int): void =
    case address:
        of WRAM_ADDRESS..WRAM_SIZE - 1:
            cpuMemory.wram[address] = value
        of PPUCTRL_ADDRESS..PPUDATA_ADDRESS:
            cpuMemory.ppuRegisters[address - PPUCTRL_ADDRESS] = value
        of SRAM_ADDRESS..PROG_ADDRESS - 1:
            cpuMemory.sram[address - SRAM_ADDRESS] = value
        of PROG_ADDRESS..0xFFFF:        
            cpuMemory.prog[address - PROG_ADDRESS] = value
        else:
            echo "Invalid address"
            return

proc getMemoryShortAt*(address: int): int =
    var lowByte = cpuMemory.prog[address - PROG_ADDRESS]
    var highByte = cpuMemory.prog[address + 1 - PROG_ADDRESS] shl 8
    return highByte or lowByte

proc getMemoryAddressAt*(address: int): pointer =
    return addr(cpuMemory.prog[address - PROG_ADDRESS])
 
proc getMemoryByteAt*(address: int): int =
    case address:
        of WRAM_ADDRESS..WRAM_SIZE - 1:
            return cpuMemory.wram[address]
        of PPUCTRL_ADDRESS..PPUDATA_ADDRESS:
            return cpuMemory.ppuRegisters[address - PPUCTRL_ADDRESS]
        of SRAM_ADDRESS..PROG_ADDRESS - 1:
            return cpuMemory.sram[address - SRAM_ADDRESS]
        of PROG_ADDRESS..0xFFFF:        
            return cpuMemory.prog[address - PROG_ADDRESS]
        else:
            return 0