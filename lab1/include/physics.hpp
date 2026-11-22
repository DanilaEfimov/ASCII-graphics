#pragma once

#include "bubble.hpp"
#include "cell.hpp"
#include <SFML/Graphics/ConvexShape.hpp>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <numbers>
#include <vector>


struct State {
    sf::ConvexShape shape;      // пересечение шарика и рамки (абсолютные координаты)
    sf::Vector2f velocity;      // px/s
    double presure;             // доля площади шарика, срезанная стенками: 0..1
};

class Physics {

using vector_t = sf::Vector2f;
using polygon_t = std::vector<vector_t>;

static constexpr std::size_t circle_points = 128;

Cell& cell;
Bubble& bubble;

State state;

// Sutherland-Hodgman: отсечение выпуклого многоугольника одной осевой полуплоскостью
static polygon_t clip(const polygon_t& in, bool by_x, float bound, bool keep_greater) {
    polygon_t out;
    if (in.empty())
        return out;

    auto coord = [by_x](vector_t p) { return by_x ? p.x : p.y; };
    auto inside = [&](vector_t p) {
        return keep_greater ? coord(p) >= bound : coord(p) <= bound;
    };
    auto cross = [&](vector_t a, vector_t b) {
        float t = (bound - coord(a)) / (coord(b) - coord(a));
        return a + (b - a) * t;
    };

    for (std::size_t i = 0; i < in.size(); ++i) {
        vector_t cur = in[i];
        vector_t prev = in[(i + in.size() - 1) % in.size()];
        if (inside(cur)) {
            if (!inside(prev))
                out.push_back(cross(prev, cur));
            out.push_back(cur);
        } else if (inside(prev)) {
            out.push_back(cross(prev, cur));
        }
    }
    return out;
}

static double area(const polygon_t& p) {
    double s = 0.0;
    for (std::size_t i = 0; i < p.size(); ++i) {
        const vector_t& a = p[i];
        const vector_t& b = p[(i + 1) % p.size()];
        s += static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
    }
    return std::abs(s) / 2.0;
}

polygon_t circlePolygon() const {
    const vector_t c = this->bubble.getCenter();
    const float r = this->bubble.getRadius();
    constexpr float two_pi = 2.f * std::numbers::pi_v<float>;

    polygon_t poly;
    poly.reserve(circle_points);
    for (std::size_t i = 0; i < circle_points; ++i) {
        float a = two_pi * static_cast<float>(i) / static_cast<float>(circle_points);
        poly.push_back(c + vector_t{r * std::cos(a), r * std::sin(a)});
    }
    return poly;
}

// Центр шарика не может покинуть рамку: упираемся в стенку и гасим скорость вдоль неё
void resolveCollisions(vector_t& c) {
    const sf::FloatRect b = this->cell.getBounds();
    const float left = b.position.x;
    const float top = b.position.y;
    const float right = left + b.size.x;
    const float bottom = top + b.size.y;

    vector_t& v = this->state.velocity;
    if (c.x < left)        { c.x = left;   v.x = 0.f; }
    else if (c.x > right)  { c.x = right;  v.x = 0.f; }
    if (c.y < top)         { c.y = top;    v.y = 0.f; }
    else if (c.y > bottom) { c.y = bottom; v.y = 0.f; }
}

void selectShape() {
    const sf::FloatRect b = this->cell.getBounds();

    polygon_t full = this->circlePolygon();
    polygon_t poly = full;
    poly = clip(poly, true,  b.position.x,              true);
    poly = clip(poly, true,  b.position.x + b.size.x,   false);
    poly = clip(poly, false, b.position.y,              true);
    poly = clip(poly, false, b.position.y + b.size.y,   false);

    this->state.shape.setPointCount(poly.size());
    for (std::size_t i = 0; i < poly.size(); ++i)
        this->state.shape.setPoint(i, poly[i]);
    this->state.shape.setFillColor(this->bubble.getColor());

    const double full_area = area(full);
    this->state.presure = (full_area > 0.0 && poly.size() >= 3)
        ? 1.0 - area(poly) / full_area
        : 0.0;
}

public:
    Physics(Cell& c, Bubble& b)
        : cell(c), bubble(b) {
        this->state.velocity = {0.f, 0.f};
        this->state.presure = 0.0;
        this->selectShape();
    }

    // Скорость задаёт управление (px/s)
    void setVelocity(vector_t v) {
        this->state.velocity = v;
    }

    const State& evolute(float dt) {
        vector_t c = this->bubble.getCenter() + this->state.velocity * dt;
        this->resolveCollisions(c);
        this->bubble.setCenter(c);
        this->selectShape();
        return this->state;
    }

    // Для случая, когда шарик изменили снаружи (например, расширили) без шага по времени
    const State& state_now() {
        this->selectShape();
        return this->state;
    }

};
