
The TestAssignment is a CMake project, generated with CLion.

The ./script.sh runs on a Ubuntu 20.04, system must have docker installed.

On Win10, running the Docker script als batch file, does not work, docker throw error. (something with OCI, I think is related with mounting a volume).
Therefore run the bin file provided for Win10:
 in TestAssignment\bin: TestAssignment.exe -d Images

Compiled and tested also on Mac M1 (must recompile because M1 is an arm arhictecture).

The average.pgm file in bin folder is the program output with the input beening the 10 pgm files provided.
