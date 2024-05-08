// Local includes
#include "Img.h"

Img::Img(int w, int h, std::string title) : img(w, h, 1, 3), disp(img, title.c_str(), 0)
{
    // We move the display to our defaults position.
    disp.move(200, 200);
}

int Img::getHeight(void) const
{
    return img.height();
}

int Img::getWidth(void) const
{
    return img.width();
}

bool Img::isClosed(void) const
{
    return disp.is_closed();
}

void Img::setTitle(const char *title)
{
    disp.set_title(title);
}

void Img::drawPoint(int col, int row, float *color)
{
    img.draw_point(col, row, color);
}

void Img::drawCircle(int col, int row, float *color)
{
    img.draw_circle(col, row, 500, color, 0.5f);
}

void Img::drawLine(int x0, int y0, int x1, int y1, float *color)
{
    img.draw_line(x0, y0, x1, y1, color);
}

void Img::drawRectangle(const int x0, const int y0, const int x1, const int y1,
                        float *color, const float opacity)
{
    img.draw_rectangle(x0, y0, x1, y1, color, opacity);
}

void Img::display(void)
{
    disp.display(img);
}

bool Img::mouseClick(void)
{
    return disp.button() & 1;
}
