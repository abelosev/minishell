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

# exec_test "exit ------0"
# exec_test "exit \"666\""
# exec_test "exit '666'"
# exec_test "exit '-666'"
# exec_test "exit '+666'"
# exec_test "exit '----666'"
# exec_test "exit '++++666'"
# exec_test "exit '6'66"
# exec_test "exit '2'66'32'"
# exec_test "exit \"'666'\""
# exec_test "exit '\"666\"'"
# exec_test "exit '666\"666\"666'"
# exec_test "exit +\'666\"666\"666'"
# exec_test "exit -\'666\"666\"666'"
# exec_test "exit 9223372036854775807"
# exec_test "exit 9223372036854775808"
# exec_test "exit -9223372036854775808"
# exec_test "exit -9223372036854775809"
# exec_test "cat | cat | cat | ls"
# exec_test "ls | exit"
# exec_test "ls | exit 42"
# exec_test "exit | ls"
# exec_test "exit | cat -e bonjour"
# exec_test "echo hola > bonjour"
# exec_test "echo hola > bonjour"
# exec_test "cat -e bonjour | exit"
# exec_test "echo | echo"
# exec_test "echo hola | echo que tal"
# exec_test "pwd | echo hola"
# exec_test "env | echo hola"
# exec_test "echo oui | cat -e"
# exec_test "echo oui | echo non | echo hola | grep oui"
# exec_test "echo oui | echo non | echo hola | grep non"
# exec_test "echo oui | echo non | echo hola | grep hola"
# exec_test "echo hola | cat -e | cat -e | cat -e"
# exec_test "cd .. | echo \"hola\""
# exec_test "cd / | echo \"hola\""
# exec_test "cd .. | pwd"
# exec_test "ifconfig | grep \":\""
# exec_test "ifconfig | grep hola"
# exec_test "whoami | grep $USER"
# exec_test "whoami | grep $USER > /tmp/bonjour"
# exec_test "whoami | cat -e | cat -e > /tmp/bonjour"
# exec_test "whereis ls | cat -e | cat -e > /tmp/bonjour"
# exec_test "ls | hola"
# exec_test "ls | ls hola"
# exec_test "ls | ls | hola"
# exec_test "ls | hola | ls"
# exec_test "ls | ls | hola | rev"
# exec_test "ls | ls | echo hola | rev"
# exec_test "ls -la | grep \".\""
# exec_test "ls -la | grep \"'.'\""
# exec_test "echo test.c | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e"
# exec_test "ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls"
# exec_test "echo hola | cat | cat | cat | cat | cat | grep hola"
# exec_test "echo hola | cat"
# exec_test "echo hola| cat"
# exec_test "echo hola |cat"
# exec_test "echo hola|cat"
# exec_test "echo hola || cat"
# exec_test "echo hola ||| cat"
# exec_test "ech|o hola | cat"
# exec_test "cat Makefile | cat -e | cat -e"
# exec_test "cat Makefile | grep srcs | cat -e"
# exec_test "cat Makefile | grep srcs | grep srcs | cat -e"
# exec_test "cat Makefile | grep pr | head -n 5 | cd file_not_exist"
# exec_test "cat Makefile | grep pr | head -n 5 | hello"
# exec_test "export HOLA=bonjour | cat -e | cat -e"
# exec_test "unset HOLA | cat -e"
# exec_test "export HOLA | echo hola"
# exec_test "export | echo hola"
# exec_test "sleep 3 | sleep 3"
# exec_test "time sleep 3 | sleep 3"
# exec_test "sleep 3 | exit"
# exec_test "exit | sleep 3"
# exec_test "echo hola > a"
# exec_test ">>b echo que tal"
# exec_test "cat a | <b cat | cat > c | cat"
# exec_test "pwd && ls"
# exec_test "pwd || ls"
# exec_test "echo hola || echo bonjour"
# exec_test "echo hola && echo bonjour"
# exec_test "echo bonjour || echo hola"
# exec_test "echo bonjour && echo hola"
# exec_test "echo -n bonjour && echo -n hola"
# exec_test "pwd && ls && echo hola"
# exec_test "pwd || ls && echo hola"
# exec_test "pwd && ls || echo hola"
# exec_test "pwd || ls || echo hola"
# exec_test "ls || export \"\""
# exec_test "export \"\" || ls"
# exec_test "ls && export \"\""
# exec_test "export \"\" && ls"
# exec_test "ls || ;"
# exec_test "; || ls"
# exec_test "ls && ;"
# exec_test "; && ls"
# exec_test "ls || <"
# exec_test "ls && <"
# exec_test "cat | echo || ls"
# exec_test "cat | echo && ls"
# exec_test "ls || cat | echo"
# exec_test "ls && cat | echo"
# exec_test "export \"\" && unset \"\""

rm -rf minishell out1 test2 testpwd truc2