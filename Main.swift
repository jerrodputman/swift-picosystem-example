import PicoSys

@_cdecl("swift_init")
func `init`() {

}

@_cdecl("swift_update")
func update(_ ticks: UInt32) {

}

@_cdecl("swift_draw")
func draw(_ ticks: UInt32) {
    ps_pen(1, 1, 1)
    ps_clear()

    let yOffset = bounceOffset(height: 10, durationMs: 800)
    ps_sprite(160, 20, 60 - yOffset)

    let str: StaticString = "Hello, Swift!"
    ps_pen(255, 255, 255)
    ps_cursor(40, 60)
    ps_text(str.utf8Start)
}

func bounceOffset(height: Int32, durationMs: UInt32) -> Int32 {
    let bounceTime = Float(ps_time() % durationMs)
    let lerp = abs(bounceTime / (Float(durationMs) / 2) - 1)
    let ease = easeOut(lerp)
    let offset = ease * Float(height)

    return Int32(offset)
}

func easeOut(_ value: Float) -> Float {
    ps_fsin(value * Float.pi / 2)
}