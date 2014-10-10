/*
 * Copyright 2010-2014 Free Software Foundation, Inc.
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

#define GR_SDR_API

////////////////////////////////////////////////////////////////////////
// standard includes
////////////////////////////////////////////////////////////////////////

%include <std_vector.i>
%include <std_map.i>
%include "gnuradio.i"

//load generated python docstrings
%include "sdr_swig_doc.i"

////////////////////////////////////////////////////////////////////////
// block headers
////////////////////////////////////////////////////////////////////////
%{
#include <gnuradio/sdr/types.h>
#include <gnuradio/sdr/source.h>
#include <gnuradio/sdr/sink.h>
%}

////////////////////////////////////////////////////////////////////////
// used types
////////////////////////////////////////////////////////////////////////

%include <gnuradio/sdr/types.h>

%template(sdr_string_vector_t) std::vector<std::string>;

%template(sdr_size_vector_t) std::vector<size_t>;

%template(sdr_range_vector_t) std::vector<gr::sdr::range_t>;

%template(sdr_kwargs_t) std::map<std::string, std::string>;

////////////////////////////////////////////////////////////////////////
// block magic
////////////////////////////////////////////////////////////////////////
%include <gnuradio/sdr/source.h>
%include <gnuradio/sdr/sink.h>

GR_SWIG_BLOCK_MAGIC2(sdr, source)
GR_SWIG_BLOCK_MAGIC2(sdr, sink)
