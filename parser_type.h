#ifndef PARSER_TYPE_H
#define PARSER_TYPE_H

// TODO: Find better workaround to not redefine YYSSTYPE
#ifdef YYSTYPE
#undef YYSTYPE
#endif

#define PARSERSTYPE calc_value_t
#define YYSTYPE PARSERSTYPE

#endif // PARSER_TYPE_H