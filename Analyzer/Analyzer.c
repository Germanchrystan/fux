#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Analyzer.h"
#include "../Remark/Remark.h"
#include "../Notation/Notation.h"

static RemarkArray MergeRemarkArrays(RemarkArray* arrays, size_t numArrays)
{
    RemarkArray combined;
    size_t totalSize = 0;
    for (size_t i = 0; i < numArrays; i++) 
    {
        totalSize += arrays[i].size;
    }
    combined.size = totalSize;
    combined.data = (Remark*)malloc(totalSize * sizeof(Remark));

    size_t offset = 0;
    for (size_t i = 0; i < numArrays; i++) 
    {
        memcpy(combined.data + offset, arrays[i].data, arrays[i].size * sizeof(Remark));
        offset += arrays[i].size;
    }

    for (size_t i = 0; i < numArrays; i++) 
    {
        free(arrays[i].data);
    }
    free(arrays);
    return combined;
}

EXPORT RemarkArray AnalyzeMusicPiece(const Analyzer* analyzer, const MusicPiece* piece)
{
    RemarkArray allRemarks;
    allRemarks.data = NULL;
    allRemarks.size = 0;
    
    RemarkArray newRemarks;
    RemarkArray* tempArray = NULL;
    
    for (size_t i = 0; i < analyzer->modules.numModules; i++) {
        newRemarks = analyzer->modules.modules[i](piece);
        tempArray = (RemarkArray*)malloc(2 * sizeof(RemarkArray));
        tempArray[0] = allRemarks;
        tempArray[1] = newRemarks;
        allRemarks = MergeRemarkArrays(tempArray, 2);
    }

    return allRemarks;
}

EXPORT Analyzer* NewAnalyzer(const char* name, AnalyzerModuleList modules)
{
    Analyzer* analyzer = (Analyzer*)malloc(sizeof(Analyzer));
    if (analyzer == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for analyzer\n");
        return NULL;
    }
    analyzer->name = strdup(name);
    analyzer->modules = modules;
    return analyzer;
}

EXPORT void FreeAnalyzer(Analyzer* analyzer)
{
    free(analyzer->name);
    free(analyzer->modules.modules);
    free(analyzer);
}

EXPORT Analyzer* AddModule(Analyzer* analyzer, AnalyzerModule module)
{
    AnalyzerModule*temp =(AnalyzerModule*)realloc(analyzer->modules.modules, (analyzer->modules.numModules + 1) * sizeof(AnalyzerModule));
    if (temp == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for analyzer modules\n");
        return NULL;
    }
    analyzer->modules.modules = temp;
    analyzer->modules.modules[analyzer->modules.numModules] = module;
    analyzer->modules.numModules++;
    return analyzer;
}

EXPORT Analyzer* AddModules(Analyzer* analyzer, AnalyzerModule* modules, size_t numModules)
{
    AnalyzerModule* temp = (AnalyzerModule*)realloc(analyzer->modules.modules, (analyzer->modules.numModules + numModules) * sizeof(AnalyzerModule));
    if (temp == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for analyzer modules\n");
        return NULL;
    }

    analyzer->modules.modules = temp;
    memcpy(analyzer->modules.modules + analyzer->modules.numModules, modules, numModules * sizeof(AnalyzerModule));
    analyzer->modules.numModules += numModules;
    free(modules);
    return analyzer;
}
