/* comp-interface.cpp
  
   Copyright (c) 2013 Sylvain Afchain

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
#include "comp-interface.h"
#include "SimpleComp.h"

JNIEXPORT jlong JNICALL Java_sa_dsp_Compressor_newCompressor
  (JNIEnv *env, jclass clazz)
{
	__android_log_print(ANDROID_LOG_DEBUG, "libcompressor.so", "new instance");

	return (jlong) new chunkware_simple::SimpleComp();
}

JNIEXPORT void JNICALL Java_sa_dsp_Compressor_setThresh
  (JNIEnv *env, jclass clazz, jlong obj, jdouble dB)
{
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;
	comp->setThresh(dB);

	__android_log_print(ANDROID_LOG_DEBUG, "libcompressor.so", "thresh: %f", dB);
}

JNIEXPORT jdouble JNICALL Java_sa_dsp_Compressor_getThresh
  (JNIEnv *env, jclass clazz, jlong obj)
{
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;
	return comp->getThresh();
}

JNIEXPORT void JNICALL Java_sa_dsp_Compressor_setRatio
  (JNIEnv *env, jclass clazz, jlong obj, jdouble dB)
{
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;
	comp->setRatio(dB);

	__android_log_print(ANDROID_LOG_DEBUG, "libcompressor.so", "ratio: %f", dB);

}

JNIEXPORT jdouble JNICALL Java_sa_dsp_Compressor_getRatio
  (JNIEnv *env, jclass clazz, jlong obj)
{
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;
	return comp->getRatio();
}

JNIEXPORT void JNICALL Java_sa_dsp_Compressor_initRuntime
  (JNIEnv *env, jclass clazz, jlong obj)
{
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;
	comp->initRuntime();

	__android_log_print(ANDROID_LOG_DEBUG, "libcompressor.so", "initRuntime");
}

JNIEXPORT void JNICALL Java_sa_dsp_Compressor_processCompressorMono
  (JNIEnv *env, jclass clazz, jlong obj, jint bufferSize,
		  jshortArray pcm) {
	short *pcm_buf;
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;

	pcm_buf = env->GetShortArrayElements(pcm, NULL);

	double d;
	for (int i = 0; i != bufferSize; i++) {
		d = pcm_buf[i];
		d /= 32768;

		comp->process(d);

		//__android_log_print(ANDROID_LOG_DEBUG, "libcompressor.so", "process: %d/%d", (int) (d * 32768), pcm_buf[i]);

		pcm_buf[i] = (int) (d * 32768);
	}

	env->ReleaseShortArrayElements(pcm, pcm_buf, 0);
}

JNIEXPORT void JNICALL Java_sa_dsp_Compressor_processCompressorStereo
  (JNIEnv *env, jclass clazz, jlong obj, jint bufferSize,
		  jshortArray pcmLeft, jshortArray pcmRight) {
	short *pcmleft_buf, *pcmright_buf;
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;

	pcmleft_buf = env->GetShortArrayElements(pcmLeft, NULL);
	pcmright_buf = env->GetShortArrayElements(pcmRight, NULL);


	double dl, dr;
	for (int i = 0; i != bufferSize; i++) {
		dl = pcmleft_buf[i];
		dl /= 32768;

		dr = pcmright_buf[i];
		dr /= 32768;

		comp->process(dl, dr);

		//__android_log_print(ANDROID_LOG_DEBUG, "libcompressor.so", "process: %d/%d", (int) (d * 32768), pcm_buf[i]);

		pcmleft_buf[i] = (int) (dl * 32768);
		pcmright_buf[i] = (int) (dr * 32768);
	}

	env->ReleaseShortArrayElements(pcmLeft, pcmleft_buf, 0);
	env->ReleaseShortArrayElements(pcmRight, pcmright_buf, 0);
}

JNIEXPORT void JNICALL Java_sa_dsp_Compressor_processCompressorInterleaved
  (JNIEnv *env, jclass clazz, jlong obj, jint bufferSize,
		  jshortArray pcm) {
	short *pcm_buf;
	chunkware_simple::SimpleComp *comp = (chunkware_simple::SimpleComp *) obj;

	pcm_buf = env->GetShortArrayElements(pcm, NULL);

	double dl, dr;
	for (int i = 0; i != bufferSize; i += 2) {
		dl = pcm_buf[i];
		dl /= 32768;

		dr = pcm_buf[i + 1];
		dr /= 32768;

		comp->process(dl, dr);

		//__android_log_print(ANDROID_LOG_DEBUG, "libcompressor.so", "process: %d/%d", (int) (d * 32768), pcm_buf[i]);

		pcm_buf[i] = (int) (dl * 32768);
		pcm_buf[i + 1] = (int) (dr * 32768);
	}

	env->ReleaseShortArrayElements(pcm, pcm_buf, 0);
}
