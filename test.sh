#!/bin/bash
# ==============================================================================
# run_tests.sh - test harness for minishell
#
# Usage:
#   ./run_tests.sh [path-to-minishell] [--no-build] [-v]
#
#   path-to-minishell   defaults to ./minishell
#   --no-build          skip the `make` step
#   -v                  also print input/output for passing tests, not just failures
#
# How it works: each test sends a small block of input lines to minishell over
# stdin, wrapped with two unique marker echoes and a trailing "echo $?" so we
# can reliably pull out just the tested command's output + exit status, no
# matter what your prompt looks like or whether it's printed at all. The
# result is compared either against real bash running the equivalent command
# (run_test), or against a literal string you supply yourself (run_test_raw
# and run_test_status_only), for cases where bash's own wording isn't a fair
# reference (e.g. custom "command not found" / cd error messages).
#
# COVERAGE NOTE: this harness feeds minishell via a plain pipe, which has no
# controlling TTY. That means anything relying on real terminal signal
# generation (Ctrl-C / Ctrl-\ turning into SIGINT/SIGQUIT via the line
# discipline's ISIG processing) or on readline's interactive history
# (Up/Down arrow recall) cannot be exercised this way — a raw 0x03/0x1c byte
# on a pipe is just data, not a signal. Those items are listed at the bottom
# as a manual checklist instead of being faked with something unreliable.
# Ctrl-D (EOF) *is* testable here, since EOF-on-read is exactly what closing
# the piped stdin produces, regardless of TTY.
# ==============================================================================

set -u

MINISHELL="./minishell"
DO_BUILD=1
VERBOSE=0

for arg in "$@"; do
	case "$arg" in
		--no-build) DO_BUILD=0 ;;
		-v) VERBOSE=1 ;;
		*) MINISHELL="$arg" ;;
	esac
done

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

PASS_COUNT=0
FAIL_COUNT=0
FAILED_TESTS=()

TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

START_MARK="__MS_TEST_START__"
END_MARK="__MS_TEST_END__"

# ---------- build -----------------------------------------------------------

if [ "$DO_BUILD" -eq 1 ]; then
	echo -e "${CYAN}${BOLD}==> Building project (make)${RESET}"
	if ! make -s > "$TMP_DIR/build.log" 2>&1; then
		echo -e "${RED}${BOLD}Build failed:${RESET}"
		cat "$TMP_DIR/build.log"
		exit 1
	fi
	echo -e "${GREEN}Build OK${RESET}\n"
fi

if [ ! -x "$MINISHELL" ]; then
	echo -e "${RED}${BOLD}Cannot find executable minishell at '$MINISHELL'${RESET}"
	exit 1
fi

# ---------- low-level capture -----------------------------------------------
#
# Sends: echo START / <input_block> / echo END:$? / exit
# to minishell, then pulls out (a) everything printed between the two marker
# echoes (the tested command's own stdout+stderr) and (b) the exit status
# that followed the END marker on the same line — using plain substring
# parameter expansion rather than line-based tools, so it still works even
# when the tested command suppresses its own trailing newline (e.g. `echo -n`)
# and the END marker ends up glued onto the same output line.

capture() {
	local input_block="$1"
	local ms_input ms_raw prompt_text after_start between after_end code_and_rest

	ms_input=$(printf 'echo %s\n%s\necho %s:$?\nexit\n' \
		"$START_MARK" "$input_block" "$END_MARK")
	ms_raw=$(printf '%s\n' "$ms_input" | "$MINISHELL" 2>&1)

	# Whatever the shell printed before it ever saw our first line is its
	# prompt (some shells print it unconditionally, even reading from a
	# pipe). Since prompt_loop builds the prompt string once per session,
	# it stays constant for the rest of this run, so we can safely strip
	# every later occurrence of it too.
	prompt_text="${ms_raw%%"$START_MARK"*}"

	after_start="${ms_raw#*"$START_MARK"}"
	between="${after_start%%"$END_MARK"*}"
	if [ -n "$prompt_text" ]; then
		between="${between//$prompt_text/}"
	fi
	between="${between#$'\n'}"
	between="${between%$'\n'}"

	after_end="${after_start#*"$END_MARK"}"
	code_and_rest="${after_end#:}"
	local code="${code_and_rest%%$'\n'*}"

	CAPTURED_OUTPUT="$between"
	CAPTURED_CODE="$code"
}

# format_result <output> <exit_code>
#
# Joins captured/expected output with its exit-status line consistently: no
# leading blank line when the command produced no output at all. Used by
# every assertion helper below so "actual" and "expected" are built the same
# way and never mismatch purely on this formatting choice.
format_result() {
	local output="$1" code="$2"
	if [ -z "$output" ]; then
		printf '%s' "$code"
	else
		printf '%s\n%s' "$output" "$code"
	fi
}

# ---------- assertion helpers -------------------------------------------------

report_pass() {
	PASS_COUNT=$((PASS_COUNT + 1))
	echo -e "${GREEN}[PASS]${RESET} $1"
}

report_fail() {
	local name="$1" input_block="$2" expected="$3" got="$4"
	FAIL_COUNT=$((FAIL_COUNT + 1))
	FAILED_TESTS+=("$name")
	echo -e "${RED}[FAIL]${RESET} $name"
	echo -e "  ${CYAN}input:${RESET}"
	echo "$input_block" | sed 's/^/    /'
	echo -e "  ${YELLOW}expected:${RESET}"
	echo "$expected" | sed 's/^/    /'
	echo -e "  ${RED}got:${RESET}"
	echo "$got" | sed 's/^/    /'
}

# run_test <name> <input_block> <bash_reference_command>
#
# <bash_reference_command> should be the plain, direct bash equivalent of
# input_block (statements joined with ';', '&&', '|', etc. as appropriate) —
# do NOT append your own "; echo $?", the harness adds that automatically and
# derives the expected exit status from bash's real exit code for you.
run_test() {
	local name="$1" input_block="$2" ref_cmd="$3"
	local bash_out bash_code expected

	capture "$input_block"

	bash_out=$(bash -c "$ref_cmd" 2>&1)
	bash_code=$(bash -c "$ref_cmd" > /dev/null 2>&1; echo $?)
	expected=$(format_result "$bash_out" "$bash_code")

	local actual
	actual=$(format_result "$CAPTURED_OUTPUT" "$CAPTURED_CODE")
	if [ "$actual" == "$expected" ]; then
		report_pass "$name"
		[ "$VERBOSE" -eq 1 ] && echo -e "  ${CYAN}output:${RESET} $actual"
	else
		report_fail "$name" "$input_block" "$expected" "$actual"
	fi
}

# run_test_raw <name> <input_block> <expected_literal>
#
# Use when bash's own message wording isn't an appropriate reference (e.g.
# your project's own "command not found" / cd error text). <expected_literal>
# should be the full expected output including the trailing exit-status line,
# e.g. $'somecmd: command not found\n127\n0' (last line = exit status of
# whatever the final line of input_block was).
run_test_raw() {
	local name="$1" input_block="$2" expected="$3"

	capture "$input_block"
	local actual
	actual=$(format_result "$CAPTURED_OUTPUT" "$CAPTURED_CODE")

	if [ "$actual" == "$expected" ]; then
		report_pass "$name"
		[ "$VERBOSE" -eq 1 ] && echo -e "  ${CYAN}output:${RESET} $actual"
	else
		report_fail "$name" "$input_block" "$expected" "$actual"
	fi
}

# run_test_status_only <name> <input_block> <bash_reference_command>
#
# Only checks the final exit status against bash's, ignoring stdout/stderr
# wording entirely. Use for builtins whose error text is implementation-
# specific (cd, custom messages) but whose exit code is well-defined.
run_test_status_only() {
	local name="$1" input_block="$2" ref_cmd="$3"

	capture "$input_block"
	local bash_code
	bash_code=$(bash -c "$ref_cmd" > /dev/null 2>&1; echo $?)

	if [ "$CAPTURED_CODE" == "$bash_code" ]; then
		report_pass "$name (status $CAPTURED_CODE)"
	else
		report_fail "$name" "$input_block" "exit status $bash_code" \
			"exit status $CAPTURED_CODE (output was: $CAPTURED_OUTPUT)"
	fi
}

# run_test_process_exit <name> <input_block> <bash_reference_command>
#
# For cases where the tested command terminates the shell itself (e.g. the
# `exit` builtin actually exiting) — the marker-based capture() can't be used
# here because "echo END:$?" and the trailing "exit" appended by capture()
# would never run. Instead this feeds input_block directly and compares the
# *process's own* exit code against bash -c's own exit code for the same
# script, which is the correct analogue (bash -c's exit status IS whatever
# "exit N" inside it produced).
run_test_process_exit() {
	local name="$1" input_block="$2" ref_cmd="$3"
	local actual_code bash_code

	printf '%s\n' "$input_block" | "$MINISHELL" > /dev/null 2>&1
	actual_code=$?

	bash -c "$ref_cmd" > /dev/null 2>&1
	bash_code=$?

	if [ "$actual_code" == "$bash_code" ]; then
		report_pass "$name (process exit code $actual_code)"
	else
		report_fail "$name" "$input_block" \
			"process exit code $bash_code" "process exit code $actual_code"
	fi
}

# ==============================================================================
# TEST SUITE
# ==============================================================================

echo -e "${CYAN}${BOLD}==> simple commands & empty input${RESET}"
run_test "absolute path simple command" '/bin/ls /tmp' '/bin/ls /tmp'
run_test "empty command line produces no output, status unchanged" \
	$'true\n' 'true'
run_test "line with only spaces produces no output" \
	$'true\n   ' 'true;   '
run_test "line with only tabs produces no output" \
	$'true\n\t\t' $'true;\t\t'

echo -e "\n${CYAN}${BOLD}==> arguments${RESET}"
run_test "command with multiple arguments" '/bin/ls -l -a /tmp' '/bin/ls -l -a /tmp'
run_test "command with one argument, no path lookup needed" 'wc -l /etc/hostname' 'wc -l /etc/hostname'

echo -e "\n${CYAN}${BOLD}==> echo${RESET}"
run_test "echo simple"                 'echo hello world'  'echo hello world'
run_test "echo -n suppresses newline"  'echo -n hello'     'echo -n hello'
run_test "echo no args"                'echo'              'echo'
run_test "echo collapses shell-level spacing" 'echo a   b   c' 'echo a b c'

echo -e "\n${CYAN}${BOLD}==> exit${RESET}"
run_test_process_exit "exit with no args uses last status" \
	$'false\nexit' $'false\nexit'
run_test_process_exit "exit with numeric arg" \
	'exit 42' 'exit 42'
run_test_process_exit "exit with out-of-range numeric arg wraps mod 256" \
	'exit 300' 'exit 300'
run_test_process_exit "exit with non-numeric arg errors and exits" \
	'exit abc' 'exit abc'
run_test_status_only "exit with too many arguments does not exit, sets status" \
	'exit 1 2' 'exit 1 2'
run_test "shell survives exit with too many arguments and keeps running" \
	$'exit 1 2\necho still_alive' $'exit 1 2; echo still_alive'

echo -e "\n${CYAN}${BOLD}==> EOF (Ctrl-D) handling${RESET}"
# A closed/empty pipe stdin delivers EOF to read() exactly like Ctrl-D does
# at an empty interactive prompt — this part is genuinely testable headless.
eof_code=$(printf '' | timeout 2 "$MINISHELL" > /dev/null 2>&1; echo $?)
if [ "$eof_code" == "0" ]; then
	report_pass "EOF on empty prompt exits minishell cleanly (status 0)"
elif [ "$eof_code" == "124" ]; then
	report_fail "EOF on empty prompt exits minishell cleanly" \
		"(empty stdin, immediate EOF)" "exit status 0, no hang" \
		"timed out after 2s — shell is hanging on EOF instead of exiting"
else
	report_fail "EOF on empty prompt exits minishell cleanly" \
		"(empty stdin, immediate EOF)" "exit status 0" "exit status $eof_code"
fi

eof_partial_code=$(printf 'cd /tmp' | timeout 2 "$MINISHELL" > /dev/null 2>&1; echo $?)
if [ "$eof_partial_code" == "0" ]; then
	report_pass "EOF after a command with no trailing newline still exits cleanly"
elif [ "$eof_partial_code" == "124" ]; then
	report_fail "EOF after a command with no trailing newline still exits cleanly" \
		"(cd /tmp, no trailing newline, then EOF)" "exit status 0, no hang" \
		"timed out after 2s — shell is hanging"
else
	report_fail "EOF after a command with no trailing newline still exits cleanly" \
		"(cd /tmp, no trailing newline, then EOF)" "exit status 0" "exit status $eof_partial_code"
fi

echo -e "\n${CYAN}${BOLD}==> pwd${RESET}"
run_test "pwd prints cwd" 'pwd' 'pwd'
run_test "pwd after cd reflects new directory" $'cd /tmp\npwd' 'cd /tmp && pwd'

echo -e "\n${CYAN}${BOLD}==> cd${RESET}"
run_test "cd absolute path then pwd" $'cd /tmp\npwd' 'cd /tmp && pwd'
run_test "cd relative path then pwd" $'cd /\ncd tmp\npwd' 'cd / && cd tmp && pwd'
run_test "cd . stays in same directory" $'cd /tmp\ncd .\npwd' 'cd /tmp && cd . && pwd'
run_test "cd .. moves up a directory" $'cd /tmp\ncd ..\npwd' 'cd /tmp && cd .. && pwd'
run_test_status_only "cd nonexistent dir fails with status 1" \
	'cd /no/such/dir/xyz' 'cd /no/such/dir/xyz'
run_test "cd - returns to OLDPWD and echoes it" \
	$'cd /tmp\ncd /\ncd -\npwd' 'cd /tmp && cd / && cd - && pwd'

echo -e "\n${CYAN}${BOLD}==> relative paths${RESET}"
mkdir -p "$TMP_DIR/reldir/nested"
cat > "$TMP_DIR/reldir/hello.sh" <<'EOS'
#!/bin/sh
echo hello_from_relative
EOS
chmod +x "$TMP_DIR/reldir/hello.sh"
run_test "execute via simple relative path" \
	"cd $TMP_DIR/reldir
./hello.sh" \
	"cd $TMP_DIR/reldir && ./hello.sh"
run_test "execute via complex relative path with multiple .." \
	"cd $TMP_DIR/reldir/nested
../../reldir/nested/../hello.sh" \
	"cd $TMP_DIR/reldir/nested && ../../reldir/nested/../hello.sh"

echo -e "\n${CYAN}${BOLD}==> exit status (\$?)${RESET}"
run_test "successful external command status 0" 'ls /tmp' 'ls /tmp'
run_test "failing external command status nonzero" \
	$'ls /no/such/dir\necho $?' 'ls /no/such/dir; echo $?'
run_test "cd success then \$? reflects it" $'cd /tmp\necho $?' 'cd /tmp; echo $?'
run_test "\$? used twice in one command (expr \$? + \$?)" \
	$'ls /no/such/dir_xyz\nexpr $? + $?' 'ls /no/such/dir_xyz; expr $? + $?'

echo -e "\n${CYAN}${BOLD}==> environment path (\$PATH)${RESET}"
pathdir1="$TMP_DIR/pathbin1"
pathdir2="$TMP_DIR/pathbin2"
mkdir -p "$pathdir1" "$pathdir2"
cat > "$pathdir1/mytool" <<'EOS'
#!/bin/sh
echo from_dir1
EOS
cat > "$pathdir2/mytool" <<'EOS'
#!/bin/sh
echo from_dir2
EOS
chmod +x "$pathdir1/mytool" "$pathdir2/mytool"
run_test "PATH order: left directory takes priority" \
	"export PATH=$pathdir1:$pathdir2:\$PATH
mytool" \
	"export PATH=$pathdir1:$pathdir2:\$PATH && mytool"
run_test_status_only "unset PATH makes external commands fail" \
	$'unset PATH\nls /tmp' 'unset PATH; ls /tmp'

echo -e "\n${CYAN}${BOLD}==> environment: export / unset / env${RESET}"
run_test "export then echo expands var" \
	$'export FOO=bar\necho $FOO' 'export FOO=bar; echo $FOO'
run_test "unset removes var" \
	$'export FOO=bar\nunset FOO\necho $FOO' 'export FOO=bar; unset FOO; echo $FOO'
run_test "export no value creates bare var (visible via export -p)" \
	$'export BARE\nexport | grep BARE' 'export BARE; export | grep BARE'
run_test "env shows exported variable" \
	$'export FOO=bar\nenv | grep ^FOO=' 'export FOO=bar; env | grep ^FOO='
run_test "unset then env no longer shows variable" \
	$'export FOO=bar\nunset FOO\nenv | grep ^FOO=' \
	'export FOO=bar; unset FOO; env | grep ^FOO='

echo -e "\n${CYAN}${BOLD}==> quoting${RESET}"
run_test "single quotes prevent expansion" \
	$'export FOO=bar\necho '"'"'$FOO'"'" 'export FOO=bar; echo '"'"'$FOO'"'"
run_test "single quotes with empty argument" \
	"echo ''" "echo ''"
run_test "single quotes preserve pipes and redirection chars literally" \
	"echo 'a | b > c'" "echo 'a | b > c'"
run_test "double quotes still expand" \
	$'export FOO=bar\necho "$FOO"' 'export FOO=bar; echo "$FOO"'
run_test "quotes concatenate with bare word" \
	'echo hel"lo wor"ld' 'echo hel"lo wor"ld'

echo -e "\n${CYAN}${BOLD}==> environment variables${RESET}"
run_test "echo \$USER expands to current user" \
	$'export USER=testuser\necho $USER' 'export USER=testuser; echo $USER'
run_test "echo \"\$USER\" expands inside double quotes" \
	$'export USER=testuser\necho "$USER"' 'export USER=testuser; echo "$USER"'

echo -e "\n${CYAN}${BOLD}==> pipes${RESET}"
run_test "two-stage pipe" 'echo hello | cat' 'echo hello | cat'
run_test "three-stage pipe with wc" \
	$'echo -e "a\\nb\\nc" | cat | wc -l' 'echo -e "a\nb\nc" | cat | wc -l'
run_test_status_only "wrong command inside pipe chain does not crash" \
	'ls /no/such/dir/xyz | grep bla | wc -l' 'ls /no/such/dir/xyz | grep bla | wc -l'
run_test "safe stand-in for 'cat | cat | ls' using piped data, not a blocking read" \
	$'echo piped_data | cat | cat | wc -l' 'echo piped_data | cat | cat | wc -l'
run_test "long command with many arguments" \
	"echo $(seq 1 100 | tr '\n' ' ')" "echo $(seq 1 100 | tr '\n' ' ')"

echo -e "\n${CYAN}${BOLD}==> redirections${RESET}"
out1="$TMP_DIR/out1.txt"
out1_ref="$TMP_DIR/out1_ref.txt"
run_test "output redirection creates file" \
	"$(printf 'echo hi > %s\ncat %s' "$out1" "$out1")" \
	"echo hi > $out1_ref; cat $out1_ref"

out2="$TMP_DIR/out2.txt"
out2_ref="$TMP_DIR/out2_ref.txt"
run_test "append redirection" \
	"$(printf 'echo one > %s\necho two >> %s\ncat %s' "$out2" "$out2" "$out2")" \
	"echo one > $out2_ref; echo two >> $out2_ref; cat $out2_ref"

in1="$TMP_DIR/in1.txt"
run_test "input redirection" \
	"$(printf 'echo fromfile > %s\ncat < %s' "$in1" "$in1")" \
	"echo fromfile > $in1; cat < $in1"

out3="$TMP_DIR/out3.txt"
out3_ref="$TMP_DIR/out3_ref.txt"
run_test "repeated > redirection truncates each time, doesn't accumulate" \
	"$(printf 'echo first > %s\necho second > %s\ncat %s' "$out3" "$out3" "$out3")" \
	"echo first > $out3_ref; echo second > $out3_ref; cat $out3_ref"

out4="$TMP_DIR/out4.txt"
out4_ref="$TMP_DIR/out4_ref.txt"
run_test "pipe output redirected to a file" \
	"$(printf 'echo hello | cat > %s\ncat %s' "$out4" "$out4")" \
	"echo hello | cat > $out4_ref; cat $out4_ref"

echo -e "\n${CYAN}${BOLD}==> heredoc${RESET}"
run_test "heredoc feeds cat until delimiter" \
	$'cat << EOF\nline one\nline two\nEOF' \
	$'cat << EOF\nline one\nline two\nEOF'
run_test "heredoc with variable expansion (unquoted delimiter)" \
	$'export FOO=bar\ncat << EOF\nvalue is $FOO\nEOF' \
	$'export FOO=bar\ncat << EOF\nvalue is $FOO\nEOF'
run_test "heredoc with quoted delimiter suppresses expansion" \
	$'export FOO=bar\ncat << '"'"'EOF'"'"'\nvalue is $FOO\nEOF' \
	$'export FOO=bar\ncat << '"'"'EOF'"'"'\nvalue is $FOO\nEOF'

echo -e "\n${CYAN}${BOLD}==> command not found${RESET}"
# bash's own "command not found" wording differs from a custom minishell's;
# checking the exact literal text here assumes the project reports errors as
# "<cmd>: command not found" on stderr, matching the executor implementation
# reviewed earlier in this project. Adjust the literal below if your wording
# differs.
run_test_raw "unknown command reports not found, status 127" \
	'thiscommanddoesnotexist123' \
	$'thiscommanddoesnotexist123: command not found\n127'
run_test_raw "\$? is 127 right after command-not-found" \
	$'thiscommanddoesnotexist123\necho $?' \
	$'thiscommanddoesnotexist123: command not found\n127\n0'
run_test_raw "unknown command inside a longer script doesn't crash the shell" \
	$'dsbksdgbksdghsd\necho survived' \
	$'dsbksdgbksdghsd: command not found\nsurvived\n0'

# ------------------------------------------------------------------------
# BONUS: && / || with parentheses, wildcards
# ------------------------------------------------------------------------

echo -e "\n${CYAN}${BOLD}==> bonus: && / ||${RESET}"
run_test "&& runs second only if first succeeds" \
	'true && echo yes' 'true && echo yes'
run_test "&& skips second if first fails" \
	'false && echo should_not_print' 'false && echo should_not_print'
run_test "|| runs second only if first fails" \
	'false || echo fallback' 'false || echo fallback'
run_test "|| skipped if first succeeds" \
	'true || echo should_not_print' 'true || echo should_not_print'
run_test "parentheses group precedence" \
	'(false || true) && echo grouped_ok' '(false || true) && echo grouped_ok'
run_test "chained &&/|| without parens, left to right" \
	'false && echo a || echo b' 'false && echo a || echo b'

echo -e "\n${CYAN}${BOLD}==> bonus: wildcards${RESET}"
mkdir -p "$TMP_DIR/wctest"
touch "$TMP_DIR/wctest/aaa.txt" "$TMP_DIR/wctest/bbb.txt" "$TMP_DIR/wctest/ccc.log"
run_test "wildcard expands *.txt in target dir" \
	"cd $TMP_DIR/wctest
echo *.txt" \
	"cd $TMP_DIR/wctest && echo *.txt"
run_test "bare wildcard expands all entries" \
	"cd $TMP_DIR/wctest
echo *" \
	"cd $TMP_DIR/wctest && echo *"

echo -e "\n${CYAN}${BOLD}==> bonus: surprise (nested quote interpolation)${RESET}"
# echo "'$USER'"  -> double quotes still expand $USER; the single quote
# characters inside are just literal characters, not real quoting.
surprise_line1="echo \"'\$USER'\""
run_test "echo \"'\$USER'\" expands USER, quotes stay literal" \
	$'export USER=testuser\n'"$surprise_line1" \
	"export USER=testuser; $surprise_line1"

# echo '"$USER"'  -> single quotes suppress everything, prints literally.
surprise_line2="echo '\"\$USER\"'"
run_test "echo '\"\$USER\"' prints literally, no expansion" \
	$'export USER=testuser\n'"$surprise_line2" \
	"export USER=testuser; $surprise_line2"

# ==============================================================================
# MANUAL-ONLY CHECKLIST (cannot be automated without a real/pseudo TTY)
# ==============================================================================
#
# The items below require actual terminal signal generation (ISIG) or
# readline's interactive history recall, neither of which exist on a plain
# piped stdin. Run these by hand with $MINISHELL in a real terminal:
#
#   [ ] Ctrl-C on an empty prompt -> new line + new prompt, no crash
#   [ ] Ctrl-\ on an empty prompt -> nothing happens
#   [ ] Ctrl-C after typing a partial command -> line is cleared, new prompt,
#       pressing Enter afterward executes nothing
#   [ ] Ctrl-\ after typing a partial command -> nothing happens
#   [ ] Ctrl-C while a blocking child is running (e.g. `cat` with no args,
#       or `grep something` with no file) -> child is interrupted, shell
#       returns to a fresh prompt, minishell itself does not exit
#   [ ] Ctrl-\ while a blocking child is running -> same as above but via
#       SIGQUIT; minishell itself must not exit or print anything itself
#   [ ] Ctrl-D while a blocking child is running -> behavior matches bash
#       (typically ends the child's stdin without killing minishell)
#   [ ] Up/Down arrow recall previous commands via readline history
#   [ ] Re-running a recalled history entry executes it correctly
#
# ==============================================================================
# SUMMARY
# ==============================================================================

TOTAL=$((PASS_COUNT + FAIL_COUNT))
echo ""
echo -e "${BOLD}==============================${RESET}"
echo -e "${BOLD}Results: ${GREEN}${PASS_COUNT} passed${RESET}, ${RED}${FAIL_COUNT} failed${RESET} (of ${TOTAL})"
if [ "$FAIL_COUNT" -gt 0 ]; then
	echo -e "${RED}${BOLD}Failed tests:${RESET}"
	for t in "${FAILED_TESTS[@]}"; do
		echo -e "  ${RED}- $t${RESET}"
	done
fi
echo -e "${BOLD}==============================${RESET}"
echo -e "${YELLOW}Note: signal (Ctrl-C/Ctrl-\\\\) and readline history behavior are"
echo -e "not covered above — see the manual checklist in this script's source.${RESET}"

[ "$FAIL_COUNT" -eq 0 ]