# loc
Show statistics about Lines of Code

This project is a toy meant to expand on `wc` as described in KNR to 
act like most LoC variants in the wild.  

loc will simply list some trivial statistics about a codebase such as
total lines, blank lines, commented lines, and code lines.  These 
statistics will be printed for each language that is detected.

For simplicity, I will assume that file names and extentions are all 
that are needed to "know" what language a file contains.  Any language 
requiring more advanced checking will be ignored, for now at least.
