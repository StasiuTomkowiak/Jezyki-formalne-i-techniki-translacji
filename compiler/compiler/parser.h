/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    IS = 259,                      /* IS  */
    _BEGIN = 260,                  /* _BEGIN  */
    END = 261,                     /* END  */
    PROCEDURE = 262,               /* PROCEDURE  */
    DECLARE = 263,                 /* DECLARE  */
    READ = 264,                    /* READ  */
    WRITE = 265,                   /* WRITE  */
    IF = 266,                      /* IF  */
    THEN = 267,                    /* THEN  */
    ELSE = 268,                    /* ELSE  */
    ENDIF = 269,                   /* ENDIF  */
    WHILE = 270,                   /* WHILE  */
    DO = 271,                      /* DO  */
    REPEAT = 272,                  /* REPEAT  */
    UNTIL = 273,                   /* UNTIL  */
    ENDWHILE = 274,                /* ENDWHILE  */
    TABLE = 275,                   /* TABLE  */
    FOR = 276,                     /* FOR  */
    FROM = 277,                    /* FROM  */
    TO = 278,                      /* TO  */
    DOWNTO = 279,                  /* DOWNTO  */
    ENDFOR = 280,                  /* ENDFOR  */
    SEMICOLON = 281,               /* SEMICOLON  */
    LPRNT = 282,                   /* LPRNT  */
    RPRNT = 283,                   /* RPRNT  */
    LBRCKT = 284,                  /* LBRCKT  */
    RBRCKT = 285,                  /* RBRCKT  */
    COLON = 286,                   /* COLON  */
    COMMA = 287,                   /* COMMA  */
    ASSIGN = 288,                  /* ASSIGN  */
    EQ = 289,                      /* EQ  */
    NEQ = 290,                     /* NEQ  */
    LE = 291,                      /* LE  */
    GE = 292,                      /* GE  */
    LEQ = 293,                     /* LEQ  */
    GEQ = 294,                     /* GEQ  */
    ADD = 295,                     /* ADD  */
    SUB = 296,                     /* SUB  */
    MUL = 297,                     /* MUL  */
    DIV = 298,                     /* DIV  */
    MOD = 299,                     /* MOD  */
    ERROR = 300,                   /* ERROR  */
    pidentifier = 301,             /* pidentifier  */
    num = 302                      /* num  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "parser.y"

    int num;
    std::string* pidentifier;
    std::vector<std::string>* condition;
   
    std::vector<std::string>* expression;
    std::vector<std::string>* main;


#line 121 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
