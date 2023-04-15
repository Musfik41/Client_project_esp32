#ifndef BLINK_TIMES_H
#define BLINK_TIMES_H

const unsigned long SECONDS = 1;
const unsigned long times = SECONDS * 60;

//################################################### All values are stored in Minutes ##############################################################

extern unsigned long blinkTimes[24] = {
  1 * times,   // On Sequence 1 (in minutes)
  1 * times,   // Off Sequence 2 (in minutes)
  
  2 * times,   // On Sequence 3 (in minutes)
  1 * times,   // Off Sequence 4 (in minutes)
  
  1 * times,   // On Sequence 5 (in minutes)
  1 * times,   // Off Sequence 6 (in minutes)
  
  2 * times,   // On Sequence 7 (in minutes)
  1 * times,   // Off Sequence 8 (in minutes)
  
  1 * times,   // On Sequence 9 (in minutes)
  1 * times,   // Off Sequence 10 (in minutes)
  
  2 * times,   // On Sequence 11 (in minutes)
  1 * times,   // Off Sequence 12 (in minutes)
  
  1 * times,   // On Sequence 13 (in minutes)
  1 * times,   // Off Sequence 14 (in minutes)
  
  2 * times,   // On Sequence 15 (in minutes)
  1 * times,   // Off Sequence 16 (in minutes)
  
  1 * times,   // On Sequence 17 (in minutes)
  1 * times,   // Off Sequence 18 (in minutes)
  
  2 * times,   // On Sequence 19 (in minutes)
  1 * times,   // Off Sequence 20 (in minutes)
  
  1 * times,   // On Sequence 21 (in minutes)
  1 * times,   // Off Sequence 22 (in minutes)
  
  2 * times,   // On Sequence 23 (in minutes)
  1 * times,   // Off Sequence 24 (in minutes)

  
};

#endif
