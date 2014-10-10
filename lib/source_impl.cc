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

#include "source_impl.h"
#include "sdr_helpers.h"
#include <boost/foreach.hpp>

gr::sdr::source::sptr gr::sdr::source::make(const gr::sdr::kwargs_t &addr, const std::string &format, const std::vector<size_t> &channels_, const gr::sdr::kwargs_t &args)
{
    check_abi("gr::sdr::source::make");
    std::vector<size_t> channels = channels_;
    gr::io_signature::sptr sig = stream_args_to_io_signature(format, channels);
    SoapySDR::Device *device = SoapySDR::Device::make(addr);
    SoapySDR::Stream *stream = device->setupStream(SOAPY_SDR_RX, format, channels, args);

    return gr::sdr::source::sptr(new gr_sdr_source_impl(device, stream, channels, sig));
}

gr_sdr_source_impl::gr_sdr_source_impl(
    SoapySDR::Device *device,
    SoapySDR::Stream *stream,
    const std::vector<size_t> &channels,
    const gr::io_signature::sptr sig):
    gr::sync_block("gr::sdr::source", sig, gr::io_signature::make(0, 0, 0)),
    d_device(device),
    d_stream(stream),
    d_channels(channels)
{
    return;
}

gr_sdr_source_impl::~gr_sdr_source_impl(void)
{
    d_device->closeStream(d_stream);
    SoapySDR::Device::unmake(d_device);
}

void gr_sdr_source_impl::set_frontend_map(const std::string &mapping)
{
    return d_device->setFrontendMapping(SOAPY_SDR_RX, mapping);
}

std::string gr_sdr_source_impl::get_frontend_map()
{
    return d_device->getFrontendMapping(SOAPY_SDR_RX);
}

void gr_sdr_source_impl::set_samp_rate(double rate)
{
    BOOST_FOREACH(const size_t chan, d_channels)
    {
        d_device->setSampleRate(SOAPY_SDR_RX, chan, rate);
    }
}

double gr_sdr_source_impl::get_samp_rate(void)
{
    return d_device->getSampleRate(SOAPY_SDR_RX, d_channels.front());
}

std::vector<double> gr_sdr_source_impl::get_samp_rates(void)
{
    return d_device->listSampleRates(SOAPY_SDR_RX, d_channels.front());
}

void gr_sdr_source_impl::set_center_freq(double freq, size_t chan)
{
    return d_device->setFrequency(SOAPY_SDR_RX, d_channels.at(chan), freq);
}

double gr_sdr_source_impl::get_center_freq(size_t chan)
{
    return d_device->getFrequency(SOAPY_SDR_RX, d_channels.at(chan));
}

std::vector<gr::sdr::range_t> gr_sdr_source_impl::get_freq_range(size_t chan)
{
    return toRanges(d_device->getFrequencyRange(SOAPY_SDR_RX, d_channels.at(chan)));
}

void gr_sdr_source_impl::set_gain(double gain, size_t chan)
{
    return d_device->setGain(SOAPY_SDR_RX, d_channels.at(chan), gain);
}

void gr_sdr_source_impl::set_gain(double gain, const std::string &name, size_t chan)
{
    return d_device->setGain(SOAPY_SDR_RX, d_channels.at(chan), name, gain);
}

double gr_sdr_source_impl::get_gain(size_t chan)
{
    return d_device->getGain(SOAPY_SDR_RX, d_channels.at(chan));
}

double gr_sdr_source_impl::get_gain(const std::string &name, size_t chan)
{
    return d_device->getGain(SOAPY_SDR_RX, d_channels.at(chan), name);
}

std::vector<std::string> gr_sdr_source_impl::get_gain_names(size_t chan)
{
    return d_device->listGains(SOAPY_SDR_RX, d_channels.at(chan));
}

gr::sdr::range_t gr_sdr_source_impl::get_gain_range(size_t chan)
{
    return toRange(d_device->getGainRange(SOAPY_SDR_RX, d_channels.at(chan)));
}

gr::sdr::range_t gr_sdr_source_impl::get_gain_range(const std::string &name, size_t chan)
{
    return toRange(d_device->getGainRange(SOAPY_SDR_RX, d_channels.at(chan), name));
}

void gr_sdr_source_impl::set_antenna(const std::string &ant, size_t chan)
{
    return d_device->setAntenna(SOAPY_SDR_RX, d_channels.at(chan), ant);
}

std::string gr_sdr_source_impl::get_antenna(size_t chan)
{
    return d_device->getAntenna(SOAPY_SDR_RX, d_channels.at(chan));
}

std::vector<std::string> gr_sdr_source_impl::get_antennas(size_t chan)
{
    return d_device->listAntennas(SOAPY_SDR_RX, d_channels.at(chan));
}

void gr_sdr_source_impl::set_bandwidth(double bandwidth, size_t chan)
{
    return d_device->setBandwidth(SOAPY_SDR_RX, d_channels.at(chan), bandwidth);
}

double gr_sdr_source_impl::get_bandwidth(size_t chan)
{
    return d_device->getBandwidth(SOAPY_SDR_RX, d_channels.at(chan));
}

std::vector<double> gr_sdr_source_impl::get_bandwidth_range(size_t chan)
{
    return d_device->listBandwidths(SOAPY_SDR_RX, d_channels.at(chan));
}

void gr_sdr_source_impl::set_dc_offset(const std::complex<double> &offset, size_t chan)
{
    return d_device->setDCOffset(SOAPY_SDR_RX, d_channels.at(chan), offset);
}

void gr_sdr_source_impl::set_iq_balance(const std::complex<double> &correction, size_t chan)
{
    return d_device->setIQBalance(SOAPY_SDR_RX, d_channels.at(chan), correction);
}

void gr_sdr_source_impl::set_time_source(const std::string &source)
{
    return d_device->setTimeSource(source);
}

std::string gr_sdr_source_impl::get_time_source()
{
    return d_device->getTimeSource();
}

std::vector<std::string> gr_sdr_source_impl::get_time_sources()
{
    return d_device->listTimeSources();
}

void gr_sdr_source_impl::set_clock_source(const std::string &source)
{
    return d_device->setClockSource(source);
}

std::string gr_sdr_source_impl::get_clock_source()
{
    return d_device->getClockSource();
}

std::vector<std::string> gr_sdr_source_impl::get_clock_sources()
{
    return d_device->listClockSources();
}

double gr_sdr_source_impl::get_clock_rate()
{
    return d_device->getMasterClockRate();
}

void gr_sdr_source_impl::set_clock_rate(double rate)
{
    return d_device->setMasterClockRate(rate);
}

bool gr_sdr_source_impl::start(void)
{
    return d_device->activateStream(d_stream) == 0;
}

bool gr_sdr_source_impl::stop(void)
{
    return d_device->deactivateStream(d_stream) == 0;
}

int gr_sdr_source_impl::work(int noutput_items,
           gr_vector_const_void_star &,
           gr_vector_void_star &output_items)
{

    //TODO set tags from flags and time

    int flags = 0;
    long long timeNs = 0;
    const long timeoutUs = 10000; //10ms
    return d_device->readStream(d_stream, &output_items[0], noutput_items, flags, timeNs, timeoutUs);
}

