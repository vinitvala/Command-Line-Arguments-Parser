# Command-Line-Arguments-Parser

## Project Overview

This project is a command-line tool that allows users to search for and replace text in a file. It provides several optional features, including the ability to limit the search and replace function to specific lines, as well as support for wildcard searching. The tool requires the input file and output file paths, along with the search and replace texts as arguments.

The syntax for running the tool is as follows:

```bash
 $ text_tool -s <search_text> -r <replace_text> [-w] [-l start_line,end_line] <input_file> <output_file>
 ```
 
 ## Arguments
 
**-s <search_text>:** The text to search for in the input file. This option is required.

**-r <replace_text>:** The text that will replace the search text in the output file. This option is required.

**-w:** Enable wildcard searching of words. This option is optional.

**-l <start_line,end_line>:** The range of lines of the input file to process. The range is inclusive. Lines outside this range are simply copied from the input file to the output file unmodified. If end_line is greater than the number of lines in the file, the tool will read to the end of the file. Note that line numbers start at 1, not 0. This option is optional.

**<input_file>:** Pathname of the input file. This argument is required.

**<output_file>:** Pathname of the output file. This argument is required.

## Usage Example

For example, to search for occurrences of "hello" in the lines 4 through 10 (inclusive) in the file **input1.txt** located in the directory named "dir1", and replace the occurrences of "hello" with "wonder" in the file **output1.txt** (which will be created in the directory "dir2"), the command-line arguments would be as follows:

```bash
 $ text_tool -s hello -r wonder -l 4,10 dir1/input1.txt dir2/output1.txt
 ```
 
This tool is a simple yet powerful way of manipulating text in files. Enjoy using it!

Please remember that this command-line tool assumes that the **input_file** and **output_file** refer to different files.

## Installation 

Follow the steps below to install and run this command-line arguments:

### Step 1: Clone the Repository

First, you will need to clone the repository from GitHub. Open a terminal and use the **git** command to clone. 

```bash
 $ git clone https://github.com/mohamzamir/Command-line-Arguments.git
 ```
 
 ### Step 2: Navigate to the Project Directory
 
 Change your current directory to the project's directory:
 
 ```bash
$ cd <project-directory>
 ```
 
 Replace **<project-directory>** with the name of the directory that was created when you cloned the repository.
 
 ### Step 3: Build the Project
 
 The project uses a **Makefile** for compiling the source code. To build the project, use the **make** command in the terminal:
 
  ```bash
$ make
 ```
 
This should compile the source code and create an executable file. If there are any errors during the compilation process, you should see them in the terminal.
 
 ### Step 4: Run Tests
 
 You can run the project's tests using the **make test** command:
 
  ```bash
$ make test
 ```
 
 This should run all the tests for the project. If the tests pass, you should see a success message in the terminal.
