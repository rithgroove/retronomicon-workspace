#include <iostream>
#include "retronomicon/lib/math/point.h"
#include "retronomicon/lib/math/rect.h"

using namespace retronomicon::lib::math;

int main() {
    Point pos(10.0f, 20.0f);
    Rect rect(pos, 100.0f, 50.0f);

    std::cout << "Rect Position: (" << rect.getX() << ", " << rect.getY() << ")\n";
    std::cout << "Rect Size: " << rect.getWidth() << "x" << rect.getHeight() << std::endl;

    return 0;
}