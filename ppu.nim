import mem, colors

type
    PPPU* = ref TPPU
    TPPU* = object of TObject

var nesPpu* : PPPU

proc setVBlank*(): void =
    mmioWrite(0x2002, 0x80)

proc initPpu*(): void =
    new(nesPpu)
    setVBlank()
    
