/*=========================================================================================================
  
  File          : shortest_snippet.c 
  Functionality : Finding the minimal span snippet 
  Author        : Sri Venkatesh 
  Created On    : 04/07/2007

  Revision History 
  ----------------
  Sri Venkatesh  05/07/2007  Created - Added main(), FindShortestSpan() functions

=======================================================================================================*/

/* Header File Inclusion */
#include <stdio.h>
#include <stdlib.h>

/* Macros */
#define TRUE 1
#define FALSE 0
#define TERMINATOR_VALUE 0
                
/* Structure Definition */
typedef struct span_t
{
    int min;
    int max;
} span;

/* Function Declarations */
span FindShortestSpan (int num_search_terms, int **word_hit_locs);

/* Function Definitions */

/*=========================================================================================================
Function Name   :- main

Inputs          :- None

Return Value    :- None

Description     :- This function is a driver for using the FindShortestSpan() Function
                   The inputs are obtained from the user and the memory is allocated 
                   according to the inputs entered by the user. Then the shortest span 
                   is calculated by calling the function FindShortestSpan() function.
                   The range of the shortest span is then printed in the console.
Pre-Conditions :-  None as this is the first function of the program

Post-Conditions :- The locations values should not be modified
==========================================================================================================*/
void main()
{
/*-------------------------------- LOCAL VARIABLES ---------------------------------*/
    int numRows, numCols;
    int **a,i,j;
    span shortestSnippetSpan;

/*-------------------------------- CODE --------------------------------------------*/
  
    /* Getting Inputs From User */
    printf ("Enter the number of search strings : \n");
    scanf("%d", &numRows);
    a = (int**)malloc(sizeof(int*)*numRows);
    if(a == NULL)
    {
        printf("Error while mallocing : \n");
        exit(-1);
    }
    for(i=0;i<numRows;i++)
    {
        printf("Enter the number of locations for the string %d : ", i+1);
        scanf("%d", &numCols);
        a[i] = (int*)malloc((numCols+1)*sizeof(int));
        if(a[i] == NULL)
        {
            printf("Error while mallocing : \n");
            exit(-1);
        }

        for(j=0;j<numCols;j++)
        {
            printf("Enter %d th Column : ", j + 1);
            scanf("%d", &a[i][j]);   
        }
        a[i][j] = 0;
    }

    printf("Input Taken \n");
    shortestSnippetSpan = FindShortestSpan(numRows, a);
    printf("Processing Done\n");
 
    /* Printing the shortest snippet */
    if(shortestSnippetSpan.min != 0)
    {
        printf("\nShortest Snippet Span : %d to %d\n", shortestSnippetSpan.min, shortestSnippetSpan.max);
        printf("\nThe minimal Span length is %d", shortestSnippetSpan.max - shortestSnippetSpan.min + 1);
    }
    else
    {
        printf("No Such Snippet Found \n");
    }

    /*Freeing the memory allocated the 2-D array */
    for(i=0; i<numRows; ++i)
        free((void*)a[i]);
    free((void*)a);
} 

/*=========================================================================================================
Function Name   :- FindShortestSpan

Inputs          :- int numSearchTerms - number of search strings
                 int **wordHitLocs - 2-D array containing the locations of every search string

Return Value    :- struct span (span of shortest snippet)

Pre-Conditions  :- The locations per search string are in sorted order.

Post-Conditions :- The locations values should not be modified

Algorithm :
  Step 1: If the number of search terms is less than or equal to zero 
          return immediately with the span of span={0,0}
  Step 2: Initialize pointers for every string's subarray such that 
          initially the pointers are pointing to the first element of each 
          subarray
  Step 3: Form a Subset S such that S contains the current element from each string's
          subarray. The pointer corresponding to every subarray will be pointing to 
          that subarray's current element
          Note :- The subset is not actually created. Our aim is just to find out 
          the minimum and the maximum value of the subset and the string 
          corresponding to the minimum value.
  Step 4: Find the minimum and the maximum value in this subset S formed. This will give 
          the span of a snippet. But this span need not be the minimal. 
          There is a possiblity that this span could be minimal.
          If it is minimal then store it as the "minimalSpan."
  Step 5: Consider that the jth element in the subset is the minimal value. 
          Then increment pointer corresponding to the jth string's subarray
  Step 6: Repeat from Step 3 Until any one of the subarrays' pointer reaches 
          the end of the subarray(i.e reaches the terminator-value 0)

==========================================================================================================*/
span FindShortestSpan (int num_search_terms, int **word_hit_locs)
{
/*-------------------------------- LOCAL VARIABLES ---------------------------------*/   
    int *curIndexInSubArr;
    int rowIndexOfMinLocation, rowIndexOfMaxLocation;
    int minLocValue, maxLocValue, stringIndex;
    char endOfArray = FALSE;
    span minSpan = {0,0};
    int minSpanValue, currentSpanValue;

/*------------------------------------- CODE ---------------------------------------*/
    
    /* When the numSearchTerms is less than or equal to zero, immediately
       return with the minSpan = {0,0} */
     if(num_search_terms <= 0)
        return minSpan; 
   
    /* callocing for currentIndexArr. currentIndexArr is an integer array 
       currentIndexArr[0] represents the current index in the 1-D array 
       of the first string 
       Similarly currentIndexArr[1] represents the current index in the 1-D 
       array of the second string */
     curIndexInSubArr = (int*)calloc(num_search_terms, sizeof(int));
     if(curIndexInSubArr == NULL)
     {
         printf("Error : Something wrong with calloc :\n");
         exit(-1);
     }
     /* Now we have to scan the strings subarray and pick one location 
        from every subarray . During this picking process itself we find the 
        minimum and the maximum of those locations */
     
     while (endOfArray == FALSE)
     {
         rowIndexOfMinLocation = rowIndexOfMaxLocation = 0;
         minLocValue = maxLocValue = word_hit_locs[0][curIndexInSubArr[0]];
         for(stringIndex=0; stringIndex<num_search_terms; ++stringIndex)
         {        
            if(word_hit_locs[stringIndex][curIndexInSubArr[stringIndex]] > maxLocValue)
            {
                rowIndexOfMaxLocation = stringIndex;
                maxLocValue = word_hit_locs[stringIndex][curIndexInSubArr[stringIndex]];
            }
            if(word_hit_locs[stringIndex][curIndexInSubArr[stringIndex]] < minLocValue)
            {
                rowIndexOfMinLocation = stringIndex;
                minLocValue = word_hit_locs[stringIndex][curIndexInSubArr[stringIndex]];
            }
   
           /* The following if condition is added for the reason stated as below.
              Reason :- When the particular search string is not at all present in the document
              then the first entry itself will be 0(terminator). So return 
              immediately with the minSpan(minSpan should be having {0,0} for this case) */      
            if(minLocValue <= TERMINATOR_VALUE)
            {
                free((void*)curIndexInSubArr);
                return minSpan;
            }    
         } /* end of for */
         
         minSpanValue = minSpan.max - minSpan.min + 1;
         currentSpanValue = word_hit_locs[rowIndexOfMaxLocation][curIndexInSubArr[rowIndexOfMaxLocation]] - \
                                 word_hit_locs[rowIndexOfMinLocation][curIndexInSubArr[rowIndexOfMinLocation]] + 1;
         if(currentSpanValue < minSpanValue || minSpan.min == 0)
         {
             minSpan.min = word_hit_locs[rowIndexOfMinLocation][curIndexInSubArr[rowIndexOfMinLocation]];
             minSpan.max = word_hit_locs[rowIndexOfMaxLocation][curIndexInSubArr[rowIndexOfMaxLocation]];
         }
         /* If its not the end of the subarray, then increment the pointer, so that 
            the pointer points to the next element in the subarray */
         if(word_hit_locs[rowIndexOfMinLocation][curIndexInSubArr[rowIndexOfMinLocation] + 1] > TERMINATOR_VALUE)
             ++(curIndexInSubArr[rowIndexOfMinLocation]);
         else
             endOfArray = TRUE;         
     } /* end of while */
     free((void*)curIndexInSubArr);
     
     
     return minSpan;
}
 
