#!/bin/bash

TRUE_TEST=0
FALSE_TEST=0
FILE_1="tests/1.txt"
FILE_2="tests/2.txt"
FILE_3="tests/3.txt"
FILE_4="tests/4.txt"
COMMAND_1="cat"
COMMAND_2="./s21_cat"
RES_1="cat_res.txt"
RES_2="s21_cat_res.txt"


for flag in -b -e -n -s -t 
do
    for file in $FILE_1 $FILE_2 $FILE_3 $FILE_4
    do
        TEST_1="$flag $file"
        echo "$TEST_1"
        $COMMAND_1 $TEST_1 > $RES_1
        $COMMAND_2 $TEST_1 > $RES_2
        DIFF=$(diff $RES_1 $RES_2) 
        if [ "$DIFF" = "" ] 
        then
            let "TRUE_TEST+=1"
        else
            echo "Error"
            let "FALSE_TEST+=1"
        fi
        
    done
done

for flag1 in -b -e -n -s -t 
do
    for flag2 in -b -e -n -s -t 
    do
        for flag3 in -b -e -n -s -t 
        do
            for file in $FILE_1 $FILE_2 $FILE_3 $FILE_4
            do
                TEST_1="$flag1 $flag2 $flag3 $file"
                echo "$TEST_1"
                $COMMAND_1 $TEST_1 > $RES_1
                $COMMAND_2 $TEST_1 > $RES_2
                DIFF=$(diff $RES_1 $RES_2) 
                if [ "$DIFF" = "" ] 
                then
                    let "TRUE_TEST+=1"
                else
                    echo "Error"
                    let "FALSE_TEST+=1"
                fi
            done
        done
    done
done



for flag in -b -e -n -s -t 
do
    for file1 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
    do
        for file2 in $FILE_1 $FILE_2 $FILE_3 $FILE_4
        do
            TEST_1="$flag $TEMPLATE_1 $file1 $file2"
            echo "$TEST_1"
            $COMMAND_1 $TEST_1 > $RES_1
            $COMMAND_2 $TEST_1 > $RES_2
            DIFF=$(diff $RES_1 $RES_2)
            if [ "$DIFF" = "" ]
            then
                let "TRUE_TEST+=1"
            else
                echo "Error"
                let "FALSE_TEST+=1"
            fi

        done
    done
done

rm $RES_1 $RES_2
echo "SUCCESFUL: $TRUE_TEST"
echo "FAILED: $FALSE_TEST"