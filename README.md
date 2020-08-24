# meshconvert

Convert numerous formats of 3D mesh files into another with single command.
This program natively supports multithreading and conversion of 3D mesh files stored in certain directory hierarchy.

## BUILD
g++ main.cpp util.h -lboost_system -lboost_filesystem -lassimp

## EXECUTE
./a.out --source=[SOURCE] --destination=[DESTINATION] --format=obj
