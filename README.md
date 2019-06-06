# CS2_Final_Project
Final Project for CS002 Jamal Ashraf

Connect 4 with an AI

<h2>  
  How to Play
</h2>

Connect 4 is a strategy game where two players must compete to match 4 chips in a row, either horizontally, vertically, or      diagonally.
The first to do so wins the game and sends the other player to the shadow realm for enternity. 

<h2>  
  FAQ
</h2>

<b> 1.	How does the scoring system work? </b>
The scoring system works by scoring each individual column and selecting the largest score. That score corresponds to the column and the AI will choose that column. 
<b> 2.	How did you check the board to see if there was a win? </b>
I checked horizontals by counting the chips horizontally and resetting the count when there is an empty space or opponent chip in the cell.
<b> 3.	How does the clrscr function work? </b>
It clears the console using the window’s api header.
<b> 4.	Why did you not do a GUI? </b>
I did not plan to do a GUI nor did I plan to take an object oriented approach to this project. Transferring everything would take time that I do not have as of now. 
<b> 5.	How smart is the AI? </b>
The AI can only see the present, or the board at its current state. Therefore, it cannot see into the future and a tactical plan may catch at AI off guard.
<b> 6.	Is this anyway of improving the AI? </b>
An algorithm called Minimax can be implemented to allow the AI to see up to n times into the future. This allows the AI to determine the best possible move making the AI unbeatable. The details of the minimax algorithm can be found on the Wikipedia page, but the main point is it is a search tree and the root node (first node) will be the maximizing player (BOT) and will try to get the highest score from its children. It uses recursion to go n times deep into the search tree. The larger the n the better the AI because n is how many times it will see all the board possibilities and all the choices the opponent could make. But since it is recursing so many times the AI’s time complexity will be increased. This is when alpha beta pruning can be added to decrease the amount of time it takes to run. 
<b> 7.	Why are you using cin.clear and cin.ignore after your cin? </b>
This was added so if the user enters a character or string the program will not infinitely loop. It clears the error flags and ignores what is in the buffer allowing the user to enter another input without the program exploding. 
<b> 8.	How does the center column score work? </b>
The center column scoring works by favoring the center by multiplying the score by a value which can be changed by the programmer. Since the center column is the most advantageous column the AI will favor it because it can create many possible wins through connecting a diagonal, vertical, or horizontal connect 4. 
<b> 9.	Why is your AI using columns 1 to 7? Why is it not 0-6 since arrays start at 0? </b>
My DropChip function subtracts 1 from the column so It can be reused for other things. The AI calls this function therefore it must be from 1 to 7 otherwise there will be a bug. 
<b> 10.	Why is best score initialized to -1000? Why is it a large negative number? </b>
Best score is initialized to -1000 because when it scores the window if the opponent is about to win it subtracts X value from the score (which results in a negative) and if the best score is not a large negative number there could be an error. For example, if best score were to be 0 it would be larger than the negative score even though the negative score should be favored as it is the largest score among the 7 columns. 
<b> 11.	Why are you subtracting the score when the opponent has 3 and 1 empty space? Why not add a positive score? </b>
This is because it will subtract X value from the score and wherever the opponent is about to win that will be the largest number while all the other column will be negative values. Therefore, it will choose that column to drop the chip in. 
<b> 12.	Why did you create a window? What is the window? Why are you scoring the window instead of the entire board? </b>
I put the chips into a window to have an easier time scoring them rather than looking at the entire board. It is easy to keep track of and less confusing. 
<b> 13.	Why are you creating a copy of your board? </b>
This will allow the AI to drop their chip into all the spots and determine the best score and best col. 
<b> 14.	What was the most difficult part of this project? </b>
I was encountering many bugs with the AI and counting the board, specifically diagonals as they are harder to input into code. 
<b> 15.	What bugs did you encounter? </b>
One major bug that took many days of thinking of a solution was why sometimes the best score would be in a column that is full, therefore creating an infinite loop because the AI keep attempting to put their piece in that column and the program returning that the column is full but the AI still continues to put the chip in there. 
