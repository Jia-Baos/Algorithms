#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <sys/types.h>

const double ARC_TO_DEG = 57.29577951308238;
const double DEG_TO_ARC = 0.0174532925199433;

/**
 * rotation-vector 旋转向量
 * rotation-matrix 旋转矩阵
 * euler-angle 欧拉角
 * quaternion 四元数
 */

namespace ROTATION_VECTOR
{
/**
 * 旋转向量 -> 旋转矩阵
 * 旋转向量 -> 四元数
 */

// 定义旋转角度 (例如：45度，即 π/4 弧度)
const double angle = M_PI / 4;

// 定义旋转轴 (绕Z轴旋转)
Eigen::Vector3d axis(0, 0, 1); // Z轴单位向量

// 创建旋转对象 (AngleAxisd)
Eigen::AngleAxisd rotation_vector(angle, axis);

// 旋转向量 -> 旋转矩阵
// Eigen::Matrix3d rotation_matrix = rotation_vector.matrix();
Eigen::Matrix3d rotation_matrix = rotation_vector.toRotationMatrix();

// 旋转向量 -> 旋转矩阵 -> 欧拉角
// eulerAngles(2, 1, 0)，首先绕Z轴旋转，然后绕Y轴旋转，最后绕X轴旋转
// eulerAngles(0, 1, 2)，首先绕X轴旋转，然后绕Y轴旋转，最后绕Z轴旋转
Eigen::Vector3d euler_angle = rotation_vector.matrix().eulerAngles(2, 1, 0);

// 旋转向量 -> 四元数
Eigen::Quaternion quaternion = Eigen::Quaterniond(rotation_vector);

} // namespace ROTATION_VECTOR

namespace ROTATION_MATRIX
{
/**
 * 旋转矩阵 -> 旋转向量
 * 旋转矩阵 -> 欧拉角
 * 旋转矩阵 -> 四元数
 */

// 定义旋转角度 (例如：45度，即 π/4 弧度)
const double angle = M_PI / 4;

// 定义旋转轴 (绕Z轴旋转)
Eigen::Vector3d axis(0, 0, 1); // Z轴单位向量

// 创建旋转对象 (AngleAxisd)
Eigen::AngleAxisd rotation_vector_0(angle, axis);

// 旋转向量 -> 旋转矩阵
Eigen::Matrix3d rotation_matrix = rotation_vector_0.toRotationMatrix();

// 旋转矩阵 -> 旋转向量
Eigen::AngleAxisd rotation_vector(rotation_matrix);

// 旋转矩阵 -> 欧拉角
Eigen::Vector3d euler_angle = rotation_matrix.eulerAngles(0, 1, 2);

// 旋转矩阵 -> 四元素数
Eigen::Quaterniond quaternion(rotation_matrix);

bool isRotationMatirx(Eigen::Matrix3d R)
{
    double err = 1e-6;
    Eigen::Matrix3d shouldIdenity;
    shouldIdenity = R * R.transpose();
    Eigen::Matrix3d I = Eigen::Matrix3d::Identity();
    return (shouldIdenity - I).norm() < err;
}

// 旋转矩阵 -> 欧拉角
Eigen::Vector3d rotationMatrixToEulerAngles(Eigen::Matrix3d &R)
{
    assert(isRotationMatirx(R));
    double sy = sqrt(R(0, 0) * R(0, 0) + R(1, 0) * R(1, 0));
    bool singular = sy < 1e-6;
    double x, y, z;
    if (!singular) {
        x = atan2(R(2, 1), R(2, 2));
        y = atan2(-R(2, 0), sy);
        z = atan2(R(1, 0), R(0, 0));
    } else {
        x = atan2(-R(1, 2), R(1, 1));
        y = atan2(-R(2, 0), sy);
        z = 0;
    }
    return { x, y, z };
}

} // namespace ROTATION_MATRIX

namespace EULER_ANGLE
{
/**
 * 欧拉角 -> 旋转向量
 * 欧拉角 -> 旋转矩阵
 * 欧拉角 -> 四元数
 */

// 设定车体欧拉角(角度)，绕固定轴
const double roll_deg = 0;  // 绕X轴
const double pitch_deg = 0; // 绕Y轴
const double yaw_deg = 45;  // 绕Z轴

// 转化为弧度
const double roll_arc = roll_deg * DEG_TO_ARC;   // 绕X轴
const double pitch_arc = pitch_deg * DEG_TO_ARC; // 绕Y轴
const double yaw_arc = yaw_deg * DEG_TO_ARC;     // 绕Z轴

// 初始化欧拉角（rpy）,对应绕x轴，绕y轴，绕z轴的旋转角度
Eigen::Vector3d euler_angle(roll_arc, pitch_arc, yaw_arc);

Eigen::Matrix3d eulerAnglesToRotationMatrix(Eigen::Vector3d &theta)
{
    Eigen::Matrix3d R_x; // 计算旋转矩阵的X分量
    R_x << 1, 0, 0,
        0, cos(theta[0]), -sin(theta[0]),
        0, sin(theta[0]), cos(theta[0]);

    Eigen::Matrix3d R_y; // 计算旋转矩阵的Y分量
    R_y << cos(theta[1]), 0, sin(theta[1]),
        0, 1, 0,
        -sin(theta[1]), 0, cos(theta[1]);

    Eigen::Matrix3d R_z; // 计算旋转矩阵的Z分量
    R_z << cos(theta[2]), -sin(theta[2]), 0,
        sin(theta[2]), cos(theta[2]), 0,
        0, 0, 1;
    Eigen::Matrix3d R = R_z * R_y * R_x;
    return R;
}
} // namespace EULER_ANGLE

namespace QUATERNION
{
/**
 * 四元素数 -> 旋转矩阵
 * 四元素数 -> 四元数
 */

// 定义旋转角度(例如：45度，即 π / 4 弧度)
const double angle = M_PI / 4;

// 定义旋转轴 (绕Z轴旋转)
Eigen::Vector3d axis(0, 0, 1); // Z轴单位向量

// 创建旋转对象 (AngleAxisd)
Eigen::AngleAxisd rotation_vector(angle, axis);

// 旋转向量 -> 四元素数
Eigen::Quaternion quaternion = Eigen::Quaterniond(rotation_vector);

// 四元素数 -> 旋转向量
// rotation_vector = Eigen::AngleAxisd(quaternion.toRotationMatrix());

// 四元素数 -> 旋转矩阵
Eigen::Matrix3d rotation_matrix = quaternion.toRotationMatrix();

// 四元素数 -> 欧拉角
Eigen::Vector3d euler_angle = quaternion.toRotationMatrix().eulerAngles(0, 1, 2);

} // namespace QUATERNION
