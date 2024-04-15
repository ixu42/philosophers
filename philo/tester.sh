#!/bin/bash

make

PHILO=./philo

NC='\033[0m'
GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'

OUTFILE=out

LEAKS_ON=0

test_error()
{
	if [ $LEAKS_ON -eq 1 ]
	then
		OUT=$( valgrind $ARG 2> leaks.log )
		cat leaks.log | grep "at exit"
		rm -rf leaks.log
	else
		OUT=$( $ARG )
	fi
	echo "$OUT" > $OUTFILE
	cat $OUTFILE
	OUT_LEN=$( cat $OUTFILE | wc -l )
	OUT_WORDS=$( echo $OUTFILE | wc -w )
	if [ $OUT_LEN -eq 1 ] && [ $OUT_WORDS -ge 1 ]
	then
		echo -e ${GREEN}"$ARG: [OK]"${NC}
	else
		echo -e ${RED}"$ARG: [KO]"${NC}
	fi
	rm -f $OUTFILE
}

test_philo_death()
{
	DEATH=$( $PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT | grep "died" )
	DEATH_COUNT=$( echo "$DEATH" | wc -l )
	DIED_AT=$( echo "$DEATH" | awk '{print $1}' )
	if [ $DEATH_COUNT -eq 1 ]
	then
		if [ $DIED_AT -ge $DEATH_TIME ] && [ $DIED_AT -lt $(( $DEATH_TIME + 10 )) ]
		then
			echo -e ${GREEN}"$DEATH_TIME: [OK]"${NC}
		else
			echo -e ${RED}"$DEATH_TIME: [KO]"${NC}
			echo "died at $DIED_AT"
		fi
	else
		echo -e ${RED}"$DEATH_TIME: [KO]"${NC}
		echo "more than one philosopher died"
	fi
	test_leaks
}

test_philo_count()
{
	OUT=$( $PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT | grep 'is eating' )
	TIMES_EATEN=$( echo "$OUT" | grep "is eating" | wc -l )
	DEATH_COUNT=$( echo "$OUT" | grep "died" | wc -l )
	TIMES_EATEN_PER=$(( $TIMES_EATEN / $PHILO_COUNT ))
	if [ $DEATH_COUNT -ge 1 ]
	then
		echo -e ${RED}"$PHILO_COUNT: [KO]"${NC}
		echo "$OUT" | grep 'died'
	else
		if [ $TIMES_EATEN_PER -ge $EAT_LIMIT ] || [ $PHILO_COUNT -eq 1 ]
		then
			echo -e ${GREEN}"$PHILO_COUNT: [OK]"${NC}
		else
			echo -e ${RED}"$PHILO_COUNT: [KO]"${NC}
			echo "times eaten per = $TIMES_EATEN_PER"
		fi
	fi
	test_leaks
}

test_times_eaten()
{
	TIMES_EATEN=$( $PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT | grep "is eating" | wc -l )
	TIMES_EATEN_PER=$(( $TIMES_EATEN / $PHILO_COUNT ))
	if [ $TIMES_EATEN_PER -ge $EAT_LIMIT ]
	then
		echo -e ${GREEN}"$TIMES_EATEN_PER: [OK]"${NC}
	else
		echo -e ${RED}"$TIMES_EATEN_PER: [KO]"${NC}
	fi
	test_leaks
}

test_leaks()
{
	if [ $LEAKS_ON -eq 1 ]
	then
		valgrind $PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT 1> trash.log 2> leaks.log
		cat leaks.log | grep "at exit"
		rm -rf trash.log
		rm -rf leaks.log
	fi
}


echo -e ${CYAN}"--- TEST INVALID ARGS ---"${NC}

PHILO_COUNT=4
DEATH_TIME=410
EAT_TIME=200
SLEEP_TIME=200
EAT_LIMIT=1

ARG="$PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME"
test_error
ARG="$PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT extra_arg"
test_error

ARG="$PHILO 123a $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT"
test_error
ARG="$PHILO $PHILO_COUNT 123a $EAT_TIME $SLEEP_TIME $EAT_LIMIT"
test_error
ARG="$PHILO $PHILO_COUNT $DEATH_TIME 123a $SLEEP_TIME $EAT_LIMIT"
test_error
ARG="$PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME 123a $EAT_LIMIT"
test_error
ARG="$PHILO $PHILO_COUNT $DEATH_TIME $EAT_TIME $SLEEP_TIME 123a"
test_error

ARG="$PHILO 0 $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT"
test_error
ARG="$PHILO -4 $DEATH_TIME $EAT_TIME $SLEEP_TIME $EAT_LIMIT"
test_error

OUT=$( ./philo 4 400 " " 200 )
echo "$OUT" > $OUTFILE
cat $OUTFILE
OUT_LEN=$( cat $OUTFILE | wc -l )
OUT_WORDS=$( echo $OUTFILE | wc -w )
if [ $OUT_LEN -eq 1 ] && [ $OUT_WORDS -ge 1 ]
then
	echo -e ${GREEN}"./philo 4 400 \" \" 200: [OK]"${NC}
else
	echo -e ${RED}"./philo 4 400 \" \" 200: [KO]"${NC}
fi
rm -f $OUTFILE

OUT=$( ./philo 4 400 "" 200 )
echo "$OUT" > $OUTFILE
cat $OUTFILE
OUT_LEN=$( cat $OUTFILE | wc -l )
OUT_WORDS=$( echo $OUTFILE | wc -w )
if [ $OUT_LEN -eq 1 ] && [ $OUT_WORDS -ge 1 ]
then
	echo -e ${GREEN}"./philo 4 400 \"\" 200: [OK]"${NC}
else
	echo -e ${RED}"./philo 4 400 \"\" 200: [KO]"${NC}
fi
rm -f $OUTFILE



echo -e ${CYAN}"--- TEST PHILO DEATHS ---"${NC}

PHILO_COUNT=4
EAT_TIME=200
SLEEP_TIME=200
EAT_LIMIT=4

DEATH_TIME=1
test_philo_death
DEATH_TIME=100
test_philo_death
DEATH_TIME=200
test_philo_death
DEATH_TIME=300
test_philo_death
DEATH_TIME=390
test_philo_death

DEATH_TIME=310
PHILO_COUNT=3
EAT_TIME=200
SLEEP_TIME=100
test_philo_death

PHILO_COUNT=1
DEATH_TIME=410
EAT_LIMIT=1
test_philo_death




echo -e ${CYAN}"--- TEST PHILO COUNTS ---"${NC}

DEATH_TIME=410
SLEEP_TIME=200
EAT_LIMIT=2

PHILO_COUNT=1
while [ $PHILO_COUNT -le 10 ]
do
	if [ $(( $PHILO_COUNT % 2 )) -eq 0 ]
	then
		EAT_TIME=200
	else
		EAT_TIME=100
	fi
	test_philo_count
	PHILO_COUNT=$(( $PHILO_COUNT + 1 ))
done

PHILO_COUNT=49
EAT_TIME=100
test_philo_count

PHILO_COUNT=50
EAT_TIME=200
test_philo_count

PHILO_COUNT=99
EAT_TIME=100
test_philo_count

PHILO_COUNT=100
EAT_TIME=200
test_philo_count

PHILO_COUNT=199
EAT_TIME=100
test_philo_count

PHILO_COUNT=200
EAT_TIME=200
test_philo_count

echo -e ${CYAN}"--- TEST EAT COUNTS ---"${NC}

PHILO_COUNT=4
DEATH_TIME=410
EAT_TIME=200
SLEEP_TIME=200

EAT_LIMIT=1
while [ $EAT_LIMIT -le 10 ]
do
	test_times_eaten
	EAT_LIMIT=$(( $EAT_LIMIT + 1 ))
done
