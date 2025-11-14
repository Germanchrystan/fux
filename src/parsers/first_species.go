using fux.entities;
using fux.utils;


namespace fux.parsers
{
  public class FirstSpeciesParser : ParserInterface
  {
    private const int FIFTH = 7;
    private const int OCTAVE = 12;
    private const int UNISON = 0;

    private readonly int[] PERFECT_INTERVALS = {FIFTH, OCTAVE, UNISON};

    public Error[] Parse(MusicFile file)
    {
      List<Error> errors = new List<Error>();
      int length = file.voices.Count();
      for (int i = 0; i < length - 1; i++)
      {
        for (int j = i + 1; j < length; j++)
        {
          Voice firstVoice = file.voices[i];
          Voice secondVoice = file.voices[j];
          errors.AddRange(checkFirstSpecies(firstVoice, secondVoice));
        }
      }

      return errors.ToArray();
    }

    private List<Error> checkFirstSpecies(Voice firstVoice, Voice secondVoice)
    {
      List<Error> errors = new List<Error>();
      int firstVoiceNotePosition = 0;
      int secondVoiceNotePosition = 0;

      NoteEvent secondVoiceNote = secondVoice.notes[0];

      int firstVoiceIndex = 0;
      int secondVoiceIndex = 0;
      foreach (NoteEvent note in firstVoice.notes)
      {
        bool skipCheck = false;
        if (note.pitch.pitch < 0) skipCheck = true;

        while (secondVoiceNotePosition + secondVoiceNote.duration <= firstVoiceNotePosition)
        {
          secondVoiceNotePosition += secondVoiceNote.duration;
          secondVoiceIndex = Math.Min(secondVoiceIndex + 1, secondVoice.notes.Length - 1);
          secondVoiceNote = secondVoice.notes[secondVoiceIndex];
        }

        // Pick second voice note that coincides with first voice note position
        if (secondVoiceNotePosition == firstVoiceNotePosition && !skipCheck)
        {
          Error? error = checkFifthOrOctave(firstVoice, firstVoiceIndex, secondVoice, secondVoiceIndex);
          if (error.HasValue) errors.Add(error.Value);
        }
        
        if (secondVoiceIndex == secondVoice.notes.Length - 1) break;

        firstVoiceNotePosition += note.duration;
      }

      return errors;
    }

    private Error? checkFifthOrOctave(Voice firstVoice, int firstVoiceIndex, Voice secondVoice, int secondVoiceIndex)
    {
      int interval = IntervalUtils.NormalizeInterval(firstVoice.notes[firstVoiceIndex], secondVoice.notes[secondVoiceIndex]);

      if (PERFECT_INTERVALS.Contains(interval))
      {
        return new Error
        {
          // TODO: Add error specification
        };
      }

      return null;
    }
  }
}