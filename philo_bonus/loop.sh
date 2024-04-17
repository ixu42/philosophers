#!/bin/bash

if [ "$#" -lt 4 ] || [ "$#" -gt 5 ]; then
	echo "Usage: bash $0 <philo_count> <time_to_die> <time_to_eat> <time_to_sleep> [num_of_times_each_philo_must_eat]"
	exit 1
fi

PROG='./philo_bonus'
PHILO_COUNT="$1"
TIME_TO_DIE="$2"
TIME_TO_EAT="$3"
TIME_TO_SLEEP="$4"
MEALS_LIMIT="$5"

BLUE='\033[0;34m'
RESET='\033[0m'

# execute the program 100 times for testing stability of the performance of the program
for (( i = 1; i <= 100; i++ )); do
	echo -e "${BLUE}Running program for the $i-th time${RESET}"
	if [ "$#" -eq 4 ]; then
		"$PROG" "$PHILO_COUNT" "$TIME_TO_DIE" "$TIME_TO_EAT" "$TIME_TO_SLEEP"
	else
		"$PROG" "$PHILO_COUNT" "$TIME_TO_DIE" "$TIME_TO_EAT" "$TIME_TO_SLEEP" "$MEALS_LIMIT"
	fi
done
