/*-----------------------------------------------------------------------

File  : ccl_fcvindexing.h

Author: Stephan Schulz

Contents

  Functions for handling frequency count vector indexing for clause
  subsumption.

  2003 by the author.
  This code is released under the GNU General Public Licence.
  See the file COPYING in the main CLIB directory for details.
  Run "eprover -h" for contact information.

Changes

<1> Tue Jul  1 13:05:36 CEST 2003
    New

-----------------------------------------------------------------------*/

#ifndef CCL_FCVINDEXING

#define CCL_FCVINDEXING

#include <clb_pdarrays.h>
#include <ccl_clauses.h>


/*---------------------------------------------------------------------*/
/*                    Data type declarations                           */
/*---------------------------------------------------------------------*/

typedef struct freq_vector_cell
{
   long size;        /* How many fields? */
   long *freq_vector;
   Clause_p clause; /* Just an unprotected reference */
}FreqVectorCell, *FreqVector_p, *FVPackedClause_p;

#define FV_MAX_SYMBOL_COUNT 50



/*

Case 1: Just one successor
- Key is >=0
- Array size is 0
- Pointer to successor

Case 1a: No successor
- Key is -1
- Array size is 0
- Pointer is NULL

Case 2: Many successors
- Key is -1
- Array Size > 0
- Pointer to array 

Case 3: Final cell
- Number = -2
- Array size = 0
- Pointer contains PTree of clauses

Initial case: Many successors with array size N

*/


#define FVINDEXTYPE_EMPTY   -1
#define FVINDEXTYPE_MANY    -2
#define FVINDEXTYPE_FINAL   -3

#define FVIndexEmptyNode(node) ((node)->type_or_key == FVINDEXTYPE_EMPTY)
#define FVIndexUnaryNode(node) ((node)->type_or_key >= 0)
#define FVIndexFinalNode(node) ((node)->type_or_key == FVINDEXTYPE_FINAL)
#define FVIndexManySuccNode(node) ((node)->type_or_key == FVINDEXTYPE_MANY)

typedef struct fv_index_cell
{
   long type_or_key;
   long clause_count;
   long array_size;
   union 
   {
      struct fv_index_cell **successors;
      struct fv_index_cell *succ;
      PTree_p clauses;
   } u1;
}FVIndexCell, *FVIndex_p;

typedef struct fvi_anchor_cell
{
   long      symbol_limit;
   long      node_count;
   long      array_count;
   FVIndex_p index;
}FVIAnchorCell, *FVIAnchor_p;


/*---------------------------------------------------------------------*/
/*                Exported Functions and Variables                     */
/*---------------------------------------------------------------------*/


#define FreqVectorCellAlloc()    (FreqVectorCell*)SizeMalloc(sizeof(FreqVectorCell))
#define FreqVectorCellFree(junk) SizeFree(junk, sizeof(FreqVectorCell))

#define NON_SIG_FEATURES 2
#define SigSizeToFreqVectorSize(size) (size*2-2+NON_SIG_FEATURES)
FreqVector_p FreqVectorAlloc(long size);
void         FreqVectorFree(FreqVector_p junk);

void         FreqVectorPrint(FILE* out, FreqVector_p vec);

void             StandardFreqVectorAddVals(FreqVector_p vec, long sig_symbols, 
					   Clause_p clause);
FreqVector_p     StandardFreqVectorCompute(Clause_p clause, long sig_symbols);
FVPackedClause_p FVPackClause(Clause_p clause, FVIAnchor_p index);
Clause_p         FVUnpackClause(FVPackedClause_p pack);
void             FVPackedClauseFree(FVPackedClause_p pack);

#define FVIndexCellAlloc()    (FVIndexCell*)SizeMalloc(sizeof(FVIndexCell))
#define FVIndexCellFree(junk) SizeFree(junk, sizeof(FVIndexCell))

FVIndex_p FVIndexAlloc(void);
void      FVIndexFree(FVIndex_p junk);

#define FVIAnchorCellAlloc()    (FVIAnchorCell*)SizeMalloc(sizeof(FVIAnchorCell))
#define FVIAnchorCellFree(junk) SizeFree(junk, sizeof(FVIAnchorCell))

FVIAnchor_p FVIAnchorAlloc(long symbol_limit);
void        FVIAnchorFree(FVIAnchor_p junk);

#define FVIndexStorage(index) ((index)?(index)->node_count*MEMSIZE(FVIndexCell)+\
			       (index)->array_count*sizeof(long):0)

FVIndex_p   FVIndexGetNextNonEmptyNode(FVIndex_p node, long key);
void        FVIndexInsert(FVIAnchor_p index, FreqVector_p vec_clause);

bool        FVIndexDelete(FVIAnchor_p index, Clause_p clause);

long        FVIndexCountNodes(FVIndex_p index, bool leafs, bool empty);

#endif

/*---------------------------------------------------------------------*/
/*                        End of File                                  */
/*---------------------------------------------------------------------*/





