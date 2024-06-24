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

exec_test "cd ./"
exec_test "cd ./././."
exec_test "cd ././././"
exec_test "cd .."
exec_test "cd ../"
exec_test "cd ../.."
exec_test "cd ../."
exec_test "cd .././././."
exec_test "cd srcs"
exec_test "cd srcs objs"
exec_test "cd 'srcs'"
exec_test "cd \"srcs\""
exec_test "cd '/etc'"
exec_test "cd /e'tc'"
exec_test "cd /e\"tc\""
exec_test "cd sr"
exec_test "cd Makefile"
exec_test "cd ../minishell"
exec_test "cd ../../../../../../.."
exec_test "cd .././../.././../bin/ls"
exec_test "cd /"
exec_test "cd '/'"
exec_test "cd //"
exec_test "cd '//'"
exec_test "cd ///"
exec_test "cd ////////"
exec_test "cd '/////////'"
exec_test "cd /minishell"
exec_test "cd /"
exec_test "cd _"
exec_test "cd -"
exec_test "cd --"
exec_test "cd ---"
exec_test "cd \$HOME"
exec_test "cd \$HOME \$HOME"
exec_test "cd \"\$PWD/srcs\""
exec_test "cd \"\$PWD/srcs\""
exec_test "unset HOME"
exec_test "unset HOME"
exec_test "cd \"minishell Docs crashtest.c\""
exec_test "cd / | echo \$?"
exec_test "cd ~"
exec_test "cd ~/ | echo \$?"
# exec_test "cd *"
# exec_test "cd *"
# exec_test "cd *"
# exec_test "mkdir a"
# exec_test "mkdir a/b"
# exec_test "mkdir a"
# exec_test "mkdir a/b"
# exec_test "mkdir a"
# exec_test "mkdir a/b"
# exec_test "export CDPATH=/"
# exec_test "export CDPATH=/"
# exec_test "export CDPATH=./"
# exec_test "export CDPATH=./"
# exec_test chmod 000 minishell"
# exec_test "ls hola"
# exec_test "./Makefile"
# exec_test "./minishell"
# exec_test "env | grep SHLVL"
# exec_test "touch hola"
# exec_test "env|\"wc\" -l"
# exec_test "env|\"wc \"-l"
# exec_test "expr 1 + 1"
# exec_test "expr \$? + \$?"
# exec_test "env -i ./minishell"
# exec_test "env -i ./minishell"
# exec_test "env -i ./minishell"
# exec_test "env -i ./minishell"
# exec_test "EXIT ⛔ # exec_test exit"
exec_test "exit exit"
exec_test "exit hola"
exec_test "exit hola que tal"
exec_test "exit 42"
exec_test "exit 000042"
exec_test "exit 666"
exec_test "exit 666 666"
exec_test "exit -666 666"
exec_test "exit hola 666"
exec_test "exit 666 666 666 666"
exec_test "exit 666 hola 666"
exec_test "exit hola 666 666"
exec_test "exit 259"
exec_test "exit -4"
exec_test "exit -42"
exec_test "exit -0000042"
exec_test "exit -259"
exec_test "exit -666"
exec_test "exit +666"
exec_test "exit 0"
exec_test "exit +0"
exec_test "exit -0"
exec_test "exit +42"
exec_test "exit -69 -96"
exec_test "exit --666"
exec_test "exit ++++666"
exec_test "exit ++++++0"

rm -rf minishell out1 test2 testpwd truc2