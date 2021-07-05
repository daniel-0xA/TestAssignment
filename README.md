
The TestAssignment is a CMake project.

prerequisites:
 ./Images with 10 pgm files (to be found in bin folder)
 
run
 Ubuntu 20.04, with docker installed
	$./scripts/script.sh
 Win10, with docker installed
	>.\scripts\script.bat
 Mac M1
	Compiled and tested also on Mac M1 (must recompile because M1 is an arm arhictecture).
	
run the bin file (Win10):
 in TestAssignment\bin: TestAssignment.exe -d Images

The average.pgm file in bin folder is the program output with the input beening the 10 pgm files provided.
