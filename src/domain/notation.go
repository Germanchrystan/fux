package domain

type Pitch struct {
	Pitch    int // 0-11
	Octave   int
	absPitch int
}

func (p *Pitch) AbsolutePitch() int {
	return p.absPitch
}

func NewPitch(pitch, octave int) *Pitch {
	return &Pitch{
		Pitch:    pitch,
		Octave:   octave,
		absPitch: octave*12 + pitch,
	}
}

type NoteEvent struct {
	Pitch     Pitch
	StartTime int
	Duration  int
}

type Register struct {
	Name   string
	Higher Pitch
	Lower  Pitch
}

type Voice struct {
	ID       int
	Register Register
	Notes    []NoteEvent
}

type MusicFile struct {
	Voices []Voice
	BPM    int
}
