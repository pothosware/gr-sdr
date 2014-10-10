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

#ifndef INCLUDED_GR_SDR_SOURCE_H
#define INCLUDED_GR_SDR_SOURCE_H

#include <gnuradio/sdr/api.h>
#include <gnuradio/sdr/types.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace sdr {

    class GR_SDR_API source : virtual public sync_block
    {
    public:
      typedef boost::shared_ptr<source> sptr;

      /*!
       * \brief Make a new SDR device source block (usually a radio receiver).
       *
       * The SDR device source block receives samples and writes to a stream.
       * The source block also provides API calls for receiver settings.
       *
       * \param addr the address args to identify the hardware
       * \param format the host sample format markup string
       * \param channels a list of channels on the device to use
       * \param args optional special key/value arguments
       * \return a new SDR device source block object
       */
      static sptr make(const gr::sdr::kwargs_t &addr = gr::sdr::kwargs_t(),
                       const std::string &format = "CF32",
                       const std::vector<size_t> &channels = std::vector<size_t>(),
                       const gr::sdr::kwargs_t &args = gr::sdr::kwargs_t());

      /*!
       * Set the frontend mapping.
       * \param mapping the subdev spec markup string
       */
      virtual void set_frontend_map(const std::string &mapping) = 0;

      /*!
       * Get the RX frontend mapping.
       * \return the frontend mapping in use
       */
      virtual std::string get_frontend_map() = 0;

      /*!
       * Set the sample rate for the SDR device.
       * \param rate a new rate in Sps
       */
      virtual void set_samp_rate(double rate) = 0;

      /*!
       * Get the sample rate for the SDR device.
       * This is the actual sample rate and may differ from the rate set.
       * \return the actual rate in Sps
       */
      virtual double get_samp_rate(void) = 0;

      /*!
       * Get the possible sample rates for the SDR device.
       * \return a range of rates in Sps
       */
      virtual std::vector<double> get_samp_rates(void) = 0;

      /*!
       * Tune the SDR device to the desired center frequency.
       * This is a wrapper around set center freq so that in this case,
       * the user can pass a single frequency in the call through swig.
       * \param freq the desired frequency in Hz
       * \param chan the channel index 0 to N-1
       * \return a tune result with the actual frequencies
       */
      virtual void set_center_freq(double freq, size_t chan = 0) = 0;

      /*!
       * Get the center frequency.
       * \param chan the channel index 0 to N-1
       * \return the frequency in Hz
       */
      virtual double get_center_freq(size_t chan = 0) = 0;

      /*!
       * Get the tunable frequency range.
       * \param chan the channel index 0 to N-1
       * \return the frequency range in Hz
       */
      virtual std::vector<gr::sdr::range_t> get_freq_range(size_t chan = 0) = 0;

      /*!
       * Set the gain for the dboard.
       * \param gain the gain in dB
       * \param chan the channel index 0 to N-1
       */
      virtual void set_gain(double gain, size_t chan = 0) = 0;

      /*!
       * Set the named gain on the dboard.
       * \param gain the gain in dB
       * \param name the name of the gain stage
       * \param chan the channel index 0 to N-1
       */
      virtual void set_gain(double gain,
                            const std::string &name,
                            size_t chan = 0) = 0;

      /*!
       * Get the actual dboard gain setting.
       * \param chan the channel index 0 to N-1
       * \return the actual gain in dB
       */
      virtual double get_gain(size_t chan = 0) = 0;

      /*!
       * Get the actual dboard gain setting of named stage.
       * \param name the name of the gain stage
       * \param chan the channel index 0 to N-1
       * \return the actual gain in dB
       */
      virtual double get_gain(const std::string &name, size_t chan = 0) = 0;

      /*!
       * Get the actual dboard gain setting of named stage.
       * \param chan the channel index 0 to N-1
       * \return the actual gain in dB
       */
      virtual std::vector<std::string> get_gain_names(size_t chan = 0) = 0;

      /*!
       * Get the settable gain range.
       * \param chan the channel index 0 to N-1
       * \return the gain range in dB
       */
      virtual gr::sdr::range_t get_gain_range(size_t chan = 0) = 0;

      /*!
       * Get the settable gain range.
       * \param name the name of the gain stage
       * \param chan the channel index 0 to N-1
       * \return the gain range in dB
       */
      virtual gr::sdr::range_t get_gain_range(const std::string &name, size_t chan = 0) = 0;

      /*!
       * Set the antenna to use.
       * \param ant the antenna string
       * \param chan the channel index 0 to N-1
       */
      virtual void set_antenna(const std::string &ant, size_t chan = 0) = 0;

      /*!
       * Get the antenna in use.
       * \param chan the channel index 0 to N-1
       * \return the antenna string
       */
      virtual std::string get_antenna(size_t chan = 0) = 0;

      /*!
       * Get a list of possible antennas.
       * \param chan the channel index 0 to N-1
       * \return a vector of antenna strings
       */
      virtual std::vector<std::string> get_antennas(size_t chan = 0) = 0;

      /*!
       * Set the bandpass filter on the RF frontend.
       * \param bandwidth the filter bandwidth in Hz
       * \param chan the channel index 0 to N-1
       */
      virtual void set_bandwidth(double bandwidth, size_t chan = 0) = 0;

      /*!
       * Get the bandpass filter setting on the RF frontend.
       * \param chan the channel index 0 to N-1
       * \return bandwidth of the filter in Hz
       */
      virtual double get_bandwidth(size_t chan = 0) = 0;

      /*!
       * Get the bandpass filter range of the RF frontend.
       * \param chan the channel index 0 to N-1
       * \return the range of the filter bandwidth in Hz
       */
      virtual std::vector<double> get_bandwidth_range(size_t chan = 0) = 0;

      /*!
       * Set a constant DC offset value.
       * The value is complex to control both I and Q.
       * Only set this when automatic correction is disabled.
       * \param offset the dc offset (1.0 is full-scale)
       * \param chan the channel index 0 to N-1
       */
      virtual void set_dc_offset(const std::complex<double> &offset, size_t chan = 0) = 0;

      /*!
       * Set the RX frontend IQ imbalance correction.
       * Use this to adjust the magnitude and phase of I and Q.
       *
       * \param correction the complex correction value
       * \param chan the channel index 0 to N-1
       */
      virtual void set_iq_balance(const std::complex<double> &correction, size_t chan = 0) = 0;

      /*!
       * Set the time source for the SDR device.
       * This sets the method of time synchronization,
       * typically a pulse per second or an encoded time.
       * Typical options for source: external, MIMO.
       * \param source a string representing the time source
       */
      virtual void set_time_source(const std::string &source) = 0;

      /*!
       * Get the currently set time source.
       * \return the string representing the time source
       */
      virtual std::string get_time_source() = 0;

      /*!
       * Get a list of possible time sources.
       * \return a vector of strings for possible settings
       */
      virtual std::vector<std::string> get_time_sources() = 0;

      /*!
       * Set the clock source for the SDR device.
       * This sets the source for a 10 Mhz reference clock.
       * Typical options for source: internal, external, MIMO.
       * \param source a string representing the clock source
       */
      virtual void set_clock_source(const std::string &source) = 0;

      /*!
       * Get the currently set clock source.
       * \return the string representing the clock source
       */
      virtual std::string get_clock_source() = 0;

      /*!
       * Get a list of possible clock sources.
       * \return a vector of strings for possible settings
       */
      virtual std::vector<std::string> get_clock_sources() = 0;

      /*!
       * Get the master clock rate.
       * \return the clock rate in Hz
       */
      virtual double get_clock_rate() = 0;

      /*!
       * Set the master clock rate.
       * \param rate the new rate in Hz
       */
      virtual void set_clock_rate(double rate) = 0;
    };

  } /* namespace sdr */
} /* namespace gr */

#endif /* INCLUDED_GR_SDR_SOURCE_H */
