# tex_cleanup

`tex_cleanup` is a utility for LaTeX users that cleans up auxiliary `.aux` and `.log` files from a directory and its subdirectories. It supports running `pdflatex` on `.tex` files before or after the cleanup process.

## Problem

When working with LaTeX, temporary files like `.aux` and `.log` files are generated. These files can clutter your directories and may not always be necessary after your document has been successfully built. `tex_cleanup` is designed to automatically delete these files for you.

Additionally, `tex_cleanup` can run `pdflatex` on `.tex` files in the directory and subdirectories before or after the cleanup process.

## Installation

First, clone the repository from GitHub:

```bash
git clone https://github.com/username/tex_cleanup.git
```

Replace 'username' with the correct GitHub username

Navigate to the cloned directory:

```bash
cd tex_cleanup
```

Compile the C program using the included Makefile:

```bash
make
```

This will produce an executable named `tex_cleanup`.

## Usage

You can run the `tex_cleanup program` with no arguments to clean the current directory:

```bash
./tex_cleanup
```

To specify a different directory, use the -d or --directory flag:

```bash
./tex_cleanup -d path/to/directory
```

To output each file that is deleted, use the -v or --verbose flag:

```bash
./tex_cleanup -v
```

To run `pdflatex` on each `.tex` file before the cleanup process, use the `-b` or `--run_before` flag:

```bash
./tex_cleanup -b
```

To run pdflatex on each .tex file after the cleanup process, use the -a or --run_after flag:

```bash
./tex_cleanup -a
```

## Help

For a helpful list of all arguments, run the program with the `-h` or `--help` argument:

```bash
./tex_cleanup -h

```

## Contributing

Currently no rules, feel free to fork and make modifications.

## License

This project is licensed under the terms of the MIT license.
