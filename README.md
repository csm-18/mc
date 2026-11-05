# mc
A pre-preprocessor for C for header files generation using comment macro syntax.


## Example

## Development Environment
- OS: Linux Mint
- GCC Toolchain
- GNU Make

## Make Commands
- `make` - Build the project
- `make all` - Same as make
- `make -j$(nproc)` - Build using all available CPU cores
- `make clean` - Remove build/ and the output binary
- `make rebuild` - Clean everything and rebuild


## mc Usage
```
mc <no args>       -> Print mc version and help.
mc -v              -> Print mc version.
mc -h              -> Print mc help.
mc -w              -> Watch current directory for file changes and update the header files.
mc main.c hello.c  -> Generate header files for provided .c files.
```

## License
MIT