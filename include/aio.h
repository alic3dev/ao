#ifndef __aio_h
#define __aio_h

#include <CoreAudio/CoreAudio.h>

OSStatus aio(
 AudioObjectID,
 const AudioTimeStamp*,
 const AudioBufferList*,
 const AudioTimeStamp*,
 AudioBufferList*,
 const AudioTimeStamp*,
 void *
);

#endif
