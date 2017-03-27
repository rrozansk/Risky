# Risky

[![LICENSE](https://img.shields.io/badge/LICENSE-MIT-green.svg)](https://github.com/rrozansk/Risky/blob/master/LICENSE.txt)

An implementation of risk which supports up to 8 players and 3 modes:
- Human v Human
- Computer v Human
- Computer v Computer

The third mode is used for training the ai's which can then be used as an opponent in mode 2.
All gameplay is configurable through a conf file, which among other things, holds the chromosomes of the ai.
This makes it possible for the ai's to keep there intellegence between games.
An example conf file (conf.txt) is included in the repo.

## Prerequisites
- gcc (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3 or equivalent
- make

## Getting Started
```sh
$ git clone https://github.com/rrozansk/Risky.git
$ cd Risky
$ make
$ ./risky conf.txt
```
