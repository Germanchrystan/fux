package pkg

type Error struct {
	Voice     int
	Note      int
	Gravity   float32 // 0-1
	ErrorCode int
}

const (
	GravityHigh   float32 = 1.0
	GravityMedium float32 = 0.5
	GravityLow    float32 = 0.1
)

const (
	OutOfRegister    = 1
	JumpCompensation = 2
	RepeatedNotes    = 3
	TritoneInPassage = 4
)

const (
	OutOfRegisterGravity    float32 = GravityHigh
	JumpCompensationGravity float32 = GravityMedium
	RepeatedNotesGravity    float32 = GravityLow // TODO: Revise this
	TritoneInPassageGravity float32 = GravityHigh
)

func NewError(voice int, note int, gravity float32, errCode int) Error {
	return Error{
		Voice:     voice,
		Note:      note,
		Gravity:   gravity,
		ErrorCode: errCode,
	}
}
