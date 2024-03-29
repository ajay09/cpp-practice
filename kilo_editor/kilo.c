// https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html
// use reset to reset the attributes of your terminal

/*** includes ***/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h> // to get terminal window size
#include <string.h>



/*** defines ***/

#define KILO_VERSION "0.0.1"

#define CTRL_KEY(k) (0x1f & (k))  // Press Ctrl-Q to quit


// choose a representation for arrow keys that doesn’t conflict with w,a,s,d
enum editorKey {
  ARROW_LEFT = 1000, //'a',
  ARROW_RIGHT,       //'d',
  ARROW_UP,          //'w',
  ARROW_DOWN,        //'s'
  PAGE_UP,           // Page Up is sent as <esc>[5~ and Page Down is sent as <esc>[6~.
  PAGE_DOWN,
  HOME_KEY,
  END_KEY,
  DEL_KEY            // sends the escape sequence <esc>[3~       esc <=> \x1b
};
// The Home key could be sent as <esc>[1~, <esc>[7~, <esc>[H, or <esc>OH. Similarly, 
//  the End key could be sent as <esc>[4~, <esc>[8~, <esc>[F, or <esc>OF



/*** data ***/

struct editorConfig {
    int cx, cy; // we want user to be able to move cursor around. Thus we need to keep track of cursor in a global state.
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

struct editorConfig E;


/*** terminal ***/

// Prints the error message and exits.
void die(const char *s) {
    // clear the screen on exit
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);  // perror() comes from <stdio.h>, and exit() comes from <stdlib.h>.
    exit(1);
    // Most C library functions that fail will set the global errno variable to indicate what the error was. 
    // perror() looks at the global errno variable and prints a descriptive error message for it. 
    // It also prints the string given to it before it prints the error message, which is meant to 
    // provide context about what part of your code caused the error.
}


// To reset the terminal to its original settings
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1)
        die("tcsetattr");
    // tcsetattr(), tcgetattr(), and read() all return -1 on failure, and set the errno value to indicate the error.
}


// Enable raw mode : input is taken as you press a key and not wait for you to press enter
//                 : disable various control flags as they should not work in a text editor
void enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &E.orig_termios) == -1)  // get the attributes
        die("tcgetattr");
    atexit(disableRawMode); // register callback

    struct termios raw = E.orig_termios;
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    // ECHO flag is to suggest if we want our provided input to be shown on stdout or not.
    //   ~ECHO flag turns off it off 
    // There is an ICANON flag that allows us to turn off canonical mode. 
    //   This means we will finally be reading input byte-by-byte, instead of line-by-line.


    // Ctrl-C sends a SIGINT signal to the current process which causes it to terminate, and 
    // Ctrl-Z sends a SIGTSTP signal to the current process which causes it to suspend.
    // ISIG helps us to disable/enable ctrl-c/z

    // Disable Ctrl-S and Ctrl-Q
    // By default, Ctrl-S and Ctrl-Q are used for software flow control. 
    // Ctrl-S stops data from being transmitted to the terminal until you press Ctrl-Q
    // Flag for this is  IXON
    //   XOFF to pause transmission and XON to resume transmission.

    // Disable Ctrl-V
    // when you type Ctrl-V, the terminal waits for you to type another character and then 
    // sends that character literally. For example, before we disabled Ctrl-C, you might’ve been 
    // able to type Ctrl-V and then Ctrl-C to input a 3 byte. 
    // We can turn off this feature using the IEXTEN flag.
    // Turning off IEXTEN also fixes Ctrl-O in macOS, whose terminal driver is otherwise 
    //  set to discard that control character.


    // Fix Ctrl-M
    // If you run the program now and go through the whole alphabet while holding down Ctrl, 
    // you should see that we have every letter except M. Ctrl-M is weird: it’s being read as 10, 
    // when we expect it to be read as 13, since it is the 13th letter of the alphabet, and Ctrl-J 
    // already produces a 10. What else produces 10? The Enter key does.
    // ICRNL The I stands for “input flag”, CR stands for “carriage return”, and NL stands for “new line”.
    // It turns out that the terminal is helpfully translating any carriage returns (13, '\r') 
    //  inputted by the user into newlines (10, '\n'). Let’s turn off this feature.

    // Turn off all output processing
    // terminal translates each newline ("\n") we print into a carriage return followed by a newline ("\r\n")
    // The terminal requires both of these characters in order to start a new line of text. 
    // The carriage return moves the cursor back to the beginning of the current line, and the 
    // newline moves the cursor down a line, scrolling the screen if necessary.
    // We will turn off all output processing features by turning off the OPOST flag. 
    // In practice, the "\n" to "\r\n" translation is likely the only output processing feature turned on by default.

    
    // BRKINT, INPCK, ISTRIP, and CS8 are some other flags that are turned off for modern termials by default.


    raw.c_cc[VMIN] = 0; 
    // The VMIN value sets the minimum number of bytes of input needed before read() can return. 
    // We set it to 0 so that read() returns as soon as there is any input to be read.
    raw.c_cc[VTIME] = 1;
    // The VTIME value sets the maximum amount of time to wait before read() returns. It is in 1/10 of a second

    // Currently, read() will wait indefinitely for input from the keyboard before it returns. 
    // What if we want to do something like animate something on the screen while waiting for user input? 
    // We can set a timeout, so that read() returns if it doesn’t get any input for a certain amount of time.

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)  // set the attributes with updated flags
        die("tcsetattr");;
}

// When tcgetattr() fails
// An easy way to make tcgetattr() fail is to give your program a text file or a pipe as the standard input instead 
//    of your terminal. To give it a file as standard input, run ./kilo <kilo.c. 
// To give it a pipe, run echo test | ./kilo. Both should result in the same error from tcgetattr(), 
//    something like Inappropriate ioctl for device



// editorReadKey()’s job is to wait for one keypress, and return it. 
// Later, we’ll expand this function to handle escape sequences, 
//  which involves reading multiple bytes that represent a single keypress, as is the case with the arrow keys.
int editorReadKey() {
    int nread;
    char c;
    // If read times out it will return 0.
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) { // read 1 byte from std input to variable c
                           // errno.h
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }

    // If we read an escape character, we immediately read two more bytes into the seq buffer. 
    // If either of these reads time out (after 0.1 seconds), then we assume the user just pressed the Escape key 
    //   and return that.
    if (c == '\x1b') {
        char seq[3];

        if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

        if (seq[0] == '[') {
            if (seq[1] > '0' && seq[1] <= '9') {
                if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
                //  If the byte after [ is a digit, we read another byte expecting it to be a ~. 
                // Then we test the digit byte to see if it’s a 5 or a 6.
                if (seq[2] == '~') {
                    switch (seq[1]) {
                        case '1': return HOME_KEY;
                        case '3': return DEL_KEY;
                        case '4': return END_KEY;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        case '7': return HOME_KEY;
                        case '8': return END_KEY;
                    }
                }
            } else {
                switch (seq[1]) {
                    // We have basically aliased the arrow keys to the w,a,s,d keys
                    //  ARROW_UP, ARROW_LEFT, ARROW_DOWN, and ARROW_RIGHT.
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                    case 'H': return HOME_KEY;
                    case 'F': return END_KEY;
                }
            }
        } else if (seq[0] == 'O') {
            switch (seq[1]) {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
            }
        }

        return '\x1b';
    } else {
        return c;
    }
}
// Note that editorReadKey() belongs in the /*** terminal ***/ section because it deals with low-level terminal input


int getCursorPosition(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;
    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;
    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;
    }
    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;
    return 0;
    // printf("\r\n&buf[1]: '%s'\r\n", &buf[1]);
    // we’ve inserted a temporary call to editorReadKey() to let us observe our debug output before 
    // the screen gets cleared on exit.
    // editorReadKey();
    // return -1;
}

// If ioctl() failed in either way, we have getWindowSize() report failure by returning -1. 
// If it succeeded, we pass the values back by setting the int references that were passed to the function.
// This is a common approach to having functions return multiple values in C. 
// It also allows you to use the return value to indicate success or failure.
int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    // ioctl(), TIOCGWINSZ, and struct winsize come from <sys/ioctl.h>.
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) // move the cursor to the bottom right position
            return -1;
        return getCursorPosition(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }

    // ioctl() isn’t guaranteed to be able to request the window size on all systems, 
    // so we are going to provide a fallback method of getting the window size.

    // The strategy is to position the cursor at the bottom-right of the screen, 
    // then use escape sequences that let us query the position of the cursor. 
    // That tells us how many rows and columns there must be on the screen.
}




/*** append buffer ***/
/*
It’s not a good idea to make a whole bunch of small write()’s every time we refresh the screen. 
It would be better to do one big write(), to make sure the whole screen updates at once. 
Otherwise there could be small unpredictable pauses between write()’s, which would cause an annoying flicker effect.

We want to replace all our write() calls with code that appends the string to a buffer, and then write() 
this buffer out at the end. Unfortunately, C doesn’t have dynamic strings, so we’ll create our own 
dynamic string type that supports one operation: appending.
*/
struct abuf {
    char *b; // a pointer to our buffer in memory
    int len; // length
};

// Acts as a constructor for abuf type
#define ABUF_INIT {NULL, 0} // constant which represents an empty buffer

// realloc() and free() come from <stdlib.h>. memcpy() comes from <string.h>.
void abAppend(struct abuf *ab, const char *s, int len) {
    // gives us a block of memory that is the size of the current string plus the string we are appending
    // realloc will either extend the size of the block or free it and allocate a new one of required size.
    char *new = realloc(ab->b, ab->len + len);  // Changes the size of the memory block pointed to by ptr.

    if (new == NULL) return;
    // memcopy to copy the string s after the end of the current data in the buffer
    memcpy(&new[ab->len], s, len);
    ab->b = new;
    ab->len += len;
}

// is a destructor that deallocates the dynamic memory used by an abuf.
void abFree(struct abuf *ab) {
    if (ab->b != NULL)
        free(ab->b);
}


/*** input ***/

void editorMoveCursor(int key) {
    switch(key) {
        case ARROW_LEFT:
            if (E.cx != 0) {
                E.cx--;
            }
            break;
        case ARROW_RIGHT:
            if (E.cx != E.screencols - 1) {
                E.cx++;
            }
            break;
        case ARROW_UP:
            if (E.cy != 0) {
                E.cy--;
            }
            break;
        case ARROW_DOWN:
            if (E.cy != E.screenrows - 1) {
                E.cy++;
            }
            break;
    }
}


// editorProcessKeypress() waits for a keypress, and then handles it. 
//  Later, it will map various Ctrl key combinations and other special keys to different editor functions, 
//  and insert any alphanumeric and other printable keys’ characters into the text that is being edited.
void editorProcessKeypress() {
    int c = editorReadKey();

    switch (c) {
        case CTRL_KEY('q'):
            // clear the screen while exiting.
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);
            break;
            case HOME_KEY:
                E.cx = 0;
                break;
            case END_KEY:
                E.cx = E.screencols - 1;
                break;
        case PAGE_UP:
        case PAGE_DOWN: {
                // We create a code block with that pair of braces so that we’re allowed to declare the times variable. 
                // (You can’t declare variables directly inside a switch statement.)
                int times = E.screenrows;
                while (times--)
                    editorMoveCursor(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
            }
            break;
        case ARROW_LEFT:
        case ARROW_RIGHT:
        case ARROW_UP:
        case ARROW_DOWN:
            editorMoveCursor(c);
            break;
    }
}




/*** output ***/

// We will render the editor's user interface to the screen after each keypress. 

// draws a column of tildes on the left hand side of the screen like vim
void editorDrawRows(struct abuf *ab) {
    for (int y = 0; y < E.screenrows; y++) {
        if (y == E.screenrows / 3) {
            char welcome[80];
            int welcomelen = snprintf(welcome, sizeof(welcome),
                                "Kilo editor -- version %s", KILO_VERSION);
            if (welcomelen > E.screencols) welcomelen = E.screencols;
            int padding = (E.screencols - welcomelen) / 2;
            if (padding) {
                abAppend(ab, "~", 1);
                padding--;
            }
            while (padding--) abAppend(ab, " ", 1);
            abAppend(ab, welcome, welcomelen);
        } else {
            abAppend(ab, "~", 1);
            // write(STDOUT_FILENO, "~", 1);
        }

        abAppend(ab, "\x1b[K", 3);  // The K command erases part of the current line.
                                    // 0 is the default argument, erases the part of the line to the right of the cursor.
        if (y < E.screenrows - 1) {      // so that we do not go to next line after printing the ~ on the last line.
            abAppend(ab, "\r\n", 2);
            // write(STDOUT_FILENO, "\r\n", 2);
        }
    }
}


// For this we'll start by clearing the screen
void editorRefreshScreen() {
    struct abuf ab = ABUF_INIT;     // initialize a new abuf

    abAppend(&ab, "\x1b[?25l", 6); // hide the cursor before refreshing the screen
    // write() and STDOUT_FILENO come from <unistd.h>
    // abAppend(&ab, "\x1b[2J", 4); // don't clear the entire screen at once. clear each line as we refresh it.
                                    // clear line added in editorDrawRows()
    // write(STDOUT_FILENO, "\x1b[2J", 4); // clear the screen
    abAppend(&ab, "\x1b[H", 3);
    // write(STDOUT_FILENO, "\x1b[H", 3);  // reposition the cursor

    editorDrawRows(&ab);

    char buf[32];
    // We add 1 to E.cy and E.cx to convert from 0-indexed values to the 1-indexed values that the terminal uses.
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", E.cy + 1, E.cx + 3);  // use this instead of abAppend(&ab, "\x1b[H", 3);
                                                                    // We changed the old H command into an H command with arguments, 
                                                                    // specifying the exact position we want the cursor to move to
    abAppend(&ab, buf, strlen(buf));

    // abAppend(&ab, "\x1b[H", 3);
    // write(STDOUT_FILENO, "\x1b[H", 3);  // reposition the cursor   
    abAppend(&ab, "\x1b[?25h", 6);  // unhide the cursor after refresh finishes.

    // In the end write the ab to std out
    write(STDOUT_FILENO, ab.b, ab.len);
    abFree(&ab);
}



// printf("%d\r\n", c); // since we turned off automatic  \n => \r\n  translation. Thus we have to supply \r
// fun => try replacing \r and \n

/*** init ***/

void initEditor() {
    E.cx = E.cy = 0;

    if (getWindowSize(&E.screenrows, &E.screencols) == -1)
        die("getWindowSize");
}

int main() {
    enableRawMode();
    initEditor();

    while (1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}


/*
That concludes our arrow key handling code. At this point, it can be fun to try entering an escape sequence 
manually while the program runs. Try pressing the Escape key, the [ key, and Shift+C in sequence really fast, 
and you may see your keypresses being interpreted as the right arrow key being pressed. 
You have to be pretty fast to do it, so you may want to adjust the VTIME value in enableRawMode() temporarily, 
to make it easier. 
(It also helps to know that pressing Ctrl-[ is the same as pressing the Escape key, for 
the same reason that Ctrl-M is the same as pressing Enter: Ctrl clears the 6th and 7th bits of the character 
you type in combination with it.)
*/


