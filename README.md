# Minishell

An UNIX interactive command interpter.


## Summary

This is a school project I have done at [EPITECH](https://epitech.eu) as a
**B3ed**. This is based on the minishell 1 and minishell 2 project.

The goal is to make a working command line command interpreter, inspired by
the TCSH project.


## Features

### Builtins
- `cd` and `pwd`
- `env`, `setenv` and `unsetenv`
- `exit`

### Redirects
- `[cmd]<file` Redirecting Input
- `[cmd]>file` Redirecting Output
- `[cmd]>>file` Appending Redirected Output
- `[cmd]|[cmd]` Pipeline


## Parameters

- `-c [cmd]` run a specific command


## Compilation

```sh
git clone https://github.com/drawpitech/minishell
cd minishell
make
```
```sh
./mysh
```

Or using Nix

```sh
nix run github:drawpitech/minishell
```
