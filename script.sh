#!/bin/bash

docker run  -it \
    -v /home/dani/projects/testAssignment/Images:/usr/src/TestAssignment/Images \
    test_assignment \
    /usr/src/TestAssignment/TestAssignment -d Images