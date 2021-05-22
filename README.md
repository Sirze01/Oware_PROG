    ######################################################################################################

     ---------------------------------  OWARE - A count and capture game  -------------------------------
 
    ######################################################################################################
    Author: José Costa T1_201907216 <up201907216@fe.up.pt>
    Game Developed for the 1st year Programming Course of the Master in Informatics and Computing Engineering (EI0012)
    (April 2020) 
   
   
 # Comentary
   
   This project was fun and a great way to get to know the basics and the in's and out's of the C++ programming language.
   In my particular case, I guess I could make an even better job if I learnt about structs and classes, as well as about
   header files and distributing the code across several files, making organization simpler.
   
   More features could be implemented if structs were used, given that passing so many arguments to the functions can be 
   confusing for everyone working or reading the code. I think that from now on, as documenting the code is as important as
   writing it, keeping its reading easy and it's use simple, I will be writing code with documentation in mind, maybe automatic.
   
   Despite all the negatives above, this was an amazing experience and I think that I made a fun and simple game.
   
   
   
 # Objectives
  
  ## Basic version
   The program must execute in console mode. You are free to choose the interface of the program. (Achieved) 
   
   The seeds in each hole can be indicated by numbers, instead of other symbols. (Achieved, using numbers) 
   
   Colored numbers may be used to distinguish the seeds of each player. (Not achieved, being a nice feature to add, more notable
   in the Windows terminal 'game developed in a Linux platform') 
   
   Display the board in its starting position, as well as during and after each move. (Achieved) 
   
   Allow each player, on his turn, to do his move, by collecting his seeds, sowing them and capturing the
   opponent seeds, if possible. (Achieved) 
   
   After each move, detect if the game ended and announce the winner or declare a draw. (Achieved) 
   
  ## Enhanced version
   If you feel that the basic version is too easy, you can implement an enhanced version that allows a player to play
   against the computer. It is suggested that you start by implementing a "random player version" that simply looks at
   the available choices and picks one of them, randomly; (Achieved, by tricking the player 2 name - Bad implementation) 
   
   
   
 # Development State
   
   The game is playable, does sow and capture moves, declares the end of the game in win/draw situations, outputs error messages 
   and handles bad inputs.
   The game probably will crah if the only possible move is a "Grand Slam", that is, removing all the opponents seeds.
   I could't make the game crash any other way than those mentioned under.
   
   
   Some known bugs are:
     - Flickering when clearing the console in Windows
     - Not being able to output special characters inputed to the program in the Windows console (Output works fine using UTF8
       encoding)
     - Ctrl + C works fine in Windows but Ctrl + D in Linux causes a "Segmentation fault (core dumped)" Exit using the game 
       option ('e' in any input prompt)
   
   

 # Screens
 
     ######################################################################################################
     
      ---------------------------------  OWARE - A count and capture game  -------------------------------
     
     ######################################################################################################
     
     Author: José Costa T1_201907216 <up201907216@fe.up.pt> 
     Game Developed for the 1st year Programming Course of the Master in Informatics and Computing Engineering (EI0012)
     (April 2020) 
     
     Press 'r' to see the rules of the game, 'g' to skip to the game (You can press 'e' to exit the game 
     at anytime): r
     
     
     ##############################################################################################
   
   ###  GENERAL
   
     The Oware game is an game from the Mancala family of board games with Ashanti origin in Ghana.

     The game requires 48 seeds and board like  this one:
   
   
     Player 2 points:
                   00
                             6      5      4      3      2      1  
                          ┌─────────────────────────────────────────┐
                          │  04  │  06  │  02  │  04  │  04  │  06  │
                          └─────────────────────────────────────────┘

                          ┌─────────────────────────────────────────┐
                          │  04  │  03  │  03  │  06  │  04  │  02  │
                          └─────────────────────────────────────────┘
                              1      2      3      4      5      6  
                                                                          Player 1 points:
                                                                                        00


     
     The game starts with 4 seed in each house. The goal of the game is to capture more seeds than your 
     opponent and, since there are 48 seeds, capturing 25 is enough. The game can end with a draw, since 
     there's a even number of seeds.

   ### Sowing
   
     Players take turns moving the seeds. On each turn, the player chooses one of the six houses on their
     side of the table, removing all the seeds in that house and distributing them for the next houses, 
     one seed per house, including the opponent's houses, in a counterclockwise way. You can't seed 
     either in the score houses or in the house you picked to remove the seeds.

   ### Capturing

     You can capture the seeds in a opponent's house when, the last sowed seed makes a house 2 or 3 
     seeds, and doesn't capture all of the opponent's seeds. In a turn you can capture seeds from more 
     than one house. The captured seeds are stored in the scoring houses.

     ###################################################################################
  

     Press 'g' to start a game, press 'b' to go back: 
     
     Press '1' to start a game against the computer, press '2' to play a 2 player game: 

     Input your name: Test
     
     
     

     Computer points:
                   00
                             6      5      4      3      2      1  
                          ┌─────────────────────────────────────────┐
                          │  04  │  04  │  04  │  04  │  04  │  04  │
                          └─────────────────────────────────────────┘

                          ┌─────────────────────────────────────────┐
                          │  04  │  04  │  04  │  04  │  04  │  04  │
                          └─────────────────────────────────────────┘
                              1      2      3      4      5      6  
                                                                         Test points:
                                                                                   00


     Test goes first.

     Test's turn!

     Input your house: 1
       
     
     

     Computer points:
                   00
                             6      5      4      3      2      1  
                          ┌─────────────────────────────────────────┐
                          │  04  │  04  │  04  │  04  │  04  │  04  │
                          └─────────────────────────────────────────┘

                          ┌─────────────────────────────────────────┐
                          │  04  │  05  │  05  │  05  │  05  │  04  │
                          └─────────────────────────────────────────┘
                              1      2      3      4      5      6  
                                                                         Test points:
                                                                                   00


     Test chose house 1.

     Computer's turn!

     Computer chose 2
     Press enter key to continue...

\

    Author: José Costa T1_201907216 <up201907216@fe.up.pt>
    Game Developed for the 1st year Programming Course of the Master in Informatics and Computing Engineering (EI0012) (April 2020)    
    ######################################################################################################
    
     ---------------------------------  OWARE - A count and capture game  -------------------------------
    
    ######################################################################################################  
