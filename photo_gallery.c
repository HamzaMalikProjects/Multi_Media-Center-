/*----------------------------------------------------------------------------
 * Name:    Blinky.c (Photo Gallery Module)
 * Purpose: LED Flasher and Graphic Demo
 *----------------------------------------------------------------------------*/

#include <LPC17xx.H> 
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "photos.h"

int selector();
int selected();

extern unsigned char ClockLEDOn;
extern unsigned char ClockLEDOff;
extern unsigned char ClockANI;
extern unsigned int counter;

extern int images(int x);

void photo_menu() {
    // 1. Global Background
    GLCD_SetBackColor(Navy);

    // 2. Header Bar (White Background, Navy Text)
    GLCD_SetBackColor(White);
    GLCD_SetTextColor(Navy);
    // Centered: 3 spaces left, 4 right
    GLCD_DisplayString(0, 0, 1, "   PHOTO GALLERY    ");

    // 3. Sub-header / Decoration
    GLCD_SetBackColor(Navy);
    GLCD_SetTextColor(Cyan);
    // Centered: 4 spaces left, 5 right
    GLCD_DisplayString(1, 0, 1, "    Visual Mode     ");

    // 4. Separator
    GLCD_SetTextColor(White);
    GLCD_DisplayString(2, 0, 1, "--------------------");

    // 5. Footer Instructions (LightGrey Bar)
    GLCD_SetBackColor(LightGrey);
    GLCD_SetTextColor(Black);
    // Centered: 3 spaces left, 3 right
    GLCD_DisplayString(8, 0, 1, "   Scroll to View   ");
    // Centered: 2 spaces left, 3 right
    GLCD_DisplayString(9, 0, 1, "  Click to Return   "); 
}

int photo(void) // Function for displaying image
{
    /* Main Program */
    // Selector to see which program the user is choosing
    int selector = 0;
    int selected = 0;

    int joystick_val = 0;  // Track the current joystick value
    int joystick_prev = 0; // Track the previous value for the joystick

    KBD_Init();
    LED_Init();

    // Initialize Screen to Navy
    GLCD_Clear(Navy);
    photo_menu();

    SysTick_Config(SystemCoreClock / 100);

    while (1) // Loop forever
    {
        joystick_val = get_button();

        if (joystick_val != joystick_prev)
        {
            if (joystick_val == KBD_DOWN)
            {
                if (selector >= 4) {
                    selector = 4;
                } else {
                    selector += 1;
                }
            }
            else if (joystick_val == KBD_UP)
            {
                if (selector <= 1) {
                    selector = 1;
                } else {
                    selector -= 1;
                }
            }
        
            else if (joystick_val == KBD_SELECT)
            {
                if (selector == 1)
                {
                    GLCD_Clear(Black); 
                    images(1);

                    
                    GLCD_Clear(Navy);
                    photo_menu();
                }
                else if (selector == 2)
                {
                    GLCD_Clear(Black);
                    images(2);

                    GLCD_Clear(Navy);
                    photo_menu();
                }
                else if (selector == 3)
                {
                    GLCD_Clear(Black);
                    images(3);

                    GLCD_Clear(Navy);
                    photo_menu();
                }
                else if (selector == 4)
                {
                    // Exit back to Main Menu
                    GLCD_Clear(Navy);
                    return (0);
                }
            }

            joystick_prev = joystick_val;
        }

      
        /* REDRAWING LOGIC - CENTERED ALIGNED BLOCK */
        /* Text starts at Index 4. Brackets start at Index 2. */

        if (selected == 0)
        {
            if (selector == 1)
            {
                photo_menu(); // Keep base clear

                // Selected Item: Cyan Button
                GLCD_SetBackColor(Cyan);
                GLCD_SetTextColor(Black);
                GLCD_DisplayString(4, 0, 1, "  [ View Image 1 ]  ");

                // Unselected
                GLCD_SetBackColor(Navy);
                GLCD_SetTextColor(White);
                GLCD_DisplayString(5, 0, 1, "    View Image 2    ");
                GLCD_DisplayString(6, 0, 1, "    View Image 3    ");
                GLCD_DisplayString(7, 0, 1, "    Return Home     "); 
            }
            else if (selector == 2)
            {
                photo_menu();

                GLCD_SetBackColor(Navy);
                GLCD_SetTextColor(White);
                GLCD_DisplayString(4, 0, 1, "    View Image 1    ");

                // Selected
                GLCD_SetBackColor(Cyan);
                GLCD_SetTextColor(Black);
                GLCD_DisplayString(5, 0, 1, "  [ View Image 2 ]  ");

                GLCD_SetBackColor(Navy);
                GLCD_SetTextColor(White);
                GLCD_DisplayString(6, 0, 1, "    View Image 3    ");
                GLCD_DisplayString(7, 0, 1, "    Return Home     ");
            }
            else if (selector == 3)
            {
                photo_menu();

                GLCD_SetBackColor(Navy);
                GLCD_SetTextColor(White);
                GLCD_DisplayString(4, 0, 1, "    View Image 1    ");
                GLCD_DisplayString(5, 0, 1, "    View Image 2    ");

                // Selected
                GLCD_SetBackColor(Cyan);
                GLCD_SetTextColor(Black);
                GLCD_DisplayString(6, 0, 1, "  [ View Image 3 ]  ");

                GLCD_SetBackColor(Navy);
                GLCD_SetTextColor(White);
                GLCD_DisplayString(7, 0, 1, "    Return Home     ");
            }
            else if (selector == 4)
            {
                photo_menu();

                GLCD_SetBackColor(Navy);
                GLCD_SetTextColor(White);
                GLCD_DisplayString(4, 0, 1, "    View Image 1    ");
                GLCD_DisplayString(5, 0, 1, "    View Image 2    ");
                GLCD_DisplayString(6, 0, 1, "    View Image 3    ");

                // Selected
                GLCD_SetBackColor(Cyan);
                GLCD_SetTextColor(Black);
                GLCD_DisplayString(7, 0, 1, "  [ Return Home ]   ");
            }
            else
            {
                // Default State
                photo_menu();
                GLCD_SetBackColor(Navy);
                GLCD_SetTextColor(White);
                GLCD_DisplayString(4, 0, 1, "    View Image 1    ");
                GLCD_DisplayString(5, 0, 1, "    View Image 2    ");
                GLCD_DisplayString(6, 0, 1, "    View Image 3    ");
                GLCD_DisplayString(7, 0, 1, "    Return Home     ");
            }
        }
    }
}