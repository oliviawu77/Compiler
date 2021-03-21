/*******************************************************************************
 *
 * source: [lexer.flex]
 *
 ******************************************************************************/

%{

#include <stdio.h>

#include "ParseTreeNode.h"
#include "ParseTree.h"

using namespace codegen;

#include "parser.h"


%}

%option noyywrap

INT int
RETURN return
TEST test

NUM		[0-9][0-9]*
ID		[a-zA-Z][a-zA-Z0-9]*
ADD		"+"
MULT		"*"
ASSIGN		"="
LP		"("
RP		")"
NL		"\n"
SEMI		";"
COMMA		","
LC			"{"
RC			"}"



%%

{INT}		{
				return INT;
			}

{TEST}		{
				return TEST;
			}
			
{RETURN}	{
				return RETURN;
			}

{NUM}		{
				return NUM;
			}

{ID}		{
				return ID;
			}

{ADD}		{
				return ADD;
			}

{MULT}		{
				return MULT;
			}

{ASSIGN}	{
				return ASSIGN;
			}			

{LP}		{
				return LP;
			}

{RP}		{
				return RP;
			}

{NL}		{
				return NL;
			}

{SEMI}		{
				return SEMI;
			}

{COMMA}		{
				return COMMA;
			}

{LC}		{
				return LC;
			}

{RC}		{
				return RC;
			}

<<EOF>>		{
				return -1;
			}

%%



