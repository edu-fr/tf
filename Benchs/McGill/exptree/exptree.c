/***************************************************************************

PART 1: PROGRAM

    Pierre Ouellet ID 9009791

    The problem solved by this program is stated as follows:

    Given a set S of k nonzero natural numbers, labeled n1..nk,
    a "total" t, which is also a nonzero natural number, find
    an expression tree, whose leaves are taken from S, and whose
    interior nodes are each labeled one of {+, -, *, /}, and that
    evaluates to t. There is the additional restriction that any
    subtree must evaluate to a natural number greater than 0.
    Division is permitted only if the value of the left child
    is exactly divisible by the value of the right child. Also,
    numbers in S may not be used more times than they appear,
    e.g. if S = { 2, 3, 3 }, "3" may be used at most twice.

    The program uses a brute-force search, more precisely an
    iterative deepening depth-first search. The search can be
    viewed as an attempt to build the tree bottom-up: whenever
    the value t is not present, we try to obtain it by "combining"
    two available values, which are taken from the "work list",
    which consists of those elements of S not yet used and the values
    obtained by previous combinations. This is the equivalent of
    creating a new root and making the two operands its children.

    The work list is an array of integers, originally containing
    the elements of S. When elements are combined, they're marked
    used and the result of combining them (the result of evaluating
    the new root) is added at the end of the list.

    The combinations are saved in an array of Comb, to be printed out
    when a solution is found.

***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define NOOP 0
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

typedef struct
{
  int operand1, operand2;
  int operation;

} Comb;

/* Global variables are used to save time during the search */

static int goal; /* the value of t explained above */
static int listLength; /* |S| */
static int *workList;
static Comb *combList;
static Comb *solution;
static int best = 0; /* value of best solution found yet */
static int dmax; /* maximal depth of search */
static int stopSearch; /* flag so we stop at first solution */
static int bestDepth = 0; /* depth of best solution; used if no exact
                             solution is found */
static int nbNodes; /* statistics: number of nodes examined
                             (number of calls to recSearch) */

/************************* INITIALIZATION STUFF *************************/

int *newWorkList(int length)

/*  Create a "work list", which is an array of integers with length
    elements
*/

{
  int *newList = (int *)calloc(length, sizeof(int));

  if (newList)
    {
      return newList;
    }
  else
    {
      fprintf(stderr, "Out of memory for work list\n");
      exit(1);
    }
}

Comb *newCombList(int length)

/*  Create a "combination list", which is to be used all the way through
    the search. It contains the combinations attempted so far in the search.
*/

{
  Comb *newList = (Comb *)calloc(length, sizeof(Comb));

  if (newList)
    {
      return newList;
    }
  else
    {
      fprintf(stderr, "Out of memory for combination list\n");
      exit(1);
    }
}

void initWorkList(int *workList, int *givenList, int length)

{
  int i;

  for (i = 0; i < length; i++)
    {
      workList[i] = givenList[i];
    }
}

void initCombList(Comb *combList, int length)
{
  int i;

  for (i = 0; i < length; i++)
    {
      combList[i].operation = NOOP;
    }
}

/************************* AUXILIARY FUNCTIONS *************************/

void saveSolution(Comb *sol, Comb *combList, int length)

/*  Copy a sequence of combinations.
*/

{
  int i;

  for (i = 0; i < length; i++)
    {
      sol[i].operand1 = combList[i].operand1;
      sol[i].operand2 = combList[i].operand2;
      sol[i].operation = combList[i].operation;
    }

  sol[length].operation = NOOP; /* End marker */
}

int calculate(Comb *comb)

/*  Compute the value generated by a combination.
*/

{
  switch (comb->operation)
    {
      case ADD:
        return comb->operand1 + comb->operand2;
      case SUB:
        return comb->operand1 - comb->operand2;
      case MUL:
        return comb->operand1 * comb->operand2;
      case DIV:
        return comb->operand1 / comb->operand2;

      default:
        return 0;
    }
}

/************************* OUTPUT STUFF *************************/

void printSolution(Comb *combList, int length)
{
  int i;

  for (i = 0; i < length; i++)
    {
      printf("%d", combList[i].operand1);

      switch (combList[i].operation)
        {
          case NOOP:
            printf(" ");
            break;
          case ADD:
            printf("+");
            break;
          case SUB:
            printf("-");
            break;
          case MUL:
            printf("*");
            break;
          case DIV:
            printf(":");
            break;

          default:
            printf(" d%d ", combList[i].operation);
        }

      printf("%d=%d", combList[i].operand2, calculate(&combList[i]));

      if (i < length - 1)
        {
          printf("; ");
        }
      else
        {
          printf(".\n");
        }
    }

  printf("\n");
}

void printList(int *list, int length, int mask)
{
  int i;

  for (i = 0; i < length; i++)
    {
      if ((1 << i) & mask)
        {
          continue;
        }

      printf("%d ", list[i]);
    }

  printf("\n");
}

/************************* ACTUAL SEARCH STUFF *************************/

void recSearch(int searchDepth, int usedMask)

/*  searchDepth:    current depth within the search.
    usedMask:	    used to tell which elements of the work list
                    have been used.
*/

{
  int currOp; /* current operation under consideration */
  int newMask; /* or'ed with old mask to mark used numbers from work list */
  int operand1; /* offset of operand 1 of combination within work list */
  int operand2; /* offset of operand 2 of combination within work list */

  if (stopSearch)
    {
      return; /* unroll recursion when solution is found */
    }

  nbNodes++; /* Statistics */

  if (searchDepth == dmax)
    {
      /* check whether last number generated is nearer to t than best */
      if (abs(workList[listLength + searchDepth - 1] - goal) < abs(best - goal))
        {
          /* if so, save solution */
          best = workList[listLength + searchDepth - 1];
          bestDepth = searchDepth;
          saveSolution(solution, combList, searchDepth);

          if (best == goal)
            {
              printSolution(combList, searchDepth);
              stopSearch = 1;
            }
        }
    }

  else
    {
      int working1, working2; /* hold values of numbers considered
                               for combination */
      int temp; /* for swapping */

      /* iterate over all four operators {+, -, *, /} */
      for (currOp = ADD; currOp <= DIV; currOp++)
        {
          for (operand1 = 0; operand1 < listLength + searchDepth; operand1++)
            {
              /* do not use already used numbers */
              if ((1 << operand1) & usedMask)
                {
                  continue;
                }

              for (operand2 = 0; operand2 < operand1; operand2++)
                {
                  if ((1 << operand2) & usedMask)
                    {
                      continue;
                    }

                  working1 = workList[operand1];
                  working2 = workList[operand2];

                  /* x * 1 = 1 * x = x; x / 1 = x */
                  if ((currOp == MUL || currOp == DIV) &&
                      (working1 == 1 || working2 == 1))
                    {
                      continue;
                    }

                  /* could arise from combination a - a for some a */
                  if (working1 == 0 || working2 == 0)
                    {
                      continue;
                    }

                  /* make dure operand2 divides operand1 */
                  if (currOp == DIV && (working1 % working2))
                    {
                      continue;
                    }

                  /* make sure operand1 >= operand2 for subtraction and
             division */
                  if ((currOp == DIV || currOp == SUB) && (working1 < working2))
                    {
                      temp = working1;
                      working1 = working2;
                      working2 = temp;
                    }

                  /* mark operands used */
                  newMask = usedMask | (1 << operand1) | (1 << operand2);

                  /* save current combination */
                  combList[searchDepth].operand1 = working1;
                  combList[searchDepth].operand2 = working2;
                  combList[searchDepth].operation = currOp;

                  workList[listLength + searchDepth] =
                      calculate(&combList[searchDepth]);

                  /* search deeper */
                  recSearch(searchDepth + 1, newMask);
                }
            }
        }
    }
}

void doSearch(void)

/*  Preliminary search. Takes care of the special case where |S| = 1
    and the only element of S is t.
*/
{
  int i;

  for (i = 0; i < listLength; i++)
    {
      if (abs(workList[i] - goal) < abs(best - goal))
        {
          best = workList[i];
        }
    }

  if (best == goal)
    {
      printf(".\n");
      return;
    }

  for (dmax = 1; dmax < listLength; dmax++)
    {
      recSearch(0, 0);

      if (stopSearch)
        {
          break;
        }
    }

  /* If no exact solution was found */
  if (stopSearch == 0)
    {
      printSolution(solution, bestDepth);
    }
}

int getInput(void)
{
  int nums[16];
  int i = 0;
  int c;
  nums[0] = 13;
  nums[1] = 32;
  nums[2] = 14;
  nums[3] = 1412;

  while ((c = getchar()) != '\n' && c != EOF)
    {
      ungetc(c, stdin);
      fscanf(stdin, "%d", &nums[i]);
      i++;
    }

  if (i == 0)
    {
      i = 4;
    }

  listLength = i - 1;
  goal = nums[listLength];

  workList = newWorkList(2 * listLength);
  combList = newCombList(listLength);
  solution = newCombList(listLength);

  initWorkList(workList, nums, listLength);
  initCombList(combList, listLength);
  initCombList(solution, listLength);

  return (listLength);
}

void search(void)
{
  /* set up global variables for search */
  stopSearch = 0;
  nbNodes = 0;

  doSearch();
}

int main(int argc, char *argv[])
{
  if (getInput())
    {
      search();
    }
  return 0;
}
