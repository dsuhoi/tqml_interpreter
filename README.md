# tqml_interpreter

### About TQML
TQML (Text Quest Markup Language) - a markup language for text quests (Wiki Wiki), created to simplify the creation of games of this genre.
The selected blocks are used for displaying text (in the main, secondary, and header Windows), selecting a response, and clicking links to other blocks.
which may be in different files.
#### The main blocks:
- `<text[*]>...</text>` - section block. It includes texts and links related to each other (question + answers). `*` - a number from `0` to `999` that defines the block number in this file. The quest always starts with the section number 0.

- `<header>...</header>` - header block. Text for the upper window (there can only be one in the section).

- `<info>...</info>` - additional information block. Text located in the lower-left window (there can only be one in the section).

- `<main>...</main>` - the main text block (there can only be one in the section).

- `<links>...</links>` - link block. This section contains only links to other sections (there can only be one per section).

- `<&(*)[**] = "***" >` - link. `*` - absolute path to the file (from the directory with the first file)(leave empty to search for a section in this file), `**` - section number, `***` - the response that leads to a click on the link.

#### Formatting modifiers:
- `<n>` - replaced with the `'\n'` character, Because the interpreter does not take into account the tab and carriage translation in the text itself.

### About interpreter
The TQML interpreter is a program for processing TQML and performing quests based on it. Input and output of information via the terminal is performed using the library. To display information about the window, there is a system submenu (the current page, the number of pages and characters in the text, as well as a string with exceptions). You can switch pages using the left and right keys. To enter an answer, press ENTER.
The interpreter is currently running on UNIX systems.
### Installation
Instalation command:

`make`

Run the quest:

`./tqml path/first_file.txt`
