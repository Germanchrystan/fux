#pragma once

// #include <stddef.h>
#include "export.h"
#include "remark/remark.h"
#include "notation/notation.h"
#include "analyzer/analyzer.h"

// Library functions
extern "C" {
  EXPORT Analyzer* CreateAnalyzer(void);
  EXPORT void FreeRemarkArray(RemarkArray a);
  EXPORT RemarkArray Analyze(const Analyzer* analyzer, const MusicPiece* piece);
}