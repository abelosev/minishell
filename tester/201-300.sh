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

# exec_test "$>"
# exec_test "$?"
# exec_test "$?$?"
# exec_test "?$HOME"
# exec_test "$"
# exec_test "$HOME"
# exec_test "$HOMEdskjhfkdshfsd"
# exec_test "\"$HOMEdskjhfkdshfsd\""
# exec_test "'$HOMEdskjhfkdshfsd'"
# exec_test "$DONTEXIST"
# exec_test "$LESS$VAR"
# exec_test "env"
# exec_test "env hola"
# exec_test "env hola que tal"
# exec_test "env env"
# exec_test "env env env env env"
# exec_test "env ls"
# exec_test "env ./Makefile"
# exec_test "export HOLA=bonjour"
# exec_test "export"
# exec_test "export Hola"
# exec_test "export Hola9hey"
# exec_test "export $DONTEXIST"
# exec_test "export | grep \"HOME\""
# exec_test "export \"\""
# exec_test "export ="
# exec_test "export %"
# exec_test "export $?"
# exec_test "export ?=2"
# exec_test "export 9HOLA="
# exec_test "export HOLA9=bonjour"
# exec_test "export _HOLA=bonjour"
# exec_test "export ___HOLA=bonjour"
# exec_test "export _HO_LA_=bonjour"
# exec_test "export HOL@=bonjour"
# exec_test "export HOL\\~A=bonjour"
# exec_test "export -HOLA=bonjour"
# exec_test "export --HOLA=bonjour"
# exec_test "export HOLA-=bonjour"
# exec_test "export HO-LA=bonjour"
# exec_test "export HOL.A=bonjour"
# exec_test "export HOL\\\\\$A=bonjour"
# exec_test "export HO\\\\\\\\LA=bonjour"
# exec_test "export HOL}A=bonjour"
# exec_test "export HOL{A=bonjour"
# exec_test "export HO*LA=bonjour"
# exec_test "export HO#LA=bonjour"
# exec_test "export HO@LA=bonjour"
# exec_test "export HO!LA=bonjour"
# exec_test "export HO$?LA=bonjour"
# exec_test "export +HOLA=bonjour"
# exec_test "export HOL+A=bonjour"
# exec_test "export HOLA+=bonjour"
# exec_test "export HOLA=bonjour"
# exec_test "export HOLA=bonjour BYE=casse-toi"
# exec_test "export $HOLA=bonjour"
# exec_test "export HOLA=\"bonjour \""
# exec_test "export HOLA=\" -n bonjour \""
# exec_test "export HOLA=\"bonjour \"/"
# exec_test "export HOLA='\"'"
# exec_test "export HOLA=at"
# exec_test "export HOLA\$USER=bonjour"
# exec_test "export HOLA=bonjour=casse-toi"
# exec_test "export \"HOLA=bonjour\"=casse-toi"
# exec_test "export HOLA=bonjour"
# exec_test "export HOLA=bonjour BYE=casse-toi"
# exec_test "export $HOLA=bonjour"
# exec_test "export HOLA=\"cat Makefile | grep NAME\""
# exec_test "export HOLA=hey"
# exec_test "echo \$HOLA\$HOLA\$HOLA=hey\$HOLA"

rm -rf minishell out1 test2 testpwd truc2