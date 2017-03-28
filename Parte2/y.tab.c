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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "jac.y" /* yacc.c:339  */

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "estruturas.h"
    #include "ast.h"

    void yyerror (const char *s);
    int yylex(void);

    /*importa as variaveis do lex*/
    extern int lineNum;
    extern int columnNum;
    extern char *yytext; 
    extern int yyleng;

    /*importa do lex mas para AST*/
    extern ARVORE raiz;
    

#line 88 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OCURV = 258,
    CCURV = 259,
    OBRACE = 260,
    CBRACE = 261,
    OSQUARE = 262,
    CSQUARE = 263,
    AND = 264,
    OR = 265,
    LT = 266,
    GT = 267,
    EQ = 268,
    NEQ = 269,
    LEQ = 270,
    GEQ = 271,
    PLUS = 272,
    MINUS = 273,
    STAR = 274,
    DIV = 275,
    MOD = 276,
    NOT = 277,
    ASSIGN = 278,
    SEMI = 279,
    COMMA = 280,
    BOOL = 281,
    CLASS = 282,
    DO = 283,
    DOTLENGTH = 284,
    DOUBLE = 285,
    ELSE = 286,
    IF = 287,
    INT = 288,
    PARSEINT = 289,
    PRINT = 290,
    PUBLIC = 291,
    RETURN = 292,
    STATIC = 293,
    STRING = 294,
    VOID = 295,
    WHILE = 296,
    BOOLLIT = 297,
    RESERVED = 298,
    ID = 299,
    DECLIT = 300,
    REALLIT = 301,
    STRLIT = 302,
    IFX = 303
  };
#endif
/* Tokens.  */
#define OCURV 258
#define CCURV 259
#define OBRACE 260
#define CBRACE 261
#define OSQUARE 262
#define CSQUARE 263
#define AND 264
#define OR 265
#define LT 266
#define GT 267
#define EQ 268
#define NEQ 269
#define LEQ 270
#define GEQ 271
#define PLUS 272
#define MINUS 273
#define STAR 274
#define DIV 275
#define MOD 276
#define NOT 277
#define ASSIGN 278
#define SEMI 279
#define COMMA 280
#define BOOL 281
#define CLASS 282
#define DO 283
#define DOTLENGTH 284
#define DOUBLE 285
#define ELSE 286
#define IF 287
#define INT 288
#define PARSEINT 289
#define PRINT 290
#define PUBLIC 291
#define RETURN 292
#define STATIC 293
#define STRING 294
#define VOID 295
#define WHILE 296
#define BOOLLIT 297
#define RESERVED 298
#define ID 299
#define DECLIT 300
#define REALLIT 301
#define STRLIT 302
#define IFX 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "jac.y" /* yacc.c:355  */

        char* string;   
        struct arvore *arv; /*definimos uma estrutura do tipo arvore*/

#line 229 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 246 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   328

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    56,    56,    60,    61,    62,    63,    66,    67,    71,
      72,    75,    78,    79,    83,    84,    87,    91,    92,    93,
      96,    97,   101,   102,   105,   108,   109,   110,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   130,   131,   134,   137,   138,   139,   143,   144,
     147,   148,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   178,   179
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OCURV", "CCURV", "OBRACE", "CBRACE",
  "OSQUARE", "CSQUARE", "AND", "OR", "LT", "GT", "EQ", "NEQ", "LEQ", "GEQ",
  "PLUS", "MINUS", "STAR", "DIV", "MOD", "NOT", "ASSIGN", "SEMI", "COMMA",
  "BOOL", "CLASS", "DO", "DOTLENGTH", "DOUBLE", "ELSE", "IF", "INT",
  "PARSEINT", "PRINT", "PUBLIC", "RETURN", "STATIC", "STRING", "VOID",
  "WHILE", "BOOLLIT", "RESERVED", "ID", "DECLIT", "REALLIT", "STRLIT",
  "IFX", "$accept", "Program", "Program_2", "FieldDecl", "comma_id",
  "MethodDecl", "MethodHeader", "MethodHeader_2", "MethodBody",
  "MethodBody_2", "FormalParams", "FormalParams_2", "VarDecl", "Type",
  "Statement", "Statement_2", "Assignment", "MethodInvocation",
  "MethodInvocation_2", "ParseArgs", "Expr2", "Expr", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -5,   -15,    30,    41,   -53,   -53,    14,    31,   -53,   -53,
      32,   -53,   -53,   -53,     9,   -53,   -53,   -53,    25,    72,
      34,    78,   -53,   -53,    79,    50,   151,    50,    12,    77,
      75,   -53,    42,    61,   -53,   -53,   -53,   173,    87,    95,
      99,   216,   100,    18,   -53,    63,   -53,    85,    86,    93,
     114,   -53,    80,   117,   -53,   -53,   -53,   188,    89,   225,
       4,   126,   105,   234,   234,   234,   -53,   -53,     5,   -53,
     -53,   -53,   -53,   -53,   272,   104,   225,    70,   225,   -53,
     -53,   -53,   -53,   -53,   -53,    88,   106,   -53,   -53,   130,
     133,   134,   135,   136,   137,   141,   142,    11,   -53,   -53,
     -53,   -53,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   -53,   149,   150,   -53,   -53,
     -53,    28,   -53,    21,   225,   173,   -53,   225,   131,   138,
     -53,   -53,   296,   285,    76,    76,   307,   307,    76,    76,
      24,    24,   -53,   -53,   -53,   173,   -53,     2,   -53,   115,
     154,   132,   153,   -53,   -53,   -53,   -53,   225,   -53,   140,
     173,   161,   -53,   -53,   -53,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     6,     0,     0,     2,     5,
       0,     3,     4,     8,     0,    25,    27,    26,     0,     0,
       0,     0,    19,    11,    10,    15,     0,    15,     0,     0,
       0,    14,     0,     0,    43,    16,    38,     0,     0,     0,
       0,     0,     0,     0,    17,     0,    18,     0,     0,     0,
       0,     7,     0,     0,    13,    23,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,    72,    70,    73,
      74,    77,    52,    53,    78,     0,     0,     0,     0,    10,
      35,    36,    37,    12,     9,     0,    20,    28,    42,     0,
       0,     0,     0,     0,     0,     0,     0,    70,    68,    69,
      67,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,     0,     0,    45,    49,
      44,     0,    21,     0,     0,     0,    51,     0,     0,     0,
      76,    75,    54,    55,    60,    58,    56,    61,    59,    57,
      62,    63,    64,    65,    66,     0,    47,     0,    24,     0,
       0,    29,     0,    34,    33,    31,    46,     0,    22,     0,
       0,     0,    48,    32,    30,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   -53,   -53,    90,   -53,   -53,   139,   -53,   -53,
     -53,   -53,   -53,   -10,   -34,   -53,   -26,   -25,   -53,   -24,
     -46,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    11,    28,    12,    19,    30,    23,    26,
      31,    86,    44,    32,    46,    57,    71,    72,   147,    73,
      74,    75
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    48,    49,    58,    20,    91,   156,    90,    77,    94,
      96,    47,    48,    49,    77,     7,    45,    98,    99,   100,
       8,    77,     1,    88,   116,   119,   120,   157,    78,     3,
       4,    47,    48,    49,   101,    15,    51,    52,     9,    16,
     101,    78,    17,   112,   113,   114,     5,    15,    92,    18,
      10,    16,   148,    52,    17,    13,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,    21,
      14,   117,   150,    62,   118,   152,    15,    22,    24,    54,
      16,    25,    27,    17,    53,    56,    55,    63,    64,    29,
      59,   151,    65,   110,   111,   112,   113,   114,    60,    47,
      48,    49,    61,    76,    39,   162,    95,    79,    62,    80,
      81,   155,    67,   149,    68,    69,    70,    82,    83,    47,
      48,    49,    63,    64,    84,    85,   164,    65,   115,    62,
      89,   123,   122,   124,    47,    48,    49,   125,   126,    39,
     128,   129,   127,    63,    64,   130,   131,    67,    65,    68,
      69,    70,    33,   145,   146,   153,    34,    35,   159,   158,
      39,   161,   154,   160,   163,   165,    50,     0,    67,   121,
      68,    69,    70,    93,    33,    36,     0,    15,    34,    37,
       0,    16,     0,    38,    17,    39,    40,     0,    41,    33,
       0,     0,    42,    34,    87,    43,     0,    36,     0,     0,
       0,    37,     0,     0,     0,    38,     0,    39,    40,     0,
      41,     0,    36,     0,    42,     0,    37,    43,     0,    62,
      38,     0,    39,    40,     0,    41,     0,     0,    62,    42,
       0,     0,    43,    63,    64,     0,     0,    62,    65,     0,
      66,     0,    63,    64,     0,     0,     0,    65,     0,     0,
      39,    63,    64,     0,     0,     0,    65,     0,    67,    39,
      68,    69,    70,     0,     0,     0,     0,    67,    39,    68,
      69,    70,     0,     0,     0,     0,    67,     0,    97,    69,
      70,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   102,     0,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   104,   105,
       0,     0,   108,   109,   110,   111,   112,   113,   114
};

static const yytype_int16 yycheck[] =
{
      26,    26,    26,    37,    14,     1,     4,    59,     3,    61,
      62,    37,    37,    37,     3,     1,    26,    63,    64,    65,
       6,     3,    27,    57,    76,    77,    78,    25,    23,    44,
       0,    57,    57,    57,    29,    26,    24,    25,    24,    30,
      29,    23,    33,    19,    20,    21,     5,    26,    44,    40,
      36,    30,    24,    25,    33,    24,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    44,
      38,     1,   124,     3,     4,   127,    26,     5,    44,     4,
      30,     3,     3,    33,     7,    24,    44,    17,    18,    39,
       3,   125,    22,    17,    18,    19,    20,    21,     3,   125,
     125,   125,     3,     3,    34,   157,     1,    44,     3,    24,
      24,   145,    42,   123,    44,    45,    46,    24,     4,   145,
     145,   145,    17,    18,    44,     8,   160,    22,    24,     3,
      41,    25,    44,     3,   160,   160,   160,     4,     4,    34,
       4,     4,     7,    17,    18,     4,     4,    42,    22,    44,
      45,    46,     1,     4,     4,    24,     5,     6,     4,    44,
      34,     8,    24,    31,    24,     4,    27,    -1,    42,    79,
      44,    45,    46,    47,     1,    24,    -1,    26,     5,    28,
      -1,    30,    -1,    32,    33,    34,    35,    -1,    37,     1,
      -1,    -1,    41,     5,     6,    44,    -1,    24,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    32,    -1,    34,    35,    -1,
      37,    -1,    24,    -1,    41,    -1,    28,    44,    -1,     3,
      32,    -1,    34,    35,    -1,    37,    -1,    -1,     3,    41,
      -1,    -1,    44,    17,    18,    -1,    -1,     3,    22,    -1,
      24,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      34,    17,    18,    -1,    -1,    -1,    22,    -1,    42,    34,
      44,    45,    46,    -1,    -1,    -1,    -1,    42,    34,    44,
      45,    46,    -1,    -1,    -1,    -1,    42,    -1,    44,    45,
      46,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     9,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    11,    12,
      -1,    -1,    15,    16,    17,    18,    19,    20,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    50,    44,     0,     5,    51,     1,     6,    24,
      36,    52,    54,    24,    38,    26,    30,    33,    40,    55,
      62,    44,     5,    57,    44,     3,    58,     3,    53,    39,
      56,    59,    62,     1,     5,     6,    24,    28,    32,    34,
      35,    37,    41,    44,    61,    62,    63,    65,    66,    68,
      56,    24,    25,     7,     4,    44,    24,    64,    63,     3,
       3,     3,     3,    17,    18,    22,    24,    42,    44,    45,
      46,    65,    66,    68,    69,    70,     3,     3,    23,    44,
      24,    24,    24,     4,    44,     8,    60,     6,    63,    41,
      70,     1,    44,    47,    70,     1,    70,    44,    69,    69,
      69,    29,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    24,    70,     1,     4,    70,
      70,    53,    44,    25,     3,     4,     4,     7,     4,     4,
       4,     4,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,     4,     4,    67,    24,    62,
      70,    63,    70,    24,    24,    63,     4,    25,    44,     4,
      31,     8,    70,    24,    63,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    57,    58,    58,    58,
      59,    59,    60,    60,    61,    62,    62,    62,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    64,    65,    66,    66,    66,    67,    67,
      68,    68,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     2,     2,     2,     0,     6,     2,     3,
       0,     4,     5,     5,     1,     0,     3,     2,     2,     0,
       3,     4,     4,     0,     4,     1,     1,     1,     3,     5,
       7,     5,     7,     5,     5,     2,     2,     2,     1,     2,
       3,     2,     2,     0,     3,     3,     5,     4,     3,     0,
       7,     4,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       1,     2,     1,     1,     1,     3,     3,     1,     1
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
      yyerror (YY_("syntax error: cannot back up")); \
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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
#line 56 "jac.y" /* yacc.c:1646  */
    {raiz = criarNo("Program", "Null"); raiz->filho = (yyvsp[-1].arv);}
#line 1466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 60 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv); criarIrmao((yyval.arv), (yyvsp[0].arv));}
#line 1472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 61 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv); criarIrmao((yyval.arv), (yyvsp[0].arv));}
#line 1478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 62 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv);}
#line 1484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 63 "jac.y" /* yacc.c:1646  */
    {;}
#line 1490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 66 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("FieldDecl", "Null"); (yyval.arv)->filho = (yyvsp[-3].arv); criarIrmao((yyval.arv)->filho, criarNo("Id", (yyvsp[-2].string))); criarIrmao((yyval.arv)->filho, (yyvsp[-1].arv));}
#line 1496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 67 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("FieldDecl", "error");}
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 71 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-2].arv); criarIrmao((yyval.arv), criarNo("Id", (yyvsp[0].string)));}
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 72 "jac.y" /* yacc.c:1646  */
    {;}
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 75 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("MethodDecl", "Null"); criarIrmao((yyval.arv)->filho, (yyvsp[-1].arv)); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 78 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("MethodHeader", "Null"); (yyval.arv)->filho = (yyvsp[-4].arv); criarIrmao((yyval.arv)->filho, criarNo("Id", (yyvsp[-3].string))); criarIrmao((yyval.arv)->filho, (yyvsp[-1].arv));}
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 79 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("MethodHeader", "Null"); (yyval.arv)->filho = criarNo("Void", "Null"); criarIrmao((yyval.arv)->filho, criarNo("Id", (yyvsp[-3].string))); criarIrmao((yyval.arv)->filho, (yyvsp[-1].arv));}
#line 1532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("MethodParams", "Null"); (yyval.arv) = (yyvsp[0].arv);}
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 84 "jac.y" /* yacc.c:1646  */
    {;}
#line 1544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 87 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv);}
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 91 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv); criarIrmao((yyval.arv), (yyvsp[0].arv));}
#line 1556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 92 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv); criarIrmao((yyval.arv), (yyvsp[0].arv));}
#line 1562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 93 "jac.y" /* yacc.c:1646  */
    {;}
#line 1568 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 96 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-2].arv); criarIrmao((yyval.arv), criarNo("Id", (yyvsp[-1].string))); criarIrmao((yyval.arv), (yyvsp[0].arv));}
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 97 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("StringArray", "Null"); criarIrmao((yyval.arv), criarNo("Id", (yyvsp[0].string)));}
#line 1580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 101 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-3].arv); criarIrmao((yyval.arv), (yyvsp[-1].arv)); criarIrmao((yyval.arv), criarNo("Id", (yyvsp[0].string)));}
#line 1586 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 102 "jac.y" /* yacc.c:1646  */
    {;}
#line 1592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 105 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("VarDecl", "Null"); (yyval.arv)->filho = (yyvsp[-3].arv); criarIrmao((yyval.arv)->filho, criarNo("Id", (yyvsp[-2].string)));}
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 108 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Bool", "Null");}
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 109 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Int", "Null");}
#line 1610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 110 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Double", "Null");}
#line 1616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 113 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv);}
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 114 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("If", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 115 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("If", "Null"); (yyval.arv)->filho = (yyvsp[-4].arv); criarIrmao((yyval.arv)->filho, (yyvsp[-2].arv)); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 116 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("While", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 117 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("DoWhile", "Null"); (yyval.arv)->filho = (yyvsp[-5].arv); criarIrmao((yyval.arv)->filho, (yyvsp[-2].arv));}
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 118 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Print", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv);}
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 119 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Print", (yyvsp[-2].string));}
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 120 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv);}
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 121 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv);}
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 122 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv);}
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 123 "jac.y" /* yacc.c:1646  */
    {;}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 124 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Return", "Null");}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 125 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Return", "Null"); (yyval.arv)->filho = (yyvsp[-1].arv);}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 126 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Statement", "error");}
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 130 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv); criarIrmao((yyval.arv), (yyvsp[0].arv));}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 131 "jac.y" /* yacc.c:1646  */
    {;}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 134 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Assign", "Null"); (yyval.arv)->filho = criarNo("Id", (yyvsp[-2].string)); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 137 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Id", "Null");}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 138 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Id", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[-1].arv));}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 139 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Id", "error");}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 143 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-2].arv); criarIrmao((yyval.arv), (yyvsp[0].arv));}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 144 "jac.y" /* yacc.c:1646  */
    {;}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 147 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("ParseArgs", "Null"); (yyval.arv)->filho = criarNo("Id", (yyvsp[-4].string)); criarIrmao((yyval.arv)->filho, (yyvsp[-2].arv));}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 148 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("ParseArgs", "error");}
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 151 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[0].arv);}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 152 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[0].arv);}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 153 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("And", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 154 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Or", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 155 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Eq", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 156 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Geq", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 157 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Gt", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 158 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Leq", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 159 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Lt", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 160 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Neq", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 161 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Plus", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 162 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Minus", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 163 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Star", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 164 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Div", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 165 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Mod", "Null"); (yyval.arv)->filho = (yyvsp[-2].arv); criarIrmao((yyval.arv)->filho, (yyvsp[0].arv));}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 166 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Not", "Null"); (yyval.arv)->filho = (yyvsp[0].arv);}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 167 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Plus", "Null"); (yyval.arv)->filho = (yyvsp[0].arv);}
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 168 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Minus", "Null"); (yyval.arv)->filho = (yyvsp[0].arv);}
#line 1868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 169 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Id", (yyvsp[0].string));}
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 170 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Length", "Null"); (yyval.arv)->filho = criarNo("Id", (yyvsp[-1].string));}
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 171 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("BoolLit", (yyvsp[0].string));}
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 172 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("DecLit", (yyvsp[0].string));}
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 173 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("RealLit", (yyvsp[0].string));}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 174 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[-1].arv);}
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 175 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = criarNo("Expr", "error");}
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 178 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[0].arv);}
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 179 "jac.y" /* yacc.c:1646  */
    {(yyval.arv) = (yyvsp[0].arv);}
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1926 "y.tab.c" /* yacc.c:1646  */
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
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
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
                      yytoken, &yylval);
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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 181 "jac.y" /* yacc.c:1906  */


void yyerror (const char *s) {      
        printf ("Line %d, col %d: %s: %s\n", lineNum, columnNum-(int)yyleng, s, yytext); 
}
