package firstspecies

import (
	"github.com/germanchrystan/fux/src/domain"
	pkg "github.com/germanchrystan/fux/src/pkg/parsing_error"
)

type FirstSpeciesParser struct{}

func (f FirstSpeciesParser) Parse(file domain.MusicFile) []pkg.Error {
	var errors []pkg.Error

	for i, firstVoice := range file.Voices[:len(file.Voices)-1] {
		for _, secondVoice := range file.Voices[i+1:] {
			errors = append(errors, checkFirstSpecies(firstVoice, secondVoice)...)
		}
	}

	return errors
}

func checkFirstSpecies(firstVoice, secondVoice domain.Voice) []pkg.Error {
	var errors []pkg.Error
	return errors
}

//     private List<Error> checkFirstSpecies(Voice firstVoice, Voice secondVoice)
//     {
//       List<Error> errors = new List<Error>();
//       int firstVoiceNotePosition = 0;
//       int secondVoiceNotePosition = 0;

//       NoteEvent secondVoiceNote = secondVoice.notes[0];

//       int firstVoiceIndex = 0;
//       int secondVoiceIndex = 0;
//       foreach (NoteEvent note in firstVoice.notes)
//       {
//         bool skipCheck = false;
//         if (note.pitch.pitch < 0) skipCheck = true;

//         while (secondVoiceNotePosition + secondVoiceNote.duration <= firstVoiceNotePosition)
//         {
//           secondVoiceNotePosition += secondVoiceNote.duration;
//           secondVoiceIndex = Math.Min(secondVoiceIndex + 1, secondVoice.notes.Length - 1);
//           secondVoiceNote = secondVoice.notes[secondVoiceIndex];
//         }

//         // Pick second voice note that coincides with first voice note position
//         if (secondVoiceNotePosition == firstVoiceNotePosition && !skipCheck)
//         {
//           Error? error = checkFifthOrOctave(firstVoice, firstVoiceIndex, secondVoice, secondVoiceIndex);
//           if (error.HasValue) errors.Add(error.Value);
//         }

//         if (secondVoiceIndex == secondVoice.notes.Length - 1) break;

//         firstVoiceNotePosition += note.duration;
//       }

//       return errors;
//     }

//     private Error? checkFifthOrOctave(Voice firstVoice, int firstVoiceIndex, Voice secondVoice, int secondVoiceIndex)
//     {
//       int interval = IntervalUtils.NormalizeInterval(firstVoice.notes[firstVoiceIndex], secondVoice.notes[secondVoiceIndex]);

//       if (PERFECT_INTERVALS.Contains(interval))
//       {
//         return new Error
//         {
//           // TODO: Add error specification
//         };
//       }

//       return null;
//     }
//   }
// }
