#pragma once

#include <cinttypes>
#include <cstdlib>
#include <unordered_map>


namespace sin_widths {
	// Note that all widths here are given in _bytes_, not in _bits_

    constexpr size_t INT_WIDTH = 4;
    constexpr size_t LONG_WIDTH = 8;
    constexpr size_t SHORT_WIDTH = 2;

    constexpr size_t BOOL_WIDTH = 1;
	constexpr size_t CHAR_WIDTH = 1;

    constexpr size_t PTR_WIDTH = 8;

    constexpr size_t FLOAT_WIDTH = 4;
    constexpr size_t DOUBLE_WIDTH = 8;
    constexpr size_t HALF_WIDTH = 2;

    constexpr size_t STRING_LENGTH_SIZE = 4;
    constexpr size_t ARRAY_LENGTH_SIZE = 4;
};
