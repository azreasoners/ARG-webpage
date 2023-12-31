The package contains the following files:

1. f2lp.c - source code of F2LP version 1.0.1.
2. f2lp - binary for Linux based systems (compiled using gcc 4.4.1).
3. COPYRIGHT - information about copyright and warranty.

*******************
Compiling f2lp:
*******************
The following command line should work with most gcc distributions:

gcc f2lp.c -o f2lp

******************
Invoking f2lp:
******************
f2lp input_file_1 ... input_file_n

Please type "f2lp --help" for a list of all options.

*****************
Debugging:
*****************
f2lp can be compiled to output debug information using the
following command line:

gcc -D DEBUG f2lp.c -o f2lp

Note that the output of f2lp in this case cannot be
directly fed into the answer set solvers.


*************************************************************************
Revisions and New Features ( with respect to the earlier version (1.0) ):
**************************************************************************
1. F :- G where F and G are first-order formulas are permitted.
2. "_" can be used in variables.
3. Fixed a bug in quantifier elimination (replacement of variables).



*************************************************************************
Revisions and New Features ( with respect to the earlier version (0.9) ):
*************************************************************************
1. Fixed a bug in searching for patterns.
2. Fixed some problems with parsing comments.
3. Added suport for STDIN and multiple input files.
4. Added options (can be viewed using "f2lp --help").
5. Added # before hide.
6. Hides the new predicates.
7. Adds double negation only for S.P occurrences when new predicates are introduced.
9. Added support for extensional predicates (Example: #extensional P(X,Y).)
10. Supports comparisons involving function constants (Example: p(X,a) != A). 
11. Fixed a bug in the code that replaces variables with new ones 
    (when the size of the new variable is smaller than that of the older variable).
12. Removed the error message that # can be used only to declare domain variables. 

****************************************
Under consideration for future versions:
****************************************
1. Output programs that can be run on dlv.
2. Treating aggregates as atoms.
3. Implementing safety-preserving transformations.
