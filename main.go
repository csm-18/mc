package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

type Options struct {
	Version     bool
	Help        bool
	Watch       bool
	SrcPaths    []string
	OutDirPath  string
	HeaderPaths []string
	Errors      []string
}

func main() {
	args := os.Args[1:]
	options := Options{}

	if len(args) == 0 {
		options.Help = true
	}

	for i := 0; i < len(args); i += 1 {
		if args[i] == "-v" {
			options.Version = true
		} else if args[i] == "-h" {
			options.Help = true
		} else if args[i] == "-w" {
			options.Watch = true
		} else if strings.HasSuffix(args[i], ".c") {
			options.SrcPaths = append(options.SrcPaths, args[i])
		} else if args[i] == "-o" {
			i += 1
			if i < len(args) {
				path := args[i]
				info, err := os.Stat(path)
				if err != nil {
					error := fmt.Sprintf("error: Invalid path provided to -o flag:\n '%s'", path)
					options.Errors = append(options.Errors, error)
				} else if !info.IsDir() {
					error := fmt.Sprintf("error: Path provided to -o flag is not a directory:\n '%s'", path)
					options.Errors = append(options.Errors, error)
				} else {
					options.OutDirPath = path
				}
			} else {
				error := "error: No path provided to -o flag."
				options.Errors = append(options.Errors, error)
			}
		} else {
			error := fmt.Sprintf("error: Unknown command:\n '%s'", args[i])
			options.Errors = append(options.Errors, error)
		}
	}

	if len(options.Errors) != 0 {
		for _, err := range options.Errors {
			fmt.Println(err)
		}
		os.Exit(1)
	}

	if options.Watch && (options.Version || options.Help || len(options.SrcPaths) != 0) {
		fmt.Println("error: -w (watch) flag cannot be used with other options.")
		os.Exit(1)
	}

	if options.Version && options.Help {
		fmt.Println(VERSION)
		fmt.Println(HELP)
	} else if options.Version {
		fmt.Println(VERSION)
	} else if options.Help {
		fmt.Println(VERSION)
		fmt.Println(HELP)
	} else if options.Watch {
		fmt.Println("watching!")
	} else {
		if len(options.SrcPaths) != 0 {
			if options.OutDirPath != "" {
				for _, src_path := range options.SrcPaths {
					filename := filepath.Base(src_path)
					header_path := filepath.Join(options.OutDirPath, filename[:len(filename)-1]+"h")
					options.HeaderPaths = append(options.HeaderPaths, header_path)
				}
			} else {
				for _, src_path := range options.SrcPaths {
					header_path := src_path[:len(src_path)-1] + "h"
					options.HeaderPaths = append(options.HeaderPaths, header_path)
				}
			}

			for i := 0; i < len(options.SrcPaths); i++ {
				err := generate_header_file(options.SrcPaths[i], options.HeaderPaths[i])
				if err != "" {
					fmt.Println(err)
					os.Exit(1)
				} else {
					fmt.Printf("Generated %s\n", options.HeaderPaths[i])
				}
			}

		}
	}

}

const VERSION = "mc 1.0.0"
const HELP = `A pre-preprocessor for C for header files generation
using comment macro syntax.
    
Commands:
	mc <no args>       -> Print mc version and help.
	mc -v              -> Print mc version.
	mc -h              -> Print mc help.
	mc -w              -> Watch current directory for file changes and 
update the header files.
	mc main.c hello.c  -> Generate header files for provided .c files.

Author: csm
License: MIT
`
