#include <aio.h>
#include <aio_data.h>
#include <aio_display.h>
#include <aio_export.h>
#include <aio_frequency.h>
#include <amplitude.h>

#include <pthread.h>
#include <stdio.h>

#include <CoreAudio/CoreAudio.h>

unsigned char average = 1;
float amplitude_display = 0.95f;

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

  if (
    aio_data->initialized == 0 ||
    (aio_data->mode == export_play && aio_data->exporting == 0)
  ) {
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
    float value_average = 0.0f;
    unsigned int length_value_average = 10;
    unsigned int frame = 0;
    
    for (
      unsigned long int index_buffer_out = 0;
      index_buffer_out < size_buffer_out;
      ++index_buffer_out
    ) {
      unsigned long int channel = index_buffer_out % count_channel_out;

      if (channel == 0) {
        float frequency = aio_frequency_get(
          aio_data,
          index_file_input
        );

        cer0_oscillator_frequency_set(
          &aio_data->oscillator,
          frequency
        );

        value = cer0_oscillator_poll(
          &aio_data->oscillator
        );

        if (aio_data->visualizer != 0) {
          if (average == 0) {
            aio_display_next(
              &aio_data->display
            );

            aio_display_update(
              &aio_data->display,
              value
            );
          } else {
            value_average += value;

            if (++frame >= length_value_average) {
              value_average = (
                value_average / ((float)length_value_average)
              );

              aio_display_next(
                &aio_data->display
              );

              aio_display_update(
                &aio_data->display,
                value * amplitude_display
              );

              frame = 0;
              value_average = 0.0f;
            }
          }
        }
      }

      float value_output = value * amplitude;

      buffer_out[index_buffer_out] = (
        value_output
      );

      if (aio_data->mode == export_play) {
        aio_export_write(
          aio_data->file_output,
          value_output
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

        if (
          index_file_input == 0 &&
          aio_data->mode == export_play
        ) {
          aio_data->exporting = 0;

          pthread_mutex_unlock(
            &mutex_exporting
          );
        }
      } 
    }
  }

  if (aio_data->visualizer != 0) {
    aio_display_render(
      &aio_data->display
    );
  }

  return 0;
}
