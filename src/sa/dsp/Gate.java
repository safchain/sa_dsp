/* Gate.java
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

public class Gate {
	private static final String GATE_LIB = "gate";

	private long instancePtr;
	
	static {
		System.loadLibrary(GATE_LIB);
	}

	private static native long newGate();
	private static native void setThresh(long obj, double dB);
	private static native double getThresh(long obj);
	private static native void initRuntime(long obj);
	private static native void processGate(long obj, int size, short[] pcm);
	
	public Gate () {
		instancePtr = newGate();
	}
	
	public void setThresh(double dB) {
		setThresh(instancePtr, dB);
	}
	
	public double getThresh() {
		return getThresh(instancePtr);
	}
	
	public void initRuntime () {
		initRuntime(instancePtr);
	}
	
	public void process(int size, short[] pcm) {
		processGate(instancePtr, size, pcm);
	}
}