# MINISHELL

A shell implementation project developed as part of the 42 school curriculum. This project aims to create a simple shell, similar to bash, to understand the inner workings of command interpretation and execution.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Built-in Commands](#built-in-commands)
- [Contributing](#contributing)
- [License](#license)

## Installation

```bash
git clone https://github.com/Chamuraii/minishell.git
cd minishell
make
```

## Usage

To run the program:

```bash
./minishell
```

## Features

- Command line parsing and execution
- Built-in commands implementation
- Environment variable management
- Signal handling
- Redirection and pipes
- Command history

Bonus features (if implemented):
- Auto-completion
- Wildcard expansion
- Advanced line editing

## Built-in Commands

Minishell typically implements the following built-in commands:

1. `echo`: Display a line of text
2. `cd`: Change the current directory
3. `pwd`: Print the current working directory
4. `export`: Set environment variables
5. `unset`: Unset environment variables
6. `env`: Display the environment
7. `exit`: Exit the shell

Usage examples:
```bash
echo Hello, World!
cd /path/to/directory
pwd
export MY_VAR=value
unset MY_VAR
env
exit
```

## Contributing

This project is part of the 42 school curriculum. While contributions are not expected, feel free to fork the project for your own learning and experimentation.

## License

This project is licensed under the AGPLv3 License - see the [LICENSE](LICENSE) file for details.
