/*******************************************************************************
 *
 * source: [codegen_arith/parser.y]
 *
 ******************************************************************************/

%{

#include <stdio.h>

#include "lexer.h"

#include "codegen.h"
#include "ParseTreeNode.h"
#include "ParseTree.h"

using namespace codegen;

int yyerror (char const *s);

%}

%define api.value.type {ParseTreeNode*}

%token NUM
%token ID
%token EMAIL
%token ADD
%token MULT
%token LP
%token RP
%token NL

%token SEMI
%token ASSIGN
%token RETURN
%token LC
%token RC
%token COMMA
%token INT
%token TEST
%%

program:
	function-definition{
		parse_tree = new ParseTree($1);
		return 0;		
	};

function-definition:
		decl-specifier declarator fct-body{
			$$ = new ParseTreeNode(ParseTreeNode::Rule_0, $1, $2, $3);
		};

decl-specifier:
		type-specifier{
			$$ = new ParseTreeNode(ParseTreeNode::Rule_1, $1, NULL);
		};

type-specifier:
		simple-type-name{
			$$ = new ParseTreeNode(ParseTreeNode::Rule_2, $1, NULL);
		};

simple-type-name:
		INT{
			$$ = new ParseTreeNode(ParseTreeNode::Rule_3, $1, NULL);
		};

declarator:
		declarator LP RP{
			$$ = new ParseTreeNode(ParseTreeNode::Rule_4, $1, NULL);
		}
		|
		dname{
			$$ = new ParseTreeNode(ParseTreeNode::Rule_5, $1, NULL);
		};

dname:
	name{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_6, $1, NULL);
	};

name:
	ID{
		$$ = new ParseTreeNode(yytext);
	};

fct-body:
	compound-statement{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_8, $1, NULL);
	};

compound-statement:
	LC statement-list RC{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_9, $2, NULL);
	};

statement-list:
	statement{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_10, $1, NULL);
	}
	|
	statement-list statement{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_11, $1, $2);
	};

statement:
	expression-statement{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_12, $1, NULL);
	}
	|
	declaration-statement{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_13, $1, NULL);
	}
	|
	jump-statement{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_14, $1, NULL);
	}
	|
	NL{
	};

expression-statement:
	expression SEMI NL{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_15, $1, NULL);
	};

expression:
	assignment-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_16, $1, NULL);
	}
	|
	expression COMMA assignment-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_17, $1, $3);
	};

assignment-expression:
	additive-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_18, $1, NULL);
	}
	|
	assignment-expression ASSIGN additive-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_19, $1, $3);
	};

additive-expression:
	multiplicative-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_20, $1, NULL);
	}
	|
	additive-expression ADD multiplicative-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_21, $1, $3);
	};

multiplicative-expression:
	primary-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_22, $1, NULL);
	}
	|
	multiplicative-expression MULT primary-expression{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_23, $1, $3);
	};

primary-expression:
	literal{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_24, $1, NULL);
	}
	|
	name{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_25, $1, NULL);
	};

literal:
	NUM{
		$$ = new ParseTreeNode(atoi(yytext));
	};

declaration-statement:
	declaration SEMI NL{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_27, $1, NULL);		
	};

declaration:
	decl-specifier declarator-list{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_28, $1, $2);	
	};

declarator-list:
	init-declarator{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_29, $1, NULL);
	}
	|
	declarator-list COMMA init-declarator{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_30, $1, $3);
	};

init-declarator:
	declarator{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_31, $1, NULL);
	};

jump-statement:
	RETURN expression SEMI NL{
		$$ = new ParseTreeNode(ParseTreeNode::Rule_32, $2, NULL);
	};

%%

int
yyerror (char const *s)
{
	fprintf (stderr, "%s\n", s);
}//end of function yyerror




