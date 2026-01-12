#include <stdlib.h>

#include "modules.h"

RemarkArray DummyModule(const MusicPiece* piece)
{
    RemarkArray result;
    result.size = 1;
    result.data = (Remark*)malloc(sizeof(Remark));
    
    // Create a dummy remark
    result.data[0].voice = 0;
    result.data[0].note = 0;
    result.data[0].gravity = 0.5f;
    result.data[0].code = 99;  // dummy error code
    
    return result;
}