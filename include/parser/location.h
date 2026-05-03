#ifndef TACA_PARSER_LOCATION_H
#define TACA_PARSER_LOCATION_H

#define TQLOC_ZERO ((TQLocation){0})
#define TQLOC_POINT(line, col, pos)                                             \
  ((TQLocation){                                                                 \
      .first_line = (line),                                                      \
      .first_column = (col),                                                     \
      .last_line = (line),                                                       \
      .last_column = (col),                                                      \
      .first_pos = (pos),                                                        \
      .last_pos = (pos),                                                         \
  })

/* Tell Bison how to propagate our extra location fields. */
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(Current, Rhs, N)                                        \
  do {                                                                         \
    if (N) {                                                                   \
      (Current).first_line = YYRHSLOC(Rhs, 1).first_line;                      \
      (Current).first_column = YYRHSLOC(Rhs, 1).first_column;                  \
      (Current).first_pos = YYRHSLOC(Rhs, 1).first_pos;                        \
      (Current).last_line = YYRHSLOC(Rhs, N).last_line;                        \
      (Current).last_column = YYRHSLOC(Rhs, N).last_column;                    \
      (Current).last_pos = YYRHSLOC(Rhs, N).last_pos;                          \
    } else {                                                                   \
      (Current).first_line = (Current).last_line = YYRHSLOC(Rhs, 0).last_line; \
      (Current).first_column = (Current).last_column =                         \
          YYRHSLOC(Rhs, 0).last_column;                                        \
      (Current).first_pos = (Current).last_pos = YYRHSLOC(Rhs, 0).last_pos;    \
    }                                                                          \
  } while (0)
#endif

#define TQSET_NODE_LOC(node, source_loc)                                       \
  do {                                                                         \
    if ((node) != NULL) {                                                      \
      (node)->loc = (source_loc);                                              \
    }                                                                          \
  } while (0)

#define TQerror_LOC(loc, code, detail)                                         \
  panic(&file, (loc), (code), (detail))


typedef struct TQLocation {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    int first_pos;
    int last_pos;
} TQLocation;

#endif
