package main

import (
	"fmt"
	"os"
)

type HeaderContent struct {
	Content    string
	StartIndex int
	EndIndex   int
}

func generate_header_file(src_path string, header_file_path string) string {
	error := ""
	header_content := HeaderContent{}
	header_content.Content = "//@mc\n#pragma once\n\n"
	pub_macro_start := false
	pub_macro_end := false

	src, read_error := read_file(src_path)
	if read_error != "" {
		error = read_error
		return error
	}

	x := 0
	for ; x < len(src); x += 1 {
		if src[x] <= ' ' {

		} else if x+5 < len(src) && src[x:x+6] == "//@pub" {
			if x-1 > 0 && !(src[x-1] < ' ') {
				error = fmt.Sprintf("error: @pub macro must be on a separate line, in file '%s'.", src_path)
				return error
			}
			pub_macro_start = true

			newline := false
			y := x + 6
			for ; y < len(src); y += 1 {
				if src[y] == ' ' || src[y] == '\r' {

				} else if src[y] == '\n' {
					newline = true
					break
				} else {
					error = fmt.Sprintf("error: Unexpected characters in @pub macro opening, in file '%s'.", src_path)
					return error
				}
			}

			if !newline {
				error = fmt.Sprintf("error: @pub macro opening must end with newline character, in file '%s'.", src_path)
				return error
			} else {
				y += 1
				header_content.StartIndex = y
				x = y
			}

			for ; x < len(src); x += 1 {
				if x+5 < len(src) && src[x:x+6] == "//@end" {
					if src[x-1] != '\n' {
						error = fmt.Sprintf("error: @end macro must be on a separate line, in file '%s'.", src_path)
						return error
					}
					pub_macro_end = true
					newline := false
					z := x + 6
					for ; z < len(src); z += 1 {
						if src[z] == ' ' || src[z] == '\r' {

						} else if src[z] == '\n' {
							newline = true
							break
						} else {
							error = fmt.Sprintf("error: Unexpected characters in @end macro opening, in file '%s'.", src_path)
							return error
						}
					}

					if newline {
						header_content.EndIndex = x
						break
					} else {
						error = fmt.Sprintf("error: @end macro must end with newline character, in file '%s'.", src_path)
						return error
					}
				} else if src[x] == '\'' {

					end_quote := false
					y := x + 1
					for ; y < len(src); y += 1 {
						if src[y] == '\\' {
							y = +2
							continue
						} else if src[y] == '\'' {
							end_quote = true
							break
						}
					}

					if end_quote {
						x = y + 1
						continue
					} else {
						error = fmt.Sprintf("error: Character literal is not closed in file '%s'.", src_path)
						return error
					}

				} else if src[x] == '"' {

					end_quote := false
					y := x + 1
					for ; y < len(src); y += 1 {
						if src[y] == '\\' {
							y = +2
							continue
						} else if src[y] == '"' {
							end_quote = true
							break
						}
					}

					if end_quote {
						x = y + 1
						continue
					} else {
						error = fmt.Sprintf("error: String literal is not closed in file '%s'.", src_path)
						return error
					}

				} else if x+1 < len(src) && src[x:x+2] == "//" {
					newline := false

					y := x + 2
					for ; y < len(src); y += 1 {
						if src[y] == '\n' {
							newline = true
							break
						}
					}

					if newline {
						x = y + 1
						continue
					} else {
						break
					}

				} else if x+1 < len(src) && src[x:x+2] == "/*" {
					found_comment_end := false
					y := x + 2
					for ; y < len(src); y += 1 {
						if y+1 < len(src) && src[y:y+2] == "*/" {
							found_comment_end = true
							break
						}
					}

					if found_comment_end {
						x = y + 2
						continue
					} else {
						error = fmt.Sprintf("error: Multi-line comment is not closed in file '%s'.", src_path)
						return error
					}
				}
			}

			break

		} else if x+1 < len(src) && src[x:x+2] == "//" {
			newline := false

			y := x + 2
			for ; y < len(src); y += 1 {
				if src[y] == '\n' {
					newline = true
					break
				}
			}

			if newline {
				x = y + 1
				continue
			} else {
				break
			}

		} else if x+1 < len(src) && src[x:x+2] == "/*" {
			found_comment_end := false
			y := x + 2
			for ; y < len(src); y += 1 {
				if y+1 < len(src) && src[y:y+2] == "*/" {
					found_comment_end = true
					break
				}
			}

			if found_comment_end {
				x = y + 2
				continue
			} else {
				error = fmt.Sprintf("error: Multi-line comment is not closed in file '%s'.", src_path)
				return error
			}
		} else {
			error = fmt.Sprintf("error: Valid @pub macro must be present at the top of the file '%s'.", src_path)
			return error

		}
	}

	if !pub_macro_start || !pub_macro_end {
		error = fmt.Sprintf("error: Valid @pub macro must be present at the top of the file '%s'.", src_path)
		return error
	}

	header_content.Content += src[header_content.StartIndex:header_content.EndIndex]

	write_error := os.WriteFile(header_file_path, []byte(header_content.Content), 0644)
	if write_error != nil {
		error = fmt.Sprintf("error: Unable to create file '%s'", header_file_path)
	}

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
