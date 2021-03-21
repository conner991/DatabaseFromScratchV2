# Design Document - Conner Fissell: Project 1

## Status
Unfortunately I was not able to complete Project 1 in time to get all of the proper functionalites working correctly. 
I do however have a plan to finish this up after I submit it for partial credit. I think I know how to implement the rest of the
project using a couple classes and a struct. I was able to come up with a protoype design but did not have time to integrate it properly 
with the rest of the program. I want to get this first assignment working because I know the rest will build off of this one and I 
think I can make that happen. Just going to have to put more time into it of course. Apologies for the tardiness and incompleteness 
of the project. Next time will hopefully be better!

## System Design
I decided to model the system design of the project after the example from the video and the paper guide. Whenever a database 
gets created I have my program create an empty directory titled after the name the user wants to call the database. My plan is to have
tables be files that get created inside of the database directories. 

## Implementation
I decided to write the program using C++ with one driver file containing main(), two header files and a Makefile. The only functionalities 
that I was able to get working are database creation and deletion ones; plus the USE command. I designed the program so the it first reads in
the input from the SQL prompt as a string. The parser then takes that string and splits it up into dynamic words that later get analyzed by the 
"wordDecider()" function. Here is where the rest of the program flows from depending on what is entered into the prompt. I made three functions
titled "createDB()", "deleteDB()" and "useDB()" that handle database creation, deletion and usage. I use a "struct" titled "Database" to store 
relavant information pertaining to a database and a vector to hold the created struct databases. The createDB() and deleteDB() functions use logic,
a counter a boolean flag to manipulate the database vector according to the users input.  

## Interface
The interface of the program runs exactly how the example program from the TA test video ran. This design was also modeled after the 
terminal interface design that is on the paper guide. Running "make dbDriver" compiles the program. Then entering "./dbDriver" into the 
command prompt will launch the program into "SQL Mode." A "-->" symbol pops up letting the user know that the program is now ready to accept
SQL commands. 

## Testing
This program was created using VS Code on Ubuntu 20.10. No external libraries, that needed to be downloaded and installed locally were used.
As I am wrting this now I realize that I did not implement this program as one which could accept the PA1_test.sql script on the command line. The 
SQL commands will have to be entered manually. I totally forgot about that idea and apologize Abdullah! That would definitely be the best way to write 
this program. I will work on implementing that idea for next time. 