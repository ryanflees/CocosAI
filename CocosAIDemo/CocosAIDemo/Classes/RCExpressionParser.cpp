//
//  RCExpressionParser.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-19.
//
//

#include "RCExpressionParser.h"

#include 	<stdlib.h>
#include 	<string.h>
#include	<ctype.h>

NS_EXP

double_t degtorad(double_t d)
{
	return pi*(d/180.0);
}



double_t radtodeg(double_t r)
{
	return 180.0*(r/pi);
}


NS_EXP_END
