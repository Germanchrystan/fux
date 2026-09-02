#include "module.h"

static void dealPerfectConsonance(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2);
static void dealDissonance(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2);
static void dealImperfectConsonance(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2);
static void dealFourth(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2);

static NoteEvent *prevNoteEvent1 = NULL;
static NoteEvent *prevNoteEvent2 = NULL;

Registry registry = 
{
  dealPerfectConsonance,
  dealDissonance,
  dealDissonance,
  dealImperfectConsonance,
  dealImperfectConsonance,
  dealFourth,
  dealDissonance,
  dealPerfectConsonance,
  dealImperfectConsonance,
  dealImperfectConsonance,
  dealDissonance,
  dealDissonance,
  dealPerfectConsonance,
};


static void dealPerfectConsonance(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2)
{
  if (prevNoteEvent1 != NULL && prevNoteEvent2 != NULL) return;
  Remark *remark = newRemark(0, 0, GravityHigh, REMARK_PERFECT_CONSONANCE);
  addRemark(remarkArray, *remark);
}

static void dealDissonance(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2)
{
  Remark *remark = newRemark(0, 0, GravityHigh, REMARK_DISSONANCE);
  addRemark(remarkArray, *remark);
}

static void dealImperfectConsonance(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2)
{
  return;
}

static void dealFourth(RemarkArray *remarkArray, NoteEvent note1, NoteEvent note2)
{
  return;
}

Specie FirstSpecies = {
  .registry = registry
};