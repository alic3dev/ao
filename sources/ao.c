#include <ao.h>
#include <aio.h>

#include <stdio.h>

#include <cer0.h>

int main(
  int count_parameters,
  char** parameters
) {
  if (count_parameters != 2) {
    fprintf(
      stderr,
      "usage: ao path_file_input\n"
    );

    return 1;
  }

  FILE* file_input = fopen(
    parameters[1],
    "rb"
  );

  if (!file_input) {
    fprintf(
      stderr,
      "unable_to_open:%s\n",
      parameters[1]
    );

    return 2;
  }

  struct cer0_audio_output output_audio;
  cer0_audio_output_initialize(
    &output_audio,
    aio,
    file_input
  );

  printf("press enter to quit:");
  getc(stdin);
  
  fclose(file_input);

  cer0_audio_output_destroy(
    &output_audio
  );

  return 0;
}
