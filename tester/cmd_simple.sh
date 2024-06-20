#!/bin/bash

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLD="\033[1m"
BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

# Compile and set executable rights
make -C ../ > /dev/null
cp ../minishell .
chmod 755 minishell
##ya peut etre un truc avec read pour les ';'

pipe=/tmp/testpipe
trap "rm -f $pipe" EXIT
if [[ ! -p $pipe ]]; then
    mkfifo $pipe
fi

function exec_test()
{
	rm -f msh_log
	# execute commands, separated by ';' in minishell, using nfifo
	./minishell <$pipe >msh_log 2>&- &
	mshpid=$!
	IFS=';' read -ra CMND <<< "$@"
	for command in "${CMND[@]}"; do
		echo $command > $pipe
	done

	echo 'exit' > $pipe 
	sleep 0.03
	wait $!
	ES_1=$?
	TEST1=$(cat msh_log)

	rm -f msh_log
	#TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
	#ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		printf " $BOLD$GREEN%s$RESET" "✓ "
	else
		printf " $BOLD$RED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLD$RED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLD$GREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		echo
		echo
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n"
	fi
	echo
	sleep 0.01
}

#Simple Command
exec_test "/bin/ls"
exec_test "ls"
exec_test "env"
exec_test ""
exec_test "    "
exec_test "			"
exec_test "   	 "
exec_test "cat test_cases.c"
exec_test "wc test_cases.c"


#Arguments
exec_test "/bin/ls -la"
exec_test "/bin/ls -l -a"
exec_test "ls \"-la\""
# добавить еще

#Path
exec_test "/bin/echo"
exec_test "/bin/echo Hola Que Tal"
exec_test "/bin/env"
exec_test ""
exec_test ""
exec_test ""

#cmd not found (or no such file or directory)
exec_test "-"
exec_test "\"hola\""
exec_test "'hola'"
exec_test "hola que tal"
exec_test "Makefile"
exec_test "echoHola"
exec_test "echo-nHola"
exec_test "EechoE"
exec_test ".echo."
exec_test "//bin/env"
exec_test "/bin/cd Desktop"
exec_test "ech|o hola | cat"


rm -rf minishell out1 test2 testpwd truc2

exec_test ""
exec_test ""
exec_test ""