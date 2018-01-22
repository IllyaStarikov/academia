//  File Name:  enChar.h
//  Function:   Define an enumeration type for characters
//              used in lexical analyzer
//  Author:     Franck Xia
//  Creation:   Nov. 3, 2001

#ifndef ENCHAR_H_42431
#define ENCHAR_H_42431

enum enChar
{
    DIGIT=0,
    DOT,      //1      // floating point
    LETTER,   //2
    UNDERSCORE,//3
    BLANK,     //4
    ENDCODE,   //5    // we use $ for the end of program
    ENDLINE,   //6
    GENERAL    //7
};

#endif

