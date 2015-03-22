import ppu, debug, rom
    
type
    CPUMemoryRef* = ref CpuMemoryObj
    CPUMemoryObj* = object of RootObj
        bank: seq[int]

var cpuMemory* : CPUMemoryRef

# load the NES program into memory
# if program's size fits in only one PRG page, we must copy
# it twice so it can fit the entire PRG region in NES memory
proc setProgram*(program: pointer, size: int): void =
    var temporaryBank = newSeq[char](0x10000)
    if size < 0x8000 :
        copyMem(addr(temporaryBank[0x8000]), program, 0x4000)
        copyMem(addr(temporaryBank[0xC000]), program, 0x4000)
    else:
        copyMem(addr(temporaryBank[0x8000]), program, 0x8000)
    for i, value in temporaryBank:
        cpuMemory.bank[i] = cast[int](value)

# only used in a NES program context
proc reflectValue(address, value: int): void =
    cpuMemory.bank[address] = value
    ppu.updateRegisters(address, cpuMemory.bank[address])

# allows an illegal write to 0x2002 which is a read-only memory location
# this proc is intended to apply bitwise operation on ppu registers outside
# the context of a NES program
proc reflectBitwise*(address, bitId: int): void =
    var bit = cpuMemory.bank[address] and (1 shl bitId)
    if bit == 0 :
        cpuMemory.bank[address] = cpuMemory.bank[address] or (1 shl bitId)   
    else :
        cpuMemory.bank[address] = cpuMemory.bank[address] and not (1 shl bitId)
    ppu.transmitToRegister(address, cpuMemory.bank[address])

# the CPU can't communicate directly with the PPU
# but greatfully, the PPU registers are memory mapped
# through $2000 - $2007 location addresses
proc mmioWrite*(address, value: int): void =
    case address:
        of 0..0x1999, 0x2008..0x10000:
            cpuMemory.bank[address] = value
        of 0x2000, 0x2007:
            reflectValue(address, value)  
        else:
            echo "Invalid address"

# /!\ note : 0x2002, which is the interface memory
# location for the PPU status register, is readonly
proc mmioRead*(address: int): int =
    case address:
        of 0..0x2001, 0x2003..0x10000:
            result = cpuMemory.bank[address]
        of 0x2002:
            result = ppu.readStatus()
        else:
            echo "Invalid address"
            return 0

# return the next 16-bit address after the
# current instruction
proc getMemoryShortAt*(address: int): int =
    var lowByte = cpuMemory.bank[address]
    var highByte = cpuMemory.bank[address + 1] shl 8
    return highByte or lowByte

# out of emulation context
proc getMemoryAddressAt*(address: int): pointer =
    return addr(cpuMemory.bank[address])

proc initMem*(): void = 
    new(cpuMemory)
    # 65536 bytes in total
    cpuMemory.bank = newSeq[int](0x10000)
    # load program in NES memory
    setProgram(addr(nesRom.prgBytes[0]), len(nesRom.prgBytes))
    # manual vblank switch
    reflectBitwise(0x2002, 7)
