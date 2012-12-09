/* Lame.java
   A port of LAME for Android

   Copyright (c) 2010 Ethan Chen

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
/*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <android/log.h>
#include "gate-interface.h"
#include "SimpleGate.h"

JNIEXPORT jlong JNICALL Java_sa_dsp_Gate_newGate
  (JNIEnv *env, jclass clazz)
{
	__android_log_print(ANDROID_LOG_DEBUG, "libgate.so", "new instance");

	return (jlong) new chunkware_simple::SimpleGate();
}

JNIEXPORT void JNICALL Java_sa_dsp_Gate_setThresh
  (JNIEnv *env, jclass clazz, jlong obj, jdouble dB)
{
	chunkware_simple::SimpleGate *gate = (chunkware_simple::SimpleGate *) obj;
	gate->setThresh(dB);

	__android_log_print(ANDROID_LOG_DEBUG, "libgate.so", "thresh: %f", dB);
}

JNIEXPORT jdouble JNICALL Java_sa_dsp_Gate_getThresh
  (JNIEnv *env, jclass clazz, jlong obj)
{
	chunkware_simple::SimpleGate *gate = (chunkware_simple::SimpleGate *) obj;
	return gate->getThresh();
}

JNIEXPORT void JNICALL Java_sa_dsp_Gate_initRuntime
  (JNIEnv *env, jclass clazz, jlong obj)
{
	chunkware_simple::SimpleGate *gate = (chunkware_simple::SimpleGate *) obj;
	gate->initRuntime();

	__android_log_print(ANDROID_LOG_DEBUG, "libgate.so", "initRuntime");
}

JNIEXPORT void JNICALL Java_sa_dsp_Gate_processGate
  (JNIEnv *env, jclass clazz, jlong obj, jint bufferSize,
		  jshortArray pcm) {
	short *pcm_buf;
	chunkware_simple::SimpleGate *gate = (chunkware_simple::SimpleGate *) obj;

	pcm_buf = env->GetShortArrayElements(pcm, NULL);

	double d;
	for (int i = 0; i != bufferSize; i++) {
		d = pcm_buf[i];
		d /= 32768;

		gate->process(d);

		//__android_log_print(ANDROID_LOG_DEBUG, "libgate.so", "process: %d/%d", (int) (d * 32768), pcm_buf[i]);

		pcm_buf[i] = (int) (d * 32768);
	}

	env->ReleaseShortArrayElements(pcm, pcm_buf, 0);
}
