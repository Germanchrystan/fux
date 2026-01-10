#pragma once
// #include <stdlib.h>
#include "../Remark/Remark.h"

typedef struct 
{
  int pitch;
  int octave;
  int absPitch;
} Pitch;

typedef struct 
{
  Pitch pitch;
  int startTime;
  int duration;
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
