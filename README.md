# Risky

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Risky/blob/master/LICENSE.txt) [![BUILD](https://img.shields.io/badge/BUILD-IN_DEVELOPMENT-yellow.svg)]()

A cmd line implementation of a Risk like game which supports up to 8 players and 4 modes:
  - Human v Human
  - Computer v Human
  - Computer v Computer
  - Training

The fourth mode is used exclusively for improving the AI's DNA, which can then 
be used as an opponent in mode two or three. During training (and all other modes)
games can be logged and there output placed under a training directory so they 
can be reviewed or inspected later if so desired.

Risky is actually composed of 3 libraries:
  - log: a simple library for file logging
  - ini: a simple library for ini like configuration files supporting CRUD operations
  - risky: exposes a Risk game like API to easily implement Risk like games quickly. 

All of this is composed together to create an easily custom configurable risk
game with AI (using genetic algorithms) layer on top to make things fun and
interesting! Along with making gameplay easily configurable, the ini conf also
makes it possible for the AIs to keep there intelligence between games. An
example conf file (conf.ini) is included in the repo along with comments
explaining the different sections, keys, and values accepted. The current 
configuration is setup for the classic risk map, cards, bonuses, etc. as well
as coming set up with pre-configured AIs, but allows for the user to
freely mutate, add, and delete as they deem fit. However, some caution must be
taken when editing the conf, as it will be overwritten in mode four since
DNA will be changing. All settings will be preserved, but comments will not be.

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
