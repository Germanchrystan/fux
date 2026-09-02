#include <stdlib.h>

#include "notation/Notation.h"
#include "analyzer/Analyzer.h"
#include "modules/modules.h"
#include "export.h"

EXPORT Analyzer* CreateAnalyzer(void)
{
    AnalyzerModuleList emptyList = { 0, NULL };
    Analyzer* analyzer = NewAnalyzer("Analyzer", emptyList);
    AddModule(analyzer, MelodicModule);
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
