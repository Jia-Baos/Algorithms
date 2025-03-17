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

bool ContainPoints(const std::vector<Point2f> &rectangle, const Point2f pt)
{
    bool contain_flag = false;
    for (int i = 0; i < rectangle.size(); i++) {

        int next_idx = (i + 1) % rectangle.size();

        Point2f pt1 = rectangle[i];
        Point2f pt2 = rectangle[next_idx];
        std::cout << "candidate pox x: " << pt1.x + (pt.y - pt1.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y + 0.00000001) << std::endl;

        // 如果候选点的y坐标在矩形的y坐标范围内，那么判断候选点的x坐标在直线的左侧还是右侧来判断是否跨越直线
        if ((pt1.y < pt.y != pt2.y < pt.y) && pt1.x + (pt.y - pt1.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y + 0.00000001) > pt.x && pt1.x < pt.x && pt2.x > pt.x) {
            std::cout << i << ", changed..." << std::endl;
            contain_flag = !contain_flag;
        }
    }
    return contain_flag;
}

int main()
{

    std::vector<Point2f> vec{};
    vec.emplace_back(Point2f{ 0, 0 });
    vec.emplace_back(Point2f{ 0, 100 });
    vec.emplace_back(Point2f{ 100, 100 });
    vec.emplace_back(Point2f{ 100, 0 });

    auto res = ContainPoints(vec, Point2f(50, 50));
    std::cout << "res flag: " << res << std::endl;
}
