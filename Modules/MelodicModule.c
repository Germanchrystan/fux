#include <math.h>
#include "modules.h"

const int MAX_JUMP = 7;

typedef  RemarkArray(*melodicModuleFunction)(const Voice* voice);
static melodicModuleFunction melodicChecks[] = {
  checkOutOfRegister,
  checkJumpCompensation,
  checkTritoneRange
};

RemarkArray MelodicModule(const MusicPiece* piece)
{
    RemarkArray remarks = newRemarkArray(0);

    for (size_t v = 0; v < piece->numVoices; v++) 
    {
      Voice* voice = &piece->voices[v];
      for (size_t i = 0; i < sizeof(melodicChecks)/sizeof(melodicModuleFunction); i++) 
      {
        RemarkArray checkRemarks = melodicChecks[i](voice);
        fuseRemarks(&remarks, &checkRemarks);
        freeRemarkArray(checkRemarks);
      }
    }

    return remarks;
}

static RemarkArray checkJumpCompensation(const Voice* voice) 
{
    RemarkArray remarks = newRemarkArray(0);

    for (size_t i = 1; i < voice->numNotes - 2; i++) 
    {
      int currentPitch = voice->notes[i].pitch.absPitch;
      int nextPitch = voice->notes[i + 1].pitch.absPitch;

      int interval = nextPitch - currentPitch;
      if (abs(interval) > MAX_JUMP)
      {
        int nextNextPitch = voice->notes[i + 2].pitch.absPitch;
        int compensation = nextNextPitch - nextPitch;
        if(sign(compensation) == sign(interval))
        {
          Remark remark = {0};
          remark.voice = voice->id;
          remark.note = i + 1; // index of the note causing the issue
          remark.gravity = JumpCompensationGravity;
          remark.errorCode = JumpCompensation;

          addRemark(&remarks, remark);
        }
      }
    }

    return remarks;
}

static RemarkArray checkOutOfRegister(const Voice* voice) 
{
    RemarkArray remarks = newRemarkArray(0);

    for (size_t i = 0; i < voice->numNotes; i++) 
    {
      int pitch = voice->notes[i].pitch.absPitch;
      if (pitch > voice->registerData.higher.absPitch || pitch < voice->registerData.lower.absPitch)
      {
        Remark remark = {0};
        remark.voice = voice->id;
        remark.note = i; // index of the note causing the issue
        remark.gravity = OutOfRegisterGravity;
        remark.errorCode = OutOfRegister;

        addRemark(&remarks, remark);
      }
    }

    return remarks;
}

static RemarkArray checkTritoneRange(const Voice* voice) 
{
    RemarkArray remarks = newRemarkArray(0);

    for (size_t i = 0; i < voice->numNotes - 1; i++) 
    {
      int currentPitch = voice->notes[i].pitch.absPitch;
      int nextPitch = voice->notes[i + 1].pitch.absPitch;
      
      int interval = abs(nextPitch - currentPitch);
      if (interval != 0)
      {
        int direction = sign(interval);
        int j = 0;
        int sameDirection = 0;
        while(sameDirection && (i + j) < voice->numNotes - 1)
        {
          j++;
          int followingPitch = voice->notes[i + j].pitch.absPitch;
          int nextInterval = followingPitch - nextPitch;
          sameDirection = sign(nextInterval) == direction;
        }

        int endOfRangePitch = voice->notes[i + j - 1].pitch.absPitch;

        if (abs(currentPitch - endOfRangePitch) == 6)
        {
          Remark remark;
          remark.voice = voice->id;
          remark.note = i + j - 1; // index of the note causing the issue
          remark.gravity = TritoneInPassageGravity;
          remark.errorCode = TritoneInPassage;

          addRemark(&remarks, remark);
        }
        i += j - 1;
      }
    }

    return remarks;
}