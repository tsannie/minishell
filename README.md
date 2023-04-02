# Minishell

42cursus - (2021-2022) 💻

- Result : 111/100 ✅

![screen](https://i.imgur.com/smkBx44.gif)

## Description

Minishell is a simple shell implementation that can be used to execute commands on a Unix-like operating system. It was implemented as part of a school project where we were asked to reimplement a shell like bash.

## Features

- ; (semicolon) should separate commands like in bash.
- \ (backslash) should escape the next character.
- ’ (single quote) and " (double quote) should work like in bash.
- | (pipe) should work like in bash.
- Redirections <, > and >> << should work like in bash.
- Handle the environment ($ followed by characters).
- Handle the return value of the commands ($?).
- Handle errors without having any undefined behaviors like in bash.
- Handle the ctrl-C, ctrl-D and ctrl-\ signals like in bash.
- Implement the following builtins: echo, cd, pwd, export, unset, env, exit.
- Have a working history.

## Usage
To use minishell, simply run the executable:

```bash
git clone https://github.com/tsannie/minishell && cd minishell
make bonus

./minishell
```

This will display a prompt where you can enter commands. Use the built-in help command to display a list of available commands.

## Credits

Minishell was created by

- [@tsannie](https://github.com/tsannie)
- [@philippebarradas](https://github.com/philippebarradas)
