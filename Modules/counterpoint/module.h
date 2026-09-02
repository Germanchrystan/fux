#include <Remark.h>
#include <Notation.h>

typedef void (*NoteDealing)(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2);
typedef NoteDealing Registry[13];

typedef struct Specie
{
  Registry registry;
} Specie;

extern Specie FirstSpecies;
