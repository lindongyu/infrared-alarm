#ifndef __SPEAKER_H_
#define __SPEAKER_H_
#include "iostm8s003f3.h"

extern unsigned char speaker,flag_speaker_on, flag_speaker_off,somebody;

void work_gongzuo(void);
void work_anzhuang(void);
void speaker_on(void);
void speaker_off(void);

#endif