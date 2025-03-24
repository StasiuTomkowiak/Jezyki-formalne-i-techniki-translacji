# Formal Languages and Translation Techniques

Solutions to laboratory tasks from FLTT 2024/2025

## Project Structure

- `compiler/` - Contains files related to the compiler, including sources, headers, lexical files, and parser.
    - `src/` - Source files for the compiler.
    - `include/` - Header files for the compiler.
    - `lex/` - Lexical analysis files.
    - `parser/` - Parser files.
    - `virtual_machine/` - Contains files related to the virtual machine, including instructions, lexical files, and the main source file.
    - `examples/` - Example files for testing.
    - `tests/` - Test files.
- `list1/` - Files related to the first task list.
- `list2/` - Files related to the second task list.
- `list3/` - Files related to the third task list.

## Compilation

To compile the project, navigate to the appropriate directory and use `make`:

```sh
cd compiler
make
```

## Running

To run the compiled program, use the following command:

```sh
./compiler your_executable.imp
./maszyna-wirtualna your_executable.mr
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.