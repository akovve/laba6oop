#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"
#include <cmath>

/**
 * @brief Класс трёхмерной точки, наследник Point2D.
 * 
 * Добавляет координату Z и переопределяет метод DistanceTo для учёта трёх измерений.
 */
class Point3D : public Point2D {
public:
    /**
     * @brief Конструктор с параметрами.
     * 
     * @param x координата X.
     * @param y координата Y.
     * @param z координата Z.
     */
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0) : Point2D(x, y), z_(z) {}

    /**
     * @brief Получить координату Z.
     * @return значение Z.
     */
    double GetZ() const { return z_; }

    /**
     * @brief Установить координату Z.
     * @param z новое значение Z.
     */
    void SetZ(double z) { z_ = z; }

    /**
     * @brief Вычисляет евклидово расстояние до другой трёхмерной точки.
     * 
     * @param other другая трёхмерная точка.
     * @return расстояние между точками.
     */
    double DistanceTo(const Point3D& other) const {
        double dx = GetX() - other.GetX();
        double dy = GetY() - other.GetY();
        double dz = z_ - other.z_;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

private:
    double z_;  ///< Координата Z.
};

#endif // POINT3D_H