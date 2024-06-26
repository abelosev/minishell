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

exec_test "echo -nnnnn"
exec_test "echo -n -nnn -nnnn"
exec_test "echo -n-nnn -nnnn"
exec_test "echo -n -nnn hola -nnnn"
exec_test "echo -n -nnn-nnnn"
exec_test "echo --------n"
exec_test "echo -nnn --------n"
exec_test "echo -nnn -----nn---nnnn"
exec_test "echo -nnn --------nnnn"
exec_test "echo $"
exec_test "echo $?"
exec_test "echo $?$"
exec_test "echo $? | echo $? | echo $?"
exec_test "echo $:$= | cat -e"
exec_test "echo \" $ \" | cat -e"
exec_test "echo ' $ ' | cat -e"
# exec_test "echo \$HOME"
exec_test "echo my shit terminal is [$TERM]"
exec_test "echo my shit terminal is [$TERM4"
exec_test "echo my shit terminal is [$TERM4]"
exec_test "echo $UID"
exec_test "echo $HOME9"
exec_test "echo $9HOME"
exec_test "echo $HOME%"
exec_test "echo $UID$HOME"
exec_test "echo Le path de mon HOME est $HOME"
exec_test "echo $USER$var\$USER$USER\$USERtest$USER"
# exec_test "echo $hola*"
exec_test "echo -nnnn $hola"
exec_test "echo > <"
exec_test "echo | |"
exec_test "EechoE"
exec_test ".echo."
exec_test ">echo>"
exec_test "<echo<"
exec_test ">>echo>>"
exec_test "|echo|"
exec_test "|echo -n hola"
exec_test "echo $"
exec_test "echo $\"\""
exec_test "echo '$'''"
exec_test "echo $\"HOME\""
exec_test "echo $''HOME"
exec_test "echo $\"\"HOME"
exec_test "echo \"$HO\"ME"
exec_test "echo '$HO'ME"
exec_test "echo \"$HO\"\"ME\""
exec_test "echo '$HO''ME'"
exec_test "echo \"'$HO''ME'\""
exec_test "echo \"\"$HOME"
exec_test "echo \"\" $HOME"
exec_test "echo ''$HOME"
exec_test "echo '' $HOME"
exec_test "echo $\"HO\"\"ME\""
exec_test "echo $'HO''ME'"
exec_test "echo $'HOME'"
exec_test "echo \"$\"HOME"
exec_test "echo $=HOME"
exec_test "echo $\"HOLA\""
exec_test "echo $'HOLA'"
exec_test "echo $DONTEXIST Hola"
exec_test "echo \"hola\""
exec_test "echo 'hola'"
exec_test "echo ''hola''"
exec_test "echo ''h'o'la''"
exec_test "echo \"''h'o'la''\""
exec_test "echo \"'\"h'o'la\"'\""
exec_test "echo\"'hola'\""
exec_test "echo \"'hola'\""
exec_test "echo '\"hola\"'"
exec_test "echo '''ho\"''''l\"a'''"
exec_test "echo hola\"\"\"\"\"\"\"\"\"\""
exec_test "echo hola\"''''''''''\""
exec_test "echo hola''''''''''''"
exec_test "echo hola'\"\"\"\"\"\"\"\"'"
exec_test "e\"cho hola\""
exec_test "e'cho hola'"
exec_test "echo \"hola \" | cat -e"
exec_test "echo \"\"hola"
exec_test "echo \"\" hola"  #из-за снятия кавычек
exec_test "echo \"\" hola"
exec_test "echo \"\"hola"
exec_test "echo \"\" hola"
exec_test "echo hola\"\"bonjour"
exec_test "\"e\"'c'ho 'b'\"o\"nj\"o\"'u'r"
exec_test "\"\"e\"'c'ho 'b'\"o\"nj\"o\"'u'r\""
exec_test "echo \"$DONTEXIST\"Makefile"
exec_test "echo \"$DONTEXIST\"\"Makefile\""

rm -rf minishell out1 test2 testpwd truc2