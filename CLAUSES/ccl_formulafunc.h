/*-----------------------------------------------------------------------

File  : ccl_formulafunc.h

Author: Stephan Schulz

Contents
 
  Higher level Formula functions that need to know about sets (and
  CNFing).

  Copyright 2004 by the author.
  This code is released under the GNU General Public Licence.
  See the file COPYING in the main CLIB directory for details.
  Run "eprover -h" for contact information.

Changes

<1> Sun Apr  4 14:10:19 CEST 2004
    New

-----------------------------------------------------------------------*/

#ifndef CCL_FORMULAFUNC

#define CCL_FORMULAFUNC

#include <ccl_formula_wrapper.h>
#include <ccl_cnf.h>


/*---------------------------------------------------------------------*/
/*                    Data type declarations                           */
/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/
/*                Exported Functions and Variables                     */
/*---------------------------------------------------------------------*/


long WFormulaCNF(WFormula_p form, ClauseSet_p set, 
                       TB_p terms, VarBank_p fresh_vars);
void FormulaSetCNF(FormulaSet_p set, ClauseSet_p clauseset, 
                   TB_p terms, VarBank_p fresh_vars);
long FormulaAndClauseSetParse(Scanner_p in, ClauseSet_p cset,
                              FormulaSet_p fset, TB_p terms);
long FormulaToCNF(Formula_p form, ClauseProperties type, 
                  ClauseSet_p set, TB_p terms, VarBank_p fresh_vars);



#endif

/*---------------------------------------------------------------------*/
/*                        End of File                                  */
/*---------------------------------------------------------------------*/






