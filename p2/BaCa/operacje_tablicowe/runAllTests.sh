#!/bin/bash

function usage() {
    cat <<USAGE
Usage: $0 [-c]

Options:
    -c, --compile:        compile program before running tests
USAGE
    exit 1
}

compile=0

while [ "$1" != "" ]; do
    case $1 in
    -c | --compile)
		compile=1
        ;;
     *)
         usage
         exit 1
         ;;
    esac
    shift
done

rm -r test
mkdir test
csplit --suppress-matched -s -b "%0d.test" all-tests /---/ {*} -f file
count=$(ls -1q file* | wc -l)
for((i = 0; i < $((count)); i=i+2)); do
	j=$(echo "$i + 1" | bc)
	iDiv2=$(echo "$i/2" | bc)
 	mv "file${i}.test" "test${iDiv2}.in"
 	mv "file${j}.test" "test${iDiv2}.out"
done

mv *.in *.out test/
[ $compile = 1 ] && make

all_correct=true
countDiv2=$(echo "$count/2" | bc)
for((i = 0; i < countDiv2; i++)); do
	printf "test ${i}...\t"
	./bin/prog.x < "test/test${i}.in" &> "test/output${i}.out" 
	#diff "test/test${i}.out" "test/output${i}.out" > diffLog
	diff "test/test${i}.out" "test/output${i}.out" > diffLog
	if [ $? == 0 ]; then
		# \033[K clears the line after \r
		#printf '\e[32m%s\e[0m\n' "ok"
		printf '\e[32m%s\e[0m\r\033[K' "ok"
	else
		printf '\e[31m%s\e[0m\n' "failed"
		printf "input:\n"
		cat "test/test${i}.in"
		printf "your output:\n"
		cat "test/output${i}.out"
		printf "expected output:\n"
		cat "test/test${i}.out"
		#printf "\n"
		all_correct=false
	fi
done
[ $all_correct = true ] && printf '\e[32m%s\e[0m\n' "ok"

[ -f diffLog ] && rm diffLog
