Shortest-Snippet---Google-Interview
===================================

This is one of my interview questions that I cracked, way back in 2007.
I am not sure if this problem can be cracked in an hour or 2 hour interviews, but its used for offline interviews
where in a canditate will be given a day or 2 to submit a working code for the given question.


Problem Description
===================

I hope you have used google. When they show results, they show
"snippets". If I searched "stormy weather india", it comes with
several hits, one of which is displayed as:
Ania Loomba: "The Postcolonial Tempest: Response to Peter Hulm's
...Peter Hulme's 'Stormy Weather' is, as the author remarks, ... As I
started to write this response in New Delhi, India, it seemed to me even
more important ...
eserver.org/emc/1-3/loomba.html - 32k - Cached - Similar pages - Remove
result

The words "Stormy", "Weather" and "India" are shown in bold.

Let's suppose you are writing a display routine for "google search".
Let's say the backend engine gives you the following:
the specific document that matched, as well as the following
pieces of information
Stormy - 3, 7, 16, 48
Weather - 5, 9, 21, 27, 49, 58
India - 1, 4, 8, 17, 47, 50
The numbers indicate the index of the location of the word.
For example, the document that starts with the sentence:
"The Stormy weather in India today is alarming even though the
weather in Nepal has been perfectly normal. We always thought
that India is not vulnerable to stormy conditions." will return
Stormy - 2, 28
Weather - 3, 12
India - 5, 23

A "snippet" is a contiguous sequence of words that have at least one
occurrence of all the words in the search (irrespective of order).
The "span" of a snippet is defined as the number
of words from the first to the last word in the # of words in the search.
Your job is to find a "snippet" (within the html page) that has
the smallest span.
Google does not care about the ordering of the search words.

In the above example, Google would be looking to display a snippet
that shows only "The Stormy weather in India" and not the longer
span that has all the three words.

Write a piece of code that will take the above input (array of numbers
per search string) and output the range of the shortest span. For the
above example, it should return "2, 5" (and not "2, 12").
Obviously, the arrays can be different lengths.
You can assume that 0 is used to signal the end of the above arrays.
You can also assume that each of the arrays are sorted.

Here is the function prototype:

typedef struct span_t
{
        int min;
        int max;

} span;

span FindShortestSpan (int numSearchTerms, int **wordHitLocs)
{

        /* your code here */

}
