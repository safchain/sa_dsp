/* Compressor.java
Android Jni interface to "ChunkWare Music Software" audio compressor/gate/limiter filters

Copyright (c) 2012 Sylvain Afchain

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

package sa.dsp;

public class Compressor {
	private static final String COMPRESSOR_LIB = "compressor";

	private long instancePtr;
	
	static {
		System.loadLibrary(COMPRESSOR_LIB);
	}

	private static native long newCompressor();
	private static native void setThresh(long obj, double dB);
	private static native double getThresh(long obj);
	private static native void setRatio(long obj, double dB);
	private static native double getRatio(long obj);
	private static native void initRuntime(long obj);
	private static native void processCompressorMono(long obj, int size, short[] pcm);
	private static native void processCompressorStereo(long obj, int size, short[] pcmLeft, short[] pcmRight);
	private static native void processCompressorInterleaved(long obj, int size, short[] pcm);
	
	
	public Compressor () {
		instancePtr = newCompressor();
	}
	
	public void setThresh(double dB) {
		setThresh(instancePtr, dB);
	}
	
	public double getThresh() {
		return getThresh(instancePtr);
	}
	
	public void setRatio(double dB) {
		setRatio(instancePtr, dB);
	}
	
	public double getRatio() {
		return getRatio(instancePtr);
	}
	
	public void initRuntime () {
		initRuntime(instancePtr);
	}
	
	public void process(int size, short[] pcm) {
		processCompressorMono(instancePtr, size, pcm);
	}
	
	public void processInterleaved(int size, short[] pcm) {
		processCompressorInterleaved(instancePtr, size, pcm);
	}
	
	public void process(int size, short[] pcmLeft, short[] pcmRight) {
		processCompressorStereo(instancePtr, size, pcmLeft, pcmRight);
	}
}