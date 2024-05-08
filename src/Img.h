#ifndef IMG_H_
#define IMG_H_

// System includes
#include <string>

// Local includes
#include "CImg.h"

class Img
{

public:
    Img(int w, int h, std::string title);
    ~Img(void) {}

    int getHeight(void) const;
    int getWidth(void) const;

    bool isClosed(void) const;

    void setTitle(const char *title);

    void drawPoint(int col, int row, float *color);
    void drawCircle(int col, int row, float *color);
    void drawLine(int x0, int y0, int x1, int y1, float *color);
    void drawRectangle(const int x0, const int y0, const int x1, const int y1,
                       float *color, const float opacity = 1);

    void display(void);

    bool mouseClick(void);

private:
    cimg_library::CImg<float> img;
    cimg_library::CImgDisplay disp;
};

#endif /* IMG_H_ */
