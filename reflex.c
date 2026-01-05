#include <LPC17xx.H>
#include "string.h"
#include <stdio.h>      /* REQUIRED for sprintf */
#include <stdlib.h>     /* REQUIRED for rand() */
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

/*----------------------------------------------------------------------------
  Game 2: REFLEX HUNTER (Normal Difficulty)
  - Tuned for Joystick physical travel time
  - Forgiving timing windows
  - PERFECTLY CENTERED UI (20 char width)
  - Added Ranking Guide Screen
 *----------------------------------------------------------------------------*/

// Joystick Direction Definitions
#ifndef KBD_UP
  #define KBD_SELECT  0x01
  #define KBD_DOWN    0x02
  #define KBD_LEFT    0x04
  #define KBD_RIGHT   0x08
  #define KBD_UP      0x10
#endif

void play_reflex_test(void) {
    int round = 1;
    int total_score = 0;
    int timer = 0;
    int delay_time = 0;
    int target_dir = 0; // 0=Up, 1=Down, 2=Left, 3=Right
    int input = 0;
    int i = 0;
    char buffer[40]; 
    int round_result = 0; // Stores points won this round

    // --- 1. SCORING RULES SCREEN ---
    GLCD_Clear(Navy);
    GLCD_SetBackColor(Navy);
    GLCD_SetTextColor(Yellow);
    // Centered: 20 chars
    GLCD_DisplayString(1, 0, 1, "   REFLEX HUNTER    ");
    
    GLCD_SetTextColor(White);
    // Aligning the list for visual neatness starting at Col 2
    GLCD_DisplayString(3, 2, 1, "PERFECT: +5 pts   ");
    GLCD_DisplayString(4, 2, 1, "FAST:    +3 pts   ");
    GLCD_DisplayString(5, 2, 1, "SLOW:    +1 pt    ");
    GLCD_SetTextColor(Red);
    GLCD_DisplayString(6, 2, 1, "MISTAKE: -1 pt    ");
    
    GLCD_SetTextColor(Green);
    // Centered: 20 chars
    GLCD_DisplayString(8, 0, 1, "   Click for Info   ");

    while(get_button() != KBD_SELECT); 
    while(get_button() == KBD_SELECT);

    // --- 1.5. RANKING REQUIREMENTS SCREEN ---
    GLCD_Clear(Navy);
    GLCD_SetBackColor(Navy);
    
    GLCD_SetTextColor(Cyan);
    // "RANKING GUIDE" is 13 chars. (20-13)/2 = 3.5 -> 3
    GLCD_DisplayString(0, 3, 1, "RANKING GUIDE");

    GLCD_SetTextColor(White);
    // Col 2 alignment
    GLCD_DisplayString(2, 2, 1, "S (GOD):  20+ pts ");
    GLCD_DisplayString(3, 2, 1, "A (PRO):  15+ pts ");
    GLCD_DisplayString(4, 2, 1, "B (GOOD): 10+ pts ");
    GLCD_DisplayString(5, 2, 1, "C (OKAY):  5+ pts ");
    
    GLCD_SetTextColor(Red);
    GLCD_DisplayString(6, 2, 1, "F (FAIL): <5 pts  ");

    GLCD_SetTextColor(Green);
    GLCD_DisplayString(9, 3, 1, "Click to Start");

    while(get_button() != KBD_SELECT); 
    while(get_button() == KBD_SELECT);


    // --- 2. GAME LOOP (5 Rounds) ---
    for(round = 1; round <= 5; round++) {
        round_result = 0;
        
        // Setup UI
        GLCD_Clear(Black);
        GLCD_SetBackColor(Black);
        
        // Show Current Score
        GLCD_SetTextColor(White);
        // "Rnd 1 | Score: 0" is 16 chars. (20-16)/2 = 2.
        sprintf(buffer, " Rnd %d | Score: %d ", round, total_score);
        GLCD_DisplayString(0, 0, 1, (unsigned char*)buffer);
        
        // "READY..." is 8 chars. (20-8)/2 = 6.
        GLCD_DisplayString(4, 6, 1, "READY...");
        
        // Random Wait (1s to 3s)
        delay_time = (rand() % 3000000) + 1000000;
        
        // --- WAIT PHASE (Check for Cheating) ---
        for(i = 0; i < delay_time; i++) {
            if(get_button() != 0) { 
                round_result = -1; // Penalty
                
                GLCD_SetBackColor(Red);
                GLCD_SetTextColor(White);
                GLCD_Clear(Red);
                
                // "TOO EARLY!" is 10 chars. (20-10)/2 = 5.
                GLCD_DisplayString(4, 5, 1, "TOO EARLY!");
                // "-1 POINT" is 8 chars. (20-8)/2 = 6.
                GLCD_DisplayString(5, 6, 1, "-1 POINT");
                goto END_ROUND; // Skip to score calculation
            }
        }

        // --- ACTION PHASE ---
        target_dir = rand() % 4; // 0 to 3
        
        GLCD_Clear(White);
        GLCD_SetBackColor(White);
        GLCD_SetTextColor(Blue); 

        // Draw BIG Directions
        if(target_dir == 0) {
            // "UP" is 2 chars. (20-2)/2 = 9.
            GLCD_DisplayString(4, 9, 1, "UP");
        }
        else if(target_dir == 1) {
            // "DOWN" is 4 chars. (20-4)/2 = 8.
            GLCD_DisplayString(4, 8, 1, "DOWN");
        }
        else if(target_dir == 2) {
             // "LEFT" is 4 chars. (20-4)/2 = 8.
            GLCD_DisplayString(4, 8, 1, "LEFT");
        }
        else if(target_dir == 3) {
            // "RIGHT" is 5 chars. (20-5)/2 = 7.
            GLCD_DisplayString(4, 7, 1, "RIGHT");
        }

        // --- TIMER ---
        timer = 0;
        while(1) {
            input = get_button();
            timer++;
            
            // Timeout (Too Slow) -> -1 Point
            if(timer > 2000000) {
                round_result = -1;
                GLCD_SetBackColor(Red);
                GLCD_SetTextColor(White);
                // "TOO SLOW" is 8 chars. (20-8)/2 = 6.
                GLCD_DisplayString(6, 6, 1, "TOO SLOW");
                break;
            }

            if(input != 0) {
                // Check if Correct Button
                int success = 0;
                if (target_dir == 0 && input == KBD_UP) success = 1;
                else if (target_dir == 1 && input == KBD_DOWN) success = 1;
                else if (target_dir == 2 && input == KBD_LEFT) success = 1;
                else if (target_dir == 3 && input == KBD_RIGHT) success = 1;
                
                if (success) {
                    // Calculate Score based on reaction speed
                    
                    // LEVEL 1: GOD (Fastest)
                    if(timer < 300000) {
                        round_result = 5; 
                        GLCD_SetBackColor(Green);
                        GLCD_SetTextColor(Black);
                        // "PERFECT!" is 8 chars. Col 6.
                        GLCD_DisplayString(2, 6, 1, "PERFECT!");
                        // "+5 PTS!!" is 8 chars. Col 6.
                        GLCD_DisplayString(3, 6, 1, "+5 PTS!!");
                    }
                    // LEVEL 2: FAST
                    else if(timer < 600000) {
                        round_result = 3; 
                        GLCD_SetBackColor(Cyan);
                        GLCD_SetTextColor(Black);
                        // "GOOD!" is 5 chars. Col 7.
                        GLCD_DisplayString(2, 7, 1, "GOOD!");
                        // "+3 PTS" is 6 chars. Col 7.
                        GLCD_DisplayString(3, 7, 1, "+3 PTS");
                    }
                    // LEVEL 3: OKAY
                    else {
                        round_result = 1; 
                        GLCD_SetBackColor(Yellow);
                        GLCD_SetTextColor(Black);
                        // "OKAY" is 4 chars. Col 8.
                        GLCD_DisplayString(2, 8, 1, "OKAY");
                        // "+1 PT" is 5 chars. Col 7.
                        GLCD_DisplayString(3, 7, 1, "+1 PT");
                    }
                }
                else {
                    // Wrong Button
                    round_result = -1;
                    GLCD_SetBackColor(Red);
                    GLCD_SetTextColor(White);
                    // "WRONG KEY" is 9 chars. Col 5.
                    GLCD_DisplayString(6, 5, 1, "WRONG KEY");
                    // "-1 PT" is 5 chars. Col 7.
                    GLCD_DisplayString(7, 7, 1, "-1 PT");
                }
                break; // Exit timer loop
            }
        }

        END_ROUND:
        total_score += round_result;
        
        // Show result for a moment
        for(i=0; i<8000000; i++); 
    }

    // --- 3. FINAL RESULTS SCREEN ---
    GLCD_Clear(Navy);
    GLCD_SetBackColor(Navy);
    
    GLCD_SetTextColor(Yellow);
    // "FINAL RESULTS" is 13 chars. (20-13)/2 = 3.5 -> 3.
    GLCD_DisplayString(1, 3, 1, "FINAL RESULTS");
    
    GLCD_SetTextColor(White);
    // "Final Score: XX" is approx 15 chars. (20-15)/2 = 2.
    sprintf(buffer, "Final Score: %d", total_score);
    GLCD_DisplayString(4, 2, 1, (unsigned char*)buffer);

    // RANKING SYSTEM
    GLCD_SetTextColor(Cyan);
    // Ranks are ~13-14 chars long. Centered at Col 3.
    if(total_score >= 20)      GLCD_DisplayString(6, 3, 1, "RANK: S (GOD)");
    else if(total_score >= 15) GLCD_DisplayString(6, 3, 1, "RANK: A (PRO)");
    else if(total_score >= 10) GLCD_DisplayString(6, 3, 1, "RANK: B (GOOD)");
    else if(total_score >= 5)  GLCD_DisplayString(6, 3, 1, "RANK: C (OKAY)");
    else                       GLCD_DisplayString(6, 3, 1, "RANK: F (FAIL)");

    GLCD_SetTextColor(Green);
    // "Click to Exit" is 13 chars. (20-13)/2 = 3.
    GLCD_DisplayString(9, 3, 1, "Click to Exit");

    // Wait for click to exit
    while(get_button() == KBD_SELECT); 
    while(get_button() != KBD_SELECT); 
}