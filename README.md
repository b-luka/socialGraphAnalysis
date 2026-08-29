# socialGraphAnalysis
Simulate a small social media using graphs, written in C++.

## Compilation Commands:
* **Compile the project:**
  ```bash
  make
  ```
* **Clean build files (object files and executable):**
  ```bash
  make clean
  ```
* **Run the emulator directly after compilation:**
  ```bash
  .\socialGraph.exe
  ```

---

## Usage

Upon launching you will be prompted to enter a file name, make sure it's in the same directory as the executable and that its in .txt format.
If an error occurs, the program will shut down and if not you will be asked to enter an option (0 for help).

### Input Format
```txt
[Non negative number of starting graph vertices]
[Non negative number of starting graph edges]
[Vertex names (usernames) separated by spaces]
[vertex_from vertex_to height]
```
* For reference, look at the 3 provided example graphs. 

### Supported Commands:

| Command | Options (Flags) | Arguments | Description | Example |
| :--- | :--- | :--- | :--- | :--- |
| `echo` | None | `[input]` | Prints the provided text to the screen. | `echo "Hello World"` |
| `date` | None | None | Displays the current system date. | `date` |
| `time` | None | None | Displays the current system time. | `time` |
| `head` | `-n[lines]` | `[input]` | Outputs the first part (lines) of a file. | `head -n5 file.txt` |
| `prompt`| None | `[input]`| Changes the default terminal prompt indicator. | `prompt "#"` |
| `touch`| None | `[input_file]` | Creates a new empty file, if it doesn't exist. | `touch new_file.txt` |
| `rm` | None | `[input_file]` | Removes files. | `rm old_file.txt` |
| `truncate`| None | `[input_file]` | Removes the contents of a file. | `truncate file.txt` |
| `tr` | None | `[input] [set1] [set2]`| Translates or deletes characters every occurence of a string. | `tr "Hello World!" " " "-"` |
| `wc` | `-w`, `-c` | `[input]` | Counts words or characters in a given input. | `wc -l notes.txt` |
| `batch` | None | `[input]` | Reads and executes commands from the input (careful with recursion!) | `batch commands.bat` |

* **`[input]`**: *accepts either a string (surrounded by quotation marks), a file (provided as the relative path) or, if nothing is provided, will read from the console until it detects EOF (Ctrl + Z).*
* **`[input_file]`**: *accepts only files as input and will not work otherwise.*

### I/O Redirection:
* **`>` (Overwrite):** Redirects standard output of a command to a file, overwriting its content.
  ```bash
  echo "Hello World" > output.txt
  ```
* **`>>` (Append):** Redirects standard output of a command, appending it to the end of a file.
  ```bash
  date >> log.txt
  ```
* **`<` (Input):** Redirects a file's content into the standard input of a command.
  ```bash
  wc -w < input.txt
  ```

### Pipelines (`|`):
You can connect the output of one command directly into the input of another.
* **Basic pipeline:**
  ```bash
  echo "hello terminal" | wc -c
  ```
* **Pipeline combined with redirection:**
  ```bash
  echo input.txt | head -n1 | wc -w > output.txt
  ```

## License
This project is open-source and available under the [MIT License](LICENSE).
