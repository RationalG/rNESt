import strutils

type
    PPUObj* = object of RootObj
        controller, mask, status: int
        oamAddress, oamData: int
        vramAddress, vramData: int
        spriteMemory, virtualMemory: seq[int]
        scrollerWriteCount, vramAddressWriteCount: int

    ControllerObj* = object of RootObj
        generateNMI, masterSlave, spriteSize, backgroundAddress: int
        spriteAddress, VRAMincrement, nameTableAddress: int

    MaskObj* = object of RootObj
        grayscale, partialBackground, partialSprites: int
        background, sprites, color: int

    ScrollerObj* = object of RootObj
        xCoordinate, yCoordinate: int

    PPUMemoryObj* = object of RootObj
        bank: seq[int]

var nesPpu* : PPUObj
var ppuMask : MaskObj
var ppuMemory : PPUMemoryObj
var ppuScroller : ScrollerObj
var ppuController : ControllerObj

import mem

proc updateController*(value: int): void =
    if value != nesPpu.controller: 
        nesPpu.controller = value
    # update bit flags on ppu controller
    ppuController.nameTableAddress = nesPpu.controller and 3
    ppuController.VRAMincrement = (nesPpu.controller shr 2) and 1
    ppuController.spriteAddress = (nesPpu.controller shr 3) and 1
    ppuController.backgroundAddress = (nesPpu.controller shr 4) and 1
    ppuController.spriteSize = (nesPpu.controller shr 5) and 1
    ppuController.masterSlave = (nesPpu.controller shr 6) and 1
    ppuController.generateNMI = (nesPpu.controller shr 7) and 1

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

proc initPpu*(): void =
    # initialize sections of memory
    ppuMemory.bank = newSeq[int](0x4000)
    nesPpu.spriteMemory = newSeq[int](0x100)