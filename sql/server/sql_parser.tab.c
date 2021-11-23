/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         sqlparse
#define yylex           sqllex
#define yyerror         sqlerror
#define yydebug         sqldebug
#define yynerrs         sqlnerrs


/* Copy the first part of user declarations.  */
#line 9 "sql_parser.y" /* yacc.c:339  */

#include "monetdb_config.h"
#include "sql_mem.h"
#include "sql_parser.h"
#include "sql_symbol.h"
#include "sql_datetime.h"
#include "sql_decimal.h"	/* for decimal_from_str() */
#include "sql_semantic.h"	/* for sql_add_param() */
#include "sql_env.h"
#include "rel_sequence.h"	/* for sql_next_seq_name() */

static int sqlerror(mvc *sql, const char *err);
static int sqlformaterror(mvc *sql, _In_z_ _Printf_format_string_ const char *format, ...)
	        __attribute__((__format__(__printf__, 2, 3)));

static void *ma_alloc(sql_allocator *sa, size_t sz);
static void ma_free(void *p);

#include <unistd.h>
#include <string.h>

#define SA 	m->sa
#define _symbol_create(t,d)         symbol_create( SA, t, d)
#define _symbol_create_list(t,d)    symbol_create_list( SA, t, d)
#define _symbol_create_int(t,d)     symbol_create_int( SA, t, d)
#define _symbol_create_lng(t,d)     symbol_create_lng( SA, t, d)
#define _symbol_create_symbol(t,d)  symbol_create_symbol( SA, t, d)
#define _symbol_create_hexa(t,d)    symbol_create_hexa( SA, t, d)
#define _newAtomNode(d)		    newAtomNode( SA, d)

#define L()                  dlist_create( SA )

#define append_list(l,d)     dlist_append_list( SA, l, d)
#define append_int(l,d)      dlist_append_int( SA, l, d)
#define append_lng(l,d)      dlist_append_lng( SA, l, d)
#define append_symbol(l,d)   dlist_append_symbol( SA, l, d)
#define append_string(l,d)   dlist_append_string( SA, l, d)
#define append_type(l,d)     dlist_append_type( SA, l, d)

#define _atom_string(t, v)   atom_string(SA, t, v)

#define Malloc(sz) ma_alloc(m->ta,sz)
#define YYMALLOC Malloc
#define YYFREE ma_free 

#define YY_parse_LSP_NEEDED	/* needed for bison++ 1.21.11-3 */

#define SET_Z(info)(info = info | 0x02)
#define SET_M(info)(info = info | 0x01)

#ifdef HAVE_HGE
#define MAX_DEC_DIGITS 38
#define MAX_HEX_DIGITS 32
#else
#define MAX_DEC_DIGITS 18
#define MAX_HEX_DIGITS 16
#endif

static inline int
UTF8_strlen(const char *val)
{
	const unsigned char *s = (const unsigned char *) val;
	int pos = 0;

	while (*s) {
		int c = *s++;

		pos++;
		if (c < 0xC0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xE0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xF0)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xF8)
			continue;
		if (*s++ < 0x80)
			return int_nil;
		if (c < 0xFC)
			continue;
		if (*s++ < 0x80)
			return int_nil;
	}
	return pos;
}


static char *
uescape_xform(char *restrict s, const char *restrict esc)
{
	size_t i, j;

	for (i = j = 0; s[i]; i++) {
		if (s[i] == *esc) {
			if (s[i + 1] == *esc) {
				s[j++] = *esc;
				i++;
			} else {
				int c = 0;
				int n;
				if (s[i + 1] == '+') {
					n = 6;
					i++;
				} else {
					n = 4;
				}
				do {
					i++;
					c <<= 4;
					if ('0' <= s[i] && s[i] <= '9')
						c |= s[i] - '0';
					else if ('a' <= s[i] && s[i] <= 'f')
						c |= s[i] - 'a' + 10;
					else if ('A' <= s[i] && s[i] <= 'F')
						c |= s[i] - 'A' + 10;
					else
						return NULL;
				} while (--n > 0);
				if (c == 0 || c > 0x10FFFF || (c & 0xFFF800) == 0xD800)
					return NULL;
				if (c < 0x80) {
					s[j++] = c;
				} else {
					if (c < 0x800) {
						s[j++] = 0xC0 | (c >> 6);
					} else {
						if (c < 0x10000) {
							s[j++] = 0xE0 | (c >> 12);
						} else {
							s[j++] = 0xF0 | (c >> 18);
							s[j++] = 0x80 | ((c >> 12) & 0x3F);
						}
						s[j++] = 0x80 | ((c >> 6) & 0x3F);
					}
					s[j++] = 0x80 | (c & 0x3F);
				}
			}
		} else {
			s[j++] = s[i];
		}
	}
	s[j] = 0;
	return s;
}

#line 224 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "sql_parser.tab.h".  */
#ifndef YY_SQL_HOME_WYF_PIM4DB_MAY2021_SP1_MONETDB_11_39_11_BUILD_SQL_SERVER_SQL_PARSER_TAB_H_INCLUDED
# define YY_SQL_HOME_WYF_PIM4DB_MAY2021_SP1_MONETDB_11_39_11_BUILD_SQL_SERVER_SQL_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int sqldebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    STRING = 258,
    USTRING = 259,
    XSTRING = 260,
    X_BODY = 261,
    IDENT = 262,
    UIDENT = 263,
    aTYPE = 264,
    ALIAS = 265,
    RANK = 266,
    sqlINT = 267,
    OIDNUM = 268,
    HEXADECIMAL = 269,
    INTNUM = 270,
    APPROXNUM = 271,
    USING = 272,
    GLOBAL = 273,
    CAST = 274,
    CONVERT = 275,
    CHARACTER = 276,
    VARYING = 277,
    LARGE = 278,
    OBJECT = 279,
    VARCHAR = 280,
    CLOB = 281,
    sqlTEXT = 282,
    BINARY = 283,
    sqlBLOB = 284,
    sqlDECIMAL = 285,
    sqlFLOAT = 286,
    TINYINT = 287,
    SMALLINT = 288,
    BIGINT = 289,
    HUGEINT = 290,
    sqlINTEGER = 291,
    sqlDOUBLE = 292,
    sqlREAL = 293,
    PRECISION = 294,
    PARTIAL = 295,
    SIMPLE = 296,
    ACTION = 297,
    CASCADE = 298,
    RESTRICT = 299,
    BOOL_FALSE = 300,
    BOOL_TRUE = 301,
    CURRENT_DATE = 302,
    CURRENT_TIMESTAMP = 303,
    CURRENT_TIME = 304,
    LOCALTIMESTAMP = 305,
    LOCALTIME = 306,
    LEX_ERROR = 307,
    GEOMETRY = 308,
    GEOMETRYSUBTYPE = 309,
    GEOMETRYA = 310,
    USER = 311,
    CURRENT_USER = 312,
    SESSION_USER = 313,
    LOCAL = 314,
    LOCKED = 315,
    BEST = 316,
    EFFORT = 317,
    CURRENT_ROLE = 318,
    sqlSESSION = 319,
    CURRENT_SCHEMA = 320,
    CURRENT_TIMEZONE = 321,
    sqlDELETE = 322,
    UPDATE = 323,
    SELECT = 324,
    INSERT = 325,
    MATCHED = 326,
    LATERAL = 327,
    LEFT = 328,
    RIGHT = 329,
    FULL = 330,
    OUTER = 331,
    NATURAL = 332,
    CROSS = 333,
    JOIN = 334,
    INNER = 335,
    COMMIT = 336,
    ROLLBACK = 337,
    SAVEPOINT = 338,
    RELEASE = 339,
    WORK = 340,
    CHAIN = 341,
    NO = 342,
    PRESERVE = 343,
    ROWS = 344,
    START = 345,
    TRANSACTION = 346,
    READ = 347,
    WRITE = 348,
    ONLY = 349,
    ISOLATION = 350,
    LEVEL = 351,
    UNCOMMITTED = 352,
    COMMITTED = 353,
    sqlREPEATABLE = 354,
    SERIALIZABLE = 355,
    DIAGNOSTICS = 356,
    sqlSIZE = 357,
    STORAGE = 358,
    ASYMMETRIC = 359,
    SYMMETRIC = 360,
    ORDER = 361,
    ORDERED = 362,
    BY = 363,
    IMPRINTS = 364,
    EXISTS = 365,
    ESCAPE = 366,
    UESCAPE = 367,
    HAVING = 368,
    sqlGROUP = 369,
    ROLLUP = 370,
    CUBE = 371,
    sqlNULL = 372,
    GROUPING = 373,
    SETS = 374,
    FROM = 375,
    FOR = 376,
    MATCH = 377,
    EXTRACT = 378,
    SEQUENCE = 379,
    INCREMENT = 380,
    RESTART = 381,
    CONTINUE = 382,
    MAXVALUE = 383,
    MINVALUE = 384,
    CYCLE = 385,
    NEXT = 386,
    VALUE = 387,
    CACHE = 388,
    GENERATED = 389,
    ALWAYS = 390,
    IDENTITY = 391,
    SERIAL = 392,
    BIGSERIAL = 393,
    AUTO_INCREMENT = 394,
    SCOLON = 395,
    AT = 396,
    XMLCOMMENT = 397,
    XMLCONCAT = 398,
    XMLDOCUMENT = 399,
    XMLELEMENT = 400,
    XMLATTRIBUTES = 401,
    XMLFOREST = 402,
    XMLPARSE = 403,
    STRIP = 404,
    WHITESPACE = 405,
    XMLPI = 406,
    XMLQUERY = 407,
    PASSING = 408,
    XMLTEXT = 409,
    NIL = 410,
    REF = 411,
    ABSENT = 412,
    EMPTY = 413,
    DOCUMENT = 414,
    ELEMENT = 415,
    CONTENT = 416,
    XMLNAMESPACES = 417,
    NAMESPACE = 418,
    XMLVALIDATE = 419,
    RETURNING = 420,
    LOCATION = 421,
    ID = 422,
    ACCORDING = 423,
    XMLSCHEMA = 424,
    URI = 425,
    XMLAGG = 426,
    FILTER = 427,
    UNION = 428,
    EXCEPT = 429,
    INTERSECT = 430,
    CORRESPONDING = 431,
    WITH = 432,
    DATA = 433,
    FILTER_FUNC = 434,
    NOT = 435,
    ALL = 436,
    ANY = 437,
    NOT_BETWEEN = 438,
    BETWEEN = 439,
    NOT_IN = 440,
    sqlIN = 441,
    NOT_LIKE = 442,
    LIKE = 443,
    NOT_ILIKE = 444,
    ILIKE = 445,
    OR = 446,
    SOME = 447,
    AND = 448,
    COMPARISON = 449,
    LEFT_SHIFT = 450,
    RIGHT_SHIFT = 451,
    LEFT_SHIFT_ASSIGN = 452,
    RIGHT_SHIFT_ASSIGN = 453,
    CONCATSTRING = 454,
    SUBSTRING = 455,
    POSITION = 456,
    SPLIT_PART = 457,
    UMINUS = 458,
    GEOM_OVERLAP = 459,
    GEOM_OVERLAP_OR_ABOVE = 460,
    GEOM_OVERLAP_OR_BELOW = 461,
    GEOM_OVERLAP_OR_LEFT = 462,
    GEOM_OVERLAP_OR_RIGHT = 463,
    GEOM_BELOW = 464,
    GEOM_ABOVE = 465,
    GEOM_DIST = 466,
    GEOM_MBR_EQUAL = 467,
    TEMP = 468,
    TEMPORARY = 469,
    STREAM = 470,
    MERGE = 471,
    REMOTE = 472,
    REPLICA = 473,
    ASC = 474,
    DESC = 475,
    AUTHORIZATION = 476,
    CHECK = 477,
    CONSTRAINT = 478,
    CREATE = 479,
    COMMENT = 480,
    NULLS = 481,
    FIRST = 482,
    LAST = 483,
    TYPE = 484,
    PROCEDURE = 485,
    FUNCTION = 486,
    sqlLOADER = 487,
    AGGREGATE = 488,
    RETURNS = 489,
    EXTERNAL = 490,
    sqlNAME = 491,
    DECLARE = 492,
    CALL = 493,
    LANGUAGE = 494,
    ANALYZE = 495,
    MINMAX = 496,
    SQL_EXPLAIN = 497,
    SQL_PLAN = 498,
    SQL_DEBUG = 499,
    SQL_TRACE = 500,
    PREP = 501,
    PREPARE = 502,
    EXEC = 503,
    EXECUTE = 504,
    DEALLOCATE = 505,
    DEFAULT = 506,
    DISTINCT = 507,
    DROP = 508,
    TRUNCATE = 509,
    FOREIGN = 510,
    RENAME = 511,
    ENCRYPTED = 512,
    UNENCRYPTED = 513,
    PASSWORD = 514,
    GRANT = 515,
    REVOKE = 516,
    ROLE = 517,
    ADMIN = 518,
    INTO = 519,
    IS = 520,
    KEY = 521,
    ON = 522,
    OPTION = 523,
    OPTIONS = 524,
    PATH = 525,
    PRIMARY = 526,
    PRIVILEGES = 527,
    PUBLIC = 528,
    REFERENCES = 529,
    SCHEMA = 530,
    SET = 531,
    AUTO_COMMIT = 532,
    RETURN = 533,
    ALTER = 534,
    ADD = 535,
    TABLE = 536,
    COLUMN = 537,
    TO = 538,
    UNIQUE = 539,
    VALUES = 540,
    VIEW = 541,
    WHERE = 542,
    sqlDATE = 543,
    TIME = 544,
    TIMESTAMP = 545,
    INTERVAL = 546,
    CENTURY = 547,
    DECADE = 548,
    YEAR = 549,
    QUARTER = 550,
    DOW = 551,
    DOY = 552,
    MONTH = 553,
    WEEK = 554,
    DAY = 555,
    HOUR = 556,
    MINUTE = 557,
    SECOND = 558,
    EPOCH = 559,
    ZONE = 560,
    LIMIT = 561,
    OFFSET = 562,
    SAMPLE = 563,
    SEED = 564,
    CASE = 565,
    WHEN = 566,
    THEN = 567,
    ELSE = 568,
    NULLIF = 569,
    COALESCE = 570,
    IF = 571,
    ELSEIF = 572,
    WHILE = 573,
    DO = 574,
    ATOMIC = 575,
    BEGIN = 576,
    END = 577,
    COPY = 578,
    RECORDS = 579,
    DELIMITERS = 580,
    STDIN = 581,
    STDOUT = 582,
    FWF = 583,
    CLIENT = 584,
    SERVER = 585,
    INDEX = 586,
    REPLACE = 587,
    AS = 588,
    TRIGGER = 589,
    OF = 590,
    BEFORE = 591,
    AFTER = 592,
    ROW = 593,
    STATEMENT = 594,
    sqlNEW = 595,
    OLD = 596,
    EACH = 597,
    REFERENCING = 598,
    OVER = 599,
    PARTITION = 600,
    CURRENT = 601,
    EXCLUDE = 602,
    FOLLOWING = 603,
    PRECEDING = 604,
    OTHERS = 605,
    TIES = 606,
    RANGE = 607,
    UNBOUNDED = 608,
    GROUPS = 609,
    WINDOW = 610
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 173 "sql_parser.y" /* yacc.c:355  */

	int		i_val,bval;
	lng		l_val,operation;
	double		fval;
	char *		sval;
	symbol*		sym;
	dlist*		l;
	sql_subtype	type;

#line 630 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sqlparse (mvc *m);

#endif /* !YY_SQL_HOME_WYF_PIM4DB_MAY2021_SP1_MONETDB_11_39_11_BUILD_SQL_SERVER_SQL_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */
#line 182 "sql_parser.y" /* yacc.c:358  */

extern int sqllex( YYSTYPE *yylval, void *m );
/* enable to activate debugging support
int yydebug=1;
*/

#line 652 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  264
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   21559

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  374
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  455
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1273
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2343

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   610

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   213,   200,     2,
     179,   180,   211,   198,   368,   199,   369,   212,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   370,     2,
       2,   183,     2,   373,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   371,     2,   372,   202,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   201,     2,   215,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   181,   182,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     203,   204,   205,   206,   207,   208,   209,   210,   214,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,   313,   314,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   716,   716,   727,   727,   740,   740,   754,   754,   768,
     768,   777,   777,   782,   783,   784,   785,   786,   787,   791,
     792,   796,   797,   800,   802,   806,   810,   813,   814,   818,
     819,   823,   824,   828,   831,   834,   838,   839,   840,   841,
     842,   843,   844,   845,   846,   853,   854,   858,   859,   863,
     864,   868,   869,   873,   878,   886,   887,   891,   896,   901,
     908,   915,   922,   929,   936,   944,   953,   962,   966,   970,
     977,   980,   981,   985,   986,   990,   991,   995,   995,   995,
     995,   995,   998,   999,  1003,  1004,  1008,  1017,  1028,  1029,
    1034,  1035,  1039,  1040,  1045,  1046,  1050,  1058,  1068,  1069,
    1073,  1074,  1078,  1082,  1089,  1090,  1095,  1096,  1100,  1101,
    1102,  1113,  1114,  1115,  1119,  1120,  1125,  1126,  1127,  1128,
    1129,  1130,  1131,  1135,  1136,  1141,  1142,  1148,  1154,  1165,
    1171,  1177,  1183,  1189,  1195,  1206,  1212,  1219,  1225,  1230,
    1235,  1245,  1254,  1260,  1266,  1276,  1281,  1285,  1289,  1291,
    1299,  1307,  1312,  1317,  1326,  1327,  1331,  1332,  1333,  1334,
    1335,  1336,  1337,  1338,  1354,  1365,  1382,  1392,  1393,  1396,
    1397,  1401,  1402,  1406,  1407,  1408,  1412,  1413,  1414,  1415,
    1416,  1420,  1421,  1422,  1423,  1424,  1425,  1426,  1427,  1434,
    1444,  1445,  1446,  1447,  1467,  1472,  1483,  1484,  1485,  1489,
    1490,  1494,  1507,  1514,  1527,  1540,  1556,  1569,  1587,  1588,
    1592,  1596,  1597,  1601,  1602,  1622,  1626,  1627,  1631,  1632,
    1636,  1637,  1641,  1642,  1646,  1651,  1657,  1666,  1667,  1672,
    1677,  1683,  1692,  1693,  1694,  1695,  1696,  1697,  1701,  1702,
    1703,  1704,  1708,  1709,  1713,  1723,  1724,  1725,  1729,  1731,
    1735,  1735,  1736,  1736,  1736,  1739,  1740,  1744,  1752,  1805,
    1806,  1810,  1812,  1817,  1826,  1828,  1832,  1832,  1832,  1835,
    1839,  1843,  1852,  1881,  1919,  1920,  1925,  1936,  1937,  1941,
    1942,  1943,  1944,  1945,  1949,  1953,  1957,  1958,  1959,  1960,
    1961,  1965,  1966,  1967,  1968,  1972,  1973,  1977,  1978,  1979,
    1980,  1981,  1991,  1995,  1997,  1999,  2013,  2017,  2019,  2024,
    2028,  2041,  2042,  2046,  2047,  2051,  2052,  2056,  2057,  2061,
    2065,  2069,  2077,  2081,  2082,  2086,  2087,  2088,  2089,  2090,
    2091,  2092,  2093,  2094,  2095,  2098,  2099,  2102,  2116,  2130,
    2178,  2180,  2184,  2202,  2203,  2208,  2209,  2214,  2215,  2216,
    2217,  2218,  2219,  2220,  2221,  2222,  2223,  2224,  2225,  2229,
    2230,  2231,  2232,  2233,  2234,  2235,  2236,  2240,  2241,  2242,
    2243,  2244,  2245,  2258,  2262,  2266,  2275,  2278,  2279,  2280,
    2284,  2288,  2289,  2290,  2295,  2301,  2309,  2317,  2319,  2324,
    2332,  2334,  2339,  2340,  2347,  2361,  2362,  2364,  2375,  2396,
    2397,  2401,  2402,  2406,  2410,  2418,  2420,  2425,  2426,  2430,
    2434,  2439,  2488,  2503,  2504,  2509,  2510,  2511,  2512,  2513,
    2517,  2518,  2522,  2523,  2529,  2530,  2531,  2532,  2535,  2537,
    2540,  2542,  2546,  2554,  2555,  2559,  2560,  2564,  2565,  2569,
    2571,  2577,  2586,  2592,  2601,  2610,  2616,  2621,  2622,  2623,
    2624,  2633,  2634,  2635,  2639,  2642,  2647,  2648,  2649,  2654,
    2655,  2659,  2660,  2661,  2662,  2663,  2664,  2668,  2675,  2676,
    2680,  2682,  2684,  2686,  2690,  2692,  2694,  2699,  2700,  2704,
    2706,  2711,  2712,  2713,  2714,  2718,  2719,  2720,  2721,  2725,
    2726,  2730,  2731,  2732,  2736,  2737,  2741,  2742,  2743,  2747,
    2763,  2779,  2784,  2792,  2800,  2811,  2812,  2817,  2818,  2823,
    2824,  2828,  2829,  2833,  2837,  2846,  2850,  2855,  2860,  2869,
    2870,  2874,  2875,  2876,  2877,  2879,  2884,  2885,  2889,  2890,
    2891,  2895,  2896,  2900,  2901,  2905,  2906,  2910,  2911,  2915,
    2916,  2921,  2931,  2932,  2933,  2937,  2943,  2952,  2964,  2965,
    2969,  2973,  2978,  2986,  2991,  2999,  3000,  3004,  3015,  3023,
    3034,  3035,  3037,  3041,  3042,  3047,  3048,  3053,  3054,  3059,
    3063,  3064,  3068,  3069,  3073,  3074,  3075,  3079,  3080,  3085,
    3090,  3098,  3099,  3105,  3107,  3112,  3120,  3131,  3132,  3133,
    3137,  3138,  3142,  3143,  3144,  3148,  3149,  3169,  3173,  3183,
    3184,  3188,  3201,  3202,  3203,  3204,  3205,  3206,  3210,  3211,
    3215,  3227,  3239,  3271,  3280,  3289,  3297,  3298,  3299,  3303,
    3304,  3305,  3310,  3311,  3313,  3318,  3322,  3333,  3338,  3339,
    3343,  3344,  3348,  3349,  3353,  3354,  3359,  3363,  3369,  3375,
    3385,  3397,  3402,  3407,  3412,  3417,  3422,  3430,  3431,  3435,
    3436,  3440,  3441,  3445,  3446,  3447,  3448,  3449,  3453,  3454,
    3458,  3459,  3463,  3464,  3468,  3469,  3473,  3474,  3475,  3476,
    3477,  3481,  3482,  3486,  3491,  3495,  3500,  3504,  3505,  3510,
    3511,  3515,  3519,  3520,  3524,  3528,  3529,  3533,  3537,  3541,
    3542,  3546,  3550,  3551,  3556,  3564,  3565,  3566,  3570,  3571,
    3572,  3576,  3577,  3578,  3579,  3580,  3581,  3582,  3583,  3587,
    3588,  3592,  3593,  3594,  3595,  3599,  3608,  3620,  3627,  3637,
    3638,  3639,  3643,  3650,  3657,  3664,  3674,  3678,  3694,  3695,
    3699,  3705,  3711,  3716,  3724,  3726,  3733,  3737,  3738,  3742,
    3746,  3755,  3756,  3760,  3761,  3766,  3767,  3775,  3783,  3791,
    3799,  3807,  3815,  3823,  3831,  3839,  3847,  3855,  3862,  3870,
    3878,  3886,  3894,  3902,  3910,  3918,  3925,  3933,  3941,  3949,
    3957,  3959,  3972,  3976,  3977,  3981,  3982,  3983,  3987,  3988,
    3996,  3997,  3998,  3999,  4000,  4001,  4002,  4003,  4004,  4012,
    4013,  4014,  4015,  4016,  4020,  4029,  4034,  4035,  4039,  4040,
    4044,  4045,  4050,  4051,  4056,  4057,  4062,  4063,  4064,  4068,
    4074,  4078,  4081,  4083,  4089,  4090,  4094,  4098,  4101,  4106,
    4107,  4108,  4109,  4110,  4114,  4119,  4138,  4139,  4144,  4145,
    4146,  4147,  4151,  4159,  4165,  4171,  4177,  4183,  4192,  4193,
    4197,  4208,  4219,  4227,  4235,  4243,  4251,  4265,  4266,  4271,
    4276,  4281,  4286,  4294,  4295,  4296,  4300,  4310,  4311,  4316,
    4322,  4328,  4334,  4340,  4346,  4352,  4358,  4374,  4390,  4406,
    4410,  4411,  4412,  4416,  4417,  4428,  4430,  4434,  4436,  4440,
    4441,  4447,  4456,  4457,  4458,  4459,  4460,  4464,  4465,  4469,
    4470,  4471,  4472,  4473,  4474,  4476,  4478,  4482,  4488,  4491,
    4497,  4500,  4506,  4509,  4514,  4536,  4537,  4538,  4542,  4543,
    4547,  4548,  4552,  4553,  4557,  4563,  4624,  4652,  4710,  4744,
    4758,  4771,  4784,  4797,  4798,  4812,  4826,  4840,  4854,  4872,
    4876,  4883,  4929,  4930,  4934,  4945,  4948,  4952,  4960,  4963,
    4969,  4975,  4983,  4988,  4990,  4996,  5004,  5008,  5013,  5021,
    5023,  5028,  5036,  5038,  5043,  5044,  5050,  5061,  5072,  5082,
    5092,  5094,  5099,  5100,  5102,  5104,  5113,  5114,  5123,  5124,
    5125,  5126,  5127,  5129,  5130,  5141,  5156,  5157,  5168,  5183,
    5184,  5185,  5186,  5187,  5188,  5189,  5191,  5192,  5194,  5203,
    5214,  5225,  5232,  5245,  5258,  5265,  5285,  5298,  5314,  5326,
    5327,  5331,  5332,  5333,  5336,  5337,  5340,  5342,  5345,  5346,
    5348,  5349,  5350,  5354,  5365,  5366,  5368,  5369,  5370,  5371,
    5372,  5376,  5387,  5388,  5389,  5390,  5391,  5392,  5393,  5394,
    5395,  5396,  5397,  5398,  5399,  5400,  5401,  5402,  5403,  5404,
    5405,  5406,  5407,  5408,  5409,  5410,  5411,  5413,  5414,  5415,
    5416,  5417,  5418,  5419,  5420,  5421,  5422,  5423,  5424,  5425,
    5426,  5427,  5428,  5429,  5430,  5431,  5432,  5433,  5434,  5435,
    5436,  5437,  5438,  5439,  5440,  5441,  5442,  5443,  5444,  5445,
    5446,  5447,  5448,  5449,  5450,  5451,  5452,  5453,  5454,  5455,
    5456,  5457,  5458,  5459,  5460,  5461,  5462,  5465,  5466,  5467,
    5468,  5469,  5470,  5471,  5472,  5473,  5474,  5475,  5476,  5477,
    5478,  5479,  5480,  5484,  5504,  5505,  5509,  5530,  5531,  5543,
    5545,  5550,  5552,  5557,  5559,  5564,  5565,  5575,  5580,  5581,
    5585,  5592,  5598,  5614,  5615,  5619,  5622,  5625,  5631,  5640,
    5641,  5642,  5643,  5649,  5656,  5657,  5658,  5662,  5666,  5668,
    5673,  5677,  5678,  5679,  5680,  5681,  5682,  5683,  5684,  5685,
    5686,  5690,  5698,  5706,  5713,  5727,  5728,  5732,  5736,  5740,
    5744,  5748,  5752,  5759,  5763,  5767,  5768,  5778,  5786,  5787,
    5791,  5795,  5799,  5806,  5808,  5813,  5817,  5818,  5822,  5823,
    5824,  5825,  5826,  5830,  5843,  5844,  5848,  5850,  5855,  5861,
    5865,  5866,  5870,  5875,  5884,  5885,  5889,  5900,  5904,  5905,
    5910,  5920,  5923,  5925,  5929,  5933,  5934,  5938,  5939,  5943,
    5947,  5950,  5952,  5956,  5957,  5961,  5969,  5978,  5979,  5983,
    5984,  5988,  5989,  5990,  6005,  6009,  6010,  6020,  6021,  6025,
    6029,  6033,  6041,  6045,  6048,  6050,  6054,  6055,  6058,  6060,
    6064,  6069,  6070,  6074,  6075,  6079,  6083,  6086,  6088,  6092,
    6096,  6100,  6103,  6105,  6109,  6110,  6114,  6116,  6120,  6124,
    6125,  6129,  6133,  6137
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "USTRING", "XSTRING", "X_BODY",
  "IDENT", "UIDENT", "aTYPE", "ALIAS", "RANK", "sqlINT", "OIDNUM",
  "HEXADECIMAL", "INTNUM", "APPROXNUM", "USING", "GLOBAL", "CAST",
  "CONVERT", "CHARACTER", "VARYING", "LARGE", "OBJECT", "VARCHAR", "CLOB",
  "sqlTEXT", "BINARY", "sqlBLOB", "sqlDECIMAL", "sqlFLOAT", "TINYINT",
  "SMALLINT", "BIGINT", "HUGEINT", "sqlINTEGER", "sqlDOUBLE", "sqlREAL",
  "PRECISION", "PARTIAL", "SIMPLE", "ACTION", "CASCADE", "RESTRICT",
  "BOOL_FALSE", "BOOL_TRUE", "CURRENT_DATE", "CURRENT_TIMESTAMP",
  "CURRENT_TIME", "LOCALTIMESTAMP", "LOCALTIME", "LEX_ERROR", "GEOMETRY",
  "GEOMETRYSUBTYPE", "GEOMETRYA", "USER", "CURRENT_USER", "SESSION_USER",
  "LOCAL", "LOCKED", "BEST", "EFFORT", "CURRENT_ROLE", "sqlSESSION",
  "CURRENT_SCHEMA", "CURRENT_TIMEZONE", "sqlDELETE", "UPDATE", "SELECT",
  "INSERT", "MATCHED", "LATERAL", "LEFT", "RIGHT", "FULL", "OUTER",
  "NATURAL", "CROSS", "JOIN", "INNER", "COMMIT", "ROLLBACK", "SAVEPOINT",
  "RELEASE", "WORK", "CHAIN", "NO", "PRESERVE", "ROWS", "START",
  "TRANSACTION", "READ", "WRITE", "ONLY", "ISOLATION", "LEVEL",
  "UNCOMMITTED", "COMMITTED", "sqlREPEATABLE", "SERIALIZABLE",
  "DIAGNOSTICS", "sqlSIZE", "STORAGE", "ASYMMETRIC", "SYMMETRIC", "ORDER",
  "ORDERED", "BY", "IMPRINTS", "EXISTS", "ESCAPE", "UESCAPE", "HAVING",
  "sqlGROUP", "ROLLUP", "CUBE", "sqlNULL", "GROUPING", "SETS", "FROM",
  "FOR", "MATCH", "EXTRACT", "SEQUENCE", "INCREMENT", "RESTART",
  "CONTINUE", "MAXVALUE", "MINVALUE", "CYCLE", "NEXT", "VALUE", "CACHE",
  "GENERATED", "ALWAYS", "IDENTITY", "SERIAL", "BIGSERIAL",
  "AUTO_INCREMENT", "SCOLON", "AT", "XMLCOMMENT", "XMLCONCAT",
  "XMLDOCUMENT", "XMLELEMENT", "XMLATTRIBUTES", "XMLFOREST", "XMLPARSE",
  "STRIP", "WHITESPACE", "XMLPI", "XMLQUERY", "PASSING", "XMLTEXT", "NIL",
  "REF", "ABSENT", "EMPTY", "DOCUMENT", "ELEMENT", "CONTENT",
  "XMLNAMESPACES", "NAMESPACE", "XMLVALIDATE", "RETURNING", "LOCATION",
  "ID", "ACCORDING", "XMLSCHEMA", "URI", "XMLAGG", "FILTER", "UNION",
  "EXCEPT", "INTERSECT", "CORRESPONDING", "WITH", "DATA", "'('", "')'",
  "FILTER_FUNC", "NOT", "'='", "ALL", "ANY", "NOT_BETWEEN", "BETWEEN",
  "NOT_IN", "sqlIN", "NOT_LIKE", "LIKE", "NOT_ILIKE", "ILIKE", "OR",
  "SOME", "AND", "COMPARISON", "'+'", "'-'", "'&'", "'|'", "'^'",
  "LEFT_SHIFT", "RIGHT_SHIFT", "LEFT_SHIFT_ASSIGN", "RIGHT_SHIFT_ASSIGN",
  "CONCATSTRING", "SUBSTRING", "POSITION", "SPLIT_PART", "'*'", "'/'",
  "'%'", "UMINUS", "'~'", "GEOM_OVERLAP", "GEOM_OVERLAP_OR_ABOVE",
  "GEOM_OVERLAP_OR_BELOW", "GEOM_OVERLAP_OR_LEFT", "GEOM_OVERLAP_OR_RIGHT",
  "GEOM_BELOW", "GEOM_ABOVE", "GEOM_DIST", "GEOM_MBR_EQUAL", "TEMP",
  "TEMPORARY", "STREAM", "MERGE", "REMOTE", "REPLICA", "ASC", "DESC",
  "AUTHORIZATION", "CHECK", "CONSTRAINT", "CREATE", "COMMENT", "NULLS",
  "FIRST", "LAST", "TYPE", "PROCEDURE", "FUNCTION", "sqlLOADER",
  "AGGREGATE", "RETURNS", "EXTERNAL", "sqlNAME", "DECLARE", "CALL",
  "LANGUAGE", "ANALYZE", "MINMAX", "SQL_EXPLAIN", "SQL_PLAN", "SQL_DEBUG",
  "SQL_TRACE", "PREP", "PREPARE", "EXEC", "EXECUTE", "DEALLOCATE",
  "DEFAULT", "DISTINCT", "DROP", "TRUNCATE", "FOREIGN", "RENAME",
  "ENCRYPTED", "UNENCRYPTED", "PASSWORD", "GRANT", "REVOKE", "ROLE",
  "ADMIN", "INTO", "IS", "KEY", "ON", "OPTION", "OPTIONS", "PATH",
  "PRIMARY", "PRIVILEGES", "PUBLIC", "REFERENCES", "SCHEMA", "SET",
  "AUTO_COMMIT", "RETURN", "ALTER", "ADD", "TABLE", "COLUMN", "TO",
  "UNIQUE", "VALUES", "VIEW", "WHERE", "sqlDATE", "TIME", "TIMESTAMP",
  "INTERVAL", "CENTURY", "DECADE", "YEAR", "QUARTER", "DOW", "DOY",
  "MONTH", "WEEK", "DAY", "HOUR", "MINUTE", "SECOND", "EPOCH", "ZONE",
  "LIMIT", "OFFSET", "SAMPLE", "SEED", "CASE", "WHEN", "THEN", "ELSE",
  "NULLIF", "COALESCE", "IF", "ELSEIF", "WHILE", "DO", "ATOMIC", "BEGIN",
  "END", "COPY", "RECORDS", "DELIMITERS", "STDIN", "STDOUT", "FWF",
  "CLIENT", "SERVER", "INDEX", "REPLACE", "AS", "TRIGGER", "OF", "BEFORE",
  "AFTER", "ROW", "STATEMENT", "sqlNEW", "OLD", "EACH", "REFERENCING",
  "OVER", "PARTITION", "CURRENT", "EXCLUDE", "FOLLOWING", "PRECEDING",
  "OTHERS", "TIES", "RANGE", "UNBOUNDED", "GROUPS", "WINDOW", "','", "'.'",
  "':'", "'['", "']'", "'?'", "$accept", "sqlstmt", "$@1", "$@2", "$@3",
  "$@4", "$@5", "prepare", "execute", "opt_prepare", "deallocate",
  "create", "create_or_replace", "if_exists", "if_not_exists", "drop",
  "set", "declare", "sql", "opt_minmax", "declare_statement",
  "variable_ref_commalist", "variable_list", "opt_equal", "set_statement",
  "schema", "schema_name_clause", "authorization_identifier",
  "opt_schema_default_char_set", "opt_schema_element_list",
  "schema_element_list", "schema_element", "opt_grantor", "grantor",
  "grant", "authid_list", "opt_with_grant", "opt_with_admin",
  "opt_from_grantor", "revoke", "opt_grant_for", "opt_admin_for",
  "privileges", "global_privileges", "global_privilege", "object_name",
  "object_privileges", "operation_commalist", "operation",
  "grantee_commalist", "grantee", "alter_statement", "passwd_schema",
  "alter_table_element", "drop_table_element", "opt_column",
  "create_statement", "seq_def", "opt_seq_params", "params_list",
  "opt_alt_seq_params", "opt_seq_param", "opt_alt_seq_param",
  "opt_seq_common_param", "index_def", "opt_index_type", "role_def",
  "opt_encrypted", "table_opt_storage", "table_def", "partition_type",
  "partition_expression", "partition_on", "opt_partition_by",
  "partition_list_value", "partition_range_from", "partition_range_to",
  "partition_list", "opt_with_nulls", "opt_partition_spec",
  "opt_as_partition", "with_opt_credentials", "opt_temp", "opt_on_commit",
  "table_content_source", "as_subquery_clause", "with_or_without_data",
  "table_element_list", "add_table_element", "table_element",
  "serial_or_bigserial", "column_def", "opt_column_def_opt_list",
  "column_def_opt_list", "column_options", "column_option_list",
  "column_option", "default", "default_value", "column_constraint",
  "generated_column", "serial_opt_params", "table_constraint",
  "opt_constraint_name", "ref_action", "ref_on_update", "ref_on_delete",
  "opt_ref_action", "opt_match_type", "opt_match",
  "column_constraint_type", "table_constraint_type",
  "domain_constraint_type", "ident_commalist", "like_table", "view_def",
  "query_expression_def", "query_expression", "opt_with_check_option",
  "opt_column_list", "column_commalist_parens",
  "variable_ref_commalist_parens", "type_def", "external_function_name",
  "function_body", "func_def_type", "func_def_opt_return", "func_def",
  "routine_body", "procedure_statement_list",
  "trigger_procedure_statement_list", "procedure_statement",
  "trigger_procedure_statement", "control_statement", "call_statement",
  "call_procedure_statement", "routine_invocation", "routine_name",
  "argument_list", "return_statement", "return_value", "case_statement",
  "when_statement", "when_statements", "when_search_statement",
  "when_search_statements", "case_opt_else_statement", "if_statement",
  "if_opt_else", "while_statement", "opt_begin_label", "opt_end_label",
  "table_function_column_list", "func_data_type", "opt_paramlist",
  "paramlist", "trigger_def", "trigger_action_time", "trigger_event",
  "opt_referencing_list", "old_or_new_values_alias_list",
  "old_or_new_values_alias", "opt_as", "opt_row", "triggered_action",
  "opt_for_each", "row_or_statement", "opt_when", "triggered_statement",
  "routine_designator", "drop_statement", "opt_typelist", "typelist",
  "drop_action", "update_statement", "transaction_statement",
  "start_transaction", "transaction_stmt", "transaction_mode_list",
  "_transaction_mode_list", "transaction_mode", "iso_level", "opt_work",
  "opt_chain", "opt_to_savepoint", "opt_on_location", "copyfrom_stmt",
  "opt_fwf_widths", "fwf_widthlist", "opt_header_list", "header_list",
  "header", "opt_seps", "opt_using", "opt_nr", "opt_null_string",
  "opt_escape", "opt_locked", "opt_best_effort", "opt_constraint",
  "string_commalist", "string_commalist_contents", "delete_stmt",
  "check_identity", "truncate_stmt", "update_stmt", "opt_search_condition",
  "merge_update_or_delete", "merge_insert", "merge_match_clause",
  "merge_when_list", "merge_stmt", "insert_stmt", "values_or_query_spec",
  "row_commalist", "atom_commalist", "value_commalist", "null",
  "insert_atom", "value", "opt_distinct", "assignment_commalist",
  "assignment", "opt_where_clause", "joined_table", "join_type",
  "opt_outer", "outer_join_type", "join_spec", "with_query", "with_list",
  "with_list_element", "with_query_expression", "simple_select",
  "select_statement_single_row", "select_no_parens_orderby",
  "select_no_parens", "set_distinct", "opt_corresponding", "selection",
  "table_exp", "window_definition", "window_definition_list",
  "opt_window_clause", "opt_from_clause", "table_ref_commalist",
  "table_ref", "table_name", "opt_table_name", "opt_group_by_clause",
  "group_by_list", "group_by_element", "ordinary_grouping_set",
  "ordinary_grouping_element", "column_ref_commalist", "grouping_set_list",
  "grouping_set_element", "opt_having_clause", "search_condition",
  "and_exp", "opt_order_by_clause", "opt_limit", "opt_offset",
  "opt_sample", "opt_seed", "sort_specification_list", "ordering_spec",
  "opt_asc_desc", "opt_nulls_first_last", "predicate", "pred_exp",
  "opt_any_all_some", "comparison_predicate", "between_predicate",
  "opt_bounds", "like_predicate", "like_exp", "test_for_null",
  "in_predicate", "pred_exp_list", "existence_test", "filter_arg_list",
  "filter_args", "filter_exp", "subquery_with_orderby", "subquery",
  "simple_scalar_exp", "scalar_exp", "opt_over", "value_exp", "param",
  "window_specification", "window_ident_clause",
  "search_condition_commalist", "window_partition_clause",
  "window_order_clause", "window_frame_clause", "window_frame_units",
  "window_frame_extent", "window_frame_start", "window_bound",
  "window_frame_between", "window_following_bound",
  "window_frame_exclusion", "func_ref", "qfunc", "func_ident",
  "datetime_funcs", "opt_brackets", "string_funcs", "column_exp_commalist",
  "column_exp", "opt_alias_name", "atom", "qrank", "aggr_or_window_ref",
  "opt_sign", "tz", "time_precision", "timestamp_precision",
  "datetime_type", "non_second_datetime_field", "datetime_field",
  "extract_datetime_field", "start_field", "end_field",
  "single_datetime_field", "interval_qualifier", "interval_type",
  "session_user", "session_timezone", "session_schema", "session_role",
  "literal", "interval_expression", "qname", "column_ref", "variable_ref",
  "cast_exp", "case_exp", "case_search_condition_commalist", "when_value",
  "when_value_list", "when_search", "when_search_list", "case_opt_else",
  "nonzero", "nonzerolng", "poslng", "posint", "data_type",
  "subgeometry_type", "type_alias", "varchar", "clob", "blob", "column",
  "authid", "calc_restricted_ident", "restricted_ident", "calc_ident",
  "ident", "non_reserved_word", "lngval", "ident_or_uident", "intval",
  "opt_uescape", "ustring", "blobstring", "sstring", "string", "exec",
  "dealloc_ref", "dealloc", "exec_ref", "opt_path_specification",
  "path_specification", "schema_name_list", "comment_on_statement",
  "catalog_object", "XML_value_expression", "XML_value_expression_list",
  "XML_primary", "XML_value_function", "XML_comment", "XML_concatenation",
  "XML_document", "XML_element",
  "opt_comma_XML_namespace_declaration_attributes_element_content",
  "XML_element_name", "XML_attributes", "XML_attribute_list",
  "XML_attribute", "opt_XML_attribute_name", "XML_attribute_value",
  "XML_attribute_name", "XML_element_content_and_option",
  "XML_element_content_list", "XML_element_content",
  "opt_XML_content_option", "XML_content_option", "XML_forest",
  "opt_XML_namespace_declaration_and_comma", "forest_element_list",
  "forest_element", "forest_element_value", "opt_forest_element_name",
  "forest_element_name", "XML_parse", "XML_whitespace_option", "XML_PI",
  "XML_PI_target", "opt_comma_string_value_expression", "XML_query",
  "XQuery_expression", "opt_XML_query_argument_list",
  "XML_query_default_passing_mechanism", "XML_query_argument_list",
  "XML_query_argument", "XML_query_context_item", "XML_query_variable",
  "opt_XML_query_returning_mechanism", "XML_query_empty_handling_option",
  "XML_text", "XML_validate", "document_or_content_or_sequence",
  "document_or_content", "opt_XML_returning_clause",
  "XML_namespace_declaration", "XML_namespace_declaration_item_list",
  "XML_namespace_declaration_item", "XML_namespace_prefix",
  "XML_namespace_URI", "XML_regular_namespace_declaration_item",
  "XML_default_namespace_declaration_item", "opt_XML_passing_mechanism",
  "XML_passing_mechanism", "opt_XML_valid_according_to_clause",
  "XML_valid_according_to_clause", "XML_valid_according_to_what",
  "XML_valid_according_to_URI", "XML_valid_target_namespace_URI",
  "XML_URI", "opt_XML_valid_schema_location",
  "XML_valid_schema_location_URI", "XML_valid_according_to_identifier",
  "registered_XML_Schema_name", "opt_XML_valid_element_clause",
  "XML_valid_element_clause", "opt_XML_valid_element_name_specification",
  "XML_valid_element_name_specification",
  "XML_valid_element_namespace_specification",
  "XML_valid_element_namespace_URI", "XML_valid_element_name",
  "XML_aggregate", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,    40,
      41,   434,   435,    61,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449,    43,    45,
      38,   124,    94,   450,   451,   452,   453,   454,   455,   456,
     457,    42,    47,    37,   458,   126,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   559,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   575,   576,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   591,   592,
     593,   594,   595,   596,   597,   598,   599,   600,   601,   602,
     603,   604,   605,   606,   607,   608,   609,   610,    44,    46,
      58,    91,    93,    63
};
# endif

#define YYPACT_NINF -2088

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-2088)))

#define YYTABLE_NINF -1245

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   21224,    39, -2088,    99, 19826,   656,   -90,   458,   458, 19826,
     475, -2088, -2088, 19826,   113,   273,   459,   397, -2088, 16070,
   19826, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, 20139,   992,   193,   983,   259,   508, -2088,   284,   726,
   -2088,   731,   648,  1450,   691,  1307, 13879, 14192,   662, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088,   740, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,   911,   739,
     744, -2088, -2088, 19826, -2088,   789, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, 20452, -2088,   544, -2088, -2088, -2088,  6682, 19826, -2088,
     700,   700, -2088, 19826,   129, -2088,   816,   656,  1163, 19826,
     697,   977, -2088, -2088, -2088, -2088,   898, -2088,   752,   816,
   11148, 11148, 21224, 21224, 19826,  1128, -2088,   789, -2088, -2088,
   -2088, -2088,   816,   816, -2088,   867, -2088,   816,   331, -2088,
     198,   859, -2088,   771,   900,   833, -2088, -2088, -2088, -2088,
     904,   929,   389,  1677,  1123,  1168, 17322, 19826,   890,   890,
    7053,   862, -2088,   972,   440,   974,  1254,   996, -2088,  1019,
   -2088, -2088,  -131, -2088, -2088, 11148, -2088,  1089, -2088, -2088,
   -2088,   463,  1036, 19826,  1078, -2088, -2088, 19826, -2088, -2088,
    1016,  1018,  1033,  1052, 19826, 19826,  1020,  1020, -2088,  1012,
   -2088, -2088,  1059,  1134, -2088, -2088,  1155,  1167, 19826, 19826,
    1174, 19826, 19826, 19826,   581, 19826, 19826,   890,   890,   890,
   19826,   890,   890, -2088, -2088, -2088, -2088,  1161, -2088, -2088,
   19826,  1051,  1061,  1111,  1249,  1256,  1256,  1256,  1256,  1260,
    1068,  1169,  1178,   745,   105,  1086, -2088, -2088, -2088,  1168,
    1359,   782,   782,   782,  1156, -2088, -2088, 20452,  1314, -2088,
   19826,  1189, -2088, 19826,  1481,  1481,  1481,  1336,   789,  1314,
    1382,  1313, -2088, -2088, -2088, -2088, -2088,  1323,  1329,  1487,
   -2088, -2088, -2088,  1343,  1343,  1343,  1343,  1343, -2088, -2088,
   -2088,  1349, -2088,  1366,  1377,  1372,  1385,  1394,  1396,  1398,
    1401,  1407,  1418,  1420,  1422,  1427,  1439,  2911,  9279, 10703,
   10703,  1448,  1459,  1470, -2088, 10703,  1314,   638,   668,   503,
    7424,  1492,  1493,  9279, -2088, -2088,   416, 17635,  1362, -2088,
    1379, -2088, -2088, -2088, -2088, -2088, -2088, 19826, -2088, -2088,
   -2088, 14490, -2088, -2088,  1215,  1494, -2088, -2088,  1302, -2088,
   -2088,  1502,  1334, -2088, -2088, -2088, -2088, -2088, -2088,  1314,
    1314,    67,  1314,   789, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,   348,
    1348, -2088,  1397, -2088, 19826, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, 19826,  1350, -2088,  6682, -2088, 20452, -2088, 19826,
   19826, 19826, 19826, 19826, 19826, 19826, -2088,  1416,  7795, 16070,
    1374,  1557,  1559, -2088, -2088,  1128,  1564,  1565,  1357, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088,    90,  1677,    90,  1367,
   11028,   722,  1583,  1586,  1588,     1,  1168,  1393,  1614,  1609,
   -2088,  1344, -2088,  1226,   723,   393,  1605, 19826, 19826, -2088,
     -10, -2088,  1522,  1538,   166,  1539, 19826,  1540,   907, 19826,
   -2088,    83, 19826,  1254,  1402,  1582,  3343, -2088, -2088, -2088,
   -2088, -2088,  1546, -2088, -2088,   938,  1020,  1020,  1020,  1020,
    1483,  1551,  1549, 20765, 19826, 19826,  1020, -2088, -2088, -2088,
     816,  1187, -2088,  1553, -2088, -2088, 19826,  1357, -2088, 19826,
   19826, 19826, -2088, 19826, 19826,  1256,    12, -2088,  1349, -2088,
   19826,  2115, 19826, 19826,  9279, 19826, -2088,   789,  1554, -2088,
     915, -2088, -2088, -2088,  1556,  1560, -2088, -2088, -2088, -2088,
   -2088,  1695, -2088,  1561, -2088, -2088, -2088,  1562,  1566,  1151,
   19826, -2088, -2088, -2088,  1569,  1570,  1571,  1575,  1577, 19826,
   -2088,  9279, -2088, -2088,  1568,  1568,  1568,    64,  1417,  1458,
   -2088, -2088, 17948,  1390, -2088, -2088, -2088,  1585, -2088,  9279,
    9279,  1736,  1581, -2088, -2088, -2088, -2088, -2088,   461, -2088,
   19826,  2019,  1641, 10703, 10703, 10703,  1516,  1603,   934,  1518,
    1764, 10703,   946, 10703,  2911,  1591,  1308,     0,  1054,    87,
    1379,  2911,   950,   950, 10703, 10703, 10703,  1617, -2088,   731,
    1596,   731,  1596, -2088, -2088,  1314,  9279,   386, -2088,   673,
    9279,  9279,  1379,   836, 14505, 19826, -2088,  1408,  9279, -2088,
    9279,  1015,  1491,  1491,  1590,  1593, 10703, 10703, 10703, 10703,
    1015,   310,  1403, 10703, 10703, 10703, 10703, 10703, 10703, 10703,
   10703, 10703, 10703, 10703, 10703, 10703, 10703, 10703, 10703, 10703,
   10703, 10703, 10703, 10703, 10703, 10703, 10703,  1576,  3714,  6682,
    5198, 18261, -2088, -2088, -2088, 14818, -2088, -2088, 16383,  1471,
   -2088,   400, -2088, -2088,  1690,  1703, -2088, -2088,   232, -2088,
    1611,  1668,  1774, -2088, -2088, -2088,  1423, -2088, -2088,  1615,
     855, -2088,  1522,   240, -2088, -2088,    65,  1542, -2088, -2088,
    1357, -2088, -2088, -2088, -2088, -2088, -2088,   -68, -2088, -2088,
   -2088,   -59, -2088,    42, 19826, -2088, -2088, -2088, -2088, -2088,
   -2088,    90,    90, -2088, -2088, -2088,   854,   731,  1168, -2088,
   -2088,  1525,  1226,  1503,  1510, -2088,  1097,  1691,  1623,  1405,
    1405, -2088,  1254, 11507,   393, -2088, -2088, -2088,  1533,  1181,
   -2088,  7053,  4085, 16696,  7053,   816, -2088,  1682,    66,  1526,
     816,  1468,  1254, -2088, -2088,   248, -2088,  1186,  1522,  1226,
    1629, 11507, -2088,   938, -2088, -2088, 19826, 19826, 19826, 19826,
    1563,  1532, -2088,  1698, 19826,  1580,  1579,   573,  1530, 19826,
    1465, -2088, -2088,   377, 18574,  1357, -2088,  1357,  1357,  1357,
   -2088,  1615, 19826, -2088, -2088, -2088,  1314, -2088,  1314,  1562,
    1566,  1405, -2088, -2088, -2088,  1522, -2088, -2088,   731, -2088,
    1796,   731,   731,   731, -2088,  1048,  1596,  1596, -2088, -2088,
   -2088, -2088, -2088,  1566,  1562,  1527, -2088, -2088, -2088,   731,
     731,   731,   731,   731,   105,   954,  1455, -2088,  1716,   113,
     113,   113, -2088, -2088, -2088,    64,  1374,  9279, -2088,  1645,
      33, -2088,  1648, -2088, 19826,   247,   -91, -2088, -2088,   266,
   -2088,  1476, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088,  1726, 19826, 14490,   958, 14490, -2088,   -57, -2088,
    1683, 19826,  1670, 10703,  1479, -2088, -2088, 10703, 19826, -2088,
    1697,   958, -2088, 10703, -2088,  1745,  1325, -2088, -2088, -2088,
    1425,  9279,  2042, 12603, 11655,  1672,  1552,  1314,  1674,  1314,
    1151,   -38,  9279, -2088,   809,  9279, -2088,  1521,   -42,   367,
     292,  9279, -2088, 15131, 13566, -2088,  1488,  1555, 21078, 21078,
   21078,   225,    34, 19826,  1458,  1362,  1379, -2088, -2088, -2088,
    9279, -2088, -2088,  9279,  9279,  5569,  5569, -2088,  2181, -2088,
   -2088, -2088,  9279, -2088,  1741, -2088, 14490,  1985,  1985,  1985,
    1985,  1985,  1985,  1985,  1985,  1985,  1985,   950,   950,   950,
    1617,  1064,  1064,  1064,  1064,  1718,  1718,  1718,  1718,  1718,
   -2088,  1495,  9279,  1680,  9279,   299,   235, -2088, -2088,  9279,
    9279,   323, 19826, -2088,  1687, -2088,   255, -2088, -2088, -2088,
   19826, -2088, 19826,   461, -2088, 14505, 19826,  2798, -2088, -2088,
   -2088, -2088,  9279, -2088, -2088, -2088, -2088, -2088, -2088,  1597,
      90,  1742,  1598,  1742, -2088,    41,    41,  1519,  1769, -2088,
   -2088, -2088, -2088,  1314,  1600, 19826, 19826, -2088, -2088, -2088,
    1405,   999,  1254,  1254, -2088, -2088, -2088,  1572,   762,  1326,
      81,  1574,  1330, -2088, -2088,   340,   349,  1753, 16070, -2088,
    1757,  1541,  1295,    66,  1756, -2088, -2088, -2088,  5569,  1606,
    1405, -2088, -2088,  1700,  1700,  1700,  1700, 19826,   130, -2088,
   -2088, -2088,  1859,  1599, 19826,  1639, 17009,  1781, -2088,  1543,
   19826,  1700,   440, -2088,  1545, -2088, -2088,  1608, -2088,  1709,
    1528, 11507, -2088, -2088, -2088, -2088,  1357, -2088,  1710, -2088,
   -2088,  1713,   351,  1714,  1529, -2088,   364, -2088, -2088, -2088,
   -2088,  1607,  1201,  1715,  1535,  1720,  1724,  1727,  1729, -2088,
   -2088, -2088,  1673,  9279,  1731, -2088, -2088, -2088, -2088, -2088,
    1594,  1522,  1349, 17948,  1458,  7053, -2088, 11507, 11507, -2088,
   19826, 19826, 10703, -2088,   948,  1733, 10703,  1734,  1737, -2088,
    1548, 10001, 14490,  -156, -2088,  1584, -2088,   383, -2088,  1558,
    1798,  1683,  1744,  1759,  1683,   548,  1746,  1751,  1379, 10703,
   10703, 10703, 10703, -2088,  1604, -2088, -2088, -2088, -2088,  9279,
     418, -2088,  1610,  1522, -2088,  9279,  9279, -2088,  9279,  1379,
   21078, 21078, 13566,  1754,  1758,  1760,  1452, 14505, -2088, -2088,
   -2088,  1480,  1852, -2088,  1854,  1861, 19826, -2088,  1762, -2088,
   -2088, -2088, 16070, -2088, -2088,  1578,  1613,  1825,  1592,  1183,
    1216,   371,   379,  1314,  1665, -2088,   382, -2088,   388,  1602,
   15444,   417,   441, -2088,  1763,  1618, -2088, 19826, -2088, -2088,
     837,  1612, -2088,  1768,  1616,  1522,  1669, -2088,   130, -2088,
    1671, -2088, -2088, -2088, -2088, -2088, -2088,  1933,  1314, -2088,
   -2088,  1254, -2088,  1254, -2088, -2088, 19826, 19826, 19826, -2088,
   -2088, 19826, 19826, 19826,  1858,  1547, 19826, 19826, -2088, 19826,
   19826, 18887, -2088, -2088,   840, -2088,  1619, -2088,  1314, -2088,
   -2088,  1757,    91, -2088,  1314,  1254, -2088,  1620,  1675, -2088,
   -2088, -2088, -2088, -2088,  1667, 19826,   852, -2088, -2088, 16070,
   19826, 19826,   443, -2088, -2088, -2088, -2088, -2088,   910, -2088,
    2748,    94, 19826, -2088,   440,  1777,  1681,  1776, 19826, 19826,
    1717, 19826, -2088, -2088, -2088, -2088, -2088,   731, -2088,   731,
   -2088,   731,  1566, -2088, -2088, -2088,   731, -2088, -2088, -2088,
   -2088,  1404, -2088, -2088, 19826,    70, -2088, -2088, -2088, -2088,
   -2088,  1782,  1785, -2088,  1622, 12927, -2088, -2088, -2088, -2088,
   -2088, -2088,  9650,  1683,  1704, 10703, 14490,   464, -2088,  1627,
   -2088, -2088,   998, 10703,  1683, 19826, -2088,  1811,  1816,  1788,
   10703,  1683,    25, 10703, -2088,  1798, -2088,  1679,  1799, -2088,
    1800,  5569,  5569, 12295,  3094, 13243, 11971, -2088,  1522,  9279,
   -2088,   824,  1522,  1522, -2088, -2088, -2088, -2088, -2088,  1555,
    1897, 14505, 14505, -2088, -2088,  1803, 19826,   260, 19826,  1804,
    1870,  1873,  9279,  9279, -2088, -2088, -2088, -2088, -2088,  1807,
   -2088, -2088, -2088,  1880,  1883, -2088,  9279, 19826, -2088, 11507,
   -2088, -2088, -2088,  1637,  1705, -2088, -2088, -2088,  1357,  1357,
    1357, -2088,  1699, -2088, -2088, -2088, -2088,  1647,   563,  1647,
   -2088,  1314,  1526,  1628, -2088, -2088,  1314,  1631, -2088,  1818,
    1818,  1747, -2088,  1892, -2088,  1314, 19826,  1633, -2088,  1589,
     562, -2088,   852, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, 17009,  1725,  1728,   816, -2088, -2088, -2088,
   -2088,  1095,  1721,  1314,  1828, 19826,  1927, -2088,  1775, -2088,
    1633,  1656,  2840, 11670, 11507,  1834,  1835,  1837, -2088,  1838,
   -2088, -2088,   497, -2088, -2088, -2088, -2088, -2088,  1840, 14490,
    1654, -2088,  -151, -2088,  1655,  1844, -2088, -2088, -2088, 10001,
   19826,  1748,  1749,  1752,  1755, -2088, -2088,  1845, -2088, -2088,
   -2088, -2088, -2088,   964,  1853, -2088, -2088,   467,  1664, -2088,
   -2088, -2088,    48, -2088,  1866, -2088, -2088,   502,   509, 10703,
   -2088, -2088, 10703, -2088, 10703,  1522, -2088, 14505, -2088,   437,
   19826,   510, -2088, 19826,  5940,  9279, -2088,   -70,   -70, -2088,
    9279,  1929,    21,   607, -2088, -2088,  1767,  1765, -2088, -2088,
   -2088, 19826,  1684, -2088,  1783,   856, -2088,   514,  1953,  1314,
   -2088,  1314, 19826,    66,  1526,  1314,  -193,  1867, -2088, -2088,
   -2088,  1868,   816,   816, -2088,  1914, -2088,  9279, -2088,  1095,
   -2088, -2088, -2088, -2088,   844,  1871, -2088,   784, -2088,   515,
     543,  1778,  1294,  1935,  1875, -2088, -2088,   656,   475,  1693,
    1809, 16070,  2053,  4456,  8166,  9279,    -1, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088,  1735, -2088, -2088, -2088, -2088,  1694, -2088,
   -2088, -2088, -2088, -2088, -2088, 10703, 10703, 10703, -2088, 10352,
   -2088, -2088, -2088, -2088,  1944,   927,  1949,  1951, -2088, -2088,
   19826, -2088, -2088, 10703,  1791,  1795,  1895,   466, -2088, -2088,
   13559, 13872, 14185, -2088,   816,  9279, -2088,   518, -2088,  1899,
    1898,  1901,   830,  2421,  1719, -2088,  1522,  1522,  1722,  9279,
   -2088, -2088, -2088, -2088,  4827,   378, -2088,  1761,  1314, 19826,
   -2088,   865, -2088,   888, -2088,  1964,  9279, -2088,  1847, -2088,
   -2088,  1730,   519, -2088,  1314,  1009,    66,  1802, -2088, -2088,
      88,    93, -2088,  1797, -2088,  1740, -2088,  1522, -2088, -2088,
    1969,  1915,  1817, 19826, -2088, -2088, -2088,   841,  1918, -2088,
   -2088,  2010,  2011, -2088, -2088,   365,   504,  1294, -2088,  1750,
   -2088,  1779, 19826,  6682, 19826, -2088,  1922, -2088,  1276,  1924,
   -2088, -2088,  1522,  9279, -2088,   838,   640,   600, -2088, 12618,
    9279, -2088, 14490,   525, -2088,  1766, -2088, -2088,  1738, -2088,
   -2088,  1946, -2088, -2088, -2088,  1798, -2088,  1950,  1952, -2088,
    1958, 19826,  2106,   880, -2088, -2088, -2088, -2088, -2088, -2088,
    1522, -2088, -2088, 19200, 19200,  1934, -2088,  5940,  1455,  6311,
    1787,  1771,   489,  1780, -2088, -2088,  1916,  2062, -2088, -2088,
   -2088,  8537,  2018,  1959, -2088, -2088, -2088, -2088, -2088, -2088,
    1314, -2088, 19826, -2088,  2029, -2088,  1757,  1009, 19826,  1963,
    1966, -2088,  1314,  1876, 19826,  2012, -2088,  9279, -2088,   816,
     527, -2088, -2088, -2088, -2088,  1619, -2088,  1619,  1619,  1619,
   -2088,  1301,  1971, 13250,   534, 11507,  1877, -2088,  1786,  9279,
   -2088, -2088, -2088,   461,   620, -2088, -2088,  1820,  9279, -2088,
     864, -2088, 12618,  2016,   578, -2088, 10703, 19826, -2088, 10703,
   -2088, -2088, -2088, -2088,  1986, -2088, -2088, -2088,  1986, -2088,
    1988, 19826,  2106, -2088, -2088, -2088,  1997, 19826,   564, -2088,
   -2088,   571, 15757, -2088,  1297,   399, -2088,  1967, -2088, -2088,
   -2088, -2088,    58, -2088,  9279,  1841,  1916,  2030,  1869,  1522,
    1872,  9279, -2088, -2088, -2088,  2107,  1757, -2088,  9279, 19826,
    1226,  1314,   816,  1989,   909,  2048, -2088,   841, 19826, 19826,
   19826, 19826, -2088, -2088, -2088,  9279,  1843, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, 19826, -2088,
   19826,   582,  1522,  1992, -2088, 11986,  1851,   644, -2088,  1842,
   11341,  2037,  1846, -2088, -2088, -2088, -2088, -2088,  2106, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,   583, -2088,
   19200, -2088,  1999,  2000,  2063, 19513, -2088,   587, -2088, -2088,
   -2088,  6311,  1819, -2088,  1836, -2088,  1522,  1587,  1860, -2088,
    8908, -2088, -2088,   588,  1522, -2088,  2124,  2107,  2008,  1522,
    2009,  1919, -2088,  2048,   938, -2088, -2088,  1024,  1912, -2088,
   -2088, -2088, -2088, -2088,  1001, -2088, 11507, -2088, -2088,  9279,
   -2088, 11986,  2052, -2088, -2088,  1888, -2088,  9279,  1865,  1878,
   -2088, 12302, -2088, -2088, -2088, -2088, 19200, 19200,  2014, -2088,
   -2088, 15757, -2088, -2088, -2088, -2088,  1906, -2088,  2141,  2085,
    2038,  1522,  2038,  9279,  2152,  1953,  2124, -2088, -2088,  1314,
    1912,   920, -2088, -2088, -2088, -2088,  1595,  1937,  1939, -2088,
   -2088, 12934, -2088,  1522, -2088, 11986, -2088, 11986,   682,  1891,
   -2088,  1890,   589,   606, 15757, -2088, 17948,   816, -2088, -2088,
    2105, -2088, -2088, -2088, -2088, -2088,  1953, -2088, -2088, -2088,
     220,   220,  2156, -2088,  2157, -2088, -2088,  2084, -2088, -2088,
   19826, -2088, -2088,   608,  1862,   400,  1931,  1886, -2088, -2088,
    2187,   422, -2088, -2088, -2088, 11341, -2088, -2088, -2088, -2088,
   -2088,  2055, -2088, -2088, -2088, -2088, -2088,  1254,   616, -2088,
   -2088,  1254, -2088
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,    18,     0,     0,   574,     0,   490,   490,     0,
       0,   468,    16,     0,     0,     0,    26,     0,    35,     0,
       0,     7,     5,     9,    11,    20,    19,    22,    21,    25,
      33,     0,     0,    98,    34,     0,     0,   469,   521,     0,
       3,     0,    23,    27,     0,     0,     0,     0,     0,    42,
      43,    36,    37,    38,    41,    39,   162,   161,   158,   159,
     160,    45,   163,    40,   460,   459,     0,   467,   466,   461,
     462,   464,   465,   463,   597,   618,   608,   609,   677,     0,
       0,    46,    17,     0,  1014,  1117,  1016,  1018,  1019,  1034,
    1072,  1090,  1037,  1047,  1061,  1084,  1039,  1036,  1041,  1066,
    1058,  1085,  1087,  1062,  1045,  1035,  1063,  1067,  1069,  1025,
    1046,  1050,  1110,  1112,  1107,  1106,  1108,  1097,  1102,  1100,
    1101,  1099,  1105,  1109,  1104,  1103,  1098,  1111,  1031,  1054,
    1017,  1088,  1089,  1023,  1053,  1071,  1060,  1065,  1092,  1070,
    1033,  1048,  1068,  1059,  1076,  1057,  1091,  1077,  1038,  1029,
    1030,  1027,  1028,  1074,  1081,  1064,  1073,  1075,  1078,  1082,
    1049,  1042,  1024,  1026,  1043,  1044,  1032,  1051,  1055,  1079,
    1094,  1095,  1093,  1056,  1096,  1052,  1083,  1080,  1022,  1040,
    1086,   853,  1021,   932,  1020,   575,   576,     0,     0,   489,
     493,   493,   471,     0,     0,   600,   317,   574,     0,     0,
       0,     0,   831,   829,   830,   374,     0,   826,   828,   317,
       0,     0,     0,     0,  1042,   542,  1008,  1117,  1010,  1011,
    1012,   117,   317,   317,   116,   112,   118,   317,     0,   122,
       0,     0,   102,   104,     0,   113,   114,    88,  1013,  1007,
       0,     0,     0,     0,     0,   477,     0,     0,    29,    29,
       0,   616,  1113,     0,     0,     0,     0,     0,   311,     0,
     314,   313,     0,   958,     1,     0,  1116,     0,   959,  1127,
      24,     0,     0,     0,     0,   191,   192,     0,   233,   232,
       0,     0,     0,     0,     0,     0,    31,    31,   190,     0,
     156,   157,     0,   329,   326,   325,   333,   327,     0,     0,
     331,     0,     0,     0,     0,     0,     0,    29,    29,    29,
       0,    29,    29,   905,   907,   906,   913,  1084,   911,   909,
       0,   912,   910,  1043,     0,    56,    56,    56,    56,     0,
     938,  1088,  1089,    31,     0,    49,    50,    51,     2,   477,
       0,   619,   619,   619,   679,    13,    14,   853,     0,  1015,
    1022,     0,   855,     0,  1123,  1119,  1121,  1014,  1117,  1016,
    1018,  1019,   917,   916,   915,   918,   919,     0,     0,     0,
    1004,   929,   930,   838,   838,   838,   838,   838,   785,   784,
     786,     0,   569,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   849,     0,  1026,  1043,  1044,  1032,
       0,     0,     0,     0,   794,   790,   632,   853,   674,   710,
     676,   701,   702,   703,   704,   705,   706,     0,   707,   774,
     773,   708,   745,   791,     0,     0,   787,   792,   625,   847,
     778,     0,   777,   783,   856,   923,   782,   781,   780,     0,
       0,   935,     0,  1117,   925,  1125,   914,   793,  1151,  1152,
    1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,   869,   560,
       0,   470,   494,   472,     0,   604,   606,   607,   605,   598,
     603,   602,     0,     0,   318,     0,   617,   853,    28,     0,
       0,     0,     0,     0,     0,     0,  1146,     0,     0,     0,
     685,     0,     0,    10,    12,   542,     0,     0,   456,  1009,
     119,   120,   111,   121,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   477,     0,     0,     0,
     476,   478,   479,   196,     0,     0,     0,     0,     0,   571,
       0,   565,   570,     0,   935,     0,     0,     0,   677,     0,
     523,     0,     0,     0,   522,     0,     0,  1129,  1128,  1130,
     237,   236,     0,   235,   234,   168,    31,    31,    31,    31,
       0,    82,     0,     0,     0,     0,    31,   330,   334,   328,
     317,     0,   332,     0,   448,   165,     0,   456,   447,     0,
       0,     0,   449,     0,     0,    56,     0,   908,     0,    55,
       0,     0,     0,     0,     0,     0,  1114,  1117,   984,   998,
     960,   999,  1001,  1002,   973,   976,   968,   969,   971,   972,
     970,   979,   981,   991,   995,   994,   879,   876,   878,     0,
       0,   982,   983,    53,   986,   961,   962,   966,   989,     0,
     474,     0,   620,   621,   622,   622,   622,     0,   682,   581,
    1118,   854,     0,   933,  1124,  1120,  1122,  1015,   926,     0,
       0,     0,     0,   833,   835,   834,   837,   836,     0,   736,
       0,     0,     0,     0,     0,     0,     0,  1194,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   676,     0,
     709,     0,   770,   771,     0,     0,     0,   765,   920,     0,
     874,     0,   874,   870,   871,     0,     0,     0,   952,   954,
       0,     0,   737,     0,     0,     0,   610,   630,     0,   852,
       0,   711,   719,   719,     0,     0,     0,     0,     0,     0,
     711,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   779,   927,   924,     0,   928,  1126,     0,     0,
     562,   560,   558,   491,     0,     0,   473,   599,     0,   307,
       0,   632,     0,  1145,  1139,  1140,     0,  1141,  1144,   451,
       0,   824,   798,     0,   827,   828,     0,    47,     8,     6,
     456,   544,   543,   458,   457,   546,   125,    92,   123,   126,
      89,    90,   105,   329,  1042,   103,   110,   109,   115,    99,
     101,     0,     0,   475,   482,   481,     0,     0,     0,   198,
     197,     0,   196,     0,     0,   138,     0,     0,   177,   872,
     872,   187,     0,     0,   166,   171,   180,    30,     0,     0,
     563,     0,     0,     0,     0,   317,   312,     0,   515,   496,
     317,     0,     0,     4,  1131,     0,   567,   573,   572,   196,
       0,     0,   164,   167,   169,   175,     0,     0,     0,     0,
       0,     0,   194,     0,  1023,    71,    67,   317,     0,     0,
       0,   413,   414,     0,   409,   456,   446,   456,   456,   456,
     450,   451,     0,   320,    58,    61,     0,    63,     0,   876,
     878,   872,    64,    60,    62,    57,   939,  1115,     0,  1000,
       0,     0,     0,     0,   980,     0,   874,   874,   882,   883,
     884,   885,   886,   878,   876,     0,   903,   904,    52,     0,
       0,     0,     0,     0,     0,   695,   678,   692,   623,     0,
       0,     0,   681,   680,   957,     0,   685,     0,   541,     0,
     632,   577,     0,  1006,     0,     0,     0,  1005,   839,     0,
     662,   935,   890,   891,   892,   894,   895,   893,   888,   896,
     887,   889,     0,     0,     0,   745,  1150,  1148,  1231,  1147,
    1231,     0,     0,     0,     0,  1229,  1230,     0,     0,  1211,
    1212,   745,  1228,     0,  1227,   677,     0,   744,   743,   772,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   949,   954,     0,   953,     0,     0,     0,
       0,     0,   739,     0,     0,   642,   633,   634,   641,   647,
     647,   932,   632,     0,   581,   673,   675,   714,   712,   713,
       0,   720,   721,     0,     0,     0,     0,   722,   726,   724,
     723,   725,     0,   729,     0,   740,   761,   746,   747,   752,
     762,   751,   766,   767,   768,   769,   845,   748,   749,   750,
     763,   753,   758,   756,   754,   755,   757,   759,   760,   764,
     851,   865,     0,     0,  1028,     0,   935,   848,   859,     0,
    1028,     0,   796,   776,  1019,   850,   936,   561,   559,   492,
       0,   319,     0,     0,   601,     0,     0,     0,   441,  1138,
    1137,   825,     0,   687,   688,   686,    48,    44,   545,     0,
       0,    94,     0,    94,   108,    94,    94,     0,     0,   488,
     483,   484,   480,     0,     0,     0,     0,   185,   183,   188,
     872,   872,     0,     0,   186,   176,   172,     0,   155,   155,
       0,   155,   155,   566,   865,     0,     0,     0,     0,   520,
     526,     0,     0,   515,     0,   524,   525,  1132,     0,     0,
     872,   173,   170,   317,   317,   317,   317,     0,     0,    32,
      68,    70,     0,  1133,     0,     0,   277,   199,   243,     0,
       0,   317,     0,   416,   418,   415,   417,     0,   408,     0,
     407,     0,   444,    66,   442,   445,   456,    59,     0,   956,
    1003,     0,     0,     0,   956,   996,     0,   997,   880,   881,
     901,   900,     0,     0,   956,     0,     0,     0,     0,    54,
     696,   697,   698,     0,     0,   613,   614,   615,   684,   683,
     689,   582,     0,     0,   581,     0,   934,     0,     0,   788,
       0,     0,     0,   789,     0,     0,     0,     0,     0,  1173,
    1165,     0,  1199,  1186,  1196,  1200,  1195,   745,  1207,  1208,
       0,  1231,     0,  1248,  1231,   743,     0,     0,   735,     0,
       0,     0,     0,   875,     0,   921,   877,   922,   931,     0,
       0,   950,     0,   955,   945,     0,     0,   943,     0,   738,
       0,   647,     0,   642,     0,     0,   587,     0,   592,   593,
     594,   587,     0,   588,     0,   590,  1022,   639,   646,   648,
     637,   636,     0,   611,   628,   631,     0,   649,   716,     0,
       0,     0,     0,     0,   715,   728,     0,   863,     0,   866,
       0,     0,     0,   860,     0,   800,   797,     0,   495,   308,
     587,  1142,   453,     0,   454,   799,     0,   124,     0,    87,
       0,    86,    96,    97,   485,   486,   487,     0,     0,   139,
     143,     0,   179,     0,   184,   182,     0,     0,     0,   154,
     130,     0,     0,     0,     0,     0,     0,     0,   129,     0,
       0,   277,   866,   564,     0,   501,   428,   504,     0,   497,
     498,   526,     0,   568,     0,     0,   203,   213,     0,   205,
     321,    84,    85,    83,     0,     0,    73,  1134,    69,     0,
       0,     0,     0,   252,   248,   250,   253,   251,     0,   254,
       0,  1006,     0,   201,     0,     0,   238,   315,     0,     0,
     336,     0,   411,   443,   985,   963,   974,     0,   977,     0,
     992,     0,   878,   898,   902,   987,     0,   964,   965,   967,
     990,     0,   694,   693,     0,     0,   612,   580,   578,   547,
     579,     0,     0,   663,   936,     0,  1233,  1232,  1161,  1149,
    1162,  1163,     0,  1231,  1036,     0,  1240,     0,  1235,     0,
    1237,  1238,     0,     0,  1231,     0,  1198,     0,     0,     0,
       0,  1231,     0,     0,  1214,  1221,  1225,     0,     0,  1249,
       0,     0,     0,     0,     0,     0,     0,   873,   951,     0,
     944,     0,   946,   947,   640,   638,   583,   742,   741,   635,
       0,     0,     0,   591,   589,   644,     0,   933,     0,     0,
       0,   671,     0,     0,   730,   731,   727,   868,   867,     0,
     862,   861,   775,     0,   802,   937,     0,     0,   452,     0,
      93,    95,    91,     0,   142,   181,   178,   141,   456,   456,
     456,   135,     0,   132,   133,   131,   137,   227,     0,   227,
     127,     0,   496,   537,   539,   429,     0,   516,   503,   509,
     509,     0,   174,     0,   204,     0,     0,  1136,  1135,    27,
       0,    65,    74,    75,    77,    78,    81,    79,    80,   202,
     309,   278,   242,   277,     0,     0,     0,   276,   255,   256,
     258,   259,     0,     0,   245,     0,     0,   207,     0,   310,
     419,   420,     0,   399,     0,     0,     0,     0,   899,     0,
     700,   699,     0,   691,   690,   940,   941,   832,     0,  1185,
    1170,  1172,  1186,  1183,  1166,     0,  1243,  1242,  1234,     0,
       0,     0,     0,     0,     0,  1187,  1197,     0,  1202,  1201,
    1204,  1205,  1203,   745,     0,  1247,  1246,   745,  1213,  1215,
    1217,  1218,     0,  1222,     0,  1226,  1273,     0,     0,     0,
     842,   843,     0,   844,     0,   948,   942,     0,   584,   587,
       0,     0,   629,   796,     0,     0,   626,   717,   718,   864,
       0,     0,   804,     0,  1143,   455,     0,     0,   152,   153,
     151,     0,     0,   134,     0,     0,   128,     0,   535,     0,
     527,     0,     0,   515,   496,     0,     0,   229,    72,    76,
     249,  1006,     0,     0,   303,     0,   273,     0,   257,   260,
     261,   266,   267,   268,     0,     0,   200,     0,   244,     0,
       0,     0,     0,   433,     0,   335,   406,   574,  1039,   468,
       0,     0,  1033,     0,     0,     0,   343,   355,   356,   349,
     350,   351,   354,   352,   338,   340,   357,   368,   367,   372,
     371,   370,   369,     0,   353,   348,   347,   358,     0,   410,
     975,   978,   993,   988,   624,     0,     0,     0,  1182,     0,
    1164,  1236,  1239,  1241,     0,     0,     0,     0,  1193,  1206,
       0,  1219,  1245,     0,     0,     0,     0,     0,   732,   733,
       0,     0,     0,   586,     0,     0,   585,     0,   645,     0,
       0,     0,     0,     0,   650,   651,   653,   672,   801,     0,
     806,   807,   808,   795,     0,     0,   555,   557,     0,     0,
     136,     0,   148,     0,   146,     0,     0,   538,     0,   502,
     540,   517,     0,   511,   513,   528,   515,     0,   209,   208,
       0,   196,   206,     0,   304,     0,   269,   270,   262,   298,
       0,     0,     0,     0,   299,   271,   302,   277,     0,   247,
     189,     0,     0,   241,   316,   430,   430,   421,   422,     0,
     412,   437,     0,     0,     0,   373,     0,   376,     0,  1042,
     381,   380,   382,     0,   390,   392,     0,     0,   343,   399,
       0,   400,  1180,     0,  1175,  1178,  1171,  1184,  1167,  1169,
    1188,     0,  1191,  1190,  1189,  1244,  1216,     0,     0,  1210,
       0,     0,     0,  1262,  1251,  1252,   840,   841,   846,   596,
     595,   643,   627,     0,     0,     0,   657,     0,   803,     0,
       0,     0,     0,   819,   809,   810,   548,     0,   556,   140,
     144,     0,     0,     0,   228,   150,   149,   147,   145,   536,
       0,   510,     0,   514,     0,   529,   526,   528,     0,     0,
       0,   214,     0,     0,     0,     0,   297,     0,   300,   317,
       0,   264,   246,   239,   240,   428,   431,   428,   428,   428,
     423,     0,     0,   399,     0,     0,     0,   337,     0,   377,
     323,   339,   324,     0,     0,   343,   391,     0,     0,   387,
     392,   343,   399,     0,     0,  1174,     0,     0,  1177,     0,
    1192,  1220,  1223,  1224,  1257,  1261,  1260,  1256,  1257,  1255,
       0,     0,     0,  1250,  1263,  1264,  1266,     0,     0,   658,
     661,     0,     0,   652,     0,     0,   814,     0,   815,   813,
     811,   812,     0,   805,     0,     0,   548,     0,     0,   216,
       0,     0,   518,   512,   530,   531,   526,   195,     0,     0,
     196,     0,   317,   274,     0,   295,   263,   277,     0,     0,
       0,     0,   435,   436,   434,     0,   469,   363,   364,   361,
     362,   439,   365,   432,   360,   359,   366,   405,     0,   403,
       0,     0,   378,     0,   343,   393,     0,     0,   388,     0,
     395,     0,   344,   343,  1176,  1181,  1179,  1168,     0,  1254,
    1253,  1269,  1272,  1268,  1271,  1270,  1265,  1267,     0,   654,
       0,   655,     0,     0,     0,     0,   666,     0,   664,   817,
     818,     0,     0,   821,     0,   822,   549,     0,     0,   217,
       0,   226,   220,     0,   215,   532,   533,   531,     0,   210,
       0,     0,   231,   295,     0,   272,   306,   291,   286,   265,
     427,   425,   426,   424,     0,   345,     0,   322,   375,     0,
     383,   389,     0,   385,   343,     0,   343,     0,     0,   344,
     341,   399,  1259,  1258,   660,   659,     0,     0,     0,   670,
     656,     0,   816,   823,   820,   551,     0,   553,     0,     0,
     222,   218,   222,     0,     0,   535,   533,   212,   211,     0,
     286,     0,   293,   294,   292,   296,     0,   287,   288,   301,
     438,   399,   404,   379,   344,   386,   384,   396,     0,     0,
     342,     0,     0,     0,     0,   665,     0,   317,   554,   219,
       0,   225,   224,   221,   534,   500,   535,   230,   305,   275,
       0,     0,     0,   290,     0,   289,   440,     0,   343,   394,
     401,   667,   668,     0,   550,   560,     0,   505,   280,   281,
       0,     0,   285,   284,   346,   395,   398,   402,   669,   552,
     223,     0,   499,   279,   282,   283,   397,     0,     0,   507,
     506,     0,   508
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -2088,  1447, -2088, -2088, -2088, -2088, -2088,  2189,    36, -2088,
   -2088,  -944, -2088,   989,  -136,  -928, -2088, -2088,   810, -2088,
      18,  -251, -2088,  -180,    22,   128, -2088,  1041, -2088, -2088,
   -2088,   624, -2088,   870,     3,  1996, -2088, -2088,   188,    10,
   -2088, -2088,  2026, -2088,  1732, -2088, -2088, -2088,  1770,  -422,
    1120,    49, -2088, -2088, -2088,   206,   107, -2088, -2088,    52,
   -2088,  -871,  1426,  -447, -2088, -2088, -2088,  -808, -2088,  2205,
   -2088, -2088, -2088, -2088,    16, -2088, -2088, -2088,    20, -2088,
     686, -2088, -2088, -2088,   149, -2088, -2088, -2088,   875,   654,
   -2088, -2088, -2088, -2088, -2088, -2088, -1667, -2088,   402, -2088,
   -2088, -2088, -2088, -1129,   -22,    15,    17,    27, -2088,    85,
   -2088, -2088, -2088, -1258, -2088, -2088,  -231,  -458, -2088,  -190,
    -411, -2088, -2088, -2088, -2088,    75, -2088, -2088, -2088, -1860,
   -2088, -1568,    28, -1917, -2088,   289, -2088, -2088, -2088, -2088,
   -2088, -2088,   236, -2088,   355, -2088,   250, -2088,   -27, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
   -2088,   384,  -577,   387, -2088, -2088, -2088, -2088, -2088,  1790,
     117,  1406,   736,  -547,    26,    38, -2088, -2088,    50, -2088,
    1484, -2088,  2300,  2120, -2088, -1004, -2088, -2088, -2088,   713,
   -2088,   312, -1137, -2088, -2088, -1376,   311,   122,    80, -2087,
     908,   746,  2144,  1848, -2088,  2145,   244, -2088, -2088,   474,
   -2088,  2148,  2149,  -754, -2088,  1497,  -984, -2088,  -795,  1200,
    -184,    59,  1093,  -922,  -953,  1031, -2088, -2088, -2088,    45,
   -2088,  1917, -2088, -2088,    14,   111,   491,  1322,  1022,  -465,
    1347,   842, -2088, -2088,  1435, -2088,  -680,  -949,  -938, -2088,
   -2088,   429, -1881, -1959,  -641,   123,   167, -2088,   -32,  1696,
    1414, -2088, -2088,  1453, -2088,   552,  1170, -2088, -2088, -2088,
    -350,  1692, -2088, -2088,  1689, -2088,   687, -2088, -2088, -2088,
   -2088, -2088,  1688, -2088,  1658,  -353, -2088,  1621, -2088,  -616,
    -622,   708, -2088,  -708, -2088, -2088, -2088, -2088, -2088,   575,
     246, -2088, -2088, -2088,   -11,   -18,  -429, -2088,   916, -2088,
   -2088,  1702,   505, -2088, -2088, -2088,  -755,  -450,  -536,  -598,
   -2088,  -627, -2088, -2088, -2088, -2088, -2088,  1431, -2088,  2396,
   -2088, -2088, -2088,  1855, -2088,   642,  -658,   -15, -2088, -2088,
   -2088,  1419, -2088,  1743, -2088,  1429,   669,  1634,  -249,  -250,
    -293, -2088,  -330, -2088, -2088,  -288, -1157,    23, -2088, -2088,
   -2088,    -4, -2088,  -588,  -280,    19,  -111, -2088, -2088,  1185,
    -286, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
    -609, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,
     627, -2088,   391, -2088, -2088, -2088, -1641, -2088,   637,   793,
   -2088, -2088, -2088, -2088,   955, -2088, -2088, -2088, -2088, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088, -2088, -2088,   626, -2088,
   -2088, -2088, -2088, -2088, -2088, -2088,  1793,  -937,   965, -2088,
     795, -2088,   967, -2088, -2088,   526, -1155, -2088, -2088, -2088,
   -2088, -2088, -1254,   405, -2088, -2088, -2088, -2088, -2088, -2088,
     404, -2088, -2088, -2088, -2088
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,   265,   211,   210,   212,   213,    40,    41,   271,
      42,    43,    44,   537,   574,    45,    46,    47,    48,  1127,
    1787,   334,   335,   600,  1788,  1789,   885,  1190,  1193,  1611,
    1612,  1613,   882,  1423,  1790,   230,  1133,  1131,  1369,  1791,
     242,   243,   231,   232,   233,   815,   234,   235,   236,   807,
     808,  1792,   835,  1398,  1390,  1391,  1793,    56,   872,   873,
     844,   874,   845,   875,    57,   289,   290,   831,  1443,   291,
    1890,  2198,  2011,  1604,  2192,  2098,  2250,  2193,  2291,  1994,
    1733,  1892,   292,  1637,  1197,  1198,  1768,  1432,  1433,  1434,
    1630,  1435,  1758,  1759,  1436,  2020,  1760,  1761,  1896,  1762,
    1763,  2205,  1437,  1764,  2322,  2267,  2268,  2269,  2265,  2208,
    1905,  1627,  1906,   778,  1439,    58,   257,   258,  1639,  1199,
     484,   324,    59,  2037,  2041,   312,  1643,    60,  1794,  1939,
    2271,  2222,  2131,  1796,  1797,  1798,  1925,  1926,  2141,  1799,
    1931,  1800,  2049,  2050,  1934,  1935,  2047,  1801,  2228,  1802,
    1803,  2326,  2034,  1775,  1209,  1210,    62,   893,  1207,  1773,
    1917,  1918,  1596,  2027,  1920,  1921,  2124,  2033,  2133,   496,
    1804,  1118,  1363,   805,  1805,  1806,    66,    67,   530,   531,
     532,  1140,   190,   471,   776,  1173,    68,  2332,  2338,  1743,
    1882,  1883,  1170,  1171,   259,  1407,  2006,  2196,  2255,  1879,
    1592,  1593,    69,   508,    70,    71,  2095,  2247,  2288,  1866,
    1867,    72,    73,   772,   251,   540,   865,   415,   541,   866,
     187,   960,   961,   958,  1035,  1324,  1544,  1325,  1846,   260,
     194,   195,   479,    75,  1807,   261,    78,   644,   949,   416,
     716,  1334,  1335,  1044,   717,  1036,  1316,  1329,  1330,  1551,
    1854,  1855,  2078,  2079,  2168,  2177,  2178,  1716,   792,   418,
     344,   648,   956,   797,  1476,   946,   947,  1242,  1472,   419,
     420,  1050,   421,   422,  1053,   423,  1057,   424,   425,   689,
     426,   713,   427,   428,  1038,   429,   430,   431,   762,   432,
     433,  1354,  1355,   793,  1564,  1722,  1863,  1864,  1983,  2086,
    2087,  1985,  2088,  2093,  1039,   543,   207,   436,   663,   437,
     438,   439,   351,   440,   441,   442,   705,  1017,   700,   702,
     631,   934,   981,   982,   935,  1464,   936,   937,   632,   443,
     326,   327,   328,   444,   445,  1040,   446,   337,   447,   448,
    1030,  1023,  1024,   708,   709,  1027,  1218,   953,   262,   267,
    1364,  1226,   449,   635,   636,   450,   962,   809,   238,   239,
     182,   544,   184,   263,   452,  1219,   349,   453,   454,   455,
     456,    79,   559,    80,   269,  1426,  1427,  1608,    81,   497,
     987,   988,   989,   457,   458,   459,   460,   461,  1493,  1270,
    1660,  1943,  1944,  2058,  1945,  2156,  1661,  1662,  1663,  1504,
    1675,   462,   993,  1273,  1274,  1275,  1506,  1679,   463,  1509,
     464,  1279,  1511,   465,  1000,  1281,  1513,  1688,  1689,  1690,
    1691,  1692,  1836,   466,   467,  1003,   997,  1265,   994,  1497,
    1498,  1823,  1499,  1500,  1501,  1831,  1832,  1518,  1519,  1963,
    1964,  2068,  2069,  2159,  2233,  1965,  2066,  2073,  2074,  2166,
    2075,  2076,  2165,  2163,   468
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     183,   206,  1182,    52,   634,   192,   483,   550,   205,   196,
      53,   770,   970,   485,    76,   208,   183,  1108,    49,   500,
     781,   558,    50,   547,  1144,   952,    64,   183,   669,   969,
     927,   329,   510,   511,  1037,  1598,  1411,   513,    65,  1440,
     896,   633,   330,   330,   980,    74,   637,   688,   690,    54,
    1095,  1267,  1101,  1268,   638,   237,  1163,   985,   771,   954,
     268,  1179,   650,   712,  1282,  1001,   990,  1438,   229,   596,
     794,  1341,  1342,   658,  1005,  1795,   252,   252,  2052,   183,
    1123,  1313,   266,  1169,  1152,  1153,   354,   355,   846,  1327,
    -469,   926,  1898,  2081,   354,   355,   811,   216,   217,   218,
     219,   220,  1331,   718,  1888,  2009,   509,    55,  1264,  1129,
    1860,    77,   606,   607,   608,   609,  2132,    63,  1132,   301,
     698,   822,  1337,  2176,  1502,  1514,   610,   730,    51,  1502,
     611,   612,   613,   369,   370,   614,   615,   616,   617,   618,
     619,   620,   621,   622,  1165,  2182,   601,   602,   603,  2012,
     573,  1394,   718,   714,   714,   417,   718,  1685,   623,   624,
     625,  1368, -1031,   763,   764,  1834,   766,  1607,  2295,   435,
     850,  1889,  2183,  1395,  1124,  1946,   434,   352,  1949,    82,
    1009,  1686,   197,   451,   183,  2145,   188,  1421,   553,   473,
    1640,  2150,   903,  1422,   718,   183,     3,     4,     5,     6,
    -100,  -100,  -100,  -100,  -100,   554,  1835,   731,   480,  2317,
     183,  2235,  1503,    52,    52,    52,    52,  1817,   542,    83,
      53,    53,    53,    53,    76,    76,    76,    76,    49,    49,
      49,    49,    50,    50,    50,    50,    64,    64,    64,    64,
    2021,   959,   534,   183,  1440,   904,  -828,   657,    65,    65,
      65,    65,  1019,  1128,   954,    74,    74,    74,    74,    54,
      54,    54,    54,  2318,  2319,   859,   237,  1010,    52,   562,
    1591,  1632,  1438,   183,  -307,    53,   495,  1258,   229,    76,
     183,   571,  2176,    49,  2221,   577,  1299,    50,  1711,    61,
     268,    64,    14,  2231,   183,   183,   252,   183,   584,   183,
    1130,   183,   588,    65,   861,   481,   183,  2320,    14,  1130,
      74,  1266,   253,   770,    54,   246,   330,    55,    55,    55,
      55,    77,    77,    77,    77,  2176,  1305,    63,    63,    63,
      63,  1938,  1479,  1248,   688,  1230,   794, -1031,    51,    51,
      51,    51,   767,   352,  1515,  -828,   651,  1520,  1212,   653,
    1213,  1214,  1215,   197,  2132,  2282,  2283,    15,   851,  1313,
    1693,  1534,   829,   830,  2275,   687,  2277,  2010,  1396,   517,
    1046,  2053,    55,  1535,  1397,   806,    77,  1769,   707,   586,
     630,  1277,    63,   247,  1346,  1861,  1348,  1862,   944,   640,
     890,  1351,  1352,    51,  1283,  1381,  1383,   846,  1231,  1135,
    1136,  1253,   630,  -519,  -828,   626,   627,   628,   629,  1130,
      36, -1031,  1111,   352,  -828,   902,  2184,   197,  2157,  1020,
    1121,  2185,   858,   183,   794,  1415,    36,  1063,  1177,  1599,
     876,   877,   878,   879,  -828,  1360,   765,   414,   414,  -828,
     889,   718,   685,   414,  1203,  1204,  1259,  1205,  2325,  1986,
    2209,   514,  1847,   417,  1844,  1011,   221,   222,   223,   224,
    1480,    13,  -307,   254,  1042,   240,  1440,   435,   241,   197,
     196,  1507,  1307,   630,   434,   266,  1228,  1229,   779,  1349,
     836,   451,  1609,   352,  2151,   183,   784,   183,   786,   183,
     183,   183,  1064,   516,  1438,   795,   917,   474,  1610,    61,
      61,    61,    61,  1353,  1120,   198,  -872,  -872,  2321,   197,
    1318,  1319,  1320,   634,  1321,  1322,   183,  1323,   837,   838,
    1402,   839,   840,   841,   868,    13,   842,   768,   255,  1403,
     197,  1456,  1508,   848,   183,   853,   714,  1697,  1698,  2334,
     810,   634,   183,   189,  1460,   183,   248,  1125,   183,   199,
    1155,  1554,   249,  1960,    61,   637,  1665,   229,   193,  1555,
    1987,   718,  1557,   638,  1384,  1385,   517,  1677,  1558,   886,
     183,   888,   915,   225,  1684,  1512,   823,    13,  1181,    14,
     718,    36,   183,   637, -1244,   183,   183,   183,  1738,   183,
     183,   638,  1257,   718,  1332,   495,   905,  1560,   913,   914,
    1112,   916,  1483,   256,  1350,  1463,  1885,   515,  1122,   945,
    1911,   769,   718,  1176,   634,   938,  1178,    13,   302,   254,
     658,  1561,   698,  1622,  1357, -1244,   330,   965,   966,   964,
    2105,  1912, -1244,  1961,  1260,   330,  1962,  1539,    13,  1227,
      14,  -876,  -876,  1206,  1668,    36,   181,   557,   963,    27,
      28,  1239,   687,   200,  -617,   226,   637,  1489,  2025,   687,
    1308,  1288,   209,   769,   638,  1167,   971,  1122,  1609,  1453,
    1174,  -878,  -878,   215,  1021,   227,   201,  1814,  1028,  1029,
    1310,  1309,  1838,   718,  1610,  2335,   303,   250,  -617,  1839,
    1848,  1122,   715,  1195,  1877,  1910,   206,    36,  1971,  2001,
    1338,   703,   704,  1339,  1340,  2055,  1249,  2116,  1122,  1022,
    1041,   330,  1344,   685,  2137,  2026,  1845,   851,  1015,  1457,
    1018,  -617,  -617,  -617,   228,   347,   264,   417,  -617,   685,
    2197,  1295,  1461,  1297,   293,  1306,   685,    36,   843,  1178,
    1886,   435,  1529,   266,  2169,   548,   304,  1178,   434,  2007,
    1122,  2171,  1196,   293,  1096,   451,  1122,  1103,    36,  2180,
    2091,  1106,  2218,  2234,   779,  2035, -1042,  2240,  2252,  2311,
   -1042, -1042,   718, -1042, -1042, -1042, -1042, -1042, -1042, -1042,
   -1042, -1042, -1042, -1042,  -617,  1122,  2312,   634,  2328,   221,
     222,   223,   224,  1575,   718,  1576,  2340,  2028,  1382, -1042,
   -1042,   718,   338,   305,   294,   295,   296,   297,  1913,  1122,
     183,  1623,  1830,  -617,   718,  -876,   970,   699,  2164,   542,
    -617,  -617,   542,   294,   295,   296,   297,  1602,  1734,   637,
     469,   339,  1669,  1652,   718, -1244,   306,   638,   718,  -617,
     185,   487,   959,   354,   355,  -878,  1141,   701,  1096,  1106,
    2091,  1735,   649,  1653,  2026,   308,   505,  1377,   354,   355,
     309,  1708,  1709,   293,  1648,  1260,  -617,  -617,  -617,  -617,
    1178,  1908,   183,   183,   183,   183,   718,  1178,  1112,   345,
    1191,   634,  1739,  1112,   346,   183,  1112,  2002,   686,   535,
    1211,   354,   355,  2056,  1683,  2117,   470,  1687,  1217,  1477,
     832,   348,  2138,   794,  2232,   310,    25,    26,   311,  2153,
    1318,  1319,  1320,   353,  1321,  1322,  -617,  1323,  1452,   565,
     186,   794,   719,   637,  2051,  1251,   570,   634,   634,   300,
    1865,   638,  2170,   294,   295,   296,   297,   919,   920,  2170,
     580,   581,  1224,   583,  2144,   585,  1137,   587,   300,  1975,
    2219,  1260,   592,  1138,  1139,  2241,  2253,  2170,  1234,  1873,
    1256,  1899,  1909,  2048,  1481,  1482,   642,  2070,  2224,   637,
     637,  1447,  1119,  1874,  2170,  1755,  2241,   638,   638,   183,
    1756,  2216,    27,    28,  2341,  1991,  1992,  1269,   226,   298,
    1300,   833,   782,  1303,  1278,   482,   706,  1387,  1025,   216,
     217,   218,   219,   220,  1706,  1995,  2308,   836,   227,   670,
     870,   834,  1858,   340,  1951,   206,   206,   340,   718,  1591,
     501,   502,  1311,   868,   868,   836,  1900,  1843,   870,   208,
    1041,  1728,  1729,  1730,  1328,  1328,  1328,   299,  1875,  1336,
    2071,   488,   244,  2072,  1952,   837,   643,   867,   839,   840,
     841,   354,   355,   842,  1993,  1388,  1389,  1556,   300,   221,
     222,   223,   224,   837,  2262,  2263,   839,   840,   841,   732,
    1002,   842,  1486,   572,   245,   555,  1431,   498,  1901,  1314,
     341,   342,   343,  2013,   341,   342,   343,   486,    16,  2206,
    1365,   733,  1574,   995,   921,   996,  2004,   206,  1356,  2264,
    2299,   489,  1225,   718,  1757,   995,  1358,   996,  1359,  1487,
     634,  1041,  1361, -1042, -1042,  1671,  1566,    30,  1594,  1876,
    2005,   499,  1597,  1264,    32,    33,  1594,  1902,  1601, -1209,
    1903,   783,  1022,   785,  1025,   787,   788,   789, -1231,   519,
    1904,  1379,  1380,    35, -1209,  1315,   868,  1631,   718,   293,
     206,   512,   637,  1672,   518,  1673,  1674,  1405,  1314,   686,
     638,  1933,   817,  2045,   208,   747,   748,   749,   750,   751,
     752,   753,   754,   755,   756,  1006,   225,  1624,   668,   520,
     849,  2270,   686,  1420,   522,  1240,  1241,  2048,   855,  2045,
    1191,   857,  1441,  1625,   860,   718,   183,   703,   704,  1047,
    1048,   521,  1717,  1718,  1031,   733,  1626,  1645,  1032,   523,
    1049,   945,  -277,  1634,   526,  1754,   887,  1687,   536,   294,
     295,   296,   297,   542,  1315,  1147,  1148,  1149,   895,  1755,
     545,   897,   898,   899,  1756,   900,   901,   721,   538,   634,
     722,   723,   724,   725,   726,   727,   728,   729,   546,   963,
     549,   730,    27,    28,   506,   507,   971,  1484,   226,   198,
     527,   560,   561,   528,   490,   871,   252,  1528,   556,   529,
     491,   492,   551,  1531,  1532,   493,  1533,  -277,   227,   354,
     355,   637,  2040,   871,   752,   753,   754,   755,   756,   638,
     664,   665,   666,   667,   206,   552,   589,   590,   591,   206,
     593,   594,  2201,   563,   564,  1594,  1328,  1328,  1041,   566,
    1740,   567,   634,  1041,   634,  2080,  2080,   354,   355,  1747,
     494,  1371,  1545,  1372,  1373,  1930,   568,   228,  1547,  -277,
    1431,   731,  1416,  1417,  1418,  1419,   341,   342,   343, -1114,
   -1114,  1893,  1894,   486,   300,   569,  1106,  1766,   572,  1776,
    1446,  1809,   576,  1565,   637,   575,   637,  1314,  1757,   341,
     342,   343,   638,   302,   638,  1393,   721,  1399,  1401,   722,
     723,   724,   725,   726,   727,   728,   729,   577,  -277,  1552,
     730,  -277,  1577,  1578,   183,  -998,  -998,  1580,  1581,  1582,
    1182,  -277,  1586,   183,   595,  1588,   183,   963,   578,   721,
     803,   804,   722,   723,   724,   725,   726,   727,   728,   729,
     579,   206,  1553,   730,  1059,  1060,  1061,   582,  1619,   970,
   -1081,   779,  -734,  1315,  2080,   208,   183,  1621,   597,  1614,
   -1082,   303,   598,  1969,   773,   774,  1615,   605,  1633,   599,
    1245,  1246,  1247,   604,   779,   183,  1158,  1644,  2118,  1159,
    2119,  2120,  2121,  1880,   639,  1881,  1134,   928,  2036,  1887,
     731,   929,  -233,   930,   931,   932,   933,   641,   272,  1160,
     971,  -232,  1161,  1162,   647,  1616,   268,   652,  1646,   293,
    1647,   341,   342,   343,   354,  1649,   824,   825,  1008,   868,
     868,   304,  -857,   731,  1654,   829,   830,  1705,   341,   342,
     343,  1678,   659,   688,   672,  1285,   273,   928,   660,   274,
     661,   929,  2080,   930,   931,   932,  1462,   970,  1183,  1184,
    1185,  1186,   662,   206,   206,  1318,  1319,  1320,   668,  1321,
    1322,  1201,  1323,  1617,  1723,   891,   892,  1041,  1041,   654,
     655,   656,   779,  1618,  1336,   670,   867,   867,   305,   294,
     295,   296,   297,  1318,  1319,  1320,   671,   275,   720,   276,
    1323,  2329,   721,  1724,   673,   722,   723,   724,   725,   726,
     727,   728,   729,   674,   277,   675,   730,   676,  2080,  2080,
     677,   306,  1989,  2080,   757,  2143,   678,  1996, -1115, -1115,
    1221,  1222,  1223,  1923,   307,  1051,  1052,   679,  2003,   680,
     308,   681,  1748,   703,   704,   309,   682,   272,  1233,  1235,
    1236,  1237,  1238,  1286,  1287,  1614,  1374,  1375,   683,  1751,
    1389,  1392,  1615,  1400,  1389,  1263,  2080,   694,  1318,  1319,
    1320,   779,  1321,  1322,  -587,  1323,  1409,  1410,   695,  1808,
    1584,  1585,  2042,  1650,  1651,   273,  1915,  1916,   274,   696,
     310,  2122,  2123,   311,  2245,  2246,   731,  2179,  2090,   503,
     504,  1616,  2300,  2301,   645,   646,  1822,   950,   951,   867,
     759,   710,   711,   758,   300,   278,   279,   280,   281,   282,
     283,   760,  1856,  1857,   216,   217,   218,   219,   220,   206,
     761,   284,   775,   790,   796,   780,   275,   798,   276,   799,
     801,   802,   228,  1041,   819,   634,   779,   820,   821,  1356,
     826,   827,   828,   277,  2102,   847,   718,   852,   854,  1617,
     856,   862,   863,   869,   285,  1897,  2110,  1870,   881,  1618,
     880,   883,   894,   918,   924,   922,   955,   286,  1884,   923,
     925,   699,  2139,   287,   948,   701,   288,   637,   939,   940,
     941,  1932,  1936,  1937,   942,   638,   943,   957,   733,   964,
     967,   968,   983,   206,   991,   992,   998,   999,  1107,  1055,
     205,  1007,  1056,  1016,   413,  1043,  1109,  1041,   722,   723,
     724,   725,   726,   727,   728,   729,  1110,  1090,   714,   730,
    1113,  1115,  1116,  -193,  1117,  1126,  1143,  1146,  1145,  1150,
    1151,  1157,  1168,   548,  1175,  1172,  1180,  1188,  1189,  1200,
    1202,  1187,  1194,  1970,   278,   279,   280,   281,   282,   283,
    1220,   687,  1232,  1243,  1244,  2202,  1955,   945,  1252,  2115,
     284,  1255,  1982,   748,   749,   750,   751,   752,   753,   754,
     755,   756,  1445,  1192,  1897,  1261,  1262,  1276,  1264,  1271,
    1280,   340,  1293,  1294,  1296,  1304,  1317,   770,  1345,   733,
    1347,  1376,  1368,   285,  -824,  1990,  -858,  1386,  1389,   731,
    1370,  1378,  1366,  1404,  1406,   959,  1412,  1414,  1408,  1196,
    1424,  1425,   287,  1429,  1442,   288,   634,  1449,  1444,  1450,
    1454,   417,  1448,  1455,  1458,  1465,  1451,  1459,   685,   183,
    1467,  2044,  -897,  1466,  1468,   435,  1512,  1469,  2054,  1470,
    1474,  1471,   434,  1488,  1490,  1475,  1492,  1491,   963,   451,
    2038,  1527,  2203,  2272,  1516,  1521,  1510,  1517,   637,  1505,
    1522,  1541,  -193,  1542,  1536,  1808,   638,  1543,  1537,  1550,
    1538,  1546,   731,  1562,  1530,  1856,  1548,  2085,  1568,  1570,
    1573,  1572,  1583,  1638,  1605,  1606,  1635,  2065,  1549,  2099,
    1636,  1680,  1655,  1642,  1595,  1656,  1681,  1666,  1682,   971,
     971,  -825,  1670,  2297,  1694,  1563,  1707,  1603,  1714,  1695,
    1696,  1567,  1710,  1713,  1569,  2114,  1715,  1719,  1720,  1721,
    1726,  1357,  1732,  1727,  1731,  1745,  1739,  1742,  1884,  1741,
    1746,  1112,  1765,  1752,  2107,  1767,  1753,  2142,  1770,  1771,
     183,  1772,   867,   867,  1810,  1811,  2147,  1812,  1813,  1815,
     692,   693,  1816,  1819,  1820,  1828,   697,  1824,  1825,  1808,
    1579,  1826,  1833,  1829,  1827,  1837,  2129,  1859,  1868,  1587,
    1878,  1871,  1589,  2130,  1891,  1632,  1872,  2136,  1808,  1895,
    1907,  2127,  1869,  2155,  1922,  2128,  1919,  1924,  1914,  2134,
    1928,  1950,  2186, -1041,  1941,  1940,  1953,  2162,  1954,  2194,
    1957,  2135,  1620,   971,  1958,  1959,  2199,  1973,   971,  1972,
    1974,  1997,  1999,  2014,  1865,  2015,  2016,  1977,  2339,  2008,
    1122,  1641,  2342,  2214,  2017,  2018,  2022,  2315,  2000,  2023,
    2024,  2039,  2032,  2043,  2031,  2200,  2059,  2060,  2062,  2067,
    2063,  2057,  2094,  2082,  2210,  2211,  2212,  2213,   354,   355,
     356,  2064,   606,   607,   906,   609,   733,   362,   363,   364,
     365,   366,  2090,  2096,   963,  2100,  2217,  2089,  2101,  2092,
    2104,  1808,  2108,   369,   370,  2109,  1808,  2111,  2113,  2085,
    2125,  2161,  2158,   715,  2146,  2140,  2152,  2071,  2251,  2189,
     371,   372,  1289,  2181,  2190,  2187,   971,  2195,  2204,  2191,
    2207,   971,  2220,  2223,   907,  2215,  2225,  2229,  2236,  2237,
    2230,  2243,  2238,   733,  2248,  2254,  2244,  2273,  2257,  2258,
    2259,  2266,  2274,  2284,  2286,  2278,   744,   745,   746,  2279,
     747,   748,   749,   750,   751,   752,   753,   754,   755,   756,
    2276,  2287,  2280,  2289,  2294,  2290,  2302,  1808,  2304,  2309,
    2310,  2194,  2316,  2300,  2324,  2301,  2331,  1808,  2330,  2333,
    1253,   270,   971,   971,  2337,  1428,  1749,   971,  1571,   525,
     734,   735,   736,   737,   738,   739,   740,   741,   742,   743,
    1367,   812,   336,   744,   745,   746,  2261,   747,   748,   749,
     750,   751,   752,   753,   754,   755,   756,  1808,   524,  2293,
    1156,  1808,  2292,  1808,  2129,  1736,  1590,  1750,  1998,  2323,
     971,  2130,   963,  2305,  2303,  2136,  2148,  2298,  2260,  2127,
    2046,   818,  1343,  2128,   984,   986,   986,  2134,  2336,  2307,
    2149,  2030,   984,  2029,   986,  1725,  2327,  1216,   191,  2135,
     816,   472,  1142,  1744,  2103,  1012,  1013,  1014,  2106,  2256,
    1600,  1808,   733,   972,   973,   928,   974,   975,   976,   929,
     977,   930,   931,   932,   978,   979,  2296,  1737,   475,   476,
    2188,  1988,   477,   478,   686,  2314,  1478,  1058,  1058,  1058,
    1058,  1166,  1540,   800,  1066,  1067,  1068,  1069,  1070,  1071,
    1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,  1080,  1081,
    1082,  1083,  1084,  1085,  1086,  1087,  1088,  1089,  1413,   734,
     735,   736,   737,   738,   739,   740,   741,   742,   743,  1333,
    1712,   777,   744,   745,   746,  1254,   747,   748,   749,   750,
     751,   752,   753,   754,   755,   756,  2083,  2313,  2285,  1250,
    1290,  1978,  1054,  1473,  1045,   908,   909,   910,   911,  1284,
    1065,  1849,  1062,  1927,   354,   355,   356,  2242,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,  1114,  1984,
     367,   368,   325,  1301,    89,    90,  1948,  2154,    91,   369,
     370,  1298,  1026,  1302,  1947,  1818,   912,  1664,  1676,  1956,
      92,  1097,  1667,    93,  1821,     0,   371,   372,   373,   374,
     375,   376,   377,  2160,    94,  1004,  1154,   313,   314,   315,
    2167,  2061,     0,     0,   378,    95,   379,   380,     0,     0,
     197,   202,     0,     0,   203,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,   100,   101,   102,     0,     0,     0,     0,     0,
     103,   381,     0,   104,     0,     0,     0,     0,   382,   383,
       0,     0,     0,   105,   384,  2019,   106,     0,     0,   107,
     108,   109,   385,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,   386,   387,   388,   389,     0,   390,   391,
     112,   113,   392,   393,   114,   394,   115,   116,   117,   118,
     119,   120,   121,     0,   122,   395,   123,   124,   125,   126,
       0,   127,   396,   128,     0,     0,     0,     0,    13,   129,
     684,  1976,   130,   398,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1272,     0,     0,     0,   984,   399,
     400,     0,     0,     0,   986,     0,     0,     0,     0,   401,
     402,   403,     0,     0,     0,     0,   405,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,     0,     0,
       0,     0,     0,     0,   133,     0,  2112,     0,   134,   135,
     136,   137,   138,     0,     0,     0,     0,     0,     0,   139,
       0,     0,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,   152,     0,     0,     0,     0,
       0,     0,   153,     0,     0,   154,     0,     0,     0,   155,
       0,     0,   156,   157,     0,   158,     0,     0,   159,     0,
     160,     0,     0,     0,   161,   162,     0,     0,    36,     0,
       0,   406,   407,   408,   409,   167,   168,     0,   169,   170,
     171,     0,   172,     0,     0,     0,     0,   173,   174,     0,
       0,     0,     0,   410,     0,     0,     0,   411,   412,     0,
       0,     0,     0,     0,     0,   606,   607,   608,   609,     0,
       0,     0,   175,   176,     0,   177,   178,     0,     0,   610,
       0,   179,   180,   611,   612,   613,   369,   370,   614,   615,
     616,   617,   618,   619,   620,   621,   622,     0,     0,     0,
       0,     0,   413,     0,   414,     0,     0,     0,     0,     0,
       0,   623,   624,   625,     0,   606,   607,   608,   609,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   610,
       0,     0,     0,   611,   612,   613,   369,   370,   614,   615,
     616,   617,   618,   619,   620,   621,   622,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   606,   607,   608,
     609,   623,   624,   625,     0,     0,     0,     0,     0,     0,
       0,   610,     0,     0,     0,   611,   612,   613,   369,   370,
     614,   615,   616,   617,   618,   619,   620,   621,   622,     0,
       0,     0,     0,  1485,     0,  1628,  1629,   986,     0,     0,
       0,     0,  1496,   623,   624,   625,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1523,  1524,  1525,  1526,   354,   355,   356,     0,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,     0,     0,
     367,   368,     0,     0,    89,    90,     0,     0,    91,   369,
     370,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,     0,     0,    93,     0,     0,   371,   372,   373,   374,
     375,   376,   377,     0,    94,     0,     0,   313,   314,   315,
       0,     0,     0,     0,   378,    95,   379,   380,  1362,     0,
     197,   202,     0,     0,   203,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,   100,   101,   102,     0,     0,     0,     0,     0,
     103,   381,     0,   104,     0,     0,     0,     0,   382,   383,
       0,     0,     0,   105,   384,     0,   106,     0,     0,   107,
     108,   109,   385,   110,   111,     0,     0,     0,   626,   627,
     628,   629,     0,   386,   387,   388,   389,     0,   390,   391,
     112,   113,   392,   393,   114,   394,   115,   116,   117,   118,
     119,   120,   121,     0,   122,   395,   123,   124,   125,   126,
       0,   127,   396,   128,     0,     0,     0,     0,    13,   129,
     684,     0,   130,   398,     0,     0,     0,     0,   626,   627,
     628,   629,     0,     0,     0,     0,     0,     0,     0,   399,
     400,     0,     0,  1659,     0,     0,  1496,     0,     0,   401,
     402,   403,     0,     0,  1272,     0,   405,     0,     0,     0,
       0,   984,     0,  1774,   984,     0,   131,   132,     0,     0,
     626,   627,   628,   629,   133,     0,     0,     0,   134,   135,
     136,   137,   138,     0,     0,     0,     0,     0,     0,   139,
       0,     0,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,   152,     0,     0,     0,     0,
       0,     0,   153,     0,     0,   154,     0,     0,     0,   155,
       0,     0,   156,   157,     0,   158,     0,     0,   159,     0,
     160,     0,     0,     0,   161,   162,     0,     0,    36,     0,
       0,   406,   407,   408,   409,   167,   168,     0,   169,   170,
     171,     0,   172,     0,     0,     0,     0,   173,   174,     0,
       0,     0,     0,   410,     0,   733,     0,   411,   412,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   175,   176,     0,   177,   178,     0,     0,     0,
       0,   179,   180,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1701,     0,     0,     0,     0,     0,
       0,     0,   413,     0,   414,     0,     0,     0,     0,     0,
    1496,     0,   734,   735,   736,   737,   738,   739,   740,   741,
     742,   743,     0,     0,     0,   744,   745,   746,     0,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   756,     0,
    1840,     0,     0,  1841,     0,  1842,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   354,   355,   356,     0,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
       0,     0,   367,   368,     0,     0,    89,    90,     0,     0,
      91,   369,   370,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,     0,     0,    93,     0,     0,   371,   372,
     373,   374,   375,   376,   377,     0,    94,     0,     0,   313,
     314,   315,     0,     0,     0,     0,   378,    95,   379,   380,
       0,     0,   197,   202,     0,     0,   203,   204,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    96,     0,     0,
      97,     0,     0,    98,     0,     0,  1942,  1659,  1659,    99,
    1659,     0,     0,     0,   100,   101,   102,     0,     0,     0,
       0,     0,   103,   381,   984,   104,     0,     0,     0,     0,
     382,   383,  1702,     0,     0,   105,   384,     0,   106,     0,
       0,   107,   108,   109,   385,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,   386,   387,   388,   389,     0,
     390,   391,   112,   113,   392,   393,   114,   394,   115,   116,
     117,   118,   119,   120,   121,     0,   122,   395,   123,   124,
     125,   126,     0,   127,   396,   128,     0,     0,     0,     0,
       0,   129,   684,   864,   130,   398,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   399,   400,     0,     0,     0,     0,     0,     0,     0,
       0,   401,   402,   403,     0,     0,     0,     0,   405,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,   132,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
     134,   135,   136,   137,   138,     0,     0,     0,     0,     0,
       0,   139,     0,     0,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,     0,   152,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   154,     0,     0,
       0,   155,     0,     0,   156,   157,     0,   158,     0,     0,
     159,     0,   160,     0,     0,     0,   161,   162,     0,     0,
      36,     0,     0,   406,   407,   408,   409,   167,   168,     0,
     169,   170,   171,     0,   172,     0,     0,     0,     0,   173,
     174,     0,     0,     0,     0,   410,     0,     0,     0,   411,
     412,     0,     0,     0,     0,     0,     0,  1942,     0,     0,
    1659,     0,     0,     0,   175,   176,     0,   177,   178,     0,
       0,     0,     0,   179,   180,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   413,     0,   414,   354,   355,   356,
       0,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,     0,     0,   367,   368,     0,     0,    89,    90,     0,
       0,    91,   369,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,     0,     0,    93,     0,     0,   371,
     372,   373,   374,   375,   376,   377,     0,    94,     0,     0,
     313,   314,   315,     0,     0,     0,     0,   378,    95,   379,
     380,     0,     0,     0,   202,     0,     0,   203,   204,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,    97,     0,     0,    98,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,   100,   101,   102,     0,     0,
       0,     0,     0,   103,   381,     0,   104,     0,     0,     0,
       0,   382,   383,     0,     0,     0,   105,   384,     0,   106,
       0,     0,   107,   108,   109,   385,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,   386,   387,   388,   389,
       0,   390,   391,   112,   113,   392,   393,   114,   394,   115,
     116,   117,   118,   119,   120,   121,     0,   122,   395,   123,
     124,   125,   126,     0,   127,   396,   128,     0,     0,     0,
       0,     0,   129,   397,  1091,   130,   398,     0,  1092,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   399,   400,     0,     0,     0,     0,     0,     0,
       0,     0,   401,   402,   403,  1093,     0,     0,     0,   405,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,     0,     0,     0,     0,     0,     0,   133,     0,     0,
       0,   134,   135,   136,   137,   138,     0,     0,     0,     0,
       0,     0,   139,     0,     0,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     0,  1094,     0,
       0,     0,     0,     0,     0,   153,     0,     0,   154,     0,
       0,     0,   155,     0,     0,   156,   157,     0,   158,     0,
       0,   159,     0,   160,     0,     0,     0,   161,   162,     0,
       0,     0,     0,     0,   406,   407,   408,   409,   167,   168,
       0,   169,   170,   171,     0,   172,     0,     0,     0,     0,
     173,   174,     0,     0,     0,     0,   410,     0,     0,     0,
     411,   412,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   175,   176,     0,   177,   178,
       0,     0,     0,     0,   179,   180,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   413,     0,   414,   354,   355,
     356,     0,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,     0,     0,   367,   368,     0,     0,    89,    90,
       0,     0,    91,   369,   370,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,     0,     0,    93,     0,     0,
     371,   372,   373,   374,   375,   376,   377,     0,    94,     0,
       0,   313,   314,   315,     0,     0,     0,     0,   378,    95,
     379,   380,     0,     0,     0,   202,     0,     0,   203,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
       0,     0,    97,     0,     0,    98,     0,     0,     0,     0,
       0,    99,     0,     0,     0,     0,   100,   101,   102,     0,
       0,     0,     0,     0,   103,   381,     0,   104,     0,     0,
       0,     0,   382,   383,     0,     0,     0,   105,   384,     0,
     106,     0,     0,   107,   108,   109,   385,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,   386,   387,   388,
     389,     0,   390,   391,   112,   113,   392,   393,   114,   394,
     115,   116,   117,   118,   119,   120,   121,     0,   122,   395,
     123,   124,   125,   126,     0,   127,   396,   128,     0,     0,
       0,     0,     0,   129,   397,  1164,   130,   398,     0,  1092,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   399,   400,     0,     0,     0,     0,     0,
       0,     0,     0,   401,   402,   403,  1093,     0,     0,     0,
     405,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,   132,     0,     0,     0,     0,     0,     0,   133,     0,
       0,     0,   134,   135,   136,   137,   138,     0,     0,     0,
       0,     0,     0,   139,     0,     0,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     0,  1094,
       0,     0,     0,     0,     0,     0,   153,     0,     0,   154,
       0,     0,     0,   155,     0,     0,   156,   157,     0,   158,
       0,     0,   159,     0,   160,     0,     0,     0,   161,   162,
       0,     0,     0,     0,     0,   406,   407,   408,   409,   167,
     168,     0,   169,   170,   171,     0,   172,     0,     0,     0,
       0,   173,   174,     0,     0,     0,     0,   410,     0,     0,
       0,   411,   412,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   175,   176,     0,   177,
     178,     0,     0,     0,     0,   179,   180,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   413,     0,   414,   354,
     355,   356,     0,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,     0,     0,   367,   368,     0,     0,    89,
      90,     0,     0,    91,   369,   370,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    92,     0,     0,    93,     0,
       0,   371,   372,   373,   374,   375,   376,   377,     0,    94,
       0,     0,   313,   314,   315,     0,     0,     0,     0,   378,
      95,   379,   380,     0,     0,   197,   202,     0,     0,   203,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,     0,     0,    97,     0,     0,    98,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,   100,   101,   102,
       0,     0,     0,     0,     0,   103,   381,     0,   104,     0,
       0,     0,     0,   382,   383,     0,     0,     0,   105,   384,
       0,   106,     0,     0,   107,   108,   109,   385,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,   386,   387,
     388,   389,     0,   390,   391,   112,   113,   392,   393,   114,
     394,   115,   116,   117,   118,   119,   120,   121,     0,   122,
     395,   123,   124,   125,   126,     0,   127,   396,   128,     0,
       0,     0,     0,    13,   129,   684,     0,   130,   398,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   399,   400,     0,     0,     0,     0,
       0,     0,     0,     0,   401,   402,   403,     0,     0,     0,
       0,   405,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,     0,     0,     0,     0,     0,     0,   133,
       0,     0,     0,   134,   135,   136,   137,   138,     0,     0,
       0,     0,     0,     0,   139,     0,     0,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,     0,
     152,     0,     0,     0,     0,     0,     0,   153,     0,     0,
     154,     0,     0,     0,   155,     0,     0,   156,   157,     0,
     158,     0,     0,   159,     0,   160,     0,     0,     0,  1929,
     162,     0,     0,    36,     0,     0,   406,   407,   408,   409,
     167,   168,     0,   169,   170,   171,     0,   172,     0,     0,
       0,     0,   173,   174,     0,     0,     0,     0,   410,     0,
       0,     0,   411,   412,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   175,   176,     0,
     177,   178,     0,     0,     0,     0,   179,   180,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   413,     0,   414,
     354,   355,   356,     0,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,     0,     0,   367,   368,     0,     0,
      89,    90,     0,     0,    91,   369,   370,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92,     0,     0,    93,
       0,     0,   371,   372,   373,   374,   375,   376,   377,     0,
      94,     0,     0,   313,   314,   315,     0,     0,     0,     0,
     378,    95,   379,   380,     0,     0,     0,   202,     0,     0,
     203,   204,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    96,     0,     0,    97,     0,     0,    98,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,   100,   101,
     102,     0,     0,     0,     0,     0,   103,   381,     0,   104,
       0,     0,     0,     0,   382,   383,     0,     0,     0,   105,
     384,     0,   106,     0,     0,   107,   108,   109,   385,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,   386,
     387,   388,   389,     0,   390,   391,   112,   113,   392,   393,
     114,   394,   115,   116,   117,   118,   119,   120,   121,     0,
     122,   395,   123,   124,   125,   126,     0,   127,   396,   128,
       0,     0,     0,     0,     0,   129,   397,     0,   130,   398,
       0,     0,     0,     0,  1979,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   399,   400,     0,     0,     0,
       0,     0,     0,     0,     0,   401,   402,   403,     0,     0,
       0,     0,   405,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,     0,     0,   134,   135,   136,   137,   138,     0,
       0,     0,     0,     0,     0,   139,     0,     0,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
       0,   152,     0,     0,     0,     0,     0,     0,   153,     0,
       0,   154,     0,     0,     0,   155,     0,     0,   156,   157,
       0,   158,     0,     0,   159,     0,   160,     0,     0,     0,
     161,   162,     0,     0,     0,     0,     0,   406,   407,   408,
     409,   167,   168,     0,   169,   170,   171,     0,   172,     0,
       0,     0,     0,   173,   174,     0,     0,     0,     0,   410,
       0,     0,     0,   411,   412,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   175,   176,
       0,   177,   178,     0,     0,     0,     0,   179,   180,     0,
       0,     0,     0,     0,     0,  1980,     0,     0,     0,     0,
       0,     0,  1981,     0,     0,     0,     0,     0,   413,     0,
     414,   354,   355,   356,     0,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,     0,     0,   367,   368,     0,
       0,    89,    90,     0,     0,    91,   369,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,     0,
      93,     0,     0,   371,   372,   373,   374,   375,   376,   377,
       0,    94,     0,     0,   313,   314,   315,     0,     0,     0,
       0,   378,    95,   379,   380,     0,     0,     0,   202,     0,
       0,   203,   204,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,    97,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
     101,   102,     0,     0,     0,     0,     0,   103,   381,     0,
     104,     0,     0,     0,     0,   382,   383,     0,     0,     0,
     105,   384,     0,   106,     0,     0,   107,   108,   109,   385,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
     386,   387,   388,   389,     0,   390,   391,   112,   113,   392,
     393,   114,   394,   115,   116,   117,   118,   119,   120,   121,
       0,   122,   395,   123,   124,   125,   126,     0,   127,   396,
     128,     0,     0,     0,     0,     0,   129,   397,  1098,   130,
     398,     0,  1099,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   399,   400,     0,     0,
       0,     0,     0,     0,     0,     0,   401,   402,   403,     0,
       0,     0,     0,   405,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,   134,   135,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   139,     0,     0,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,  1100,     0,     0,     0,     0,     0,     0,   153,
       0,     0,   154,     0,     0,     0,   155,     0,     0,   156,
     157,     0,   158,     0,     0,   159,     0,   160,     0,     0,
       0,   161,   162,     0,     0,     0,     0,     0,   406,   407,
     408,   409,   167,   168,     0,   169,   170,   171,     0,   172,
       0,     0,     0,     0,   173,   174,     0,     0,     0,     0,
     410,     0,     0,     0,   411,   412,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175,
     176,     0,   177,   178,     0,     0,     0,     0,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   413,
       0,   414,   354,   355,   356,     0,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,     0,     0,   367,   368,
       0,     0,    89,    90,     0,     0,    91,   369,   370,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,    93,     0,     0,   371,   372,   373,   374,   375,   376,
     377,     0,    94,     0,     0,   313,   314,   315,     0,     0,
       0,     0,   378,    95,   379,   380,     0,     0,   197,   202,
       0,     0,   203,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,     0,    97,     0,     0,    98,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
     100,   101,   102,     0,     0,     0,     0,     0,   103,   381,
       0,   104,     0,     0,     0,     0,   382,   383,     0,     0,
       0,   105,   384,     0,   106,     0,     0,   107,   108,   109,
     385,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,   386,   387,   388,   389,     0,   390,   391,   112,   113,
     392,   393,   114,   394,   115,   116,   117,   118,   119,   120,
     121,     0,   122,   395,   123,   124,   125,   126,     0,   127,
     396,   128,     0,     0,     0,     0,     0,   129,   684,     0,
     130,   398,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   399,   400,     0,
       0,     0,     0,     0,     0,     0,     0,   401,   402,   403,
       0,     0,     0,     0,   405,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,   132,     0,     0,     0,     0,
       0,     0,   133,     0,     0,     0,   134,   135,   136,   137,
     138,     0,     0,     0,     0,     0,     0,   139,     0,     0,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,     0,   152,     0,     0,     0,     0,     0,     0,
     153,     0,     0,   154,     0,     0,     0,   155,     0,     0,
     156,   157,     0,   158,     0,     0,   159,     0,   160,     0,
       0,     0,   161,   162,     0,     0,    36,     0,     0,   406,
     407,   408,   409,   167,   168,     0,   169,   170,   171,     0,
     172,     0,     0,     0,     0,   173,   174,     0,     0,     0,
       0,   410,     0,     0,     0,   411,   412,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     175,   176,     0,   177,   178,     0,     0,     0,     0,   179,
     180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     413,     0,   414,   354,   355,   356,     0,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,     0,     0,   367,
     368,     0,     0,    89,    90,     0,     0,    91,   369,   370,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,     0,    93,     0,     0,   371,   372,   373,   374,   375,
     376,   377,     0,    94,     0,     0,   313,   314,   315,     0,
       0,     0,     0,   378,    95,   379,   380,     0,     0,     0,
     202,     0,     0,   203,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    96,     0,     0,    97,     0,     0,
      98,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   100,   101,   102,     0,     0,     0,     0,     0,   103,
     381,     0,   104,     0,     0,  1850,  1851,   382,  1852,     0,
       0,     0,   105,   384,     0,   106,     0,     0,   107,   108,
     109,   385,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,   386,   387,   388,   389,     0,   390,   391,   112,
     113,   392,   393,   114,   394,   115,   116,   117,   118,   119,
     120,   121,     0,   122,   395,   123,   124,   125,   126,     0,
     127,   396,   128,     0,     0,     0,     0,     0,   129,  1853,
       0,   130,   398,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   399,   400,
       0,     0,     0,     0,     0,     0,     0,     0,   401,   402,
     403,     0,     0,     0,     0,   405,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,     0,     0,     0,
       0,     0,     0,   133,     0,     0,     0,   134,   135,   136,
     137,   138,     0,     0,     0,     0,     0,     0,   139,     0,
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,     0,     0,     0,     0,     0,
       0,   153,     0,     0,   154,     0,     0,     0,   155,     0,
       0,   156,   157,     0,   158,     0,     0,   159,     0,   160,
       0,     0,     0,   161,   162,     0,     0,     0,     0,     0,
     406,   407,   408,   409,   167,   168,     0,   169,   170,   171,
       0,   172,     0,     0,     0,     0,   173,   174,     0,     0,
       0,     0,   410,     0,     0,     0,   411,   412,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   175,   176,     0,   177,   178,     0,     0,     0,     0,
     179,   180,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   413,     0,   414,   354,   355,   356,     0,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,     0,     0,
     367,   368,     0,     0,    89,    90,     0,     0,    91,   369,
     370,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,     0,     0,    93,     0,     0,   371,   372,   373,   374,
     375,   376,   377,     0,    94,     0,     0,   313,   314,   315,
       0,     0,     0,     0,   378,    95,   379,   380,     0,     0,
       0,   202,     0,     0,   203,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,   100,   101,   102,     0,     0,     0,     0,     0,
     103,   381,     0,   104,     0,     0,     0,     0,   382,   383,
       0,     0,     0,   105,   384,     0,   106,     0,     0,   107,
     108,   109,   385,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,   386,   387,   388,   389,     0,   390,   391,
     112,   113,   392,   393,   114,   394,   115,   116,   117,   118,
     119,   120,   121,     0,   122,   395,   123,   124,   125,   126,
       0,   127,   396,   128,     0,     0,     0,     0,     0,   129,
     397,     0,   130,   398,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   399,
     400,     0,     0,     0,     0,     0,     0,     0,     0,   401,
     402,   403,     0,     0,     0,     0,   405,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,   134,   135,
     136,   137,   138,     0,     0,     0,     0,     0,     0,   139,
       0,     0,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,   152,     0,     0,     0,     0,
       0,     0,   153,     0,     0,   154,     0,     0,     0,   155,
       0,     0,   156,   157,     0,   158,     0,     0,   159,     0,
     160,     0,     0,     0,   161,   162,     0,     0,     0,     0,
       0,   406,   407,   408,   409,   167,   168,     0,   169,   170,
     171,     0,   172,     0,     0,     0,     0,   173,   174,     0,
       0,     0,     0,   410,     0,     0,     0,   411,   412,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   175,   176,     0,   177,   178,     0,     0,     0,
       0,   179,   180,     0,     0,     0,     0,     0,     0,  1980,
       0,     0,     0,     0,     0,     0,  2084,     0,     0,     0,
       0,     0,   413,     0,   414,   354,   355,   356,     0,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,     0,
       0,   367,   368,     0,     0,    89,    90,     0,     0,    91,
     369,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,    93,     0,     0,   371,   372,   373,
     374,   375,   376,   377,     0,    94,     0,     0,   313,   314,
     315,     0,     0,     0,     0,   378,    95,   379,   380,     0,
       0,     0,   202,     0,     0,   203,   204,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,     0,     0,    97,
       0,     0,    98,     0,     0,     0,     0,     0,    99,     0,
       0,     0,     0,   100,   101,   102,     0,     0,     0,     0,
       0,   103,   381,     0,   104,     0,     0,     0,     0,   382,
     383,     0,     0,     0,   105,   384,     0,   106,     0,     0,
     107,   108,   109,   385,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,   386,   387,   388,   389,     0,   390,
     391,   112,   113,   392,   393,   114,   394,   115,   116,   117,
     118,   119,   120,   121,     0,   122,   395,   123,   124,   125,
     126,     0,   127,   396,   128,     0,     0,     0,     0,     0,
     129,   397,     0,   130,   398,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     399,   400,     0,     0,     0,     0,     0,     0,     0,     0,
     401,   402,   403,   404,     0,     0,     0,   405,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   132,     0,
       0,     0,     0,     0,     0,   133,     0,     0,     0,   134,
     135,   136,   137,   138,     0,     0,     0,     0,     0,     0,
     139,     0,     0,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,     0,   152,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   154,     0,     0,     0,
     155,     0,     0,   156,   157,     0,   158,     0,     0,   159,
       0,   160,     0,     0,     0,   161,   162,     0,     0,     0,
       0,     0,   406,   407,   408,   409,   167,   168,     0,   169,
     170,   171,     0,   172,     0,     0,     0,     0,   173,   174,
       0,     0,     0,     0,   410,     0,     0,     0,   411,   412,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   175,   176,     0,   177,   178,     0,     0,
       0,     0,   179,   180,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   413,     0,   414,   354,   355,   356,     0,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
       0,     0,   367,   368,     0,     0,    89,    90,     0,     0,
      91,   369,   370,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,     0,     0,    93,     0,     0,   371,   372,
     373,   374,   375,   376,   377,     0,    94,     0,     0,   313,
     314,   315,     0,     0,     0,     0,   378,    95,   379,   380,
       0,     0,     0,   202,     0,     0,   203,   204,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    96,     0,     0,
      97,     0,     0,    98,     0,     0,     0,     0,     0,    99,
       0,     0,     0,     0,   100,   101,   102,     0,     0,     0,
       0,     0,   103,   381,     0,   104,     0,     0,     0,     0,
     382,   383,     0,     0,     0,   105,   384,     0,   106,     0,
       0,   107,   108,   109,   385,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,   386,   387,   388,   389,     0,
     390,   391,   112,   113,   392,   393,   114,   394,   115,   116,
     117,   118,   119,   120,   121,     0,   122,   395,   123,   124,
     125,   126,     0,   127,   396,   128,     0,     0,     0,     0,
       0,   129,   397,     0,   130,   398,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   399,   400,     0,     0,     0,     0,     0,     0,     0,
       0,   401,   402,   403,     0,     0,     0,     0,   405,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,   132,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
     134,   135,   136,   137,   138,     0,     0,     0,     0,     0,
       0,   139,     0,     0,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   539,   152,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   154,     0,     0,
       0,   155,     0,     0,   156,   157,     0,   158,     0,     0,
     159,     0,   160,     0,     0,     0,   161,   162,     0,     0,
       0,     0,     0,   406,   407,   408,   409,   167,   168,     0,
     169,   170,   171,     0,   172,     0,     0,     0,     0,   173,
     174,     0,     0,     0,     0,   410,     0,     0,     0,   411,
     412,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   175,   176,     0,   177,   178,     0,
       0,     0,     0,   179,   180,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   413,     0,   414,   354,   355,   356,
       0,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,     0,     0,   367,   368,     0,     0,    89,    90,     0,
       0,    91,   369,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    92,     0,     0,    93,     0,     0,   371,
     372,   373,   374,   375,   376,   377,     0,    94,     0,     0,
     313,   314,   315,     0,     0,     0,     0,   378,    95,   379,
     380,     0,     0,     0,   202,     0,     0,   203,   204,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,    97,     0,     0,    98,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,   100,   101,   102,     0,     0,
       0,     0,     0,   103,   381,     0,   104,     0,     0,     0,
       0,   382,   383,     0,     0,     0,   105,   384,     0,   106,
       0,     0,   107,   108,   109,   385,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,   386,   387,   388,   389,
       0,   390,   391,   112,   113,   392,   393,   114,   394,   115,
     116,   117,   118,   119,   120,   121,     0,   122,   395,   123,
     124,   125,   126,     0,   127,   396,   128,     0,     0,     0,
       0,     0,   129,   397,     0,   130,   398,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   399,   400,     0,     0,     0,     0,     0,     0,
       0,     0,   401,   402,   403,     0,     0,     0,     0,   405,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,     0,     0,     0,     0,     0,     0,   133,     0,     0,
       0,   134,   135,   136,   137,   138,     0,     0,     0,     0,
       0,     0,   139,     0,     0,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     0,   152,     0,
       0,     0,     0,     0,     0,   153,     0,     0,   154,     0,
       0,     0,   155,     0,     0,   156,   157,     0,   158,     0,
       0,   159,     0,   160,     0,     0,     0,   161,   162,     0,
       0,     0,     0,     0,   406,   407,   408,   409,   167,   168,
       0,   169,   170,   171,     0,   172,     0,     0,     0,     0,
     173,   174,     0,     0,     0,     0,   410,   706,     0,     0,
     411,   412,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   175,   176,     0,   177,   178,
       0,     0,     0,     0,   179,   180,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   413,     0,   414,   354,   355,
     356,     0,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,     0,     0,   367,   368,     0,     0,    89,    90,
       0,     0,    91,   369,   370,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    92,     0,     0,    93,     0,     0,
     371,   372,   373,   374,   375,   376,   377,     0,    94,     0,
       0,   313,   314,   315,     0,     0,     0,     0,   378,    95,
     379,   380,     0,     0,     0,   202,     0,     0,   203,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
       0,     0,    97,     0,     0,    98,     0,     0,     0,     0,
       0,    99,     0,     0,     0,     0,   100,   101,   102,     0,
       0,     0,     0,     0,   103,   381,     0,   104,     0,     0,
       0,     0,   382,   383,     0,     0,     0,   105,   384,     0,
     106,     0,     0,   107,   108,   109,   385,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,   386,   387,   388,
     389,     0,   390,   391,   112,   113,   392,   393,   114,   394,
     115,   116,   117,   118,   119,   120,   121,     0,   122,   395,
     123,   124,   125,   126,     0,   127,   396,   128,     0,     0,
       0,     0,     0,   129,   397,   791,   130,   398,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   399,   400,     0,     0,     0,     0,     0,
       0,     0,     0,   401,   402,   403,     0,     0,     0,     0,
     405,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,   132,     0,     0,     0,     0,     0,     0,   133,     0,
       0,     0,   134,   135,   136,   137,   138,     0,     0,     0,
       0,     0,     0,   139,     0,     0,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     0,   152,
       0,     0,     0,     0,     0,     0,   153,     0,     0,   154,
       0,     0,     0,   155,     0,     0,   156,   157,     0,   158,
       0,     0,   159,     0,   160,     0,     0,     0,   161,   162,
       0,     0,     0,     0,     0,   406,   407,   408,   409,   167,
     168,     0,   169,   170,   171,     0,   172,     0,     0,     0,
       0,   173,   174,     0,     0,     0,     0,   410,     0,     0,
       0,   411,   412,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   175,   176,     0,   177,
     178,     0,     0,     0,     0,   179,   180,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   413,     0,   414,   354,
     355,   356,     0,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,     0,     0,   367,   368,     0,     0,    89,
      90,     0,     0,    91,   369,   370,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    92,     0,     0,    93,     0,
       0,   371,   372,   373,   374,   375,   376,   377,     0,    94,
       0,     0,   313,   314,   315,     0,     0,     0,     0,   378,
      95,   379,   380,     0,     0,     0,   202,     0,     0,   203,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,     0,     0,    97,     0,     0,    98,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,   100,   101,   102,
       0,     0,     0,     0,     0,   103,   381,     0,   104,     0,
       0,     0,     0,   382,   383,     0,     0,     0,   105,   384,
       0,   106,     0,     0,   107,   108,   109,   385,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,   386,   387,
     388,   389,     0,   390,   391,   112,   113,   392,   393,   114,
     394,   115,   116,   117,   118,   119,   120,   121,     0,   122,
     395,   123,   124,   125,   126,     0,   127,   396,   128,     0,
       0,     0,     0,     0,   129,   397,     0,   130,   398,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   399,   400,     0,     0,     0,     0,
       0,     0,     0,     0,   401,   402,   403,     0,     0,     0,
       0,   405,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,     0,     0,     0,     0,     0,     0,   133,
       0,     0,     0,   134,   135,   136,   137,   138,     0,     0,
       0,     0,     0,     0,   139,     0,     0,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,     0,
     152,     0,     0,     0,     0,     0,     0,   153,     0,     0,
     154,     0,     0,     0,   155,     0,     0,   156,   157,     0,
     158,     0,     0,   159,     0,   160,     0,     0,     0,   161,
     162,     0,     0,     0,     0,     0,   406,   407,   408,   409,
     167,   168,     0,   169,   170,   171,     0,   172,     0,     0,
       0,     0,   173,   174,     0,     0,     0,     0,   410,  1933,
       0,     0,   411,   412,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   175,   176,     0,
     177,   178,     0,     0,     0,     0,   179,   180,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   413,     0,   414,
     354,   355,   356,     0,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,     0,     0,   367,   368,     0,     0,
      89,    90,     0,     0,    91,   369,   370,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92,     0,     0,    93,
       0,     0,   371,   372,   373,   374,   375,   376,   377,     0,
      94,     0,     0,   313,   314,   315,     0,     0,     0,     0,
     378,    95,   379,   380,     0,     0,     0,   202,     0,     0,
     203,   204,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    96,     0,     0,    97,     0,     0,    98,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,   100,   101,
     102,     0,     0,     0,     0,     0,   103,   381,     0,   104,
       0,     0,     0,     0,   382,   383,     0,     0,     0,   105,
     384,     0,   106,     0,     0,   107,   108,   109,   385,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,   386,
     387,   388,   389,     0,   390,   391,   112,   113,   392,   393,
     114,   394,   115,   116,   117,   118,   119,   120,   121,     0,
     122,   395,   123,   124,   125,   126,     0,   127,   396,   128,
       0,     0,     0,     0,     0,   129,   397,     0,   130,   398,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   399,   400,     0,     0,     0,
       0,     0,     0,     0,     0,   401,   402,   403,     0,     0,
       0,     0,   405,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,     0,     0,   134,   135,   136,   137,   138,     0,
       0,     0,     0,     0,     0,   139,     0,     0,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
       0,   152,     0,     0,     0,     0,     0,     0,   153,     0,
       0,   154,     0,     0,     0,   155,     0,     0,   156,   157,
       0,   158,     0,     0,   159,     0,   160,     0,     0,     0,
     161,   162,     0,     0,     0,     0,     0,   406,   407,   408,
     409,   167,   168,     0,   169,   170,   171,     0,   172,     0,
       0,     0,     0,   173,   174,     0,     0,     0,     0,   410,
       0,     0,     0,   411,   412,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   175,   176,
       0,   177,   178,     0,     0,     0,     0,   179,   180,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2097,     0,     0,     0,     0,     0,     0,   413,     0,
     414,   354,   355,   356,     0,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,     0,     0,   367,   368,     0,
       0,    89,    90,     0,     0,    91,   369,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,     0,
      93,     0,     0,   371,   372,   373,   374,   375,   376,   377,
       0,    94,     0,     0,   313,   314,   315,     0,     0,     0,
       0,   378,    95,   379,   380,     0,     0,     0,   202,     0,
       0,   203,   204,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,    97,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
     101,   102,     0,     0,     0,     0,     0,   103,   381,     0,
     104,     0,     0,     0,     0,   382,   383,     0,     0,     0,
     105,   384,     0,   106,     0,     0,   107,   108,   109,   385,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
     386,   387,   388,   389,     0,   390,   391,   112,   113,   392,
     393,   114,   394,   115,   116,   117,   118,   119,   120,   121,
       0,   122,   395,   123,   124,   125,   126,     0,   127,   396,
     128,     0,     0,     0,     0,     0,   129,   397,     0,   130,
     398,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   399,   400,     0,     0,
       0,     0,     0,     0,     0,     0,   401,   402,   403,     0,
       0,     0,     0,   405,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,   134,   135,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   139,     0,     0,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,   152,     0,     0,     0,     0,     0,     0,   153,
       0,     0,   154,     0,     0,     0,   155,     0,     0,   156,
     157,     0,   158,     0,     0,   159,     0,   160,     0,     0,
       0,   161,   162,     0,     0,     0,     0,     0,   406,   407,
     408,   409,   167,   168,     0,   169,   170,   171,     0,   172,
       0,     0,     0,     0,   173,   174,     0,     0,     0,     0,
     410,     0,     0,     0,   411,   412,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175,
     176,     0,   177,   178,     0,     0,     0,     0,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2249,     0,     0,     0,     0,     0,     0,   413,
       0,   414,   354,   355,   356,     0,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,     0,     0,   367,   368,
       0,     0,    89,    90,     0,     0,    91,   369,   370,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,    93,     0,     0,   371,   372,   373,   374,   375,   376,
     377,     0,    94,     0,     0,   313,   314,   315,     0,     0,
       0,     0,   378,    95,   379,   380,     0,     0,     0,   202,
       0,     0,   203,   204,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,     0,    97,     0,     0,    98,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
     100,   101,   102,     0,     0,     0,     0,     0,   103,   381,
       0,   104,     0,     0,     0,     0,   382,   383,     0,     0,
       0,   105,   384,     0,   106,     0,     0,   107,   108,   109,
     385,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,   386,   387,   388,   389,     0,   390,   391,   112,   113,
     392,   393,   114,   394,   115,   116,   117,   118,   119,   120,
     121,     0,   122,   395,   123,   124,   125,   126,     0,   127,
     396,   128,     0,     0,     0,     0,     0,   129,   397,     0,
     130,   398,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   399,   400,     0,
       0,     0,     0,     0,     0,     0,     0,   401,   402,   403,
       0,     0,     0,     0,   405,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,   132,     0,     0,     0,     0,
       0,     0,   133,     0,     0,     0,   134,   135,   136,   137,
     138,     0,     0,     0,     0,     0,     0,   139,     0,     0,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,     0,   152,     0,     0,     0,     0,     0,     0,
     153,     0,     0,   154,     0,     0,     0,   155,     0,     0,
     156,   157,     0,   158,     0,     0,   159,     0,   160,     0,
       0,     0,   161,   162,     0,     0,     0,     0,     0,   406,
     407,   408,   409,   167,   168,     0,   169,   170,   171,     0,
     172,     0,     0,     0,     0,   173,   174,     0,     0,     0,
       0,   410,     0,     0,     0,   411,   412,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     175,   176,     0,   177,   178,     0,     0,     0,     0,   179,
     180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     413,     0,   414,   354,   355,   356,     0,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,     0,     0,   367,
     368,     0,     0,    89,    90,     0,     0,    91,   369,   370,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,     0,    93,     0,     0,   371,   372,   373,   374,   375,
     376,   377,     0,    94,     0,     0,   313,   314,   315,     0,
       0,     0,     0,   378,    95,   379,   380,     0,     0,     0,
     202,     0,     0,   203,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    96,     0,     0,    97,     0,     0,
      98,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   100,   101,   102,     0,     0,     0,     0,     0,   103,
       0,     0,   104,     0,     0,     0,     0,   382,   383,     0,
       0,     0,   105,   384,     0,   106,     0,     0,   107,   108,
     109,   385,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,   386,   387,   388,   389,  1658,   390,   391,   112,
     113,   392,   393,   114,   394,   115,   116,   117,   118,   119,
     120,   121,   992,   122,   395,   123,   124,   125,   126,     0,
     127,   396,   128,     0,     0,     0,     0,     0,   129,   691,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   399,   400,
       0,     0,     0,     0,     0,     0,     0,     0,   401,   402,
     403,     0,     0,     0,     0,   405,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,     0,     0,     0,
       0,     0,     0,   133,     0,     0,     0,   134,   135,   136,
     137,   138,     0,     0,     0,     0,     0,     0,   139,     0,
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,     0,     0,     0,     0,     0,
       0,   153,     0,     0,   154,     0,     0,     0,   155,     0,
       0,   156,   157,     0,   158,     0,     0,   159,     0,   160,
       0,     0,     0,   161,   162,     0,     0,     0,     0,     0,
     406,   407,   408,   409,   167,   168,     0,   169,   170,   171,
       0,   172,     0,     0,     0,     0,   173,   174,     0,     0,
       0,     0,   410,     0,     0,     0,   411,   412,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   175,   176,     0,   177,   178,     0,     0,     0,     0,
     179,   180,     0,     0,   354,   355,   356,     0,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,     0,     0,
     367,   368,     0,   414,    89,    90,     0,     0,    91,   369,
     370,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,     0,     0,    93,     0,     0,   371,   372,   373,   374,
     375,   376,   377,     0,    94,     0,     0,   313,   314,   315,
       0,     0,     0,     0,   378,    95,   379,   380,     0,     0,
       0,   202,     0,     0,   203,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,  1494,     0,
       0,    98,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,   100,   101,   102,     0,     0,     0,     0,     0,
     103,     0,     0,   104,     0,     0,     0,     0,   382,   383,
       0,     0,     0,   105,   384,     0,   106,     0,     0,   107,
     108,   109,   385,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,   386,   387,   388,   389,     0,   390,   391,
     112,   113,   392,   393,   114,   394,   115,   116,   117,   118,
     119,   120,   121,     0,   122,   395,   123,   124,   125,   126,
       0,   127,   396,   128,     0,     0,     0,     0,     0,   129,
     691,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   399,
     400,     0,     0,     0,     0,     0,     0,     0,     0,   401,
     402,   403,     0,     0,     0,     0,   405,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,   134,   135,
     136,   137,   138,     0,     0,     0,     0,     0,     0,   139,
       0,     0,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,  1495,   152,     0,     0,     0,     0,
       0,     0,   153,     0,     0,   154,     0,     0,     0,   155,
       0,     0,   156,   157,     0,   158,     0,     0,   159,     0,
     160,     0,     0,     0,   161,   162,     0,     0,     0,     0,
       0,   406,   407,   408,   409,   167,   168,     0,   169,   170,
     171,     0,   172,     0,     0,     0,     0,   173,   174,     0,
       0,     0,     0,   410,     0,     0,     0,   411,   412,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   175,   176,     0,   177,   178,     0,     0,     0,
       0,   179,   180,     0,     0,   354,   355,   356,     0,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,     0,
       0,   367,   368,     0,   414,    89,    90,     0,     0,    91,
     369,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,    93,     0,     0,   371,   372,   373,
     374,   375,   376,   377,     0,    94,     0,     0,   313,   314,
     315,     0,     0,     0,     0,   378,    95,   379,   380,     0,
       0,     0,   202,     0,     0,   203,   204,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,     0,     0,    97,
       0,     0,    98,     0,     0,     0,     0,     0,    99,     0,
       0,     0,     0,   100,   101,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,     0,     0,     0,     0,   382,
     383,     0,     0,     0,   105,   384,     0,   106,     0,     0,
     107,   108,   109,   385,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,   386,   387,   388,   389,  1658,   390,
     391,   112,   113,   392,   393,   114,   394,   115,   116,   117,
     118,   119,   120,   121,     0,   122,   395,   123,   124,   125,
     126,     0,   127,   396,   128,     0,     0,     0,     0,     0,
     129,   691,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     399,   400,     0,     0,     0,     0,     0,     0,     0,     0,
     401,   402,   403,     0,     0,     0,     0,   405,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   132,     0,
       0,     0,     0,     0,     0,   133,     0,     0,     0,   134,
     135,   136,   137,   138,     0,     0,     0,     0,     0,     0,
     139,     0,     0,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,     0,   152,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   154,     0,     0,     0,
     155,     0,     0,   156,   157,     0,   158,     0,     0,   159,
       0,   160,     0,     0,     0,   161,   162,     0,     0,     0,
       0,     0,   406,   407,   408,   409,   167,   168,     0,   169,
     170,   171,     0,   172,     0,     0,     0,     0,   173,   174,
       0,     0,     0,     0,   410,     0,     0,     0,   411,   412,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   175,   176,     0,   177,   178,     0,     0,
       0,     0,   179,   180,     0,     0,   354,   355,   356,     0,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
       0,     0,   367,   368,     0,   414,    89,    90,     0,     0,
      91,   369,   370,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,     0,     0,    93,     0,     0,   371,   372,
     373,   374,   375,   376,   377,     0,    94,     0,     0,   313,
     314,   315,     0,     0,     0,     0,   378,    95,   379,   380,
       0,     0,     0,   202,     0,     0,   203,   204,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    96,     0,     0,
      97,     0,     0,    98,     0,     0,     0,     0,     0,    99,
       0,     0,     0,     0,   100,   101,   102,     0,     0,     0,
       0,     0,   103,     0,     0,   104,     0,     0,     0,     0,
     382,   383,     0,     0,     0,   105,   384,     0,   106,     0,
       0,   107,   108,   109,   385,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,   386,   387,   388,   389,     0,
     390,   391,   112,   113,   392,   393,   114,   394,   115,   116,
     117,   118,   119,   120,   121,     0,   122,   395,   123,   124,
     125,   126,     0,   127,   396,   128,     0,     0,     0,     0,
       0,   129,   691,     0,   130,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   399,   400,     0,     0,     0,     0,     0,     0,     0,
       0,   401,   402,   403,     0,     0,     0,     0,   405,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,   132,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
     134,   135,   136,   137,   138,     0,     0,     0,     0,     0,
       0,   139,     0,     0,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,     0,   152,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   154,     0,     0,
       0,   155,     0,     0,   156,   157,     0,   158,     0,     0,
     159,     0,   160,     0,     0,     0,   161,   162,     0,     0,
       0,     0,     0,   406,   407,   408,   409,   167,   168,     0,
     169,   170,   171,     0,   172,     0,     0,     0,     0,   173,
     174,     0,     0,     0,     0,   410,     0,     0,     0,   411,
     412,     0,     0,     0,     0,    84,    85,    86,    87,    88,
       0,     0,     0,     0,   175,   176,     0,   177,   178,     0,
       0,    89,    90,   179,   180,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,     0,     0,
      93,     0,     0,     0,     0,     0,   414,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,    97,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
     101,   102,     0,     0,     0,     0,     0,   103,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,   106,     0,     0,   107,   108,   109,     0,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
       0,   122,     0,   123,   124,   125,   126,     0,   127,     0,
     813,     0,     0,     0,     0,     0,   129,     0,     0,   130,
       0,     0,     0,     0,     0,     3,     4,     5,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     9,    10,     0,     0,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,   134,   135,   136,   137,   138,
     294,   295,   296,   297,     0,     0,   139,     0,     0,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,   152,     0,     0,     0,     0,     0,     0,   153,
       0,     0,   154,     0,     0,     0,   155,     0,     0,   156,
     157,     0,   158,     0,     0,   159,     0,   160,     0,     0,
       0,   814,   162,     0,     0,    13,     0,    14,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,     0,   172,
       0,     0,     0,     0,   173,   174,     0,     0,    84,    85,
      86,    87,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,     0,     0,    91,   175,
     176,     0,   177,   178,     0,     0,    15,     0,   179,   180,
      92,     0,     0,    93,    16,    17,     0,     0,     0,     0,
       0,     0,     0,     0,    94,   300,     0,    18,    19,     0,
      20,     0,     0,     0,     0,    95,     0,     0,     3,     4,
    1777,     6,     0,    30,    31,     0,     0,     0,     0,     0,
      32,    33,     7,     8,     9,  1778,     0,     0,    97,     0,
       0,  1779,     0,     0,     0,     0,    34,    99,     0,    35,
       0,     0,   100,   101,   102,    36,     0,     0,     0,     0,
     103,     0,     0,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,   106,     0,     0,   107,
     108,   109,     0,   110,   111,     0,     0,     0,     0,     0,
       0,    37,     0,    38,     0,     0,     0,     0,     0,     0,
     112,   113,     0,     0,   114,     0,   115,   116,   117,   118,
     119,   120,   121,     0,   122,     0,   123,   124,   125,   126,
       0,   127,     0,   128,   606,   607,   608,   609,     0,   129,
       0,     0,   130,     0,     0,     0,     0,     0,   610,     0,
       0,     0,   611,   612,   613,   369,   370,   614,   615,   616,
     617,   618,   619,   620,   621,   622,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     623,   624,   625,     0,     0,     0,   131,   132,     0,    15,
       0,     0,     0,     0,   133,     0,     0,    16,   134,   135,
     136,   137,   138,     0,     0,     0,     0,     0,     0,   139,
      18,  1781,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,   152,    30,    31,     0,     0,
       0,     0,   153,    32,    33,   154,     0,     0,     0,   155,
       0,     0,   156,   157,     0,   158,     0,     0,   159,    34,
     160,  1783,    35,     0,   161,   162,     0,     0,     0,     0,
       0,   163,   164,   165,   166,   167,   168,     0,   169,   170,
     171,     0,   172,     0,     0,     0,     0,   173,   174,     0,
       0,     0,     0,  1784,     0,     0,  2226,     0,     0,  1785,
    2227,  -399,     0,     0,    37,     0,    38,    84,    85,    86,
      87,    88,   175,   176,     0,   177,   178,     0,     0,     0,
       0,   179,   180,    89,    90,     0,     0,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     3,     4,  1777,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,     9,  1778,     0,     0,    97,     0,     0,
    1779,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   100,   101,   102,     0,     0,     0,     0,     0,   103,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105,     0,     0,   106,   733,     0,   107,   108,
     109,     0,   110,   111,     0,     0,     0,   626,   627,   628,
     629,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     0,   122,     0,   123,   124,   125,   126,     0,
     127,     0,   128,     0,     0,     0,     0,     0,   129,     0,
       0,   130,     0,   734,   735,   736,   737,   738,   739,   740,
     741,   742,   743,     0,     0,     0,   744,   745,   746,     0,
     747,   748,   749,   750,   751,   752,   753,   754,   755,   756,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,     0,    15,     0,
       0,     0,     0,   133,     0,     0,    16,   134,   135,   136,
     137,   138,     0,     0,     0,     0,     0,  1780,   139,    18,
    1781,  1782,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,    30,    31,     0,     0,     0,
       0,   153,    32,    33,   154,     0,     0,     0,   155,     0,
       0,   156,   157,     0,   158,     0,     0,   159,    34,   160,
    1783,    35,     0,   161,   162,     0,     0,     0,     0,     0,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
       0,   172,     0,     0,     0,     0,   173,   174,     0,     0,
       0,     0,  1784,    84,    85,    86,    87,    88,  1785,     0,
       0,     0,     0,  1786,     0,    38,     0,     0,     0,    89,
      90,   175,   176,    91,   177,   178,     0,     0,     0,     0,
     179,   180,     0,  1292,     0,    92,     0,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     3,     4,  1777,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     7,     8,     9,
    1778,     0,     0,    97,     0,     0,  1779,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,   100,   101,   102,
       0,     0,     0,     0,     0,   103,     0,     0,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,   106,   733,     0,   107,   108,   109,     0,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,   115,   116,   117,   118,   119,   120,   121,     0,   122,
       0,   123,   124,   125,   126,     0,   127,     0,   128,     0,
       0,     0,     0,     0,   129,     0,     0,   130,     0,   734,
     735,   736,   737,   738,   739,   740,   741,   742,   743,     0,
       0,     0,   744,   745,   746,     0,   747,   748,   749,   750,
     751,   752,   753,   754,   755,   756,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,     0,    15,     0,     0,     0,     0,   133,
       0,     0,    16,   134,   135,   136,   137,   138,     0,     0,
       0,     0,     0,     0,   139,    18,  1781,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,     0,
     152,    30,    31,     0,     0,     0,     0,   153,    32,    33,
     154,     0,     0,     0,   155,     0,     0,   156,   157,     0,
     158,     0,     0,   159,    34,   160,  1783,    35,     0,   161,
     162,     0,     0,     0,     0,     0,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,     0,   172,     0,     0,
       0,     0,   173,   174,     0,     0,     0,     0,  1784,    84,
      85,    86,    87,    88,  1785,     0,  -399,     0,     0,    37,
       0,    38,     0,     0,     0,    89,    90,   175,   176,    91,
     177,   178,     0,     0,     0,     0,   179,   180,     0,  1704,
       0,    92,     0,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    95,     0,     0,     3,
       4,  1777,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,  1778,     0,     0,    97,
       0,     0,  1779,     0,     0,     0,     0,     0,    99,     0,
       0,     0,     0,   100,   101,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,     0,  1699,     0,     0,     0,
       0,     0,     0,     0,   105,     0,     0,   106,     0,     0,
     107,   108,   109,     0,   110,   111,   733,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,   115,   116,   117,
     118,   119,   120,   121,     0,   122,     0,   123,   124,   125,
     126,     0,   127,     0,   128,  1700,     0,     0,     0,     0,
     129,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   734,   735,   736,   737,   738,   739,   740,
     741,   742,   743,     0,     0,     0,   744,   745,   746,     0,
     747,   748,   749,   750,   751,   752,   753,   754,   755,   756,
       0,     0,     0,     0,     0,     0,     0,   131,   132,     0,
      15,     0,     0,     0,     0,   133,     0,     0,    16,   134,
     135,   136,   137,   138,     0,     0,     0,     0,     0,     0,
     139,    18,  1781,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,     0,   152,    30,    31,     0,
       0,     0,     0,   153,    32,    33,   154,     0,     0,     0,
     155,     0,     0,   156,   157,     0,   158,     0,     0,   159,
      34,   160,  1783,    35,     0,   161,   162,     0,     0,     0,
       0,     0,   163,   164,   165,   166,   167,   168,     0,   169,
     170,   171,     0,   172,     0,     0,     0,     0,   173,   174,
       0,     0,     0,     0,  1784,    84,    85,    86,    87,    88,
    1785,     0,     0,     0,     0,    37,  2281,    38,     0,     0,
       0,    89,    90,   175,   176,    91,   177,   178,     0,     0,
       0,     0,   179,   180,     0,     0,     0,    92,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,     0,     0,     3,     4,  1777,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     9,  1778,     0,     0,    97,     0,     0,  1779,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
     101,   102,     0,     0,     0,     0,     0,   103,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,   106,   733,     0,   107,   108,   109,     0,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
       0,   122,     0,   123,   124,   125,   126,     0,   127,     0,
     128,     0,  1291,     0,     0,     0,   129,     0,     0,   130,
       0,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     743,     0,     0,     0,   744,   745,   746,     0,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   756,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     0,    15,     0,     0,     0,
       0,   133,     0,     0,    16,   134,   135,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   139,    18,  1781,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,   152,    30,    31,     0,     0,     0,     0,   153,
      32,    33,   154,     0,     0,     0,   155,     0,     0,   156,
     157,     0,   158,     0,     0,   159,    34,   160,  1783,    35,
       0,   161,   162,     0,     0,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,     0,   172,
       0,     0,     0,     0,   173,   174,     0,     0,     0,     0,
    1784,    84,    85,    86,    87,    88,  1785,     0,     0,     0,
       0,    37,     0,    38,     0,     0,     0,    89,    90,   175,
     176,    91,   177,   178,     0,     0,     0,     0,   179,   180,
       0,     0,     0,    92,     0,     0,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     3,     4,  1777,     6,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     8,     9,  1778,     0,
       0,    97,     0,     0,  1779,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,   100,   101,   102,     0,     0,
       0,     0,     0,   103,     0,     0,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,     0,     0,   106,
       0,     0,   107,   108,   109,     0,   110,   111,   733,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,     0,     0,   114,     0,   115,
     116,   117,   118,   119,   120,   121,     0,   122,     0,   123,
     124,   125,   126,     0,   127,     0,   128,  1657,     0,     0,
       0,     0,   129,     0,     0,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   743,     0,     0,     0,   744,   745,
     746,     0,   747,   748,   749,   750,   751,   752,   753,   754,
     755,   756,     0,     0,     0,     0,     0,     0,     0,   131,
     132,     0,    15,     0,     0,     0,     0,   133,     0,     0,
       0,   134,   135,   136,   137,   138,     0,     0,     0,     0,
       0,     0,   139,    18,  1781,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     0,   152,     0,
      31,     0,     0,     0,     0,   153,    32,    33,   154,     0,
       0,     0,   155,     0,     0,   156,   157,     0,   158,     0,
       0,   159,    34,   160,  1783,     0,     0,   161,   162,     0,
       0,     0,     0,     0,   163,   164,   165,   166,   167,   168,
       0,   169,   170,   171,     0,   172,     0,     0,     0,     0,
     173,   174,     0,     0,     0,     0,  1784,    84,    85,    86,
      87,    88,  1785,     0,     0,     0,     0,    37,  2306,    38,
       0,     0,     0,    89,    90,   175,   176,    91,   177,   178,
       0,     0,     0,     0,   179,   180,     0,     0,     0,    92,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     3,     4,  1777,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     7,     8,     9,  1778,     0,     0,    97,     0,     0,
    1779,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   100,   101,   102,     0,     0,     0,     0,     0,   103,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105,     0,     0,   106,     0,     0,   107,   108,
     109,     0,   110,   111,   733,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     0,   122,     0,   123,   124,   125,   126,     0,
     127,     0,   128,  1703,     0,     0,     0,     0,   129,     0,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     743,     0,     0,     0,   744,   745,   746,     0,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   756,     0,     0,
       0,     0,     0,     0,     0,   131,   132,     0,    15,     0,
       0,     0,     0,   133,     0,     0,     0,   134,   135,   136,
     137,   138,     0,     0,     0,     0,     0,     0,   139,    18,
    1781,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,     0,    31,     0,     0,     0,
       0,   153,    32,    33,   154,     0,     0,     0,   155,     0,
       0,   156,   157,     0,   158,     0,     0,   159,    34,   160,
    1783,     0,     0,   161,   162,     0,     0,     0,     0,     0,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
       0,   172,     0,     0,     0,     0,   173,   174,     0,     0,
       0,     0,  1784,    84,    85,    86,    87,    88,  1785,     0,
       0,     0,     0,  2126,     0,    38,     0,     0,     0,    89,
      90,   175,   176,    91,   177,   178,     0,     0,     0,     0,
     179,   180,     0,     0,     0,    92,     0,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,     0,   197,   202,     0,  1033,   203,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,     0,     0,    97,     0,     0,    98,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,   100,   101,   102,
       0,     0,     0,     0,     0,   103,     0,     0,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,   106,     0,     0,   107,   108,   109,     0,   110,   111,
     733,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,   115,   116,   117,   118,   119,   120,   121,     0,   122,
       0,   123,   124,   125,   126,     0,   127,     0,   128,  1966,
       0,     0,     0,    13,   129,  1312,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   734,   735,   736,
     737,   738,   739,   740,   741,   742,   743,     0,     0,     0,
     744,   745,   746,     0,   747,   748,   749,   750,   751,   752,
     753,   754,   755,   756,     0,     0,     0,     0,     0,     0,
       0,   131,   132,     0,     0,     0,     0,     0,     0,   133,
       0,     0,     0,   134,   135,   136,   137,   138,     0,     0,
       0,     0,     0,     0,   139,     0,     0,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,     0,
     152,     0,     0,     0,     0,     0,     0,   153,     0,     0,
     154,     0,     0,     0,   155,     0,     0,   156,   157,     0,
     158,     0,     0,   159,     0,   160,     0,     0,     0,   161,
     162,     0,     0,    36,     0,     0,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,     0,   172,     0,     0,
       0,     0,   173,   174,     0,     0,    84,    85,    86,    87,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,    91,   175,   176,     0,
     177,   178,     0,     0,     0,     0,   179,   180,    92,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,     0,     0,   313,   314,   315,     0,     0,
       0,     0,   316,   317,   318,   319,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,     0,    97,     0,     0,    98,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
     100,   101,   102,     0,     0,     0,     0,     0,   103,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,     0,     0,   106,     0,     0,   107,   108,   109,
       0,   110,   111,   733,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
       0,     0,   114,     0,   115,   116,   117,   118,   119,   120,
     121,     0,   122,     0,   123,   124,   125,   126,     0,   127,
       0,   128,  1967,     0,     0,     0,     0,   129,   320,     0,
     130,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     734,   735,   736,   737,   738,   739,   740,   741,   742,   743,
       0,     0,     0,   744,   745,   746,     0,   747,   748,   749,
     750,   751,   752,   753,   754,   755,   756,     0,     0,     0,
       0,     0,     0,     0,   131,   132,     0,     0,     0,     0,
       0,     0,   133,     0,     0,     0,   134,   135,   136,   137,
     138,     0,     0,     0,     0,     0,     0,   139,     0,     0,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,     0,   152,     0,     0,     0,     0,     0,     0,
     153,     0,     0,   321,     0,     0,     0,   155,     0,     0,
     156,   157,     0,   158,     0,     0,   322,     0,   160,     0,
       0,     0,   161,   162,     0,     0,     0,     0,     0,   163,
     323,   165,   166,   167,   168,     0,   169,   170,   171,     0,
     172,     0,     0,     0,     0,   173,   174,     0,     0,    84,
      85,    86,    87,    88,     0,     0,     0,     0,     0,     0,
     272,     0,     0,     0,     0,    89,    90,     0,     0,    91,
     175,   176,     0,   177,   178,     0,     0,     0,     0,   179,
     180,    92,     0,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,   274,     0,     0,     0,     0,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,     0,     0,    97,
       0,     0,    98,     0,     0,     0,     0,     0,    99,     0,
       0,     0,     0,   100,   101,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,     0,     0,   106,     0,     0,
     107,   108,   109,     0,   110,   111,   733,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,   115,   116,   117,
     118,   119,   120,   121,     0,   122,     0,   123,   124,   125,
     126,     0,   127,     0,   128,  1968,     0,     0,     0,     0,
     129,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   734,   735,   736,   737,   738,   739,   740,
     741,   742,   743,     0,     0,     0,   744,   745,   746,     0,
     747,   748,   749,   750,   751,   752,   753,   754,   755,   756,
       0,     0,     0,     0,     0,     0,     0,   331,   332,   280,
     281,   282,   283,     0,     0,   133,     0,     0,     0,   134,
     135,   136,   137,   138,     0,     0,     0,     0,     0,     0,
     139,     0,     0,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,     0,   152,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   154,     0,     0,     0,
     155,     0,     0,   156,   157,     0,   158,     0,     0,   159,
       0,   160,     0,     0,     0,   333,   162,     0,     0,     0,
       0,     0,   163,   164,   165,   166,   167,   168,     0,   169,
     170,   171,     0,   172,     0,     0,     0,     0,   173,   174,
       0,     0,    84,    85,    86,    87,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    90,
       0,     0,    91,   175,   176,     0,   177,   178,     0,     0,
       0,     0,   179,   180,    92,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,   202,     0,  1033,   203,   204,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
       0,     0,    97,     0,     0,    98,     0,     0,     0,     0,
       0,    99,     0,     0,     0,     0,   100,   101,   102,     0,
       0,     0,     0,     0,   103,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,     0,     0,
     106,   733,     0,   107,   108,   109,     0,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,     0,     0,   114,     0,
     115,   116,   117,   118,   119,   120,   121,     0,   122,     0,
     123,   124,   125,   126,     0,   127,     0,   128,     0,     0,
       0,     0,     0,   129,  1034,     0,   130,     0,   734,   735,
     736,   737,   738,   739,   740,   741,   742,   743,     0,     0,
       0,   744,   745,   746,     0,   747,   748,   749,   750,   751,
     752,   753,   754,   755,   756,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,   132,     0,     0,     0,     0,     0,     0,   133,     0,
       0,     0,   134,   135,   136,   137,   138,     0,     0,     0,
       0,     0,     0,   139,     0,     0,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     0,   152,
       0,     0,     0,     0,     0,     0,   153,     0,     0,   154,
       0,     0,     0,   155,     0,     0,   156,   157,     0,   158,
       0,     0,   159,     0,   160,     0,     0,     0,   161,   162,
       0,     0,     0,     0,     0,   163,   164,   165,   166,   167,
     168,     0,   169,   170,   171,     0,   172,     0,     0,     0,
       0,   173,   174,     0,     0,    84,    85,    86,    87,  1104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,    90,     0,     0,    91,   175,   176,     0,   177,
     178,     0,     0,     0,     0,   179,   180,    92,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,     0,     0,     0,     0,     0,   202,     0,
       0,   203,   204,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,    97,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
     101,   102,     0,     0,     0,     0,     0,   103,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,   106,     0,     0,   107,   108,   109,     0,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
       0,   122,     0,   123,   124,   125,   126,     0,   127,     0,
     128,     0,     0,     0,     0,     0,   129,     0,     0,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1105,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,   134,   135,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   139,     0,     0,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,   152,     0,     0,     0,     0,     0,     0,   153,
       0,     0,   154,     0,     0,     0,   155,     0,     0,   156,
     157,     0,   158,     0,     0,   159,     0,   160,     0,     0,
       0,   161,   162,     0,     0,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,     0,   172,
       0,     0,     0,     0,   173,   174,     0,     0,    84,    85,
      86,    87,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,     0,     0,    91,   175,
     176,     0,   177,   178,     0,     0,     0,     0,   179,   180,
      92,     0,     0,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,     0,     0,     0,     0,
       0,   202,     0,     0,   203,   204,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,   100,   101,   102,     0,     0,     0,     0,     0,
     103,     0,     0,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,   106,     0,     0,   107,
     108,   109,     0,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,   113,     0,     0,   114,     0,   115,   116,   117,   118,
     119,   120,   121,     0,   122,     0,   123,   124,   125,   126,
       0,   127,     0,   128,     0,     0,     0,     0,     0,   129,
     668,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,   134,   135,
     136,   137,   138,     0,     0,     0,     0,     0,     0,   139,
       0,     0,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,   152,     0,     0,     0,     0,
       0,     0,   153,     0,     0,   154,     0,     0,     0,   155,
       0,     0,   156,   157,     0,   158,     0,     0,   159,     0,
     160,     0,     0,     0,   161,   162,     0,     0,     0,     0,
       0,   163,   164,   165,   166,   167,   168,     0,   169,   170,
     171,     0,   172,     0,     0,     0,     0,   173,   174,     0,
       0,    84,    85,    86,    87,  1104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,     0,
       0,    91,   175,   176,     0,   177,   178,     0,     0,     0,
       0,   179,   180,    92,     0,     0,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     0,     0,     0,   202,     0,     0,   203,   204,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,    97,     0,     0,    98,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,   100,   101,   102,     0,     0,
       0,     0,     0,   103,     0,     0,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,     0,     0,   106,
       0,     0,   107,   108,   109,     0,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,     0,     0,   114,     0,   115,
     116,   117,   118,   119,   120,   121,     0,   122,     0,   123,
     124,   125,   126,     0,   127,     0,   128,     0,     0,     0,
       0,     0,   129,     0,     0,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1559,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,     0,     0,     0,     0,     0,     0,   133,     0,     0,
       0,   134,   135,   136,   137,   138,     0,     0,     0,     0,
       0,     0,   139,     0,     0,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     0,   152,     0,
       0,     0,     0,     0,     0,   153,     0,     0,   154,     0,
       0,     0,   155,     0,     0,   156,   157,     0,   158,     0,
       0,   159,     0,   160,     0,     0,     0,   161,   162,     0,
       0,     0,     0,     0,   163,   164,   165,   166,   167,   168,
       0,   169,   170,   171,     0,   172,     0,     0,     0,     0,
     173,   174,     0,     0,    84,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    90,     0,     0,    91,   175,   176,     0,   177,   178,
       0,     0,     0,     0,   179,   180,    92,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    96,     0,     0,    97,     0,     0,    98,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,   100,   101,
     102,     0,     0,     0,     0,     0,   103,     0,     0,   104,
       0,     0,  2172,  2173,     0,  2174,     0,     0,     0,   105,
       0,     0,   106,     0,     0,   107,   108,   109,     0,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,     0,     0,
     114,     0,   115,   116,   117,   118,   119,   120,   121,     0,
     122,     0,   123,   124,   125,   126,     0,   127,     0,   128,
       0,     0,     0,     0,     0,   129,  2175,     0,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,     0,     0,   134,   135,   136,   137,   138,     0,
       0,     0,     0,     0,     0,   139,     0,     0,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
       0,   152,     0,     0,     0,     0,     0,     0,   153,     0,
       0,   154,     0,     0,     0,   155,     0,     0,   156,   157,
       0,   158,     0,     0,   159,     0,   160,     0,     0,     0,
     161,   162,     0,     0,     0,     0,     0,   163,   164,   165,
     166,   167,   168,     0,   169,   170,   171,     0,   172,     0,
       0,     0,     0,   173,   174,     0,     0,    84,    85,    86,
      87,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,    90,     0,     0,    91,   175,   176,
       0,   177,   178,     0,     0,     0,     0,   179,   180,    92,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
     202,     0,     0,   203,   204,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    96,     0,     0,    97,     0,     0,
      98,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   100,   101,   102,     0,     0,     0,     0,     0,   103,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105,     0,     0,   106,     0,     0,   107,   108,
     109,     0,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     0,   122,     0,   123,   124,   125,   126,     0,
     127,     0,   128,     0,     0,     0,     0,     0,   129,     0,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,     0,     0,     0,
       0,     0,     0,   133,     0,     0,     0,   134,   135,   136,
     137,   138,     0,     0,     0,     0,     0,     0,   139,     0,
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,     0,     0,     0,     0,     0,
       0,   153,     0,     0,   154,     0,     0,     0,   155,     0,
       0,   156,   157,     0,   158,     0,     0,   159,     0,   160,
       0,     0,     0,   161,   162,     0,     0,     0,     0,     0,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
       0,   172,     0,     0,     0,     0,   173,   174,     0,     0,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,     0,     0,
      91,   175,   176,     0,   177,   178,     0,     0,     0,     0,
     179,   180,    92,     0,     0,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,   197,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    96,     0,     0,
      97,     0,     0,    98,     0,     0,     0,     0,     0,    99,
       0,     0,     0,     0,   100,   101,   102,     0,     0,     0,
       0,     0,   103,     0,     0,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,   106,     0,
       0,   107,   108,   109,     0,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   113,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,     0,   122,     0,   123,   124,
     125,   126,     0,   127,     0,   128,     0,     0,     0,     0,
       0,   129,    14,     0,   130,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,   132,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
     134,   135,   136,   137,   138,     0,     0,     0,     0,     0,
       0,   139,     0,     0,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,     0,   152,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   154,     0,     0,
       0,   155,     0,     0,   156,   157,     0,   158,     0,     0,
     159,     0,   160,     0,     0,     0,   161,   162,     0,     0,
      36,     0,     0,   163,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,   172,     0,     0,     0,     0,   173,
     174,     0,     0,    84,    85,    86,    87,  1104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,     0,     0,    91,   175,   176,     0,   177,   178,     0,
       0,     0,     0,   179,   180,    92,     0,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,     0,     0,   202,     0,     0,   203,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,     0,     0,    97,     0,     0,    98,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,   100,   101,   102,
       0,     0,     0,     0,     0,   103,     0,     0,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,   106,     0,     0,   107,   108,   109,     0,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,   115,   116,   117,   118,   119,   120,   121,     0,   122,
       0,   123,   124,   125,   126,     0,   127,     0,   128,     0,
       0,     0,     0,     0,   129,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,     0,     0,     0,     0,     0,     0,   133,
       0,     0,     0,   134,   135,   136,   137,   138,     0,     0,
       0,     0,     0,     0,   139,     0,     0,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,     0,
     152,     0,     0,     0,     0,     0,     0,   153,     0,     0,
     154,     0,     0,     0,   155,     0,     0,   156,   157,     0,
     158,     0,     0,   159,     0,   160,     0,     0,     0,   161,
     162,     0,     0,     0,     0,     0,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,     0,   172,     0,     0,
       0,     0,   173,   174,     0,     0,    84,    85,    86,    87,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,    91,   175,   176,     0,
     177,   178,     0,     0,     0,     0,   179,   180,    92,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,     0,    97,     0,     0,    98,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
     100,   101,   102,     0,     0,     0,     0,     0,   103,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,     0,     0,   106,     0,     0,   107,   108,   109,
       0,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
       0,     0,   114,     0,   115,   116,   117,   118,   119,   120,
     121,     0,   122,     0,   123,   124,   125,   126,     0,   127,
       0,   128,     0,     0,     0,     0,     0,   129,     0,     0,
     130,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1430,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,   132,     0,     0,     0,     0,
       0,     0,   133,     0,  1431,     0,   134,   135,   136,   137,
     138,     0,     0,     0,     0,     0,     0,   139,     0,     0,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,     0,   152,     0,     0,     0,     0,     0,     0,
     153,     0,     0,   154,     0,     0,     0,   155,     0,     0,
     156,   157,     0,   158,     0,     0,   159,     0,   160,     0,
       0,     0,   161,   162,     0,     0,     0,     0,     0,   163,
     164,   165,   166,   167,   168,     0,   169,   170,   171,     0,
     172,     0,     0,     0,     0,   173,   174,     0,     0,    84,
      85,    86,    87,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    90,     0,     0,    91,
     175,   176,     0,   177,   178,     0,     0,     0,     0,   179,
     180,    92,     0,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,     0,     0,    97,
       0,     0,    98,     0,     0,     0,     0,     0,    99,     0,
       0,     0,     0,   100,   101,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,     0,     0,   106,     0,     0,
     107,   108,   109,     0,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,   115,   116,   117,
     118,   119,   120,   121,     0,   122,     0,   123,   124,   125,
     126,     0,   127,     0,   128,     0,     0,     0,     0,     0,
     129,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   132,     0,
       0,     0,     0,     0,     0,   133,     0,     0,     0,   134,
     135,   136,   137,   138,     0,     0,     0,     0,     0,     0,
     139,     0,     0,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,     0,   152,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   154,     0,     0,     0,
     155,     0,     0,   156,   157,     0,   158,     0,     0,   159,
     533,   160,     0,     0,     0,   161,   162,     0,     0,     0,
       0,     0,   163,   164,   165,   166,   167,   168,     0,   169,
     170,   171,     0,   172,     0,     0,     0,     0,   173,   174,
       0,     0,    84,    85,    86,    87,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    90,
       0,     0,    91,   175,   176,     0,   177,   178,     0,     0,
       0,     0,   179,   180,    92,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
       0,     0,    97,     0,     0,    98,     0,     0,     0,     0,
       0,    99,     0,     0,     0,     0,   100,   101,   102,     0,
       0,     0,     0,     0,   103,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,     0,     0,
     106,     0,     0,   107,   108,   109,     0,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,     0,     0,   114,     0,
     115,   116,   117,   118,   119,   120,   121,     0,   122,     0,
     123,   124,   125,   126,     0,   127,     0,   128,     0,     0,
       0,     0,     0,   129,     0,     0,   130,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   718,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,   132,     0,     0,     0,     0,     0,     0,   133,     0,
       0,     0,   134,   135,   136,   137,   138,     0,     0,     0,
       0,     0,     0,   139,     0,     0,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     0,   152,
       0,     0,     0,     0,     0,     0,   153,     0,     0,   154,
       0,     0,     0,   155,     0,     0,   156,   157,     0,   158,
       0,     0,   159,     0,   160,     0,     0,     0,   161,   162,
       0,     0,     0,     0,     0,   163,   164,   165,   166,   167,
     168,     0,   169,   170,   171,     0,   172,     0,     0,     0,
       0,   173,   174,     0,     0,    84,    85,    86,    87,    88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,    90,     0,     0,    91,   175,   176,     0,   177,
     350,     0,     0,     0,     0,   179,   180,    92,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,    97,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
     101,   102,     0,     0,     0,     0,     0,   103,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,   106,     0,     0,   107,   108,   109,     0,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
       0,   122,     0,   123,   124,   125,   126,     0,   127,     0,
     128,     0,     0,     0,     0,     0,   129,   482,     0,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,   134,   135,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   139,     0,     0,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,   152,     0,     0,     0,     0,     0,     0,   153,
       0,     0,   154,     0,     0,     0,   155,     0,     0,   156,
     157,     0,   158,     0,     0,   159,     0,   160,     0,     0,
       0,   161,   162,     0,     0,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,     0,   172,
       0,     0,     0,     0,   173,   174,     0,     0,    84,    85,
      86,    87,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    89,    90,     0,     0,    91,   175,
     176,     0,   177,   178,     0,     0,     0,     0,   179,   180,
      92,     0,     0,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    96,     0,     0,    97,     0,
       0,    98,     0,     0,     0,     0,     0,    99,     0,     0,
       0,     0,   100,   101,   102,     0,     0,     0,     0,     0,
     103,     0,     0,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,     0,     0,   106,     0,     0,   107,
     108,   109,     0,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,   113,     0,     0,   114,     0,   115,   116,   117,   118,
     119,   120,   121,     0,   122,     0,   123,   124,   125,   126,
       0,   127,     0,   128,     0,     0,     0,     0,     0,   129,
    1102,     0,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,   132,     0,     0,
       0,     0,     0,     0,   133,     0,     0,     0,   134,   135,
     136,   137,   138,     0,     0,     0,     0,     0,     0,   139,
       0,     0,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,     0,   152,     0,     0,     0,     0,
       0,     0,   153,     0,     0,   154,     0,     0,     0,   155,
       0,     0,   156,   157,     0,   158,     0,     0,   159,     0,
     160,     0,     0,     0,   161,   162,     0,     0,     0,     0,
       0,   163,   164,   165,   166,   167,   168,     0,   169,   170,
     171,     0,   172,     0,     0,     0,     0,   173,   174,     0,
       0,    84,    85,    86,    87,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,     0,
       0,    91,   175,   176,     0,   177,   178,     0,     0,     0,
       0,   179,   180,    92,     0,     0,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,     0,
       0,    97,     0,     0,    98,     0,     0,     0,     0,     0,
      99,     0,     0,     0,     0,   100,   101,   102,     0,     0,
       0,     0,     0,   103,     0,     0,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,     0,     0,   106,
       0,     0,   107,   108,   109,     0,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,     0,     0,   114,     0,   115,
     116,   117,   118,   119,   120,   121,     0,   122,     0,   123,
     124,   125,   126,     0,   127,     0,   128,     0,     0,     0,
       0,     0,   129,     0,     0,   130,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1208,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   131,
     132,     0,     0,     0,     0,     0,     0,   133,     0,     0,
       0,   134,   135,   136,   137,   138,     0,     0,     0,     0,
       0,     0,   139,     0,     0,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     0,   152,     0,
       0,     0,     0,     0,     0,   153,     0,     0,   154,     0,
       0,     0,   155,     0,     0,   156,   157,     0,   158,     0,
       0,   159,     0,   160,     0,     0,     0,   161,   162,     0,
       0,     0,     0,     0,   163,   164,   165,   166,   167,   168,
       0,   169,   170,   171,     0,   172,     0,     0,     0,     0,
     173,   174,     0,     0,    84,    85,    86,    87,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    90,     0,     0,    91,   175,   176,     0,   177,   178,
       0,     0,     0,     0,   179,   180,    92,     0,     0,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    96,     0,     0,    97,     0,     0,    98,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,   100,   101,
     102,     0,     0,     0,     0,     0,   103,     0,     0,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
       0,     0,   106,     0,     0,   107,   108,   109,     0,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,     0,     0,
     114,     0,   115,   116,   117,   118,   119,   120,   121,     0,
     122,     0,   123,   124,   125,   126,     0,   127,     0,   128,
       0,     0,     0,     0,     0,   129,     0,     0,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   132,     0,     0,     0,     0,     0,     0,
     133,     0,  1431,     0,   134,   135,   136,   137,   138,     0,
       0,     0,     0,     0,     0,   139,     0,     0,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
       0,   152,     0,     0,     0,     0,     0,     0,   153,     0,
       0,   154,     0,     0,     0,   155,     0,     0,   156,   157,
       0,   158,     0,     0,   159,     0,   160,     0,     0,     0,
     161,   162,     0,     0,     0,     0,     0,   163,   164,   165,
     166,   167,   168,     0,   169,   170,   171,     0,   172,     0,
       0,     0,     0,   173,   174,     0,     0,    84,    85,    86,
      87,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,    90,     0,     0,    91,   175,   176,
       0,   177,   178,     0,     0,     0,     0,   179,   180,    92,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    96,     0,     0,    97,     0,     0,
      98,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   100,   101,   102,     0,     0,     0,     0,     0,   103,
       0,     0,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105,     0,     0,   106,     0,     0,   107,   108,
     109,     0,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     0,   122,     0,   123,   124,   125,   126,     0,
     127,     0,   128,     0,     0,     0,     0,     0,   129,  2077,
       0,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   131,   132,     0,     0,     0,
       0,     0,     0,   133,     0,     0,     0,   134,   135,   136,
     137,   138,     0,     0,     0,     0,     0,     0,   139,     0,
       0,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     0,   152,     0,     0,     0,     0,     0,
       0,   153,     0,     0,   154,     0,     0,     0,   155,     0,
       0,   156,   157,     0,   158,     0,     0,   159,     0,   160,
       0,     0,     0,   161,   162,     0,     0,     0,     0,     0,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
       0,   172,     0,     0,     0,     0,   173,   174,     0,     0,
      84,    85,    86,    87,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,     0,     0,
      91,   175,   176,     0,   177,   178,     0,     0,     0,     0,
     179,   180,    92,     0,     0,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    94,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    96,     0,     0,
      97,     0,     0,    98,     0,     0,     0,     0,     0,    99,
       0,     0,     0,     0,   100,   101,   102,     0,     0,     0,
       0,     0,   103,     0,     0,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,     0,     0,   106,     0,
       0,   107,   108,   109,     0,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   113,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,     0,   122,     0,   123,   124,
     125,   126,     0,   127,     0,   128,     0,     0,     0,     0,
       0,   129,     0,  2239,   130,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   131,   132,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
     134,   135,   136,   137,   138,     0,     0,     0,     0,     0,
       0,   139,     0,     0,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,     0,   152,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   154,     0,     0,
       0,   155,     0,     0,   156,   157,     0,   158,     0,     0,
     159,     0,   160,     0,     0,     0,   161,   162,     0,     0,
       0,     0,     0,   163,   164,   165,   166,   167,   168,     0,
     169,   170,   171,     0,   172,     0,     0,     0,     0,   173,
     174,     0,     0,    84,    85,    86,    87,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,     0,     0,    91,   175,   176,     0,   177,   178,     0,
       0,     0,     0,   179,   180,    92,     0,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      96,     0,     0,    97,     0,     0,    98,     0,     0,     0,
       0,     0,    99,     0,     0,     0,     0,   100,   101,   102,
       0,     0,     0,     0,     0,   103,     0,     0,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,   106,     0,     0,   107,   108,   109,     0,   110,   111,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,   114,
       0,   115,   116,   117,   118,   119,   120,   121,     0,   122,
       0,   123,   124,   125,   126,     0,   127,     0,   128,     0,
       0,     0,     0,     0,   129,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,   132,     0,     0,     0,     0,     0,     0,   133,
       0,     0,     0,   134,   135,   136,   137,   138,     0,     0,
       0,     0,     0,     0,   139,     0,     0,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,     0,
     152,     0,     0,     0,     0,     0,     0,   153,     0,     0,
     154,     0,     0,     0,   155,     0,     0,   156,   157,     0,
     158,     0,     0,   159,     0,   160,     0,     0,     0,   161,
     162,     0,     0,     0,     0,     0,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,     0,   172,     0,     0,
       0,     0,   173,   174,     0,     0,    84,    85,    86,    87,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,    90,     0,     0,    91,   175,   176,     0,
     177,   178,     0,     0,     0,     0,   179,   180,    92,     0,
       0,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,     0,    97,     0,     0,    98,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
     100,   101,   102,     0,     0,     0,     0,     0,   103,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,     0,     0,   106,     0,     0,   107,   108,   109,
       0,   110,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
       0,     0,   114,     0,   115,   116,   117,   118,   119,   120,
     121,     0,   122,     0,   123,   124,   125,   126,     0,   127,
       0,   128,     0,     0,     0,     0,     0,   129,     0,     0,
     130,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,   132,     0,     0,     0,     0,
       0,     0,   133,     0,     0,     0,   134,   135,   136,   137,
     138,     0,     0,     0,     0,     0,     0,   139,     0,     0,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,     0,   152,     0,     0,     0,     0,     0,     0,
     153,     0,     0,   154,     0,     0,     0,   155,     0,     0,
     156,   157,     0,   158,     0,     0,   159,     0,   160,     0,
       0,     0,   214,   162,     0,     0,     0,     0,     0,   163,
     164,   165,   166,   167,   168,     0,   169,   170,   171,     0,
     172,     0,     0,     0,     0,   173,   174,     0,     0,    84,
      85,    86,    87,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    90,     0,     0,    91,
     175,   176,     0,   177,   178,     0,     0,     0,     0,   179,
     180,    92,     0,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    95,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,     0,     0,    97,
       0,     0,    98,     0,     0,     0,     0,     0,    99,     0,
       0,     0,     0,   100,   101,   102,     0,     0,     0,     0,
       0,   103,     0,     0,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,     0,     0,   106,     0,     0,
     107,   108,   109,     0,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,     0,     0,   114,     0,   115,   116,   117,
     118,   119,   120,   121,     0,   122,     0,   123,   124,   125,
     126,     0,   127,     0,   128,     0,     0,     0,     0,     0,
     129,     0,     0,   130,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   132,     0,
       0,     0,     0,     0,     0,   133,     0,     0,     0,   134,
     135,   136,   137,   138,     0,     0,     0,     0,     0,     0,
     139,     0,     0,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,     0,   152,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   154,     0,     0,     0,
     155,     0,     0,   156,   157,     0,   158,     0,     0,   159,
       0,   160,     0,     0,     0,   161,   162,     0,     0,     0,
       0,     0,   163,   164,   165,   166,   167,   168,     0,   169,
     170,   171,     0,   172,     0,     0,     0,     0,   173,   174,
       0,     0,    84,    85,    86,    87,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    89,    90,
       0,     0,    91,   175,   176,     0,   177,   350,     0,     0,
       0,     0,   179,   180,    92,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    96,
       0,     0,    97,     0,     0,    98,     0,     0,     0,     0,
       0,    99,     0,     0,     0,     0,   100,   101,   102,     0,
       0,     0,     0,     0,   103,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,     0,     0,
     106,     0,     0,   107,   108,   109,     0,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,     0,     0,   114,     0,
     115,   116,   117,   118,   119,   120,   121,     0,   122,     0,
     123,   124,   125,   126,     0,   127,     0,   128,     0,     0,
       0,     0,     0,   129,     0,     0,   130,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,   132,     0,     0,     0,     0,     0,     0,   884,     0,
       0,     0,   134,   135,   136,   137,   138,     0,     0,     0,
       0,     0,     0,   139,     0,     0,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,     0,   152,
       0,     0,     0,     0,     0,     0,   153,     0,     0,   154,
       0,     0,     0,   155,     0,     0,   156,   157,     0,   158,
       0,     0,   159,     0,   160,     0,     0,     0,   161,   162,
       0,     0,     0,     0,     0,   163,   164,   165,   166,   167,
     168,     0,   169,   170,   171,     0,   172,     0,     0,     0,
       0,   173,   174,     0,     0,    84,    85,    86,    87,    88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    89,    90,     0,     0,    91,   175,   176,     0,   177,
     178,     0,     0,     0,     0,   179,   180,    92,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,     0,     0,    97,     0,     0,    98,     0,
       0,     0,     0,     0,    99,     0,     0,     0,     0,   100,
     101,   102,     0,     0,     0,     0,     0,   103,     0,     0,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,     0,     0,   106,     0,     0,   107,   108,   109,     0,
     110,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -15,     1,     0,   112,   113,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
       0,   122,     0,   123,   124,   125,   126,     0,   127,     0,
     128,     0,     0,     0,     0,     0,   129,     0,     0,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     4,     5,     6,     0,     0,     0,     0,     0,
       0,     0,     0,   131,   132,     7,     8,     9,    10,     0,
       0,   133,     0,     0,    11,   134,   135,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   139,     0,     0,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,     0,   152,     0,     0,     0,     0,     0,     0,   153,
       0,     0,   154,     0,     0,     0,   155,     0,     0,   156,
     157,     0,   158,     0,    12,   159,     0,   160,     0,     0,
       0,   161,   162,     0,     0,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,     0,   172,
       0,     0,     0,     0,   173,   174,     0,     0,     0,     0,
       0,    13,     0,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175,
     176,     0,   177,  1326,     0,     0,     0,     0,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,     0,     0,     0,     0,     0,     0,     0,
      16,    17,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,    19,     0,    20,     0,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     0,     0,    30,
      31,     0,     0,     0,     0,     0,    32,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,    35,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,     0,    38
};

static const yytype_int16 yycheck[] =
{
       4,    19,   873,     0,   334,     9,   196,   256,    19,    13,
       0,   469,   670,   197,     0,    19,    20,   771,     0,   209,
     485,   271,     0,   254,   832,   647,     0,    31,   381,   670,
     628,    46,   222,   223,   714,  1411,  1173,   227,     0,  1196,
     587,   334,    46,    47,   671,     0,   334,   397,   398,     0,
     758,   988,   760,   990,   334,    32,   851,   673,   469,   647,
      41,   869,   348,   413,  1001,   681,   675,  1196,    32,   320,
     499,  1055,  1056,   359,   683,  1643,    12,    12,  1938,    83,
      15,  1034,    12,    17,   839,   840,     3,     4,   535,  1038,
      91,   627,  1759,  1974,     3,     4,   518,     7,     8,     9,
      10,    11,  1040,   194,   297,    17,   217,     0,   165,   177,
      89,     0,     7,     8,     9,    10,  2033,     0,   177,    44,
     406,   120,  1044,  2082,   280,  1280,    21,   197,     0,   280,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   852,    87,   326,   327,   328,    56,
     286,    70,   194,   120,   120,   187,   194,   132,    53,    54,
      55,   120,   120,   449,   450,   117,   452,  1425,  2255,   187,
     180,   364,   114,    92,   796,  1816,   187,   181,  1819,   140,
     180,   156,    69,   187,   188,  2045,   276,    57,   319,   193,
    1448,  2051,   180,    63,   194,   199,    67,    68,    69,    70,
       7,     8,     9,    10,    11,   336,   158,   277,   194,  2296,
     214,  2170,   368,   210,   211,   212,   213,   368,   250,   120,
     210,   211,   212,   213,   210,   211,   212,   213,   210,   211,
     212,   213,   210,   211,   212,   213,   210,   211,   212,   213,
    1907,   652,   246,   247,  1401,   598,   179,   358,   210,   211,
     212,   213,   702,   800,   842,   210,   211,   212,   213,   210,
     211,   212,   213,    43,    44,   551,   243,   180,   265,   273,
     179,   177,  1401,   277,   180,   265,   201,   368,   242,   265,
     284,   285,  2241,   265,  2144,   243,   324,   265,  1546,     0,
     271,   265,   179,  2153,   298,   299,    12,   301,   302,   303,
     368,   305,   306,   265,   553,   194,   310,    87,   179,   368,
     265,   368,    28,   771,   265,    56,   320,   210,   211,   212,
     213,   210,   211,   212,   213,  2284,   368,   210,   211,   212,
     213,   332,  1254,   955,   684,   933,   765,   295,   210,   211,
     212,   213,   453,   347,  1281,   179,   350,  1284,   895,   353,
     897,   898,   899,    69,  2271,  2236,  2237,   228,   368,  1312,
    1515,  1310,   269,   270,  2224,   397,  2226,   279,   287,   368,
     720,  1939,   265,  1311,   293,   285,   265,  1635,   410,   304,
     368,   997,   265,   124,  1092,   364,  1094,   366,   639,   339,
     580,  1099,  1100,   265,  1003,  1150,  1151,   844,   934,   821,
     822,   368,   368,   337,   179,   300,   301,   302,   303,   368,
     297,   369,   180,   417,   179,   595,   358,    69,  2059,   705,
     180,   363,   339,   427,   853,  1180,   297,   117,   180,   338,
     566,   567,   568,   569,   179,  1115,   369,   373,   373,   179,
     576,   194,   397,   373,    67,    68,   180,    70,  2308,    71,
    2117,   120,  1710,   485,    17,   368,    67,    68,    69,    70,
    1255,   177,   368,   179,   715,   272,  1623,   485,   275,    69,
     474,    88,   180,   368,   485,    12,   926,   927,   482,   180,
      87,   485,  1426,   487,  2052,   489,   490,   491,   492,   493,
     494,   495,   182,   295,  1623,   499,   607,   368,  1426,   210,
     211,   212,   213,   180,   790,    14,     3,     4,   288,    69,
      73,    74,    75,   843,    77,    78,   520,    80,   125,   126,
     180,   128,   129,   130,   556,   177,   133,   179,   244,   180,
      69,   180,   149,   537,   538,   369,   120,  1521,  1522,   117,
     517,   871,   546,    85,   180,   549,   287,   796,   552,   276,
     843,   180,   293,    87,   265,   843,  1493,   521,    83,   180,
     182,   194,   180,   843,  1152,  1153,   368,  1504,   180,   573,
     574,   575,   604,   184,  1511,   108,   526,   177,   871,   179,
     194,   297,   586,   871,   117,   589,   590,   591,  1592,   593,
     594,   871,   345,   194,   369,   520,   600,   180,   602,   603,
     368,   605,  1260,   319,   369,  1232,  1743,   276,   368,   641,
      67,   263,   194,   862,   944,   630,   368,   177,    56,   179,
     906,   180,   908,   180,   369,   158,   630,   659,   660,   369,
    2006,    88,   165,   167,   368,   639,   170,  1317,   177,   925,
     179,     3,     4,   266,   180,   297,     4,   184,   652,   260,
     261,   944,   684,   194,   106,   266,   944,  1266,   293,   691,
     368,  1011,    20,   263,   944,   855,   670,   368,  1612,  1216,
     860,     3,     4,    31,   706,   286,   279,   180,   710,   711,
    1033,  1031,   180,   194,  1612,   263,   124,   179,   140,   180,
     180,   368,   276,   120,   180,   180,   714,   297,   180,   180,
    1050,   198,   199,  1053,  1054,   180,   955,   180,   368,   323,
     714,   715,  1062,   668,   180,   350,   279,   368,   699,   368,
     701,   173,   174,   175,   335,    83,     0,   759,   180,   684,
    2106,  1017,   368,  1019,   172,   368,   691,   297,   345,   368,
    1744,   759,   324,    12,   180,   254,   184,   368,   759,  1886,
     368,   180,   179,   172,   758,   759,   368,   761,   297,   360,
     361,   765,   180,   180,   768,  1922,    21,   180,   180,   180,
      25,    26,   194,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   236,   368,   180,  1117,   180,    67,
      68,    69,    70,  1381,   194,  1383,   180,   293,  1151,    54,
      55,   194,   140,   241,   242,   243,   244,   245,   265,   368,
     814,   368,   345,   265,   194,   177,  1474,   179,  2072,   851,
     272,   273,   854,   242,   243,   244,   245,  1415,   265,  1117,
     188,    91,   368,  1474,   194,   368,   274,  1117,   194,   291,
     184,   199,  1253,     3,     4,   177,   827,   179,   852,   853,
     361,   288,   347,  1475,   350,   293,   214,  1143,     3,     4,
     298,  1541,  1542,   172,  1462,   368,   318,   319,   320,   321,
     368,    87,   876,   877,   878,   879,   194,   368,   368,   140,
     884,  1211,   368,   368,   140,   889,   368,   368,   397,   247,
     894,     3,     4,   368,  1510,   368,   196,  1513,   902,  1252,
     177,   112,   368,  1332,  2158,   343,   258,   259,   346,   331,
      73,    74,    75,   369,    77,    78,   368,    80,  1211,   277,
     264,  1350,   417,  1211,   324,   957,   284,  1257,  1258,   367,
     323,  1211,   368,   242,   243,   244,   245,    22,    23,   368,
     298,   299,   923,   301,   324,   303,    92,   305,   367,   119,
     368,   368,   310,    99,   100,   368,   368,   368,   939,   103,
     964,   117,   178,   323,  1257,  1258,   184,    87,   324,  1257,
    1258,  1202,   117,   117,   368,   134,   368,  1257,  1258,   983,
     139,  2138,   260,   261,   368,   120,   121,   991,   266,   298,
    1022,   268,   487,  1025,   998,   179,   323,   235,   325,     7,
       8,     9,    10,    11,   180,   117,   324,    87,   286,   179,
      90,   288,  1720,   106,    87,  1033,  1034,   106,   194,   179,
     210,   211,  1033,  1055,  1056,    87,   182,  1707,    90,  1033,
    1034,  1578,  1579,  1580,  1038,  1039,  1040,   346,   182,  1043,
     160,   344,    59,   163,   117,   125,   264,   556,   128,   129,
     130,     3,     4,   133,   189,   293,   294,  1343,   367,    67,
      68,    69,    70,   125,    40,    41,   128,   129,   130,   427,
     124,   133,   124,   328,    91,   265,   235,   179,   234,  1034,
     173,   174,   175,  1891,   173,   174,   175,   180,   236,   180,
    1122,   141,  1378,   159,   179,   161,    87,  1115,  1102,    75,
     180,   124,    54,   194,   263,   159,  1110,   161,  1112,   161,
    1440,  1115,  1116,   368,   369,   117,   279,   265,  1404,   263,
     111,   369,  1408,   165,   272,   273,  1412,   283,  1414,   165,
     286,   489,   323,   491,   325,   493,   494,   495,   180,   368,
     296,  1145,  1146,   291,   180,  1034,  1178,  1440,   194,   172,
    1168,   284,  1440,   155,   295,   157,   158,  1168,  1113,   668,
    1440,   323,   520,   325,  1168,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   684,   184,   267,   179,   279,
     538,   180,   691,  1187,   280,   231,   232,   323,   546,   325,
    1194,   549,  1196,   283,   552,   194,  1200,   198,   199,   184,
     185,   368,  1552,  1553,   368,   141,   296,  1457,   372,   280,
     195,  1243,   117,  1444,    91,  1626,   574,  1833,   328,   242,
     243,   244,   245,  1255,  1113,   128,   129,   130,   586,   134,
     368,   589,   590,   591,   139,   593,   594,   183,   249,  1569,
     186,   187,   188,   189,   190,   191,   192,   193,   276,  1253,
     276,   197,   260,   261,   126,   127,  1260,  1261,   266,   768,
      92,   225,   226,    95,   287,   345,    12,  1299,   179,   101,
     293,   294,   276,  1305,  1306,   298,  1308,   182,   286,     3,
       4,  1569,     6,   345,   220,   221,   222,   223,   224,  1569,
     374,   375,   376,   377,  1312,   276,   307,   308,   309,  1317,
     311,   312,  2110,   225,   226,  1591,  1310,  1311,  1312,   293,
    1596,   293,  1642,  1317,  1644,  1973,  1974,     3,     4,  1605,
     343,  1133,  1326,  1135,  1136,  1783,   293,   335,  1332,   234,
     235,   277,  1183,  1184,  1185,  1186,   173,   174,   175,     3,
       4,  1752,  1753,   180,   367,   293,  1350,  1633,   328,  1642,
    1201,  1644,   293,  1357,  1642,   343,  1644,  1312,   263,   173,
     174,   175,  1642,    56,  1644,  1159,   183,  1161,  1162,   186,
     187,   188,   189,   190,   191,   192,   193,   243,   283,   196,
     197,   286,  1386,  1387,  1388,     3,     4,  1391,  1392,  1393,
    2261,   296,  1396,  1397,   233,  1399,  1400,  1401,   243,   183,
      43,    44,   186,   187,   188,   189,   190,   191,   192,   193,
     243,  1429,   196,   197,   727,   728,   729,   243,  1429,  2077,
     369,  1425,   368,  1312,  2082,  1429,  1430,  1431,   317,  1426,
     369,   124,   183,  1844,    86,    87,  1426,   369,  1442,   183,
     949,   950,   951,   183,  1448,  1449,   265,  1451,  2025,   268,
    2027,  2028,  2029,  1739,   368,  1741,   814,   306,  1923,  1745,
     277,   310,   293,   312,   313,   314,   315,   108,    18,   288,
    1474,   293,   291,   292,   318,  1426,  1457,   288,  1459,   172,
    1461,   173,   174,   175,     3,  1466,    93,    94,   180,  1521,
    1522,   184,   179,   277,  1475,   269,   270,  1529,   173,   174,
     175,  1505,   179,  1853,   132,   180,    56,   306,   179,    59,
      23,   310,  2170,   312,   313,   314,   315,  2175,   876,   877,
     878,   879,   179,  1541,  1542,    73,    74,    75,   179,    77,
      78,   889,    80,  1426,  1566,   348,   349,  1541,  1542,   354,
     355,   356,  1546,  1426,  1548,   179,  1055,  1056,   241,   242,
     243,   244,   245,    73,    74,    75,   179,   107,   196,   109,
      80,  2315,   183,  1567,   179,   186,   187,   188,   189,   190,
     191,   192,   193,   179,   124,   179,   197,   179,  2236,  2237,
     179,   274,  1868,  2241,   369,  2043,   179,  1873,     3,     4,
     921,   922,   923,  1777,   287,   104,   105,   179,  1884,   179,
     293,   179,  1606,   198,   199,   298,   179,    18,   939,   940,
     941,   942,   943,   188,   189,  1612,    97,    98,   179,  1623,
     294,   295,  1612,   293,   294,   983,  2284,   179,    73,    74,
      75,  1635,    77,    78,    79,    80,   341,   342,   179,  1643,
      93,    94,  1928,   239,   240,    56,   352,   353,    59,   179,
     343,   350,   351,   346,    67,    68,   277,   360,   361,   212,
     213,  1612,    67,    68,   342,   343,  1670,   645,   646,  1178,
     368,   179,   179,   179,   367,   225,   226,   227,   228,   229,
     230,   179,  1714,  1715,     7,     8,     9,    10,    11,  1707,
     356,   241,   295,   277,   320,   345,   107,   140,   109,   140,
     136,   136,   335,  1707,   121,  2035,  1710,   121,   120,  1713,
      96,   102,   368,   124,  2000,   110,   194,   179,   179,  1612,
     180,   319,   140,   177,   274,  1757,  2012,  1731,   177,  1612,
     247,   182,   179,   179,    39,   179,   319,   287,  1742,   179,
     179,   179,  2035,   293,   176,   179,   296,  2035,   179,   179,
     179,  1783,  1784,  1785,   179,  2035,   179,   299,   141,   369,
      24,   180,   121,  1781,   248,   162,   248,     3,   297,   179,
    1781,   180,   179,   177,   371,   367,    86,  1781,   186,   187,
     188,   189,   190,   191,   192,   193,    83,   211,   120,   197,
     179,    17,   369,   343,   179,   253,   271,   287,   295,   108,
     177,   268,   120,  1312,   336,   279,   177,   275,   110,   279,
     345,   248,   233,  1845,   225,   226,   227,   228,   229,   230,
      24,  1853,   295,   368,   108,  2111,  1830,  1859,   183,  2019,
     241,   183,  1864,   216,   217,   218,   219,   220,   221,   222,
     223,   224,  1200,   263,  1876,   369,   120,   368,   165,   179,
     153,   106,   180,   301,   180,   334,   368,  2315,   117,   141,
     180,    92,   120,   274,   369,  1869,   179,   295,   294,   277,
     272,   271,   275,   120,   117,  2286,   120,   271,   337,   179,
      21,   282,   293,   244,   103,   296,  2216,   279,   345,   180,
     180,  1923,   347,   180,   180,   180,   368,   368,  1853,  1903,
     180,  1933,   295,   368,   180,  1923,   108,   180,  1940,   180,
     179,   238,  1923,   180,   180,   321,   368,   180,  1922,  1923,
    1924,   317,  2112,  2216,   180,   179,   368,   168,  2216,   345,
     179,    79,   343,    79,   180,  1939,  2216,    76,   180,   114,
     180,   179,   277,   180,   334,  1977,   368,  1979,   180,   280,
      17,   280,    94,   177,   279,   288,   179,  1961,   345,  1991,
     279,   150,   180,   246,   345,   180,   150,   263,   180,  1973,
    1974,   369,   345,  2259,   295,   357,    79,   357,   108,   180,
     180,   369,   179,   179,   368,  2017,   113,   180,   108,   106,
     353,   369,   345,   288,   295,   248,   368,   179,  2002,   368,
     108,   368,   281,   278,  2008,   177,   278,  2039,    81,   234,
    2014,   355,  1521,  1522,   180,   180,  2048,   180,   180,   179,
     399,   400,   368,   368,   180,   180,   405,   279,   279,  2033,
    1388,   279,   368,   180,   279,   169,  2033,   108,   271,  1397,
      87,   357,  1400,  2033,   177,   177,   263,  2033,  2052,   135,
     179,  2033,   287,  2057,   179,  2033,   121,   248,   280,  2033,
       7,   117,  2094,   370,   370,   330,   117,  2071,   117,  2101,
     279,  2033,  1430,  2077,   279,   180,  2108,   179,  2082,   180,
     179,   117,   235,   286,   323,   345,   117,   368,  2337,   287,
     368,  1449,  2341,  2125,   179,   278,   178,  2287,   368,    89,
      89,   179,   323,   179,   354,  2109,   368,   161,   158,     3,
     158,   345,   196,   179,  2118,  2119,  2120,  2121,     3,     4,
       5,   163,     7,     8,     9,    10,   141,    12,    13,    14,
      15,    16,   361,    71,  2138,   117,  2140,   350,   179,   359,
     111,  2145,   179,    28,    29,   179,  2150,   271,   136,  2181,
     179,   163,   166,   276,   334,   369,   140,   160,  2190,   129,
      45,    46,   120,   196,   295,   324,  2170,    60,   179,   297,
     122,  2175,   180,   322,    59,   332,   334,   140,   179,   179,
     334,   362,   119,   141,   324,    61,   350,  2219,   180,   180,
     271,   279,   140,   179,   288,  2227,   211,   212,   213,   334,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     322,    70,   334,   128,    62,   177,   279,  2221,   279,   328,
     330,  2253,   117,    67,   140,    68,   340,  2231,   297,    42,
     368,    42,  2236,  2237,   179,  1194,  1612,  2241,  1368,   243,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
    1130,   519,    47,   211,   212,   213,  2204,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,  2271,   242,  2253,
     844,  2275,  2252,  2277,  2271,  1589,  1401,  1623,  1876,  2301,
    2284,  2271,  2286,  2268,  2267,  2271,  2050,  2260,  2203,  2271,
    1935,   521,   111,  2271,   673,   674,   675,  2271,  2325,  2271,
    2050,  1917,   681,  1916,   683,  1569,  2310,   901,     8,  2271,
     520,   191,   828,  1600,  2002,   694,   695,   696,  2007,  2197,
    1412,  2325,   141,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,  2256,  1591,   194,   194,
    2096,  1867,   194,   194,  1853,  2286,  1253,   726,   727,   728,
     729,   854,  1321,   505,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   743,   744,   745,   746,   747,   748,
     749,   750,   751,   752,   753,   754,   755,   756,  1178,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,  1042,
    1548,   474,   211,   212,   213,   960,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,  1977,  2284,  2241,   956,
     368,  1859,   723,  1243,   718,   300,   301,   302,   303,  1005,
     732,  1713,   730,  1781,     3,     4,     5,  2181,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,   780,  1864,
      19,    20,    46,  1024,    23,    24,  1819,  2056,    27,    28,
      29,  1020,   709,  1024,  1817,  1662,   601,  1492,  1503,  1833,
      39,   759,  1495,    42,  1669,    -1,    45,    46,    47,    48,
      49,    50,    51,  2068,    53,   682,   842,    56,    57,    58,
    2076,  1955,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      69,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
     109,   110,    -1,   112,    -1,    -1,    -1,    -1,   117,   118,
      -1,    -1,    -1,   122,   123,  1903,   125,    -1,    -1,   128,
     129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,   143,   144,   145,    -1,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    -1,   163,   164,   165,   166,   167,   168,
      -1,   170,   171,   172,    -1,    -1,    -1,    -1,   177,   178,
     179,   180,   181,   182,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   993,    -1,    -1,    -1,   997,   198,
     199,    -1,    -1,    -1,  1003,    -1,    -1,    -1,    -1,   208,
     209,   210,    -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,  2014,    -1,   237,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,
      -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,
     289,    -1,    -1,    -1,   293,   294,    -1,    -1,   297,    -1,
      -1,   300,   301,   302,   303,   304,   305,    -1,   307,   308,
     309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,
      -1,    -1,    -1,   322,    -1,    -1,    -1,   326,   327,    -1,
      -1,    -1,    -1,    -1,    -1,     7,     8,     9,    10,    -1,
      -1,    -1,   341,   342,    -1,   344,   345,    -1,    -1,    21,
      -1,   350,   351,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,   371,    -1,   373,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    -1,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     7,     8,     9,
      10,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    -1,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,  1262,    -1,   137,   138,  1266,    -1,    -1,
      -1,    -1,  1271,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1289,  1290,  1291,  1292,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    -1,    -1,    23,    24,    -1,    -1,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    42,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    -1,    -1,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,   180,    -1,
      69,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
     109,   110,    -1,   112,    -1,    -1,    -1,    -1,   117,   118,
      -1,    -1,    -1,   122,   123,    -1,   125,    -1,    -1,   128,
     129,   130,   131,   132,   133,    -1,    -1,    -1,   300,   301,
     302,   303,    -1,   142,   143,   144,   145,    -1,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    -1,   163,   164,   165,   166,   167,   168,
      -1,   170,   171,   172,    -1,    -1,    -1,    -1,   177,   178,
     179,    -1,   181,   182,    -1,    -1,    -1,    -1,   300,   301,
     302,   303,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,
     199,    -1,    -1,  1492,    -1,    -1,  1495,    -1,    -1,   208,
     209,   210,    -1,    -1,  1503,    -1,   215,    -1,    -1,    -1,
      -1,  1510,    -1,   293,  1513,    -1,   225,   226,    -1,    -1,
     300,   301,   302,   303,   233,    -1,    -1,    -1,   237,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,
      -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,
     289,    -1,    -1,    -1,   293,   294,    -1,    -1,   297,    -1,
      -1,   300,   301,   302,   303,   304,   305,    -1,   307,   308,
     309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,
      -1,    -1,    -1,   322,    -1,   141,    -1,   326,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   341,   342,    -1,   344,   345,    -1,    -1,    -1,
      -1,   350,   351,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   371,    -1,   373,    -1,    -1,    -1,    -1,    -1,
    1669,    -1,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,    -1,    -1,    -1,   211,   212,   213,    -1,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,    -1,
    1699,    -1,    -1,  1702,    -1,  1704,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    -1,    -1,    23,    24,    -1,    -1,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    -1,    -1,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      -1,    -1,    69,    70,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      87,    -1,    -1,    90,    -1,    -1,  1815,  1816,  1817,    96,
    1819,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,   109,   110,  1833,   112,    -1,    -1,    -1,    -1,
     117,   118,   368,    -1,    -1,   122,   123,    -1,   125,    -1,
      -1,   128,   129,   130,   131,   132,   133,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,   143,   144,   145,    -1,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,    -1,   163,   164,   165,   166,
     167,   168,    -1,   170,   171,   172,    -1,    -1,    -1,    -1,
      -1,   178,   179,   180,   181,   182,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,   209,   210,    -1,    -1,    -1,    -1,   215,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,
     237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
      -1,   248,    -1,    -1,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,    -1,   264,    -1,    -1,
      -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,
      -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,
     287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,
     297,    -1,    -1,   300,   301,   302,   303,   304,   305,    -1,
     307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,
     317,    -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,
     327,    -1,    -1,    -1,    -1,    -1,    -1,  2056,    -1,    -1,
    2059,    -1,    -1,    -1,   341,   342,    -1,   344,   345,    -1,
      -1,    -1,    -1,   350,   351,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   371,    -1,   373,     3,     4,     5,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    19,    20,    -1,    -1,    23,    24,    -1,
      -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    -1,    -1,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,   109,   110,    -1,   112,    -1,    -1,    -1,
      -1,   117,   118,    -1,    -1,    -1,   122,   123,    -1,   125,
      -1,    -1,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,   143,   144,   145,
      -1,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,    -1,   163,   164,   165,
     166,   167,   168,    -1,   170,   171,   172,    -1,    -1,    -1,
      -1,    -1,   178,   179,   180,   181,   182,    -1,   184,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,   211,    -1,    -1,    -1,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,
      -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,
      -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,    -1,   264,    -1,
      -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,
      -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,
      -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,
      -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,   305,
      -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,
     316,   317,    -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,
     326,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   341,   342,    -1,   344,   345,
      -1,    -1,    -1,    -1,   350,   351,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   371,    -1,   373,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,    24,
      -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    -1,
      -1,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,   109,   110,    -1,   112,    -1,    -1,
      -1,    -1,   117,   118,    -1,    -1,    -1,   122,   123,    -1,
     125,    -1,    -1,   128,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,   143,   144,
     145,    -1,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,    -1,   163,   164,
     165,   166,   167,   168,    -1,   170,   171,   172,    -1,    -1,
      -1,    -1,    -1,   178,   179,   180,   181,   182,    -1,   184,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,   199,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   208,   209,   210,   211,    -1,    -1,    -1,
     215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,
      -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,
      -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,    -1,   264,
      -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,
      -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,
      -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,
      -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,
     305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,
      -1,   316,   317,    -1,    -1,    -1,    -1,   322,    -1,    -1,
      -1,   326,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   341,   342,    -1,   344,
     345,    -1,    -1,    -1,    -1,   350,   351,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,   373,     3,
       4,     5,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,
      24,    -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      -1,    -1,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    69,    70,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,   109,   110,    -1,   112,    -1,
      -1,    -1,    -1,   117,   118,    -1,    -1,    -1,   122,   123,
      -1,   125,    -1,    -1,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,   143,
     144,   145,    -1,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,    -1,   163,
     164,   165,   166,   167,   168,    -1,   170,   171,   172,    -1,
      -1,    -1,    -1,   177,   178,   179,    -1,   181,   182,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   198,   199,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   208,   209,   210,    -1,    -1,    -1,
      -1,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,
      -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,
      -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,    -1,
     264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,
     274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,
     284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,
     294,    -1,    -1,   297,    -1,    -1,   300,   301,   302,   303,
     304,   305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,
      -1,    -1,   316,   317,    -1,    -1,    -1,    -1,   322,    -1,
      -1,    -1,   326,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,   342,    -1,
     344,   345,    -1,    -1,    -1,    -1,   350,   351,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,   373,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    19,    20,    -1,    -1,
      23,    24,    -1,    -1,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    42,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    -1,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,   109,   110,    -1,   112,
      -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,   122,
     123,    -1,   125,    -1,    -1,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
     143,   144,   145,    -1,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,    -1,
     163,   164,   165,   166,   167,   168,    -1,   170,   171,   172,
      -1,    -1,    -1,    -1,    -1,   178,   179,    -1,   181,   182,
      -1,    -1,    -1,    -1,   187,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   198,   199,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,    -1,
      -1,    -1,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,
     233,    -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,
      -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
      -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,
      -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,
      -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,
     293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,
     303,   304,   305,    -1,   307,   308,   309,    -1,   311,    -1,
      -1,    -1,    -1,   316,   317,    -1,    -1,    -1,    -1,   322,
      -1,    -1,    -1,   326,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,   342,
      -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,    -1,
      -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,    -1,
      -1,    -1,   365,    -1,    -1,    -1,    -1,    -1,   371,    -1,
     373,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    19,    20,    -1,
      -1,    23,    24,    -1,    -1,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      42,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    70,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,   109,   110,    -1,
     112,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,
     122,   123,    -1,   125,    -1,    -1,   128,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,   143,   144,   145,    -1,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
      -1,   163,   164,   165,   166,   167,   168,    -1,   170,   171,
     172,    -1,    -1,    -1,    -1,    -1,   178,   179,   180,   181,
     182,    -1,   184,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,
      -1,    -1,    -1,   215,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,
      -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,   241,
      -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,
      -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,
     282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,
      -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,
     302,   303,   304,   305,    -1,   307,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,   316,   317,    -1,    -1,    -1,    -1,
     322,    -1,    -1,    -1,   326,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,
     342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   371,
      -1,   373,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    19,    20,
      -1,    -1,    23,    24,    -1,    -1,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    -1,    -1,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    -1,    -1,    69,    70,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,   110,
      -1,   112,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,
      -1,   122,   123,    -1,   125,    -1,    -1,   128,   129,   130,
     131,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,   143,   144,   145,    -1,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,    -1,   163,   164,   165,   166,   167,   168,    -1,   170,
     171,   172,    -1,    -1,    -1,    -1,    -1,   178,   179,    -1,
     181,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,   199,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,
      -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,
      -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,
     241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
     271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,
     281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,
      -1,    -1,   293,   294,    -1,    -1,   297,    -1,    -1,   300,
     301,   302,   303,   304,   305,    -1,   307,   308,   309,    -1,
     311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,    -1,
      -1,   322,    -1,    -1,    -1,   326,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,
     351,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     371,    -1,   373,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    19,
      20,    -1,    -1,    23,    24,    -1,    -1,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    42,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    -1,    -1,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,
     110,    -1,   112,    -1,    -1,   115,   116,   117,   118,    -1,
      -1,    -1,   122,   123,    -1,   125,    -1,    -1,   128,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,   143,   144,   145,    -1,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,    -1,   163,   164,   165,   166,   167,   168,    -1,
     170,   171,   172,    -1,    -1,    -1,    -1,    -1,   178,   179,
      -1,   181,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,   199,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,    -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,
      -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,
      -1,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,
      -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,
      -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,
      -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
     300,   301,   302,   303,   304,   305,    -1,   307,   308,   309,
      -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,
      -1,    -1,   322,    -1,    -1,    -1,   326,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,
     350,   351,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   371,    -1,   373,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    -1,    -1,    23,    24,    -1,    -1,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    42,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    -1,    -1,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
     109,   110,    -1,   112,    -1,    -1,    -1,    -1,   117,   118,
      -1,    -1,    -1,   122,   123,    -1,   125,    -1,    -1,   128,
     129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,   143,   144,   145,    -1,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    -1,   163,   164,   165,   166,   167,   168,
      -1,   170,   171,   172,    -1,    -1,    -1,    -1,    -1,   178,
     179,    -1,   181,   182,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,
     199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,
     209,   210,    -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,
      -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,
     289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,
      -1,   300,   301,   302,   303,   304,   305,    -1,   307,   308,
     309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,
      -1,    -1,    -1,   322,    -1,    -1,    -1,   326,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   341,   342,    -1,   344,   345,    -1,    -1,    -1,
      -1,   350,   351,    -1,    -1,    -1,    -1,    -1,    -1,   358,
      -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,    -1,    -1,
      -1,    -1,   371,    -1,   373,     3,     4,     5,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    -1,    -1,    23,    24,    -1,    -1,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    42,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    -1,    -1,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   109,   110,    -1,   112,    -1,    -1,    -1,    -1,   117,
     118,    -1,    -1,    -1,   122,   123,    -1,   125,    -1,    -1,
     128,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   142,   143,   144,   145,    -1,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,    -1,   163,   164,   165,   166,   167,
     168,    -1,   170,   171,   172,    -1,    -1,    -1,    -1,    -1,
     178,   179,    -1,   181,   182,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     198,   199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,   211,    -1,    -1,    -1,   215,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,
      -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,
     238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,
     248,    -1,    -1,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,
      -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,
     278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,
      -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,
      -1,    -1,   300,   301,   302,   303,   304,   305,    -1,   307,
     308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,
      -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,   327,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   341,   342,    -1,   344,   345,    -1,    -1,
      -1,    -1,   350,   351,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   371,    -1,   373,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    -1,    -1,    23,    24,    -1,    -1,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    -1,    -1,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,   109,   110,    -1,   112,    -1,    -1,    -1,    -1,
     117,   118,    -1,    -1,    -1,   122,   123,    -1,   125,    -1,
      -1,   128,   129,   130,   131,   132,   133,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,   143,   144,   145,    -1,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,    -1,   163,   164,   165,   166,
     167,   168,    -1,   170,   171,   172,    -1,    -1,    -1,    -1,
      -1,   178,   179,    -1,   181,   182,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,   209,   210,    -1,    -1,    -1,    -1,   215,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,
     237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
      -1,   248,    -1,    -1,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,    -1,    -1,
      -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,
      -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,
     287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,
      -1,    -1,    -1,   300,   301,   302,   303,   304,   305,    -1,
     307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,
     317,    -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,
     327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   341,   342,    -1,   344,   345,    -1,
      -1,    -1,    -1,   350,   351,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   371,    -1,   373,     3,     4,     5,
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    19,    20,    -1,    -1,    23,    24,    -1,
      -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    -1,    -1,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,   109,   110,    -1,   112,    -1,    -1,    -1,
      -1,   117,   118,    -1,    -1,    -1,   122,   123,    -1,   125,
      -1,    -1,   128,   129,   130,   131,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   142,   143,   144,   145,
      -1,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,    -1,   163,   164,   165,
     166,   167,   168,    -1,   170,   171,   172,    -1,    -1,    -1,
      -1,    -1,   178,   179,    -1,   181,   182,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,    -1,    -1,    -1,    -1,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,
      -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,
      -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,    -1,   264,    -1,
      -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,
      -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,
      -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,
      -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,   305,
      -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,
     316,   317,    -1,    -1,    -1,    -1,   322,   323,    -1,    -1,
     326,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   341,   342,    -1,   344,   345,
      -1,    -1,    -1,    -1,   350,   351,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   371,    -1,   373,     3,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,    24,
      -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    -1,
      -1,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,   109,   110,    -1,   112,    -1,    -1,
      -1,    -1,   117,   118,    -1,    -1,    -1,   122,   123,    -1,
     125,    -1,    -1,   128,   129,   130,   131,   132,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,   143,   144,
     145,    -1,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,    -1,   163,   164,
     165,   166,   167,   168,    -1,   170,   171,   172,    -1,    -1,
      -1,    -1,    -1,   178,   179,   180,   181,   182,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,   199,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   208,   209,   210,    -1,    -1,    -1,    -1,
     215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,
      -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,
      -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,    -1,   264,
      -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,
      -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,
      -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,
      -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,
     305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,
      -1,   316,   317,    -1,    -1,    -1,    -1,   322,    -1,    -1,
      -1,   326,   327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   341,   342,    -1,   344,
     345,    -1,    -1,    -1,    -1,   350,   351,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,   373,     3,
       4,     5,    -1,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    19,    20,    -1,    -1,    23,
      24,    -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    42,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      -1,    -1,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,   109,   110,    -1,   112,    -1,
      -1,    -1,    -1,   117,   118,    -1,    -1,    -1,   122,   123,
      -1,   125,    -1,    -1,   128,   129,   130,   131,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,   143,
     144,   145,    -1,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,    -1,   163,
     164,   165,   166,   167,   168,    -1,   170,   171,   172,    -1,
      -1,    -1,    -1,    -1,   178,   179,    -1,   181,   182,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   198,   199,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   208,   209,   210,    -1,    -1,    -1,
      -1,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,
      -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,
      -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,    -1,
     264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,
     274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,
     284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,
     294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,
     304,   305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,
      -1,    -1,   316,   317,    -1,    -1,    -1,    -1,   322,   323,
      -1,    -1,   326,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,   342,    -1,
     344,   345,    -1,    -1,    -1,    -1,   350,   351,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,   373,
       3,     4,     5,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    19,    20,    -1,    -1,
      23,    24,    -1,    -1,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    42,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    -1,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,   109,   110,    -1,   112,
      -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,   122,
     123,    -1,   125,    -1,    -1,   128,   129,   130,   131,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,
     143,   144,   145,    -1,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,    -1,
     163,   164,   165,   166,   167,   168,    -1,   170,   171,   172,
      -1,    -1,    -1,    -1,    -1,   178,   179,    -1,   181,   182,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   198,   199,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,    -1,
      -1,    -1,   215,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,
     233,    -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,
      -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
      -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,
      -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,
      -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,
     293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,
     303,   304,   305,    -1,   307,   308,   309,    -1,   311,    -1,
      -1,    -1,    -1,   316,   317,    -1,    -1,    -1,    -1,   322,
      -1,    -1,    -1,   326,   327,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,   342,
      -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   364,    -1,    -1,    -1,    -1,    -1,    -1,   371,    -1,
     373,     3,     4,     5,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    19,    20,    -1,
      -1,    23,    24,    -1,    -1,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      42,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      -1,    53,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    -1,    -1,    -1,    70,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,   109,   110,    -1,
     112,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,    -1,
     122,   123,    -1,   125,    -1,    -1,   128,   129,   130,   131,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,   143,   144,   145,    -1,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
      -1,   163,   164,   165,   166,   167,   168,    -1,   170,   171,
     172,    -1,    -1,    -1,    -1,    -1,   178,   179,    -1,   181,
     182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,
      -1,    -1,    -1,   215,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,
      -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,   241,
      -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,
      -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,
     282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,
      -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,
     302,   303,   304,   305,    -1,   307,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,   316,   317,    -1,    -1,    -1,    -1,
     322,    -1,    -1,    -1,   326,   327,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,
     342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   364,    -1,    -1,    -1,    -1,    -1,    -1,   371,
      -1,   373,     3,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    19,    20,
      -1,    -1,    23,    24,    -1,    -1,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    -1,    -1,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,   110,
      -1,   112,    -1,    -1,    -1,    -1,   117,   118,    -1,    -1,
      -1,   122,   123,    -1,   125,    -1,    -1,   128,   129,   130,
     131,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   142,   143,   144,   145,    -1,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,    -1,   163,   164,   165,   166,   167,   168,    -1,   170,
     171,   172,    -1,    -1,    -1,    -1,    -1,   178,   179,    -1,
     181,   182,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,   199,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,
      -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,
      -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,
     241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
     271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,
     281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,
      -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,
     301,   302,   303,   304,   305,    -1,   307,   308,   309,    -1,
     311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,    -1,
      -1,   322,    -1,    -1,    -1,   326,   327,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,
     351,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     371,    -1,   373,     3,     4,     5,    -1,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    19,
      20,    -1,    -1,    23,    24,    -1,    -1,    27,    28,    29,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    42,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    -1,    -1,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,
      -1,    -1,   112,    -1,    -1,    -1,    -1,   117,   118,    -1,
      -1,    -1,   122,   123,    -1,   125,    -1,    -1,   128,   129,
     130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,    -1,
     170,   171,   172,    -1,    -1,    -1,    -1,    -1,   178,   179,
      -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,   199,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,    -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,
      -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,
      -1,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,
      -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,
      -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,
      -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
     300,   301,   302,   303,   304,   305,    -1,   307,   308,   309,
      -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,
      -1,    -1,   322,    -1,    -1,    -1,   326,   327,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,
     350,   351,    -1,    -1,     3,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      19,    20,    -1,   373,    23,    24,    -1,    -1,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    42,    -1,    -1,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    -1,    -1,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
     109,    -1,    -1,   112,    -1,    -1,    -1,    -1,   117,   118,
      -1,    -1,    -1,   122,   123,    -1,   125,    -1,    -1,   128,
     129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,   143,   144,   145,    -1,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    -1,   163,   164,   165,   166,   167,   168,
      -1,   170,   171,   172,    -1,    -1,    -1,    -1,    -1,   178,
     179,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,
     199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,
     209,   210,    -1,    -1,    -1,    -1,   215,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,    -1,    -1,    -1,
      -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,
      -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,
     289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,
      -1,   300,   301,   302,   303,   304,   305,    -1,   307,   308,
     309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,
      -1,    -1,    -1,   322,    -1,    -1,    -1,   326,   327,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   341,   342,    -1,   344,   345,    -1,    -1,    -1,
      -1,   350,   351,    -1,    -1,     3,     4,     5,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    19,    20,    -1,   373,    23,    24,    -1,    -1,    27,
      28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    42,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    -1,    -1,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   109,    -1,    -1,   112,    -1,    -1,    -1,    -1,   117,
     118,    -1,    -1,    -1,   122,   123,    -1,   125,    -1,    -1,
     128,   129,   130,   131,   132,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,    -1,   163,   164,   165,   166,   167,
     168,    -1,   170,   171,   172,    -1,    -1,    -1,    -1,    -1,
     178,   179,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     198,   199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,    -1,    -1,    -1,    -1,   215,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,
      -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,
     238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,
     248,    -1,    -1,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,
      -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,
     278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,
      -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,
      -1,    -1,   300,   301,   302,   303,   304,   305,    -1,   307,
     308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,
      -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,   327,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   341,   342,    -1,   344,   345,    -1,    -1,
      -1,    -1,   350,   351,    -1,    -1,     3,     4,     5,    -1,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    -1,   373,    23,    24,    -1,    -1,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    -1,    -1,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,   109,    -1,    -1,   112,    -1,    -1,    -1,    -1,
     117,   118,    -1,    -1,    -1,   122,   123,    -1,   125,    -1,
      -1,   128,   129,   130,   131,   132,   133,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,   143,   144,   145,    -1,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,    -1,   163,   164,   165,   166,
     167,   168,    -1,   170,   171,   172,    -1,    -1,    -1,    -1,
      -1,   178,   179,    -1,   181,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,   209,   210,    -1,    -1,    -1,    -1,   215,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,
     237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
      -1,   248,    -1,    -1,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,    -1,   264,    -1,    -1,
      -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,
      -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,
     287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,
      -1,    -1,    -1,   300,   301,   302,   303,   304,   305,    -1,
     307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,
     317,    -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,   326,
     327,    -1,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,   341,   342,    -1,   344,   345,    -1,
      -1,    23,    24,   350,   351,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,   373,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,   125,    -1,    -1,   128,   129,   130,    -1,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,    -1,
      -1,   153,    -1,   155,   156,   157,   158,   159,   160,   161,
      -1,   163,    -1,   165,   166,   167,   168,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,   181,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,
      -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,   241,
     242,   243,   244,   245,    -1,    -1,   248,    -1,    -1,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,
      -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,
     282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,
      -1,   293,   294,    -1,    -1,   177,    -1,   179,   300,   301,
     302,   303,   304,   305,    -1,   307,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,   316,   317,    -1,    -1,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    27,   341,
     342,    -1,   344,   345,    -1,    -1,   228,    -1,   350,   351,
      39,    -1,    -1,    42,   236,   237,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,   367,    -1,   249,   250,    -1,
     252,    -1,    -1,    -1,    -1,    64,    -1,    -1,    67,    68,
      69,    70,    -1,   265,   266,    -1,    -1,    -1,    -1,    -1,
     272,   273,    81,    82,    83,    84,    -1,    -1,    87,    -1,
      -1,    90,    -1,    -1,    -1,    -1,   288,    96,    -1,   291,
      -1,    -1,   101,   102,   103,   297,    -1,    -1,    -1,    -1,
     109,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,   125,    -1,    -1,   128,
     129,   130,    -1,   132,   133,    -1,    -1,    -1,    -1,    -1,
      -1,   333,    -1,   335,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,    -1,    -1,   153,    -1,   155,   156,   157,   158,
     159,   160,   161,    -1,   163,    -1,   165,   166,   167,   168,
      -1,   170,    -1,   172,     7,     8,     9,    10,    -1,   178,
      -1,    -1,   181,    -1,    -1,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    -1,    -1,    -1,   225,   226,    -1,   228,
      -1,    -1,    -1,    -1,   233,    -1,    -1,   236,   237,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,    -1,   264,   265,   266,    -1,    -1,
      -1,    -1,   271,   272,   273,   274,    -1,    -1,    -1,   278,
      -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,   288,
     289,   290,   291,    -1,   293,   294,    -1,    -1,    -1,    -1,
      -1,   300,   301,   302,   303,   304,   305,    -1,   307,   308,
     309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,
      -1,    -1,    -1,   322,    -1,    -1,   325,    -1,    -1,   328,
     329,   330,    -1,    -1,   333,    -1,   335,     7,     8,     9,
      10,    11,   341,   342,    -1,   344,   345,    -1,    -1,    -1,
      -1,   350,   351,    23,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    -1,    -1,    87,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,
      -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,   125,   141,    -1,   128,   129,
     130,    -1,   132,   133,    -1,    -1,    -1,   300,   301,   302,
     303,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,    -1,    -1,   153,    -1,   155,   156,   157,   158,   159,
     160,   161,    -1,   163,    -1,   165,   166,   167,   168,    -1,
     170,    -1,   172,    -1,    -1,    -1,    -1,    -1,   178,    -1,
      -1,   181,    -1,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,    -1,    -1,    -1,   211,   212,   213,    -1,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,    -1,   228,    -1,
      -1,    -1,    -1,   233,    -1,    -1,   236,   237,   238,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,   264,   265,   266,    -1,    -1,    -1,
      -1,   271,   272,   273,   274,    -1,    -1,    -1,   278,    -1,
      -1,   281,   282,    -1,   284,    -1,    -1,   287,   288,   289,
     290,   291,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
     300,   301,   302,   303,   304,   305,    -1,   307,   308,   309,
      -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,
      -1,    -1,   322,     7,     8,     9,    10,    11,   328,    -1,
      -1,    -1,    -1,   333,    -1,   335,    -1,    -1,    -1,    23,
      24,   341,   342,    27,   344,   345,    -1,    -1,    -1,    -1,
     350,   351,    -1,   368,    -1,    39,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,   125,   141,    -1,   128,   129,   130,    -1,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,    -1,    -1,   153,
      -1,   155,   156,   157,   158,   159,   160,   161,    -1,   163,
      -1,   165,   166,   167,   168,    -1,   170,    -1,   172,    -1,
      -1,    -1,    -1,    -1,   178,    -1,    -1,   181,    -1,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,    -1,
      -1,    -1,   211,   212,   213,    -1,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,    -1,   228,    -1,    -1,    -1,    -1,   233,
      -1,    -1,   236,   237,   238,   239,   240,   241,    -1,    -1,
      -1,    -1,    -1,    -1,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,    -1,
     264,   265,   266,    -1,    -1,    -1,    -1,   271,   272,   273,
     274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,
     284,    -1,    -1,   287,   288,   289,   290,   291,    -1,   293,
     294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,
     304,   305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,
      -1,    -1,   316,   317,    -1,    -1,    -1,    -1,   322,     7,
       8,     9,    10,    11,   328,    -1,   330,    -1,    -1,   333,
      -1,   335,    -1,    -1,    -1,    23,    24,   341,   342,    27,
     344,   345,    -1,    -1,    -1,    -1,   350,   351,    -1,   368,
      -1,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    -1,    -1,    87,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   109,    -1,    -1,   112,    -1,   121,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,   125,    -1,    -1,
     128,   129,   130,    -1,   132,   133,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,    -1,    -1,   153,    -1,   155,   156,   157,
     158,   159,   160,   161,    -1,   163,    -1,   165,   166,   167,
     168,    -1,   170,    -1,   172,   180,    -1,    -1,    -1,    -1,
     178,    -1,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,    -1,    -1,    -1,   211,   212,   213,    -1,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,
     228,    -1,    -1,    -1,    -1,   233,    -1,    -1,   236,   237,
     238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,    -1,   264,   265,   266,    -1,
      -1,    -1,    -1,   271,   272,   273,   274,    -1,    -1,    -1,
     278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,
     288,   289,   290,   291,    -1,   293,   294,    -1,    -1,    -1,
      -1,    -1,   300,   301,   302,   303,   304,   305,    -1,   307,
     308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,
      -1,    -1,    -1,    -1,   322,     7,     8,     9,    10,    11,
     328,    -1,    -1,    -1,    -1,   333,   334,   335,    -1,    -1,
      -1,    23,    24,   341,   342,    27,   344,   345,    -1,    -1,
      -1,    -1,   350,   351,    -1,    -1,    -1,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,   125,   141,    -1,   128,   129,   130,    -1,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,    -1,
      -1,   153,    -1,   155,   156,   157,   158,   159,   160,   161,
      -1,   163,    -1,   165,   166,   167,   168,    -1,   170,    -1,
     172,    -1,   189,    -1,    -1,    -1,   178,    -1,    -1,   181,
      -1,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,    -1,    -1,    -1,   211,   212,   213,    -1,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,    -1,   228,    -1,    -1,    -1,
      -1,   233,    -1,    -1,   236,   237,   238,   239,   240,   241,
      -1,    -1,    -1,    -1,    -1,    -1,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,   264,   265,   266,    -1,    -1,    -1,    -1,   271,
     272,   273,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,
     282,    -1,   284,    -1,    -1,   287,   288,   289,   290,   291,
      -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,
     302,   303,   304,   305,    -1,   307,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,   316,   317,    -1,    -1,    -1,    -1,
     322,     7,     8,     9,    10,    11,   328,    -1,    -1,    -1,
      -1,   333,    -1,   335,    -1,    -1,    -1,    23,    24,   341,
     342,    27,   344,   345,    -1,    -1,    -1,    -1,   350,   351,
      -1,    -1,    -1,    39,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    -1,
      -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,   109,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,   125,
      -1,    -1,   128,   129,   130,    -1,   132,   133,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   150,    -1,    -1,   153,    -1,   155,
     156,   157,   158,   159,   160,   161,    -1,   163,    -1,   165,
     166,   167,   168,    -1,   170,    -1,   172,   180,    -1,    -1,
      -1,    -1,   178,    -1,    -1,   181,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,    -1,    -1,    -1,   211,   212,
     213,    -1,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,    -1,   228,    -1,    -1,    -1,    -1,   233,    -1,    -1,
      -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,
      -1,    -1,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,    -1,   264,    -1,
     266,    -1,    -1,    -1,    -1,   271,   272,   273,   274,    -1,
      -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,
      -1,   287,   288,   289,   290,    -1,    -1,   293,   294,    -1,
      -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,   305,
      -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,
     316,   317,    -1,    -1,    -1,    -1,   322,     7,     8,     9,
      10,    11,   328,    -1,    -1,    -1,    -1,   333,   334,   335,
      -1,    -1,    -1,    23,    24,   341,   342,    27,   344,   345,
      -1,    -1,    -1,    -1,   350,   351,    -1,    -1,    -1,    39,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    -1,    -1,    87,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,
      -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,   125,    -1,    -1,   128,   129,
     130,    -1,   132,   133,   141,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,    -1,    -1,   153,    -1,   155,   156,   157,   158,   159,
     160,   161,    -1,   163,    -1,   165,   166,   167,   168,    -1,
     170,    -1,   172,   180,    -1,    -1,    -1,    -1,   178,    -1,
      -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,    -1,    -1,    -1,   211,   212,   213,    -1,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,    -1,   228,    -1,
      -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,   264,    -1,   266,    -1,    -1,    -1,
      -1,   271,   272,   273,   274,    -1,    -1,    -1,   278,    -1,
      -1,   281,   282,    -1,   284,    -1,    -1,   287,   288,   289,
     290,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
     300,   301,   302,   303,   304,   305,    -1,   307,   308,   309,
      -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,
      -1,    -1,   322,     7,     8,     9,    10,    11,   328,    -1,
      -1,    -1,    -1,   333,    -1,   335,    -1,    -1,    -1,    23,
      24,   341,   342,    27,   344,   345,    -1,    -1,    -1,    -1,
     350,   351,    -1,    -1,    -1,    39,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    69,    70,    -1,    72,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,   125,    -1,    -1,   128,   129,   130,    -1,   132,   133,
     141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,    -1,    -1,   153,
      -1,   155,   156,   157,   158,   159,   160,   161,    -1,   163,
      -1,   165,   166,   167,   168,    -1,   170,    -1,   172,   180,
      -1,    -1,    -1,   177,   178,   179,    -1,   181,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,    -1,    -1,    -1,
     211,   212,   213,    -1,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,
      -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,
      -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,    -1,
     264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,
     274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,
     284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,
     294,    -1,    -1,   297,    -1,    -1,   300,   301,   302,   303,
     304,   305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,
      -1,    -1,   316,   317,    -1,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    24,    -1,    -1,    27,   341,   342,    -1,
     344,   345,    -1,    -1,    -1,    -1,   350,   351,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,
      -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,   125,    -1,    -1,   128,   129,   130,
      -1,   132,   133,   141,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
      -1,    -1,   153,    -1,   155,   156,   157,   158,   159,   160,
     161,    -1,   163,    -1,   165,   166,   167,   168,    -1,   170,
      -1,   172,   180,    -1,    -1,    -1,    -1,   178,   179,    -1,
     181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
      -1,    -1,    -1,   211,   212,   213,    -1,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,
      -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,
     241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
     271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,
     281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,
      -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,
     301,   302,   303,   304,   305,    -1,   307,   308,   309,    -1,
     311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    27,
     341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,
     351,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    59,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   109,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,   125,    -1,    -1,
     128,   129,   130,    -1,   132,   133,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,    -1,    -1,   153,    -1,   155,   156,   157,
     158,   159,   160,   161,    -1,   163,    -1,   165,   166,   167,
     168,    -1,   170,    -1,   172,   180,    -1,    -1,    -1,    -1,
     178,    -1,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,    -1,    -1,    -1,   211,   212,   213,    -1,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,
     228,   229,   230,    -1,    -1,   233,    -1,    -1,    -1,   237,
     238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,
     248,    -1,    -1,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,
      -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,
     278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,
      -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,
      -1,    -1,   300,   301,   302,   303,   304,   305,    -1,   307,
     308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,
      -1,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      -1,    -1,    27,   341,   342,    -1,   344,   345,    -1,    -1,
      -1,    -1,   350,   351,    39,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
     125,   141,    -1,   128,   129,   130,    -1,   132,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,    -1,    -1,   153,    -1,
     155,   156,   157,   158,   159,   160,   161,    -1,   163,    -1,
     165,   166,   167,   168,    -1,   170,    -1,   172,    -1,    -1,
      -1,    -1,    -1,   178,   179,    -1,   181,    -1,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,    -1,    -1,
      -1,   211,   212,   213,    -1,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,
      -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,
      -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,    -1,   264,
      -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,
      -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,
      -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,
      -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,
     305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,
      -1,   316,   317,    -1,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    -1,    -1,    27,   341,   342,    -1,   344,
     345,    -1,    -1,    -1,    -1,   350,   351,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,   125,    -1,    -1,   128,   129,   130,    -1,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,    -1,
      -1,   153,    -1,   155,   156,   157,   158,   159,   160,   161,
      -1,   163,    -1,   165,   166,   167,   168,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,   181,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   211,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,
      -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,   241,
      -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,
      -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,
     282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,
      -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,
     302,   303,   304,   305,    -1,   307,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,   316,   317,    -1,    -1,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    27,   341,
     342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
     109,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,   125,    -1,    -1,   128,
     129,   130,    -1,   132,   133,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,    -1,    -1,   153,    -1,   155,   156,   157,   158,
     159,   160,   161,    -1,   163,    -1,   165,   166,   167,   168,
      -1,   170,    -1,   172,    -1,    -1,    -1,    -1,    -1,   178,
     179,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,
      -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,
     289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,
      -1,   300,   301,   302,   303,   304,   305,    -1,   307,   308,
     309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,
      -1,    27,   341,   342,    -1,   344,   345,    -1,    -1,    -1,
      -1,   350,   351,    39,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,   109,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,   125,
      -1,    -1,   128,   129,   130,    -1,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   150,    -1,    -1,   153,    -1,   155,
     156,   157,   158,   159,   160,   161,    -1,   163,    -1,   165,
     166,   167,   168,    -1,   170,    -1,   172,    -1,    -1,    -1,
      -1,    -1,   178,    -1,    -1,   181,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,
      -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,
      -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,    -1,   264,    -1,
      -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,
      -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,
      -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,
      -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,   305,
      -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,
     316,   317,    -1,    -1,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    24,    -1,    -1,    27,   341,   342,    -1,   344,   345,
      -1,    -1,    -1,    -1,   350,   351,    39,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,   112,
      -1,    -1,   115,   116,    -1,   118,    -1,    -1,    -1,   122,
      -1,    -1,   125,    -1,    -1,   128,   129,   130,    -1,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,    -1,    -1,
     153,    -1,   155,   156,   157,   158,   159,   160,   161,    -1,
     163,    -1,   165,   166,   167,   168,    -1,   170,    -1,   172,
      -1,    -1,    -1,    -1,    -1,   178,   179,    -1,   181,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,
     233,    -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,
      -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
      -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,
      -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,
      -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,
     293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,
     303,   304,   305,    -1,   307,   308,   309,    -1,   311,    -1,
      -1,    -1,    -1,   316,   317,    -1,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    -1,    27,   341,   342,
      -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,    39,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,
      -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,   125,    -1,    -1,   128,   129,
     130,    -1,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,    -1,    -1,   153,    -1,   155,   156,   157,   158,   159,
     160,   161,    -1,   163,    -1,   165,   166,   167,   168,    -1,
     170,    -1,   172,    -1,    -1,    -1,    -1,    -1,   178,    -1,
      -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,
      -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,
      -1,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,
      -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,
      -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,
      -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
     300,   301,   302,   303,   304,   305,    -1,   307,   308,   309,
      -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,
      27,   341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,
     350,   351,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,   109,    -1,    -1,   112,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,   125,    -1,
      -1,   128,   129,   130,    -1,   132,   133,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,    -1,    -1,   153,    -1,   155,   156,
     157,   158,   159,   160,   161,    -1,   163,    -1,   165,   166,
     167,   168,    -1,   170,    -1,   172,    -1,    -1,    -1,    -1,
      -1,   178,   179,    -1,   181,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,
     237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
      -1,   248,    -1,    -1,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,    -1,   264,    -1,    -1,
      -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,
      -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,
     287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,
     297,    -1,    -1,   300,   301,   302,   303,   304,   305,    -1,
     307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,
     317,    -1,    -1,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    -1,    -1,    27,   341,   342,    -1,   344,   345,    -1,
      -1,    -1,    -1,   350,   351,    39,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,   125,    -1,    -1,   128,   129,   130,    -1,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,    -1,    -1,   153,
      -1,   155,   156,   157,   158,   159,   160,   161,    -1,   163,
      -1,   165,   166,   167,   168,    -1,   170,    -1,   172,    -1,
      -1,    -1,    -1,    -1,   178,    -1,    -1,   181,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,
      -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,
      -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,    -1,
     264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,
     274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,
     284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,
     294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,
     304,   305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,
      -1,    -1,   316,   317,    -1,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    24,    -1,    -1,    27,   341,   342,    -1,
     344,   345,    -1,    -1,    -1,    -1,   350,   351,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,
      -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,   125,    -1,    -1,   128,   129,   130,
      -1,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
      -1,    -1,   153,    -1,   155,   156,   157,   158,   159,   160,
     161,    -1,   163,    -1,   165,   166,   167,   168,    -1,   170,
      -1,   172,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,
     181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,
      -1,    -1,   233,    -1,   235,    -1,   237,   238,   239,   240,
     241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
     271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,
     281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,
      -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,
     301,   302,   303,   304,   305,    -1,   307,   308,   309,    -1,
     311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    27,
     341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,
     351,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   109,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,   125,    -1,    -1,
     128,   129,   130,    -1,   132,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,    -1,    -1,   153,    -1,   155,   156,   157,
     158,   159,   160,   161,    -1,   163,    -1,   165,   166,   167,
     168,    -1,   170,    -1,   172,    -1,    -1,    -1,    -1,    -1,
     178,    -1,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,
      -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,
     238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,
     248,    -1,    -1,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,
      -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,
     278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,
     288,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,
      -1,    -1,   300,   301,   302,   303,   304,   305,    -1,   307,
     308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,
      -1,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      -1,    -1,    27,   341,   342,    -1,   344,   345,    -1,    -1,
      -1,    -1,   350,   351,    39,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
     125,    -1,    -1,   128,   129,   130,    -1,   132,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,    -1,    -1,   153,    -1,
     155,   156,   157,   158,   159,   160,   161,    -1,   163,    -1,
     165,   166,   167,   168,    -1,   170,    -1,   172,    -1,    -1,
      -1,    -1,    -1,   178,    -1,    -1,   181,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   194,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,
      -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,
      -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,    -1,   264,
      -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,
      -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,
      -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,
      -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,
     305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,
      -1,   316,   317,    -1,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    -1,    -1,    27,   341,   342,    -1,   344,
     345,    -1,    -1,    -1,    -1,   350,   351,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,   125,    -1,    -1,   128,   129,   130,    -1,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,    -1,
      -1,   153,    -1,   155,   156,   157,   158,   159,   160,   161,
      -1,   163,    -1,   165,   166,   167,   168,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,   178,   179,    -1,   181,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,
      -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,   241,
      -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,
      -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,
     282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,
      -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,
     302,   303,   304,   305,    -1,   307,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,   316,   317,    -1,    -1,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    27,   341,
     342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,
      39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,
      -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,
     109,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   122,    -1,    -1,   125,    -1,    -1,   128,
     129,   130,    -1,   132,   133,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,    -1,    -1,   153,    -1,   155,   156,   157,   158,
     159,   160,   161,    -1,   163,    -1,   165,   166,   167,   168,
      -1,   170,    -1,   172,    -1,    -1,    -1,    -1,    -1,   178,
     179,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,
      -1,    -1,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,
      -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,
     289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,
      -1,   300,   301,   302,   303,   304,   305,    -1,   307,   308,
     309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,
      -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,
      -1,    27,   341,   342,    -1,   344,   345,    -1,    -1,    -1,
      -1,   350,   351,    39,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,
      -1,    -1,    -1,   109,    -1,    -1,   112,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,   125,
      -1,    -1,   128,   129,   130,    -1,   132,   133,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   150,    -1,    -1,   153,    -1,   155,
     156,   157,   158,   159,   160,   161,    -1,   163,    -1,   165,
     166,   167,   168,    -1,   170,    -1,   172,    -1,    -1,    -1,
      -1,    -1,   178,    -1,    -1,   181,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,
      -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,
      -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,    -1,   264,    -1,
      -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,
      -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,
      -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,
      -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,   305,
      -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,
     316,   317,    -1,    -1,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    24,    -1,    -1,    27,   341,   342,    -1,   344,   345,
      -1,    -1,    -1,    -1,   350,   351,    39,    -1,    -1,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,   112,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,
      -1,    -1,   125,    -1,    -1,   128,   129,   130,    -1,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,    -1,    -1,
     153,    -1,   155,   156,   157,   158,   159,   160,   161,    -1,
     163,    -1,   165,   166,   167,   168,    -1,   170,    -1,   172,
      -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,   181,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,
     233,    -1,   235,    -1,   237,   238,   239,   240,   241,    -1,
      -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
      -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,
      -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,
      -1,   284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,
     293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,
     303,   304,   305,    -1,   307,   308,   309,    -1,   311,    -1,
      -1,    -1,    -1,   316,   317,    -1,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    23,    24,    -1,    -1,    27,   341,   342,
      -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,    39,
      -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,
      90,    -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,
      -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,   125,    -1,    -1,   128,   129,
     130,    -1,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,    -1,    -1,   153,    -1,   155,   156,   157,   158,   159,
     160,   161,    -1,   163,    -1,   165,   166,   167,   168,    -1,
     170,    -1,   172,    -1,    -1,    -1,    -1,    -1,   178,   179,
      -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,
      -1,    -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,
      -1,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,
      -1,   271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,
      -1,   281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,
      -1,    -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,
     300,   301,   302,   303,   304,   305,    -1,   307,   308,   309,
      -1,   311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,
      27,   341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,
     350,   351,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      87,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,
      -1,    -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,
      -1,    -1,   109,    -1,    -1,   112,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,   125,    -1,
      -1,   128,   129,   130,    -1,   132,   133,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,    -1,    -1,   153,    -1,   155,   156,
     157,   158,   159,   160,   161,    -1,   163,    -1,   165,   166,
     167,   168,    -1,   170,    -1,   172,    -1,    -1,    -1,    -1,
      -1,   178,    -1,   180,   181,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
      -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,
     237,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
      -1,   248,    -1,    -1,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,    -1,   264,    -1,    -1,
      -1,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,
      -1,   278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,
     287,    -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,
      -1,    -1,    -1,   300,   301,   302,   303,   304,   305,    -1,
     307,   308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,
     317,    -1,    -1,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      24,    -1,    -1,    27,   341,   342,    -1,   344,   345,    -1,
      -1,    -1,    -1,   350,   351,    39,    -1,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,
      -1,   125,    -1,    -1,   128,   129,   130,    -1,   132,   133,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,    -1,    -1,   153,
      -1,   155,   156,   157,   158,   159,   160,   161,    -1,   163,
      -1,   165,   166,   167,   168,    -1,   170,    -1,   172,    -1,
      -1,    -1,    -1,    -1,   178,    -1,    -1,   181,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,
      -1,    -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,
      -1,    -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,    -1,
     264,    -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,
     274,    -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,
     284,    -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,
     294,    -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,
     304,   305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,
      -1,    -1,   316,   317,    -1,    -1,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    24,    -1,    -1,    27,   341,   342,    -1,
     344,   345,    -1,    -1,    -1,    -1,   350,   351,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,
      -1,   112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   122,    -1,    -1,   125,    -1,    -1,   128,   129,   130,
      -1,   132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
      -1,    -1,   153,    -1,   155,   156,   157,   158,   159,   160,
     161,    -1,   163,    -1,   165,   166,   167,   168,    -1,   170,
      -1,   172,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,
     181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,    -1,    -1,    -1,    -1,
      -1,    -1,   233,    -1,    -1,    -1,   237,   238,   239,   240,
     241,    -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
     271,    -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,
     281,   282,    -1,   284,    -1,    -1,   287,    -1,   289,    -1,
      -1,    -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,
     301,   302,   303,   304,   305,    -1,   307,   308,   309,    -1,
     311,    -1,    -1,    -1,    -1,   316,   317,    -1,    -1,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    23,    24,    -1,    -1,    27,
     341,   342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,
     351,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,    -1,    87,
      -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,    96,    -1,
      -1,    -1,    -1,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   109,    -1,    -1,   112,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   122,    -1,    -1,   125,    -1,    -1,
     128,   129,   130,    -1,   132,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,    -1,    -1,   153,    -1,   155,   156,   157,
     158,   159,   160,   161,    -1,   163,    -1,   165,   166,   167,
     168,    -1,   170,    -1,   172,    -1,    -1,    -1,    -1,    -1,
     178,    -1,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,    -1,
      -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,   237,
     238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,
     248,    -1,    -1,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,    -1,   264,    -1,    -1,    -1,
      -1,    -1,    -1,   271,    -1,    -1,   274,    -1,    -1,    -1,
     278,    -1,    -1,   281,   282,    -1,   284,    -1,    -1,   287,
      -1,   289,    -1,    -1,    -1,   293,   294,    -1,    -1,    -1,
      -1,    -1,   300,   301,   302,   303,   304,   305,    -1,   307,
     308,   309,    -1,   311,    -1,    -1,    -1,    -1,   316,   317,
      -1,    -1,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    23,    24,
      -1,    -1,    27,   341,   342,    -1,   344,   345,    -1,    -1,
      -1,    -1,   350,   351,    39,    -1,    -1,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    87,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    96,    -1,    -1,    -1,    -1,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,   109,    -1,    -1,   112,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   122,    -1,    -1,
     125,    -1,    -1,   128,   129,   130,    -1,   132,   133,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,    -1,    -1,   153,    -1,
     155,   156,   157,   158,   159,   160,   161,    -1,   163,    -1,
     165,   166,   167,   168,    -1,   170,    -1,   172,    -1,    -1,
      -1,    -1,    -1,   178,    -1,    -1,   181,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,    -1,
      -1,    -1,   237,   238,   239,   240,   241,    -1,    -1,    -1,
      -1,    -1,    -1,   248,    -1,    -1,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,    -1,   264,
      -1,    -1,    -1,    -1,    -1,    -1,   271,    -1,    -1,   274,
      -1,    -1,    -1,   278,    -1,    -1,   281,   282,    -1,   284,
      -1,    -1,   287,    -1,   289,    -1,    -1,    -1,   293,   294,
      -1,    -1,    -1,    -1,    -1,   300,   301,   302,   303,   304,
     305,    -1,   307,   308,   309,    -1,   311,    -1,    -1,    -1,
      -1,   316,   317,    -1,    -1,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    24,    -1,    -1,    27,   341,   342,    -1,   344,
     345,    -1,    -1,    -1,    -1,   350,   351,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    -1,    87,    -1,    -1,    90,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,    -1,    -1,    -1,    -1,    -1,   109,    -1,    -1,
     112,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,    -1,    -1,   125,    -1,    -1,   128,   129,   130,    -1,
     132,   133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     0,     1,    -1,   149,   150,    -1,
      -1,   153,    -1,   155,   156,   157,   158,   159,   160,   161,
      -1,   163,    -1,   165,   166,   167,   168,    -1,   170,    -1,
     172,    -1,    -1,    -1,    -1,    -1,   178,    -1,    -1,   181,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,    81,    82,    83,    84,    -1,
      -1,   233,    -1,    -1,    90,   237,   238,   239,   240,   241,
      -1,    -1,    -1,    -1,    -1,    -1,   248,    -1,    -1,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,   271,
      -1,    -1,   274,    -1,    -1,    -1,   278,    -1,    -1,   281,
     282,    -1,   284,    -1,   140,   287,    -1,   289,    -1,    -1,
      -1,   293,   294,    -1,    -1,    -1,    -1,    -1,   300,   301,
     302,   303,   304,   305,    -1,   307,   308,   309,    -1,   311,
      -1,    -1,    -1,    -1,   316,   317,    -1,    -1,    -1,    -1,
      -1,   177,    -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   341,
     342,    -1,   344,   345,    -1,    -1,    -1,    -1,   350,   351,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   228,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     236,   237,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   249,   250,    -1,   252,    -1,   254,   255,
     256,   257,   258,   259,   260,   261,   262,    -1,    -1,   265,
     266,    -1,    -1,    -1,    -1,    -1,   272,   273,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   288,    -1,    -1,   291,    -1,    -1,    -1,    -1,
      -1,   297,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,    -1,   335
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,    52,    67,    68,    69,    70,    81,    82,    83,
      84,    90,   140,   177,   179,   228,   236,   237,   249,   250,
     252,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     265,   266,   272,   273,   288,   291,   297,   333,   335,   375,
     381,   382,   384,   385,   386,   389,   390,   391,   392,   394,
     398,   399,   408,   413,   425,   430,   431,   438,   489,   496,
     501,   509,   530,   544,   548,   549,   550,   551,   560,   576,
     578,   579,   585,   586,   603,   607,   608,   609,   610,   745,
     747,   752,   140,   120,     7,     8,     9,    10,    11,    23,
      24,    27,    39,    42,    53,    64,    84,    87,    90,    96,
     101,   102,   103,   109,   112,   122,   125,   128,   129,   130,
     132,   133,   149,   150,   153,   155,   156,   157,   158,   159,
     160,   161,   163,   165,   166,   167,   168,   170,   172,   178,
     181,   225,   226,   233,   237,   238,   239,   240,   241,   248,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   264,   271,   274,   278,   281,   282,   284,   287,
     289,   293,   294,   300,   301,   302,   303,   304,   305,   307,
     308,   309,   311,   316,   317,   341,   342,   344,   345,   350,
     351,   709,   734,   735,   736,   184,   264,   594,   276,    85,
     556,   556,   735,    83,   604,   605,   735,    69,   610,   276,
     194,   279,    70,    73,    74,   678,   679,   680,   735,   709,
     378,   377,   379,   380,   293,   709,     7,     8,     9,    10,
      11,    67,    68,    69,    70,   184,   266,   286,   335,   382,
     409,   416,   417,   418,   420,   421,   422,   731,   732,   733,
     272,   275,   414,   415,    59,    91,    56,   124,   287,   293,
     179,   588,    12,    28,   179,   244,   319,   490,   491,   568,
     603,   609,   722,   737,     0,   376,    12,   723,   739,   748,
     381,   383,    18,    56,    59,   107,   109,   124,   225,   226,
     227,   228,   229,   230,   241,   274,   287,   293,   296,   439,
     440,   443,   456,   172,   242,   243,   244,   245,   298,   346,
     367,   499,    56,   124,   184,   241,   274,   287,   293,   298,
     343,   346,   499,    56,    57,    58,    63,    64,    65,    66,
     179,   274,   287,   301,   495,   703,   704,   705,   706,   711,
     735,   225,   226,   293,   395,   396,   443,   711,   140,    91,
     106,   173,   174,   175,   634,   140,   140,   709,   112,   740,
     345,   686,   735,   369,     3,     4,     5,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    19,    20,    28,
      29,    45,    46,    47,    48,    49,    50,    51,    63,    65,
      66,   110,   117,   118,   123,   131,   142,   143,   144,   145,
     147,   148,   151,   152,   154,   164,   171,   179,   182,   198,
     199,   208,   209,   210,   211,   215,   300,   301,   302,   303,
     322,   326,   327,   371,   373,   591,   613,   632,   633,   643,
     644,   646,   647,   649,   651,   652,   654,   656,   657,   659,
     660,   661,   663,   664,   678,   679,   681,   683,   684,   685,
     687,   688,   689,   703,   707,   708,   710,   712,   713,   726,
     729,   735,   738,   741,   742,   743,   744,   757,   758,   759,
     760,   761,   775,   782,   784,   787,   797,   798,   828,   709,
     196,   557,   557,   735,   368,   576,   579,   585,   586,   606,
     608,   609,   179,   493,   494,   594,   180,   709,   344,   124,
     287,   293,   294,   298,   343,   499,   543,   753,   179,   369,
     493,   392,   392,   375,   375,   709,   126,   127,   577,   740,
     493,   493,   284,   493,   120,   276,   295,   368,   295,   368,
     279,   368,   280,   280,   416,   409,    91,    92,    95,   101,
     552,   553,   554,   288,   735,   709,   328,   387,   387,   263,
     589,   592,   632,   679,   735,   368,   276,   490,   610,   276,
     722,   276,   276,   319,   336,   392,   179,   184,   723,   746,
     225,   226,   735,   225,   226,   709,   293,   293,   293,   293,
     709,   735,   328,   388,   388,   343,   293,   243,   243,   243,
     709,   709,   243,   709,   735,   709,   499,   709,   735,   387,
     387,   387,   709,   387,   387,   233,   395,   317,   183,   183,
     397,   397,   397,   397,   183,   369,     7,     8,     9,    10,
      21,    25,    26,    27,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    53,    54,    55,   300,   301,   302,   303,
     368,   694,   702,   724,   726,   727,   728,   729,   738,   368,
     552,   108,   184,   264,   611,   611,   611,   318,   635,   686,
     744,   735,   288,   735,   743,   743,   743,   740,   744,   179,
     179,    23,   179,   682,   682,   682,   682,   682,   179,   659,
     179,   179,   132,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   603,   610,   632,   644,   653,
     644,   179,   661,   661,   179,   179,   179,   661,   744,   179,
     692,   179,   693,   198,   199,   690,   323,   632,   717,   718,
     179,   179,   644,   655,   120,   276,   614,   618,   194,   686,
     196,   183,   186,   187,   188,   189,   190,   191,   192,   193,
     197,   277,   709,   141,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   211,   212,   213,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   369,   179,   368,
     179,   356,   662,   744,   744,   369,   744,   740,   179,   263,
     491,   494,   587,    86,    87,   295,   558,   605,   487,   735,
     345,   613,   686,   709,   735,   709,   735,   709,   709,   709,
     277,   180,   632,   667,   680,   735,   320,   637,   140,   140,
     577,   136,   136,    43,    44,   547,   285,   423,   424,   731,
     731,   423,   418,   172,   293,   419,   543,   709,   422,   121,
     121,   120,   120,   552,    93,    94,    96,   102,   368,   269,
     270,   441,   177,   268,   288,   426,    87,   125,   126,   128,
     129,   130,   133,   345,   434,   436,   437,   110,   735,   709,
     180,   368,   179,   369,   179,   709,   180,   709,   339,   744,
     709,   722,   319,   140,   180,   590,   593,   610,   632,   177,
      90,   345,   432,   433,   435,   437,   388,   388,   388,   388,
     247,   177,   406,   182,   233,   400,   735,   709,   735,   388,
     493,   348,   349,   531,   179,   709,   547,   709,   709,   709,
     709,   709,   397,   180,   659,   735,     9,    59,   300,   301,
     302,   303,   707,   735,   735,   632,   735,   740,   179,    22,
      23,   179,   179,   179,    39,   179,   692,   693,   306,   310,
     312,   313,   314,   315,   695,   698,   700,   701,   711,   179,
     179,   179,   179,   179,   395,   632,   639,   640,   176,   612,
     612,   612,   664,   721,   737,   319,   636,   299,   597,   494,
     595,   596,   730,   735,   369,   632,   632,    24,   180,   628,
     710,   735,   304,   305,   307,   308,   309,   311,   315,   316,
     695,   696,   697,   121,   661,   663,   661,   754,   755,   756,
     754,   248,   162,   776,   802,   159,   161,   800,   248,     3,
     788,   663,   124,   799,   800,   754,   610,   180,   180,   180,
     180,   368,   661,   661,   661,   739,   177,   691,   739,   691,
     744,   632,   323,   715,   716,   325,   717,   719,   632,   632,
     714,   368,   372,    72,   179,   598,   619,   620,   658,   678,
     709,   735,   395,   367,   617,   633,   644,   184,   185,   195,
     645,   104,   105,   648,   648,   179,   179,   650,   661,   650,
     650,   650,   645,   117,   182,   656,   661,   661,   661,   661,
     661,   661,   661,   661,   661,   661,   661,   661,   661,   661,
     661,   661,   661,   661,   661,   661,   661,   661,   661,   661,
     211,   180,   184,   211,   264,   667,   735,   685,   180,   184,
     264,   667,   179,   735,    11,   211,   735,   297,   587,    86,
      83,   180,   368,   179,   658,    17,   369,   179,   545,   117,
     744,   180,   368,    15,   664,   722,   253,   393,   547,   177,
     368,   411,   177,   410,   709,   423,   423,    92,    99,   100,
     555,   739,   554,   271,   441,   295,   287,   128,   129,   130,
     108,   177,   690,   690,   721,   724,   436,   268,   265,   268,
     288,   291,   292,   592,   180,   667,   589,   493,   120,    17,
     566,   567,   279,   559,   493,   336,   722,   180,   368,   441,
     177,   724,   435,   709,   709,   709,   709,   248,   275,   110,
     401,   735,   263,   402,   233,   120,   179,   458,   459,   493,
     279,   709,   345,    67,    68,    70,   266,   532,   211,   528,
     529,   735,   547,   547,   547,   547,   545,   735,   720,   739,
      24,   720,   720,   720,   739,    54,   725,   744,   691,   691,
     693,   692,   295,   720,   739,   720,   720,   720,   720,   724,
     231,   232,   641,   368,   108,   610,   610,   610,   664,   722,
     637,   632,   183,   368,   618,   183,   735,   345,   368,   180,
     368,   369,   120,   709,   165,   801,   368,   801,   801,   735,
     763,   179,   661,   777,   778,   779,   368,   663,   735,   785,
     153,   789,   801,   754,   634,   180,   188,   189,   644,   120,
     368,   189,   368,   180,   301,   744,   180,   744,   701,   324,
     632,   715,   719,   632,   334,   368,   368,   180,   368,   644,
     659,   678,   179,   598,   603,   609,   620,   368,    73,    74,
      75,    77,    78,    80,   599,   601,   345,   621,   735,   621,
     622,   622,   369,   614,   615,   616,   735,   597,   644,   644,
     644,   590,   590,   111,   644,   117,   667,   180,   667,   180,
     369,   667,   667,   180,   665,   666,   735,   369,   735,   735,
     620,   735,   180,   546,   724,   632,   275,   424,   120,   412,
     272,   412,   412,   412,    97,    98,    92,   744,   271,   735,
     735,   690,   659,   690,   737,   737,   295,   235,   293,   294,
     428,   429,   295,   429,    70,    92,   287,   293,   427,   429,
     293,   429,   180,   180,   120,   678,   117,   569,   337,   341,
     342,   566,   120,   593,   271,   690,   458,   458,   458,   458,
     735,    57,    63,   407,    21,   282,   749,   750,   401,   244,
     191,   235,   461,   462,   463,   465,   468,   476,   477,   488,
     730,   735,   103,   442,   345,   709,   458,   490,   347,   279,
     180,   368,   724,   547,   180,   180,   180,   368,   180,   368,
     180,   368,   315,   695,   699,   180,   368,   180,   180,   180,
     180,   238,   642,   640,   179,   321,   638,   659,   596,   597,
     592,   724,   724,   710,   735,   661,   124,   161,   180,   754,
     180,   180,   368,   762,    87,   263,   661,   803,   804,   806,
     807,   808,   280,   368,   773,   345,   780,    88,   149,   783,
     368,   786,   108,   790,   810,   801,   180,   168,   811,   812,
     801,   179,   179,   661,   661,   661,   661,   317,   632,   324,
     334,   632,   632,   632,   621,   622,   180,   180,   180,   620,
     599,    79,    79,    76,   600,   735,   179,   735,   368,   345,
     114,   623,   196,   196,   180,   180,   744,   180,   180,   211,
     180,   180,   180,   357,   668,   735,   279,   369,   180,   368,
     280,   407,   280,    17,   744,   737,   737,   735,   735,   709,
     735,   735,   735,    94,    93,    94,   735,   709,   735,   709,
     462,   179,   574,   575,   744,   345,   536,   744,   569,   338,
     574,   744,   737,   357,   447,   279,   288,   487,   751,   385,
     389,   403,   404,   405,   408,   413,   425,   430,   544,   678,
     709,   735,   180,   368,   267,   283,   296,   485,   137,   138,
     464,   724,   177,   735,   490,   179,   279,   457,   177,   492,
     487,   709,   246,   500,   735,   723,   739,   739,   693,   739,
     239,   240,   628,   664,   739,   180,   180,   180,   146,   661,
     764,   770,   771,   772,   802,   801,   263,   806,   180,   368,
     345,   117,   155,   157,   158,   774,   778,   801,   735,   781,
     150,   150,   180,   663,   801,   132,   156,   663,   791,   792,
     793,   794,   795,   810,   295,   180,   180,   590,   590,   121,
     180,   180,   368,   180,   368,   632,   180,    79,   620,   620,
     179,   487,   615,   179,   108,   113,   631,   644,   644,   180,
     108,   106,   669,   632,   735,   546,   353,   288,   547,   547,
     547,   295,   345,   454,   265,   288,   454,   575,   559,   368,
     744,   368,   179,   563,   563,   248,   108,   744,   735,   405,
     463,   735,   278,   278,   494,   134,   139,   263,   466,   467,
     470,   471,   473,   474,   477,   281,   744,   177,   460,   487,
      81,   234,   355,   533,   293,   527,   724,    69,    84,    90,
     247,   250,   251,   290,   322,   328,   333,   394,   398,   399,
     408,   413,   425,   430,   502,   505,   507,   508,   509,   513,
     515,   521,   523,   524,   544,   548,   549,   608,   735,   724,
     180,   180,   180,   180,   180,   179,   368,   368,   773,   368,
     180,   804,   735,   805,   279,   279,   279,   279,   180,   180,
     345,   809,   810,   368,   117,   158,   796,   169,   180,   180,
     661,   661,   661,   620,    17,   279,   602,   487,   180,   665,
     115,   116,   118,   179,   624,   625,   632,   632,   667,   108,
      89,   364,   366,   670,   671,   323,   583,   584,   271,   287,
     735,   357,   263,   103,   117,   182,   263,   180,    87,   573,
     744,   744,   564,   565,   735,   566,   559,   744,   297,   364,
     444,   177,   455,   494,   494,   135,   472,   632,   470,   117,
     182,   234,   283,   286,   296,   484,   486,   179,    87,   178,
     180,    67,    88,   265,   280,   352,   353,   534,   535,   121,
     538,   539,   179,   594,   248,   510,   511,   709,     7,   293,
     491,   514,   632,   323,   518,   519,   632,   632,   332,   503,
     330,   370,   661,   765,   766,   768,   770,   772,   764,   770,
     117,    87,   117,   117,   117,   735,   792,   279,   279,   180,
      87,   167,   170,   813,   814,   819,   180,   180,   180,   494,
     632,   180,   180,   179,   179,   119,   180,   368,   639,   187,
     358,   365,   632,   672,   673,   675,    71,   182,   583,   744,
     735,   120,   121,   189,   453,   117,   744,   117,   472,   235,
     368,   180,   368,   744,    87,   111,   570,   566,   287,    17,
     279,   446,    56,   441,   286,   345,   117,   179,   278,   709,
     469,   470,   178,    89,    89,   293,   350,   537,   293,   537,
     535,   354,   323,   541,   526,   730,   613,   497,   735,   179,
       6,   498,   744,   179,   632,   325,   518,   520,   323,   516,
     517,   324,   503,   505,   632,   180,   368,   345,   767,   368,
     161,   809,   158,   158,   163,   735,   820,     3,   815,   816,
      87,   160,   163,   821,   822,   824,   825,   179,   626,   627,
     710,   626,   179,   625,   365,   632,   673,   674,   676,   350,
     361,   361,   359,   677,   196,   580,    71,   364,   449,   632,
     117,   179,   744,   565,   111,   569,   570,   735,   179,   179,
     744,   271,   709,   136,   632,   493,   180,   368,   536,   536,
     536,   536,   350,   351,   540,   179,   333,   394,   398,   408,
     413,   506,   507,   542,   548,   549,   608,   180,   368,   724,
     369,   512,   632,   491,   324,   503,   334,   632,   516,   520,
     503,   505,   140,   331,   766,   735,   769,   770,   166,   817,
     817,   163,   735,   827,   816,   826,   823,   824,   628,   180,
     368,   180,   115,   116,   118,   179,   627,   629,   630,   360,
     360,   196,    87,   114,   358,   363,   632,   324,   580,   129,
     295,   297,   448,   451,   632,    60,   571,   569,   445,   632,
     735,   441,   744,   493,   179,   475,   180,   122,   483,   470,
     735,   735,   735,   735,   632,   332,   730,   735,   180,   368,
     180,   503,   505,   322,   324,   334,   325,   329,   522,   140,
     334,   503,   816,   818,   180,   627,   179,   179,   119,   180,
     180,   368,   674,   362,   350,    67,    68,   581,   324,   364,
     450,   632,   180,   368,    61,   572,   571,   180,   180,   271,
     483,   433,    40,    41,    75,   482,   279,   479,   480,   481,
     180,   504,   724,   632,   140,   503,   322,   503,   632,   334,
     334,   334,   626,   626,   179,   630,   288,    70,   582,   128,
     177,   452,   452,   448,    62,   573,   572,   744,   481,   180,
      67,    68,   279,   480,   279,   479,   334,   506,   324,   328,
     330,   180,   180,   629,   595,   493,   117,   573,    43,    44,
      87,   288,   478,   478,   140,   503,   525,   735,   180,   587,
     297,   340,   561,    42,   117,   263,   522,   179,   562,   722,
     180,   368,   722
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   374,   375,   376,   375,   377,   375,   378,   375,   379,
     375,   380,   375,   375,   375,   375,   375,   375,   375,   381,
     381,   382,   382,   383,   383,   384,   385,   386,   386,   387,
     387,   388,   388,   389,   390,   391,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   393,   393,   394,
     394,   395,   395,   396,   396,   397,   397,   398,   398,   398,
     398,   398,   398,   398,   398,   399,   399,   400,   400,   400,
     401,   402,   402,   403,   403,   404,   404,   405,   405,   405,
     405,   405,   406,   406,   407,   407,   408,   408,   409,   409,
     410,   410,   411,   411,   412,   412,   413,   413,   414,   414,
     415,   415,   416,   416,   417,   417,   418,   418,   419,   419,
     419,   420,   420,   420,   421,   421,   422,   422,   422,   422,
     422,   422,   422,   423,   423,   424,   424,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   426,   426,   426,   427,   427,   427,   427,   427,
     427,   428,   428,   428,   429,   429,   430,   430,   430,   430,
     430,   430,   430,   430,   431,   431,   431,   432,   432,   433,
     433,   434,   434,   435,   435,   435,   436,   436,   436,   436,
     436,   437,   437,   437,   437,   437,   437,   437,   437,   438,
     439,   439,   439,   439,   440,   440,   441,   441,   441,   442,
     442,   443,   443,   443,   443,   443,   443,   443,   444,   444,
     445,   446,   446,   447,   447,   448,   449,   449,   450,   450,
     451,   451,   452,   452,   453,   453,   453,   454,   454,   455,
     455,   455,   456,   456,   456,   456,   456,   456,   457,   457,
     457,   457,   458,   458,   459,   460,   460,   460,   461,   461,
     462,   462,   463,   463,   463,   464,   464,   465,   465,   466,
     466,   467,   467,   468,   469,   469,   470,   470,   470,   471,
     472,   473,   474,   474,   475,   475,   476,   477,   477,   478,
     478,   478,   478,   478,   479,   480,   481,   481,   481,   481,
     481,   482,   482,   482,   482,   483,   483,   484,   484,   484,
     484,   484,   484,   485,   485,   485,   486,   487,   487,   488,
     489,   490,   490,   491,   491,   492,   492,   493,   493,   494,
     495,   496,   497,   498,   498,   499,   499,   499,   499,   499,
     499,   499,   499,   499,   499,   500,   500,   501,   501,   501,
     502,   502,   502,   503,   503,   504,   504,   505,   505,   505,
     505,   505,   505,   505,   505,   505,   505,   505,   505,   506,
     506,   506,   506,   506,   506,   506,   506,   507,   507,   507,
     507,   507,   507,   508,   509,   510,   511,   512,   512,   512,
     513,   514,   514,   514,   515,   515,   516,   517,   517,   518,
     519,   519,   520,   520,   521,   522,   522,   522,   523,   524,
     524,   525,   525,   526,   526,   527,   527,   528,   528,   528,
     529,   529,   530,   531,   531,   532,   532,   532,   532,   532,
     533,   533,   534,   534,   535,   535,   535,   535,   536,   536,
     537,   537,   538,   539,   539,   540,   540,   541,   541,   542,
     542,   543,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   545,   545,   545,   546,   546,   547,   547,   547,   392,
     392,   548,   548,   548,   548,   548,   548,   549,   550,   550,
     551,   551,   551,   551,   551,   551,   551,   552,   552,   553,
     553,   554,   554,   554,   554,   555,   555,   555,   555,   556,
     556,   557,   557,   557,   558,   558,   559,   559,   559,   560,
     560,   560,   560,   560,   560,   561,   561,   562,   562,   563,
     563,   564,   564,   565,   565,   566,   566,   566,   566,   567,
     567,   568,   568,   568,   568,   568,   569,   569,   570,   570,
     570,   571,   571,   572,   572,   573,   573,   574,   574,   575,
     575,   576,   577,   577,   577,   578,   578,   579,   580,   580,
     581,   581,   582,   583,   583,   584,   584,   585,   586,   586,
     587,   587,   587,   588,   588,   589,   589,   590,   590,   591,
     592,   592,   593,   593,   594,   594,   594,   595,   595,   596,
     596,   597,   597,   598,   598,   598,   598,   599,   599,   599,
     600,   600,   601,   601,   601,   602,   602,   392,   603,   604,
     604,   605,   606,   606,   606,   606,   606,   606,   392,   392,
     607,   608,   609,   610,   610,   610,   610,   610,   610,   611,
     611,   611,   612,   612,   612,   613,   614,   615,   616,   616,
     617,   617,   618,   618,   619,   619,   620,   620,   620,   620,
     620,   620,   620,   621,   621,   621,   621,   622,   622,   623,
     623,   624,   624,   625,   625,   625,   625,   625,   626,   626,
     627,   627,   628,   628,   629,   629,   630,   630,   630,   630,
     630,   631,   631,   632,   632,   633,   633,   634,   634,   635,
     635,   635,   636,   636,   636,   637,   637,   637,   637,   638,
     638,   638,   639,   639,   640,   641,   641,   641,   642,   642,
     642,   643,   643,   643,   643,   643,   643,   643,   643,   644,
     644,   645,   645,   645,   645,   646,   646,   647,   647,   648,
     648,   648,   649,   649,   649,   649,   650,   650,   651,   651,
     652,   652,   652,   652,   653,   653,   654,   655,   655,   656,
     657,   658,   658,   659,   659,   660,   660,   660,   660,   660,
     660,   660,   660,   660,   660,   660,   660,   660,   660,   660,
     660,   660,   660,   660,   660,   660,   660,   660,   660,   660,
     660,   660,   660,   661,   661,   662,   662,   662,   663,   663,
     663,   663,   663,   663,   663,   663,   663,   663,   663,   663,
     663,   663,   663,   663,   664,   665,   666,   666,   667,   667,
     668,   668,   669,   669,   670,   670,   671,   671,   671,   672,
     672,   673,   673,   673,   674,   674,   675,   676,   676,   677,
     677,   677,   677,   677,   678,   678,   679,   679,   680,   680,
     680,   680,   681,   681,   681,   681,   681,   681,   682,   682,
     683,   683,   683,   683,   683,   683,   683,   684,   684,   685,
     685,   685,   685,   686,   686,   686,   687,   688,   688,   689,
     689,   689,   689,   689,   689,   689,   689,   689,   689,   689,
     690,   690,   690,   691,   691,   692,   692,   693,   693,   694,
     694,   694,   695,   695,   695,   695,   695,   696,   696,   697,
     697,   697,   697,   697,   697,   697,   697,   698,   699,   699,
     700,   700,   701,   701,   702,   703,   703,   703,   704,   704,
     705,   705,   706,   706,   707,   707,   707,   707,   707,   707,
     707,   707,   707,   707,   707,   707,   707,   707,   707,   707,
     707,   708,   709,   709,   709,   710,   710,   710,   711,   711,
     712,   712,   713,   713,   713,   713,   714,   714,   715,   716,
     716,   717,   718,   718,   719,   719,   720,   721,   722,   723,
     724,   724,   724,   724,   724,   724,   724,   724,   724,   724,
     724,   724,   724,   724,   724,   724,   724,   724,   724,   724,
     724,   724,   724,   724,   724,   724,   724,   724,   724,   724,
     724,   724,   724,   724,   724,   724,   725,   725,   726,   727,
     727,   728,   728,   728,   729,   729,   730,   731,   732,   732,
     732,   732,   732,   733,   734,   734,   734,   734,   734,   734,
     734,   735,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   736,   736,   736,   736,   736,   736,   736,
     736,   736,   736,   737,   738,   738,   739,   740,   740,   741,
     741,   742,   742,   743,   743,   744,   744,   745,   746,   746,
     747,   748,   748,   749,   749,   750,   751,   752,   752,   753,
     753,   753,   753,   753,   753,   753,   753,   754,   755,   755,
     756,   757,   757,   757,   757,   757,   757,   757,   757,   757,
     757,   758,   759,   760,   761,   762,   762,   762,   762,   762,
     762,   762,   762,   763,   764,   765,   765,   766,   767,   767,
     768,   769,   770,   771,   771,   772,   773,   773,   774,   774,
     774,   774,   774,   775,   776,   776,   777,   777,   778,   779,
     780,   780,   781,   782,   783,   783,   784,   785,   786,   786,
     787,   788,   789,   789,   790,   791,   791,   792,   792,   793,
     794,   795,   795,   796,   796,   797,   798,   799,   799,   800,
     800,   801,   801,   801,   802,   803,   803,   804,   804,   805,
     806,   807,   808,   808,   809,   809,   810,   810,   811,   811,
     812,   813,   813,   814,   814,   815,   816,   817,   817,   818,
     819,   820,   821,   821,   822,   822,   823,   823,   824,   825,
     825,   826,   827,   828
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     4,     0,     4,     0,     4,     0,
       3,     0,     3,     2,     2,     0,     1,     2,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     1,     3,     0,
       2,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     1,     1,     0,     1,     2,
       2,     1,     3,     2,     4,     1,     0,     4,     4,     5,
       4,     4,     4,     4,     4,     7,     5,     1,     2,     3,
       1,     0,     4,     0,     1,     1,     2,     1,     1,     1,
       1,     1,     0,     3,     1,     1,     6,     6,     1,     3,
       0,     3,     0,     3,     0,     2,     6,     6,     0,     3,
       0,     3,     1,     3,     1,     3,     2,     2,     2,     1,
       1,     2,     1,     1,     1,     3,     1,     1,     1,     2,
       2,     2,     1,     1,     3,     1,     1,     7,     8,     6,
       6,     7,     7,     7,     8,     7,     9,     7,     4,     6,
      10,     7,     4,     3,     7,     5,     4,     5,     4,     5,
       5,     3,     3,     3,     1,     0,     2,     2,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     1,     0,     1,
       2,     1,     2,     2,     4,     1,     2,     1,     4,     3,
       1,     4,     3,     2,     3,     2,     2,     1,     2,     9,
       1,     1,     1,     0,     3,    10,     0,     1,     1,     0,
       3,     5,     6,     5,     6,     5,     8,     6,     1,     1,
       1,     4,     4,     0,     4,     1,     1,     2,     1,     2,
       1,     3,     0,     3,     5,     5,     3,     0,     3,     0,
       6,     4,     1,     1,     2,     2,     2,     2,     0,     4,
       4,     3,     3,     1,     4,     0,     3,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     0,
       1,     1,     2,     6,     1,     3,     1,     1,     1,     2,
       1,     2,     5,     1,     0,     3,     2,     0,     2,     2,
       1,     1,     2,     2,     3,     3,     0,     1,     1,     2,
       2,     0,     1,     1,     1,     0,     2,     2,     1,     1,
       2,     5,     1,     2,     3,     8,     4,     1,     3,     2,
       7,     1,     3,     1,     1,     0,     3,     0,     1,     3,
       3,     6,     3,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     1,     2,     2,     0,    10,     8,    10,
       1,     5,     6,     0,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     4,     1,     0,     1,     3,
       2,     1,     1,     4,     6,     5,     4,     1,     2,     4,
       1,     2,     0,     2,     7,     0,     2,     5,     8,     0,
       2,     0,     1,     2,     4,     4,     1,     1,     1,     0,
       4,     2,     9,     1,     1,     1,     1,     1,     1,     3,
       0,     2,     1,     2,     4,     4,     4,     4,     0,     1,
       0,     1,     3,     0,     3,     1,     1,     0,     4,     1,
       4,     3,     5,     6,     5,     5,     4,     3,     3,     3,
       4,     0,     3,     2,     1,     3,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     3,     4,     3,     4,     3,     0,     1,     1,
       3,     2,     2,     3,     3,     2,     2,     2,     1,     1,
       0,     2,     3,     0,     0,     3,     0,     2,     2,    16,
      14,     6,     9,     7,     6,     0,     4,     1,     3,     0,
       3,     1,     3,     1,     2,     0,     3,     5,     7,     0,
       1,     0,     2,     2,     4,     4,     0,     3,     0,     1,
       2,     0,     1,     0,     2,     0,     2,     1,     3,     1,
       3,     5,     0,     2,     2,     5,     4,     7,     0,     2,
       3,     1,     3,     5,     6,     1,     2,     9,     4,     5,
       0,     2,     1,     3,     5,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     3,     3,
       3,     0,     2,     3,     4,     5,     5,     0,     1,     2,
       0,     1,     1,     1,     1,     2,     2,     1,     3,     3,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     6,     6,     5,     5,     5,     2,     3,     1,     0,
       1,     1,     0,     1,     5,     1,     5,     5,     1,     3,
       0,     2,     0,     2,     1,     3,     2,     2,     3,     2,
       3,     1,     1,     5,     2,     4,     1,     0,     1,     0,
       3,     1,     3,     1,     4,     4,     5,     2,     1,     3,
       3,     1,     1,     3,     1,     3,     1,     4,     4,     5,
       2,     0,     2,     3,     1,     3,     1,     0,     3,     0,
       2,     2,     0,     2,     2,     0,     2,     2,     2,     0,
       2,     2,     1,     3,     3,     0,     1,     1,     0,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     0,     1,     1,     1,     4,     4,     6,     6,     0,
       1,     1,     3,     3,     3,     3,     1,     3,     4,     3,
       5,     5,     7,     7,     1,     3,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       2,     2,     3,     1,     1,     4,     2,     0,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       1,     1,     1,     1,     1,     4,     0,     1,     1,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     1,     1,
       1,     2,     2,     2,     1,     1,     4,     2,     2,     0,
       3,     2,     2,     3,     3,     4,     1,     3,     1,     1,
       1,     1,     6,     2,     2,     2,     2,     2,     0,     2,
       8,     8,     6,     6,     6,     3,     8,     1,     3,     1,
       3,     3,     2,     0,     2,     1,     1,     1,     3,     3,
       4,     5,     5,     4,     6,     3,     4,     5,     5,     1,
       1,     1,     0,     3,     0,     3,     0,     3,     0,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       2,     2,     3,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     4,     4,     1,     2,     1,     2,     2,     2,     1,
       1,     4,     1,     3,     5,     1,     3,     5,     1,     3,
       6,     6,     6,     4,     5,     4,     3,     3,     4,     1,
       2,     4,     1,     2,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     4,     1,     4,     1,     1,
       1,     1,     1,     1,     4,     6,     1,     4,     6,     1,
       2,     1,     1,     1,     1,     4,     1,     4,     6,     1,
       4,     1,     4,     6,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     3,     1,     3,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     0,     2,     1,
       2,     1,     2,     1,     2,     1,     2,     2,     1,     1,
       3,     3,     4,     0,     1,     2,     1,     5,     5,     2,
       2,     2,     4,     6,     2,     2,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     5,     7,     0,     2,     4,     6,     4,
       2,     4,     2,     1,     4,     1,     3,     2,     0,     2,
       1,     1,     2,     1,     3,     1,     0,     2,     3,     3,
       3,     3,     4,     7,     0,     2,     1,     3,     2,     1,
       0,     2,     1,     6,     2,     2,     7,     1,     0,     2,
       8,     1,     0,     3,     1,     1,     3,     1,     1,     2,
       4,     0,     1,     3,     3,     5,     6,     1,     1,     1,
       1,     0,     2,     2,     4,     1,     3,     1,     1,     1,
       1,     3,     2,     2,     0,     1,     2,     2,     0,     1,
       5,     1,     1,     3,     3,     1,     1,     0,     2,     1,
       2,     1,     0,     1,     1,     2,     0,     1,     2,     2,
       2,     1,     1,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (m, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, m); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, mvc *m)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (m);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, mvc *m)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, m);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, mvc *m)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , m);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, m); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, mvc *m)
{
  YYUSE (yyvaluep);
  YYUSE (m);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (mvc *m)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, m);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 717 "sql_parser.y" /* yacc.c:1646  */
    {
		if (m->sym) {
			append_symbol(m->sym->data.lval, (yyval.sym));
			(yyval.sym) = m->sym;
		} else {
			m->sym = (yyval.sym) = (yyvsp[-1].sym);
		}
		YYACCEPT;
	}
#line 7483 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 727 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emode = m_prepare; 
			  m->scanner.as = m->scanner.yycur; 
			}
#line 7492 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 731 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 7506 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 740 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emode = m_plan;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 7515 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 744 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 7529 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 754 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emod |= mod_explain;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 7538 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 758 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->sym) {
				append_symbol(m->sym->data.lval, (yyvsp[-1].sym));
				(yyval.sym) = m->sym;
			  } else {
				m->sym = (yyval.sym) = (yyvsp[-1].sym);
			  }
			  YYACCEPT;
			}
#line 7552 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 768 "sql_parser.y" /* yacc.c:1646  */
    {
			  if (m->scanner.mode == LINE_1) {
				yyerror(m, "SQL debugging only supported in interactive mode");
				YYABORT;
			  }
		  	  m->emod |= mod_debug;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 7565 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 776 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); YYACCEPT; }
#line 7571 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 777 "sql_parser.y" /* yacc.c:1646  */
    {
		  	  m->emod |= mod_trace;
			  m->scanner.as = m->scanner.yycur; 
			}
#line 7580 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 781 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); YYACCEPT; }
#line 7586 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 782 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = (yyvsp[-1].sym); YYACCEPT; }
#line 7592 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 783 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = (yyvsp[-1].sym); YYACCEPT; }
#line 7598 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 784 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 7604 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 785 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 7610 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 786 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYACCEPT; }
#line 7616 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 787 "sql_parser.y" /* yacc.c:1646  */
    { m->sym = (yyval.sym) = NULL; YYABORT; }
#line 7622 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 810 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 7628 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 814 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 7634 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 818 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 7640 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 819 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 7646 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 823 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 7652 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 824 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 7658 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 847 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-3].l));
		append_list(l, (yyvsp[-2].l));
		append_symbol(l, (yyvsp[-1].sym));
		append_int(l, (yyvsp[0].i_val));
		(yyval.sym) = _symbol_create_list( SQL_ANALYZE, l); }
#line 7669 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 858 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 7675 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 859 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 7681 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 863 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_DECLARE, (yyvsp[0].l)); }
#line 7687 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 864 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); if ((yyval.sym)) (yyval.sym)->token = SQL_DECLARE_TABLE; }
#line 7693 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 868 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 7699 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 869 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list( (yyvsp[-2].l), (yyvsp[0].l) ); }
#line 7705 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 874 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-1].l) );
		append_type(l, &(yyvsp[0].type) );
		(yyval.l) = append_symbol(L(), _symbol_create_list( SQL_DECLARE, l)); }
#line 7714 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 879 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-1].l) );
		append_type(l, &(yyvsp[0].type) );
		(yyval.l) = append_symbol((yyvsp[-3].l), _symbol_create_list( SQL_DECLARE, l)); }
#line 7723 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 892 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-2].l) );
		append_symbol(l, (yyvsp[0].sym) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 7732 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 897 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  	append_list(l, (yyvsp[-2].l));
	  	append_symbol(l, (yyvsp[0].sym));
	  	(yyval.sym) = _symbol_create_list( SQL_SET, l ); }
#line 7741 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 902 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_user")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 7752 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 909 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_schema")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 7763 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 916 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0 );
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_user")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 7774 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 923 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "char", UTF8_strlen((yyvsp[0].sval)), 0);
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_role")));
		append_symbol(l, _newAtomNode( _atom_string(&t, (yyvsp[0].sval))) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 7785 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 930 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  sql_subtype t;
		sql_find_subtype(&t, "sec_interval", inttype2digits(ihour, isec), 0);
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_timezone")));
		append_symbol(l, _newAtomNode(atom_int(SA, &t, 0)));
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 7796 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 937 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_timezone")));
		append_symbol(l, (yyvsp[0].sym) );
		(yyval.sym) = _symbol_create_list( SQL_SET, l); }
#line 7805 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 946 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-3].l));
		append_symbol(l, (yyvsp[-2].sym));
		append_symbol(l, (yyvsp[-1].sym));
		append_list(l, (yyvsp[0].l));
		append_int(l, (yyvsp[-4].bval));
		(yyval.sym) = _symbol_create_list( SQL_CREATE_SCHEMA, l); }
#line 7817 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 954 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_int(l, (yyvsp[0].i_val));
		append_int(l, (yyvsp[-2].bval));
		(yyval.sym) = _symbol_create_list( SQL_DROP_SCHEMA, l); }
#line 7827 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 963 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_string((yyval.l), (yyvsp[0].sval) );
	  append_string((yyval.l), NULL ); }
#line 7835 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 967 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_string((yyval.l), NULL );
	  append_string((yyval.l), (yyvsp[0].sval) ); }
#line 7843 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 971 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_string((yyval.l), (yyvsp[-2].sval) );
	  append_string((yyval.l), (yyvsp[0].sval) ); }
#line 7851 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 980 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 7857 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 981 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_CHARSET, (yyvsp[0].sval) ); }
#line 7863 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 985 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 7869 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 990 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 7875 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 992 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym) ); }
#line 7881 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 998 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_user; }
#line 7887 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 999 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 7893 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1003 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_user; }
#line 7899 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1004 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_role; }
#line 7905 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1009 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_GRANT, l);
	}
#line 7917 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1019 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_GRANT_ROLES, l); }
#line 7928 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1028 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 7934 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1030 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 7940 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1034 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 7946 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1035 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 7952 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1039 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 7958 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1040 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 7964 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1045 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = cur_user; }
#line 7970 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1046 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 7976 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1051 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[-4].bval)); /* GRANT OPTION FOR */
	  append_int(l, 0);
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_REVOKE, l); }
#line 7988 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1059 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  append_int(l, (yyvsp[-4].bval));
	  append_int(l, (yyvsp[0].i_val));
	(yyval.sym) = _symbol_create_list( SQL_REVOKE_ROLES, l); }
#line 7999 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1068 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 8005 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1069 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 8011 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1073 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 8017 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1074 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 8023 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1079 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_list((yyval.l), (yyvsp[0].l));
	  append_symbol((yyval.l), _symbol_create(SQL_GRANT, NULL)); }
#line 8031 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1083 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_list((yyval.l), (yyvsp[-2].l));
	  append_symbol((yyval.l), (yyvsp[0].sym)); }
#line 8039 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1089 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(L(), (yyvsp[0].i_val)); }
#line 8045 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1091 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(append_int(L(), (yyvsp[-2].i_val)), (yyvsp[0].i_val)); }
#line 8051 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1095 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = PRIV_COPYFROMFILE; }
#line 8057 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1096 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = PRIV_COPYINTOFILE; }
#line 8063 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1100 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TABLE, (yyvsp[0].l)); }
#line 8069 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1101 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NAME, (yyvsp[0].l)); }
#line 8075 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1102 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_FUNC, (yyvsp[0].l)); }
#line 8081 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1113 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8087 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1114 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8093 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1119 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 8099 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1121 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 8105 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1125 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_INSERT,NULL); }
#line 8111 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1126 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_DELETE,NULL); }
#line 8117 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1127 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_TRUNCATE,NULL); }
#line 8123 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1128 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_UPDATE,(yyvsp[0].l)); }
#line 8129 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1129 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_SELECT,(yyvsp[0].l)); }
#line 8135 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1130 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_SELECT,(yyvsp[0].l)); }
#line 8141 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1131 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_EXECUTE,NULL); }
#line 8147 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1135 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 8153 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1137 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 8159 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1141 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 8165 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1142 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 8171 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1149 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8181 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1155 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L(), *part;
	  append_list(l, (yyvsp[-4].l));
	  append_symbol(l, _symbol_create_list( SQL_TABLE, append_list(L(),(yyvsp[-1].l))));
	  append_int(l, (yyvsp[-5].bval));
	  if((yyvsp[0].sym)) {
	      part = (yyvsp[0].sym)->data.lval;
	      append_int(part, FALSE);
	  }
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8196 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1166 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, (yyvsp[-3].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8206 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1172 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, (yyvsp[-3].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8216 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1178 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_readonly));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8226 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1184 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_append));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8236 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1190 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, _symbol_create_int(SQL_ALTER_TABLE, tr_writable));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8246 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1196 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L(), *part;
	  append_list(l, (yyvsp[-4].l));
	  append_symbol(l, _symbol_create_list( SQL_TABLE, append_list(L(),(yyvsp[-1].l))));
	  append_int(l, (yyvsp[-5].bval));
	  if((yyvsp[0].sym)) {
	      part = (yyvsp[0].sym)->data.lval;
	      append_int(part, TRUE);
	  }
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_TABLE, l ); }
#line 8261 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1207 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_TABLE, l ); }
#line 8271 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1213 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-5].l));
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-6].bval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_COLUMN, l); }
#line 8282 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1220 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-3].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_SET_TABLE_SCHEMA, l ); }
#line 8292 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1226 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval));
	  append_list(l, (yyvsp[0].l));
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_USER, l ); }
#line 8301 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1231 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_USER, l ); }
#line 8310 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1236 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  dlist *p = L();
	  append_string(l, NULL);
	  append_string(p, (yyvsp[-4].sval));
	  append_string(p, NULL);
	  append_int(p, (yyvsp[-6].i_val));
	  append_string(p, (yyvsp[0].sval));
	  append_list(l, p);
	  (yyval.sym) = _symbol_create_list( SQL_ALTER_USER, l ); }
#line 8324 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1246 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_RENAME_SCHEMA, l ); }
#line 8334 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1254 "sql_parser.y" /* yacc.c:1646  */
    { dlist * l = L();
				  append_string(l, (yyvsp[0].sval));
				  append_string(l, NULL);
				  append_int(l, (yyvsp[-2].i_val));
				  append_string(l, NULL);
				  (yyval.l) = l; }
#line 8345 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1260 "sql_parser.y" /* yacc.c:1646  */
    { dlist * l = L();
				  append_string(l, NULL);
				  append_string(l, (yyvsp[0].sval));
				  append_int(l, 0);
				  append_string(l, NULL);
				  (yyval.l) = l; }
#line 8356 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1267 "sql_parser.y" /* yacc.c:1646  */
    { dlist * l = L();
				  append_string(l, (yyvsp[-3].sval));
				  append_string(l, (yyvsp[0].sval));
				  append_int(l, (yyvsp[-5].i_val));
				  append_string(l, NULL);
				  (yyval.l) = l; }
#line 8367 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1277 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_DEFAULT, l); }
#line 8376 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1282 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-2].sval));
	  (yyval.sym) = _symbol_create_list( SQL_NULL, l); }
#line 8384 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1286 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  (yyval.sym) = _symbol_create_list( SQL_NOT_NULL, l); }
#line 8392 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1290 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_DROP_DEFAULT, (yyvsp[-2].sval)); }
#line 8398 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1292 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  if (!strlen((yyvsp[0].sval)))
	  	append_string(l, NULL);
	  else
	  	append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_STORAGE, l); }
#line 8410 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1300 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_STORAGE, l); }
#line 8419 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1308 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_COLUMN, l ); }
#line 8428 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1313 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_CONSTRAINT, l ); }
#line 8437 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1318 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, FALSE); /* no if exists check */
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TABLE, l ); }
#line 8447 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1326 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 8453 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1327 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 8459 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1331 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8465 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1332 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8471 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1333 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8477 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1355 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_list(l, (yyvsp[0].l));
		append_int(l, 0); /* to be dropped */
		(yyval.sym) = _symbol_create_list(SQL_CREATE_SEQ, l);
	}
#line 8489 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1366 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
		append_list(l, (yyvsp[0].l));
		(yyval.sym) = _symbol_create_list(SQL_DROP_SEQ, l);
	}
#line 8499 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1383 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
		append_list(l, (yyvsp[-1].l));
		append_list(l, (yyvsp[0].l)); 
		(yyval.sym) = _symbol_create_list(SQL_ALTER_SEQ, l);
	}
#line 8510 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1392 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 8516 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1393 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8522 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1396 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 8528 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1397 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-1].l), (yyvsp[0].sym)); }
#line 8534 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1401 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 8540 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1402 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-1].l), (yyvsp[0].sym)); }
#line 8546 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1406 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TYPE, append_type(L(),&(yyvsp[0].type))); }
#line 8552 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1407 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_lng(SQL_START, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 8558 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1408 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8564 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1412 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TYPE, append_type(L(),&(yyvsp[0].type))); }
#line 8570 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1413 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_START, append_int(L(),0)); /* plain restart now */ }
#line 8576 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1414 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_START, append_lng(append_int(L(),2), is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)));  }
#line 8582 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1415 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_START, append_symbol(append_int(L(),1), (yyvsp[0].sym)));  }
#line 8588 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1416 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8594 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1420 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_lng(SQL_INC, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 8600 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1421 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_lng(SQL_MINVALUE, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 8606 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1422 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_lng(SQL_MINVALUE, 0); }
#line 8612 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1423 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_lng(SQL_MAXVALUE, is_lng_nil((yyvsp[0].l_val)) ? (yyvsp[0].l_val) : (yyvsp[-1].i_val) * (yyvsp[0].l_val)); }
#line 8618 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1424 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_lng(SQL_MAXVALUE, 0); }
#line 8624 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1425 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_lng(SQL_CACHE, (yyvsp[0].l_val)); }
#line 8630 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1426 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int(SQL_CYCLE, 1); }
#line 8636 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1427 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int(SQL_CYCLE, 0); }
#line 8642 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1435 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-5].sval));
	  append_int(l, (yyvsp[-7].i_val));
	  append_list(l, (yyvsp[-3].l));
	  append_list(l, (yyvsp[-1].l));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_INDEX, l); }
#line 8653 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1444 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = hash_idx; }
#line 8659 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1445 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = ordered_idx; }
#line 8665 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1446 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = imprints_idx; }
#line 8671 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1447 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = hash_idx; }
#line 8677 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1468 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval));
	  append_int(l, (yyvsp[0].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_ROLE, l ); }
#line 8686 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1473 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-8].sval));
	  append_string(l, (yyvsp[-4].sval));
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-6].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_USER, l ); }
#line 8698 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1483 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_PW_UNENCRYPTED; }
#line 8704 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1484 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_PW_UNENCRYPTED; }
#line 8710 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1485 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_PW_ENCRYPTED; }
#line 8716 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1489 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 8722 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1490 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_string(L(), (yyvsp[-1].sval)), (yyvsp[0].sval)); }
#line 8728 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1495 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT;
	  dlist *l = L();

	  append_int(l, SQL_PERSIST);
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-3].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 8745 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1508 "sql_parser.y" /* yacc.c:1646  */
    {
      dlist *l = L();
      append_list(l, (yyvsp[-3].l));
      append_symbol(l, (yyvsp[0].sym));
      (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE_LOADER, l);
    }
#line 8756 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1515 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_STREAM;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-2].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 8773 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1528 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_MERGE_TABLE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-3].bval));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 8790 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1541 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_REPLICA_TABLE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-2].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 8807 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1557 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT, tpe = SQL_REMOTE;
	  dlist *l = L();

	  append_int(l, tpe);
	  append_list(l, (yyvsp[-4].l));
	  append_symbol(l, (yyvsp[-3].sym));
	  append_int(l, commit_action);
	  append_string(l, (yyvsp[-1].sval));
	  append_list(l, (yyvsp[0].l));
	  append_int(l, (yyvsp[-5].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 8824 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1570 "sql_parser.y" /* yacc.c:1646  */
    { int commit_action = CA_COMMIT;
	  dlist *l = L();

	  append_int(l, (yyvsp[-5].i_val));
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  if ((yyvsp[-5].i_val) != SQL_PERSIST)
		commit_action = (yyvsp[0].i_val);
	  append_int(l, commit_action);
	  append_string(l, NULL);
	  append_list(l, NULL);
	  append_int(l, (yyvsp[-3].bval));
	  append_symbol(l, NULL); /* only used for merge table */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, l ); }
#line 8843 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1587 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = PARTITION_RANGE; }
#line 8849 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1588 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = PARTITION_LIST; }
#line 8855 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1592 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8861 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1596 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_PARTITION_COLUMN, append_string(L(), (yyvsp[-1].sval)) ); }
#line 8867 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1597 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_PARTITION_EXPRESSION, append_symbol(L(), (yyvsp[-1].sym)) ); }
#line 8873 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1601 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 8879 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1603 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
     int properties = (yyvsp[-1].i_val);
     append_int(l, (yyvsp[-1].i_val));
     append_symbol(l, (yyvsp[0].sym));

     assert((yyvsp[-1].i_val) == PARTITION_RANGE || (yyvsp[-1].i_val) == PARTITION_LIST);
     if((yyvsp[0].sym)->token == SQL_PARTITION_COLUMN) {
        properties |= PARTITION_COLUMN;
     } else if((yyvsp[0].sym)->token == SQL_PARTITION_EXPRESSION) {
        properties |= PARTITION_EXPRESSION;
     } else {
        assert(0);
     }
     append_int(l, properties);

     (yyval.sym) = _symbol_create_list( SQL_MERGE_PARTITION, l ); }
#line 8900 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1622 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8906 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1626 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8912 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1627 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_MINVALUE, NULL ); }
#line 8918 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1631 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8924 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1632 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_MAXVALUE, NULL ); }
#line 8930 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1636 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 8936 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 1637 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 8942 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1641 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 8948 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1642 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 8954 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1647 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
      append_list(l, (yyvsp[-2].l));
      append_int(l, (yyvsp[0].bval));
      (yyval.sym) = _symbol_create_list( SQL_PARTITION_LIST, l ); }
#line 8963 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1652 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
      append_symbol(l, (yyvsp[-3].sym));
      append_symbol(l, (yyvsp[-1].sym));
      append_int(l, (yyvsp[0].bval));
      (yyval.sym) = _symbol_create_list( SQL_PARTITION_RANGE, l ); }
#line 8973 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 1658 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
      append_symbol(l, NULL);
      append_symbol(l, NULL);
      append_int(l, TRUE);
      (yyval.sym) = _symbol_create_list( SQL_MERGE_PARTITION, l ); }
#line 8983 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1666 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 8989 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 1667 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 8995 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1672 "sql_parser.y" /* yacc.c:1646  */
    {
	  (yyval.l) = append_string(L(), NULL);
	  append_int((yyval.l), SQL_PW_ENCRYPTED);
	  append_string((yyval.l), NULL);
  }
#line 9005 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 1678 "sql_parser.y" /* yacc.c:1646  */
    {
	  (yyval.l) = append_string(L(), (yyvsp[-3].sval));
	  append_int((yyval.l), (yyvsp[-2].i_val));
	  append_string((yyval.l), (yyvsp[0].sval));
  }
#line 9015 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1684 "sql_parser.y" /* yacc.c:1646  */
    {
	  (yyval.l) = append_string(L(), NULL);
	  append_int((yyval.l), (yyvsp[-2].i_val));
	  append_string((yyval.l), (yyvsp[0].sval));
  }
#line 9025 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 1692 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9031 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1693 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9037 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 1694 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9043 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1695 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_LOCAL_TEMP; }
#line 9049 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 1696 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_GLOBAL_TEMP; }
#line 9055 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 1697 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = SQL_GLOBAL_TEMP; }
#line 9061 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 1701 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_COMMIT; }
#line 9067 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1702 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_DELETE; }
#line 9073 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 1703 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_PRESERVE; }
#line 9079 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 1704 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = CA_DROP; }
#line 9085 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1708 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_CREATE_TABLE, (yyvsp[-1].l)); }
#line 9091 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 1709 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_SELECT, (yyvsp[0].l)); }
#line 9097 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1717 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[-3].l));
			  append_symbol((yyval.l), (yyvsp[-1].sym)); 
			  append_int((yyval.l), (yyvsp[0].i_val)); }
#line 9105 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 1723 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 9111 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1724 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9117 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 1725 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 9123 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1730 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 9129 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 1732 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 9135 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1739 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9141 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1740 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 9147 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1745 "sql_parser.y" /* yacc.c:1646  */
    {
			dlist *l = L();
			append_string(l, (yyvsp[-2].sval));
			append_type(l, &(yyvsp[-1].type));
			append_list(l, (yyvsp[0].l));
			(yyval.sym) = _symbol_create_list(SQL_COLUMN, l);
		}
#line 9159 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1753 "sql_parser.y" /* yacc.c:1646  */
    { /* SERIAL = INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY */
			/* handle multi-statements by wrapping them in a list */
			sql_subtype it;
			dlist* stmts;
			/* note: sql_next_seq_name uses sa_alloc */
			str sn = sql_next_seq_name(m);
			dlist *p; /* primary key */
			/* sequence generation code */
			dlist *l = L();
			/* finally all the options */
			dlist *o = L();

			/* the name of the sequence */
			dlist *seqn1 = L(), *seqn2 = L();

			if (m->scanner.schema)
				append_string(seqn1, m->scanner.schema);
			append_list(l, append_string(seqn1, sn));
			if ((yyvsp[0].i_val) == 1)
				sql_find_subtype(&it, "bigint", 64, 0);
			else
				sql_find_subtype(&it, "int", 32, 0);
    			append_symbol(o, _symbol_create_list(SQL_TYPE, append_type(L(),&it)));
			append_list(l, o);
			append_int(l, 1); /* to be dropped */

			if (m->sym) {
				stmts = m->sym->data.lval;
			} else {
				stmts = L();
				m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
			}	
			append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));

			l = L();
			append_string(l, (yyvsp[-1].sval));
			append_type(l, &it);
			o = L();
			if (m->scanner.schema)
				append_string(seqn2, m->scanner.schema);
			append_string(seqn2, sn);
			append_symbol(o, _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, seqn2)));
			p = L();
			append_string(p, NULL);
			append_symbol(p, _symbol_create(SQL_PRIMARY_KEY, NULL));
			append_symbol(o, _symbol_create_list(SQL_CONSTRAINT, p));
			append_list(l, o);
			(yyval.sym) = _symbol_create_list(SQL_COLUMN, l);
		}
#line 9213 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 1805 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 9219 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 1811 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 9225 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 1813 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym) ); }
#line 9231 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 1819 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-5].sval) );
	  append_list(l, (yyvsp[-1].l) );
	  (yyval.sym) = _symbol_create_list( SQL_COLUMN_OPTIONS, l ); }
#line 9240 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1827 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 9246 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1829 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 9252 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1835 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, (yyvsp[0].sym)); }
#line 9258 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 1839 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9264 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1845 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_symbol(l, (yyvsp[0].sym) );
	  (yyval.sym) = _symbol_create_list( SQL_CONSTRAINT, l ); }
#line 9273 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1853 "sql_parser.y" /* yacc.c:1646  */
    {
		/* handle multi-statements by wrapping them in a list */
		sql_subtype it;
		dlist* stmts;
		/* note: sql_next_seq_name uses sa_alloc */
		str sn = sql_next_seq_name(m);
		/* sequence generation code */
		dlist *l = L();
		/* the name of the sequence */
		append_list(l, append_string(L(), sn));
		if (!(yyvsp[0].l))
			(yyvsp[0].l) = L();
		sql_find_subtype(&it, "int", 32, 0);
		append_symbol((yyvsp[0].l), _symbol_create_list(SQL_TYPE, append_type(L(),&it)));

		/* finally all the options */
		append_list(l, (yyvsp[0].l));
		append_int(l, 1); /* to be dropped */
		(yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, append_string(L(), sn)));

		if (m->sym) {
			stmts = m->sym->data.lval;
		} else {
			stmts = L();
			m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
		}	
		append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));
	}
#line 9306 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 1882 "sql_parser.y" /* yacc.c:1646  */
    {
		/* handle multi-statements by wrapping them in a list */
		sql_subtype it;
		dlist* stmts;
		/* note: sql_next_seq_name uses sa_alloc */
		str sn = sql_next_seq_name(m);
		/* sequence generation code */
		dlist *l = L();
		/* finally all the options */
		dlist *o = L();

		/* the name of the sequence */
		dlist *seqn1 = L(), *seqn2 = L();

		if (m->scanner.schema)
			append_string(seqn1, m->scanner.schema);
		append_list(l, append_string(seqn1, sn));
		sql_find_subtype(&it, "int", 32, 0);
    		append_symbol(o, _symbol_create_list(SQL_TYPE, append_type(L(),&it)));
		append_list(l, o);
		append_int(l, 1); /* to be dropped */
		if (m->scanner.schema)
			append_string(seqn2, m->scanner.schema);
		append_string(seqn2, sn);
		(yyval.sym) = _symbol_create_symbol(SQL_DEFAULT, _symbol_create_list(SQL_NEXT, seqn2));

		if (m->sym) {
			stmts = m->sym->data.lval;
		} else {
			stmts = L();
			m->sym = _symbol_create_list(SQL_MULSTMT, stmts);
		}	
		append_symbol(stmts, _symbol_create_list(SQL_CREATE_SEQ, l));
	}
#line 9345 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1919 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 9351 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 1920 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 9357 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1927 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-1].sval) );
	  append_symbol(l, (yyvsp[0].sym) );
	  (yyval.sym) = _symbol_create_list( SQL_CONSTRAINT, l ); }
#line 9366 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 1936 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 9372 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1937 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 9378 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1941 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9384 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 1942 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 9390 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1943 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 9396 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 1944 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 3; }
#line 9402 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1945 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 4; }
#line 9408 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 1949 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = ((yyvsp[0].i_val) << 8); }
#line 9414 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1953 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 9420 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1957 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (2 << 8) + 2; /* defaults are RESTRICT */ }
#line 9426 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 1958 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 9432 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1959 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 9438 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 1960 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val) + (yyvsp[0].i_val); }
#line 9444 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1961 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val) + (yyvsp[0].i_val); }
#line 9450 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 1965 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9456 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 1966 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 9462 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 1967 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 9468 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 1968 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9474 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 1972 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 9480 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 1973 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 9486 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 1977 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_NOT_NULL, NULL); }
#line 9492 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 1978 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_NULL, NULL); }
#line 9498 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 1979 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_UNIQUE, NULL ); }
#line 9504 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 1980 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_PRIMARY_KEY, NULL ); }
#line 9510 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 1983 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, (yyvsp[-3].l) );
			  append_list(l, (yyvsp[-2].l) );
			  append_int(l, (yyvsp[-1].i_val) );
			  append_int(l, (yyvsp[0].i_val) );
			  (yyval.sym) = _symbol_create_list( SQL_FOREIGN_KEY, l); }
#line 9521 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 1996 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_UNIQUE, (yyvsp[0].l)); }
#line 9527 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 1998 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_PRIMARY_KEY, (yyvsp[0].l)); }
#line 9533 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 2002 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, (yyvsp[-3].l) );
			  append_list(l, (yyvsp[-5].l) );
			  append_list(l, (yyvsp[-2].l) );
			  append_int(l, (yyvsp[-1].i_val) );
			  append_int(l, (yyvsp[0].i_val) );
			  (yyval.sym) = _symbol_create_list( SQL_FOREIGN_KEY, l); }
#line 9545 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 2013 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_CHECK, (yyvsp[-1].sym)); }
#line 9551 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 2018 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 9557 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 2020 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string( (yyvsp[-2].l), (yyvsp[0].sval) ); }
#line 9563 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 2024 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_LIKE, (yyvsp[0].l) ); }
#line 9569 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 2029 "sql_parser.y" /* yacc.c:1646  */
    {  dlist *l = L();
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-3].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_int(l, (yyvsp[0].bval));
	  append_int(l, TRUE);	/* persistent view */
	  append_int(l, (yyvsp[-6].bval));
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_VIEW, l ); 
	}
#line 9583 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 2042 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 9589 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 2051 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 9595 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 2052 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 9601 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 2056 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 9607 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 2061 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 9613 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 2065 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 9619 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 2070 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				append_list(l, (yyvsp[-3].l));
				append_string(l, (yyvsp[0].sval));
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_TYPE, l ); }
#line 9628 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 2077 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval)); }
#line 9634 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 2086 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_FUNC; }
#line 9640 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 2087 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_PROC; }
#line 9646 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 2088 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_AGGR; }
#line 9652 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 2089 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_AGGR; }
#line 9658 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 2090 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_FILT; }
#line 9664 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 2091 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_FILT; }
#line 9670 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 2092 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_ANALYTIC; }
#line 9676 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 2093 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_ANALYTIC; }
#line 9682 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 2094 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_LOADER; }
#line 9688 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 2095 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = F_LOADER; }
#line 9694 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 2098 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9700 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 2099 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9706 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 2106 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-7].l));
				append_list(f, (yyvsp[-5].l));
				append_symbol(f, (yyvsp[-3].sym));
				append_list(f, (yyvsp[0].l));
				append_list(f, NULL);
				append_int(f, (yyvsp[-8].i_val));
				append_int(f, FUNC_LANG_MAL);
				append_int(f, (yyvsp[-9].bval));
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 9721 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 2120 "sql_parser.y" /* yacc.c:1646  */
    { dlist *f = L();
				append_list(f, (yyvsp[-5].l));
				append_list(f, (yyvsp[-3].l));
				append_symbol(f, (yyvsp[-1].sym));
				append_list(f, NULL);
				append_list(f, (yyvsp[0].l));
				append_int(f, (yyvsp[-6].i_val));
				append_int(f, FUNC_LANG_SQL);
				append_int(f, (yyvsp[-7].bval));
			  (yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f ); }
#line 9736 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 2134 "sql_parser.y" /* yacc.c:1646  */
    {
			int lang = 0;
			dlist *f = L();
			char l = *(yyvsp[-1].sval);

			if (l == 'R' || l == 'r')
				lang = FUNC_LANG_R;
			else if (l == 'P' || l == 'p') {
				// code does not get cleaner than this people
				if (strcasecmp((yyvsp[-1].sval), "PYTHON_MAP") == 0) {
					lang = FUNC_LANG_MAP_PY;
				} else if (strcasecmp((yyvsp[-1].sval), "PYTHON3_MAP") == 0) {
					lang = FUNC_LANG_MAP_PY3;
				} else if (strcasecmp((yyvsp[-1].sval), "PYTHON3") == 0) {
					lang = FUNC_LANG_PY3;
				} else {
					lang = FUNC_LANG_PY;
				}
			} else if (l == 'C' || l == 'c') {
				if (strcasecmp((yyvsp[-1].sval), "CPP") == 0) {
					lang = FUNC_LANG_CPP;
				} else {
					lang = FUNC_LANG_C;
				}
			}
			else if (l == 'J' || l == 'j')
				lang = FUNC_LANG_J;
			else {
				sqlformaterror(m, "Language name R, C, PYTHON[3], PYTHON[3]_MAP or J(avascript):expected, received '%c'", l);
			}

			append_list(f, (yyvsp[-7].l));
			append_list(f, (yyvsp[-5].l));
			append_symbol(f, (yyvsp[-3].sym));
			append_list(f, NULL);
			append_list(f, append_string(L(), (yyvsp[0].sval)));
			append_int(f, (yyvsp[-8].i_val));
			append_int(f, lang);
			append_int(f, (yyvsp[-9].bval));
			(yyval.sym) = _symbol_create_list( SQL_CREATE_FUNC, f );
		}
#line 9782 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 2179 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); append_symbol( (yyval.l), (yyvsp[0].sym)); }
#line 9788 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 2183 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-3].l),(yyvsp[-2].sym)); }
#line 9794 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 2187 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-3].l),(yyvsp[-2].sym)); }
#line 9800 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 2202 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 9806 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 2204 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l),(yyvsp[-1].sym));}
#line 9812 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 2208 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 9818 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 2210 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l),(yyvsp[-1].sym));}
#line 9824 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 2258 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 9830 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 2262 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.sym) = _symbol_create_symbol(SQL_CALL, (yyvsp[0].sym));}
#line 9836 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 2267 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L(); 
		  append_list( l, (yyvsp[-3].l));
		  append_list( l, (yyvsp[-1].l));
		  assert(0);
		  (yyval.sym) = _symbol_create_list( SQL_FUNC, l);
		}
#line 9847 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 2278 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 9853 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 2279 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 9859 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 2280 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 9865 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 2284 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_RETURN, (yyvsp[0].sym)); }
#line 9871 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 2291 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_TABLE, (yyvsp[-1].sym)); }
#line 9877 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 2296 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_list(
		    append_list(
		     append_symbol(
		      L(),(yyvsp[-4].sym)),(yyvsp[-3].l)),(yyvsp[-2].l))); }
#line 9887 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 2302 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_list(
		    append_list(
		     L(),(yyvsp[-3].l)),(yyvsp[-2].l))); }
#line 9896 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 2310 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_list(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].l))); }
#line 9905 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 2318 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 9911 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 2320 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 9917 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 2325 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_list(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].l))); }
#line 9926 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 2333 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 9932 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 2335 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 9938 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 2339 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 9944 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 2340 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 9950 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 2350 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_list(l, (yyvsp[-3].l));
		  append_symbol(l, (yyvsp[-2].sym));
		  (yyval.sym) = _symbol_create_list(SQL_IF, l);
		}
#line 9961 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 2361 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 9967 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 2363 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_ELSE, (yyvsp[0].l)); }
#line 9973 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 2366 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-3].sym));
		  append_list(l, (yyvsp[-1].l));
		  append_symbol(l, (yyvsp[0].sym));
		  { (yyval.sym) = _symbol_create_list(SQL_IF, l); }
		}
#line 9984 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 2380 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l;
		  char *label = (yyvsp[-7].sval)?(yyvsp[-7].sval):(yyvsp[0].sval);
		  if ((yyvsp[-7].sval) && (yyvsp[0].sval) && strcmp((yyvsp[-7].sval), (yyvsp[0].sval)) != 0) {
			(yyval.sym) = NULL;
			yyerror(m, "WHILE: labels should match");
			YYABORT;
		  }
 		  l = L();
		  append_symbol(l, (yyvsp[-5].sym)); /* condition */
		  append_list(l, (yyvsp[-3].l));	/* statements */
		  append_string(l, label);
		  (yyval.sym) = _symbol_create_list(SQL_WHILE, l);
		}
#line 10002 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 2396 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 10008 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 2401 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 10014 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 2406 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
				  append_string((yyval.l), (yyvsp[-1].sval));
			  	  append_type((yyval.l), &(yyvsp[0].type));
				}
#line 10023 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 404:
#line 2411 "sql_parser.y" /* yacc.c:1646  */
    { 
				  append_string((yyval.l), (yyvsp[-1].sval));
			  	  append_type((yyval.l), &(yyvsp[0].type));
				}
#line 10032 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 2419 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TABLE, (yyvsp[-1].l)); }
#line 10038 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 2421 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TYPE, append_type(L(),&(yyvsp[0].type))); }
#line 10044 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 2426 "sql_parser.y" /* yacc.c:1646  */
    { dlist *vararg = L();
			  append_string(vararg, "*");
			  append_type(vararg, NULL);
			  (yyval.l) = append_list(L(), vararg); }
#line 10053 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 2430 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 10059 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 410:
#line 2435 "sql_parser.y" /* yacc.c:1646  */
    { dlist *p = L();
			  append_string(p, (yyvsp[-1].sval));
			  append_type(p, &(yyvsp[0].type));
			  (yyval.l) = append_list((yyvsp[-3].l), p); }
#line 10068 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 411:
#line 2440 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *p = L();
			  append_string(p, (yyvsp[-1].sval));
			  append_type(p, &(yyvsp[0].type));
			  (yyval.l) = append_list(l, p); }
#line 10078 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 412:
#line 2490 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-6].l));
	  append_int(l, (yyvsp[-5].i_val));
	  append_symbol(l, (yyvsp[-4].sym));
	  append_list(l, (yyvsp[-2].l));
	  append_list(l, (yyvsp[-1].l));
	  append_list(l, (yyvsp[0].l));
	  append_int(l, (yyvsp[-8].bval));
	  (yyval.sym) = _symbol_create_list(SQL_CREATE_TRIGGER, l); 
	}
#line 10093 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 413:
#line 2503 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10099 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 414:
#line 2504 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 10105 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 2509 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_INSERT, NULL); }
#line 10111 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 2510 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_DELETE, NULL); }
#line 10117 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 2511 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_TRUNCATE, NULL); }
#line 10123 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 418:
#line 2512 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_UPDATE, NULL); }
#line 10129 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 2513 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_UPDATE, (yyvsp[0].l)); }
#line 10135 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 2517 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 10141 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 2518 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 10147 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 2522 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 10153 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 2524 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-1].l), (yyvsp[0].l)); }
#line 10159 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 2529 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 0), (yyvsp[0].sval)); }
#line 10165 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 2530 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 1), (yyvsp[0].sval)); }
#line 10171 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 2531 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 0), (yyvsp[0].sval)); }
#line 10177 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 2532 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(append_int(L(), 1), (yyvsp[0].sval)); }
#line 10183 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 432:
#line 2547 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_int((yyval.l), (yyvsp[-2].i_val));
	  append_symbol((yyval.l), (yyvsp[-1].sym));
	  append_list((yyval.l), (yyvsp[0].l));
	}
#line 10193 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 433:
#line 2554 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 10199 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 2555 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 10205 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 2559 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10211 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 436:
#line 2560 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 10217 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 2564 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 10223 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 2565 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 10229 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 2570 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 10235 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 2573 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 10241 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 2578 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );	
	  append_list(l, (yyvsp[0].l) );
	  append_int(l, (yyvsp[-2].i_val) );
	  (yyval.l) = l; }
#line 10251 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 2587 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, (yyvsp[-2].bval) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TABLE, l ); }
#line 10261 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 2593 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[-4].i_val) );
	  append_int(l, (yyvsp[-3].bval) );
	  append_int(l, 0 ); /* not all */
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 10274 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 2602 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_list(l, NULL );
	  append_int(l, (yyvsp[-2].i_val) );
	  append_int(l, FALSE );
	  append_int(l, 1 ); /* all */
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_FUNC, l ); }
#line 10287 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 2611 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  append_int(l, (yyvsp[-2].bval) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_VIEW, l ); }
#line 10297 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 2617 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TYPE, l ); }
#line 10306 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 447:
#line 2621 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_DROP_ROLE, (yyvsp[0].sval) ); }
#line 10312 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 448:
#line 2622 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_DROP_USER, (yyvsp[0].sval) ); }
#line 10318 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 449:
#line 2623 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_DROP_INDEX, (yyvsp[0].l) ); }
#line 10324 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 450:
#line 2625 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[0].l) );
	  append_int(l, (yyvsp[-1].bval) );
	  (yyval.sym) = _symbol_create_list( SQL_DROP_TRIGGER, l );
	}
#line 10334 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 2633 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.l) = NULL;}
#line 10340 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 2634 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.l) = (yyvsp[-1].l);}
#line 10346 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 2635 "sql_parser.y" /* yacc.c:1646  */
    {(yyval.l) = L(); }
#line 10352 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 2639 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_type(l, &(yyvsp[0].type) );
				  (yyval.l)= l; }
#line 10360 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 2642 "sql_parser.y" /* yacc.c:1646  */
    { append_type((yyvsp[0].l), &(yyvsp[-2].type));
				  (yyval.l) = (yyvsp[0].l); }
#line 10367 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 2647 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10373 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 2648 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10379 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 2649 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 10385 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 2669 "sql_parser.y" /* yacc.c:1646  */
    {
	  (yyval.sym) = (yyvsp[0].sym);
	  m->type = Q_TRANS;					}
#line 10393 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 2681 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_COMMIT, (yyvsp[0].bval));  }
#line 10399 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 471:
#line 2683 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( TR_SAVEPOINT, (yyvsp[0].sval)); }
#line 10405 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 472:
#line 2685 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( TR_RELEASE, (yyvsp[0].sval)); }
#line 10411 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 473:
#line 2687 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( TR_ROLLBACK,
		   append_string(
			append_int(L(), (yyvsp[-1].bval)), (yyvsp[0].sval) )); }
#line 10419 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 474:
#line 2691 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_START, (yyvsp[0].i_val)); }
#line 10425 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 475:
#line 2693 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_MODE, (yyvsp[0].i_val)); }
#line 10431 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 476:
#line 2695 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_int( TR_MODE, (yyvsp[0].i_val)); }
#line 10437 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 477:
#line 2699 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_none; }
#line 10443 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 2705 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 10449 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 2707 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = ((yyvsp[-2].i_val) | (yyvsp[0].i_val)); }
#line 10455 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 481:
#line 2711 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_readonly; }
#line 10461 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 2712 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_writable; }
#line 10467 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 2713 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_serializable; }
#line 10473 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 2714 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = tr_none; /* not supported */ }
#line 10479 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 489:
#line 2725 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 10485 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 490:
#line 2726 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 10491 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 491:
#line 2730 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 10497 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 492:
#line 2731 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 10503 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 493:
#line 2732 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 10509 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 494:
#line 2736 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 10515 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 495:
#line 2737 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 10521 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 496:
#line 2741 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 10527 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 497:
#line 2742 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 10533 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 498:
#line 2743 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 10539 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 499:
#line 2748 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-12].l));
	  append_list(l, (yyvsp[-11].l));
	  append_list(l, (yyvsp[-9].l));
	  append_list(l, (yyvsp[-8].l));
	  append_list(l, (yyvsp[-6].l));
	  append_list(l, (yyvsp[-14].l));
	  append_string(l, (yyvsp[-4].sval));
	  append_int(l, (yyvsp[-3].bval));
	  append_int(l, (yyvsp[-2].bval));
	  append_int(l, (yyvsp[-1].bval));
	  append_list(l, (yyvsp[0].l));
	  append_int(l, (yyvsp[-7].bval));
	  append_int(l, (yyvsp[-5].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYFROM, l ); }
#line 10559 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 500:
#line 2764 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-10].l));
	  append_list(l, (yyvsp[-9].l));
	  append_list(l, NULL);
	  append_list(l, (yyvsp[-6].l));
	  append_list(l, (yyvsp[-5].l));
	  append_list(l, (yyvsp[-12].l));
	  append_string(l, (yyvsp[-3].sval));
	  append_int(l, (yyvsp[-2].bval));
	  append_int(l, (yyvsp[-1].bval));
	  append_int(l, (yyvsp[0].bval));
	  append_list(l, NULL);
	  append_int(l, 0);
	  append_int(l, (yyvsp[-4].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYFROM, l ); }
#line 10579 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 501:
#line 2780 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_COPYLOADER, l ); }
#line 10588 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 502:
#line 2785 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-5].l));
	  append_list(l, (yyvsp[-4].l));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[0].bval));
	  append_int(l, (yyvsp[-1].bval));
	  (yyval.sym) = _symbol_create_list( SQL_BINCOPYFROM, l ); }
#line 10600 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 503:
#line 2793 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-5].sym));
	  append_string(l, (yyvsp[-3].sval));
	  append_list(l, (yyvsp[-1].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, (yyvsp[-2].bval));
	  (yyval.sym) = _symbol_create_list( SQL_COPYTO, l ); }
#line 10612 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 504:
#line 2801 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_string(l, NULL);
	  append_list(l, (yyvsp[-1].l));
	  append_string(l, (yyvsp[0].sval));
	  append_int(l, 0);
	  (yyval.sym) = _symbol_create_list( SQL_COPYTO, l ); }
#line 10624 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 505:
#line 2811 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 10630 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 506:
#line 2812 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 10636 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 507:
#line 2817 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(L(), (yyvsp[0].l_val)); }
#line 10642 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 508:
#line 2819 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng((yyvsp[-2].l), (yyvsp[0].l_val)); }
#line 10648 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 509:
#line 2823 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 10654 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 510:
#line 2824 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 10660 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 511:
#line 2828 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 10666 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 512:
#line 2829 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-2].l), (yyvsp[0].l)); }
#line 10672 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 513:
#line 2834 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_string(l, (yyvsp[0].sval) );
			  (yyval.l) = l; }
#line 10680 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 514:
#line 2838 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_string(l, (yyvsp[-1].sval) );
			  append_string(l, (yyvsp[0].sval) );
			  (yyval.l) = l; }
#line 10689 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 515:
#line 2846 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, sa_strdup(SA, "|"));
				  append_string(l, sa_strdup(SA, "\n"));
				  (yyval.l) = l; }
#line 10698 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 516:
#line 2851 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, (yyvsp[0].sval));
				  append_string(l, sa_strdup(SA, "\n"));
				  (yyval.l) = l; }
#line 10707 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 517:
#line 2856 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, (yyvsp[-2].sval));
				  append_string(l, (yyvsp[0].sval));
				  (yyval.l) = l; }
#line 10716 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 518:
#line 2861 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
				  append_string(l, (yyvsp[-4].sval));
				  append_string(l, (yyvsp[-2].sval));
				  append_string(l, (yyvsp[0].sval));
				  (yyval.l) = l; }
#line 10726 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 519:
#line 2869 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 10732 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 520:
#line 2870 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 10738 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 521:
#line 2874 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 10744 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 522:
#line 2875 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-1].l_val)), 0); }
#line 10750 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 523:
#line 2876 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), -1), (yyvsp[0].l_val)); }
#line 10756 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 524:
#line 2878 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-3].l_val)), (yyvsp[-1].l_val)); }
#line 10762 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 525:
#line 2880 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_lng(append_lng(L(), (yyvsp[-3].l_val)), (yyvsp[0].l_val)); }
#line 10768 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 526:
#line 2884 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 10774 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 527:
#line 2885 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 10780 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 528:
#line 2889 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 10786 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 529:
#line 2890 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 10792 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 530:
#line 2891 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 10798 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 531:
#line 2895 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 10804 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 532:
#line 2896 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 10810 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 533:
#line 2900 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 10816 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 534:
#line 2901 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 10822 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 535:
#line 2905 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 10828 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 536:
#line 2906 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 10834 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 537:
#line 2910 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 10840 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 538:
#line 2911 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 10846 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 539:
#line 2915 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 10852 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 540:
#line 2917 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string((yyvsp[-2].l), (yyvsp[0].sval)); }
#line 10858 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 541:
#line 2923 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_string(l, (yyvsp[-1].sval));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_DELETE, l ); }
#line 10868 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 542:
#line 2931 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10874 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 543:
#line 2932 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 10880 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 544:
#line 2933 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 10886 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 545:
#line 2938 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, (yyvsp[-1].i_val) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_TRUNCATE, l ); }
#line 10896 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 546:
#line 2944 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l) );
	  append_int(l, (yyvsp[-1].i_val) );
	  append_int(l, (yyvsp[0].i_val) );
	  (yyval.sym) = _symbol_create_list( SQL_TRUNCATE, l ); }
#line 10906 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 547:
#line 2954 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-5].l));
	  append_string(l, (yyvsp[-4].sval));
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_UPDATE, l ); }
#line 10918 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 548:
#line 2964 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 10924 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 549:
#line 2965 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 10930 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 550:
#line 2970 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
     append_list(l, (yyvsp[0].l));
     (yyval.sym) = _symbol_create_list( SQL_UPDATE, l ); }
#line 10938 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 551:
#line 2974 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_DELETE, NULL ); }
#line 10944 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 552:
#line 2979 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
     append_list(l, (yyvsp[-1].l));
     append_symbol(l, (yyvsp[0].sym));
     (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 10953 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 553:
#line 2987 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
     append_symbol(l, (yyvsp[-2].sym));
     append_symbol(l, (yyvsp[0].sym));
     (yyval.sym) = _symbol_create_list( SQL_MERGE_MATCH, l ); }
#line 10962 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 554:
#line 2992 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
     append_symbol(l, (yyvsp[-2].sym));
     append_symbol(l, (yyvsp[0].sym));
     (yyval.sym) = _symbol_create_list( SQL_MERGE_NO_MATCH, l ); }
#line 10971 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 555:
#line 2999 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 10977 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 556:
#line 3000 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-1].l), (yyvsp[0].sym)); }
#line 10983 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 557:
#line 3006 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-6].l));
	  append_string(l, (yyvsp[-5].sval));
	  append_symbol(l, (yyvsp[-3].sym));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_list(l, (yyvsp[0].l));
	  (yyval.sym) = _symbol_create_list( SQL_MERGE, l ); }
#line 10995 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 558:
#line 3017 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-1].l));
	  append_list(l, NULL);
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 11005 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 559:
#line 3025 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INSERT, l ); }
#line 11015 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 560:
#line 3034 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VALUES, L()); }
#line 11021 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 561:
#line 3036 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VALUES, L()); }
#line 11027 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 563:
#line 3041 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[-1].l)); }
#line 11033 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 564:
#line 3043 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-4].l), (yyvsp[-1].l)); }
#line 11039 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 565:
#line 3047 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11045 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 566:
#line 3049 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11051 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 567:
#line 3053 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11057 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 568:
#line 3055 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11063 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 569:
#line 3059 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_NULL, NULL ); }
#line 11069 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 571:
#line 3064 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create(SQL_DEFAULT, NULL ); }
#line 11075 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 574:
#line 3073 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 11081 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 575:
#line 3074 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 11087 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 576:
#line 3075 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 11093 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 577:
#line 3079 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 11099 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 578:
#line 3081 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 11105 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 579:
#line 3086 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  append_string(l, (yyvsp[-2].sval));
	  (yyval.sym) = _symbol_create_list( SQL_ASSIGN, l); }
#line 11114 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 580:
#line 3091 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  append_list(l, (yyvsp[-2].l));
	  (yyval.sym) = _symbol_create_list( SQL_ASSIGN, l ); }
#line 11123 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 581:
#line 3098 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11129 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 582:
#line 3099 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11135 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 583:
#line 3106 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 11141 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 584:
#line 3108 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_CROSS, l); }
#line 11150 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 585:
#line 3113 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, 0);
	  append_int(l, (yyvsp[-3].i_val));
	  append_symbol(l, (yyvsp[-1].sym));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 11162 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 586:
#line 3121 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, 1);
	  append_int(l, (yyvsp[-2].i_val));
	  append_symbol(l, (yyvsp[0].sym));
	  append_symbol(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_JOIN, l); }
#line 11174 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 587:
#line 3131 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 11180 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 588:
#line 3132 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 11186 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 589:
#line 3133 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1 + (yyvsp[-1].i_val); }
#line 11192 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 590:
#line 3137 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 11198 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 591:
#line 3138 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 11204 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 592:
#line 3142 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 11210 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 593:
#line 3143 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 11216 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 594:
#line 3144 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 11222 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 595:
#line 3148 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11228 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 596:
#line 3150 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_USING, (yyvsp[0].l)); }
#line 11234 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 598:
#line 3174 "sql_parser.y" /* yacc.c:1646  */
    {
		dlist *l = L();
	  	append_list(l, (yyvsp[-1].l));
	  	append_symbol(l, (yyvsp[0].sym));
	  	(yyval.sym) = _symbol_create_list( SQL_WITH, l ); 
	}
#line 11245 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 599:
#line 3183 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11251 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 600:
#line 3184 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11257 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 601:
#line 3189 "sql_parser.y" /* yacc.c:1646  */
    {  dlist *l = L();
	  append_list(l, append_string(L(), (yyvsp[-3].sval)));
	  append_list(l, (yyvsp[-2].l));
	  append_symbol(l, (yyvsp[0].sym));
	  append_int(l, FALSE);	/* no with check */
	  append_int(l, FALSE);	/* inlined view  (ie not persistent) */
	  append_int(l, FALSE); /* no replace clause */
	  (yyval.sym) = _symbol_create_list( SQL_CREATE_VIEW, l ); 
	}
#line 11271 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 610:
#line 3216 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = newSelectNode( SA, (yyvsp[-2].bval), (yyvsp[-1].l), NULL,
		(yyvsp[0].l)->h->data.sym,
		(yyvsp[0].l)->h->next->data.sym,
		(yyvsp[0].l)->h->next->next->data.sym,
		(yyvsp[0].l)->h->next->next->next->data.sym,
		NULL, NULL, NULL, NULL, NULL, NULL,
		(yyvsp[0].l)->h->next->next->next->next->data.sym);
	}
#line 11284 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 611:
#line 3228 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = newSelectNode( SA, (yyvsp[-4].bval), (yyvsp[-3].l), (yyvsp[-1].l),
		(yyvsp[0].l)->h->data.sym,
		(yyvsp[0].l)->h->next->data.sym,
		(yyvsp[0].l)->h->next->next->data.sym,
		(yyvsp[0].l)->h->next->next->next->data.sym,
		NULL, NULL, NULL, NULL, NULL, NULL,
		(yyvsp[0].l)->h->next->next->next->next->data.sym);
	}
#line 11297 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 612:
#line 3240 "sql_parser.y" /* yacc.c:1646  */
    { 
	  (yyval.sym) = (yyvsp[-5].sym);
	  if ((yyvsp[-4].sym) || (yyvsp[-3].sym) || (yyvsp[-2].sym) || (yyvsp[-1].sym) || (yyvsp[0].sym)) {
	  	if ((yyvsp[-5].sym) != NULL &&
		    ((yyvsp[-5].sym)->token == SQL_SELECT ||
		     (yyvsp[-5].sym)->token == SQL_UNION  ||
		     (yyvsp[-5].sym)->token == SQL_EXCEPT ||
		     (yyvsp[-5].sym)->token == SQL_INTERSECT)) {
			if ((yyvsp[-5].sym)->token == SQL_SELECT) {
	 			SelectNode *s = (SelectNode*)(yyvsp[-5].sym);
	
	  			s -> orderby = (yyvsp[-4].sym);
	  			s -> limit = (yyvsp[-3].sym);
	  			s -> offset = (yyvsp[-2].sym);
	  			s -> sample = (yyvsp[-1].sym);
				s -> seed = (yyvsp[0].sym);
			} else { /* Add extra select * from .. in case of UNION, EXCEPT, INTERSECT */
				(yyval.sym) = newSelectNode( 
					SA, 0, 
					append_symbol(L(), _symbol_create_list(SQL_TABLE, append_string(append_string(L(),NULL),NULL))), NULL,
					_symbol_create_list( SQL_FROM, append_symbol(L(), (yyvsp[-5].sym))), NULL, NULL, NULL, (yyvsp[-4].sym), _symbol_create_list(SQL_NAME, append_list(append_string(L(),"inner"),NULL)), (yyvsp[-3].sym), (yyvsp[-2].sym), (yyvsp[-1].sym), (yyvsp[0].sym), NULL);
			}
	  	} else {
			yyerror(m, "missing SELECT operator");
			YYABORT;
	  	}
	 } 
	}
#line 11330 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 613:
#line 3273 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_UNION, l); }
#line 11341 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 614:
#line 3282 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_EXCEPT, l); }
#line 11352 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 615:
#line 3291 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_int(l, (yyvsp[-2].bval));
	  append_list(l, (yyvsp[-1].l));
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list( SQL_INTERSECT, l); }
#line 11363 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 616:
#line 3297 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VALUES, (yyvsp[0].l)); }
#line 11369 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 617:
#line 3298 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 11375 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 619:
#line 3303 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 11381 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 620:
#line 3304 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 11387 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 621:
#line 3305 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 11393 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 622:
#line 3310 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 11399 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 623:
#line 3312 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L(); }
#line 11405 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 624:
#line 3314 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 11411 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 626:
#line 3324 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
	  append_symbol((yyval.l), (yyvsp[-4].sym));
	  append_symbol((yyval.l), (yyvsp[-2].sym));
	  append_symbol((yyval.l), (yyvsp[-1].sym));
	  append_symbol((yyval.l), (yyvsp[0].sym));
	  append_symbol((yyval.l), (yyvsp[-3].sym)); }
#line 11422 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 627:
#line 3333 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L(); append_string(l, (yyvsp[-4].sval)); append_list(l, (yyvsp[-1].l));
                                            (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 11429 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 628:
#line 3338 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11435 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 629:
#line 3339 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11441 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 630:
#line 3343 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11447 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 631:
#line 3344 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WINDOW, (yyvsp[0].l)); }
#line 11453 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 632:
#line 3348 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11459 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 633:
#line 3349 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_FROM, (yyvsp[0].l)); }
#line 11465 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 634:
#line 3353 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11471 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 635:
#line 3355 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11477 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 636:
#line 3359 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_list(l, (yyvsp[-1].l));
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 11486 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 637:
#line 3364 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_symbol(l, (yyvsp[-1].sym));
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  	  	  append_int(l, 0);
		  		  (yyval.sym) = _symbol_create_list(SQL_TABLE, l); }
#line 11496 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 638:
#line 3370 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_symbol(l, (yyvsp[-1].sym));
		  	  	  append_symbol(l, (yyvsp[0].sym));
		  	  	  append_int(l, 1);
		  		  (yyval.sym) = _symbol_create_list(SQL_TABLE, l); }
#line 11506 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 639:
#line 3376 "sql_parser.y" /* yacc.c:1646  */
    {
				  (yyval.sym) = (yyvsp[-1].sym);
				  if ((yyval.sym)->token == SQL_SELECT) {
				  	SelectNode *sn = (SelectNode*)(yyvsp[-1].sym);
				  	sn->name = (yyvsp[0].sym);
				  } else {
				  	append_symbol((yyvsp[-1].sym)->data.lval, (yyvsp[0].sym));
				  }
				}
#line 11520 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 640:
#line 3386 "sql_parser.y" /* yacc.c:1646  */
    {
				  (yyval.sym) = (yyvsp[-1].sym);
				  if ((yyval.sym)->token == SQL_SELECT) {
				  	SelectNode *sn = (SelectNode*)(yyvsp[-1].sym);
				  	sn->name = (yyvsp[0].sym);
					sn->lateral = 1;
				  } else {
				  	append_symbol((yyvsp[-1].sym)->data.lval, (yyvsp[0].sym));
	  				append_int((yyvsp[-1].sym)->data.lval, 1);
				  }
				}
#line 11536 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 641:
#line 3398 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL;
				  yyerror(m, "subquery table reference needs alias, use AS xxx");
				  YYABORT;
				}
#line 11545 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 642:
#line 3402 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym);
				  append_symbol((yyvsp[0].sym)->data.lval, NULL); }
#line 11552 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 643:
#line 3408 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[-3].sval));
		  	  	  append_list(l, (yyvsp[-1].l));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 11561 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 644:
#line 3413 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[0].sval));
		  	  	  append_list(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 11570 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 645:
#line 3418 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[-3].sval));
		  	  	  append_list(l, (yyvsp[-1].l));
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 11579 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 646:
#line 3423 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  		  append_string(l, (yyvsp[0].sval));
		  	  	  append_list(l, NULL);
		  		  (yyval.sym) = _symbol_create_list(SQL_NAME, l); }
#line 11588 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 647:
#line 3430 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11594 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 648:
#line 3431 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11600 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 649:
#line 3435 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11606 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 650:
#line 3436 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, (yyvsp[0].l)); }
#line 11612 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 651:
#line 3440 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11618 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 652:
#line 3441 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11624 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 653:
#line 3445 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, append_symbol(L(), (yyvsp[0].sym))); }
#line 11630 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 654:
#line 3446 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_ROLLUP, (yyvsp[-1].l)); }
#line 11636 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 655:
#line 3447 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CUBE, (yyvsp[-1].l)); }
#line 11642 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 656:
#line 3448 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_GROUPING_SETS, (yyvsp[-1].l)); }
#line 11648 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 657:
#line 3449 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, NULL); }
#line 11654 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 658:
#line 3453 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11660 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 659:
#line 3454 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11666 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 660:
#line 3458 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_COLUMN_GROUP, (yyvsp[-1].l)); }
#line 11672 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 661:
#line 3459 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_COLUMN, (yyvsp[0].l)); }
#line 11678 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 662:
#line 3463 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), _symbol_create_list(SQL_COLUMN,(yyvsp[0].l))); }
#line 11684 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 663:
#line 3464 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), _symbol_create_list(SQL_COLUMN,(yyvsp[0].l))); }
#line 11690 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 664:
#line 3468 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11696 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 665:
#line 3469 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 11702 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 666:
#line 3473 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, append_symbol(L(), (yyvsp[0].sym))); }
#line 11708 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 667:
#line 3474 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_ROLLUP, (yyvsp[-1].l)); }
#line 11714 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 668:
#line 3475 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CUBE, (yyvsp[-1].l)); }
#line 11720 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 669:
#line 3476 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_GROUPING_SETS, (yyvsp[-1].l)); }
#line 11726 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 670:
#line 3477 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_GROUPBY, NULL); }
#line 11732 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 671:
#line 3481 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11738 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 672:
#line 3482 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11744 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 673:
#line 3487 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_OR, l ); }
#line 11753 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 674:
#line 3491 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11759 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 675:
#line 3496 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_AND, l ); }
#line 11768 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 676:
#line 3500 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11774 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 677:
#line 3504 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11780 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 678:
#line 3506 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_ORDERBY, (yyvsp[0].l)); }
#line 11786 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 679:
#line 3510 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11792 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 680:
#line 3511 "sql_parser.y" /* yacc.c:1646  */
    { 
		  	  sql_subtype *t = sql_bind_localtype("lng");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].l_val))); 
			}
#line 11801 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 681:
#line 3515 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11807 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 682:
#line 3519 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11813 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 683:
#line 3520 "sql_parser.y" /* yacc.c:1646  */
    { 
		  	  sql_subtype *t = sql_bind_localtype("lng");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].l_val))); 
			}
#line 11822 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 684:
#line 3524 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11828 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 685:
#line 3528 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11834 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 686:
#line 3529 "sql_parser.y" /* yacc.c:1646  */
    { 
		  	  sql_subtype *t = sql_bind_localtype("lng");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].l_val))); 
			}
#line 11843 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 687:
#line 3533 "sql_parser.y" /* yacc.c:1646  */
    { 
		  	  sql_subtype *t = sql_bind_localtype("dbl");
			  (yyval.sym) = _newAtomNode( atom_float(SA, t, strtod((yyvsp[0].sval), NULL)));
			}
#line 11852 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 688:
#line 3537 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11858 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 689:
#line 3541 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 11864 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 690:
#line 3542 "sql_parser.y" /* yacc.c:1646  */
    { 
		  	  sql_subtype *t = sql_bind_localtype("int");
			  (yyval.sym) = _newAtomNode( atom_int(SA, t, (yyvsp[0].i_val))); 
			}
#line 11873 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 691:
#line 3546 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11879 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 692:
#line 3550 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 11885 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 693:
#line 3552 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 11891 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 694:
#line 3557 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].bval) | (((yyvsp[0].bval) == -1 ? !(yyvsp[-1].bval) : (yyvsp[0].bval)) << 1));
	  (yyval.sym) = _symbol_create_list(SQL_COLUMN, l ); }
#line 11900 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 695:
#line 3564 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 11906 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 696:
#line 3565 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 11912 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 697:
#line 3566 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 11918 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 698:
#line 3570 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = -1; }
#line 11924 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 699:
#line 3571 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = TRUE; }
#line 11930 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 700:
#line 3572 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = FALSE; }
#line 11936 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 709:
#line 3587 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_NOT, (yyvsp[0].sym)); }
#line 11942 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 710:
#line 3588 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 11948 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 711:
#line 3592 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = -1; }
#line 11954 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 712:
#line 3593 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 11960 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 713:
#line 3594 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 11966 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 714:
#line 3595 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 11972 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 715:
#line 3600 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-3].sym));
		  append_string(l, (yyvsp[-2].sval));
		  append_symbol(l, (yyvsp[0].sym));
		  if ((yyvsp[-1].i_val) > -1)
		     append_int(l, (yyvsp[-1].i_val));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 11985 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 716:
#line 3609 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-3].sym));
		  append_string(l, sa_strdup(SA, "="));
		  append_symbol(l, (yyvsp[0].sym));
		  if ((yyvsp[-1].i_val) > -1)
		     append_int(l, (yyvsp[-1].i_val));
		  (yyval.sym) = _symbol_create_list(SQL_COMPARE, l ); }
#line 11998 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 717:
#line 3621 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_BETWEEN, l ); }
#line 12009 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 718:
#line 3628 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-5].sym));
		  append_int(l, (yyvsp[-3].i_val));
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  (yyval.sym) = _symbol_create_list(SQL_BETWEEN, l ); }
#line 12020 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 719:
#line 3637 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 12026 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 720:
#line 3638 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 12032 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 721:
#line 3639 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 12038 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 722:
#line 3644 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, FALSE);  /* case sensitive */
		  append_int(l, TRUE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12049 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 723:
#line 3651 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, TRUE);  /* case insensitive */
		  append_int(l, TRUE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12060 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 724:
#line 3658 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, FALSE);  /* case sensitive */
		  append_int(l, FALSE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12071 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 725:
#line 3665 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_symbol(l, (yyvsp[-2].sym));
		  append_symbol(l, (yyvsp[0].sym));
		  append_int(l, TRUE);  /* case insensitive */
		  append_int(l, FALSE);  /* anti */
		  (yyval.sym) = _symbol_create_list( SQL_LIKE, l ); }
#line 12082 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 726:
#line 3675 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[0].sym));
	  (yyval.sym) = _symbol_create_list(SQL_ESCAPE, l ); }
#line 12090 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 727:
#line 3679 "sql_parser.y" /* yacc.c:1646  */
    { const char *s = (yyvsp[0].sval);
	  if (_strlen(s) != 1) {
		sqlformaterror(m, SQLSTATE(22019) "%s", "ESCAPE must be one character");
		(yyval.sym) = NULL;
		YYABORT;
	  } else {
		dlist *l = L();
		append_symbol(l, (yyvsp[-2].sym));
		append_string(l, s);
		(yyval.sym) = _symbol_create_list(SQL_ESCAPE, l);
	  }
	}
#line 12107 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 728:
#line 3694 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol( SQL_IS_NOT_NULL, (yyvsp[-3].sym) );}
#line 12113 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 729:
#line 3695 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol( SQL_IS_NULL, (yyvsp[-2].sym) ); }
#line 12119 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 730:
#line 3700 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-4].sym));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_IN, l ); }
#line 12129 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 731:
#line 3706 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();

		  append_symbol(l, (yyvsp[-4].sym));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_IN, l ); }
#line 12139 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 732:
#line 3712 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-5].l));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_NOT_IN, l ); }
#line 12148 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 733:
#line 3717 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-5].l));
		  append_list(l, (yyvsp[-1].l));
		  (yyval.sym) = _symbol_create_list(SQL_IN, l ); }
#line 12157 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 734:
#line 3725 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 12163 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 735:
#line 3727 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12169 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 736:
#line 3733 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol( SQL_EXISTS, (yyvsp[0].sym) ); }
#line 12175 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 737:
#line 3737 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12181 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 738:
#line 3738 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym));  }
#line 12187 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 739:
#line 3742 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[-1].l); }
#line 12193 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 740:
#line 3747 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-2].l));
		  append_list(l, (yyvsp[-1].l));
		  append_list(l, (yyvsp[0].l));
		  (yyval.sym) = _symbol_create_list(SQL_FILTER, l ); }
#line 12203 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 741:
#line 3755 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 12209 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 742:
#line 3756 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 12215 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 743:
#line 3760 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 12221 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 744:
#line 3761 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 12227 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 746:
#line 3768 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_add")));
	  		  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12239 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 747:
#line 3776 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_sub")));
	  		  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12251 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 748:
#line 3784 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_mul")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12263 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 749:
#line 3792 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_div")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12275 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 750:
#line 3800 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "mod")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12287 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 751:
#line 3808 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_xor")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12299 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 752:
#line 3816 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_and")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
			  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12311 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 753:
#line 3824 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12323 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 754:
#line 3832 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_left")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12335 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 755:
#line 3840 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_right")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12347 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 756:
#line 3848 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_below")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12359 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 757:
#line 3856 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, append_string(L(), sa_strdup(SA, "mbr_below")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12370 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 758:
#line 3863 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_overlap_or_above")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12382 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 759:
#line 3871 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_above")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12394 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 760:
#line 3879 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_distance")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12406 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 761:
#line 3887 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_contained")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12418 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 762:
#line 3895 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_or")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12430 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 763:
#line 3903 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_contains")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12442 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 764:
#line 3911 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(L(), sa_strdup(SA, "mbr_equal")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12454 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 765:
#line 3919 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "bit_not")));
	  		  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_UNOP, l ); }
#line 12465 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 766:
#line 3926 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "left_shift")));
			  	append_int(l, FALSE); /* ignore distinct */
				append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12477 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 767:
#line 3934 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "right_shift")));
	  		   append_int(l, FALSE); /* ignore distinct */
			   append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12489 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 768:
#line 3942 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "left_shift_assign")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12501 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 769:
#line 3950 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l, 
			  	append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "right_shift_assign")));
				  append_int(l, FALSE); /* ignore distinct */
	  		  append_symbol(l, (yyvsp[-2].sym));
	  		  append_symbol(l, (yyvsp[0].sym));
	  		  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12513 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 770:
#line 3958 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 12519 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 771:
#line 3960 "sql_parser.y" /* yacc.c:1646  */
    { 
 			  (yyval.sym) = NULL;
			  assert(((yyvsp[0].sym)->token != SQL_COLUMN && (yyvsp[0].sym)->token != SQL_IDENT) || (yyvsp[0].sym)->data.lval->h->type != type_lng);
			  if (!(yyval.sym)) {
				dlist *l = L();
			  	append_list(l, 
			  		append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "sql_neg")));
	  		  	append_int(l, FALSE); /* ignore distinct */
				append_symbol(l, (yyvsp[0].sym));
	  		  	(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
			  }
			}
#line 12536 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 772:
#line 3972 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 12542 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 773:
#line 3976 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 12548 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 775:
#line 3981 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_WINDOW, append_list(L(), (yyvsp[-1].l))); }
#line 12554 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 776:
#line 3982 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(L(), (yyvsp[0].sval))); }
#line 12560 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 777:
#line 3983 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 12566 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 779:
#line 3988 "sql_parser.y" /* yacc.c:1646  */
    {
	 								if ((yyvsp[0].sym) && (yyvsp[0].sym)->token == SQL_NAME)
										(yyval.sym) = _symbol_create_list(SQL_WINDOW, append_string(append_symbol(L(), (yyvsp[-1].sym)), (yyvsp[0].sym)->data.lval->h->data.sval));
									else if ((yyvsp[0].sym))
										(yyval.sym) = _symbol_create_list(SQL_WINDOW, append_list(append_symbol(L(), (yyvsp[-1].sym)), (yyvsp[0].sym)->data.lval->h->data.lval));
									else
										(yyval.sym) = (yyvsp[-1].sym);
 								}
#line 12579 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 782:
#line 3998 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_COLUMN, (yyvsp[0].l)); }
#line 12585 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 783:
#line 3999 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_user"))); }
#line 12591 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 784:
#line 4000 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_schema"))); }
#line 12597 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 785:
#line 4001 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_role"))); }
#line 12603 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 786:
#line 4002 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NAME, append_string(append_string(L(), sa_strdup(SA, "sys")), sa_strdup(SA, "current_timezone"))); }
#line 12609 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 788:
#line 4004 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
										    append_list(l, append_string(L(), "grouping"));
											append_int(l, FALSE); /* ignore distinct */
											for (dnode *dn = (yyvsp[-1].l)->h ; dn ; dn = dn->next) {
												symbol *sym = dn->data.sym; /* do like a aggrN */
												append_symbol(l, _symbol_create_list(SQL_COLUMN, sym->data.lval));
											}
										    (yyval.sym) = _symbol_create_list(SQL_AGGR, l); }
#line 12622 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 789:
#line 4012 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NEXT, (yyvsp[0].l)); }
#line 12628 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 794:
#line 4021 "sql_parser.y" /* yacc.c:1646  */
    { 
	  int nr = (m->params)?list_length(m->params):0;

	  sql_add_param(m, NULL, NULL);
	  (yyval.sym) = _symbol_create_int( SQL_PARAMETER, nr ); 
	}
#line 12639 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 795:
#line 4030 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(append_symbol(append_symbol(append_string(L(), (yyvsp[-3].sval)), (yyvsp[-2].sym)), (yyvsp[-1].sym)), (yyvsp[0].sym)); }
#line 12645 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 796:
#line 4034 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 12651 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 797:
#line 4035 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12657 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 798:
#line 4039 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 12663 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 799:
#line 4040 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 12669 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 800:
#line 4044 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 12675 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 801:
#line 4046 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_GROUPBY, (yyvsp[0].l) ); }
#line 12681 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 802:
#line 4050 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 12687 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 803:
#line 4052 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_ORDERBY, (yyvsp[0].l) ); }
#line 12693 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 804:
#line 4056 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 12699 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 805:
#line 4058 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_FRAME, append_int(append_int((yyvsp[-1].l), (yyvsp[-2].i_val)), (yyvsp[0].i_val))); }
#line 12705 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 806:
#line 4062 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = FRAME_ROWS; }
#line 12711 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 807:
#line 4063 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = FRAME_RANGE; }
#line 12717 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 808:
#line 4064 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = FRAME_GROUPS; }
#line 12723 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 809:
#line 4068 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L(); append_symbol(l, (yyvsp[0].sym));
                            symbol *s = _symbol_create_int( SQL_FOLLOWING, CURRENT_ROW_BOUND);
                            dlist *l2 = append_symbol(L(), s);
                            symbol *sym = _symbol_create_list( SQL_CURRENT_ROW, l2);
                            append_symbol(l, sym);
                            (yyval.l) = l; }
#line 12734 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 810:
#line 4074 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = (yyvsp[0].l); }
#line 12740 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 811:
#line 4078 "sql_parser.y" /* yacc.c:1646  */
    { symbol *s = _symbol_create_int( SQL_PRECEDING, UNBOUNDED_PRECEDING_BOUND);
                            dlist *l2 = append_symbol(L(), s);
                            (yyval.sym) = _symbol_create_list( SQL_PRECEDING, l2); }
#line 12748 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 812:
#line 4081 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l2 = append_symbol(L(), (yyvsp[-1].sym));
                            (yyval.sym) = _symbol_create_list( SQL_PRECEDING, l2); }
#line 12755 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 813:
#line 4083 "sql_parser.y" /* yacc.c:1646  */
    { symbol *s = _symbol_create_int( SQL_PRECEDING, CURRENT_ROW_BOUND);
                            dlist *l = append_symbol(L(), s);
                            (yyval.sym) = _symbol_create_list( SQL_CURRENT_ROW, l); }
#line 12763 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 816:
#line 4094 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(append_symbol(L(), (yyvsp[-2].sym)), (yyvsp[0].sym)); }
#line 12769 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 817:
#line 4098 "sql_parser.y" /* yacc.c:1646  */
    { symbol *s = _symbol_create_int( SQL_FOLLOWING, UNBOUNDED_FOLLOWING_BOUND);
                            dlist *l2 = append_symbol(L(), s);
                            (yyval.sym) = _symbol_create_list( SQL_FOLLOWING, l2); }
#line 12777 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 818:
#line 4101 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l2 = append_symbol(L(), (yyvsp[-1].sym));
                            (yyval.sym) = _symbol_create_list( SQL_FOLLOWING, l2); }
#line 12784 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 819:
#line 4106 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_NONE; }
#line 12790 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 820:
#line 4107 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_CURRENT_ROW; }
#line 12796 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 821:
#line 4108 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_GROUP; }
#line 12802 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 822:
#line 4109 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_TIES; }
#line 12808 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 823:
#line 4110 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = EXCLUDE_NONE; }
#line 12814 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 824:
#line 4115 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_list(l, (yyvsp[-2].l));
      append_int(l, FALSE); /* ignore distinct */
	  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 12823 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 825:
#line 4120 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_list(l, (yyvsp[-3].l));
	  append_int(l, FALSE); /* ignore distinct */
	  if (dlist_length((yyvsp[-1].l)) == 1) {
  	  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
	  	(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
	  } else if (dlist_length((yyvsp[-1].l)) == 2) {
  	  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
  	  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
	  	(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
	  } else {
  	  	append_list(l, (yyvsp[-1].l));
	  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
	  }
	}
#line 12843 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 826:
#line 4138 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 12849 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 827:
#line 4139 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
					append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 12856 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 828:
#line 4144 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 12862 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 829:
#line 4145 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "left"); }
#line 12868 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 830:
#line 4146 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "right"); }
#line 12874 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 831:
#line 4147 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "insert"); }
#line 12880 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 832:
#line 4152 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  const char *ident = datetime_field((itype)(yyvsp[-3].i_val));
			  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, ident)));
  		  	  append_int(l, FALSE); /* ignore distinct */
			  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_UNOP, l ); }
#line 12892 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 833:
#line 4160 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_date")));
			 append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 12902 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 834:
#line 4166 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_time")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 12912 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 835:
#line 4172 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "current_timestamp")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 12922 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 836:
#line 4178 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "localtime")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 12932 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 837:
#line 4184 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  append_list(l,
			  	append_string(L(), sa_strdup(SA, "localtimestamp")));
			  append_int(l, FALSE); /* ignore distinct */
	  		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 12942 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 838:
#line 4192 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 12948 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 839:
#line 4193 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 12954 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 840:
#line 4198 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
				append_string(L(), sa_strdup(SA, "substring")));
			  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 12969 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 841:
#line 4209 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
			append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 12984 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 842:
#line 4220 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 12996 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 843:
#line 4228 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "substring")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13008 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 844:
#line 4236 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "locate")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-3].sym));
  		  	  append_symbol(l, (yyvsp[-1].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13020 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 845:
#line 4244 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  	  append_list(l,
  		  	  	append_string(L(), sa_strdup(SA, "concat")));
					  append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(l, (yyvsp[-2].sym));
  		  	  append_symbol(l, (yyvsp[0].sym));
		  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 13032 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 846:
#line 4252 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
			  dlist *ops = L();
  		  	  append_list(l,
				append_string(L(), sa_strdup(SA, "splitpart")));
				append_int(l, FALSE); /* ignore distinct */
  		  	  append_symbol(ops, (yyvsp[-5].sym));
  		  	  append_symbol(ops, (yyvsp[-3].sym));
  		  	  append_symbol(ops, (yyvsp[-1].sym));
			  append_list(l, ops);
		  	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 13047 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 847:
#line 4265 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym) ); }
#line 13053 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 848:
#line 4267 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym) ); }
#line 13059 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 849:
#line 4272 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_string(l, NULL);
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 13068 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 850:
#line 4277 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_string(l, (yyvsp[-2].sval));
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 13077 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 851:
#line 4282 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_symbol(l, (yyvsp[-2].sym));
  		  append_string(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_TABLE, l ); }
#line 13086 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 852:
#line 4287 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_symbol(l, (yyvsp[-1].sym));
  		  append_string(l, (yyvsp[0].sval));
  		  (yyval.sym) = _symbol_create_list( SQL_COLUMN, l ); }
#line 13095 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 853:
#line 4294 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 13101 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 854:
#line 4295 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 13107 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 855:
#line 4296 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 13113 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 856:
#line 4301 "sql_parser.y" /* yacc.c:1646  */
    { 
		AtomNode *an = (AtomNode*)(yyvsp[0].sym);
		atom *a = an->a; 
		an->a = atom_dup(SA, a); 
		(yyval.sym) = (yyvsp[0].sym);
	}
#line 13124 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 857:
#line 4310 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 13130 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 858:
#line 4311 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
			  append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 13137 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 859:
#line 4317 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-2].l));
  		  append_int(l, FALSE); /* ignore distinct */
  		  append_list(l, NULL);
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13147 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 860:
#line 4323 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-3].l));
  		  append_int(l, FALSE); /* ignore distinct */
  		  append_list(l, (yyvsp[-1].l));
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13157 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 861:
#line 4329 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-4].l));
  		  append_int(l, TRUE);
  		  append_list(l, (yyvsp[-1].l));
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13167 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 862:
#line 4335 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-4].l));
  		  append_int(l, FALSE);
  		  append_list(l, (yyvsp[-1].l));
  		  (yyval.sym) = _symbol_create_list( SQL_RANK, l ); }
#line 13177 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 863:
#line 4341 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-3].l));
		  append_int(l, FALSE); /* ignore distinct */
  		  append_symbol(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 13187 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 864:
#line 4347 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-5].l));
		  append_int(l, FALSE); /* ignore distinct */
  		  append_symbol(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_AGGR, l ); }
#line 13197 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 865:
#line 4353 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  		  append_list(l, (yyvsp[-2].l));
		  append_int(l, FALSE); /* ignore distinct */
		  append_list(l, NULL);
		  (yyval.sym) = _symbol_create_list( SQL_OP, l ); }
#line 13207 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 866:
#line 4359 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-3].l));
		  append_int(l, FALSE); /* ignore distinct */
 		  if (dlist_length((yyvsp[-1].l)) == 1) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
		  } else if (dlist_length((yyvsp[-1].l)) == 2) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
		  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
		  } else {
		  	append_list(l, (yyvsp[-1].l));
		  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
		  }
		}
#line 13227 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 867:
#line 4375 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-4].l));
		  append_int(l, TRUE);
 		  if (dlist_length((yyvsp[-1].l)) == 1) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
		  } else if (dlist_length((yyvsp[-1].l)) == 2) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
		  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
		  } else {
		  	append_list(l, (yyvsp[-1].l));
		  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
		  }
		}
#line 13247 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 868:
#line 4391 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, (yyvsp[-4].l));
		  append_int(l, FALSE);
 		  if (dlist_length((yyvsp[-1].l)) == 1) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_UNOP, l ); 
		  } else if (dlist_length((yyvsp[-1].l)) == 2) {
		  	append_symbol(l, (yyvsp[-1].l)->h->data.sym);
		  	append_symbol(l, (yyvsp[-1].l)->h->next->data.sym);
			(yyval.sym) = _symbol_create_list( SQL_BINOP, l ); 
		  } else {
		  	append_list(l, (yyvsp[-1].l));
		  	(yyval.sym) = _symbol_create_list( SQL_NOP, l ); 
		  }
		}
#line 13267 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 870:
#line 4410 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 13273 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 871:
#line 4411 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = -1; }
#line 13279 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 872:
#line 4412 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 13285 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 873:
#line 4416 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 1; }
#line 13291 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 874:
#line 4417 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = 0; }
#line 13297 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 875:
#line 4428 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val)+1; }
#line 13303 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 876:
#line 4430 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0+1; }
#line 13309 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 877:
#line 4434 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[-1].i_val)+1; }
#line 13315 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 878:
#line 4436 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 6+1; }
#line 13321 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 879:
#line 4440 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "date", 0, 0); }
#line 13327 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 880:
#line 4442 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[0].bval))
				sql_find_subtype(&(yyval.type), "timetz", (yyvsp[-1].i_val), 0); 
			  else
				sql_find_subtype(&(yyval.type), "time", (yyvsp[-1].i_val), 0); 
			}
#line 13337 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 881:
#line 4448 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[0].bval))
				sql_find_subtype(&(yyval.type), "timestamptz", (yyvsp[-1].i_val), 0); 
			  else
				sql_find_subtype(&(yyval.type), "timestamp", (yyvsp[-1].i_val), 0); 
			}
#line 13347 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 882:
#line 4456 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = iyear; }
#line 13353 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 883:
#line 4457 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = imonth; }
#line 13359 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 884:
#line 4458 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = iday; }
#line 13365 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 885:
#line 4459 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = ihour; }
#line 13371 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 886:
#line 4460 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = imin; }
#line 13377 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 888:
#line 4465 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = isec; }
#line 13383 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 890:
#line 4470 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = icentury; }
#line 13389 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 891:
#line 4471 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = idecade; }
#line 13395 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 892:
#line 4472 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = iquarter; }
#line 13401 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 893:
#line 4473 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = iweek; }
#line 13407 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 894:
#line 4474 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = idow; }
#line 13413 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 895:
#line 4476 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = idoy; }
#line 13419 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 896:
#line 4478 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = iepoch; }
#line 13425 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 897:
#line 4483 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[-1].i_val)), (yyvsp[0].i_val)-1);  }
#line 13432 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 898:
#line 4489 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[0].i_val)), 0);  }
#line 13439 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 899:
#line 4492 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), isec), (yyvsp[0].i_val)-1);  }
#line 13446 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 900:
#line 4498 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), (yyvsp[-1].i_val)), (yyvsp[0].i_val)-1);  }
#line 13453 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 901:
#line 4501 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_int(
			 	append_int( L(), isec), (yyvsp[0].i_val)-1);  }
#line 13460 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 902:
#line 4507 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) =  append_list(
			append_list( L(), (yyvsp[-2].l)), (yyvsp[0].l) ); }
#line 13467 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 903:
#line 4510 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) =  append_list( L(), (yyvsp[0].l)); }
#line 13473 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 904:
#line 4514 "sql_parser.y" /* yacc.c:1646  */
    {
		int sk, ek, sp, ep;
	  	int tpe;

		(yyval.type).type = NULL;
	  	if ( (tpe = parse_interval_qualifier( m, (yyvsp[0].l), &sk, &ek, &sp, &ep )) < 0){
			sqlformaterror(m, SQLSTATE(22006) "%s", "incorrect interval");
			YYABORT;
	  	} else {
			int d = inttype2digits(sk, ek);
			if (tpe == 0){
				sql_find_subtype(&(yyval.type), "month_interval", d, 0);
			} else if (d == 4) {
				sql_find_subtype(&(yyval.type), "day_interval", d, 0);
			} else {
				sql_find_subtype(&(yyval.type), "sec_interval", d, 0);
			}
	  	}
	}
#line 13497 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 914:
#line 4557 "sql_parser.y" /* yacc.c:1646  */
    { const char *s = (yyvsp[0].sval);
		  int len = UTF8_strlen(s);
		  sql_subtype t;
		  sql_find_subtype(&t, "char", len, 0 );
		  (yyval.sym) = _newAtomNode( _atom_string(&t, s)); }
#line 13507 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 915:
#line 4563 "sql_parser.y" /* yacc.c:1646  */
    { int len = _strlen((yyvsp[0].sval)), i = 2, err = 0;
		  char * hexa = (yyvsp[0].sval);
	 	  sql_subtype t;
#ifdef HAVE_HGE
		  hge res = 0;
#else
		  lng res = 0;
#endif
		  /* skip leading '0' */
		  while (i < len && hexa[i] == '0')
		  	i++;

		  /* we only support positive values that fit in a signed 128-bit type,
		   * i.e., max. 63/127 bit => < 2^63/2^127 => < 0x800...
		   * (leading sign (-0x...) is handled separately elsewhere)
		   */
		  if (len - i < MAX_HEX_DIGITS || (len - i == MAX_HEX_DIGITS && hexa[i] < '8'))
		  	while (err == 0 && i < len)
		  	{
				res <<= 4;
				if (isdigit((unsigned char) hexa[i]))
					res = res + (hexa[i] - '0');
				else if ('A' <= hexa[i] && hexa[i] <= 'F')
					res = res + (hexa[i] - 'A' + 10);
				else if ('a' <= hexa[i] && hexa[i] <= 'f')
					res = res + (hexa[i] - 'a' + 10);
				else
					err = 1;
		  		i++;
			}
		  else
			err = 1;

		  if (err == 0) {
		  	assert(res >= 0);

		  	/* use smallest type that can accommodate the given value */
			if (res <= GDK_bte_max)
				sql_find_subtype(&t, "tinyint", 8, 0 );
			else if (res <= GDK_sht_max)
				sql_find_subtype(&t, "smallint", 16, 0 );
		  	else if (res <= GDK_int_max)
				sql_find_subtype(&t, "int", 32, 0 );
			else if (res <= GDK_lng_max)
				sql_find_subtype(&t, "bigint", 64, 0 );
#ifdef HAVE_HGE
			else if (res <= GDK_hge_max)
				sql_find_subtype(&t, "hugeint", 128, 0 );
#endif
			else
				err = 1;
		  }

		  if (err != 0) {
			sqlformaterror(m, SQLSTATE(22003) "Invalid hexadecimal number or hexadecimal too large (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
			(yyval.sym) = _newAtomNode( atom_int(SA, &t, res));
		  }
		}
#line 13573 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 916:
#line 4625 "sql_parser.y" /* yacc.c:1646  */
    { int err = 0;
		  size_t len = sizeof(lng);
		  lng value, *p = &value;
		  sql_subtype t;

		  if (lngFromStr((yyvsp[0].sval), &len, &p, false) < 0 || is_lng_nil(value))
		  	err = 2;

		  if (!err) {
		    if (value >= (lng) GDK_oid_min && value <= (lng) GDK_oid_max)
#if SIZEOF_OID == SIZEOF_INT
		  	  sql_find_subtype(&t, "oid", 31, 0 );
#else
		  	  sql_find_subtype(&t, "oid", 63, 0 );
#endif
		    else
			  err = 1;
		  }

		  if (err) {
			sqlformaterror(m, SQLSTATE(22003) "OID value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode( atom_int(SA, &t, value));
		  }
		}
#line 13605 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 917:
#line 4653 "sql_parser.y" /* yacc.c:1646  */
    { int digits = _strlen((yyvsp[0].sval)), err = 0;
#ifdef HAVE_HGE
		  hge value, *p = &value;
		  size_t len = sizeof(hge);
		  const hge one = 1;
#else
		  lng value, *p = &value;
		  size_t len = sizeof(lng);
		  const lng one = 1;
#endif
		  sql_subtype t;

#ifdef HAVE_HGE
		  if (hgeFromStr((yyvsp[0].sval), &len, &p, false) < 0 || is_hge_nil(value))
		  	err = 2;
#else
		  if (lngFromStr((yyvsp[0].sval), &len, &p, false) < 0 || is_lng_nil(value))
		  	err = 2;
#endif

		  /* find the most suitable data type for the given number */
		  if (!err) {
		    int bits = (int) digits2bits(digits), obits = bits;

		    while (bits > 0 &&
			   (bits == sizeof(value) * 8 ||
			    (one << (bits - 1)) > value))
			  bits--;

 		    if (bits != obits &&
		       (bits == 8 || bits == 16 || bits == 32 || bits == 64))
				bits++;
		
		    if (value >= GDK_bte_min && value <= GDK_bte_max)
		  	  sql_find_subtype(&t, "tinyint", bits, 0 );
		    else if (value >= GDK_sht_min && value <= GDK_sht_max)
		  	  sql_find_subtype(&t, "smallint", bits, 0 );
		    else if (value >= GDK_int_min && value <= GDK_int_max)
		  	  sql_find_subtype(&t, "int", bits, 0 );
		    else if (value >= GDK_lng_min && value <= GDK_lng_max)
		  	  sql_find_subtype(&t, "bigint", bits, 0 );
#ifdef HAVE_HGE
		    else if (value >= GDK_hge_min && value <= GDK_hge_max)
		  	  sql_find_subtype(&t, "hugeint", bits, 0 );
#endif
		    else
			  err = 1;
		  }

		  if (err) {
			sqlformaterror(m, SQLSTATE(22003) "integer value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode( atom_int(SA, &t, value));
		  }
		}
#line 13667 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 918:
#line 4711 "sql_parser.y" /* yacc.c:1646  */
    { char *s = sa_strdup(SA, (yyvsp[0].sval));
			int digits;
			int scale;
			int has_errors;
			sql_subtype t;

			DEC_TPE value = decimal_from_str(s, &digits, &scale, &has_errors);

			if (!has_errors && digits <= MAX_DEC_DIGITS) {
				// The float-like value seems to fit in decimal storage
				sql_find_subtype(&t, "decimal", digits, scale );
				(yyval.sym) = _newAtomNode( atom_dec(SA, &t, value));
			}
			else {
				/*
				* The float-like value either doesn't fit in integer decimal storage
				* or it is not a valid float representation.
				*/
				char *p = (yyvsp[0].sval);
				double val;

				errno = 0;
				val = strtod((yyvsp[0].sval),&p);
				if (p == (yyvsp[0].sval) || is_dbl_nil(val) || (errno == ERANGE && (val < -1 || val > 1))) {
					sqlformaterror(m, SQLSTATE(22003) "Double value too large or not a number (%s)", (yyvsp[0].sval));
					(yyval.sym) = NULL;
					YYABORT;
				} else {
					sql_find_subtype(&t, "double", 51, 0 );
					(yyval.sym) = _newAtomNode(atom_float(SA, &t, val));
				}
		   }
		}
#line 13705 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 919:
#line 4745 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
  		  char *p = (yyvsp[0].sval);
		  double val;

		  errno = 0;
 		  val = strtod((yyvsp[0].sval),&p);
		  if (p == (yyvsp[0].sval) || is_dbl_nil(val) || (errno == ERANGE && (val < -1 || val > 1))) {
			sqlformaterror(m, SQLSTATE(22003) "Double value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  }
		  sql_find_subtype(&t, "double", 51, 0 );
		  (yyval.sym) = _newAtomNode(atom_float(SA, &t, val)); }
#line 13723 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 920:
#line 4759 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a;
		  int r;

 		  r = sql_find_subtype(&t, "date", 0, 0 );
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			sqlformaterror(m, SQLSTATE(22007) "Incorrect date value (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 13740 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 921:
#line 4772 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a;
		  int r;

	          r = sql_find_subtype(&t, ((yyvsp[-1].bval))?"timetz":"time", (yyvsp[-2].i_val), 0);
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			sqlformaterror(m, SQLSTATE(22007) "Incorrect time value (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 13757 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 922:
#line 4785 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a;
		  int r;

 		  r = sql_find_subtype(&t, ((yyvsp[-1].bval))?"timestamptz":"timestamp",(yyvsp[-2].i_val),0);
		  if (!r || (a = atom_general(SA, &t, (yyvsp[0].sval))) == NULL) {
			sqlformaterror(m, SQLSTATE(22007) "Incorrect timestamp value (%s)", (yyvsp[0].sval));
			(yyval.sym) = NULL;
			YYABORT;
		  } else {
		  	(yyval.sym) = _newAtomNode(a);
		} }
#line 13774 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 924:
#line 4799 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a= 0;
		  int r;

		  (yyval.sym) = NULL;
 		  r = sql_find_subtype(&t, "blob", 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			sqlformaterror(m, SQLSTATE(22M28) "incorrect blob %s", (yyvsp[0].sval));
			YYABORT;
		  }
		}
#line 13792 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 925:
#line 4813 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a= 0;
		  int r;

		  (yyval.sym) = NULL;
 		  r = sql_find_subtype(&t, "blob", 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			sqlformaterror(m, SQLSTATE(22M28) "incorrect blob %s", (yyvsp[0].sval));
			YYABORT;
		  }
		}
#line 13810 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 926:
#line 4827 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  atom *a= 0;
		  int r;

		  (yyval.sym) = NULL;
		  r = sql_find_subtype(&t, (yyvsp[-1].sval), 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			sqlformaterror(m, SQLSTATE(22000) "incorrect %s %s", (yyvsp[-1].sval), (yyvsp[0].sval));
			YYABORT;
		  }
		}
#line 13828 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 927:
#line 4841 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t; 
		  atom *a = 0;
		  int r;

		  (yyval.sym) = NULL;
		  r = sql_find_subtype(&t, (yyvsp[-1].sval), 0, 0);
	          if (r && (a = atom_general(SA, &t, (yyvsp[0].sval))) != NULL)
			(yyval.sym) = _newAtomNode(a);
		  if (!(yyval.sym)) {
			sqlformaterror(m, SQLSTATE(22000) "incorrect %s %s", (yyvsp[-1].sval), (yyvsp[0].sval));
			YYABORT;
		  }
		}
#line 13846 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 928:
#line 4855 "sql_parser.y" /* yacc.c:1646  */
    {
		  sql_type *t = mvc_bind_type(m, (yyvsp[-1].sval));
		  atom *a;

		  (yyval.sym) = NULL;
		  if (t) {
		  	sql_subtype tpe;
			sql_init_subtype(&tpe, t, 0, 0);
			a = atom_general(SA, &tpe, (yyvsp[0].sval));
			if (a)
				(yyval.sym) = _newAtomNode(a);
		  }
		  if (!t || !(yyval.sym)) {
			sqlformaterror(m, SQLSTATE(22000) "type (%s) unknown", (yyvsp[-1].sval));
			YYABORT;
		  }
		}
#line 13868 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 929:
#line 4873 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  sql_find_subtype(&t, "boolean", 0, 0 );
		  (yyval.sym) = _newAtomNode( atom_bool(SA, &t, FALSE)); }
#line 13876 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 930:
#line 4877 "sql_parser.y" /* yacc.c:1646  */
    { sql_subtype t;
		  sql_find_subtype(&t, "boolean", 0, 0 );
		  (yyval.sym) = _newAtomNode( atom_bool(SA, &t, TRUE)); }
#line 13884 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 931:
#line 4883 "sql_parser.y" /* yacc.c:1646  */
    { 
		sql_subtype t;
		int sk, ek, sp, ep, tpe;
	  	lng i = 0;
		int r = 0;

		(yyval.sym) = NULL;
	  	if ( (tpe = parse_interval_qualifier( m, (yyvsp[0].l), &sk, &ek, &sp, &ep )) < 0){
			yyerror(m, "incorrect interval");
			YYABORT;
	  	} else {
			int d = inttype2digits(sk, ek);
			if (tpe == 0){
				r=sql_find_subtype(&t, "month_interval", d, 0);
			} else if (d == 4) {
				r=sql_find_subtype(&t, "day_interval", d, 0);
			} else {
				r=sql_find_subtype(&t, "sec_interval", d, 0);
			}
	  	}
	  	if (!r || (tpe = parse_interval( m, (yyvsp[-2].i_val), (yyvsp[-1].sval), sk, ek, sp, ep, &i)) < 0) { 
			yyerror(m, "incorrect interval");
			(yyval.sym) = NULL;
			YYABORT;
	  	} else {
			/* count the number of digits in the input */
/*
			lng cpyval = i, inlen = 1;

			cpyval /= qualifier2multiplier(ek);
			while (cpyval /= 10)
				inlen++;
		    	if (inlen > t.digits) {
				sqlformaterror(m, SQLSTATE(22006) "incorrect interval (" LLFMT " > %d)", inlen, t.digits);
				$$ = NULL;
				YYABORT;
			}
*/
	  		(yyval.sym) = _newAtomNode( atom_int(SA, &t, i));
	  	}
	}
#line 13930 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 932:
#line 4929 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(L(), (yyvsp[0].sval)); }
#line 13936 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 933:
#line 4930 "sql_parser.y" /* yacc.c:1646  */
    {
				  m->scanner.schema = (yyvsp[-2].sval);
				  (yyval.l) = append_string(
					append_string(L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 13945 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 934:
#line 4934 "sql_parser.y" /* yacc.c:1646  */
    {
				  m->scanner.schema = (yyvsp[-4].sval);
				  (yyval.l) = append_string(
					append_string(
						append_string(L(), (yyvsp[-4].sval)), 
						(yyvsp[-2].sval)), 
					(yyvsp[0].sval))
				;}
#line 13958 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 935:
#line 4945 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				L(), (yyvsp[0].sval)); }
#line 13965 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 936:
#line 4948 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				append_string(
				 L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 13973 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 937:
#line 4953 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				append_string(
				 append_string(
				  L(), (yyvsp[-4].sval)), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 13982 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 938:
#line 4960 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				L(), (yyvsp[0].sval)); }
#line 13989 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 939:
#line 4963 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_string(
				append_string(
				 L(), (yyvsp[-2].sval)), (yyvsp[0].sval));}
#line 13997 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 940:
#line 4970 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_type(l, &(yyvsp[-1].type));
	  (yyval.sym) = _symbol_create_list( SQL_CAST, l ); }
#line 14006 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 941:
#line 4976 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-3].sym));
	  append_type(l, &(yyvsp[-1].type));
	  (yyval.sym) = _symbol_create_list( SQL_CAST, l ); }
#line 14015 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 942:
#line 4984 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_NULLIF,
		   append_symbol(
		    append_symbol(
		     L(), (yyvsp[-3].sym)), (yyvsp[-1].sym))); }
#line 14024 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 943:
#line 4989 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_COALESCE, (yyvsp[-1].l)); }
#line 14030 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 944:
#line 4991 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_symbol(
		    append_list(
		     append_symbol(
		      L(),(yyvsp[-3].sym)),(yyvsp[-2].l)),(yyvsp[-1].sym))); }
#line 14040 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 945:
#line 4997 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list(SQL_CASE,
		   append_symbol(
		    append_list(
		     L(),(yyvsp[-2].l)),(yyvsp[-1].sym))); }
#line 14049 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 946:
#line 5005 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[-2].sym));
			  (yyval.l) = append_symbol( (yyval.l), (yyvsp[0].sym));
			}
#line 14057 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 947:
#line 5009 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-2].l), (yyvsp[0].sym)); }
#line 14063 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 948:
#line 5014 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_symbol(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].sym))); }
#line 14072 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 949:
#line 5022 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym));}
#line 14078 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 950:
#line 5024 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 14084 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 951:
#line 5029 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_WHEN,
			   append_symbol(
			    append_symbol(
			     L(), (yyvsp[-2].sym)),(yyvsp[0].sym))); }
#line 14093 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 952:
#line 5037 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( L(), (yyvsp[0].sym)); }
#line 14099 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 953:
#line 5039 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol( (yyvsp[-1].l), (yyvsp[0].sym)); }
#line 14105 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 954:
#line 5043 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 14111 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 955:
#line 5044 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 14117 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 956:
#line 5051 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val);
		  if ((yyval.i_val) <= 0) {
			(yyval.i_val) = -1;
			yyerror(m, "Positive value greater than 0 expected");
			YYABORT;
		  }
		}
#line 14129 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 957:
#line 5062 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val);
		  if ((yyval.l_val) <= 0) {
			(yyval.l_val) = -1;
			yyerror(m, "Positive value greater than 0 expected");
			YYABORT;
		  }
		}
#line 14141 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 958:
#line 5072 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l_val) = (yyvsp[0].l_val);
		  if ((yyval.l_val) < 0) {
			(yyval.l_val) = -1;
			yyerror(m, "Positive value expected");
			YYABORT;
		  }
		}
#line 14153 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 959:
#line 5082 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val);
		  if ((yyval.i_val) < 0) {
			(yyval.i_val) = -1;
			yyerror(m, "Positive value expected");
			YYABORT;
		  }
		}
#line 14165 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 960:
#line 5093 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "char", 1, 0); }
#line 14171 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 961:
#line 5095 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.type).type = NULL;
			  yyerror(m, "CHARACTER VARYING needs a mandatory length specification");
			  YYABORT;
			}
#line 14180 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 962:
#line 5099 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "clob", 0, 0); }
#line 14186 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 963:
#line 5101 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "char", (yyvsp[-1].i_val), 0); }
#line 14192 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 964:
#line 5103 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "varchar", (yyvsp[-1].i_val), 0); }
#line 14198 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 965:
#line 5105 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "clob", (yyvsp[-1].i_val), 0);
			  /* NOTE: CLOB may be called as CLOB(2K) which is equivalent
			   *       to CLOB(2048).  Due to 'nonzero' it is not possible
			   *       to enter this as the parser rejects it.  However it
			   *       might be a ToDo for the future.
			   *       See p. 125 SQL-99
			   */
			}
#line 14211 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 966:
#line 5113 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "blob", 0, 0); }
#line 14217 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 967:
#line 5115 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "blob", (yyvsp[-1].i_val), 0);
			  /* NOTE: BLOB may be called as BLOB(2K) which is equivalent
			   *       to BLOB(2048).  Due to 'nonzero' it is not possible
			   *       to enter this as the parser rejects it.  However it
			   *       might be a ToDo for the future.
			   *       See p. 85 SQL-99
			   */
			}
#line 14230 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 968:
#line 5123 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "tinyint", 0, 0); }
#line 14236 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 969:
#line 5124 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "smallint", 0, 0); }
#line 14242 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 970:
#line 5125 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "int", 0, 0); }
#line 14248 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 971:
#line 5126 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "bigint", 0, 0); }
#line 14254 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 972:
#line 5127 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "hugeint", 0, 0); }
#line 14260 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 973:
#line 5129 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "decimal", 18, 3); }
#line 14266 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 974:
#line 5131 "sql_parser.y" /* yacc.c:1646  */
    { 
			  int d = (yyvsp[-1].i_val);
			  if (d > MAX_DEC_DIGITS) {
				sqlformaterror(m, SQLSTATE(22003) "Decimal of %d digits are not supported", d);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
			        sql_find_subtype(&(yyval.type), "decimal", d, 0); 
			  }
			}
#line 14281 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 975:
#line 5142 "sql_parser.y" /* yacc.c:1646  */
    { 
			  int d = (yyvsp[-3].i_val);
			  int s = (yyvsp[-1].i_val);
			  if (s > d || d > MAX_DEC_DIGITS) {
				if (s > d)
					sqlformaterror(m, SQLSTATE(22003) "Scale (%d) should be less or equal to the precision (%d)", s, d);
				else
					sqlformaterror(m, SQLSTATE(22003) "Decimal(%d,%d) isn't supported because P=%d > %d", d, s, d, MAX_DEC_DIGITS);
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_find_subtype(&(yyval.type), "decimal", d, s);
			  }
			}
#line 14300 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 976:
#line 5156 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 14306 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 977:
#line 5158 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].i_val) > 0 && (yyvsp[-1].i_val) <= 24) {
				sql_find_subtype(&(yyval.type), "real", (yyvsp[-1].i_val), 0);
			  } else if ((yyvsp[-1].i_val) > 24 && (yyvsp[-1].i_val) <= 53) {
				sql_find_subtype(&(yyval.type), "double", (yyvsp[-1].i_val), 0);
			  } else {
				sqlformaterror(m, SQLSTATE(22003) "Number of digits for FLOAT values should be between 1 and 53");
				(yyval.type).type = NULL;
				YYABORT;
			  }
			}
#line 14321 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 978:
#line 5169 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].i_val) >= (yyvsp[-3].i_val)) {
				sqlformaterror(m, SQLSTATE(22003) "Precision(%d) should be less than number of digits(%d)", (yyvsp[-1].i_val), (yyvsp[-3].i_val));
				(yyval.type).type = NULL;
				YYABORT;
			  } else if ((yyvsp[-3].i_val) > 0 && (yyvsp[-3].i_val) <= 24) {
				sql_find_subtype(&(yyval.type), "real", (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  } else if ((yyvsp[-3].i_val) > 24 && (yyvsp[-3].i_val) <= 53) {
				sql_find_subtype(&(yyval.type), "double", (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  } else {
				sqlformaterror(m, SQLSTATE(22003) "Number of digits for FLOAT values should be between 1 and 53");
				(yyval.type).type = NULL;
				YYABORT;
			  }
			}
#line 14340 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 979:
#line 5183 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 14346 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 980:
#line 5184 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "double", 0, 0); }
#line 14352 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 981:
#line 5185 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), "real", 0, 0); }
#line 14358 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 984:
#line 5188 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[0].sval), 0, 0); }
#line 14364 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 985:
#line 5190 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[-3].sval), (yyvsp[-1].i_val), 0); }
#line 14370 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 986:
#line 5191 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[0].sval), 0, 0); }
#line 14376 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 987:
#line 5193 "sql_parser.y" /* yacc.c:1646  */
    { sql_find_subtype(&(yyval.type), (yyvsp[-3].sval), (yyvsp[-1].i_val), 0); }
#line 14382 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 988:
#line 5195 "sql_parser.y" /* yacc.c:1646  */
    { if ((yyvsp[-1].i_val) >= (yyvsp[-3].i_val)) {
				sqlformaterror(m, SQLSTATE(22003) "Precision(%d) should be less than number of digits(%d)", (yyvsp[-1].i_val), (yyvsp[-3].i_val));
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
			 	sql_find_subtype(&(yyval.type), (yyvsp[-5].sval), (yyvsp[-3].i_val), (yyvsp[-1].i_val));
			  }
			}
#line 14395 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 989:
#line 5203 "sql_parser.y" /* yacc.c:1646  */
    {
			  sql_type *t = mvc_bind_type(m, (yyvsp[0].sval));
			  if (!t) {
				sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_init_subtype(&(yyval.type), t, 0, 0);
			  }
			}
#line 14410 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 990:
#line 5215 "sql_parser.y" /* yacc.c:1646  */
    {
			  sql_type *t = mvc_bind_type(m, (yyvsp[-3].sval));
			  if (!t) {
				sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-3].sval));
				(yyval.type).type = NULL;
				YYABORT;
			  } else {
				sql_init_subtype(&(yyval.type), t, (yyvsp[-1].i_val), 0);
			  }
			}
#line 14425 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 991:
#line 5225 "sql_parser.y" /* yacc.c:1646  */
    {
		if (!sql_find_subtype(&(yyval.type), "geometry", 0, 0 )) {
			sqlformaterror(m, "%s", SQLSTATE(22000) "type (geometry) unknown");
			(yyval.type).type = NULL;
			YYABORT;
		}
	}
#line 14437 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 992:
#line 5232 "sql_parser.y" /* yacc.c:1646  */
    {
		int geoSubType = (yyvsp[-1].i_val); 

		if(geoSubType == 0) {
			(yyval.type).type = NULL;
			YYABORT;
		} else if (!sql_find_subtype(&(yyval.type), "geometry", geoSubType, 0 )) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-3].sval));
			(yyval.type).type = NULL;
			YYABORT;
		}
		
	}
#line 14455 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 993:
#line 5245 "sql_parser.y" /* yacc.c:1646  */
    {
		int geoSubType = (yyvsp[-3].i_val); 
		int srid = (yyvsp[-1].i_val); 

		if(geoSubType == 0) {
			(yyval.type).type = NULL;
			YYABORT;
		} else if (!sql_find_subtype(&(yyval.type), "geometry", geoSubType, srid )) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[-5].sval));
			(yyval.type).type = NULL;
			YYABORT;
		}
	}
#line 14473 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 994:
#line 5258 "sql_parser.y" /* yacc.c:1646  */
    {
		if (!sql_find_subtype(&(yyval.type), "geometrya", 0, 0 )) {
			sqlformaterror(m, "%s", SQLSTATE(22000) "type (geometrya) unknown");
			(yyval.type).type = NULL;
			YYABORT;
		}
	}
#line 14485 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 995:
#line 5265 "sql_parser.y" /* yacc.c:1646  */
    {
	int geoSubType = find_subgeometry_type(m, (yyvsp[0].sval));

	if(geoSubType == 0) {
		(yyval.type).type = NULL;
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
		YYABORT;
	} else if (geoSubType == -1) {
		(yyval.type).type = NULL;
		sqlformaterror(m, SQLSTATE(HY013) "%s", "allocation failure");
		YYABORT;
	}  else if (!sql_find_subtype(&(yyval.type), "geometry", geoSubType, 0 )) {
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
		(yyval.type).type = NULL;
		YYABORT;
	}
}
#line 14507 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 996:
#line 5285 "sql_parser.y" /* yacc.c:1646  */
    {
	int subtype = find_subgeometry_type(m, (yyvsp[0].sval));
	char* geoSubType = (yyvsp[0].sval);

	if(subtype == 0) {
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", geoSubType);
		YYABORT;
	} else if(subtype == -1) {
		sqlformaterror(m, SQLSTATE(HY013) "%s", "allocation failure");
		YYABORT;
	} 
	(yyval.i_val) = subtype;	
}
#line 14525 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 997:
#line 5298 "sql_parser.y" /* yacc.c:1646  */
    {
	int subtype = find_subgeometry_type(m, (yyvsp[0].sval));
	char* geoSubType = (yyvsp[0].sval);

	if(subtype == 0) {
		sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", geoSubType);
		YYABORT;
	} else if (subtype == -1) {
		sqlformaterror(m, SQLSTATE(HY013) "%s", "allocation failure");
		YYABORT;
	} 
	(yyval.i_val) = subtype;	
}
#line 14543 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 998:
#line 5315 "sql_parser.y" /* yacc.c:1646  */
    { 	char *t = sql_bind_alias((yyvsp[0].sval));
	  	if (!t) {
			sqlformaterror(m, SQLSTATE(22000) "Type (%s) unknown", (yyvsp[0].sval));
			(yyval.sval) = NULL;
			YYABORT;
		}
		(yyval.sval) = t;
	}
#line 14556 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 999:
#line 5326 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14562 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1000:
#line 5327 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 14568 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1001:
#line 5331 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14574 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1002:
#line 5332 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14580 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1003:
#line 5333 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-2].sval); }
#line 14586 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1004:
#line 5336 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14592 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1005:
#line 5337 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-2].sval); }
#line 14598 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1008:
#line 5345 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14604 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1009:
#line 5347 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 14610 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1010:
#line 5348 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14616 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1011:
#line 5349 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14622 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1012:
#line 5350 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14628 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1013:
#line 5355 "sql_parser.y" /* yacc.c:1646  */
    {
		(yyval.sval) = (yyvsp[0].sval);
		if (!(yyvsp[0].sval) || _strlen((yyvsp[0].sval)) == 0) {
			sqlformaterror(m, SQLSTATE(42000) "An identifier cannot be empty");
			YYABORT;
		}
	}
#line 14640 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1014:
#line 5365 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14646 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1015:
#line 5367 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 14652 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1016:
#line 5368 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14658 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1017:
#line 5369 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14664 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1018:
#line 5370 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14670 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1019:
#line 5371 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 14676 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1021:
#line 5377 "sql_parser.y" /* yacc.c:1646  */
    {
		(yyval.sval) = (yyvsp[0].sval);
		if (!(yyvsp[0].sval) || _strlen((yyvsp[0].sval)) == 0) {
			sqlformaterror(m, SQLSTATE(42000) "An identifier cannot be empty");
			YYABORT;
		}
	}
#line 14688 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1022:
#line 5387 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "as"); }
#line 14694 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1023:
#line 5388 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "authorization"); }
#line 14700 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1024:
#line 5389 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "column"); }
#line 14706 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1025:
#line 5390 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "cycle"); }
#line 14712 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1026:
#line 5391 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "date"); }
#line 14718 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1027:
#line 5392 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "deallocate"); }
#line 14724 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1028:
#line 5393 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "distinct"); }
#line 14730 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1029:
#line 5394 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "exec"); }
#line 14736 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1030:
#line 5395 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "execute"); }
#line 14742 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1031:
#line 5396 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "filter"); }
#line 14748 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1032:
#line 5397 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "interval"); }
#line 14754 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1033:
#line 5398 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "language"); }
#line 14760 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1034:
#line 5399 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "large"); }
#line 14766 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1035:
#line 5400 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "match"); }
#line 14772 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1036:
#line 5401 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "no"); }
#line 14778 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1037:
#line 5402 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "precision"); }
#line 14784 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1038:
#line 5403 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "prepare"); }
#line 14790 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1039:
#line 5404 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "release"); }
#line 14796 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1040:
#line 5405 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "row"); }
#line 14802 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1041:
#line 5406 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "start"); }
#line 14808 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1042:
#line 5407 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "table"); }
#line 14814 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1043:
#line 5408 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "time"); }
#line 14820 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1044:
#line 5409 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "timestamp"); }
#line 14826 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1045:
#line 5410 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "uescape"); }
#line 14832 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1046:
#line 5411 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "value"); }
#line 14838 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1047:
#line 5413 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "action"); }
#line 14844 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1048:
#line 5414 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "analyze"); }
#line 14850 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1049:
#line 5415 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "auto_commit"); }
#line 14856 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1050:
#line 5416 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "cache"); }
#line 14862 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1051:
#line 5417 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "century"); }
#line 14868 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1052:
#line 5418 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "client"); }
#line 14874 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1053:
#line 5419 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "comment"); }
#line 14880 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1054:
#line 5420 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "data"); }
#line 14886 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1055:
#line 5421 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "decade"); }
#line 14892 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1056:
#line 5422 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "epoch"); }
#line 14898 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1057:
#line 5423 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "debug"); }
#line 14904 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1058:
#line 5424 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "diagnostics"); }
#line 14910 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1059:
#line 5425 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "explain"); }
#line 14916 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1060:
#line 5426 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "first"); }
#line 14922 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1061:
#line 5427 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "geometry"); }
#line 14928 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1062:
#line 5428 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "imprints"); }
#line 14934 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1063:
#line 5429 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "increment"); }
#line 14940 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1064:
#line 5430 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "key"); }
#line 14946 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1065:
#line 5431 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "last"); }
#line 14952 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1066:
#line 5432 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "level"); }
#line 14958 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1067:
#line 5433 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "maxvalue"); }
#line 14964 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1068:
#line 5434 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "MinMax"); }
#line 14970 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1069:
#line 5435 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "minvalue"); }
#line 14976 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1070:
#line 5436 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "name"); }
#line 14982 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1071:
#line 5437 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "nulls"); }
#line 14988 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1072:
#line 5438 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "object"); }
#line 14994 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1073:
#line 5439 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "options"); }
#line 15000 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1074:
#line 5440 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "password"); }
#line 15006 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1075:
#line 5441 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "path"); }
#line 15012 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1076:
#line 5442 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "plan"); }
#line 15018 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1077:
#line 5443 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "prep"); }
#line 15024 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1078:
#line 5444 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "privileges"); }
#line 15030 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1079:
#line 5445 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "quarter"); }
#line 15036 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1080:
#line 5446 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "replace"); }
#line 15042 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1081:
#line 5447 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "role"); }
#line 15048 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1082:
#line 5448 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "schema"); }
#line 15054 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1083:
#line 5449 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "server"); }
#line 15060 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1084:
#line 5450 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "session"); }
#line 15066 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1085:
#line 5451 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "size"); }
#line 15072 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1086:
#line 5452 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "statement"); }
#line 15078 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1087:
#line 5453 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "storage"); }
#line 15084 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1088:
#line 5454 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "temp"); }
#line 15090 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1089:
#line 5455 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "temporary"); }
#line 15096 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1090:
#line 5456 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "text"); }
#line 15102 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1091:
#line 5457 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "trace"); }
#line 15108 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1092:
#line 5458 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "type"); }
#line 15114 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1093:
#line 5459 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "week"); }
#line 15120 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1094:
#line 5460 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "dow"); }
#line 15126 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1095:
#line 5461 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "doy"); }
#line 15132 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1096:
#line 5462 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "zone"); }
#line 15138 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1097:
#line 5465 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "absent"); }
#line 15144 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1098:
#line 5466 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "according"); }
#line 15150 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1099:
#line 5467 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "content"); }
#line 15156 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1100:
#line 5468 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "document"); }
#line 15162 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1101:
#line 5469 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "element"); }
#line 15168 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1102:
#line 5470 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "empty"); }
#line 15174 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1103:
#line 5471 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "id"); }
#line 15180 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1104:
#line 5472 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "location"); }
#line 15186 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1105:
#line 5473 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "namespace"); }
#line 15192 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1106:
#line 5474 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "nil"); }
#line 15198 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1107:
#line 5475 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "passing"); }
#line 15204 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1108:
#line 5476 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "ref"); }
#line 15210 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1109:
#line 5477 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "returning"); }
#line 15216 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1110:
#line 5478 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "strip"); }
#line 15222 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1111:
#line 5479 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "uri"); }
#line 15228 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1112:
#line 5480 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strdup(SA, "whitespace"); }
#line 15234 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1113:
#line 5485 "sql_parser.y" /* yacc.c:1646  */
    {
		  char *end = NULL, *s = (yyvsp[0].sval);
		  int l = _strlen(s);
		  // errno might be non-zero due to other people's code
		  errno = 0;
		  if (l <= 19) {
		  	(yyval.l_val) = strtoll(s,&end,10);
		  } else {
			(yyval.l_val) = 0;
		  }
		  if (s+l != end || errno == ERANGE) {
			errno = 0;
			sqlformaterror(m, SQLSTATE(22003) "Integer value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.l_val) = 0;
			YYABORT;
		  }
		}
#line 15256 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1114:
#line 5504 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15262 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1115:
#line 5505 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 15268 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1116:
#line 5510 "sql_parser.y" /* yacc.c:1646  */
    {
		  char *end = NULL, *s = (yyvsp[0].sval);
		  int l = _strlen(s);
		  // errno might be non-zero due to other people's code
		  errno = 0;
		  if (l <= 10) {
		  	(yyval.i_val) = strtol(s,&end,10);
		  } else {
			(yyval.i_val) = 0;
		  }
		  if (s+l != end || errno == ERANGE) {
			errno = 0;
			sqlformaterror(m, SQLSTATE(22003) "Integer value too large or not a number (%s)", (yyvsp[0].sval));
			(yyval.i_val) = 0;
			YYABORT;
		  }
		}
#line 15290 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1117:
#line 5530 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = "\\"; }
#line 15296 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1118:
#line 5532 "sql_parser.y" /* yacc.c:1646  */
    { char *s = (yyvsp[0].sval);
		  if (strlen(s) != 1 || strchr("\"'0123456789abcdefABCDEF+ \t\n\r\f", *s) != NULL) {
			sqlformaterror(m, SQLSTATE(22019) "%s", "UESCAPE must be one character");
			(yyval.sval) = NULL;
			YYABORT;
		  } else {
			(yyval.sval) = s;
		  }
		}
#line 15310 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1119:
#line 5544 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15316 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1120:
#line 5546 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strconcat(SA, (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 15322 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1121:
#line 5551 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15328 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1122:
#line 5553 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strconcat(SA, (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 15334 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1123:
#line 5558 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15340 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1124:
#line 5560 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = sa_strconcat(SA, (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 15346 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1125:
#line 5564 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15352 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1126:
#line 5566 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = uescape_xform((yyvsp[-1].sval), (yyvsp[0].sval));
		  if ((yyval.sval) == NULL) {
			sqlformaterror(m, SQLSTATE(22019) "%s", "Bad Unicode string");
			YYABORT;
		  }
		}
#line 15363 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1127:
#line 5576 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_symbol(SQL_CALL, (yyvsp[0].sym)); }
#line 15369 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1128:
#line 5580 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 15375 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1129:
#line 5581 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = -1; }
#line 15381 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1130:
#line 5586 "sql_parser.y" /* yacc.c:1646  */
    {
		  m->emode = m_deallocate;
		  (yyval.sym) = _newAtomNode(atom_int(SA, sql_bind_localtype("int"), (yyvsp[0].i_val))); }
#line 15389 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1131:
#line 5593 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_int(l, (yyvsp[-2].i_val));
	  append_int(l, FALSE); /* ignore distinct */
  	  append_list(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 15399 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1132:
#line 5599 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
  	  append_int(l, (yyvsp[-3].i_val));
  	  append_int(l, FALSE); /* ignore distinct */
  	  append_list(l, (yyvsp[-1].l));
	  (yyval.sym) = _symbol_create_list( SQL_NOP, l ); }
#line 15409 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1133:
#line 5614 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 15415 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1135:
#line 5619 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_PATH, (yyvsp[0].l)); }
#line 15421 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1137:
#line 5626 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COMMENT, l );
	}
#line 15431 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1138:
#line 5632 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_string(l, NULL);
	  (yyval.sym) = _symbol_create_list( SQL_COMMENT, l );
	}
#line 15441 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1139:
#line 5640 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create( SQL_SCHEMA, (yyvsp[0].sval) ); }
#line 15447 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1140:
#line 5641 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_TABLE, (yyvsp[0].l) ); }
#line 15453 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1141:
#line 5642 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_VIEW, (yyvsp[0].l) ); }
#line 15459 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1142:
#line 5644 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COLUMN, l );
	}
#line 15469 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1143:
#line 5650 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-4].sval));
	  append_string(l, (yyvsp[-2].sval));
	  append_string(l, (yyvsp[0].sval));
	  (yyval.sym) = _symbol_create_list( SQL_COLUMN, l );
	}
#line 15480 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1144:
#line 5656 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_INDEX, (yyvsp[0].l) ); }
#line 15486 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1145:
#line 5657 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_SEQUENCE, (yyvsp[0].l) ); }
#line 15492 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1146:
#line 5658 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = _symbol_create_list( SQL_ROUTINE, (yyvsp[0].l) ); }
#line 15498 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1148:
#line 5667 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 15504 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1149:
#line 5669 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 15510 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1161:
#line 5691 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLCOMMENT, l); }
#line 15519 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1162:
#line 5699 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLCONCAT, l); }
#line 15528 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1163:
#line 5707 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLDOCUMENT, l); }
#line 15537 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1164:
#line 5717 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_list(l, (yyvsp[-2].l));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLELEMENT, l);
	}
#line 15548 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1165:
#line 5727 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = NULL; }
#line 15554 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1166:
#line 5729 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym));
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 15562 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1167:
#line 5733 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-2].sym));
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[0].sym));
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 15570 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1168:
#line 5737 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-4].sym));
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[-2].sym));
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 15578 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1169:
#line 5741 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-2].sym));
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 15586 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1170:
#line 5745 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[0].sym));
	  (yyval.l) = append_list((yyval.l), NULL); }
#line 15594 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1171:
#line 5749 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), (yyvsp[-2].sym));
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 15602 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1172:
#line 5753 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), NULL);
	  (yyval.l) = append_symbol((yyval.l), NULL);
	  (yyval.l) = append_list((yyval.l), (yyvsp[0].l)); }
#line 15610 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1174:
#line 5763 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 15616 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1175:
#line 5767 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 15622 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1176:
#line 5769 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, 
		  	append_string(L(), sa_strdup(SA, "concat")));
	  	  append_symbol(l, (yyvsp[-2].sym));
	  	  append_symbol(l, (yyvsp[0].sym));
	  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 15633 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1177:
#line 5779 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[0].sval));
	  append_symbol(l, (yyvsp[-1].sym));
	  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 15642 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1178:
#line 5786 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 15648 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1179:
#line 5787 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15654 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1182:
#line 5800 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = L();
		  (yyval.l) = append_list((yyval.l), (yyvsp[-1].l));
		  (yyval.l) = append_int((yyval.l), (yyvsp[0].i_val)); 	}
#line 15662 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1183:
#line 5807 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[0].sym)); }
#line 15668 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1184:
#line 5809 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol((yyvsp[-2].l), (yyvsp[0].sym)); }
#line 15674 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1186:
#line 5817 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 15680 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1187:
#line 5818 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = (yyvsp[0].i_val); }
#line 15686 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1188:
#line 5822 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 15692 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1189:
#line 5823 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 15698 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1190:
#line 5824 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 15704 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1191:
#line 5825 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 3; }
#line 15710 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1192:
#line 5826 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 4; }
#line 15716 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1193:
#line 5833 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-4].sym));
	  append_list(l, (yyvsp[-3].l));
	  append_int(l, (yyvsp[-2].i_val));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLFOREST, l);
	}
#line 15728 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1194:
#line 5843 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 15734 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1195:
#line 5844 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 15740 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1196:
#line 5849 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list(L(), (yyvsp[0].l)); }
#line 15746 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1197:
#line 5851 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_list((yyvsp[-2].l), (yyvsp[0].l)); }
#line 15752 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1198:
#line 5856 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.l) = append_symbol(L(), (yyvsp[-1].sym));
		  (yyval.l) = append_string((yyval.l), (yyvsp[0].sval)); }
#line 15759 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1199:
#line 5861 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 15765 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1200:
#line 5865 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 15771 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1201:
#line 5866 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15777 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1202:
#line 5870 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 15783 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1203:
#line 5877 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_int(l, (yyvsp[-3].i_val) );
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLPARSE, l); }
#line 15793 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1204:
#line 5884 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 15799 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1205:
#line 5885 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 15805 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1206:
#line 5892 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_string(l, (yyvsp[-3].sval));
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLPI, l); }
#line 15815 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1208:
#line 5904 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 15821 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1209:
#line 5906 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 15827 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1210:
#line 5917 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 15833 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1225:
#line 5963 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  append_symbol(l, (yyvsp[-2].sym));
	  append_int(l, (yyvsp[-1].i_val));
	  (yyval.sym) = _symbol_create_list( SQL_XMLTEXT, l); }
#line 15842 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1226:
#line 5974 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 15848 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1228:
#line 5979 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 2; }
#line 15854 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1229:
#line 5983 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 15860 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1230:
#line 5984 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 15866 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1231:
#line 5988 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 15872 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1232:
#line 5989 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 0; }
#line 15878 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1233:
#line 5990 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.i_val) = 1; }
#line 15884 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1234:
#line 6005 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[-1].sym); }
#line 15890 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1235:
#line 6009 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = (yyvsp[0].sym); }
#line 15896 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1236:
#line 6011 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
		  append_list(l, 
		  	append_string(L(), sa_strdup(SA, "concat")));
	  	  append_symbol(l, (yyvsp[-2].sym));
	  	  append_symbol(l, (yyvsp[0].sym));
	  	  (yyval.sym) = _symbol_create_list( SQL_BINOP, l ); }
#line 15907 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1241:
#line 6034 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  			  append_string(l, sa_strconcat(SA, "xmlns:", (yyvsp[0].sval)));
	  			  append_symbol(l, (yyvsp[-2].sym));
	  			  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 15916 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1242:
#line 6041 "sql_parser.y" /* yacc.c:1646  */
    { dlist *l = L();
	  			  append_string(l, sa_strdup(SA, "xmlns" ));
	  			  append_symbol(l, (yyvsp[0].sym));
	  			  (yyval.sym) = _symbol_create_list( SQL_XMLATTRIBUTE, l ); }
#line 15925 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1243:
#line 6045 "sql_parser.y" /* yacc.c:1646  */
    { (yyval.sym) = NULL; }
#line 15931 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;

  case 1273:
#line 6140 "sql_parser.y" /* yacc.c:1646  */
    { 
          dlist *aggr = L();

          if ((yyvsp[-2].sym)) {
	  	if ((yyvsp[-3].sym) != NULL && (yyvsp[-3].sym)->token == SQL_SELECT) {
			SelectNode *s = (SelectNode*)(yyvsp[-3].sym);
	
			s->orderby = (yyvsp[-2].sym);
	  	} else {
			yyerror(m, "ORDER BY: missing select operator");
			YYABORT;
		}
	  }
	  append_list(aggr, append_string(append_string(L(), "sys"), "xmlagg"));
	  append_int(aggr, FALSE); /* ignore distinct */
	  append_symbol(aggr, (yyvsp[-3].sym));
	  /* int returning not used */
	  (yyval.sym) = _symbol_create_list( SQL_AGGR, aggr);
	}
#line 15955 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
    break;


#line 15959 "/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/sql/server/sql_parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (m, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (m, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, m);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, m);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (m, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, m);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, m);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 6161 "sql_parser.y" /* yacc.c:1906  */

int find_subgeometry_type(mvc *m, char* geoSubType) {
	int subType = 0;
	if(strcmp(geoSubType, "point") == 0 )
		subType = (1 << 2);
	else if(strcmp(geoSubType, "linestring") == 0)
		subType = (2 << 2);
	else if(strcmp(geoSubType, "polygon") == 0)
		subType = (4 << 2);
	else if(strcmp(geoSubType, "multipoint") == 0)
		subType = (5 << 2);
	else if(strcmp(geoSubType, "multilinestring") == 0)
		subType = (6 << 2);
	else if(strcmp(geoSubType, "multipolygon") == 0)
		subType = (7 << 2);
	else if(strcmp(geoSubType, "geometrycollection") == 0)
		subType = (8 << 2);
	else {
		size_t strLength = strlen(geoSubType);
		if(strLength > 0 ) {
			char *typeSubStr = SA_NEW_ARRAY(m->ta, char, strLength);
			char flag = geoSubType[strLength-1]; 

			if (typeSubStr == NULL) {
				return -1;
			}
			memcpy(typeSubStr, geoSubType, strLength-1);
			typeSubStr[strLength-1]='\0';
			if(flag == 'z' || flag == 'm' ) {
				subType = find_subgeometry_type(m, typeSubStr);
				if (subType == -1) {
					return -1;
				}
				if(flag == 'z')
					SET_Z(subType);
				if(flag == 'm')
					SET_M(subType);
			}
		}
	}
	return subType;	
}

char *token2string(tokens token)
{
	switch (token) {
	// Please keep this list sorted for easy of maintenance
#define SQL(TYPE) case SQL_##TYPE : return #TYPE
	SQL(AGGR);
	SQL(ALTER_SEQ);
	SQL(ALTER_TABLE);
	SQL(ALTER_USER);
	SQL(ANALYZE);
	SQL(AND);
	SQL(ASSIGN);
	SQL(ATOM);
	SQL(BETWEEN);
	SQL(BINCOPYFROM);
	SQL(BINOP);
	SQL(CACHE);
	SQL(CALL);
	SQL(CASE);
	SQL(CAST);
	SQL(CHARSET);
	SQL(CHECK);
	SQL(COALESCE);
	SQL(COLUMN);
	SQL(COLUMN_GROUP);
	SQL(COLUMN_OPTIONS);
	SQL(COMMENT);
	SQL(COMPARE);
	SQL(CONSTRAINT);
	SQL(COPYFROM);
	SQL(COPYLOADER);
	SQL(COPYTO);
	SQL(CREATE_FUNC);
	SQL(CREATE_INDEX);
	SQL(CREATE_ROLE);
	SQL(CREATE_SCHEMA);
	SQL(CREATE_SEQ);
	SQL(CREATE_TABLE);
	SQL(CREATE_TABLE_LOADER);
	SQL(CREATE_TRIGGER);
	SQL(CREATE_TYPE);
	SQL(CREATE_USER);
	SQL(CREATE_VIEW);
	SQL(CROSS);
	SQL(CUBE);
	SQL(CURRENT_ROW);
	SQL(CYCLE);
	SQL(DECLARE);
	SQL(DECLARE_TABLE);
	SQL(DEFAULT);
	SQL(DELETE);
	SQL(DROP_COLUMN);
	SQL(DROP_CONSTRAINT);
	SQL(DROP_DEFAULT);
	SQL(DROP_FUNC);
	SQL(DROP_INDEX);
	SQL(DROP_ROLE);
	SQL(DROP_SCHEMA);
	SQL(DROP_SEQ);
	SQL(DROP_TABLE);
	SQL(DROP_TRIGGER);
	SQL(DROP_TYPE);
	SQL(DROP_USER);
	SQL(DROP_VIEW);
	SQL(ELSE);
	SQL(ESCAPE);
	SQL(EXCEPT);
	SQL(EXECUTE);
	SQL(EXISTS);
	SQL(FILTER);
	SQL(FOLLOWING);
	SQL(FOREIGN_KEY);
	SQL(FRAME);
	SQL(FROM);
	SQL(FUNC);
	SQL(GRANT);
	SQL(GRANT_ROLES);
	SQL(GROUPBY);
	SQL(GROUPING_SETS);
	SQL(IDENT);
	SQL(IF);
	SQL(IN);
	SQL(INC);
	SQL(INDEX);
	SQL(INSERT);
	SQL(INTERSECT);
	SQL(IS_NOT_NULL);
	SQL(IS_NULL);
	SQL(JOIN);
	SQL(LIKE);
	SQL(MAXVALUE);
	SQL(MERGE);
	SQL(MERGE_MATCH);
	SQL(MERGE_NO_MATCH);
	SQL(MERGE_PARTITION);
	SQL(MINVALUE);
	SQL(MULSTMT);
	SQL(NAME);
	SQL(NEXT);
	SQL(NOP);
	SQL(NOT);
	SQL(NOT_BETWEEN);
	SQL(NOT_EXISTS);
	SQL(NOT_IN);
	SQL(NOT_LIKE);
	SQL(NOT_NULL);
	SQL(NULL);
	SQL(NULLIF);
	SQL(OP);
	SQL(OR);
	SQL(ORDERBY);
	SQL(PARAMETER);
	SQL(PARTITION_COLUMN);
	SQL(PARTITION_EXPRESSION);
	SQL(PARTITION_LIST);
	SQL(PARTITION_RANGE);
	SQL(PATH);
	SQL(PRECEDING);
	SQL(PREP);
	SQL(PRIMARY_KEY);
	SQL(PW_ENCRYPTED);
	SQL(PW_UNENCRYPTED);
	SQL(RANK);
	SQL(RENAME_COLUMN);
	SQL(RENAME_SCHEMA);
	SQL(RENAME_TABLE);
	SQL(RENAME_USER);
	SQL(RETURN);
	SQL(REVOKE);
	SQL(REVOKE_ROLES);
	SQL(ROLLUP);
	SQL(ROUTINE);
	SQL(SCHEMA);
	SQL(SELECT);
	SQL(SEQUENCE);
	SQL(SET);
	SQL(SET_TABLE_SCHEMA);
	SQL(START);
	SQL(STORAGE);
	SQL(TABLE);
	SQL(TRUNCATE);
	SQL(TYPE);
	SQL(UNION);
	SQL(UNIQUE);
	SQL(UNOP);
	SQL(UPDATE);
	SQL(USING);
	SQL(VALUES);
	SQL(VIEW);
	SQL(WHEN);
	SQL(WHILE);
	SQL(WINDOW);
	SQL(WITH);
	SQL(XMLATTRIBUTE);
	SQL(XMLCOMMENT);
	SQL(XMLCONCAT);
	SQL(XMLDOCUMENT);
	SQL(XMLELEMENT);
	SQL(XMLFOREST);
	SQL(XMLPARSE);
	SQL(XMLPI);
	SQL(XMLTEXT);
#define TR(TYPE) case TR_##TYPE : return #TYPE
	TR(COMMIT);
	TR(MODE);
	TR(RELEASE);
	TR(ROLLBACK);
	TR(SAVEPOINT);
	TR(START);
	// Please keep this list sorted for easy of maintenance
	}
	return "unknown";	/* just needed for broken compilers ! */
}

void *sql_error( mvc * sql, int error_code, char *format, ... )
{
	va_list	ap;

	va_start (ap,format);
	if (sql->errstr[0] == '\0' || error_code == 5)
		vsnprintf(sql->errstr, ERRSIZE-1, _(format), ap);
	if (!sql->session->status || error_code == 5)
		sql->session->status = -error_code;
	va_end (ap);
	return NULL;
}

static int 
sqlformaterror(mvc * sql, _In_z_ _Printf_format_string_ const char *format, ...)
{
	va_list	ap;
	const char *sqlstate = NULL;
	size_t len = 0;

	va_start (ap,format);
	if (format && strlen(format) > 6 && format[5] == '!') {
		/* sql state provided */
		sqlstate = NULL;
	} else {
		/* default: Syntax error or access rule violation */
		sqlstate = SQLSTATE(42000);
	}
	//assert(sql->scanner.errstr == NULL);
	if (sql->errstr[0] == '\0') {
		if (sqlstate)
			len += snprintf(sql->errstr+len, ERRSIZE-1-len, "%s", sqlstate);
		len += vsnprintf(sql->errstr+len, ERRSIZE-1-len, _(format), ap);
		snprintf(sql->errstr+len, ERRSIZE-1-len, " in: \"%.80s\"\n", QUERY(sql->scanner));
	}
	if (!sql->session->status)
		sql->session->status = -4;
	va_end (ap);
	return 1;
}

static int 
sqlerror(mvc * sql, const char *err)
{
	return sqlformaterror(sql, "%s", err);
}

static void *ma_alloc(sql_allocator *sa, size_t sz)
{
	return sa_alloc(sa, sz);
}
static void ma_free(void *p)
{
	(void)p;
}
