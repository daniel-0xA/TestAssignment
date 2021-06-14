#!/bin/bash

docker run --rm \
    -v Images:/usr/src/TestAssignment/Images \
    danielspori/test_assignment \
    /usr/src/TestAssignment/TestAssignment -d Images