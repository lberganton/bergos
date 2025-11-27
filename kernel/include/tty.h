#ifndef TTY_H
#define TTY_H

int tty_initialize(void);
int tty_clear(void);

int tty_maxy(void);
int tty_maxx(void);

int tty_gety(void);
int tty_getx(void);

int tty_sety(int y);
int tty_setx(int x);

int tty_iscrlf(void);
int tty_setcrlf(int status);

int tty_iscursor(void);
int tty_setcursor(int status);

int tty_putchar(int ch);
int tty_printf(const char *format, ...);

#endif
