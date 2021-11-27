# BRIEF EXPLAINATION
# "import time / random" is used to calculate time and random
# time.sleep() is a duration of shell sleep until it moves on to the next code
# String / value in variable can be added, removed or changes to your desire
# var.upper() variable used to capitalise the string
# Array is used to pick random element by using random.shuffle()
# Custom ScrClr variable is used to clear screen, which is neither effecient nor effective, but it's a work around
# Function is used to draw display and graphic
# There may be hidden error we haven't found yet
# Debug was used to understand and finding unwanted behavior of the scoring system
# use debugMode input to enable / disable debug mode
#
# THE GAME ITSELF
# The game will pick any word from wordRandom array
# The game will not count the same guesses until new guess is given
# The game supports word with up to 14 letters
# Score will be counted throughout the game, a lose means totalScore reset
# Highest score will be recorded throughout the game as long as you don't quit
# 
# CHANGES SINCE V5
# + Added scoreModifier for each gameDecider
# + Added time taken per round
# > Changed ways to make code readable by humans
# > Utilising array instead of string
# > Cleaned up redundant / repeating code

import time
import random

debugMode = 1
debugModeModifier = 1
if(debugMode == 1): # Only from here you get to bypass intro and game delay
    debugModeModifier = 0

###     VARIABLE     ###

groupName = "Moshi Moshi"
groupMemberLeader = "CLASSIFIED"
groupMember1 = "CLASSIFIED"
groupMember2 = "CLASSIFIED"
groupMember3 = "CLASSIFIED"
groupMember4 = "CLASSIFIED"

# Modifier for certain variable
introDurationModifier = 2 * debugModeModifier # Group Intro duration
gameDelayModifier = 1 * debugModeModifier # Pause delay per each game

# Score modifier
scoreModifier = 1 # To increase or decrease score value, change these value.
scoreModifierWinFlawless = 20 * 5
scoreModifierWin1 = 20 * 4
scoreModifierWin2 = 20 * 3
scoreModifierWin3 = 20 * 2
scoreModifierWin4 = 15
scoreModifierWin5 = 10
scoreModifierLose = 5
scoreModifierSurrender = 1

# You can add, remove or change the word here. The word can support up to 14 letters.
wordRandom = ["ARTIST", "BREEZE", "CIRCLE", "DECENT", "ENROLL", "FILTHY", "GROWTH", "HONEST", "INVEST", "KERNEL", "LETTER", "NARROW", "METEOR", "POLICY", "PURSUE", "ROSTER", "RUNWAY", "SCHEME", "RIPPLE", "TODDLE", "WOBBLY", "ZEROES"]

# Some main text
gameName = "   The Game of Hangman" # If this is changed, fix the alignment at the menuMain, hangmanFigure and endScreen.
textGameName = "           The Game\n          of Hangman"
textGameNameLnSkip = 4
textGuess = "Guess the letter of the word #"
textContinueConfirm = "Do you want to retry?\n[Y]es / [N]o"
textExitConfirm = "Are you sure?\n[Y]es / [N]o"
textPrepare = "          Get ready!"
textPrepareLnSkip = 5

# This is line bar, any modification or changes may impact display.
lineBarTopGN = "   " + str(gameName)
lineBarTopT = ["=== " * 8, "=== " * 8, "/O0o=-=-=-=-=-=-=-=-=-=-=-=o0O\\", "/=============================\\", "=" * 32]
lineBarTopB = ["=== " * 8, "=== " * 8, "\\O0o=-=-=-=-=-=-=-=-=-=-=-=o0O/", "\\=============================/", "=" * 32]
lineBarBottomT = ["=== " * 8, "===|===|===|===|===|===|===|===", "=" * 32, "=" * 32, "=" * 32]
lineBarBottomB = ["=== " * 8, "===|===|===|===|===|===|===|===", "=" * 32, "=" * 32, "=" * 32]

# This is sentence in the bar when game decided, use these bar as reference.
#  ("        F L A W L E S S")
#  ("=== === === === === === === ===")
sentenceWinFlawless = ["      Flawless Guessing!!", "        F L A W L E S S", "        Super Guess!"]
sentenceWin1 = ["        Nearly Perfect!", "         Hanging Head!"]
sentenceWin2 = ["          Well Played", "      Tis' but a scratch!"]
sentenceWin3 = ["          Nicely Done", "           Good Call"]
sentenceWin4 = ["      Close but not quite", "          Tough Luck!"]
sentenceWin5 = ["          Close Call", "   I was this close to death"]
sentenceLose = ["       H A N G E D M A N", "        D E A D   B O Y"]
sentenceSurrender = ["      W H I T E   F L A G", "       S U R R E N D E R", "         Q U I T T E R"]
sentenceTextWin = ["Keep it going!", "Nice la", "Good guessing", "Keep it up!", "Guessing mastery"]
sentenceTextLose = ["You we're hanged", "Good try...", "Don't get hanged up", "Keep trying!"]
sentenceTextContinue = ["       One more time!", "     Let's do it again!", "        Let's do this!"]
sentenceTextQuit = ["Well participated.", "Maybe next time...", "We'll do it again later!"]
sentenceTextSurrender = ["Accepting fate and death, eh?", "Going so soon?", "We're not done yet!"]
sentenceTextExit = ["  Thanks for playing!", " We'll play again next time!", "     Goodbye!"]

# Screen Clear Variable; just change the multiplication amount.
ScrClr = "\n" * 64

### END OF VARIABLE ###

### DO NOT MODIFY THESE ###
lineBarIndex = list(zip(lineBarTopT, lineBarTopB, lineBarBottomT, lineBarBottomB))
gameCore = 1
gameExit = 0
gameDecider = 0
hasPlayed = 0
keyMainMenu = 0
score = 0
scoreTotal = 0
scoreTop = 0
scoreLast = 0
streakModifier = 1
streakWon = 0
streakTop = 0
timeRoundStart = 0
timeRoundEnd = 0
timeRoundTaken = 0
timeRoundShortest = 0
random.shuffle(sentenceTextExit)
textExit = sentenceTextExit[0]
### ### ### ### ### ### ###

# Display debug function
def debug():
    print("===== DEBUG ===== ===== =====")
    print("Time Taken : %.2f" % (time.time() - timeRoundStart) + "s")
    print("Correct guess(es) :", guessCorrect)
    print("Incorrect guess(es) :", guessIncorrect)
    print("Guess(es) count :", guessCount + 1)
    print("Last Score :", scoreLast)
    print("Total score :", scoreTotal)
    print("Top score :", scoreTop)
    print("Current Streak :", streakWon)
    print("Highest Streak :", streakTop)
    print("Streak Modifier :", streakModifier)
    print("Correct answer :",''.join(answerCorrect))
    print("===== " * 5, "\n")

# Display main menu function
def menuMainDisplay():
    print("       ", groupName)
    print("                            +---+")
    print("=== === === === === === === |   o")
    print(" " + gameName + "     |  /|\\")
    print("=== === === === === === === |  / \\")
    print("                           /|\_______")
    if(hasPlayed == 1): # If the player has played before, this display will start to show in menu screen
        print(" Highest Score :", scoreTop)
        print("   Longest Streak :", streakTop)
        print("  Last Highscore :", scoreTotal)
        print("    Last Longstreak :", streakWon, "\n")
    print(" [E]nter the game!")
    print("   [Q]uit the game?")

# Display graphical ASCII of hangman
def displayHangman():
    if guessIncorrect == 0:
        print(lineBarTopT)
        print(lineBarTopGN)
        print(lineBarTopB)
        print(" +----+")
        print(" |    |")
        print(" |")
        print(" |")
        print(" |")
        print(" |")
        print(" |")
        print(" |")
        print("/|\\ ",' '.join(displayCorrect))
        print(lineBarBottomT)
    elif guessIncorrect == 1:
        print(lineBarTopT)
        print(lineBarTopGN)
        print(lineBarTopB)
        print(" +----+")
        print(" |    |")
        print(" |   ( )")
        print(" |")
        print(" |")
        print(" |")
        print(" |")
        print(" |")
        print("/|\\  ",' '.join(displayCorrect))
        print(lineBarBottomT)
    elif guessIncorrect == 2:
        print(lineBarTopT)
        print(lineBarTopGN)
        print(lineBarTopB)
        print(" +----+")
        print(" |    |")
        print(" |   ( )")
        print(" |    |")
        print(" |    |")
        print(" |")
        print(" |")
        print(" |")
        print("/|\\  ",' '.join(displayCorrect))
        print(lineBarBottomT)
    elif guessIncorrect == 3:
        print(lineBarTopT)
        print(lineBarTopGN)
        print(lineBarTopB)
        print(" +----+")
        print(" |    |")
        print(" |   ( )")
        print(" |   /|")
        print(" |  / |")
        print(" |")
        print(" |")
        print(" |")
        print("/|\\  ",' '.join(displayCorrect))
        print(lineBarBottomT)
    elif guessIncorrect == 4:
        print(lineBarTopT)
        print(lineBarTopGN)
        print(lineBarTopB)
        print(" +----+")
        print(" |    |")
        print(" |   ( )")
        print(" |   /|\\")
        print(" |  / | \\")
        print(" |")
        print(" |")
        print(" |")
        print("/|\\  ",' '.join(displayCorrect))
        print(lineBarBottomT)
    elif guessIncorrect == 5:
        print(lineBarTopT)
        print(lineBarTopGN)
        print(lineBarTopB)
        print(" +----+")
        print(" |    |")
        print(" |   ( )")
        print(" |   /|\\")
        print(" |  / | \\")
        print(" |   /")
        print(" |  /")
        print(" |")
        print("/|\\ ",' '.join(displayCorrect))
        print(lineBarBottomT)
    elif guessIncorrect >= 6:
        print(lineBarTopT)
        print(lineBarTopGN)
        print(lineBarTopB)
        print(" +----+")
        print(" |    |")
        print(" |   ( )")
        print(" |   /|\\")
        print(" |  / | \\")
        print(" |   / \\")
        print(" |  /   \\")
        print(" |")
        print("/|\\  ",' '.join(answerCorrect))
        print(lineBarBottomT)

# Self-explanatory
def displayScore():
    print("Time Taken : %.2f" % timeRoundTaken + "s")
    print("Score :", score)
    print("Total Score :", scoreTotal)
    print("Highest Score :", scoreTop)
    print("Current Streak :", streakWon)
    print("Top Streak :", streakTop)

### Group Intro ###
print("Preparing. . .")
time.sleep(introDurationModifier)
print(ScrClr)
print("=== " * 8)
print("PSP0101 Project Hangman :")
print("=== " * 8)
print(groupName + " present:")
time.sleep(introDurationModifier * 0.5)
print(gameName)
time.sleep(introDurationModifier * 1.5)
print("\nGroup member:")
time.sleep(introDurationModifier * 0.5)
print("1. " + groupMemberLeader)
print("2. " + groupMember1)
print("3. " + groupMember2)
print("4. " + groupMember3)
print("5. " + groupMember4)
time.sleep(introDurationModifier * 3)
print(ScrClr)
### End Group Intro ###
  
while(gameCore == 1):
    # Resets the quitGame and endGame variable
    keyMainMenu = ""
    exitConfirm = ""
    endConfirm = ""
    gameEnd = 0
    gameExit = 0
    
    ### Menu Screen ###
    menuMainDisplay() # Display menu screen using function
    while(not(keyMainMenu == "Q" or keyMainMenu == "E")): # Any word start with Q or E will trigger the variable.
        keyMainMenu = input() # Waiting for player to give input
        if(keyMainMenu == "debugMode"): # Special input key to enable debug mode
            if(debugMode == 0):
                debugMode = 1
                print("Debug Mode [ON]")
            else:
                debugMode = 0
                print("Debug Mode [OFF]")
        if(keyMainMenu == "[E]nter the game!"): # Special hidden input that basically does the same thing as supposed input
            keyMainMenu = "E"
        elif(keyMainMenu == "[Q]uit the game?"):
            keyMainMenu = "Q"
        keyMainMenu = list(keyMainMenu)
        try:
            keyMainMenu = keyMainMenu[0] # This variable search for the first array, meaning it will find the first character in the input.
        except IndexError: # When blank is entered, it causes error. These exception triggers the variable after it
            keyMainMenu = "E"
        keyMainMenu = keyMainMenu.upper()
    if(keyMainMenu == "Q"):
        gameExit = 1
    ### End Menu Screen ###

    # Test for gameExit or end while variable
    if(gameExit == 0):
        # Resets the scoring
        score = 0
        scoreTotal = 0
        streakWon = 0
        streakModifier = 1
        print(ScrClr)
        time.sleep(gameDelayModifier * 0.25)
        print(textGameName + "\n" * textGameNameLnSkip)
        time.sleep(gameDelayModifier * 1)
        while(gameEnd == 0): # Check if the game has ended or not
            endConfirm = ""
            print(ScrClr)
            time.sleep(gameDelayModifier * 0.25)
            print(textPrepare + "\n" * textPrepareLnSkip)
            time.sleep(gameDelayModifier * 1)
            print(ScrClr)

            # These shuffle the lines, bars and words for every match restart.
            random.shuffle(lineBarIndex)
            lineBarTopT, lineBarTopB, lineBarBottomT, lineBarBottomB = zip(*lineBarIndex)
            lineBarTopT = lineBarTopT[0]
            lineBarTopB = lineBarTopB[0]
            lineBarBottomT = lineBarBottomT[0]
            lineBarBottomB = lineBarBottomB[0]
            random.shuffle(sentenceWinFlawless)
            lineBarBottomWinFlawless = sentenceWinFlawless[0]
            random.shuffle(sentenceWin1)
            lineBarBottomWin1 = sentenceWin1[0]
            random.shuffle(sentenceWin2)
            lineBarBottomWin2 = sentenceWin2[0]
            random.shuffle(sentenceWin3)
            lineBarBottomWin3 = sentenceWin3[0]
            random.shuffle(sentenceWin4)
            lineBarBottomWin4 = sentenceWin4[0]
            random.shuffle(sentenceWin5)
            lineBarBottomWin5 = sentenceWin5[0]
            random.shuffle(sentenceLose)
            lineBarBottomLose = sentenceLose[0]
            random.shuffle(sentenceTextWin)
            textWin = sentenceTextWin[0]
            random.shuffle(sentenceTextLose)
            textLose = sentenceTextLose[0]
            random.shuffle(sentenceTextContinue)
            textContinue = sentenceTextContinue[0]
            random.shuffle(sentenceSurrender)
            lineBarBottomSurrender = sentenceSurrender[0]
            random.shuffle(sentenceTextQuit)
            textQuit = sentenceTextQuit[0]
            random.shuffle(sentenceTextSurrender)
            textSurrender = sentenceTextSurrender[0]
            random.shuffle(wordRandom)
            answerCorrect = list(wordRandom[0])

            # Resets the variable
            gameDecider = 0 # Resets game decider
            guessCount = 0
            guessCorrect = 0
            guessIncorrect = 0
            letterIncorrect = []
            displayCorrect = []
            displayCorrect.extend(answerCorrect)

            # Shows the blank of each letter in a word.
            for i in range(len(displayCorrect)):
                displayCorrect[i] = "_"
            
            timeRoundStart = time.time()
            
            # Loop the Hangman game
            while True:
                if(debugMode == 1): # Check if debug is enabled
                    debug()
                print("Incorrect letter :", ' '.join(letterIncorrect))
                displayHangman()
                if(guessCorrect == len(answerCorrect) or gameDecider == 1):
                    gameDecider = 1
                    break # Break to skip out everything here
                if(guessIncorrect > 5):
                    gameDecider = 2
                    break
                print(textGuess + str(guessCount+1) + " : ", end="")
                guess = input()
                if(guess == "debugMode"): # Enable / disable debug mode in-game
                    if(debugMode == 0):
                        debugMode = 1
                        print("Debug Mode [ON]")
                    else:
                        debugMode = 0
                        print("Debug Mode [OFF]")
                    time.sleep(0.5)
                    guess = ""
                guess = guess.upper()
                if(guess in wordRandom): # Check if the word is in secret word, if true instantly end game
                    if(guess == wordRandom[0]): # Check if the word is the right secret word answer
                        gameDecider = 1
                        displayCorrect = answerCorrect[:]
                        guessCorrect = len(answerCorrect)
                        guess = "" # Turns input variable into nothing to skip out the checking process
                    else: # When the secret word is in the secret word list but not the right answer
                        guessIncorrect += 2
                        guessCount += 1 
                        guess = ""
                elif(guess == "QUIT" or guess == "EXIT" or guess == "SURRENDER"): # Special string if player wants to quit mid-game
                    guessIncorrect = 6
                    displayHangman()
                    gameDecider = 3
                    break
                guess = list(guess)
                try: # In case of more than 1 letter string, it will only take the beginning.
                    guess = guess[0]
                except IndexError:
                    guess = ""
                if(guess in answerCorrect):
                    if(guess not in displayCorrect[:]):
                        guessCount += 1
                for i in range(len(answerCorrect)):
                    if(answerCorrect[i] == guess):
                        if(guess in displayCorrect[i]):
                            guessCorrect -= 1
                        displayCorrect[i] = guess
                        guessCorrect += 1
                if(guess not in answerCorrect):
                    if(not guess == ""):
                        if(guess not in letterIncorrect[:]):
                            letterIncorrect.append(guess)
                            guessIncorrect += 1
                            guessCount += 1
                print(ScrClr)

            timeRoundTaken = time.time() - timeRoundStart

            # When the game is won
            if(gameDecider == 1):
                if(guessIncorrect == 0): # Calculates the score and turns them into integer
                    print(lineBarBottomWinFlawless)
                    score = int(guessCorrect * scoreModifierWinFlawless * scoreModifier * streakModifier)
                elif(guessIncorrect == 1):
                    print(lineBarBottomWin1)
                    score = int(guessCorrect * scoreModifierWin1 * scoreModifier * streakModifier)
                elif(guessIncorrect == 2):
                    print(lineBarBottomWin2)
                    score = int(guessCorrect * scoreModifierWin2 * scoreModifier * streakModifier)
                elif(guessIncorrect == 3):
                    print(lineBarBottomWin3)
                    score = int(guessCorrect * scoreModifierWin3 * scoreModifier * streakModifier)
                elif(guessIncorrect == 4):
                    print(lineBarBottomWin4)
                    score = int(guessCorrect * scoreModifierWin4 * scoreModifier * streakModifier)
                elif(guessIncorrect == 5):
                    print(lineBarBottomWin5)
                    score = int(guessCorrect * scoreModifierWin5 * scoreModifier * streakModifier)
                scoreTotal = int(scoreTotal + score)
                if(scoreTotal > scoreTop): # If player reach highest score, it will be on top score
                    scoreTop = scoreTotal
                scoreLast = score # For debugging purposes
                streakModifier = streakModifier + 0.02 * streakWon
                streakWon += 1
                if(streakWon > streakTop): # If player reach longest streak, it will be on top streak
                    streakTop = streakWon
                print(lineBarBottomB)
                displayScore() # Display score using function
                print("")
                print(textWin)
                hasPlayed = 1 # Automatically signs that player has played
                print(textContinueConfirm)
                while(not(endConfirm == "Y" or endConfirm == "N")):
                    endConfirm = list(input())
                    try:
                        endConfirm = endConfirm[0]
                    except IndexError:
                        endConfirm = "Y"
                    endConfirm = endConfirm.upper()
                if(endConfirm == "Y"):
                    score = 0
                    print(ScrClr)
                    print(textContinue, "\n" * 4)
                    time.sleep(gameDelayModifier * 1)
                    print(ScrClr)
                elif(endConfirm == "N"):
                    gameEnd = 1
                    print(ScrClr)
                    time.sleep(gameDelayModifier * 0.25)
                    print(textQuit, "\n" * 4)
                    time.sleep(gameDelayModifier * 1.25)
                    print(ScrClr)

            # When the game is lose
            elif(gameDecider == 2):
                print(lineBarBottomLose)
                print(lineBarBottomB)
                score = int(guessCorrect * scoreModifierLose * scoreModifier * streakModifier)
                scoreTotal = int(scoreTotal) + int(score)
                if(scoreTotal > scoreTop):
                    scoreTop = scoreTotal
                scoreLast = score
                displayScore()
                print("\nYou Lose\n")
                print(textLose)
                hasPlayed = 1
                print(textContinueConfirm)
                while(not(endConfirm == "Y" or endConfirm == "N")):
                    endConfirm = list(input())
                    try:
                        endConfirm = endConfirm[0]
                    except IndexError:
                        endConfirm = "Y"
                    endConfirm = endConfirm.upper()
                if(endConfirm == "Y"):
                    score = 0
                    scoreTotal = 0
                    print(ScrClr)
                    print(textContinue, "\n" * 4)
                    time.sleep(gameDelayModifier * 1)
                    print(ScrClr)
                elif(endConfirm == "N"):
                    gameEnd = 1
                    print(ScrClr)
                    time.sleep(gameDelayModifier * 0.25)
                    print(textQuit, "\n" * 4)
                    time.sleep(gameDelayModifier * 1.25)
                    print(ScrClr)

            # When quitting mid-game
            elif(gameDecider == 3):
                print(lineBarBottomSurrender)
                print(lineBarBottomB)
                score = int(guessCorrect * scoreModifierSurrender * scoreModifier * streakModifier)
                scoreTotal = int(scoreTotal) + int(score)
                displayScore()
                score = 0
                if(scoreTotal > scoreTop):
                    scoreTop = scoreTotal
                scoreLast = score
                print("")
                print(textSurrender)
                gameEnd = 1
                time.sleep(gameDelayModifier * 1.25)
                print(ScrClr)

    # If [Q]uit is input, user is prompted to confirm exit
    if(gameExit == 1):
        print(ScrClr)
        print(textExitConfirm)
        while(not(exitConfirm == "Y" or exitConfirm == "N")):
            exitConfirm = list(input())
            try:
                exitConfirm = exitConfirm[0]
            except IndexError:
                exitConfirm = ""
            exitConfirm = exitConfirm.upper()
        if(exitConfirm == "Y"):
            gameCore = 0
            print(ScrClr)
            time.sleep(gameDelayModifier * 0.25)
            if(hasPlayed == 1):
                print(textExit, "\n" * 3)
            else:
                print("     W e   h a v e n ' t   p l a y e d   o u r   g a m e   y e t !", "\n" * 3)
            time.sleep(gameDelayModifier * 1.75)
        elif(exitConfirm == "N"): # Basically just loops back to main menu
            print(ScrClr)
