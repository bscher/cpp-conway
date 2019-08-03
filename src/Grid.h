#pragma once

using Index_t = size_t;
using Count_t = uint32_t;

template<Index_t WIDTH, Index_t HEIGHT>
using Grid_t = std::array<std::array<bool, HEIGHT>, WIDTH>;
