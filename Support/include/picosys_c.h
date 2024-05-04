#include <cstdint>

// Implement these functions in Swift.
extern "C" {
    void swift_init();
    void swift_update(uint32_t ticks);
    void swift_draw(uint32_t ticks);
}

// C wrappers for picosystem:: functions.
//
// Add to and implement as needed.
extern "C" {
    void ps_clear();
    void ps_pen(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 15);
    void ps_cursor(int32_t x, int32_t y);
    void ps_sprite(uint32_t i, int32_t x, int32_t y);
    void ps_text(const char *c);
    uint32_t ps_time();
    float ps_fsin(float v);
}
