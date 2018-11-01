function leak_test()
{
    local PROG_PATH=$1       # 1st argument: The path to the executable to test
    echo $PROG_PATH
    # # run the executable silently and send it to background using '&'
    # ($PROG_PATH >/dev/null 2>&1) &

    # # get its process ID with '$!' and save it in a variable PID
    # PID=$!

    # echo $PID

    # # wait for 5 seconds to let the executable generating memory leak (or not)
    # sleep 5

    # # check if the process is still running in background
    # # if not, we cannot detect memory leak and we must stop the test
    # if [ -z "$(ps a | awk -v PID=$PID '$1 == PID {print}')" ]
    # then
    #     echo "An error occurred: The program has terminated too quickly"
    #     return
    # fi

    # # run the 'leaks' command with the process ID as argument,
    # # and save the outputted line where total leaked bytes appears
    # RESULT=$(leaks $PID 2>/dev/null | grep 'total leaked bytes')

    # # note: the user may be asked for his administrator password
    # # that's why we need the executable to be running 15 seconds at least
    # # letting the user entering his password if necessary

    # # kill the executable, as we do not need it to be running anymore
    # kill -9 $PID >/dev/null 2>&1

    # # test if RESULT is empty
    # if [ -z "$RESULT" ]
    # then
    #     # if yes, that means the command 'leaks' has failed
    #     echo "An error occurred: Unable to detect memory leak"
    # else
    #     # otherwise, display the total leaked bytes
    #     echo $RESULT
    # fi
}

leak_test $1