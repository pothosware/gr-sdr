/*
 * Copyright 2011-2014 Free Software Foundation, Inc.
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

#ifndef INCLUDED_GR_SDR_TYPES_H
#define INCLUDED_GR_SDR_TYPES_H

#include <gnuradio/sdr/api.h>
#include <map>
#include <string>
#include <vector>

namespace gr {
  namespace sdr {

    //! Typedef for a dictionary of key-value string arguments
    typedef std::map<std::string, std::string> kwargs_t;

    /*!
     * A simple min/max numeric range pair
     */
    class GR_SDR_API range_t
    {
    public:

        //! Create an empty range (0.0, 0.0)
        range_t(void);

        //! Create a min/max range
        range_t(const double minimum, const double maximum);

        //! Get the range minimum
        double minimum(void) const;

        //! Get the range maximum
        double maximum(void) const;

    private:
        double _min, _max;
    };

}}

#endif /* INCLUDED_GR_SDR_TYPES_H */
