#include <iostream>
#include <vector>
#include <cmath>

struct Point2f {
  float x;
  float y;
};

struct LineInfo {
  float a;
  float b;
  float c;
};

LineInfo leastSquare(const std::vector<Point2f>& points) {  // 一次最小二乘求解直线参数
  double mid1{};
  double mid2{};
  double mid3{};
  double mid4{};
  double mid5{};
  LineInfo temp{};  // 直线方程式结构体
  int n = points.size();

  for (size_t i = 0; i < points.size(); ++i) {
    mid1 += points[i].x;
    mid2 += points[i].y;
    mid3 += points[i].x * points[i].x;
    mid4 += points[i].y * points[i].y;
    mid5 += points[i].x * points[i].y;
  }

  double w1 = n * mid5 - mid1 * mid2;  // Q
  double w2 =
      mid2 * mid2 - n * mid4 - mid1 * mid1 + n * mid3;  // N, w2 = n * mid4 - mid2 * mid2 - n * mid3 + mid1 * mid1;
  double w3 = mid1 * mid2 - n * mid5;                   // M

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

int main() {
  // 输入拟合点
  std::vector<Point2f> points;
  // points.push_back(Point2f(48.0f, 58.0f));
  // points.push_back(Point2f(105.0f, 98.0f));
  // points.push_back(Point2f(155.0f, 160.0f));
  // points.push_back(Point2f(212.0f, 220.0f));
  // points.push_back(Point2f(248.0f, 260.0f));
  // points.push_back(Point2f(320.0f, 300.0f));
  // points.push_back(Point2f(350.0f, 360.0f));
  // points.push_back(Point2f(412.0f, 380.0f));

  points.emplace_back(0.6906036138534546 - 0.9530516862869263);
  points.emplace_back(0.6922041177749634 - 0.9286074042320251);
  points.emplace_back(0.6952065825462341 - 0.9150596857070923);
  points.emplace_back(0.6992769837379456 - 0.9094263315200806);
  points.emplace_back(0.7041923403739929 - 0.9097190499305725);
  points.emplace_back(0.708962619304657 - 0.9090081453323364);
  points.emplace_back(0.7138824462890625 - 0.909271776676178);
  points.emplace_back(0.7186513543128967 - 0.9085326790809631);
  points.emplace_back(0.7232605814933777 - 0.9067921042442322);
  points.emplace_back(0.7281826138496399 - 0.9070128798484802);
  points.emplace_back(0.7329448461532593 - 0.9062321782112122);
  points.emplace_back(0.7377048134803772 - 0.9054375886917114);
  points.emplace_back(0.7428003549575806 - 0.9066004753112793);
  points.emplace_back(0.7475613355636597 - 0.9057772159576416);
  points.emplace_back(0.7524946331977844 - 0.9059247374534607);
  points.emplace_back(0.7572535872459412 - 0.9050732851028442);
  points.emplace_back(0.7621905207633972 - 0.9051917195320129);
  points.emplace_back(0.7671306133270264 - 0.905295193195343);
  points.emplace_back(0.7722599506378174 - 0.906366229057312);
  points.emplace_back(0.7772091031074524 - 0.9064393639564514);
  points.emplace_back(0.7821613550186157 - 0.9064974188804626);
  points.emplace_back(0.7873112559318542 - 0.9075213670730591);
  points.emplace_back(0.7922722697257996 - 0.9075490236282349);
  points.emplace_back(0.7972362637519836 - 0.9075616598129272);
  points.emplace_back(0.8019998073577881 - 0.9065800905227661);
  points.emplace_back(0.8067604899406433 - 0.9055846929550171);
  points.emplace_back(0.8117271661758423 - 0.9055532813072205);
  points.emplace_back(0.8164848685264587 - 0.9045295715332031);
  points.emplace_back(0.8214541673660278 - 0.9044687747955322);
  points.emplace_back(0.8262085914611816 - 0.9034167528152466);
  points.emplace_back(0.8311802744865417 - 0.9033262729644775);
  points.emplace_back(0.8363776803016663 - 0.9041956663131714);
  points.emplace_back(0.8418091535568237 - 0.9060225486755371);
  points.emplace_back(0.8472545146942139 - 0.9078317880630493);
  points.emplace_back(0.8522502779960632 - 0.9076775312423706);
  points.emplace_back(0.8572483658790588 - 0.9075080156326294);
  points.emplace_back(0.8622488379478455 - 0.9073233604431152);
  points.emplace_back(0.8672515749931335 - 0.9071234464645386);
  points.emplace_back(0.872499406337738 - 0.9078782796859741);
  points.emplace_back(0.8777551054954529 - 0.9086164236068726);
  points.emplace_back(0.8827700018882751 - 0.9083693027496338);
  points.emplace_back(0.8877869248390198 - 0.9081067442893982);
  points.emplace_back(0.8928059339523315 - 0.9078289270401001);
  points.emplace_back(0.8978268504142761 - 0.9075358510017395);
  points.emplace_back(0.9025899171829224 - 0.906261682510376);
  points.emplace_back(0.9076119065284729 - 0.905938446521759);
  points.emplace_back(0.9123702645301819 - 0.9046358466148376);
  points.emplace_back(0.91712486743927 - 0.9033193588256836);
  points.emplace_back(0.9224176406860352 - 0.9039141535758972);
  points.emplace_back(0.9277178049087524 - 0.9044921398162842);
  points.emplace_back(0.9330251812934875 - 0.9050529599189758);
  points.emplace_back(0.9377808570861816 - 0.9036763906478882);
  points.emplace_back(0.9433792233467102 - 0.9051640629768372);
  points.emplace_back(0.9487051963806152 - 0.905674397945404);
  points.emplace_back(0.9540382623672485 - 0.9061676263809204);
  points.emplace_back(0.9590877294540405 - 0.9056867957115173);
  points.emplace_back(0.9638451337814331 - 0.9042344689369202);
  points.emplace_back(0.9768849611282349 - 0.895980715751648);

  LineInfo line_info = leastSquare(points);
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