#!/usr/bin/env python
#
# Copyright 2014 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

from gnuradio import gr, gr_unittest

#local import
import sdr

class test_sdr(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_000_import (self):
        """Just see if we can import the module...
        They may not have a SDR device connected, etc.  Don't try to run anything"""
        pass

    def test_range_type (self):
        r0 = sdr.range_t()
        self.assertEqual(r0.minimum(), 0.0)
        self.assertEqual(r0.maximum(), 0.0)

        r1 = sdr.range_t(-100.0, 200.5)
        self.assertEqual(r1.minimum(), -100.0)
        self.assertEqual(r1.maximum(), 200.5)

    def test_has_symbols (self):
        self.assertTrue(sdr.source)
        self.assertTrue(sdr.sink)

if __name__ == '__main__':
    gr_unittest.run(test_sdr, "test_sdr.xml")
