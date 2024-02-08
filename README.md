![hcml_logo](https://github.com/blhmr/HCML/assets/134303496/76d27b0a-771a-4eeb-84d0-f2cc2e7846eb)

# HCML 📎 (Hatim's Configuration Markup Language)

HCML is a lightweight markup language designed for configuring applications. It provides a simple and human-readable syntax for specifying key-value pairs and hierarchical data structures.

## Features

- Simple and intuitive syntax
- Support for key-value pairs
- Lightweight and easy to use
- Portable C library
- Arrays: parsing a string into array and array from a string

## 

## Installation

HCML is a configuration markup language, but right now it can only be used as a C library to manipulate `.hcml` files, more wrappers for more languages are coming soon only if this gets any popular. Here is how to install the library on your system (UNIX):

```bash
git clone https://github.com/blhmr/HCML.git
cd HCML
make install
```
There is also a `main.c` file if you want to see an example of usage.

## Usage

Like any other key-value configuration files, HCML has `families` instead of sections:

```html
# This is a comment

<family: key = value>

<personal_info: first_name = Hatim>
<personal_info: last_name = Belahmer>
<personal_info: age = 17>
<personal_info: country = Morocco>

<account_info: username = hatim225>
<account_info: password = SOMEPASS1234>

<profile_info: profile_picture = PFP_1>
<profile_info: color_scheme = RED>
```
### Some rules to follow:

- A family can have many **unique** key-value paires, and by **unique** I mean you can't have the same key names in the same family.
- Family part, and the value part accept spaces, unline keys, so for example you can have an entry like this:
```html
# Wrong
<family 123: some key = some value>

# Right
<family 123: some_key = some value>
```
- The syntax is strict, meaning that if you add a space between the value part and '=', it will be a part of the value.

### Using the minimal C library:

```c
#include <hcml.h>

/* These are set to 50 by default */
#define MAX_LEN_KEY 50
#define MAX_LEN_VALUE 50
#define MAX_LEN_FAMILY 50

int main(void) {
    hcml_file_t file;
    
    hcml_file_open(&file, "newfile.hcml"); // Returns 0 if success

    hcml_insert_value(&file, "family", "key", "value"); // Returns 0 if success

    hcml_file_close(file); // Same thing

    return 0;
}
```
There are examples in the `example` directory, use `make` to compile the run each example! Read the code for explanations

### Arrays

Arrays are here ! Here is how to use them:
```html
<food: fruits = apple;orange;banana>
```
This is an array of family `food`, its key is `fruits` and has the values `apple`, `orange` and `banana`
When using the C library:
- `bool hcml_value_is_array(const char* value)`: This returns a `bool` value, it checks wether a `value` string is an array so we can use it for parsing
- `char** hcml_parse_from_array(const char* string)`: This functions returns an `array of strings`, must be freed after working with it, just pass a string that can be parsed using the function above
- `char* hcml_parse_to_array(int num_args, ...)`: This functions takes a number of `num_args` of arguments as string, converts them into a string buffer that can be treated as an array, or can be written to the HCML file

## Vim

This language and library was made in Vim, so if you want to use the syntax highlighting file, simply copy and paste this into `.vim/after/syntax/hcml.vim`:

```vim
" Language: HCML (Hatim's Configuration Markup Language)
" Author: Hatim Belahmer
" Last Updated: Monday 2024-01-29

" Define HCML file extensions
au BufRead,BufNewFile *.hcml set filetype=hcml

" Define HCML syntax highlighting
syntax region hcmlComment start="#.*" end="$"
syntax match hcmlComment "#.*$"

syntax region hcmlTag start="<" end=">" contains=hcmlTagName,hcmlAttribute,hcmlComment
syntax match hcmlTagName "\<\w\+\%(\s\|>\)" contained
syntax match hcmlAttribute "\<\w\+\ze\s*=" contained contains=hcmlKey,hcmlValue
syntax match hcmlKey "\<\w\+\ze\s*=" contained
syntax match hcmlValue "\<[^=]\+\ze\s*=" contained

" Highlight HCML tags
highlight link hcmlTag Special
highlight link hcmlTagName Keyword
highlight link hcmlAttribute Identifier
highlight link hcmlKey Type
highlight link hcmlValue String
highlight link hcmlComment Comment
```
Preview:
<img src="https://cdn.discordapp.com/attachments/1043106668839456860/1202015711191367700/Tue_Jan_30_112045_PM_01_2024.png?ex=65cbeb5d&is=65b9765d&hm=0f9fc35a1dea6e109ffa719fab3b583c7573cca3f840de345745916e7ecb7d80&">

## Use case

This language was primarly for personal use, therefore it lacks some features other configuration files have, so keep your expectations low.
Example of usage: consider the following folder scheme

```
school/
├── class-1/
│   ├── student-1/
│   │   ├── history.txt
│   │   ├── grades/
│   │   └── information.hcml <- Informations about the student
│   ├── student-2/
│   │   ├── history.txt
│   │   ├── grades/
│   │   └── information.hcml
```

## Undone and In Progress

- Bindings for other languages: I will probably only make Python and C++ bindings unless this project gets too popular

## License

This library is provided under the [MIT License](LICENSE). Feel free to use and modify it in your projects.
