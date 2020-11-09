# MINISHELL-TESTER

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

cp cmake-build-debug/minishell .
chmod 755 minishell

function exec_test()
{
	TEST1=$(echo $@ "; exit" | ./minishell 2>&-)
	ES_1=$?
	TEST2=$(echo $@ "; exit" | bash 2>&-)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] ; then
		printf " $BOLDGREEN%s$RESET" "✓ "
	else
		printf " $BOLDRED%s$RESET" "✗ "
	fi
	printf "$CYAN \"$@\" $RESET"
	if [ "$TEST1" != "$TEST2" ]; then
		echo
		echo
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
	fi
	echo
	sleep 0.1
}

exec_test 'echo \"\|\;\"\| cat -e > \q\w\e\r\t\y ; cat qwerty'

# SYNTAX ERROR
printf "SYNTAX ERROR\n"
exec_test 'echo \\'
exec_test "echo \\"
exec_test ';; test'
exec_test '| test'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'
exec_test ';;'
exec_test ';'
exec_test '|'
exec_test '||'
exec_test ';@@;'
exec_test '| |'
exec_test 'ls;;'
exec_test 'ls; ;'
exec_test 'ls||'
exec_test 'ls | |'
exec_test 'echo <'
exec_test 'echo >>'
exec_test 'echo >'
exec_test 'echo > ;'
exec_test 'echo > |'
exec_test '                 echo >                  |                    '
exec_test '         echo         >                                       ;                    '
exec_test 'echo ||||'
exec_test '||||||'
exec_test 'echo|||'
exec_test 'echo aaa |||'
exec_test 'wc < Makefile |'
exec_test 'echo "'
exec_test "echo ';"
exec_test "echo '"
exec_test 'ls ""'
exec_test 'echo hello      ;;;'
exec_test 'echo hello      world          ;;;'
exec_test 'echo hello      ;'
exec_test 'echo hello, ;               echo                        world'
exec_test 'echo hello                         , ;               echo                        world '
exec_test 'echo hello                          ;               echo                        world'
exec_test "'"
exec_test '"'
exec_test 'echo aa >>>'
exec_test '>>>'
exec_test 'echo ; ;'
exec_test 'lol kek > ; kek'
exec_test 'echo ";;"'
exec_test 'echo ";"'

# ESC sequences
printf "\nESC sequences\n"
exec_test echo         \'\"\\
exec_test echo \'
exec_test 'echo '\'''
exec_test echo "'\''"
exec_test '\ls\ ;'
exec_test echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\
exec_test echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\ ; cat t1

# DOLLARS AND QUOTES
printf "\nDOLLARS AND QUOTES\n"
exec_test "e""c""h""o" 'e''c'"h""o" 'e'"c"'h'"o"
exec_test echo '"""""""""",         wtf     :""'
exec_test echo ~
exec_test 'echo "~"'
exec_test 'echo ~~'
exec_test 'echo \~'
exec_test 'ec""""ho kek'
exec_test 'e"c"ho kek'
exec_test echo '""'
exec_test 'echo "$?TEST"'
exec_test 'echo -'
exec_test "echo \'"
exec_test echo helloworld"'''$USER'''"1234556789
exec_test 'echo $USER$USER$USER'
exec_test 'echo "$USER"'
exec_test "echo '$USER'"
exec_test 'echo $USER'
exec_test 'echo -n $USER'
exec_test echo ''\''"a|"\'q'a'\a'w'
exec_test '>>"helo l" echo hell\ f ; echo hell\ f'
exec_test '>"helo l" echo hell\ f'
exec_test 'echo "\$PWD" "\PWD" '
exec_test echo \'\"\\ "\hello\$PWD"
exec_test 'echo "\hello \$PWD"'
exec_test "echo '\hello \$PWD'"
exec_test 'echo \hello \$PWD'

# ECHO TESTS
printf "\nECHO TESTS\n"
exec_test 'echo -n kek'
exec_test 'echo                                                kek             '
exec_test 'echo -n '

# PIPE TESTS AND REDIRS
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo -n aa|cat -e'
exec_test 'pwd >a1>a2>a3; echo s1 >q1 s2>q2 s3; cat a2; cat a3; cat q1; cat q2; '

## ENV EXPANSIONS + ESCAPE
exec_test 'echo test     \    test'
exec_test echo \"test
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo "\$TEST"'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$1TEST"'
exec_test 'echo "$T1TEST"'
exec_test 'echo $?\?'

## CMD TESTS
exec_test 'cd .; pwd; echo $PWD'
exec_test 'cd'
exec_test 'export kek='
exec_test 'export kek======='
exec_test 'export kek lol cheburek'
exec_test 'export lol'
exec_test 'export hello="echo hello; echo world" 5d'
exec_test 'echo $hello'
exec_test '"/bin/ls" ""includes""'
exec_test 'echo | cat -e'
exec_test '/bin/cat <Makefile'
exec_test '/bin/cat <               Makefile'
exec_test '/bin/cat'
exec_test '/bin/ls'
exec_test 'wc < Makefile | cat -e cat -e cat -e cat -e cat -e cat -e cat -e'
exec_test 'wc < Makefile | cat -e -e -e -e -e -e'
exec_test '/bin/ls -la'
exec_test '/bin/ls includes'
exec_test '/bin/ls                   includes               '
exec_test './minishell ; exit'
exec_test 'exit 12 sdlkfsdkfs'
exec_test '$hello'
exec_test 'unset 10ls hello'
exec_test '$hello'
exec_test 'export lol=kek chebu=rek; $lol$chebu hello'
exec_test 'unset HOME; cd'
exec_test 'echo -n aa | cat -e'
exec_test 'echo -n aa|cat -e'
exec_test 'echo $PWD > as ; cat as'
exec_test 'export a=l d=s; $a$d'
exec_test "echo -$t '-n' '-''n' '-n;'         -n hello"
exec_test 'ls -la'
exec_test 'echo $PWD; echo $OLDPWD'
exec_test 'unset OLDPWD; echo $OLDPWD'
exec_test 'pwd; echo $PWD'

########################################################################################################
printf "\n\nHANDLE THEM\n"
exec_test '$PWD'
exec_test 'echo $TEST $TEST'
exec_test 'export t=n; echo -$t -n "-"n hello'
exec_test 'cd; echo $PWD; cd -'
exec_test 'cd -'
exec_test 'ls "-la" ; cd -'
exec_test 'cd ; echo $PWD; echo $OLDPWD'
exec_test 'cd; echo $OLDPWD'
exec_test 'cd ..; pwd; echo $PWD'
exec_test 'echo $PWD; cd ..; echo $PWD'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo $ywywtasdt hello'

###########################################################################################################

rm -f as 'helo l' qwerty t1 'qwe\r' qwe
rm -rf qwe$'\r'
