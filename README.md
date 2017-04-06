# Risky

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Risky/blob/master/LICENSE.txt)

An implementation of Risk which supports up to 8 players and 3 modes:
- Human v Human
- Computer v Human
- Computer v Computer

The third mode is used exclusively for training the ai's which can then be used as an opponent in mode 2.
During the third mode all games can be logged and there output placed under a training directory.
Along with risk is a custom written ini library/module so that all gameplay is configurable.
In fact, the current configuration is just setup for the classic risk map, cards, bonuses, etc.
This also makes it possible for the ai's to keep there intelligence between games.
An example conf file (conf.ini) is included in the repo. Some caution must be taken though, as the conf
is overwritten in mode 3 since dna will be changing. all settings will be preserved, but comments will not be.

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
