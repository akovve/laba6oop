#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>

/**
 * @brief Класс двумерной точки с координатами X и Y.
 */
class Point2D {
public:
    /**
     * @brief Конструктор с параметрами.
     * 
     * @param x координата X.
     * @param y координата Y.
     */
    Point2D(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}

    /**
     * @brief Получить координату X.
     * @return значение X.
     */
    double GetX() const { return x_; }

    /**
     * @brief Получить координату Y.
     * @return значение Y.
     */
    double GetY() const { return y_; }

    /**
     * @brief Установить координату X.
     * @param x новое значение X.
     */
    void SetX(double x) { x_ = x; }

    /**
     * @brief Установить координату Y.
     * @param y новое значение Y.
     */
    void SetY(double y) { y_ = y; }

    /**
     * @brief Вычисляет евклидово расстояние до другой двумерной точки.
     * 
     * @param other другая точка.
     * @return расстояние между точками.
     */
    double DistanceTo(const Point2D& other) const {
        double dx = x_ - other.x_;
        double dy = y_ - other.y_;
        return std::sqrt(dx * dx + dy * dy);
    }

private:
    double x_;  ///< Координата X.
    double y_;  ///< Координата Y.
};

#endif // POINT2D_H