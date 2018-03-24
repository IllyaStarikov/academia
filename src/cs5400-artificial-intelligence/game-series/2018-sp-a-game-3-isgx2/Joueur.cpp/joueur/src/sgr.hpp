#ifndef SGR_HPP
#define SGR_HPP

#include <iostream>

#ifdef SGR_ALLOW_ATTRS
   #define SGR_RARE [[deprecated("Rarely supported.")]]
#else
   #define SGR_RARE
#endif

//ANSI Select Graph Rendition (SGR) keys
//If attributes are enabled via SGR_ALLOW_ATTRS then
//rarely supported attributes will be marked as deprecated
//[see https://en.wikipedia.org/wiki/ANSI_escape_code]
enum class sgr
{
   reset = 0,
   normal = 0,
   bold = 1,
   bright = 1,
   SGR_RARE faint = 2,
   SGR_RARE italic = 3,
   single_underline = 4,
   blink_slow = 5,
   SGR_RARE blink_rapid = 6,
   reverse_video = 7,
   SGR_RARE conceal = 8,
   SGR_RARE crossed_out = 9,
   default_font = 10,
   alt_font_1,
   alt_font_2,
   alt_font_3,
   alt_font_4,
   alt_font_5,
   alt_font_6,
   alt_font_7,
   alt_font_8,
   alt_font_9,
   SGR_RARE fraktur = 20,
   SGR_RARE bold_off_underline_double = 21,
   normal_color_intensity = 22,
   not_italic_not_fraktur = 23,
   no_underline = 24,
   no_blink = 25,
   image_positive = 27,
   reveal = 28,
   not_crossed_off = 29,
   text_black,
   text_red,
   text_green,
   text_yellow,
   text_blue,
   text_magenta,
   text_cyan,
   text_white,
   default_foreground = 39,
   background_black,
   background_red,
   background_green,
   background_yellow,
   background_blue,
   background_magenta,
   background_cyan,
   background_white,
   default_background = 49,
   framed = 51,
   encircled = 52,
   overlined = 53,
   not_framed_or_encircled = 54,
   not_overlined = 55,

};

inline std::ostream& operator<<(std::ostream& out, sgr code)
{
   out << "\x1b[" << static_cast<int>(code) << "m";
   return out;
}

#undef SGR_RARE

#endif // SGR_HPP
