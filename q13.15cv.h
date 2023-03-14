#ifndef _VECTOR3D_
#define _VECTOR3D_

#include "q13.15cp.h"

class Vector3D
{
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);
    void print() const;
    friend void Point3D::moveByVector(const Vector3D &v);
};

#endif
