
The TestAssignment is a CMake project, generated with CLion.

The ./script.sh should be run on a system with docker installed.
Tested on Ubuntu 20.04 and Win10 with git tools installed.

Docker push images:
 docker build -t test_assignment . 
 docker login -u danielspori 
 docker tag test_assignment danielspori/test_assignment
 docker push danielspori/test_assignment