Machine oriented programming Project 2

# Yukon Solitaire in c #
Course: 02322 Machine oriented programming Spring 22

Contributors:
- Rasmus Prætorius s215777
- Andrew Shereef s173750
- Alban Dalifi s205416

## Requirement specifications ##

### Game rules ###
The game of Yukon Solitaire includes a deck split into 7 columns with rows of 1, 6, 7, 8, 9, 10 and 11 cards ordered from left to right with 21 of the cards hidden face down. The goal of the game is to move cards into the four foundations arranged by suit in order of value. The player is allowed to move cards from one column to another column as long as the top of the chosen cards is one value less than the bottom card of the column they are placing them onto. If there are no more visible cards in a column, the top hidden card becomes visible. The player wins when there are no cards left in the deck, and all cards have been placed in the foundations based on their suit.

### Displaying cards ###
The cards will be displayed in the terminal, with a horizontal array of card names, named C1-C7, representing each card column, and a vertical column of foundations named F1-F4. Each card column will be displayed chronologically in order, with varying array size, going from 1 for C1, 6 for C2,..., 11 for C7. This means that the first card array will contain 1 card, the second card array will contain 6 cards,...,the seventh card array will contain 11 cards. The cards can be displayed by using the SW command, which prints all the cards to the terminal (See SW description under Commands).

### Commands ###
Core commands:
- LD <filename>
The LD command should load a deck of cards from a file “filename” containing the card deck data.

- SW
The SW command shows/prints all the cards in the card deck to a terminal in the order of the deck.

- SI<split>
The SI command shuffles the cards in an interleaved manner by first splitting the deck into two piles depending on the presence and value of the optional split parameter, and then using the top cards of each pile to create a new shuffled pile.

- SR
The SR command shuffles the deck of cards randomly by iteratively taking the top of an unshuffled pile, and adding the card to a random position in a new shuffled pile.

- SD<filename>
The SD command saves the cards from the player’s current card deck to a file which is specified by a parameter. If the file is not specified it will be default named to “cards.txt”. The cards will be stored in the file a card for each line.

- QQ
The QQ command prompts the program to shut down.

- P
The P command starts up a game in the PLAY phase, using the current card deck at hand. All commands available in the STARTUP phase are excluded.

- Q
Quits the game and returns the player to the STARTUP phase. If a replay of the previous game is desired, one can simply use the command P after initiating the Q command, since the previous card deck still is stored in memory.

- Game Moves
There are two general moves in the game, <from> and <to>, where the format is typically <from> -> <to>. The <from> command moves a card, either from a column or from a foundation. The <to> command is the destination of the card. This can be either at a column or foundation.

Extentions:
- S <filename>
The extension command S allows the player to save the current state of a game with the name of the savefile specified by a <filename> parameter.

- L <filename>
The extension command L allows the player to load the game to a previous state using a savefile with name specified by the <filename> parameter.
