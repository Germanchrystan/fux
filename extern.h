#pragma once

// #include <stddef.h>
#include "export.h"
#include "remark/Remark.h"
#include "notation/Notation.h"
#include "analyzer/Analyzer.h"

// Library functions
extern "C" {
  EXPORT Analyzer* CreateAnalyzerWithDummyModule(void);
  EXPORT void FreeRemarkArray(RemarkArray a);
  EXPORT RemarkArray Analyze(const Analyzer* analyzer, const MusicPiece* piece);
}