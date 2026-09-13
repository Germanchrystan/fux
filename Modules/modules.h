#pragma once
#include "../Analyzer/Analyzer.h"

typedef struct Disonance
{
  Voice *voice1;
  Voice *voice2;
  Interval interval;
  int note1Index;
  int note2Index;
} Disonance;


RemarkArray MelodicModule(const MusicPiece* piece);
RemarkArray CounterpointModule(const MusicPiece* piece);
// Flavour module will deal with not repeating notes, chords, intervals
RemarkArray FlavourModule(const MusicPiece* piece);