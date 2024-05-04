#include "picosys_c.h"
#include "picosystem.hpp"


void init() {
    swift_init();
}

void update(uint32_t ticks) {
    swift_update(ticks);
}

void draw(uint32_t ticks) {
    swift_draw(ticks);
}


void ps_clear() {
    picosystem::clear();
}

void ps_pen(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    picosystem::pen(r, g, b, a);
}

void ps_cursor(int32_t x, int32_t y) {
    picosystem::cursor(x, y);
}
  
void ps_sprite(uint32_t i, int32_t x, int32_t y) {
    picosystem::sprite(i, x, y);
}

void ps_text(const char *c) {
    picosystem::text(c);
}

uint32_t ps_time() {
    return picosystem::time();
}

float ps_fsin(float v) {
    return picosystem::fsin(v);
}