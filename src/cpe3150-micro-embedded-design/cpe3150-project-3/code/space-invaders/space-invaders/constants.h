//
//  constants.h
//  space-invaders
//
//  Created by Illya Starikov on 11/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef constants_h
#define constants_h

//typedef enum { false, true } bool;

static const char NAME[] = "Text Invaders";

static const char SCORE[] = "    Score: ";
static const char LIVES[] = "    Lives: ";

static const char SHOT = 'A';

static const unsigned int STATE_CHANGE_ALIENS = 1500;

// These are borrowwed from https://github.com/macdice/ascii-invaders/blob/master/invaders.c
static const char *gunner[] = {
    " mAm " ,
    "MAZAM" };

static const char *alienBlank =  "      ";
static const char *smallInvaderOne[] = {
    " {@@} ",
    " /\"\"\\ " };
    
static const char *smallInvaderTwo[] = {
    " {@@} ",
    " \\\\//\  " };

static const char *mediumInvaderOne[] = {
    " /MM\\ ",
    " |~~| " };


static const char *mediumInvaderTwo[] = {
    " /MM\\ ",
    " \\~~/ ",
    "      " };

static const char *largeInvaderOne[] = {
    " dOOb ",
    " ^/\\^ " };

static const char *largeInvaderTwo[] = {
    " dOOb ",
    " ~||~ " };


static const char *ufo[] = {
    "_/MM\\_",
    "qWAAWp" };

static const char *gunnerExplode[]  = {
    " ,' %  ",
    " ;&+,! ",
    " -,+$! ",
    " +  ^~ " };

static const char *alienExplode[] = {
    " \\||/ ",
    " /||\\ ",
    "      " };

static const char *shelter[] = {
    " /MMMMM\\  ",
    " MMMMMMM   ",
    " MMM MMM   " };

#endif /* constants_h */
