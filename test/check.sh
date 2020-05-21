#!/bin/sh
TESTS=0
FAILURES=0
TDIRS="lex"

echo "Running tests..."
for tdir in $TDIRS; do
	echo
	tpath="test/$tdir"
	TESTS=$(expr "$TESTS" + $(ls "$tpath" | wc -l))
	echo '*** '"Testing $tdir"' ***'
	for test in $(ls "$tpath"); do
		if "$tpath/$test"; then
			echo -e "\033[0;92m[$test] Passes\033[0m";
		else
			echo -e "\033[0;91m[$test] Fails\033[0m";
			FAILURES=$(expr "$FAILURES" + 1)
		fi
	done
done

echo
[ "$FAILURES" -ne "0" ] && echo -ne "\033[0;91m"
[ "$FAILURES" -eq "0" ] && echo -ne "\033[0;92m"
echo -ne "$TESTS tests, $FAILURES failures"
echo -e "\033[0m"
[ "$FAILURES" -eq "0" ] && exit 0
[ "$FAILURES" -ne "0" ] && exit 1
