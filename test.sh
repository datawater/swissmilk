#!/bin/bash

# set -xe

FAILED="Failed!"
PASSED="Passed!"

TESTS=$(find . -type f -perm /111 -path "./$1/*.test")

I=1
FAILED_X=0

echo $TESTS

for TEST in $TESTS ; do
    echo "TEST N$I: $TEST"

    $TEST > test_output.tmp
    if cmp -s "test_output.tmp" "./tests/$(basename $TEST | rev | cut -d"." -f2- | cut -d"." -f2- | rev | sed "s/.*/&.txt/")"; then
        echo "Test N$I ${PASSED}";
    else
        echo "Test N$I ${FAILED}";
        echo "Diff:"
        diff "test_output.tmp" "./tests/$(basename $TEST | rev | cut -d"." -f2- | cut -d"." -f2- | rev | sed "s/.*/&.txt/")"
        FAILED_X=$(( ${FAILED_X} + 1 ))
    fi

    I=$(( ${I} + 1 ))
done

echo ""

if [ $FAILED_X = 0 ]; then
    echo "All Tests ${PASSED} :)"
else
    echo "$FAILED_X Test(s) Failed :("
    exit 1
fi

exit 0
