sa_dsp
======

Android Jni interface to "ChunkWare Music Software" audio compressor/gate/limiter filters

Example:

```java
	import sa.dsp.Compressor;
	import sa.dsp.Gate;

	public void record {
		Compressor compressor = new Compressor();
		compressor.setThresh(-10.0d);
		compressor.setRatio(-4.0d);
		compressor.initRuntime();

		Gate gate = new Gate();
		gate.setThresh(-36.0d);
		gate.initRuntime();
		
		int bufferSize = AudioRecord.getMinBufferSize(RECORDER_SAMPLERATE,
					RECORDER_CHANNELS, RECORDER_AUDIO_ENCODING);
		
		AudioRecord recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
				RECORDER_SAMPLERATE, RECORDER_CHANNELS,
				RECORDER_AUDIO_ENCODING, bufferSize);
		
		recorder.startRecording();
		
		short pcm[] = new short[bufferSize];
		
		int read = 0;
		while (true) {
			read = recorder.read(pcm, 0, bufferSize);
			
			if (read > 0 && AudioRecord.ERROR_INVALID_OPERATION != read) {
				gate.process(read, pcm);
				compressor.process(read, pcm);
			}
		}
		
		recorder.stop();
		recorder.release();
	}
```