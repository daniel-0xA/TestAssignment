
The TestAssignment is a CMake project, generated with CLion.

The ./script.sh runs on a Ubuntu 20.04 system with docker installed.

On Win10, running the script als batch file, does not work, docker thrown error. (something with OCI, I think is related with mounting a volume).

Tested on Mac M1 (must recompile because is M1 is an arm arhictecture).

Running the bin file on Win10:
 in TestAssignment\bin: TestAssignment.exe -d Images

The average.pgm file in bin folder is the program output with the input beening the 10 pgm files provided.
