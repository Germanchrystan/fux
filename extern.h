#pragma once

// #include <stddef.h>
#include "export.h"
#include "Remark/Remark.h"
#include "Notation/Notation.h"
#include "Analyzer/Analyzer.h"

// Library functions
extern "C" {
  EXPORT Analyzer* CreateAnalyzerWithDummyModule(void);
  EXPORT void FreeRemarkArray(RemarkArray a);
  EXPORT RemarkArray Analyze(const Analyzer* analyzer, const MusicPiece* piece);
}