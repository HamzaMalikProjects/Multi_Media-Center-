#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

/* EXTERNAL LINKING: Link to the Reflex Test game logic */
extern void play_reflex_test(void); 

/*----------------------------------------------------------------------------
  Game 2 Menu UI - Matches "Multimedia Center" Navy Theme
 *----------------------------------------------------------------------------*/
 
 void game2_menu(){ 
    // 1. Set Global Background to Navy
    GLCD_SetBackColor(Navy);
    
    // 2. Header Bar (White Background, Navy Text)
    GLCD_SetBackColor(White);
    GLCD_SetTextColor(Navy);
    GLCD_DisplayString (0, 0, 1, "      GAME MENU     "); 
    
    // 3. Sub-header (Navy Background, Cyan Text)
    GLCD_SetBackColor(Navy);
    GLCD_SetTextColor(Cyan);
    GLCD_DisplayString (1, 0, 1, "     REFLEX TEST    ");
    
    // 4. Decorative Separator
    GLCD_SetTextColor(White);
    GLCD_DisplayString (2, 0, 1, "--------------------");

    // 5. Footer / Status Bar (LightGrey Background)
    GLCD_SetBackColor(LightGrey);
    GLCD_SetTextColor(Black);
    GLCD_DisplayString (8, 0, 1, "   Scroll to View   ");
    GLCD_DisplayString (9, 0, 1, "   Click to Select  "); 
 }
 
int start_game2 (void) 
{       /* Main Program                         */
      //selector to see which program is user the choosing
    
    int selector = 0;
    int selected = 0;
                      
    int joystick_val = 0;   //track the current joystick value
    int joystick_prev = 0;  //track the previous value for the joystick
    
    // Initialize with Navy Theme
    GLCD_Clear(Navy);
    game2_menu();
    
  while(1)        //loop forever
    {
            joystick_val = get_button();    
            
            if (joystick_val != joystick_prev)
            {
                    if (joystick_val == KBD_DOWN)
                    {
                        if (selector >= 2){
                                selector = 2;
                        }
                        else{
                                selector +=1;
                        }
                    }
                    else if (joystick_val == KBD_UP)
                    {
                        if (selector <= 1){
                                selector = 1;
                        }
                        else{
                                selector -=1;
                        }
                    }
                // Selection Logic
                else if(joystick_val == KBD_SELECT) 
                {
                        if (selector == 1)
                        {
                            play_reflex_test();
                            
                            // Ensure screen is clean and NAVY when returning
                            GLCD_Clear(Navy); 
                            game2_menu();

                        }
                        else if (selector == 2)
                        {
                            // Clear before returning to Main Menu
                            GLCD_Clear(Navy);
                            return(0);
                        }
                }
                joystick_prev = joystick_val;    
            }
            
            // VISUAL UPDATE LOGIC - "Button" Style
            if(selected == 0){
                if (selector == 1)
                {
                        // Redraw Menu base to keep clean
                        game2_menu(); 

                        // Selected: Start Game (Cyan Button)
                        GLCD_SetBackColor(Cyan);
                        GLCD_SetTextColor(Black);    
                        GLCD_DisplayString(5,0,1, "   [ Start Game ]   ");
                        
                        // Unselected: Return (Navy Background)
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(6,0,1, "     Return Home    ");
                        
                }
                else if(selector == 2)
                {
                        // Redraw Menu base
                        game2_menu();

                        // Unselected: Start Game
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(5,0,1, "     Start Game     ");
                        
                        // Selected: Return (Cyan Button)
                        GLCD_SetBackColor(Cyan);
                        GLCD_SetTextColor(Black);
                        GLCD_DisplayString(6,0,1, "   [ Return Home ]  ");

                }
                else
                {
                        // Default State
                        game2_menu();
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(5,0,1, "     Start Game     ");
                        GLCD_DisplayString(6,0,1, "     Return Home    ");
                }
            }
    }
}