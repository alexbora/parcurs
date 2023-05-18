/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : audio
 * @created     : Sâmbătă Mai 13, 2023 08:03:35 EEST
 */

#include <sys/fcntl.h>
#define MINIAUDIO_IMPLEMENTATION
#include "/Users/alex/dev/wx/miniaudio/miniaudio.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

void
data_callback(ma_device* pDevice, void* pOutput, const void* pInput,
              ma_uint32 frameCount)
{
  (void) pInput;

  ma_decoder* pDecoder = (ma_decoder*) pDevice->pUserData;
  if (pDecoder == NULL) { return; }

  ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
}

typedef struct {
  ma_decoder decoder;
  ma_device  device;
} Playback;

Playback*
init_playback(char** argv)
{
  Playback* playback = malloc(sizeof(Playback));
  ma_result result;
  /* ma_decoder       decoder; */
  ma_device_config deviceConfig;
  /* ma_device        device; */

  result = ma_decoder_init_file("/Users/alex/dev/wx/miniaudio/test.mp3", NULL,
                                &playback->decoder);

  deviceConfig                 = ma_device_config_init(ma_device_type_playback);
  deviceConfig.playback.format = playback->decoder.outputFormat;
  deviceConfig.playback.channels = playback->decoder.outputChannels;
  deviceConfig.sampleRate        = playback->decoder.outputSampleRate;
  deviceConfig.dataCallback      = data_callback;
  deviceConfig.pUserData         = &playback->decoder;

  result = ma_device_init(NULL, &deviceConfig, &playback->device);

  return playback;
}

void
play(Playback* p)
{
  if (ma_device_start(&p->device) != MA_SUCCESS) {
    printf("Failed to start playback device.\n");
    ma_device_uninit(&p->device);
    ma_decoder_uninit(&p->decoder);
    return;
  }

  printf("Press Enter to quit...");
  getchar();

  ma_device_uninit(&p->device);
  ma_decoder_uninit(&p->decoder);
}

void
play2(void* b, size_t sz)
{

  bool success = false;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  SDL_AudioStream* stream =
      SDL_NewAudioStream(AUDIO_S16, 1, 22050, AUDIO_F32, 2, 48000);
  SDL_AudioStreamPut(stream, b, sz);
  static Uint8* audio_pos;

  SDL_Delay(3000);
  /* getchar(); */
  SDL_AudioStreamFlush(stream);
}

int
main(int argc, char** argv)
{
  /* ma_result        result; */
  /* ma_decoder       decoder; */
  /* ma_device_config deviceConfig; */
  /* ma_device        device; */

  /* if (argc < 2) { */
  /*   printf("No input file.\n"); */
  /*   return -1; */

  /*   result = ma_decoder_init_file(argv[1], NULL, &decoder); */
  /*   if (result != MA_SUCCESS) { */
  /*     printf("Could not load file: %s\n", argv[1]); */
  /*     return -2; */
  /*   } */

  /*   deviceConfig = ma_device_config_init(ma_device_type_playback); */
  /*   deviceConfig.playback.format   = decoder.outputFormat; */
  /*   deviceConfig.playback.channels = decoder.outputChannels; */
  /*   deviceConfig.sampleRate        = decoder.outputSampleRate; */
  /*   deviceConfig.dataCallback      = data_callback; */
  /*   deviceConfig.pUserData         = &decoder; */

  /*   if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) { */
  /*     printf("Failed to open playback device.\n"); */
  /*     ma_decoder_uninit(&decoder); */
  /*     return -3; */
  /*   } */
  Playback* p = init_playback(argv);

  /* play(p); */
  /* if (ma_device_start(&p->device) != MA_SUCCESS) { */
  /*   printf("Failed to start playback device.\n"); */
  /*   ma_device_uninit(&p->device); */
  /*   ma_decoder_uninit(&p->decoder); */
  /*   return -4; */
  /* } */

  /* printf("Press Enter to quit..."); */
  /* getchar(); */

  /* ma_device_uninit(&p->device); */
  /* ma_decoder_uninit(&p->decoder); */
  char* b = malloc(16340);

  int fd = open("/Users/alex/dev/wx/miniaudio/test.mp3", O_RDONLY);

  size_t i = 0;
  while (i < 16340) {
    read(fd, b + i, 1);
    i++;
  }

  play2(b, 16340);
  return 0;
}
