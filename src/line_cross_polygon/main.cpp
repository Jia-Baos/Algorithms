#include <climits>
#include <iostream>
#include <vector>
#include <cmath>

struct Point2f {
    Point2f(const Point2f &) = default;
    Point2f(Point2f &&) = default;
    Point2f &operator=(const Point2f &) = default;
    Point2f &operator=(Point2f &&) = default;
    Point2f(float x, float y)
        : x(x), y(y) {}
    float x;
    float y;
};

struct SLine {
    SLine(const SLine &) = default;
    SLine(SLine &&) = default;
    SLine(float x1, float y1, float x2, float y2)
        : x1(x1), y1(y1), x2(x2), y2(y2) {}
    float x1;
    float y1;
    float x2;
    float y2;
};

bool Intersection(const SLine &l1, const SLine &l2)
{
    // 快速排斥实验
    if ((l1.x1 > l1.x2 ? l1.x1 : l1.x2) < (l2.x1 < l2.x2 ? l2.x1 : l2.x2)
        || (l1.y1 > l1.y2 ? l1.y1 : l1.y2) < (l2.y1 < l2.y2 ? l2.y1 : l2.y2)
        || (l2.x1 > l2.x2 ? l2.x1 : l2.x2) < (l1.x1 < l1.x2 ? l1.x1 : l1.x2)
        || (l2.y1 > l2.y2 ? l2.y1 : l2.y2) < (l1.y1 < l1.y2 ? l1.y1 : l1.y2)) {
        return false;
    }
    // 跨立实验，本质在于被跨立的线段的方向在连线的同侧还是中央区域
    if ((((l1.x1 - l2.x1) * (l2.y2 - l2.y1) - (l1.y1 - l2.y1) * (l2.x2 - l2.x1)) * ((l1.x2 - l2.x1) * (l2.y2 - l2.y1) - (l1.y2 - l2.y1) * (l2.x2 - l2.x1))) > 0
        || (((l2.x1 - l1.x1) * (l1.y2 - l1.y1) - (l2.y1 - l1.y1) * (l1.x2 - l1.x1)) * ((l2.x2 - l1.x1) * (l1.y2 - l1.y1) - (l2.y2 - l1.y1) * (l1.x2 - l1.x1))) > 0) {
        return false;
    }
    return true;
}

int main()
{

    SLine l1{ 0, 0, 100, 100 };
    SLine l2{ 0, 100, 100, 0 };
    auto res = Intersection(l1, l2);
    std::cout << "res flag: " << res << std::endl;
}
