#ifndef __AIO_H
#define __AIO_H

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

