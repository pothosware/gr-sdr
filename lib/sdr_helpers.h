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

#ifndef INCLUDED_GR_SDR_SDR_HELPERS_H
#define INCLUDED_GR_SDR_SDR_HELPERS_H

#include <SoapySDR/Version.hpp>
#include <gnuradio/sdr/types.h>
#include <gnuradio/io_signature.h>
#include <sstream>
#include <stdexcept>

static void check_abi(const std::string &what)
{
    if (SoapySDR::getABIVersion() == SOAPY_SDR_ABI_VERSION) return;
    std::stringstream ss;
    ss << what << "() failed ABI check" << std::endl;
    ss << "  GNURadio Client ABI Version: " << SOAPY_SDR_ABI_VERSION << std::endl;
    ss << "  SoapySDR Library ABI Version: " << SoapySDR::getABIVersion() << std::endl;
    ss << "  Rebuild module against installed library..." << std::endl;
    throw std::runtime_error(ss.str());
}

static gr::io_signature::sptr stream_args_to_io_signature(const gr::sdr::kwargs_t &stream_args)
{
    
}

#endif /* INCLUDED_GR_SDR_SDR_HELPERS_H */
