## Build
./build.sh

## Run
./SegShell

## Install
- Standalone commands are installed into ~/segshell/bin
- config file located in ~/.segshellrc

## Features
- Minimal POSIX-like shell written in C
- Interactive and batch (script) modes
- Simple scripting using `.sg` files
- Line and inline comments (`#`)
- Built-in command dispatcher
- 15 commands (3 built-ins, 12 standalone binaries)
- Standalone commands compiled as separate executables

Some available commands:
`ls`, `cat`, `calc`, `touch`, `rm`, `pwd`, `whoami`, ...

## Future updates
- Extended scripting features
- More built-in and standalone commands
- Improved stability and error handling

## Resources
- [Linux man pages](https://man7.org/linux/man-pages/)
- [POSIX Shell & Utilities](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [BusyBox source](https://git.busybox.net/busybox/tree/shell)
