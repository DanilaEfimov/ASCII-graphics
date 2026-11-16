#pragma once

#include "coord_traits.hpp"
#include <SFML/Graphics/Rect.hpp>

class Cell {

using pos_t = coord_t<CoordCategory::UnsignedInteger>;
using vector_t = vec_t<pos_t>;
using rect_t = sf::Rect<pos_t>;

rect_t border;

public:

    Cell(rect_t br) : border(br) {};
    Cell(vector_t pos, vector_t size)
        : border(pos, size) {};

    void move(vector_t sh) {
        this->border.position += sh;
    }

};
