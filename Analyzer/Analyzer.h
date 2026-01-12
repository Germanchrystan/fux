#pragma once

#include <stdlib.h>

#include "../notation/Notation.h"
#include "../remark/Remark.h"
#include "../export.h"

typedef RemarkArray(*AnalyzerModule)(const MusicPiece* piece);

typedef struct {
  size_t numModules;
  AnalyzerModule* modules;
} AnalyzerModuleList;

typedef struct
{
  const char* name;
  AnalyzerModuleList modules;
} Analyzer;

EXPORT RemarkArray AnalyzeMusicPiece(const Analyzer* analyzer, const MusicPiece* piece);
EXPORT Analyzer* NewAnalyzer(const char* name, AnalyzerModuleList modules);
EXPORT void FreeAnalyzer(Analyzer* analyzer);
EXPORT Analyzer* AddModule(Analyzer* analyzer, AnalyzerModule module);
EXPORT Analyzer* AddModules(Analyzer* analyzer, AnalyzerModule* modules, size_t numModules);