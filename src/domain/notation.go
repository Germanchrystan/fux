package domain

type Pitch struct {
	Pitch    int // 0-11
	Octave   int
	absPitch int
}

func (p *Pitch) AbsolutePitch() int {
	return p.absPitch
}

// NewPitch creates a new Pitch with the given pitch and octave values
func NewPitch(pitch, octave int) *Pitch {
	return &Pitch{
		Pitch:    pitch,
		Octave:   octave,
		absPitch: octave*12 + pitch,
	}
}

// NoteEvent represents a musical note event
type NoteEvent struct {
	Pitch     Pitch
	StartTime int
	Duration  int
}

// Register represents a musical register
type Register struct {
	Name   string
	Higher Pitch
	Lower  Pitch
}

// Voice represents a musical voice
type Voice struct {
	ID       int
	Register Register
	Notes    []NoteEvent
}

// MusicFile represents a complete music file
type MusicFile struct {
	Voices []Voice
	BPM    int
}
