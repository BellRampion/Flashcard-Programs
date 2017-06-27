/*** Text-based Role-play Game ***/
#include <stdio.h>
#include <curses.h>
#include <unistd.h>

int main(){
    int i;
    int x = 0;
    int y = 0;
    char ch;


    (void) initscr();      /* initialize the curses library */
    keypad(stdscr, TRUE);  /* enable keyboard mapping */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */
    (void) echo();         /* echo input - in color */

    printf("Press h, j, k, or l to start. Press $ to stop:\n");
    clear();

    while (ch != '$'){

        clear();
        ch = getchar();

        if(ch == 'l')
        {
            x++;
            mvaddch(y, x, '@'); //first y coordinate, then the x coordinate
            refresh();
        //    sleep(1);
        }
        else if(ch == 'h')
        {
            x--;
            mvaddch(y, x, '@'); //first y coordinate, then the x coordinate
            refresh();
        //    sleep(1);
        }
        else if(ch == 'j')
        {
            y++;
            mvaddch(y, x, '@'); //first y coordinate, then the x coordinate
            refresh();
            //sleep(1);
        }
        else if(ch == 'k')
        {
            y--;
            mvaddch(y, x, '@'); //first y coordinate, then the x coordinate
            refresh();
            sleep(0.5);
        }
    }
    mvprintw(30, 10, "Press enter to continue:");
    getch();

    endwin();
}
