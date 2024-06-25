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

#exit
# exec_test "exit 42"
# exec_test "exit 0"
# exec_test "exit truc"
# exec_test "exit 42 56"
# exec_test "exit"
# exec_test "exit			 "
# exec_test "exit -1"
# exec_test "exit 255"
# exec_test "exit 256"
# exec_test "exit 2147483647"
# exec_test "exit 2147483648"
# exec_test "exit 9223372036854775806"
# exec_test "exit 9223372036854775807"
# exec_test "exit 9223372036854775808"
# exec_test "exit 9223372036854775818"
# exec_test "exit 922337203685477580866"
# exec_test "exit -9223372036854775807"
# exec_test "exit -9223372036854775808"
# exec_test "exit -9223372036854775809"
# exec_test "exit -n"
# exec_test "exit exit"
# exec_test "exit que tal"
# exec_test "exit 000042"
# exec_test "exit -777 777"
# exec_test "exit truc 777"
# exec_test "exit +0"
# exec_test "exit -0"
# exec_test "exit --777"
# exec_test "exit +++777"

#env
exec_test "env truc"
exec_test "env -n truc"
exec_test "env truc machin"
exec_test "env"
exec_test "export HOLA=bonjour ; env"


# #export
# exec_test "export TRUC=machin ; echo \$TRUC"
# exec_test "export TRUC=machin  CHOSE=chouette ; echo \$TRUC ; echo \$CHOSE"
# exec_test 'export LOL="		 truc machin	 " ; cat $LOL'
# exec_test "export TRUC=machin ; echo $TRUC"
# exec_test "export"
# exec_test "export Hola ; export"
# exec_test "export Hola9hey ; export"
# exec_test "export $DONTEXIST"
# exec_test "export | grep "HOME""
# exec_test "export """
# exec_test "export ="
# exec_test " export %"
# exec_test "export $?"
# exec_test "export ?=2"
# exec_test "export 9HOLA="
# exec_test "export HOLA9=bonjour ; env"
# exec_test "export _HOLA=bonjour ; env"
# exec_test "export ___HOLA=bonjour ; env"
# exec_test "export _HO_LA_=bonjour ; env"
# exec_test "export HOL@=bonjour"
# exec_test "export -HOLA=bonjour"
# exec_test "export --HOLA=bonjour"
# exec_test "export HOLA-=bonjour"
# exec_test "export HO-LA=bonjour"
# exec_test "export HOL.A=bonjour"
# exec_test "export HOL}A=bonjour"
# exec_test "export HOL{A=bonjour"
# exec_test "export HO*LA=bonjour"
# exec_test "export HO#LA=bonjour"
# exec_test "export HO@LA=bonjour"
# exec_test "export HO!LA=bonjour"
# exec_test "export HO$?LA=bonjour ; env"
# exec_test "export +HOLA=bonjour"
# exec_test "export HOL+A=bonjour"
# exec_test "export HOLA+=bonjour ; env"

# # (248 - 330)


# #unset
# exec_test "export TRUC=machin ; echo \$TRUC ; unset TRUC ; echo \$TRUC"
# exec_test "unset RIEN"
# exec_test "export HOLA=bonjour ; env ; unset HOLA ; env"
# exec_test "export HOLA=bonjour ; env ; unset HOLA ; unset HOLA ; env"
# exec_test "unset PATH ; echo $PATH"
# exec_test "unset PATH ; ls"
# exec_test "unset """
# exec_test "unset INEXISTANT"
# exec_test "unset PWD ; env | grep PWD ; pwd"
# exec_test "pwd ; unset PWD ; env | grep PWD ; cd $PWD ; pwd"
# exec_test "unset OLDPWD ; env | grep OLDPWD"
# exec_test "unset 9HOLA"
# exec_test "unset HOLA9"
# exec_test "unset HOL?A"
# exec_test "unset HOLA HOL?A"
# exec_test "unset HOL?A HOLA"
# exec_test "unset HOL?A HOL.A"
# exec_test "unset HOLA="
# exec_test "unset HOL.A"
# exec_test "unset HOL+A"
# exec_test "unset HOL=A"
# exec_test "unset HOL{A"
# exec_test "unset HOL-A"
# exec_test "unset -HOLA"
# exec_test "unset _HOLA"
# exec_test "unset HOL_A"
# exec_test "unset HOL_A"
# exec_test "unset HOL_A"
# exec_test "unset HOL#A"
# exec_test "unset $HOLA"
# exec_test "unset $PWD"
# exec_test "unset HOL@"
# exec_test "unset HOL!A"
# exec_test "unset HOL^A"
# exec_test "unset HOL$?A"
# exec_test "unset HOL\~A"
# exec_test "unset "" HOLA ; env | grep HOLA"
# exec_test "unset PATH ; echo $PATH"
# exec_test "unset PATH ; cat Makefile"
# exec_test "unset ="
# exec_test "unset ======"
# exec_test "unset ++++++"
# exec_test "unset _______"
# exec_test "unset export"
# exec_test "unset echo"
# exec_test "unset pwd"
# exec_test "unset cd"
# exec_test "unset unset"
# exec_test "unset sudo"

# #cd
# exec_test "cd oui non"
# exec_test "pwd ; cd ; pwd"
# exec_test "pwd ; cd .. ; pwd"
# exec_test "pwd ; cd false"
# exec_test "pwd ; cd false ; pwd"
# exec_test "cd"
# exec_test "cd ."
# exec_test "cd ./"
# exec_test "cd ./././."
# exec_test "cd .."
# exec_test "cd ../.."
# exec_test "cd .././././."
# exec_test "cd ../"
# exec_test "cd srcs"
# exec_test "cd srcs objs"

# # (411)

# #pwd
# exec_test "pwd"
# exec_test "pwd truc"
# exec_test "pwd > testpwd ; cat testpwd"
# exec_test "pwd > testpwd"
# exec_test "pwd ./hola"
# exec_test "pwd hola que tal"
# exec_test "pwd -p"
# exec_test "pwd --p"
# exec_test "pwd ---p"
# exec_test "pwd pwd pwd"
# exec_test "pwd ls"
# exec_test "pwd ls env"


rm -rf minishell out1 test2 testpwd truc2