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

exec_test "export HOLA=\" bonjour hey \""
exec_test "echo \$HOLA | cat -e"
exec_test "export HOLA=\" bonjour hey \""
exec_test "echo \"\"\"\$HOLA\"\"\" | cat -e"
exec_test "export HOLA=\" bonjour hey \""
exec_test "echo wesh\"\$HOLA\" | cat -e"
exec_test "export HOLA=\" bonjour hey \""
exec_test "echo wesh\"\"\$HOLA\"."
exec_test "export HOLA=\" bonjour hey \""
exec_test "echo wesh\$\"\"HOLA."
exec_test "export HOLA=\" bonjour hey \""
exec_test "echo wesh\$\"HOLA HOLA\"."
exec_test "export HOLA=bonjour"
exec_test "export HOLA=\" hola et \$HOLA\""
exec_test "export HOLA=bonjour"
exec_test "export HOLA=' hola et \$HOLA'"
exec_test "export HOLA=bonjour"
exec_test "export HOLA=\" hola et \$HOLA\"\$HOLA"
exec_test "export HOLA=\"ls -l - a\""
exec_test "export HOLA=\"s -la\""
exec_test "l\$HOLA"
exec_test "export HOLA=\"s -la\""
exec_test "l\"\$HOLA\""
exec_test "export HOLA=\"l\""
# exec_test "\$HOLAs"
exec_test "export HOLA=\"l\""
exec_test "\"\$HOLA\"s"
exec_test "export HOL=A=bonjour"
exec_test "env"
exec_test "export HOLA=\"l\""
exec_test "'\$HOLA's"
exec_test "export HOL=A=\"\""
exec_test "env"
exec_test "export TE+S=T"
exec_test "export \"\"=\"\""
exec_test "export ''=''"
exec_test "export \"=\"=\"=\""
exec_test "export '='='='"
exec_test "export HOLA=p"
exec_test "export BYE=w"
exec_test "\$HOLA\"BYE\"d"
exec_test "export HOLA=p"
exec_test "export BYE=w"
exec_test "\"\$HOLA\"'\$BYE'd"
exec_test "export HOLA=p"
exec_test "export BYE=w"
exec_test "\"\$HOLA\"\$\"BYE\"d"
exec_test "export HOLA=p"
exec_test "export BYE=w"
exec_test "\$\"HOLA\"\$\"BYE\"d"
exec_test "export HOLA=p"
exec_test "export BYE=w"
exec_test "\$'HOLA'\$'BYE'd"
exec_test "export HOLA=-n"
exec_test "\"echo \$HOLA\" hey"
exec_test "export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8"
exec_test "echo \"\$A'\$B'\$C\"\$D'\$E'\"\$F\"'\"\$G'\$H\""
# exec_test "export HOLA=bonjour"
# exec_test "env"
# exec_test "unset HOLA"
# exec_test "env"
# exec_test "unset HOLA"
# exec_test "unset HOLA"
# exec_test "env"
# exec_test "unset PATH"
# exec_test "echo \$PATH"
# exec_test "unset PATH"
# exec_test "ls"
# exec_test "unset \"\""
# exec_test "unset INEXISTANT"
# exec_test "unset PWD"
# exec_test "env | grep PWD"
# exec_test "pwd"
# exec_test "unset PWD"
# exec_test "env | grep PWD"
# exec_test "cd \$PWD"
# exec_test "pwd"
# exec_test "unset OLDPWD"
# exec_test "env | grep OLDPWD"
# exec_test "unset 9HOLA"
# exec_test "unset HOLA9"
# exec_test "unset HOL?A"
# exec_test "unset HOLA HOL?A"
# exec_test "unset HOL?A HOLA"
# exec_test "unset HOL?A HOL.A"
# exec_test "unset HOLA="
# exec_test "unset HOL\\\\A"
# exec_test "unset HOL;A"
# exec_test "unset HOL.A"
# exec_test "unset HOL+A"
# exec_test "unset HOL=A"
# exec_test "unset HOL{A"
# exec_test "unset HOL}A"
# exec_test "unset HOL-A"
# exec_test "unset -HOLA"
# exec_test "unset _HOLA"
# exec_test "unset HOL_A"
# exec_test "unset HOLA_"
# exec_test "unset HOL*A"
# exec_test "unset HOL#A"
# exec_test "unset \$HOLA"
# exec_test "unset \$PWD"
# exec_test "unset HOL@"
# exec_test "unset HOL!A"
# exec_test "unset HOL^A"
# exec_test "unset HOL\$?A"
# exec_test "unset HOL\\~A"
# exec_test "unset \"\" HOLA"
# exec_test "unset PATH"
# exec_test "echo \$PATH"
# exec_test "unset PATH"
# exec_test "cat Makefile"
# exec_test "unset ="
# exec_test "unset ======="
# exec_test "unset ++++++"
# exec_test "unset _______"
# exec_test "unset export"
# exec_test "unset echo"
# exec_test "unset pwd"
# exec_test "unset cd"
# exec_test "unset unset"
# exec_test "unset sudo"
# exec_test "export hola | unset hola | echo \$?"
# exec_test "/bin/echo"
# exec_test "/bin/echo Hola Que Tal"
# exec_test "/bin/env"
# exec_test "/bin/cd Desktop"

rm -rf minishell out1 test2 testpwd truc2