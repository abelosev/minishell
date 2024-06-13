#cd
exec_test "cd oui non"
exec_test "pwd ; cd ; pwd"
exec_test "pwd ; cd .. ; pwd"
exec_test "pwd ; cd false"
exec_test "pwd ; cd false ; pwd"

#pwd
exec_test "pwd"
exec_test "pwd truc"
exec_test "pwd > testpwd ; cat testpwd"
exec_test "pwd > testpwd"

#Relative Path

#Environment path

#Redirections
exec_test '>>truc2'
exec_test "cat <test_cases.c >out1 ; <out1 wc "
exec_test "cat <test_cases.c"

#Pipes
exec_test ' "" | "" '
exec_test "ls <non | wc"
exec_test "cat <test_cases.c | wc"

#Go Crazy and history

#Environment variables (expand)
exec_test "echo $ "
exec_test "echo $"
exec_test "echo $\"rfrgrg\""
exec_test "echo $'rfrgrg'"
exec_test 'echo $rfrgrg'
exec_test "echo 'l"
exec_test "echo \$USER \"\$USER\" '\$USER'"
exec_test "\$FALSE"
exec_test "truc ; echo $?"
exec_test "/truc ; echo $?"
exec_test "touch test2 ; chmod 000 test2 ; cat test2 ; echo \$?"

#syntax error tests
exec_test "wc <"
exec_test "wc >"
exec_test "wc |"
exec_test "wc | |"
exec_test "wc |||"