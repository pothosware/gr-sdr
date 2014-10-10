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
#include <SoapySDR/Types.hpp>
#include <gnuradio/sdr/types.h>
#include <gnuradio/io_signature.h>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <cctype>
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

static gr::io_signature::sptr stream_args_to_io_signature(const std::string &format, std::vector<size_t> &channels)
{
    //create a single channel if unspecified
    if (channels.empty()) channels.push_back(0);

    //parse the format string
    bool isComplex = false;
    std::string numStr;
    BOOST_FOREACH (const char ch, format)
    {
        if (ch == 'C') isComplex = true;
        if (std::isdigit(ch)) numStr += ch;
    }

    //create io signature
    int bits = boost::lexical_cast<int>(numStr);
    if (isComplex) bits *= 2;
    return gr::io_signature::make(channels.size(), channels.size(), bits/8);
}

static gr::sdr::range_t toRange(const SoapySDR::Range &r)
{
    return gr::sdr::range_t(r.minimum(), r.maximum());
}

static std::vector<gr::sdr::range_t> toRanges(const std::vector<SoapySDR::Range> &ranges)
{
    std::vector<gr::sdr::range_t> out;
    BOOST_FOREACH (const SoapySDR::Range &r, ranges) out.push_back(toRange(r));
    return out;
}

#endif /* INCLUDED_GR_SDR_SDR_HELPERS_H */
