#ifndef COLOR_H
#define COLOR_H

// Reset
#define AC_RESET "\x1b[0m"

// Základní barvy (RGB) – pevné
#define AC_BLACK   "\x1b[38;2;0;0;0m"
#define AC_RED     "\x1b[38;2;255;0;0m"
#define AC_GREEN   "\x1b[38;2;0;255;0m"
#define AC_YELLOW  "\x1b[38;2;255;255;0m"
#define AC_BLUE    "\x1b[38;2;0;0;255m"
#define AC_MAGENTA "\x1b[38;2;255;0;255m"
#define AC_CYAN    "\x1b[38;2;0;255;255m"
#define AC_WHITE   "\x1b[38;2;255;255;255m"

// Extra odstíny
#define AC_ORANGE  "\x1b[38;2;255;165;0m"
#define AC_PINK    "\x1b[38;2;255;192;203m"
#define AC_LIME    "\x1b[38;2;50;205;50m"
#define AC_PURPLE  "\x1b[38;2;128;0;128m"
#define AC_TEAL    "\x1b[38;2;0;128;128m"
#define AC_GRAY    "\x1b[38;2;128;128;128m"
#define AC_BROWN   "\x1b[38;2;139;69;19m"

#endif
