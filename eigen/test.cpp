#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>

int main()
{
    Eigen::Matrix3f m3;
    std::cout << "m3 uninitialized = " << std::endl << m3 << std::endl;

    m3 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    std::cout << "m3 = " << std::endl << m3 << std::endl;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            std::cout << "m(" << r << "," << c << ") = " << m3(r, c) << "; ";
        }
        std::cout << std::endl;
    }

    Eigen::Matrix4f M2{ Eigen::Matrix4f::Constant(2.2) };
    std::cout << "M2 = \n" << M2 << std::endl;

    std::cout << "M2 - Ones()*2.2 = \n" << M2 - Eigen::Matrix4f::Ones() * 2.2 << std::endl;

    std::cout << ((M2 - Eigen::Matrix4f::Ones() * 2.2 == Eigen::Matrix4f::Zero()) ? "true" : "false") << std::endl;

    std::cout << "m3.transport() = \n" << m3.transpose() << std::endl;

    std::cout << "m3.inverse() = \n" << m3.transpose() << std::endl;

    Eigen::Matrix3f m123;
    m123 << 1, 0, 0, 0, 2, 0, 0, 0, 4;
    std::cout << "m123 = \n" << m123 << std::endl;
    std::cout << "{1,0,0;0,2,0;0,0,4}.inverse() = \n" << m123.inverse() << std::endl;
    std::cout << "m123 = \n" << m123 << std::endl;

    Eigen::Vector3f v1{Eigen::Vector3f::Ones()}, v2{Eigen::Vector3f::Zero()};
    Eigen::Vector4d v3{Eigen::Vector4d::Random()}, v4{Eigen::Vector4d::Constant(1.8)};
    std::cout << "v1 = " << v1 << std::endl << "v2 = " << v2 << std::endl
              << "v3 = " << v3 << std::endl << "v4 = " << v4 << std::endl;
    std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
    std::cout << "v4 - v3 = " << v4 - v3 << std::endl;
    std::cout << "v4 * 2 = " << v4 * 2 << std::endl;
    std::cout << "V2f::1 * 3 == V2f::3 ? : "
              << (Eigen::Vector2f::Ones() * 3 == Eigen::Vector2f::Constant(3) ? "true" : "false")
              << std::endl;
}
