# my_ls

LiSting command-like, in C.

## Supported options

- `-a`, `--all`: do not ignore entries starting with .
- `--color`: color the output
- `-d`, `--directory`: list directories themselves, not their contents
- `-f`: list all entries in directory order
- `-F`, `--classify`: append indicator (one of */=>@|) to entries
- `-g`: like -l, but do not list owner
- `-l`: use a long listing format
- `-r`, `--reverse`: reverse order while sorting
- `-R`, `--recursive`: list subdirectories recursively
- `-t`: sort by modification time, newest first
- `-u`: sort by last access time

## Notable features

- Blazzing fast sorting with the Quick Sort algorithm
- Extensible options with bit shifting
