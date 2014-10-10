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

#ifndef INCLUDED_GR_SDR_SINK_IMPL_H
#define INCLUDED_GR_SDR_SINK_IMPL_H

#include <SoapySDR/Device.hpp>
#include <gnuradio/sdr/sink.h>

class gr_sdr_sink_impl : public gr::sdr::sink
{
public:
    gr_sdr_sink_impl(
        SoapySDR::Device *device,
        SoapySDR::Stream *stream,
        const std::vector<size_t> &channels,
        const gr::io_signature::sptr sig);
    ~gr_sdr_sink_impl(void);
    void set_frontend_map(const std::string &mapping);
    std::string get_frontend_map();
    void set_samp_rate(double rate);
    double get_samp_rate(void);
    std::vector<double> get_samp_rates(void);
    void set_center_freq(double freq, size_t chan);
    double get_center_freq(size_t chan);
    std::vector<gr::sdr::range_t> get_freq_range(size_t chan);
    void set_gain(double gain, size_t chan);
    void set_gain(double gain, const std::string &name, size_t chan);
    double get_gain(size_t chan);
    double get_gain(const std::string &name, size_t chan);
    std::vector<std::string> get_gain_names(size_t chan);
    gr::sdr::range_t get_gain_range(size_t chan);
    gr::sdr::range_t get_gain_range(const std::string &name, size_t chan);
    void set_antenna(const std::string &ant, size_t chan);
    std::string get_antenna(size_t chan);
    std::vector<std::string> get_antennas(size_t chan);
    void set_bandwidth(double bandwidth, size_t chan);
    double get_bandwidth(size_t chan);
    std::vector<double> get_bandwidth_range(size_t chan);
    void set_dc_offset(const std::complex<double> &offset, size_t chan);
    void set_iq_balance(const std::complex<double> &correction, size_t chan);
    void set_time_source(const std::string &source);
    std::string get_time_source();
    std::vector<std::string> get_time_sources();
    void set_clock_source(const std::string &source);
    std::string get_clock_source();
    std::vector<std::string> get_clock_sources();
    double get_clock_rate();
    void set_clock_rate(double rate);
    int work(int noutput_items,
               gr_vector_const_void_star &input_items,
               gr_vector_void_star &output_items);
    bool start(void);
    bool stop(void);

private:
    SoapySDR::Device *d_device;
    SoapySDR::Stream *d_stream;
    const std::vector<size_t> d_channels;
};

#endif /* INCLUDED_GR_SDR_SINK_IMPL_H */
