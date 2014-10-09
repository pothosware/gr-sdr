/*
 * Copyright 2014 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <gnuradio/sdr/types.h>

namespace gr {
  namespace sdr {
    range_t::range_t(void):
        _min(0.0), _max(0.0)
    {}
    range_t::range_t(const double minimum, const double maximum):
        _min(minimum), _max(maximum)
    {}
    double range_t::minimum(void) const
    {
        return _min;
    }
    double range_t::maximum(void) const
    {
        return _max;
    }
}}
