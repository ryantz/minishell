#!/bin/bash
# test.sh
MINISHELL=./minishell

run_test() {
    cmd="$1"
    bash_out=$(bash -c "$cmd" 2>&1)
    bash_exit=$?

    mini_out=$(echo "$cmd" | $MINISHELL 2>&1 | grep -v "^$cmd$" | grep -v "^exit$")
    mini_exit=${PIPESTATUS[0]}

    if [ "$bash_out" == "$mini_out" ] && [ "$bash_exit" == "$mini_exit" ]; then
        echo "PASS: $cmd"
    else
        echo "FAIL: $cmd"
        echo "  bash:  '$bash_out' (exit $bash_exit)"
        echo "  mini:  '$mini_out' (exit $mini_exit)"
    fi
}

run_test "echo hello"
run_test "echo \$HOME"
run_test "ls -l | grep .c"
run_test "cat nonexistent_file"
run_test "export FOO=bar && echo \$FOO"
