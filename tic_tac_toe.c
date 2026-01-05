#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
// #include "game.h" /* Include if you have a header, otherwise commented out */

/*----------------------------------------------------------------------------
  Tic Tac Toe - (P1=O, P2=X, Click-to-Exit)
  - Added Pre-Game Instructions
 *----------------------------------------------------------------------------*/
 
 void draw_board(){ 
    GLCD_SetBackColor(Navy);
    
    // Draw Player Names in White
    GLCD_SetTextColor(White);
    GLCD_DisplayString (0, 0, 1, "P1:");
    GLCD_DisplayString (0, 15, 1, "P2:");
    
    // Draw Grid Lines in Cyan
    GLCD_SetTextColor(Cyan);
    GLCD_DisplayString (0, 4, 1, "   |   |   ");
    GLCD_DisplayString (1, 4, 1, "           ");
    GLCD_DisplayString (2, 4, 1, "_ _|_ _|_ _");
    GLCD_DisplayString (3, 4, 1, "   |   |   ");
    GLCD_DisplayString (4, 4, 1, "           ");
    GLCD_DisplayString (5, 4, 1, "_ _|_ _|_ _");
    GLCD_DisplayString (6, 4, 1, "   |   |   ");
    GLCD_DisplayString (7, 4, 1, "           ");
    GLCD_DisplayString (8, 4, 1, "   |   |   ");
 }
 
 
     int c = 0;
     int moves = 0;
 
     void switch_turn(){
         moves += 1;
         if(c == 0)
         {
                 c++;
         }
         else{
                 c--;
         }
     }
 
    int x = 5;
    int y = 1;
    int placeholder[15][15] = {0};    
    
    int P1, P2;
    
    int max_y = 7;
    int max_x = 13;

    char s1[10];
    char s2[10];

int tic_tac_toe (void) 
{       /* Main Program                         */
    
    int joystick_val = 0;   //track the current joystick value
    int joystick_prev = 0;  //track the previous value for the joystick
    
    KBD_Init();
    LED_Init ();
    
    // --- 1. INSTRUCTIONS SCREEN (Professional Version) ---
    GLCD_Clear(Navy);
    GLCD_SetBackColor(Navy);
    
    // Title Header
    GLCD_SetTextColor(Yellow);
    // Centered Title (2 spaces left)
    GLCD_DisplayString(0, 0, 1, "  TIC TAC TOE PRO   ");

    // Section Header
    GLCD_SetTextColor(Cyan);
    // Centered Header (2 spaces left)
    GLCD_DisplayString(2, 0, 1, "  RULES & CONTROLS  ");
    
    // Separator Line
    GLCD_SetTextColor(White);
    GLCD_DisplayString(3, 0, 1, "--------------------");

    // Numbered Instructions List (Left Aligned)
    GLCD_DisplayString(4, 0, 1, " 1. Joystick to Move");
    GLCD_DisplayString(5, 0, 1, " 2. Click to Select ");
    GLCD_DisplayString(6, 0, 1, " 3. P1 (O) vs P2 (X)");
    GLCD_DisplayString(7, 0, 1, " 4. Match 3 to Win! ");

    // Footer Action
    GLCD_SetTextColor(Green);
    // Centered Footer (3 spaces left)
    GLCD_DisplayString(9, 0, 1, "   Click to Start   ");

    // Wait for click to start
    while(get_button() != KBD_SELECT);
    while(get_button() == KBD_SELECT);

    // --- 2. START GAME ---
    
    // Initialize Screen to Navy
    GLCD_Clear(Navy);
    draw_board();
    
    sprintf(s1, "%d", P1);
    sprintf(s2, "%d", P2);

    // Display Scores in White
    GLCD_SetBackColor(Navy);
    GLCD_SetTextColor(White);
    GLCD_DisplayString(0, 3, 1, (unsigned char *)s1);
    GLCD_DisplayString(0, 18, 1, (unsigned char *)s2);
    
    moves = 0;
    memset(placeholder, 0, sizeof(placeholder));
    
    SysTick_Config(SystemCoreClock/100); 

  while(1)        //loop forever
    {            
            joystick_val = get_button();    
            
            if (joystick_val != joystick_prev)
            {
                    // Ensure we are erasing with the Navy Background
                    GLCD_SetBackColor(Navy);

                    if (joystick_val == KBD_DOWN)
                    {
                        GLCD_DisplayString(y+1,x,1, " ");

                        if(y < max_y){
                            y += 3;
                        }
                    }
                    else if (joystick_val == KBD_UP)
                    {
                        GLCD_DisplayString(y+1,x,1, " ");

                        if(y > 1){
                            y -= 3;
                        }
                    }
                    else if(joystick_val == KBD_RIGHT)
                    {
                        GLCD_DisplayString(y+1,x,1, " ");

                        if(x < max_x){
                            x += 4;
                        }
                    }
                    else if(joystick_val == KBD_LEFT)
                    {
                        GLCD_DisplayString(y+1,x,1, " ");

                        if(x > 5){
                            x -= 4;
                        }
                    }
                    else if(joystick_val == KBD_SELECT)
                    {
                            GLCD_SetTextColor(White);
                            
                            // SWAPPED LOGIC:
                            // c==0 (Player 1) places 'O' (0x80)
                            // c==1 (Player 2) places 'X' (0x58)
                            
                            if(c == 0 && placeholder[y][x] != 2){
                                GLCD_DisplayChar(y, x, 1, 0x80); // 0x80 is Circle/O
                                placeholder[y][x] = 1;
                                switch_turn();
                            }
                            else if(c == 1 && placeholder[y][x] != 1){
                                GLCD_DisplayChar(y, x, 1, 0x58); // 0x58 is 'X'
                                placeholder[y][x] = 2;
                                switch_turn();
                            }
                            LED_On(moves-1);
                    }
                    
                    GLCD_SetTextColor(Yellow);
                    GLCD_DisplayChar(y+1, x, 1, 0x85);

                    // --- WIN CHECKING LOGIC ---
                    
                    // CHECK PLAYER 1 WIN
                    if((placeholder[1][5] == 1 && placeholder[1][9] == 1 && placeholder[1][13] == 1) ||
                    (placeholder[4][5] == 1 && placeholder[4][9] == 1 && placeholder[4][13] == 1) ||
                    (placeholder[7][5] == 1 && placeholder[7][9] == 1 && placeholder[7][13] == 1) ||
                    (placeholder[1][5] == 1 && placeholder[4][5] == 1 && placeholder[7][5] == 1) ||
                    (placeholder[1][9] == 1 && placeholder[4][9] == 1 && placeholder[7][9] == 1) ||
                    (placeholder[1][13] == 1 && placeholder[4][13] == 1 && placeholder[7][13] == 1) ||
                    (placeholder[1][5] == 1 && placeholder[4][9] == 1 && placeholder[7][13] == 1) ||
                    (placeholder[7][5] == 1 && placeholder[4][9] == 1 && placeholder[1][13] == 1)){
                        
                        P1 += 1;
                        GLCD_Clear(Navy);
                        LED_Out(0);
                        
                        // Result Screen
                        GLCD_SetBackColor(White); 
                        GLCD_SetTextColor(Navy);
                        GLCD_DisplayString (3, 0, 1, "   Player 1 Wins!!  ");
                        
                        // Instruction for User
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(LightGrey);
                        GLCD_DisplayString (8, 0, 1, "  Click to Continue ");
                        
                        // Wait for Release (Debounce)
                        while(get_button() == KBD_SELECT);
                        // Wait for New Click
                        while(get_button() != KBD_SELECT);
                        
                        return(0);
                    }        
                    
                    // CHECK PLAYER 2 WIN
                    if((placeholder[1][5] == 2 && placeholder[1][9] == 2 && placeholder[1][13] == 2) ||
                    (placeholder[4][5] == 2 && placeholder[4][9] == 2 && placeholder[4][13] == 2) ||
                    (placeholder[7][5] == 2 && placeholder[7][9] == 2 && placeholder[7][13] == 2) ||
                    (placeholder[1][5] == 2 && placeholder[4][5] == 2 && placeholder[7][5] == 2) ||
                    (placeholder[1][9] == 2 && placeholder[4][9] == 2 && placeholder[7][9] == 2) ||
                    (placeholder[1][13] == 2 && placeholder[4][13] == 2 && placeholder[7][13] == 2) ||
                    (placeholder[1][5] == 2 && placeholder[4][9] == 2 && placeholder[7][13] == 2) ||
                    (placeholder[7][5] == 2 && placeholder[4][9] == 2 && placeholder[1][13] == 2)){
                        
                        P2 += 1; 
                        GLCD_Clear(Navy);
                        LED_Out(0);
                        
                        GLCD_SetBackColor(White);
                        GLCD_SetTextColor(Navy);
                        GLCD_DisplayString (3, 0, 1, "   Player 2 Wins!!  ");
                        
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(LightGrey);
                        GLCD_DisplayString (8, 0, 1, "  Click to Continue ");
                        
                        // Wait for Release (Debounce)
                        while(get_button() == KBD_SELECT);
                        // Wait for New Click
                        while(get_button() != KBD_SELECT);
                        
                        return(0);
                    }
                    
                    // CHECK TIE
                    if (moves == 9){
                        GLCD_Clear(Navy);
                        
                        GLCD_SetBackColor(White);
                        GLCD_SetTextColor(Navy);
                        GLCD_DisplayString (3, 0, 1, "      Tie Game!!    ");
                        
                        GLCD_SetBackColor(Navy);
                        GLCD_SetTextColor(LightGrey);
                        GLCD_DisplayString (8, 0, 1, "  Click to Continue ");
                        
                        // Wait for Release (Debounce)
                        while(get_button() == KBD_SELECT);
                        // Wait for New Click
                        while(get_button() != KBD_SELECT);
                        
                        return(0);
                    }
                    
                    joystick_prev = joystick_val;
            }
    }
}