package domain

type Parser interface {
	Parse(file MusicFile) []Error
}
