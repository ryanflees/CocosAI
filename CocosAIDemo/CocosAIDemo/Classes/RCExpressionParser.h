//
//  RCExpressionParser.h
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-19.
//
//

#ifndef __CocosAIDemo__RCExpressionParser__
#define __CocosAIDemo__RCExpressionParser__

#include <iostream>
#include <math.h>
#include <string.h>

#ifndef bcopy
#include	<string.h>
#define bcopy(src, dest, count) memcpy((dest), (src), (count))
#endif

#define	NUMBER		258
#define	FUNCTION	259
#define	VAR			260
#define	NEG			261

#define NS_EXP namespace ExpressionParser {
#define NS_EXP_END }
#define USING_EXP_PARSER using namespace ExpressionParser

NS_EXP

double_t degtorad(double_t d);
double_t radtodeg(double_t r);

    // this structure used to form elements of a simple symbol table which can contain literal values or
    // pointers to functions that return values
    

typedef struct symbol
{
    char* name;
    int type;
    union
    {
        double_t var;
        double_t (*func)(double_t arg);
    }
    value;
    struct symbol* next;
}
symbol;

// this structure used for a table of callable math functions

struct init
{
	char *fname;
	double_t (*fnct)(double_t arg);
};

int 	yyparse(void* param);
void	yyerror(char* errStr);

// the parser class:

class	RCExpressionParser
{
private:
	symbol*	st;
	double_t result;
	char* expStr;
	
public:
	RCExpressionParser(){
        init();
    }
	virtual ~RCExpressionParser();
	
	void	init();
    
    // the only methods you need (as a user!):
	virtual double_t	evaluate(const char* expression);
	virtual void setSymbolValue(const char* aName, const double_t aValue);
    
    // these called internally:
	symbol*	get(const char* aName);
	symbol*	put(const char* aName, const int aType);
	void	setResult(const double_t v);
	char* getExpStr(){ return expStr; }
};

#ifndef pi
#define pi 3.141592654
#endif


NS_EXP_END

#endif /* defined(__CocosAIDemo__RCExpressionParser__) */
