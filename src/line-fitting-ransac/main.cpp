#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

bool MacroEqual(const float p1, const float p2, const float tolerance = 1e-5)
{
    return std::fabs(p1 - p2) < tolerance;
}

struct Point2f {
    Point2f(const Point2f &) = default;
    Point2f(Point2f &&) = default;
    Point2f &operator=(const Point2f &) = default;
    Point2f &operator=(Point2f &&) = default;
    Point2f(float x, float y)
        : x(x), y(y) {}
    float x;
    float y;

    bool operator==(const Point2f &other) const
    {
        return MacroEqual(x, other.x) && MacroEqual(y, other.y);
    }
};

struct LineInfo {
    float a;
    float b;
    float c;
};

float PointToLineDistance(const LineInfo &line_info, const Point2f &point)
{
    float distance_1 = std::abs(line_info.a * point.x + line_info.b * point.x + line_info.c);
    float distance_2 = std::sqrt(std::pow(line_info.a, 2) + 1.0f);
    return distance_1 / distance_2;
}

LineInfo LeastSquare(const std::vector<Point2f> &points)
{ // 一次最小二乘求解直线参数
    if (points.size() < 2) {
        return LineInfo();
    }

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

    // Q
    double w1 = n * mid5 - mid1 * mid2;
    // N, w2 = n * mid4 - mid2 * mid2 - n * mid3 + mid1 * mid1;
    double w2 = mid2 * mid2 - n * mid4 - mid1 * mid1 + n * mid3;
    // M
    double w3 = mid1 * mid2 - n * mid5;

    // ax+by+c = 0
    // 等价于 y = kx + b; kx -y + b = 0
    // a = k, c = b, b = -1
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

void LeastSquareRansac(const std::vector<Point2f> &points, LineInfo &line_info, const int maxIterations, const double threshold)
{
    LineInfo line_info_curr{};
    size_t best_inliners_count{};
    std::vector<Point2f> best_inliers{};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, points.size() - 1);

    for (size_t i = 0; i < maxIterations; ++i) {
        std::vector<Point2f> inliners_compute{};
        const int kInputSize = std::floor(0.8 * points.size());
        for (size_t j = 0; j < kInputSize; ++j) {
            size_t idx = dis(gen);
            if (std::find(inliners_compute.begin(), inliners_compute.end(), points[idx]) == inliners_compute.end()) {
                inliners_compute.emplace_back(points[idx]);
            }
        }

        std::cout << "points used to compute size: " << inliners_compute.size() << std::endl;

        line_info_curr = LeastSquare(inliners_compute);
        std::cout << "curr a: " << line_info.a << ", b: " << line_info.b << ", c: " << line_info.c << std::endl;

        std::vector<Point2f> inliners{};
        for (const auto &iter : points) {
            if (PointToLineDistance(line_info_curr, iter) < threshold) {
                inliners.emplace_back(iter);
            }
        }

        if (inliners.size() > best_inliners_count) {
            best_inliners_count = inliners.size();
            best_inliers = inliners;
            line_info = line_info_curr;
        }
    }
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
    points.push_back(Point2f(412.0f, 400.0f));

    LineInfo line_info = LeastSquare(points);
    std::cout << "line_info a: " << line_info.a << ", line_fino b: " << line_info.b << ", line_info c: " << line_info.c
              << std::endl;

    LineInfo line_info_new{};
    LeastSquareRansac(points, line_info_new, 10, 0.03);
    std::cout << "line_info_new a: " << line_info_new.a << ", line_info_new b: " << line_info_new.b
              << ", line_info_new c: " << line_info_new.c << std::endl;

    for (int i = 0; i < points.size(); i++) {
        std::cout << "old, idx: " << i << ", x: " << points[i].x << ", y: " << points[i].y << std::endl;
        Point2f temp = Point2f(points[i].x, line_info.a * points[i].x + line_info.c);

        float distance_1 = std::abs(line_info.a * points[i].x + line_info.b * points[i].x + line_info.c);
        float distance_2 = std::sqrt(std::pow(line_info.a, 2) + 1.0f);

        float distance = distance_1 / distance_2;

        std::cout << "line_info, idx: " << i << ", x: " << temp.x << ", y: " << temp.y << ", dis: " << distance
                  << std::endl;

        temp = Point2f(points[i].x, line_info_new.a * points[i].x + line_info_new.c);

        distance_1 = std::abs(line_info_new.a * points[i].x + line_info_new.b * points[i].x + line_info_new.c);
        distance_2 = std::sqrt(std::pow(line_info_new.a, 2) + 1.0f);

        distance = distance_1 / distance_2;

        std::cout << "line_info_new, idx: " << i << ", x: " << temp.x << ", y: " << temp.y << ", dis: " << distance
                  << std::endl;
    }

    return 0;
}
