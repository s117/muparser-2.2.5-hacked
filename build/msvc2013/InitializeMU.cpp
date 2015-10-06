#include "muParser.h"

using namespace std;
using namespace mu;

/* Mathematic */
static value_type Add(value_type v1, value_type v2) { return v1 + v2; }							// +   level 9	L2R  STABLE
static value_type Sub(value_type v1, value_type v2) { return v1 - v2; }							// -   level 9	L2R	 STABLE
static value_type Mul(value_type v1, value_type v2) { return v1 * v2; }							// *   level 10	L2R	 STABLE
static value_type Div(value_type v1, value_type v2) { return v1 / v2; }							// /   level 10	L2R	 STABLE
static value_type Mod(value_type v1, value_type v2) { return (signed)v1 % (signed)v2; }			// %   level 10	L2R	 STABLE
																									   
/* Bitwise */																						   
static value_type BNot(value_type v) { return ~(unsigned)v; }									// ~   level 11	R2L	 STABLE
static value_type BAnd(value_type v1, value_type v2) { return (unsigned)v1 & (unsigned)v2; }	// &   level 5	L2R	 STABLE
static value_type BOr(value_type v1, value_type v2) { return (unsigned)v1 | (unsigned)v2; }		// |   level 3	L2R	 STABLE
static value_type BXor(value_type v1, value_type v2) { return (unsigned)v1 ^ (unsigned)v2; }	// ^   level 4	L2R	 STABLE
static value_type BSHL(value_type v1, value_type v2) { return (unsigned)v1 << (unsigned)v2; }	// <<  level 8	L2R	 STABLE
static value_type BSHR(value_type v1, value_type v2) { return (unsigned)v1 >> (unsigned)v2; }	// >>> level 8	L2R	 STABLE
static value_type BSAR(value_type v1, value_type v2) { return (signed)v1 >> (signed)v2; }		// >>  level 8	L2R	 STABLE
																									   
/* Logic */																							   
static value_type LNot(value_type v) { return !(unsigned)v; }									// !   level 11	R2L	 STABLE
static value_type LAnd(value_type v1, value_type v2) { return (unsigned)v1 && (unsigned)v2; }	// &&  level 2	L2R	 STABLE
static value_type LOr(value_type v1, value_type v2) { return (unsigned)v1 || (unsigned)v2; }	// ||  level 1	L2R	 STABLE
static value_type LE(value_type v1, value_type v2) { return v1 == v2; }							// ==  level 6	L2R	 STABLE
static value_type LNE(value_type v1, value_type v2) { return v1 != v2; }						// !=  level 6	L2R	 STABLE
static value_type LL(value_type v1, value_type v2) { return v1 < v2; }							// <   level 7	L2R	 STABLE
static value_type LLE(value_type v1, value_type v2) { return v1 <= v2; }						// <=  level 7	L2R	 STABLE
static value_type LG(value_type v1, value_type v2) { return v1 > v2; }							// >   level 7	L2R	 STABLE
static value_type LGE(value_type v1, value_type v2) { return v1 >= v2; }						// >=  level 7	L2R	 STABLE

/* MISC */
// Random
static value_type Rnd(value_type v) { return v*std::rand() / (value_type)(RAND_MAX + 1.0); }	// @   level 11	R2L  UNSTABLE

void Initialize(mu::Parser *parser) {
	parser->DefineOprt(_T("+"), Add, 9, oaLEFT, true);		// +   level 9	L2R  STABLE
	parser->DefineOprt(_T("-"), Sub, 9, oaLEFT, true);		// -   level 9	L2R	 STABLE
	parser->DefineOprt(_T("*"), Mul, 10, oaLEFT, true);		// *   level 10	L2R	 STABLE
	parser->DefineOprt(_T("/"), Div, 10, oaLEFT, true);		// /   level 10	L2R	 STABLE
	parser->DefineOprt(_T("%"), Mod, 10, oaLEFT, true);		// %   level 10	L2R	 STABLE
	parser->DefineInfixOprt(_T("~"), BNot, 11, true);		// ~   level 11	R2L	 STABLE
	parser->DefineOprt(_T("&"), BAnd, 5, oaLEFT, true);		// &   level 5	L2R	 STABLE
	parser->DefineOprt(_T("|"), BOr, 3, oaLEFT, true);		// |   level 3	L2R	 STABLE
	parser->DefineOprt(_T("^"), BXor, 4, oaLEFT, true);		// ^   level 4	L2R	 STABLE
	parser->DefineOprt(_T("<<"), BSHL, 8, oaLEFT, true);		// <<  level 8	L2R	 STABLE
	parser->DefineOprt(_T(">>>"), BSHR, 8, oaLEFT, true);	// >>> level 8	L2R	 STABLE
	parser->DefineOprt(_T(">>"), BSAR, 8, oaLEFT, true);		// >>  level 8	L2R	 STABLE
	parser->DefineInfixOprt(_T("!"), LNot, 11, true);		// !   level 11	R2L	 STABLE
	parser->DefineOprt(_T("&&"), LAnd, 2, oaLEFT, true);		// &&  level 2	L2R	 STABLE
	parser->DefineOprt(_T("||"), LOr, 1, oaLEFT, true);		// ||  level 1	L2R	 STABLE
	parser->DefineOprt(_T("=="), LE, 6, oaLEFT, true);		// ==  level 6	L2R	 STABLE
	parser->DefineOprt(_T("!="), LNE, 6, oaLEFT, true);		// !=  level 6	L2R	 STABLE
	parser->DefineOprt(_T("<"), LL, 7, oaLEFT, true);		// <   level 7	L2R	 STABLE
	parser->DefineOprt(_T("<="), LLE, 7, oaLEFT, true);		// <=  level 7	L2R	 STABLE
	parser->DefineOprt(_T(">"), LG, 7, oaLEFT, true);		// >   level 7	L2R	 STABLE
	parser->DefineOprt(_T(">="), LGE, 7, oaLEFT, true);		// >=  level 7	L2R	 STABLE
	parser->DefineInfixOprt(_T("@"), Rnd, 11, false);		// @   level 11	R2L  UNSTABLE
}