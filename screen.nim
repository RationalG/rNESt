import sdl, colors

const
    SCREEN_WIDTH = 256
    SCREEN_HEIGHT = 240
    DARK_BLUE = 0x0000AA

var screen : PSurface

proc initScreen*() =
    discard sdl.init(INIT_VIDEO)
    screen = sdl.setvideomode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SW_SURFACE)

proc draw() =
    discard screen.fillRect(nil, DARK_BLUE)
    discard screen.flip

proc tick*(): void =
    var eventType : sdl.TEvent
    var eventAddr = addr eventType
    
    while true:
        if sdl.pollEvent(eventAddr) > 0:
            case eventAddr.kind
            of QUITEV:
                break
            of KEYDOWN:
                if evKeyboard(eventAddr).keysym.sym == K_ESCAPE:
                    break
            else:
                discard

        draw()

