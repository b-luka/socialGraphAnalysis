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

## Usage & Commands

Upon launching you will be prompted to enter a file name, make sure it's in the same directory as the executable and that its in .txt format.
If an error occurs, the program will shut down and if not you will be asked to enter an option (-1 or other non valid option for help).

### Input Format
```txt
[Non negative number of starting graph vertices]
[Non negative number of starting graph edges]
[Vertex names (usernames) separated by spaces]
[vertex_from vertex_to height]
```
* For reference, look at the 3 provided example graphs. 

### Supported Commands:

| Command Index | Description |
| :--- | :--- |
| `1` | Prints the current graph state to the console. |
| `2` | Add a new edge to the graph. |
| `3` | Add a new vertex to the graph. |
| `4` | Remove and edge from the graph. |
| `5`| Remove a vertex from the graph. |
| `6`| Simulate liking a post from one user (vertex) to another. |
| `7` | Print out the largest strongly connected component in the graph. |
| `8`| Print the most probable path between two users (vertices). |
| `9` | List the k-th most influential person on the social network. |
| `0` | Exit program. |
| `other` | Print out this list to the console. |

## License
This project is open-source and available under the [MIT License](LICENSE).
