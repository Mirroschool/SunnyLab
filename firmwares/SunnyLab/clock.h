#ifndef _CLOCK_H
#define _CLOCK_H

#include <RtcDS3231.h>

RtcDS3231<TwoWire> rtc(Wire);
RtcDateTime now;

#endif
