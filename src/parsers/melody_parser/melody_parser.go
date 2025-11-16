package melodyparsers

import (
	"math"

	"github.com/germanchrystan/fux/src/domain"
	"github.com/germanchrystan/fux/src/pkg/helpers"
	pkg "github.com/germanchrystan/fux/src/pkg/parsing_error"
)

type MelodyParser struct{}

func (p MelodyParser) Parse(file domain.MusicFile) []pkg.Error {
	var errors []pkg.Error

	for _, voice := range file.Voices {
		errors = append(errors, checkPart(voice)...)
	}

	return errors
}

func checkPart(voice domain.Voice) []pkg.Error {
	var errors []pkg.Error
	errors = append(
		errors,
		checkJumpCompensation(voice)...)
	errors = append(errors,
		checkOutOfRegister(voice)...,
	)
	errors = append(errors,
		checkRepeatedNotes(voice)...,
	)
	errors = append(errors,
		checkTritoneRange(voice)...,
	)

	return errors
}

func checkJumpCompensation(voice domain.Voice) []pkg.Error {
	var errors []pkg.Error
	lastIndexToCheck := len(voice.Notes) - 2
	if lastIndexToCheck < 0 {
		lastIndexToCheck = 0
	}

	for i := range voice.Notes[0:lastIndexToCheck] {
		currentNote := voice.Notes[i].Pitch.AbsolutePitch()
		nextNote := voice.Notes[i+1].Pitch.AbsolutePitch()

		interval := nextNote - currentNote
		if math.Abs(float64(interval)) >= float64(domain.MAX_JUMP) {
			nextInterval := voice.Notes[i+2].Pitch.AbsolutePitch() - nextNote
			sameDirection := (interval < 0 && nextInterval < 0) || (interval > 0 && nextInterval > 0)
			if sameDirection {
				errors = append(errors, pkg.NewError(voice.ID, i+1, pkg.GravityMedium, pkg.JumpCompensation))
			}
		}
	}

	return errors
}

func checkOutOfRegister(voice domain.Voice) []pkg.Error {
	var errors []pkg.Error

	lowerNote := voice.Register.Lower
	higherNote := voice.Register.Higher
	for i, note := range voice.Notes {
		pitchValue := note.Pitch.AbsolutePitch()
		if pitchValue < lowerNote.AbsolutePitch() || pitchValue > higherNote.AbsolutePitch() {
			errors = append(errors, pkg.NewError(voice.ID, i, pkg.GravityHigh, pkg.OutOfRegister))
		}
	}
	return errors
}

func checkTritoneRange(voice domain.Voice) []pkg.Error {
	var errors []pkg.Error
	for i := range voice.Notes[:len(voice.Notes)-1] {
		var interval, direction int
		interval, direction = helpers.GetInterval(voice.Notes[i], voice.Notes[i+1])
		if interval == 0 {
			continue
		}
		for j := range voice.Notes[i+1 : len(voice.Notes)-1] {
			newInterval, newDirection := helpers.GetInterval(voice.Notes[i], voice.Notes[j])
			interval = newInterval
			if direction != newDirection {
				break
			}
		}
		if math.Abs(float64(interval)) == 6 {
			errors = append(errors, pkg.NewError(voice.ID, i, pkg.GravityHigh, 123))
		}
	}
	return errors
}

func checkRepeatedNotes(voice domain.Voice) []pkg.Error {
	var errors []pkg.Error
	return errors
}
