import nes, cpu, rom

# cpu writes to ppu through mmio bus
# ppu posesses eight 8-bits registers
# to check what bits are set :
# 0xV, V being : 1, 2, 4, 8, 10, 20, 40, 80 
# conventions wants bits listed as 0-7    
# access points of internal cpu
    
type
    PCPUMEM* = ref TCPUMEM 
    TCPUMEM* = object of TObject
        bank: seq[int]

var cpuMemory* : PCPUMEM

proc setProgram*(program: pointer): void =
    var temporaryBank = newSeq[char](0x10000)
    copyMem(addr(temporaryBank[0x8000]), program, 0x8000)
    for i, value in temporaryBank:
        cpuMemory.bank[i] = cast[int](value)

proc initMem*(): void = 
    new(cpuMemory)
    # 65536 bytes in total
    cpuMemory.bank = newSeq[int](0x10000)
    # load program in NES memory
    setProgram(addr(nesRom.prgBytes[0]))

proc mmioWrite*(address, value: int): void =
    case address:
        of 0..0x10000:
            cpuMemory.bank[address] = value
        else:
            echo "Invalid address"
            return
 
proc mmioRead*(address: int): int =
    case address:
        of 0..0x10000:
            return cpuMemory.bank[address]
        else:
            echo "Invalid address"
            return 0

proc getMemoryShortAt*(address: int): int =
    var lowByte = cpuMemory.bank[address]
    var highByte = cpuMemory.bank[address + 1] shl 8
    return highByte or lowByte

proc getMemoryAddressAt*(address: int): pointer =
    return addr(cpuMemory.bank[address])