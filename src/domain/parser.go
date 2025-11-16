package domain

import pkg "github.com/germanchrystan/fux/src/pkg/parsing_error"

type Parser interface {
	Parse(file MusicFile) []pkg.Error
}
