#include "module.h"
#include "modules.h"
#include <stdbool.h>

void compareVoices(RemarkArray *remarkArray, Voice *voice1, Voice *voice2);
void compareNotes(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2);

static NoteEvent *prevNoteEvent1 = NULL;
static NoteEvent *prevNoteEvent2 = NULL;

RemarkArray CounterpointModule(const MusicPiece* piece)
{
  RemarkArray *arr = newRemarkArray();
  for (int i = 0; i < piece->numVoices; i++)
  {
    Voice *voice1 = &piece->voices[i];
    for (int j = i + 1; j < piece->numVoices; j++)
    {
      Voice *voice2 = &piece->voices[j];
      compareVoices(arr, voice1, voice2);
    }
  }

  return *arr;
}

void compareVoices(RemarkArray *remarkArray, Voice *voice1, Voice *voice2)
{
  Voice *voiceMain = voice1;
  int noteMainIndex = 0;
  int noteMainCount = voice1->numNotes;
  Voice *voiceSec = voice2;
  int noteSecIndex = 0;
  int noteSecCount = voice2->numNotes;
  bool shouldSwitch = false;
  
  // Main loop
  while(noteMainIndex < noteMainCount)
  {
    NoteEvent noteMain = voiceMain->notes[noteMainIndex];
    float totalSampleDuration = noteMain.startTime + noteMain.duration;
    float sampleDuration = noteMain.startTime;
    shouldSwitch = false;
    
    int noteSecSampleCount = 0;
    NoteEvent **noteSecSample = (NoteEvent**)calloc(sizeof(NoteEvent*), noteSecSampleCount);
    while (sampleDuration < totalSampleDuration)
    {
      NoteEvent noteSec = voice2->notes[noteSecIndex];
      float newSampleDuration = sampleDuration + noteSec.duration;
      if (newSampleDuration > totalSampleDuration)
      {
        shouldSwitch = true;
        break;
      }
      sampleDuration = newSampleDuration;
      noteSecSample = (NoteEvent**)realloc(noteSecSample, sizeof(NoteEvent*) * noteSecSampleCount + 1);
      noteSecSample[noteSecSampleCount++] = &noteSec;
      noteSecIndex++;
    }
    // Compare main note against secundary sample notes
    for(int i = 0; i < noteSecSampleCount; i++)
    {
      compareNotes(remarkArray, noteMain, *noteSecSample[i]);
    }
    
    // Switch voices
    if (shouldSwitch)
    {
      Voice *tempVoice = voiceMain;
      voiceMain = voiceSec;
      voiceSec = tempVoice;
      int tempNoteIndex = noteMainIndex;
      noteMainIndex = noteSecIndex;
      noteSecIndex = tempNoteIndex;
      int tempMainCount = noteMainCount;
      noteMainCount = noteSecCount;
      noteSecCount = tempMainCount;
    }
    free(noteSecSample);
  }
}

// TODO: Note event list should be linked, in order to compare previous notes
static void compareNotes(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2)
{
  Interval interval = getAbsolutePitchDifference(&note1, &note2);
  IntervalQuality quality = interval.quality;
  if (note1.startTime == note2.startTime)
  {
    NoteDealing dealing = FirstSpecies.registry[quality];
    if (dealing != NULL)
    {
      dealing(remarkArray, note1, note2);
    }
  }
}

