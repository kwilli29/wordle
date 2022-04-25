# wordle

Stylistic things to figure out:

Are we printing error messages inside functions or in main?
(I have cerrno included right now but should delete later if we don't end up using)
Do we return bools or ints for success?
Should we always have functions return a bool or int for success and edit things with
call by reference or can some of them return values/structs?

putting if statements with one thing to execute all on one line? probably not, right?

underscores not camelcase for naming convention

comments: introduce what the structures are in main, and explain what each function does
in the function file, nothing in the .h?


* * * * * * * * * * *

Things to consider doing:

make an undo option? -- would need to keep copies of changes etc

have it recognize when you're done

find best ones to show

* * * * * * * * * * *

STURCTS and other include things

enum Color = NAN, YELLOW, GREEN, GRAY

map: keys are each letter (char), static array len 5 of enum Colors (int) at each position
*** do we make this a struct with methods to automate things
no i don't think so i think we should just have a .h file with functions for it ****

struct Word with members rank and string

* subject to change, ideally a tree at some point *
VECTOR words: starts with all the possible wordle words, sorted by rank member, continually pruned by eliminating indices that don't work


* * * * * * * * * * *

Functions:

create words vector/or tree/ of Word structs, with calculated rankings

initialize map of letters to NAN at all positions

update map with information from user
- analyze yellow and green letters first
- remove letter if gray and not greens or yellows in position array
get word info from user

update map with information from user
- analyze yellow and green letters first
- remove letter if gray and not greens or yellows in position array
