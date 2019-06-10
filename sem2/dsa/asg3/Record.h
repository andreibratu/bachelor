#ifndef RECORD_H
#define RECORD_H

#ifndef TElem
#define TElem int
#endif

typedef struct {
  int row;
  int col;
  TElem val;
} Record;

#endif
