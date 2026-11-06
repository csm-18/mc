package main

import (
	"fmt"
	"os"
)

func generate_header_file(src_path string, header_file_path string) string {
	error := ""

	content, read_error := read_file(src_path)
	if read_error != "" {
		error = read_error
		return error
	}

	fmt.Println(content)

	return error
}

func read_file(path string) (string, string) {
	error := ""
	content, err := os.ReadFile(path)
	if err != nil {
		error = fmt.Sprintf("error: Cannot read file '%s'.", path)

	}
	return string(content), error
}
