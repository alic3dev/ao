#include <aio.h>
#include <amplitude.h>

#include <stdio.h>

#include <CoreAudio/CoreAudio.h>

OSStatus aio(
  AudioObjectID id_audio_object,
  const AudioTimeStamp* timestamp_audio,
  const AudioBufferList* buffer_list_audio_in,
  const AudioTimeStamp* timestamp_audio_in,
  AudioBufferList* buffer_list_audio_out,
  const AudioTimeStamp* timestamp_audio_out,
  void* data
) {
  unsigned long int count_buffer = buffer_list_audio_out->mNumberBuffers;

  FILE* data_file = (FILE*) data;

  for (
    unsigned long int index_buffer = 0;
    index_buffer < count_buffer;
    ++index_buffer
  ) {
    AudioBuffer audio_buffer_current = buffer_list_audio_out->mBuffers[index_buffer];

    float *buffer_out = audio_buffer_current.mData;
    unsigned long int size_buffer_out = audio_buffer_current.mDataByteSize / sizeof(float);
    unsigned long int count_channel_out = audio_buffer_current.mNumberChannels;

    unsigned char byte;
    
    for (
      unsigned long int index_buffer_out = 0;
      index_buffer_out < size_buffer_out;
      ++index_buffer_out
    ) {
      unsigned long int channel = index_buffer_out % count_channel_out;

      if (channel == 0) {
        byte = getc(data_file);
      }
      
      if (feof(data_file)) {
        rewind(data_file);
      }

      buffer_out[index_buffer_out] = (
        (
          ((float)(byte) / 127.5f)
           - 1.0f
        ) * amplitude
      );
    }
  }

  return 0;
}
