package parsers

import "github.com/germanchrystan/fux/src/domain"

type MelodyParser struct{}

const MAX_JUMP int = 7 // 5th

func (p MelodyParser) Parse(file domain.MusicFile) []domain.Error {
	var errors []domain.Error

	for _, voice := range file.Voices {
		errors = append(errors, checkPart(voice)...)
	}

	return errors
}

func checkPart(voice domain.Voice) []domain.Error {
	var errors []domain.Error

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

func checkJumpCompensation(voice domain.Voice) []domain.Error {
	var errors []domain.Error

	for _, note := range voice.Notes {

	}

	return errors
}

func checkOutOfRegister(voice domain.Voice) []domain.Error {
	var errors []domain.Error
	return errors
}

func checkRepeatedNotes(voice domain.Voice) []domain.Error {
	var errors []domain.Error
	return errors
}

func checkTritoneRange(voice domain.Voice) []domain.Error {
	var errors []domain.Error
	return errors
}
