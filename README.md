<img src="https://cdn.discordapp.com/attachments/1043106668839456860/1209171188237082654/303505010-2f3b85ac-f566-46a8-9ad0-939b42ee60b7.png?ex=65e5f36c&is=65d37e6c&hm=6509cef9ac6ca1128e90cb3a9fbf483d566cc9aadcdd83e43b0ff2acb5a10494&" alt="HCML" style="display: block; margin: 0 auto; width: 200px; height: 200px;">

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

<family:key=value>

<info/personal:first_name=Hatim>
<info/persnal:last_name=Belahmer>
<info/personal:age=17>
<info/personal:country=Morocco>

<info/account:username=hatim225>
<info/account:password=SOMEPASS1234>

<info/account:profile_picture=PFP_1>
<info/account:color_scheme=RED>
```
### Some rules to follow:

- A family can have many **unique** key-value paires, and by **unique** I mean you can't have the same key names in the same family.
- The syntax is strict:
```c
// family: letters, numbers, underscore and slash
// key: letters, numbers and underscore
// value: anything that is in ASCII
```
For example:
```html
# Wrong
<family 123:some key=some value>

# Right
<family_123:some_key=some value>

# Right
<info/personal:email=xyz@example.com>

# Right but not as expected, because it'll include the spaces
<info/personal: nationality = Moroccan>
# So the entry will be:
# FAMILY: "info/personal"
# KEY: " nationality "
# VALUE: " Moroccan"
```

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

As simple as that!
There are examples in the `example` directory, use `make` to compile the run each example! Read the code for explanations

### Arrays

Arrays are here ! Here is how to use them:
```html
<food:fruits=apple;orange;banana>
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
<img src="[https://cdn.discordapp.com/attachments/1043106668839456860/1202015711191367700/Tue_Jan_30_112045_PM_01_2024.png?ex=65cbeb5d&is=65b9765d&hm=0f9fc35a1dea6e109ffa719fab3b583c7573cca3f840de345745916e7ecb7d80&](https://cdn.discordapp.com/attachments/1043106668839456860/1209171773975953529/Mon_Feb_19_051207_PM_01_2024.png?ex=65e5f3f8&is=65d37ef8&hm=8e2122cb9dfe95646b01edff90f9545c10fbf328bfa723cb081aa6c63d5f739d&)">

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
