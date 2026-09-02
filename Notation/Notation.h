#pragma once
// #include <stdlib.h>
#include "../remark/Remark.h"

typedef enum IntervalQuality
{
  UNISON,
  MINOR_SECOND,
  MAJOR_SECOND,
  MINOR_THIRD,
  MAJOR_THIRD,
  FOURTH,
  TRITONE,
  FIFTH,
  MINOR_SIXTH,
  MAJOR_SIXTH,
  MINOR_SEVENTH,
  MAJOR_SEVENTH,
  OCTAVE
} IntervalQuality;

typedef struct
{
  IntervalQuality quality;
  int direction;
} Interval;

typedef struct 
{
  int pitch;
  int octave;
  int absPitch;
} Pitch;

typedef struct 
{
  float startTime;
  float duration;
  Pitch pitch;
} NoteEvent;

typedef struct
{
  const char* name;
  Pitch higher;
  Pitch lower;
} Register;

typedef struct 
{
  int id;
  Register registerData;
  NoteEvent* notes;
  size_t numNotes;
} Voice;

typedef struct 
{
  int numerator;
  int denominator;
} TimeSignature;

typedef struct
{
  Voice* voices;
  size_t numVoices;
  TimeSignature timeSignature;
  int bpm;
} MusicPiece;

Interval getAbsolutePitchDifference(NoteEvent *note1, NoteEvent *note2);