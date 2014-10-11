"""
Copyright 2010-2014 Free Software Foundation, Inc.

This file is part of GNU Radio

GNU Radio Companion is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

GNU Radio Companion is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
"""

MAIN_TMPL = """\
<?xml version="1.0"?>
<block>
	<name>SDR $sourk.title()</name>
	<key>sdr_$(sourk)</key>
	<category>SDR Blocks</category>
	<throttle>1</throttle>
	<import>from gnuradio import sdr</import>
	<import>import time</import>
	<make>sdr.$(sourk)(\$dev_addr, "\$type", \$stream_chans, \$stream_args)
########################################################################
\#if \$clock_rate()
self.\$(id).set_clock_rate(\$clock_rate)
\#end if
########################################################################
\#if \$clock_source()
self.\$(id).set_clock_source(\$clock_source)
\#end if
########################################################################
\#if \$time_source()
self.\$(id).set_time_source(\$time_source)
\#end if
########################################################################
\#if \$frontend_map()
self.\$(id).set_frontend_map(\$frontend_map)
\#end if
########################################################################
self.\$(id).set_samp_rate(\$samp_rate)
#for $n in range($max_nchan)
\#if \$nchan() > $n
self.\$(id).set_center_freq(\$center_freq$(n), $n)
self.\$(id).set_gain(\$gain$(n), $n)
	\#if \$ant$(n)()
self.\$(id).set_antenna(\$ant$(n), $n)
	\#end if
	\#if \$bw$(n)()
self.\$(id).set_bandwidth(\$bw$(n), $n)
	\#end if
\#end if
#end for
</make>
	<callback>set_samp_rate(\$samp_rate)</callback>
	#for $n in range($max_nchan)
	<callback>set_center_freq(\$center_freq$(n), $n)</callback>
	<callback>set_gain(\$gain$(n), $n)</callback>
	<callback>set_antenna(\$ant$(n), $n)</callback>
	<callback>set_bandwidth(\$bw$(n), $n)</callback>
	#end for
	<param>
		<name>$(direction.title())put Type</name>
		<key>type</key>
		<type>enum</type>
		<option>
			<name>Complex float32</name>
			<key>CF32</key>
			<opt>type:fc32</opt>
		</option>
		<option>
			<name>Complex int16</name>
			<key>CS16</key>
			<opt>type:sc16</opt>
		</option>
	</param>
	<param>
		<name>Stream args</name>
		<key>stream_args</key>
		<value>{}</value>
		<type>raw</type>
		<hide>
			\#if \$stream_args()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
	<param>
		<name>Stream channels</name>
		<key>stream_chans</key>
		<value>[0]</value>
		<type>int_vector</type>
		<hide>
			\#if \$stream_chans()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
	<param>
		<name>Address</name>
		<key>dev_addr</key>
		<value>{}</value>
		<type>raw</type>
		<hide>
			\#if \$dev_addr()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
	<param>
		<name>Clock Rate (Hz)</name>
		<key>clock_rate</key>
		<value>0.0</value>
		<type>real</type>
		<hide>\#if \$clock_rate() then 'none' else 'part'#</hide>
		<option>
			<name>Default</name>
			<key>0.0</key>
		</option>
	</param>
	<param>
		<name>Clock Source</name>
		<key>clock_source</key>
		<value></value>
		<type>string</type>
		<hide>
			\#if \$clock_source()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
	<param>
		<name>Time Source</name>
		<key>time_source</key>
		<value></value>
		<type>string</type>
		<hide>
			\#if \$time_source()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
	<param>
		<name>Frontend map</name>
		<key>frontend_map</key>
		<value></value>
		<type>string</type>
		<hide>
			\#if \$frontend_map()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
	<param>
		<name>Num Channels</name>
		<key>nchan</key>
		<value>1</value>
		<type>int</type>
		#for $n in range(1, $max_nchan+1)
		<option>
			<name>$(n)</name>
			<key>$n</key>
		</option>
		#end for
	</param>
	<param>
		<name>Samp Rate (Sps)</name>
		<key>samp_rate</key>
		<value>samp_rate</value>
		<type>real</type>
	</param>
	$params
	<check>$max_nchan >= \$nchan</check>
	<check>\$nchan > 0</check>
	<check>(not \$stream_chans()) or (\$nchan == len(\$stream_chans))</check>
	<$sourk>
		<name>$direction</name>
		<type>\$type.type</type>
		<nports>\$nchan</nports>
	</$sourk>
	<doc>
	</doc>
</block>
"""

PARAMS_TMPL = """
	<param>
		<name>Ch$(n): Center Freq (Hz)</name>
		<key>center_freq$(n)</key>
		<value>0</value>
		<type>real</type>
		<hide>\#if \$nchan() > $n then 'none' else 'all'#</hide>
	</param>
	<param>
		<name>Ch$(n): Gain (dB)</name>
		<key>gain$(n)</key>
		<value>0</value>
		<type>real</type>
		<hide>\#if \$nchan() > $n then 'none' else 'all'#</hide>
	</param>
	<param>
		<name>Ch$(n): Antenna</name>
		<key>ant$(n)</key>
		<value></value>
		<type>string</type>
		<hide>
			\#if not \$nchan() > $n
				all
			\#elif \$ant$(n)()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
	<param>
		<name>Ch$(n): Bandwidth (Hz)</name>
		<key>bw$(n)</key>
		<value>0</value>
		<type>real</type>
		<hide>
			\#if not \$nchan() > $n
				all
			\#elif \$bw$(n)()
				none
			\#else
				part
			\#end if
		</hide>
	</param>
"""

def parse_tmpl(_tmpl, **kwargs):
	from Cheetah import Template
	return str(Template.Template(_tmpl, kwargs))

max_num_channels = 4

if __name__ == '__main__':
	import sys
	for file in sys.argv[1:]:
		if file.endswith ('source.xml'):
			sourk = 'source'
			direction = 'out'
		elif file.endswith ('sink.xml'):
			sourk = 'sink'
			direction = 'in'
		else: raise Exception, 'is %s a source or sink?'%file

		params = ''.join([parse_tmpl(PARAMS_TMPL, n=n) for n in range(max_num_channels)])
		open(file, 'w').write(parse_tmpl(MAIN_TMPL,
			max_nchan=max_num_channels,
			params=params,
			sourk=sourk,
			direction=direction,
		))
