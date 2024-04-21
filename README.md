# Philosophers
A project that simulates the dining problem of philosophers (threads/processes) due to constraint on forks (shared resources), and how synchronization issues might arise and how certain techniques can be used to resolve them. 

## Overview
- One or more philosophers sit at a round table. Spaghetti is placed in the middle of the table.
- There are as many forks as philosophers on the table.
- The forks are either at the left and right sides of each philosopher (mandatory part) or in the middle of the table (bonus part).
- Each philosopher sequentially eats, sleeps and thinks, unless the simulation stops.
- Each philosopher can only eat while holding two forks, one in each hand.
- The program takes the following arguments:
	- number_of_philosophers
	- time_to_die, (in milliseconds(ms)): if a philosopher didn't start eating time_to_die ms since the beginning of their last meal, they die
	- time_to_eat (in ms)
	- time_to_sleep (in ms)
	- number_of_times_each_philosopher_must_eat (optional argument)
- The simulation stops, if
	- a philosopher died, or
	- each philosopher has eaten the number of times they must eat, if this argument is given.
- The philosophers do not share information between each other and they should avoid dying.

## Installation
Mandatory part
```
git clone https://github.com/ixu42/philosophers.git && cd philosophers/philo && make
```
Bonus part
```
git clone https://github.com/ixu42/philosophers.git && cd philosophers/philo_bonus && make
```

## Usage (with examples)
Mandatory part
```
./philo 4 410 200 200
```
Bonus part
```
./philo_bonus 5 800 200 200 7
```
