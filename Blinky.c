#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

extern int audio_main (void);
extern int photo (void);
extern int start_game (void);
extern int start_game2 (void); 

/*----------------------------------------------------------------------------
  Main Menu UI - COE718 Multimedia Center (Navy Theme)
   By Hamza Malik 501112545
 *----------------------------------------------------------------------------*/
 
 void main_menu(){ 
    // 1. Set Global Background to Navy
    GLCD_SetBackColor(Navy);
    
    // 2. Header Bar
    GLCD_SetBackColor(White);
    GLCD_SetTextColor(Navy);
    // Centered based on 20 characters width
    GLCD_DisplayString (0, 0, 1, " COE718 Multimedia  "); 
    GLCD_DisplayString (1, 0, 1, "       Center       ");
    
    // 3. Name
    GLCD_SetBackColor(Navy);
    GLCD_SetTextColor(Cyan);
    GLCD_DisplayString (2, 0, 1, "    Hamza Malik     ");
    
    // 4. Separator
    GLCD_SetTextColor(White);
    GLCD_DisplayString (3, 0, 1, "--------------------");
    
    // 5. Footer
    GLCD_SetBackColor(LightGrey);
    GLCD_SetTextColor(Black);
    GLCD_DisplayString (8, 0, 1, "   Scroll to View   ");
    GLCD_DisplayString (9, 0, 1, "   Click to Start   "); 
 }
 
int main (void) 
{       
    int joystick_val = 0;   
    int joystick_prev = 0;  
    
    int selector = 0;
    int selected = 0;
    
    KBD_Init();
    LED_Init ();
    GLCD_Init();

    // Initialize with Navy Theme
    GLCD_Clear(Navy); 
    main_menu();
    
    SysTick_Config(SystemCoreClock/100); 

  while(1)        //loop forever
    {
            joystick_val = get_button();    
            
            if (joystick_val != joystick_prev)
            {
                    if (joystick_val == KBD_DOWN)
                    {
                        if (selector >= 4){
                                selector = 4;
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
                // "Just Click" logic (Select button)
                else if(joystick_val == KBD_SELECT) 
                {
                        if (selector == 1)
                        {
                            photo();    
                        }
                        else if (selector == 2)
                        {
                            audio_main();
                        }
                        else if (selector == 3)
                        {
                            start_game();   // Starts Game 1
                        }
                        else if (selector == 4)
                        {
                            start_game2();  // Starts Game 2
                        }
                }
                joystick_prev = joystick_val;    
            }
            
            /* REDRAWING LOGIC - CENTERED STRINGS */
            /* Assuming screen is ~20 chars wide */
            
            if(selected == 0){
                if (selector == 1)
                {
                        main_menu(); // Redraw header/footer
                        
                        // Selected Item
                        GLCD_SetBackColor(Cyan);
                        GLCD_SetTextColor(Black);
                        GLCD_DisplayString(4,0,1, " [ Photo Gallery ]  ");
                        
                        // Unselected Items
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(5,0,1, "    Audio Player    ");
                        GLCD_DisplayString(6,0,1, "       Game 1       ");
                        GLCD_DisplayString(7,0,1, "       Game 2       ");
                }
                else if(selector == 2)
                {
                        main_menu();
                        
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(4,0,1, "   Photo Gallery    ");
                        
                        // Selected Item
                        GLCD_SetBackColor(Cyan);
                        GLCD_SetTextColor(Black);
                        GLCD_DisplayString(5,0,1, "  [ Audio Player ]  ");
                        
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(6,0,1, "       Game 1       ");
                        GLCD_DisplayString(7,0,1, "       Game 2       ");
                }
                else if(selector == 3)
                {
                        main_menu();
                        
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(4,0,1, "   Photo Gallery    ");
                        GLCD_DisplayString(5,0,1, "    Audio Player    ");
                        
                        // Selected Item
                        GLCD_SetBackColor(Cyan);
                        GLCD_SetTextColor(Black);
                        GLCD_DisplayString(6,0,1, "     [ Game 1 ]     ");                  
                        
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(7,0,1, "       Game 2       ");
                }
                else if(selector == 4)
                {
                        main_menu();
                        
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(4,0,1, "   Photo Gallery    ");
                        GLCD_DisplayString(5,0,1, "    Audio Player    ");
                        GLCD_DisplayString(6,0,1, "       Game 1       ");
                        
                        // Selected Item
                        GLCD_SetBackColor(Cyan);
                        GLCD_SetTextColor(Black);
                        GLCD_DisplayString(7,0,1, "     [ Game 2 ]     ");                  
                }
                else
                {
                        // Default state
                        main_menu();
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(White);
                        GLCD_DisplayString(4,0,1, "   Photo Gallery    ");
                        GLCD_DisplayString(5,0,1, "    Audio Player    ");
                        GLCD_DisplayString(6,0,1, "       Game 1       ");
                        GLCD_DisplayString(7,0,1, "       Game 2       ");
                }
            }
    }
}