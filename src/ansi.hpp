/*
ansi.h
File defining names for ANSI codes
Author: Dorian Lesbre
*/

#ifndef ANSI_H
#define ANSI_H

#include <iostream>

#ifdef USE_ANSI

	// Colors - defined as "" if not USE_ANSI
	#define Color_Reset       "\033[38;48m"
	#define Color_Fg_Reset    "\033[38m"
	#define Color_Bg_Reset    "\033[48m"
	#define Color_Orange      "\033[33m"
	#define Color_Green       "\033[32m"
	#define Color_Red         "\033[31m"
	#define Color_Blue        "\033[34m"
	#define Color_Purple      "\033[35m"
	#define Color_Grey        "\033[37m"
	#define Color_Cyan        "\033[36m"
	#define Color_DarkGrey    "\033[90m"
	#define Color_LightRed    "\033[91m"
	#define Color_LightGreen  "\033[92m"
	#define Color_Yellow      "\033[93m"
	#define Color_LightBlue   "\033[94m"
	#define Color_LightPurple "\033[95m"
	#define Color_Turquoise   "\033[96m"
	#define Color_White       "\033[97m"

	void inline Color_Fg(unsigned short n) {
		std::printf("\033[38;2;%um", n);
	}

	void inline Color_Fg(unsigned short r, unsigned short g, unsigned short b) {
		std::printf("\033[38;2;%u;%u;%um", r, g, b);
	}

	void inline Color_Bg(unsigned short n) {
		std::printf("\033[48;2;%um", n);
	}

	void inline Color_Bg(unsigned short r, unsigned short g, unsigned short b) {
		std::printf("\033[48;2;%u;%u;%um", r, g, b);
	}

	//Styles - defined as "" if not USE_ANSI
	#define Style_Reset         "\033[0m"
	#define Style_Bold          "\033[1m"
	#define Style_Bold_Off      "\033[22m"
	#define Style_Faint         "\033[2m"
	#define Style_Faint_Off     "\033[22m"
	#define Style_Italic        "\033[3m"
	#define Style_Italic_Off    "\033[23m"
	#define Style_Underline     "\033[4m"
	#define Style_Underline_Off "\033[24m"
	#define Style_Blink         "\033[5m"
	#define Style_Blink_Off     "\033[25m"
	#define Style_Inverse       "\033[7m"
	#define Style_Inverse_Off   "\033[22m"
	#define Style_Barred        "\033[9m"
	#define Style_Barred_Off    "\033[29m"
	#define Style_Overline      "\033[53m"
	#define Style_Overline_Off  "\033[55m"
	#define Style_Framed        "\033[51m"
	#define Style_Framed_Off    "\033[54m"
	#define Style_Circled       "\033[52m"
	#define Style_Circled_Off   "\033[54m"

// Not redefined if not USE_ANSI

	#define Clearscreen         "\033c"
	#define Clearline           "\033[2K\033[1G"

	// Cursor
	void inline Cursor_Up(unsigned int n = 1) {
		std::printf("\033[%uA", n);
	}

	void inline Cursor_Down(unsigned int n = 1) {
		std::printf("\033[%uB", n);
	}

	void inline Cursor_Foward(unsigned int n = 1) {
		std::printf("\033[%uC", n);
	}

	void inline Cursor_Back(unsigned int n = 1) {
		std::printf("\033[%uD", n);
	}

	void inline Cursor_Horizontal(unsigned int n = 1) {
		// move to horizontal absolute (1 based)
		std::printf("\033[%uG", n);
	}

	void inline Cursor_Move(unsigned int line, unsigned int column) {
		// both 1-based
		std::printf("\033[%u,%uH", line, column);
	}

	void inline Erase_Display(unsigned int j = 0) {
		// 0 cursor -> end of screen
		// 1 start of screen -> cursor
		// 2 all
		std::printf("\033[%uJ", j);
	}

	void inline Erase_Line(unsigned int j = 0) {
		// 0 cursor -> end of linn
		// 1 start of line -> cursor
		// 2 all line
		std::printf("\033[%uK", j);
	}

#else

	// Colors
	#define Color_Reset       ""
	#define Color_Fg_Reset    ""
	#define Color_Bg_Reset    ""
	#define Color_Orange      ""
	#define Color_Green       ""
	#define Color_Red         ""
	#define Color_Blue        ""
	#define Color_Purple      ""
	#define Color_Grey        ""
	#define Color_Cyan        ""
	#define Color_DarkGrey    ""
	#define Color_LightRed    ""
	#define Color_LightGreen  ""
	#define Color_Yellow      ""
	#define Color_LightBlue   ""
	#define Color_LightPurple ""
	#define Color_Turquoise   ""
	#define Color_White       ""

	void inline Color_Fg(unsigned short) {}
	void inline Color_Fg(unsigned short, unsigned short, unsigned short) {}
	void inline Color_Bg(unsigned short) {}
	void inline Color_Bg(unsigned short, unsigned short, unsigned short) {}

	//Styles
	#define Style_Reset         ""
	#define Style_Bold          ""
	#define Style_Bold_Off      ""
	#define Style_Faint         ""
	#define Style_Faint_Off     ""
	#define Style_Italic        ""
	#define Style_Italic_Off    ""
	#define Style_Underline     ""
	#define Style_Underline_Off ""
	#define Style_Blink         ""
	#define Style_Blink_Off     ""
	#define Style_Inverse       ""
	#define Style_Inverse_Off   ""
	#define Style_Barred        ""
	#define Style_Barred_Off    ""
	#define Style_Overline      ""
	#define Style_Overline_Off  ""
	#define Style_Framed        ""
	#define Style_Framed_Off    ""
	#define Style_Circled       ""
	#define Style_Circled_Off   ""

#endif // USE_ANSI

#endif // ANSI_H
