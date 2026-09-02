#include "Notation.h"

Interval getAbsolutePitchDifference(NoteEvent *note1, NoteEvent *note2)
{
  int result = note1->pitch.absPitch - note2->pitch.absPitch;
  if (result > 12) result %= 12;
  
  IntervalQuality q = result > 0 ? (IntervalQuality)result : (IntervalQuality)(result * -1);
  int direction = result >= 0 ? 1 : -1;

  Interval interval;
  interval.direction = direction;
  interval.quality = q;
  return interval;
}