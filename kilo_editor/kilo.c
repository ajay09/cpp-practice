// https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    // To reset the terminal to its original settings
}

// Enable raw mode : input is taken as you press a key and not wait for you to press enter
//                 : disable various control flags as they should not work in a text editor
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);  // get the attributes
    atexit(disableRawMode); // register callback

    struct termios raw = orig_termios;
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

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);  // set the attributes with updated flags
}

int main() {
    enableRawMode();

    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1); // read 1 byte from std input to variable c
        // If read times out it will return 0.

        if (iscntrl(c)) { // iscntrl() tests whether a character is a control character. 
            printf("%d\r\n", c); // since we turned off automatic  \n => \r\n  translation. Thus we have to supply \r
        } else {
            printf("%d ('%c')\r\n", c, c);  // fun => try replacing \r and \n
        }

        if (c == 'q') break;
    }

    return 0;
}
