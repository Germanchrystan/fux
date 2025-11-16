package helpers

import "github.com/germanchrystan/fux/src/domain"

func GetInterval(firstNote, secondNote domain.NoteEvent) (interval int, direction int) {
	interval = secondNote.Pitch.AbsolutePitch() - firstNote.Pitch.AbsolutePitch()

	if interval == 0 {
		return interval, 0
	}

	if interval < 0 {
		return interval, -1
	}

	return interval, 1
}
