#include <aio.h>
#include <aio_data.h>
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

  struct aio_data* aio_data = (struct aio_data*) data;

  if (aio_data->initialized == 0) {
    return 0;
  }

  unsigned int index_file_input = 0;

  for (
    unsigned long int index_buffer = 0;
    index_buffer < count_buffer;
    ++index_buffer
  ) {
    AudioBuffer audio_buffer_current = buffer_list_audio_out->mBuffers[index_buffer];

    float *buffer_out = audio_buffer_current.mData;
    unsigned long int size_buffer_out = audio_buffer_current.mDataByteSize / sizeof(float);
    unsigned long int count_channel_out = audio_buffer_current.mNumberChannels;

    float value = 0.0f;
    
    for (
      unsigned long int index_buffer_out = 0;
      index_buffer_out < size_buffer_out;
      ++index_buffer_out
    ) {
      unsigned long int channel = index_buffer_out % count_channel_out;

      if (channel == 0) {
        unsigned char byte_file_input = getc(
          aio_data->file_inputs[index_file_input]
        );

        unsigned int index_note = byte_file_input % aio_data->length_note_table;

        cer0_oscillator_frequency_set(
          &aio_data->oscillator,
          aio_data->note_table[
            index_note
          ]
        );

        value = cer0_oscillator_poll(
          &aio_data->oscillator
        );
      }
      
      if (
        feof(
          aio_data->file_inputs[index_file_input]
        )
      ) {
        rewind(
          aio_data->file_inputs[index_file_input]
        );

        index_file_input = (
          index_file_input + 1
        ) % aio_data->length_file_inputs;
      }

      buffer_out[index_buffer_out] = (
        value * amplitude
      );
    }
  }

  return 0;
}
