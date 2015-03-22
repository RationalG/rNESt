import strutils
import debug, rom, mem

const
    VBLANK_START = 241
    VBLANK_END = 262

type
    PPUObj* = object of RootObj
        unlocked: bool
        controller, mask, status: int
        oamAddress, oamData, oamDMA: int
        vramAddress, vramData: int
        spriteMemory, virtualMemory: seq[int]
        scrollerWriteCount, vramAddressWriteCount: int
        scanline: int

    ControllerObj* = object of RootObj
        generateNMI, masterSlave, spriteSize, bgAddress: int
        spriteAddress, VRAMincrement, nameTableAddress: int

    MaskObj* = object of RootObj
        grayscale, partialBackground, partialSprites: int
        background, sprites, color: int

    ScrollerObj* = object of RootObj
        xCoordinate, yCoordinate: int

    PPUMemoryObj* = object of RootObj
        bank: seq[int]

    PixelObj* = object of RootObj
        x, y: int
        r, g, b: int

var nesPpu* : PPUObj
var ppuMask : MaskObj
var ppuMemory : PPUMemoryObj
var ppuScroller : ScrollerObj
var ppuController : ControllerObj

# rendering
var pixelBuffer : seq[PixelObj]

# update controllers flags from memory content
proc updateController*(value: int): void =
    if value != nesPpu.controller: 
        nesPpu.controller = value
    # update bit flags on ppu controller
    ppuController.nameTableAddress = nesPpu.controller and 3
    ppuController.VRAMincrement = (nesPpu.controller shr 2) and 1
    ppuController.spriteAddress = (nesPpu.controller shr 3) and 1
    ppuController.bgAddress = (nesPpu.controller shr 4) and 1
    ppuController.spriteSize = (nesPpu.controller shr 5) and 1
    ppuController.masterSlave = (nesPpu.controller shr 6) and 1
    ppuController.generateNMI = (nesPpu.controller shr 7) and 1
    debug(ppuController)

# update mask flags from memory content
proc updateMask*(value: int): void =
    if value != nesPpu.mask: 
        nesPpu.mask = value
    #update bit flags on ppu mask register
    ppuMask.grayscale = nesPpu.mask and 1
    ppuMask.partialBackground = (nesPpu.mask shr 1) and 1
    ppuMask.partialSprites = (nesPpu.mask shr 2) and 1
    ppuMask.background = (nesPpu.mask shr 3) and 1
    ppuMask.sprites = (nesPpu.mask shr 4) and 1
    ppuMask.color = (nesPpu.mask shr 5) and 7

# return status register to memory as a result for
# the cpu
proc readStatus*(): int =
    result = nesPpu.status
    # switch V-blank off
    # nesPpu.status = nesPpu.status and 7
    # clear the address latch used by PPUSCROLL & PPUADDR
    ppuScroller.xCoordinate = 0
    ppuScroller.yCoordinate = 0
    nesPpu.vramAddress = 0
 
proc writeSRAMAddress*(value: int): void =
    nesPpu.oamAddress = value

proc loadSRAM*(): int {.discardable.} =
    result = nesPpu.spriteMemory[nesPpu.oamAddress]

proc writeVRAMAddress*(value: int): void =
    if nesPpu.vramAddressWriteCount == 0 :
        nesPpu.vramAddress = value
        nesPpu.vramAddressWriteCount += 1
    else :
        nesPpu.vramAddress = ($nesPpu.vramAddress & $value).parseInt
        nesPpu.vramAddressWriteCount -= 1

proc loadVRAM*(bank: seq[int]): int {.discardable.} =
    result = bank[nesPpu.vramAddress]

proc writeScroll*(value: int): void =
    if nesPpu.scrollerWriteCount == 0 :
        ppuScroller.xCoordinate = value
        nesPpu.scrollerWriteCount += 1
    else : 
        ppuScroller.yCoordinate = value
        nesPpu.scrollerWriteCount -= 1

proc transmitToRegister*(address, value: int): void =
    case address:
        of 0x2000: nesPpu.controller = value
        of 0x2001: nesPpu.mask = value
        of 0x2002: nesPpu.status = value
        of 0x2003: nesPpu.oamAddress = value
        of 0x2004: nesPpu.oamData = value
        of 0x2006: nesPpu.vramData = value
        of 0x4014: nesPpu.oamDMA = value
        else: echo "Invalid address (transmit)"

proc updateRegisters*(address, value: int): void =
    case address:
        of 0x2000: updateController(value)
        of 0x2001: updateMask(value)
        of 0x2003: writeSRAMAddress(value)
        of 0x2004: loadSRAM()
        of 0x2005: writeScroll(value)
        of 0x2006: writeVRAMAddress(value)
        #of 0x2007: loadVRAM(cpuMemory.bank)
        else: echo "Invalid address (update)"

proc renderBackground(): void = 
    echo "draw bg"

proc renderSprites(): void = 
    echo "draw sprites"

proc isEnabledBackground(): bool = 
    result = false
    if ppuMask.background == 1:
        result = true

proc isEnabledSprites(): bool =
    result = false
    if ppuMask.sprites == 1:
        result = true

proc setChr(chr: pointer): void =
    var temporaryBank = newSeq[char](0x2000)
    copyMem(addr(temporaryBank[0x0000]), chr, 0x2000)
    for i, value in temporaryBank:
        ppuMemory.bank[i] = cast[int](value)

proc initPpu*(): void =
    # initialize sections of memory
    ppuMemory.bank = newSeq[int](0x4000)
    nesPpu.spriteMemory = newSeq[int](0x100)
    # load chr in PPU memory
    setChr(addr(nesRom.chrBytes[0]))
    # allocate buffer
    pixelBuffer = newSeq[PixelObj](256*240)

proc update*(): void =
    nesPpu.scanline += 1

    if isEnabledBackground():
        renderBackground()

    if isEnabledSprites():
        renderSprites()

