# csv2mdtable

Simple C++ console program to transform csv files into pretty markdown tables

## Installation

1. Download or clone this repository
2. Run `make` (or `cmake` directly)
3. Place the executable `csv2mdtable` anywhere on your path

## Usage

Command line arguments:

- `-i <file>` input file in csv format. Read standard input if absent
- `-o <file>` output file. Print to standard output if absent
- `-a <str>` column alignement (string of `'l'`, `'c'`, `'r'`, `'_'`)
- `-c <char>` column separation character, attempts to autodetermine if absent
- `-l <char>` line separation character, default is `\n`
- `-no-pad` don't autopad columns to have same width
- `-no-pipes` don't place external pipes (leftmost and rightmost)
- `-h --help` show help
- `-v --version` show version number

