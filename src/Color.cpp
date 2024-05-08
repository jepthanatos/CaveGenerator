// Local includes
#include "Color.h"

Color::Color(void) : r{0.f}, g{0.f}, b{0.f} {}
Color::Color(float _r, float _g, float _b) : r{_r}, g{_g}, b{_b} {}
const Color &Color::blue(void)
{
    static const Color color(0, 191, 255);
    return color;
}
const Color &Color::black(void)
{
    static const Color color(0, 0, 0);
    return color;
}
const Color &Color::yellow(void)
{
    static const Color color(255, 255, 225);
    return color;
}
const Color &Color::red(void)
{
    static const Color color(250, 0, 0);
    return color;
}
