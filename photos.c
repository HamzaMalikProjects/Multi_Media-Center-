#include <LPC17xx.H> /* LPC17xx definitions */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

// --- EXTERNAL IMAGE DATA ---
extern unsigned char JERRY_pixel_data[];
extern unsigned char MUSIC_pixel_data[];
extern unsigned char HAMZA_pixel_data[];

int images(int x)
{
    int joystick_val = 0;
    int joystick_prev = 0;

    // Start with the image selected from the main menu
    int current_img = x;

    // Flag to trigger screen redraw
    int needs_refresh = 1;

    KBD_Init();
    LED_Init();

    SysTick_Config(SystemCoreClock / 100);

    while (1)
    {
        joystick_val = get_button();

        // --- INPUT LOGIC ---
        if (joystick_val != joystick_prev)
        {
            // NEXT IMAGE (Right or Down)
            if (joystick_val == KBD_RIGHT || joystick_val == KBD_DOWN) {
                current_img++;
                if (current_img > 3) current_img = 1; // Wrap around to first
                needs_refresh = 1;
            }
            // PREVIOUS IMAGE (Left or Up)
            else if (joystick_val == KBD_LEFT || joystick_val == KBD_UP) {
                current_img--;
                if (current_img < 1) current_img = 3; // Wrap around to last
                needs_refresh = 1;
            }
            // EXIT (Center Click)
            else if (joystick_val == KBD_SELECT) {
                LED_Off(0);
                LED_Off(1);
                LED_Off(2);
                GLCD_Clear(Black);
                return 0;
            }

            joystick_prev = joystick_val;
        }

        // --- REDRAW LOGIC ---
        if (needs_refresh) {
            needs_refresh = 0;

            // 1. Clear Screen to remove old image artifacts
            GLCD_Clear(Black);

            // 2. Draw Footer (Navigation Help) - Row 9 (Y=216)
            // Centered to exactly 20 characters
            GLCD_SetBackColor(Navy);
            GLCD_SetTextColor(White);
            GLCD_DisplayString(9, 0, 1, "< PREV  EXIT  NEXT >");

            // 3. Draw Header & Content based on current_img
            // Moving titles to Header (Row 0) prevents overlap with large images
            GLCD_SetBackColor(Navy);
            GLCD_SetTextColor(Cyan);

            // Turn off all LEDs first
            LED_Off(0);
            LED_Off(1);
            LED_Off(2);

            if (current_img == 1) {
                // Header (Centered 20 chars: 3 spaces + 14 text + 3 spaces)
                GLCD_DisplayString(0, 0, 1, "   GALLERY: JERRY   ");

                // Image: Centered X=70, Y=30 (Fits between Header 24px and Footer 216px)
                // 30 + 180 = 210 (Safe)
                GLCD_Bitmap(70, 30, 180, 180, JERRY_pixel_data);
                LED_On(0);
            }
            else if (current_img == 2) {
                // Header (Centered 20 chars: 1 space + 19 text)
                GLCD_DisplayString(0, 0, 1, " GALLERY: HAMZAS FIT");

                // Image: Centered X=70, Y=40
                // 40 + 160 = 200 (Safe)
                GLCD_Bitmap(70, 40, 180, 160, HAMZA_pixel_data);
                LED_On(1);
            }
            else if (current_img == 3) {
                // Header (Centered 20 chars: 1 space + 19 text)
                GLCD_DisplayString(0, 0, 1, " GALLERY: MUSIC NOTE");

                // Image: Centered X=70, Y=50
                // 50 + 135 = 185 (Safe)
                GLCD_Bitmap(70, 50, 180, 135, MUSIC_pixel_data);
                LED_On(2);
            }
        }
    }
}