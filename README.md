# csv2mdtable

Simple C++ console program to transform csv files into pretty markdown tables.

Simple example:
```
col 1,col 2,col 3,col 4        |col 1|col 2|col 3|col 4|
5,6,7,8                   ->   |-----|-----|-----|-----|
9,10,11,12                     |5    |6    |7    |8    |
                               |9    |10   |11   |12   |
```
Which renders as

|col 1|col 2|col 3|col 4|
|-----|-----|-----|-----|
|5    |6    |7    |8    |
|9    |10   |11   |12   |



## Installation

1. Download or clone this repository
2. Run `make` (or `cmake` directly)
3. Place the executable `csv2mdtable` anywhere on your path

## Usage

Command line arguments:

- `-i <file>` input file in csv format. Read standard input if absent
- `-o <file>` output file. Print to standard output if absent
- `-a <str>` column alignement (string of `'l'`, `'c'`, `'r'`, `'_'`) specifying if each column is left aligned, centered, right aligned or unspecified.
- `-c <char>` column separation character, attempts to autodetermine if absent.
  Autodetermine chooses between these characters `'\t'`, `','`, `';'`, `'.'`, `' '`. 
- `-l <char>` line separation character, default is `\n`
- `-no-pad` don't autopad columns to have same width
- `-no-pipes` don't place external pipes (leftmost and rightmost)
- `-h --help` show help
- `-v --version` show version number
