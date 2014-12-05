import cpu, graphics, sdl, colors

const
    SCREEN_WIDTH = 256
    SCREEN_HEIGHT = 240

type
    PPPU* = ref TPPU
    TPPU* = object of TObject
        screen: graphics.PSurface

var nesPpu* : PPPU

proc initializePpu*(): void =
    new(nesPpu)

    if init(INIT_VIDEO) != 0:
        quit "SDL failed to initialize!"
        
    nesPpu.screen = newScreenSurface(SCREEN_WIDTH, SCREEN_HEIGHT)
    nesPpu.screen.fillSurface(colWhite)