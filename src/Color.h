#ifndef COLOR_H_
#define COLOR_H_

// System includes
#include <cstdint>

class Color
{
public:
    Color(void);
    Color(float _r, float _g, float _b);
    ~Color(void) {}

    static const Color &blue(void);
    static const Color &black(void);
    static const Color &yellow(void);
    static const Color &red(void);

private:
    float r;
    float g;
    float b;
};

#endif /* COLOR_H_ */
