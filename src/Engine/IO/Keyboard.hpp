/* Keyboard class 
 * Contains method to know if a key is pressed */
#pragma once
#ifndef _KEYBOARD_HPP_
#define _KEYBOARD_HPP_

#define NUM_KEYS 1024

class Keyboard {
    public: 
        /* Denotes whether a key is pressed */
        static bool isKeyPressed(int);

        static void setKeyStatus(int, int);

        static void reset();

    private:
        static int keyStatus[NUM_KEYS];
};

#endif