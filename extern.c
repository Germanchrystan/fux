#include <stdlib.h>

#include "Notation/Notation.h"
#include "Analyzer/Analyzer.h"
#include "Modules/modules.h"
#include "export.h"

EXPORT Analyzer* CreateAnalyzerWithDummyModule(void)
{
    AnalyzerModuleList emptyList = { 0, NULL };
    Analyzer* analyzer = NewAnalyzer("DummyAnalyzer", emptyList);
    AddModule(analyzer, DummyModule);
    return analyzer;
}

EXPORT void FreeRemarkArray(RemarkArray a)
{
  free(a.data);
}

EXPORT RemarkArray Analyze(const Analyzer *analyzer, const MusicPiece *piece)
{
  return AnalyzeMusicPiece(analyzer, piece);
}
