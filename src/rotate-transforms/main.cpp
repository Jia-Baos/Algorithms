#include <iostream>
#include <iterator>
#include "utils.hpp"

int main(int argc, char *argv[])
{
    /**
     * rotation_vector: 0.785398 0 0 1
     * rotation_matrix:
                        0.707107 -0.707107         0
                        0.707107  0.707107         0
                                0         0         1
     * euler_angle:     0 0 0.785398
     * quaternion:      0        0 0.382683  0.92388
     */
    Eigen::AngleAxisd rotation_vector{};
    Eigen::Matrix3d rotation_matrix{};
    Eigen::Vector3d euler_angle{};
    Eigen::Quaterniond quaternion{};

    std::cout << "--------------------------------" << std::endl;

    std::cout << "ROTATION_VECTOR::rotation_vector\n"
              << ROTATION_VECTOR::rotation_vector.angle() << " " << ROTATION_VECTOR::rotation_vector.axis().transpose() << std::endl
              << std::endl;

    std::cout << "ROTATION_VECTOR::rotation_matrix\n"
              << ROTATION_VECTOR::rotation_matrix << std::endl
              << std::endl;

    std::cout << "ROTATION_VECTOR::euler_angle\n"
              << ROTATION_VECTOR::euler_angle.transpose() << std::endl
              << std::endl;

    std::cout << "ROTATION_VECTOR::quaternion\n"
              << ROTATION_VECTOR::quaternion.coeffs().transpose() << std::endl
              << std::endl;

    std::cout << "--------------------------------" << std::endl;

    std::cout << "ROTATION_MATRIX::rotation_vector\n"
              << ROTATION_MATRIX::rotation_vector.angle() << " " << ROTATION_MATRIX::rotation_vector.axis().transpose() << std::endl
              << std::endl;

    std::cout << "ROTATION_MATRIX::rotation_matrix\n"
              << ROTATION_MATRIX::rotation_matrix << std::endl
              << std::endl;

    std::cout << "ROTATION_MATRIX::euler_angle\n"
              << ROTATION_MATRIX::euler_angle.transpose() << std::endl
              << std::endl;

    auto res = ROTATION_MATRIX::isRotationMatirx(ROTATION_MATRIX::rotation_matrix);
    euler_angle = ROTATION_MATRIX::rotationMatrixToEulerAngles(ROTATION_MATRIX::rotation_matrix);
    std::cout << "ROTATION_MATRIX::euler_angle\n"
              << euler_angle.transpose() << std::endl
              << std::endl;

    std::cout << "ROTATION_MATRIX::quaternion\n"
              << ROTATION_MATRIX::quaternion.coeffs().transpose() << std::endl
              << std::endl;

    std::cout << "--------------------------------" << std::endl;

    rotation_vector = Eigen::AngleAxisd(EULER_ANGLE::euler_angle[2], Eigen::Vector3d::UnitZ())
                      * Eigen::AngleAxisd(EULER_ANGLE::euler_angle[1], Eigen::Vector3d::UnitY())
                      * Eigen::AngleAxisd(EULER_ANGLE::euler_angle[0], Eigen::Vector3d::UnitX());

    std::cout << "EULER_ANGLE::rotation_vector\n"
              << rotation_vector.angle() << " " << rotation_vector.axis().transpose() << std::endl
              << std::endl;

    rotation_matrix = Eigen::AngleAxisd(EULER_ANGLE::euler_angle[2], Eigen::Vector3d::UnitZ())
                      * Eigen::AngleAxisd(EULER_ANGLE::euler_angle[1], Eigen::Vector3d::UnitY())
                      * Eigen::AngleAxisd(EULER_ANGLE::euler_angle[0], Eigen::Vector3d::UnitX());

    std::cout << "EULER_ANGLE::rotation_matrix\n"
              << rotation_matrix << std::endl
              << std::endl;

    rotation_matrix = EULER_ANGLE::eulerAnglesToRotationMatrix(EULER_ANGLE::euler_angle);

    std::cout << "EULER_ANGLE::rotation_matrix\n"
              << rotation_matrix << std::endl
              << std::endl;

    std::cout << "EULER_ANGLE::euler_angle\n"
              << EULER_ANGLE::euler_angle.transpose() << std::endl
              << std::endl;

    quaternion = Eigen::AngleAxisd(EULER_ANGLE::euler_angle[2], Eigen::Vector3d::UnitZ())
                 * Eigen::AngleAxisd(EULER_ANGLE::euler_angle[1], Eigen::Vector3d::UnitY())
                 * Eigen::AngleAxisd(EULER_ANGLE::euler_angle[0], Eigen::Vector3d::UnitX());

    std::cout << "EULER_ANGLE::quaternion\n"
              << quaternion.coeffs().transpose() << std::endl
              << std::endl;

    std::cout << "--------------------------------" << std::endl;

    rotation_vector = Eigen::AngleAxisd(QUATERNION::quaternion.toRotationMatrix());

    std::cout << "QUATERNION::rotation_vector\n"
              << rotation_vector.angle() << " " << rotation_vector.axis().transpose() << std::endl
              << std::endl;

    std::cout << "QUATERNION::rotation_matrix\n"
              << QUATERNION::rotation_matrix << std::endl
              << std::endl;

    std::cout << "QUATERNION::euler_angle\n"
              << QUATERNION::euler_angle.transpose() << std::endl
              << std::endl;

    std::cout << "QUATERNION::quaternion\n"
              << QUATERNION::quaternion.coeffs().transpose() << std::endl
              << std::endl;

    return 0;
}
