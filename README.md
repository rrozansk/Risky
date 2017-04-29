# Risky

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Risky/blob/master/LICENSE.txt) [![BUILD](https://img.shields.io/badge/BUILD-IN DEVELOPMENT-yellow.svg)]()

An implementation of a Risk like game which supports up to 8 players and 4 modes:
- Human v Human
- Computer v Human
- Computer v Computer
- Training

The fourth mode is used exclusively for improving the AI's DNA, which can then 
be used as an opponent in mode two or three. During training (and all other modes)
games can be logged and there output placed under a training directory so they 
can be reviewed or inspected later if so desired.

Risky itself is actually a library which exposes a Risk game like API to
easily implement Risk like games quickly. Along with this, it also exposes a
completely configurable command line input/output version of a Risk like game
which allows the competing and training of custom configured AIs, and logging
of all games to file.

Along with Risky is a custom written ini (conf file) library which allows input
and output to a file along with dynamic creation and mutation of that conf file.
This allows all gameplay to be easily configured, and also makes it possible for
the AIs to keep there intelligence between games. An example conf file (conf.ini)
is included in the repo along with comments explaining the different sections,
keys, and values accepted. The current configuration is setup for the classic 
risk map, cards, bonuses, etc. Some caution must be taken when editing the conf
though, as it will be overwritten in mode four since DNA will be changing. All
settings will be preserved, but comments will not be.

## Prerequisites
- gcc (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3 or equivalent
- make

## Getting Started
```sh
$ git clone https://github.com/rrozansk/Risky.git
$ cd Risky
$ make
$ ./risky conf.ini
```
