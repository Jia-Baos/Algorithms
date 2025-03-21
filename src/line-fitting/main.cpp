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

struct LineInfo {
    float a;
    float b;
    float c;
};

LineInfo LeastSquare(const std::vector<Point2f> &points)
{ // 一次最小二乘求解直线参数
    double mid1{};
    double mid2{};
    double mid3{};
    double mid4{};
    double mid5{};
    LineInfo temp{}; // 直线方程式结构体
    int n = points.size();

    for (size_t i = 0; i < points.size(); ++i) {
        mid1 += points[i].x;
        mid2 += points[i].y;
        mid3 += points[i].x * points[i].x;
        mid4 += points[i].y * points[i].y;
        mid5 += points[i].x * points[i].y;
    }

    double w1 = n * mid5 - mid1 * mid2; // Q
    double w2 =
        mid2 * mid2 - n * mid4 - mid1 * mid1 + n * mid3; // N, w2 = n * mid4 - mid2 * mid2 - n * mid3 + mid1 * mid1;
    double w3 = mid1 * mid2 - n * mid5;                  // M

    // ax+by+c = 0 等价于 y = kx + b; kx -y + b = 0 // a = k, c = b, b = -1
    if (w1 == 0) {
        temp.a = -1;
        temp.b = 0;
        temp.c = mid1 / n;
    } else {
        temp.a = (-w2 + std::sqrt(w2 * w2 - 4 * w1 * w3)) / 2.0 / w1;
        temp.b = -1;
        temp.c = (mid2 - temp.a * mid1) / n;
    }
    return temp;
}

int main()
{
    // 输入拟合点
    std::vector<Point2f> points;
    points.push_back(Point2f(48.0f, 58.0f));
    points.push_back(Point2f(105.0f, 98.0f));
    points.push_back(Point2f(155.0f, 160.0f));
    points.push_back(Point2f(212.0f, 220.0f));
    points.push_back(Point2f(248.0f, 260.0f));
    points.push_back(Point2f(320.0f, 300.0f));
    points.push_back(Point2f(350.0f, 360.0f));
    points.push_back(Point2f(412.0f, 380.0f));

    LineInfo line_info = LeastSquare(points);
    std::cout << "line_info a: " << line_info.a << ", line_fino b: " << line_info.b << ", line_info c: " << line_info.c
              << std::endl;

    for (int i = 0; i < points.size(); i++) {
        std::cout << "old, idx: " << i << ", x: " << points[i].x << ", y: " << points[i].y << std::endl;
        Point2f temp = Point2f(points[i].x, line_info.a * points[i].x + line_info.c);

        float distance_1 = std::abs(line_info.a * points[i].x + line_info.b * points[i].x + line_info.c);
        float distance_2 = std::sqrt(std::pow(line_info.a, 2) + 1.0f);

        float distance = distance_1 / distance_2;

        std::cout << "new, idx: " << i << ", x: " << temp.x << ", y: " << temp.y << ", dis: " << distance << std::endl;
    }

    return 0;
}
