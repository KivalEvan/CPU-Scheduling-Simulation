### PLEASE READ ###
# The program is written on Python 3.6.4
# To avoid possible error(s), run the program in Python 3.6+
# It is advised to put program together in an empty folder.
#
# The work contributions
#   Main Module |
#   CLASSIFIED
#
#   Text File Module |
#   CLASSIFIED
#   CLASSIFIED
#
#   Authentication Module |
#   CLASSIFIED
#
#   Match/Result Module |
#   CLASSIFIED
#
# The modules made by the members is scrapped and fitted into the Nabawi's own coding scheme
# to provide more consistency and readability.

# Importing built-in library in Python.
# time library is self-explanatory, used to track time and delay.
# os.path library is system library that search for path file.
# operator library is used to sort value.
# importing localtime and strftime from time to calculate actual local time.
import time
import os.path
import operator
import random
from time import localtime, strftime

### TEXT VARIABLE PARAMETER ###
# This is the text paramater where it can be modified to change the text displayed on certain modules or functions.
# Although, not every text displayed can be modified yet as they are hardcoded in the functions.
text_title_program = "|  | || Competitive Gaming Offline Scoreboard || |  |"
text_title_main_menu = "  ===  Main Menu  ===  "
text_title_game_setup = "  ===  Game Setup  ===  "
text_title_game_option = "  ===  Game Option  ===  "
text_title_game_management = "  ===  Game Management  ===  "
text_title_team_management = "  ===  Team Management  ===  "
text_title_team_manage = "  ===  Manage Team  ===  "
text_title_user_settings = "  ===  User Settings  ===  "
text_title_match_panel_standard = "  ||===  Match Panel  ===||  Standard  ||"
text_title_match_panel_total_point = "  ||===  Match Panel  ===||  Highest Total Point  ||"
text_title_match_panel_player_point = "  ||===  Match Panel  ===||  Highest Player Point  ||"
text_title_match_panel_score_ratio = "  ||===  Match Panel  ===||  Highest Score Ratio  ||"
text_subtitle_match_end = "\t\\\\\\\\\\\\\\\\ MATCH ENDED \\\\\\\\\\\\\\\\"
text_auth_password_input = "Password: "
text_auth_password_auth = "Password: "
text_auth_password_new = "New password: "
text_auth_hostname_input = "Hostname: "
text_auth_hostname_new = "New hostname: "
text_auth_username_input = "Username: "
text_auth_success = "Login successfully!"
text_auth_success_user = "Found username."
text_auth_success_pass = "Password matched!"
text_auth_fail = "Access denied."
text_auth_fail_user = "Cannot find the username."
text_auth_fail_pass = "Password does not matches."
text_auth_cancel = "Cancelled access."
text_event_name_input = "Event name: "
text_event_name_new = "New event name: "
text_game_name_input = "Game name: "
text_game_name_new = "New game name: "
text_game_genre_input = "\nGenre name: "
text_game_genre_new = "\nNew genre name: "
text_game_score_type_input = "Score type: "
text_game_mode_input = "Game mode: "
text_game_info_input = "Game info: "
text_max_player_input = "Max player: "
text_max_player_team_input = "Max player per team: "
text_team_name_input = "Team name: "
text_team_name_new = "New team name: "
text_team_player_input = "Player name: "
text_team_player_new = "New player name: "

text_message_auth_menu = ("\n  Note:"
                          "\tThe program is only suited for the user responsible in taking the score.\n"
                          "\tIt is advised to take precaution on a match for fair scoring.\n"
                          "\tThe responsible should take screencaps at the end of match to reduce\n"
                          "\tpossible human error.\n"
                          "\n\tThe program will not be responsible for score fixing.")
text_message_game_no_game = ("No game found.\n"
                             "Add game(s) or delete the game_list.txt and restart.")
text_message_game_no_alias = ("No alias found.\n"
                             "Add alias(es) to the game.")
text_message_game_max_player_uneven = ("Max player is uneven.")
text_message_game_max_player_team_uneven = ("Max player per team is uneven.")
text_message_game_max_player_strict = ("Max player strict is enabled.\n"
                                       "Disable/Toggle it to make changes for max player.")
text_message_team_no_team = ("No team found.\n"
                             "Add team(s) or delete the team_list.txt and restart.")
text_message_team_no_player = ("No player found.\n"
                               "Add player(s) or delete the team_list.txt and restart.")
text_message_team_no_team_select = ("No team selected.\n"
                                    "Select the playing team.")
text_message_team_one_team_select = ("Only one team selected.\n"
                                    "Select the playing opposing team.")
text_message_team_maxed_player = ("Max player limit reached.\n"
                                  "Remove playing player in order to add new player.")
text_message_team_full_team = ("Full playing team.\n"
                               "Remove playing team in order to add new team.")
text_message_team_no_player_select = ("No player in roster.\n"
                                      "Select the player to move into roster.")
### END PARAMETER ###

### PRE-DEFINED VARIABLE PARAMETER ###
event_name = ""
username = ""
password = ""
hostname = ""

user_list = []
userpass_db = {}
userhost_db = {}
team_list = []
player_list = []
team_player_list = {}
game_name = []
game_alias = []
game_genre = []
game_alias_list = {}
game_genre_list = {}
game_mode_list = ['Competitive', 'Classic', 'Casual']
game_score_type_list = ['Standard', 'Highest Total Point', 'Highest Player Point', 'Highest Score Ratio']

game_selected = ""
game_genre_selected = ""
game_mode_selected = "Competitive"
game_score_type_selected = "Standard"
game_info_add = ""
game_max_player = 10
game_max_player_per_team = 5
game_max_player_strict = 0
team_roster_team = []
team_roster_player = {}

scoreboard_team = []
scoreboard_team_score = {}
scoreboard_player = []
scoreboard_player_score = {}
scoreboard_match_team_score = {}

leaderboard_team = {}
leaderboard_player = {}

match_history_recent = []
match_history_recent_time = ""
match_history_recent_time_short = ""

authorise_check = 0
registering_check = 0
game_adding_check = 0
team_adding_check = 0
match_check = 0

program_run = 1
### END PARAMETER ###

### CONSTANT VARIABLE PARAMETER ###
ALPHANUMSYM = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890`~!@#$%^&*()_-+={}|:;'<>?,./"
ENCRYPT_KEY = "uejobtpzwcnsrkdgvmlfaqiyxhUEJOBTPZWCNSRKDGVMLFAQIYXH 0987654321`~!@#$%^&*()_-+={}|:;'<>?,./"
ALLOWED_SYMBOL = "`~!@#$%^&*()_-+={}|:;'<>?,./"
ALLOWED_SYMBOL = list(ALLOWED_SYMBOL)
SCRCLR = "\n" * 64
### END PARAMETER ###

### DEBUG PARAMETER ###
# For de-bugging purposes, this is only used by developer only.
# Debug mode is made to track anything that is happening in the variable.
# Insecure mode (BARELY USED; debug mode must be enabled) shows insensitive information such as password.
# Predefine mode can be toggled without debug mode and used to toggle predefinition of the variable.
# IF any changes made in the text file may cause an error for predefine_mode.
# Switch only between number 0 (OFF) and 1 (ON).
debug_mode = 0
insecure_mode = 0
predefine_mode = 0

# Text for debug
debug_prefix = "[DEBUG]"
debug_input = "[DEBUG] Input: "
debug_output = "[DEBUG] Output: "
debug_encrypt = "[DEBUG] Encrypting: "
debug_decrypt = "[DEBUG] Decrypting: "
debug_check = "[DEBUG] Checking: "
debug_look_var = "[DEBUG] Look up var.: "
debug_found_not = "[DEBUG] Not Found"
debug_found = "[DEBUG] Found: "
debug_file_read = "[DEBUG] Reading: "
debug_file_readline = "[DEBUG] Reading Line "
debug_seperate = "[DEBUG] Seperating: "
debug_strip = "[DEBUG] Stripping: "
debug_amount = "[DEBUG] Amount: "
debug_amount_database = "[DEBUG] Amount in database: "
debug_list = "[DEBUG] Listing: "
debug_sort = "[DEBUG] Sorting: "
debug_creating = "[DEBUG] Creating: "
debug_match = "[DEBUG] Matching: "
debug_match_success = "[DEBUG] Found Match(es)"
debug_match_failed = "[DEBUG] No Match"
debug_fetch = "[DEBUG] Fetching: "
debug_split = "[DEBUG] Splitting: "
debug_upper = "[DEBUG] Uppercasing: "
debug_shorten = "[DEBUG] Shortening: "
debug_despace = "[DEBUG] De-spacing: "
debug_convert = "[DEBUG] Converting: "
debug_username = "[DEBUG] Username List: "
debug_username_insecure = "[DEBUG] Username List (Incl. Password): "

if(debug_mode == 1 and insecure_mode == 1):
    print("WARNING: Debug mode runs the code slower and heavier."
          "\n\t Insecured Mode - [ON]"
          "\n\t Sensitive information will be revealed.\n")
    time.sleep(0)
elif(debug_mode == 1 and insecure_mode == 0):
    print("WARNING: Debug mode runs the code slower and heavier."
          "\n\t Insecured Mode - [OFF]\n")
    time.sleep(0)
### END PARAMETER ###

### FUNCTION PARAMETER ###
# For every time the program starts, it will go through these procedures to find or create required files.
# These files are only the text files containing the information required for user database, game list,
# and team/player list.
def initialise():
    if(debug_mode == 1):
        print(debug_check + "user_db.txt in folder")
    if(os.path.isfile('user_db.txt') == False):
        if(debug_mode == 1):
            print(debug_found_not)
            print(debug_creating + "user_db.txt")
        file_user_db = open('user_db.txt','w')
        file_user_db.write("rrablgdmfljsae[]PdffuPwfPao[]RRA Blgdmfl Jsae\n")
        file_user_db.close()
    else:
        if(debug_mode == 1):
            print(debug_found + "user_db.txt")
    
    if(debug_mode == 1):
        print(debug_check + "team_player_list.txt in folder")
    if(os.path.isfile('team_player_list.txt') == False):
        if(debug_mode == 1):
            print(debug_found_not)
            print(debug_creating + "team_player_list.txt")
        file_team_player_list = open('team_player_list.txt','w')
        file_team_player_list.write("==TEAM========\n"
                                    "Unassigned\n"
                                    "==PLAYER======\n"
                                    "==============\n\n"
                                    "==TEAM========\n"
                                    "Team 1\n"
                                    "==PLAYER======\n"
                                    "Player 1\nPlayer 2\nPlayer 3\nPlayer 4\nPlayer 5\n"
                                    "==============\n\n"
                                    "==TEAM========\n"
                                    "Team 2\n"
                                    "==PLAYER======\n"
                                    "Player 6\nPlayer 7\nPlayer 8\nPlayer 9\nPlayer 10\n"
                                    "==============\n\n")
        file_team_player_list.close()
    else:
        if(debug_mode == 1):
            print(debug_found + "team_player_list.txt")
    
    if(debug_mode == 1):
        print(debug_check + "game_list.txt in folder")
    if(os.path.isfile('game_list.txt') == False):
        if(debug_mode == 1):
            print(debug_found_not)
            print(debug_creating + "game_list.txt")
        file_game_list = open('game_list.txt','w')
        file_game_list.write("Counter-Strike: Global Offensive][First Person Shooter]csgo[\n"
                             "Dota 2][MOBA[]dota2[]dota[\n"
                             "League of Legends][MOBA]leagueoflegends[]leagueoflegend[]lol[\n"
                             "Rainbow Six: Siege][First Person Shooter]r6s[]rss[]r6siege[\n"
                             "Overwatch][First Person Shooter]ow[\n"
                             "Osu!][Rhythm[]osu[\n"
                             "Hearthstone][Card Game]hs[\n"
                             "Paladins][First Person Shooter]paladin[\n"
                             "FIFA][Sport]fifa[]fo[\n"
                             "PlayerUnknown's Battleground][Battle Royale]pubg[\n")
        file_game_list.close()
    else:
        if(debug_mode == 1):
            print(debug_found + "game_list.txt")
            print()

    # After finding or creating the required files, the program fetches the information inside the text files.
    # Modifying or removing the content inside the text file(s) may result in possible errors.
    user_data_fetcher()
    game_list_fetcher()
    team_data_fetcher()
    if(predefine_mode == 1):
        predefined_main()

def user_data_fetcher():
    global userpass_db
    global userhost_db
    with open('user_db.txt','r') as user_dbfile:
        user_data = user_dbfile.readlines()
    if(debug_mode == 1):
        print(debug_file_read + str(user_data))
    
    user_data = [x.strip() for x in user_data]
    try:        # If the user somehow made empty space in between the line, the program will ignore it.
        user_data.remove("")
    except:
        print()
    
    if(debug_mode == 1 and len(user_data) > 0):
        print(debug_strip + str(user_data))
        print(debug_amount_database + str(len(user_data)))
        if(insecure_mode == 1):
            print(debug_list)
            for i in range(len(user_data)):
                print("  [" + str(i + 1) + "]\t" + user_data[i])
            print()
    
        print(debug_seperate)
    for i in range(len(user_data)):
        temp_user_data = user_data[i]
        if(debug_mode == 1 and len(user_data) > 0):
            print(debug_file_readline + str(i + 1) + ": " + temp_user_data)
        temp_user_data = temp_user_data.split("[]")
        if(debug_mode == 1 and len(user_data) > 0):
            print(debug_split + str(temp_user_data))
        for j in range(len(temp_user_data)):
            temp_user_data[j] = simple_decrypt_encrypt(temp_user_data[j], ENCRYPT_KEY, ALPHANUMSYM)
            if(debug_mode == 1 and len(user_data) > 0):
                if(not(j == 1)):
                    print(debug_decrypt + temp_user_data[j])
                elif((j == 1) == (insecure_mode == 1)):
                    print(debug_decrypt + temp_user_data[j])
        userpass_db[temp_user_data[0]] = temp_user_data[1]
        userhost_db[temp_user_data[0]] = temp_user_data[2]
        user_list.append(temp_user_data[0])
    
    if(debug_mode == 1 and len(user_data) > 0):
        temp_counter = 0
        
        print()
        if(insecure_mode == 1):
            print(debug_username_insecure)
            for username, password in userpass_db.items():
                temp_counter += 1
                print("  [" + str(temp_counter) + "]\t[Username] " + str(username) + "\n\t[Password] " + str(password) + "\n\t[Hostname] " + str(userhost_db[username]))
        else:
            print(debug_username)
            for username, password in userpass_db.items():
                temp_counter += 1
                print("  [" + str(temp_counter) + "]\t[Username] " + str(username) + "\n\t[Hostname] " + str(userhost_db[username]))
        print()
    elif(debug_mode == 1):
        print(debug_prefix + " No user found\n")

def game_list_fetcher():
    global game_alias_list
    global game_genre_list
    global game_name
    global game_alias
    global game_genre
    
    with open('game_list.txt','r') as game_list_file:
        game_list_data = game_list_file.readlines()
    if(debug_mode == 1):
        print(debug_file_read + str(game_list_data))
    
    game_list_data = [x.strip() for x in game_list_data]
    try:        # If the user somehow made empty space in between the line, the program will ignore it.
        game_list_data.remove("")
    except:
        print()
    
    if(debug_mode == 1 and len(game_list_data) > 0):
        print(debug_strip + str(game_list_data))
        print(debug_amount_database + str(len(game_list_data)))
        print(debug_list)
        for i in range(len(game_list_data)):
            print("  [" + str(i + 1) + "]\t" + game_list_data[i])
        print()

        print(debug_seperate)
    for i in range(len(game_list_data)):
        temp_game_list_data = game_list_data[i]
        if(debug_mode == 1 and len(game_list_data) > 0):
            print(debug_file_readline + str(i + 1) + ": " + temp_game_list_data)
        temp_game_list_data = temp_game_list_data.split("][")
        temp_game_list_data_2 = temp_game_list_data[1]
        temp_game_list_data_2 = temp_game_list_data_2.split("]")
        temp_game_list_data.remove(temp_game_list_data[1])
        for j in range(len(temp_game_list_data_2)):
            temp_game_list_data.append(temp_game_list_data_2[j].replace('[',''))
        print(temp_game_list_data)
        if(debug_mode == 1 and len(game_list_data) > 0):
            print(debug_split + str(temp_game_list_data))
        game_name.append(temp_game_list_data[0])
        if(temp_game_list_data[1] not in game_genre):
            game_genre.append(temp_game_list_data[1])
        game_genre_list[temp_game_list_data[0]] = temp_game_list_data[1]
        for j in range(len(temp_game_list_data)):
            if(j != 0 and j != 1):
                game_alias_list[temp_game_list_data[j]] = temp_game_list_data[0]
                game_alias.append(temp_game_list_data[j])
    
    if(debug_mode == 1 and len(game_name) > 0):
        print()
        print(debug_list + "Game Name")
        for i in range(len(game_name)):
            print("  [" + str(i + 1) + "]\t" + game_name[i])
        print()
        if(len(game_alias) > 0):
            print(debug_list + "Game Alias")
            for i in range(len(game_alias_list)):
                print("  [" + str(i + 1) + "]\t" + game_alias[i])
            print()
        print(debug_list + "Game Genre")
        for i in range(len(game_genre)):
            print("  [" + str(i + 1) + "]\t" + game_genre[i])
        print()
        if(len(game_alias) > 0):
            print(debug_sort)
            for i in range(len(game_alias_list)):
                print("  [" + str(i + 1) + "]\t" + game_alias[i] + " alias for " + game_alias_list[game_alias[i]])
            print()
        print(debug_sort)
        for i in range(len(game_genre_list)):
            print("  [" + str(i + 1) + "]\t" + game_genre_list[game_name[i]] + " genre for " + game_name[i])
        print()
    elif(debug_mode == 1):
        print(debug_prefix + " No game found\n")

def team_data_fetcher():
    global team_list
    global player_list
    global team_player_list
    
    temp_fetcher_order = 0
    temp_team_name = ""
    temp_team_player = ""
    
    with open('team_player_list.txt','r') as team_player_listfile:
        team_player_data = team_player_listfile.readlines()
    if(debug_mode == 1):
        print(debug_file_read + str(team_player_data))
    
    team_player_data = [x.strip() for x in team_player_data]
    
    if(debug_mode == 1):
        print(debug_strip + str(team_player_data))
        print(debug_amount_database + str(len(team_player_data)))
        print(debug_list)
        for i in range(len(team_player_data)):
            print("  [" + str(i + 1) + "]\t" + team_player_data[i])
        print()
    
        print(debug_seperate)
    for i in range(len(team_player_data)):
        temp_team_player_data = team_player_data[i]
        if(debug_mode == 1):
            print(debug_file_readline + str(i + 1) + ": " + temp_team_player_data)

        if(temp_fetcher_order == 1):
            temp_team_name = temp_team_player_data
            team_list.append(temp_team_name)
            temp_fetcher_order = 0
        elif(temp_fetcher_order == 2):
            temp_team_player = temp_team_player_data
        
        if(temp_team_player_data == "==TEAM========"):
            temp_fetcher_order = 1
        elif(temp_team_player_data == "==PLAYER======"):
            temp_fetcher_order = 2
        elif(temp_team_player_data == "=============="):
            temp_fetcher_order = 0
            temp_team_name = ""
            temp_team_player = ""
        
        if(not(temp_team_name == "" or temp_team_player == "")):
            team_player_list[temp_team_player] = temp_team_name
            player_list.append(temp_team_player)
        
        if(debug_mode == 1):
            if(not(temp_team_name == "" or temp_team_player == "")):
                print(debug_prefix + " Team Name: " + temp_team_name)
                print(debug_prefix + " Player Name: " + temp_team_player)
                print(debug_prefix + " Assigning " + temp_team_player + " to " + temp_team_name + "\n")

    if(len(team_list) <= 0):
        file_team_player_list = open('team_player_list.txt','w')
        file_team_player_list.write("==TEAM========\n"
                            "Unassigned\n"
                            "==PLAYER======\n"
                            "==============\n\n")
        file_team_player_list.close()
        team_data_fetcher()
    
    if(debug_mode == 1):
        print()
        print(debug_list + "Team")
        for i in range(len(team_list)):
            print("  [" + str(i + 1) + "]\t" + team_list[i])
        print()
        print(debug_list + "Player")
        for i in range(len(player_list)):
            print("  [" + str(i + 1) + "]\t" + player_list[i])
        print()
        print(debug_sort + "Player in Team")
        for i in range(len(team_player_list)):
            print("  [" + str(i + 1) + "]\t" + player_list[i] + " in " + team_player_list[player_list[i]])
        print()

# Used to pre-define variable as debugging or demonstration purposes. Change predefine_mode = 1 to enable it.
# May cause an error if modification was made in the text file.
def predefined_main():
    global event_name
    global game_selected
    global game_genre_selected
    global game_mode_selected
    global game_score_type_selected
    global game_info_add
    global game_max_player
    global game_max_player_per_team
    global game_max_player_strict
    global team_roster_team
    global team_roster_player
    global leaderboard_team
    global leaderboard_player
    
    event_name = "Pre-defined Testing Purposes"
    game_selected = game_name[0]
    game_genre_selected = game_genre_list[game_name[0]]
    game_mode_selected = "Competitive"
    game_score_type_selected = "Standard"
    game_info_add = "Pre-defined"
    game_max_player = 10
    game_max_player_per_team = 5
    game_max_player_strict = 0
    team_roster_team = ['Team 1', 'Team 2']
    team_roster_player = {'Player 1': 'Team 1', 'Player 2': 'Team 1', 'Player 3': 'Team 1', 'Player 4': 'Team 1', 'Player 5': 'Team 1',
                          'Player 6': 'Team 2', 'Player 7': 'Team 2', 'Player 8': 'Team 2', 'Player 9': 'Team 2', 'Player 10': 'Team 2'}
    leaderboard_team = {}
    leaderboard_player = {}

def predefined_login():
    global username
    global password
    global hostname
    global authorise_check

    authorise_check = 1
    username = "mmuesportsclub"
    password = userpass_db["mmuesportsclub"]
    hostname = userhost_db["mmuesportsclub"]

# This encryption method is simple and easy to decode without the computer, given the encrypt key.
# However, since we are not doing serious security, this is the only method that is easier to use and explained.
def simple_decrypt_encrypt(encrypted_data, ENCRYPT_KEY, ALPHANUMSYM):
    key_indices = [ENCRYPT_KEY.index(k) for k in encrypted_data]
    return "".join(ALPHANUMSYM[key_index] for key_index in key_indices)

# Self-explanatory, this function is being used on certain part of the modules that requires confirmation from the user.
def prompt_confirm():
    input_choice = ''

    print("\nConfirm?")
    while(not(input_choice == 'Y' or input_choice == 'N')):
        input_choice = input("[Y]es or [N]o\n")
        input_choice = input_choice.upper().replace(' ','')
        if(len(input_choice) > 1):
            input_choice = input_choice[0:2]
            if(input_choice.isalnum() == True):
                input_choice = input_choice[0]
            if(input_choice == '[Y' or input_choice == '[N'):
                if(input_choice == '[Y'):
                    input_choice = 'Y'
                elif(input_choice == '[N'):
                    input_choice = 'N'

    return input_choice

# This is a information displayer, showing most of the details in the match.
def display_debug_menu():
    print("\tDEBUG MODE ENABLED")
    print(" ========== " * 8)
    print(debug_look_var + "team_list\n" + str(team_list))
    print(debug_look_var + "player_list\n" + str(player_list))
    print(debug_look_var + "team_player_list\n" + str(team_player_list))
    print(debug_look_var + "game_name\n" + str(game_name))
    print(debug_look_var + "game_alias\n" + str(game_alias))
    print(debug_look_var + "game_genre\n" + str(game_genre))
    print(debug_look_var + "game_alias_list\n" + str(game_alias_list))
    print(debug_look_var + "game_genre_list\n" + str(game_genre_list))
    print(debug_prefix + " Event name: " + event_name)
    print(debug_prefix + " Selected Game: " + game_selected)
    print(debug_prefix + " Selected Genre: " + game_genre_selected)
    print(debug_prefix + " Selected Mode: " + game_mode_selected)
    print(debug_prefix + " Selected Score Type: " + game_score_type_selected)
    print(debug_prefix + " Game Add. Info.: " + game_info_add)
    print(debug_prefix + " Max player: " + str(game_max_player))
    print(debug_prefix + " Max player per team: " + str(game_max_player_per_team))
    print(debug_prefix + " Max player strict: " + str(game_max_player_strict))
    print(debug_look_var + "team_roster_team\n" + str(team_roster_team))
    print(debug_look_var + "team_roster_player\n" + str(team_roster_player))
    print(debug_look_var + "leaderboard_team\n" + str(leaderboard_team))
    print(debug_look_var + "leaderboard_player\n" + str(leaderboard_player))
    print(debug_look_var + "match_history_recent\n" + str(match_history_recent))
    print(debug_prefix + " Recent Match Time: " + match_history_recent_time)
    print(debug_prefix + " Recent Match Time (Short): " + match_history_recent_time_short)
    print(" ========== " * 8)
    print("\tDEBUG MODE ENABLED\n")

def display_debug_scoreboard():
    print("\tDEBUG MODE ENABLED")
    print(" ========== " * 8)
    print(debug_prefix + " Event name: " + event_name)
    print(debug_prefix + " Selected Game: " + game_selected)
    print(debug_prefix + " Selected Genre: " + game_genre_selected)
    print(debug_prefix + " Selected Mode: " + game_mode_selected)
    print(debug_prefix + " Selected Score Type: " + game_score_type_selected)
    print(debug_prefix + " Game Add. Info.: " + game_info_add)
    print(debug_prefix + " Max player: " + str(game_max_player))
    print(debug_prefix + " Max player per team: " + str(game_max_player_per_team))
    print(debug_prefix + " Max player strict: " + str(game_max_player_strict))
    print(debug_look_var + "team_roster_team\n" + str(team_roster_team))
    print(debug_look_var + "team_roster_player\n" + str(team_roster_player))
    print(debug_look_var + "scoreboard_team\n" + str(scoreboard_team))
    print(debug_look_var + "scoreboard_team_score\n" + str(scoreboard_team_score))
    print(debug_look_var + "scoreboard_player\n" + str(scoreboard_player))
    print(debug_look_var + "scoreboard_player_score\n" + str(scoreboard_player_score))
    print(debug_look_var + "leaderboard_team\n" + str(leaderboard_team))
    print(debug_look_var + "leaderboard_player\n" + str(leaderboard_player))
    print(debug_look_var + "match_history_recent\n" + str(match_history_recent))
    print(debug_prefix + " Recent Match Time: " + match_history_recent_time)
    print(debug_prefix + " Recent Match Time (Short): " + match_history_recent_time_short)
    print(" ========== " * 8)
    print("\tDEBUG MODE ENABLED\n")

def display_info_menu():
    temp_counter_1 = 0
    temp_counter_2 = 0
    temp_team_roster_1 = ""
    temp_team_roster_2 = ""
    temp_team_roster_player = list(team_roster_player.keys())
    leaderboard_sorted_team = dict(sorted(leaderboard_team.items(), key=operator.itemgetter(1), reverse=True))
    leaderboard_sorted_player = dict(sorted(leaderboard_player.items(), key=operator.itemgetter(1), reverse=True))
    temp_leaderboard_team = list(leaderboard_sorted_team.keys())
    temp_leaderboard_player = list(leaderboard_sorted_player.keys())

    if(debug_mode == 1):
        display_debug_menu()

    print(text_title_program)
    print("|  | ||| " + event_name)
    print("\  \ Hosted by " + hostname)
    # Unused features; This shows leaderboard on main menu, but cause clutter mess.
    # if(len(temp_leaderboard_team) > 0):
    #     print("\nTeam Leaderboard | Win")
    #     for i in range(len(temp_leaderboard_team)):
    #         print("  [" + str(i + 1) + "]\t[" + str(leaderboard_sorted_team[temp_leaderboard_team[i]]) + " Win(s)] " + temp_leaderboard_team[i])
    # if(len(temp_leaderboard_player) > 0):
    #     print("\nPlayer Leaderboard | MVP")
    #     for i in range(len(temp_leaderboard_player)):
    #         print("  [" + str(i + 1) + "]\t[" + str(leaderboard_sorted_player[temp_leaderboard_player[i]]) + " MVP(s)] " + temp_leaderboard_player[i])
    if(game_selected != ""):
        print("\nPlaying: " + game_selected)
        print("Genre: " + game_genre_selected)
    if(game_selected != "" or game_mode_selected != "Default"):
        print("Gamemode: " + game_mode_selected)
    if(game_selected != "" and game_max_player_strict == 0):
        print("Max Player(s): " + str(game_max_player))
        print("Max Player(s) in Team: " + str(game_max_player_per_team))
    elif(game_selected != "" and game_max_player_strict == 1):
        print("Max Player(s) in Team (REQUIRED): " + str(game_max_player_per_team))
    if(game_selected != "" or game_score_type_selected != "Default"):
        print("\nScoring Type: " + game_score_type_selected)
    if(game_info_add != ""):
        print("Additional Info.: " + game_info_add)
    if(len(team_roster_team) == 1):
        print("\nTeam Playing: "
              "\n[" + team_roster_team[0] + "]\n")
    elif(len(team_roster_team) == 2):
        for i in range(len(temp_team_roster_player)):
            for j in range(len(team_roster_team)):
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[j]):
                    if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                        temp_counter_1 += 1
                        temp_team_roster_1 = temp_team_roster_1 + " > " + temp_team_roster_player[i] + "\n"
                    if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                        temp_counter_2 += 1
                        temp_team_roster_2 = temp_team_roster_2 + " > " + temp_team_roster_player[i] + "\n"
        if(game_max_player_strict == 0):
            print("\nTeam Playing:"
                  "\n[" + team_roster_team[0] + "]\n" + temp_team_roster_1 +
                  "\n[" + team_roster_team[1] + "]\n" + temp_team_roster_2)
        else:
            print("\nTeam Playing: [" + str(game_max_player_per_team) + " PLAYER(S) TEAM]"
                  "\n[" + team_roster_team[0] + "]\n" + temp_team_roster_1 +
                  "\n[" + team_roster_team[1] + "]\n" + temp_team_roster_2)
    display_info_missing()

def display_info_missing():
    if(game_selected == ""):
        print("\nNo game selected.\n"
              "Please select the game to play.\n")
    elif(team_roster_team == []):
        print("\nNo team selected.\n"
              "Please select the playing team.\n")
    if(len(team_roster_team) == 1):
        print("Only one team selected.\n"
              "Please select the playing opposing team.\n")
    elif(len(team_roster_team) == 2 and team_roster_player == {}):
        print("No player selected.\n"
              "Please select the playing player.\n")
    elif(len(team_roster_team) == 2):
        if(len(team_roster_player) > 0):
            for i in range(len(team_roster_team)):
                for j in range(len(player_list)):
                    if(team_roster_team[i] == team_player_list[player_list[j]] and player_list[j] in team_roster_player):
                        if(team_roster_team[i] != team_roster_player[player_list[j]]):
                            print("\nNo opposing player selected.\n"
                                  "Please select the playing opposing player.\n")
                            break

def display_info_match():
    temp_counter_1 = 0
    temp_counter_2 = 0
    temp_team_roster_1 = ""
    temp_team_roster_2 = ""
    temp_team_roster_player = list(team_roster_player.keys())

    if(debug_mode == 1):
        display_debug_scoreboard()

    print(text_title_program)
    print("|  | ||| " + event_name +
          "\n\  \ Hosted by " + hostname +
          "\n\nPlaying: " + game_selected +
          "\nGenre: " + game_genre_selected +
          "\nGamemode: " + game_mode_selected)
    if(game_max_player_strict == 0):
        print("Max Player(s): " + str(game_max_player))
        print("Max Player(s) in Team: " + str(game_max_player_per_team))
    elif(game_max_player_strict == 1):
        print("Max Player(s) in Team (REQUIRED): " + str(game_max_player_per_team))
    print("\nScoring Type: " + game_score_type_selected)
    print("Additional Info.: " + game_info_add)
    for i in range(len(temp_team_roster_player)):
        for j in range(len(team_roster_team)):
            if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[j]):
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                    temp_counter_1 += 1
                    temp_team_roster_1 = temp_team_roster_1 + " > "  + temp_team_roster_player[i] + "\n"
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                    temp_counter_2 += 1
                    temp_team_roster_2 = temp_team_roster_2 + " > "  + temp_team_roster_player[i] + "\n"
    if(game_max_player_strict == 0):
        print("\nTeam Playing:"
              "\n[" + team_roster_team[0] + "]\n" + temp_team_roster_1 +
              "\n[" + team_roster_team[1] + "]\n" + temp_team_roster_2)
    else:
        print("\nTeam Playing: [" + str(game_max_player_per_team) + " PLAYER(S) TEAM]"
              "\n[" + team_roster_team[0] + "]\n" + temp_team_roster_1 +
              "\n[" + team_roster_team[1] + "]\n" + temp_team_roster_2)
    print("Note: \tThis program is only specifically for responsible user on taking the score.\n"
          "\tPlease be advised to take precaution on a match for a fair match.\n"
          "\tMatch fixing is a serious issue that should not be taken lightly.")

def display_info_scoreboard():
    temp_counter_1 = 0
    temp_counter_2 = 0
    temp_team_roster_1 = ""
    temp_team_roster_2 = ""
    temp_team_roster_player = list(team_roster_player.keys())

    if(debug_mode == 1):
        display_debug_scoreboard()

    print(text_title_program)
    print("|  | ||| " + event_name +
          "\n\  \ Hosted by " + hostname +
          "\n\nPlaying: " + game_selected +
          "\nGenre: " + game_genre_selected +
          "\nGamemode: " + game_mode_selected)
    if(game_max_player_strict == 0):
        print("Max Player(s): " + str(game_max_player))
        print("Max Player(s) in Team: " + str(game_max_player_per_team))
    elif(game_max_player_strict == 1):
        print("Max Player(s) in Team (REQUIRED): " + str(game_max_player_per_team))
    print("\nScoring Type: " + game_score_type_selected)
    print("Additional Info.: " + game_info_add)
    for i in range(len(temp_team_roster_player)):
        for j in range(len(team_roster_team)):
            if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[j]):
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                    temp_counter_1 += 1
                    temp_team_roster_1 = temp_team_roster_1 + " > "  + temp_team_roster_player[i] + "\n"
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                    temp_counter_2 += 1
                    temp_team_roster_2 = temp_team_roster_2 + " > "  + temp_team_roster_player[i] + "\n"
    if(game_max_player_strict == 0):
        print("\nTeam Playing:"
              "\n[" + team_roster_team[0] + "] --- " + str(scoreboard_match_team_score[team_roster_team[0]]) + " Win(s)\n" + temp_team_roster_1 +
              "\n[" + team_roster_team[1] + "] --- " + str(scoreboard_match_team_score[team_roster_team[1]]) + " Win(s)\n" + temp_team_roster_2)
    else:
        print("\nTeam Playing: [" + str(game_max_player_per_team) + " PLAYER(S) TEAM]"
              "\n[" + team_roster_team[0] + "] --- " + str(scoreboard_match_team_score[team_roster_team[0]]) + " Win(s)\n" + temp_team_roster_1 +
              "\n[" + team_roster_team[1] + "] --- " + str(scoreboard_match_team_score[team_roster_team[1]]) + " Win(s)\n" + temp_team_roster_2)

def display_info_settings():
    print(text_title_program)
    print("Event name: " + event_name +
          "\n\nUsername: " + username +
          "\nHostname: " + hostname)

def display_match_scoreboard():
    if(debug_mode == 1):
        display_debug_scoreboard()

    print(text_title_program)
    print("|  | ||| " + event_name +
          "\n\  \ Hosted by " + hostname +
          "\n\nPlaying: " + game_selected +
          "\nGenre: " + game_genre_selected +
          "\nGamemode: " + game_mode_selected)
    print(" ====== " * 8)
    for i in range(len(scoreboard_team)):
        print("[" + scoreboard_team[i] + "] --- " + str(scoreboard_team_score[scoreboard_team[i]]) + " score(s)")
        for j in range(len(scoreboard_player)):
            if(team_roster_player[scoreboard_player[j]] == scoreboard_team[i]):
                print(" [" + str(scoreboard_player_score[scoreboard_player[j]]) + " Pt] > " + scoreboard_player[j])
        print("Total Point: " + str(calc_point_total(scoreboard_team[i])))
        print("Avg. Point: " + str(calc_point_avg(scoreboard_team[i])))
        print("Point/Score Ratio: " + str(calc_point_score_ratio(scoreboard_team[i])))
        print()
    print(" ====== " * 8)
    if(game_info_add != ""):
        print("Additional Info.: " + game_info_add)
        print(" ====== " * 8)

# This is the authentication menu, consisting of only program title, notes, and login & register sub-menu.
# The authentication module requires user database from the user_db.txt. If any modification made in the file
# may result in a possible error. If the user_db.txt files is empty, it will prompt the user about it and
# suggest to register a new user.
def authentication_module():
    global program_run
    input_menu_auth = ""
    
    while(not(input_menu_auth == '1' or input_menu_auth == '2' or input_menu_auth == '0')):
        if(predefine_mode == 1):
            predefined_login()
            break
        print(SCRCLR)
        print(text_title_program)
        print(text_message_auth_menu)
        if(len(userpass_db) == 0):
            print("\nNo user in database.\n"
                  "Please register new user.")
        print("\n[1] Login\n[2] Register\n\n[0] Exit\n")
        input_menu_auth = input()
        if(debug_mode == 1 and input_menu_auth != ''):
            print(debug_input + str(input_menu_auth))
            print(debug_upper + str(input_menu_auth.upper()))
            print(debug_despace + str(input_menu_auth.upper().replace(' ','')))
        input_menu_auth = input_menu_auth.upper().replace(' ','')
        if(len(input_menu_auth) > 1):
            input_menu_auth = input_menu_auth[0:2]
            if(input_menu_auth.isnumeric() == True):
                input_menu_auth = input_menu_auth[0]
            if(debug_mode == 1):
                print(debug_shorten + str(input_menu_auth))
                print(debug_match + str(input_menu_auth) + " to ['LO', 'RE', 'EX', '[1', '[2', '[0']")
            if(input_menu_auth == 'LO' or input_menu_auth == '[1' or
               input_menu_auth == 'RE' or input_menu_auth == '[2' or
               input_menu_auth == 'EX' or input_menu_auth == '[0'):
                if(input_menu_auth == 'LO' or input_menu_auth == '[1'):
                    input_menu_auth = '1'
                elif(input_menu_auth == 'RE' or input_menu_auth == '[2'):
                    input_menu_auth = '2'
                elif(input_menu_auth == 'EX' or input_menu_auth == '[0'):
                    input_menu_auth = '0'
                if(debug_mode == 1):
                    print(debug_match_success)
                    print(debug_convert + str(input_menu_auth))
            else:
                if(debug_mode == 1):
                    print(debug_match_failed)
    
    if(input_menu_auth == '1'):
        authentication_login()
    if(input_menu_auth == '2'):
        authentication_register()
    if(input_menu_auth == '0'):
        program_run = 0

# The login authentication process is effectively simple. The user have at least 3 entries,
# if the user fails to login within the amount of entries, the user will then kicked back to authentication menu.
# If the user login successfully, the authorisation check is defined and the user will be moved to main menu by
# ending the authentication module loop along with the authorisation check.
def authentication_login():
    global authorise_check
    global username
    global password
    global hostname
    
    for i in range(3):
        print(SCRCLR)
        print("Enter your username and password.\n"
              "You have " + str(3 - i) + " entry(s).\n"
              "Input Q or E if you want to cancel login.")
        username = input(text_auth_username_input)
        if(username.upper() == "Q" or username.upper() == "E"):
            print(text_auth_cancel)
            time.sleep(1)
            break
        password = input(text_auth_password_input)
        if(password.upper() == "Q" or password.upper() == "E"):
            print(text_auth_cancel)
            time.sleep(1)
            break
        username = username.lower()
        
        print(SCRCLR)
        if(username in userpass_db):
            print(text_auth_success_user)
            if(password == userpass_db[username]):
                print(text_auth_success_pass)
                hostname = userhost_db[username]
                authorise_check = 1
                break
            else:
                print(text_auth_fail_pass)
        else:
            print(text_auth_fail_user)
        time.sleep(1)
        print(SCRCLR)
    
        if(authorise_check == 1):
            print(text_auth_success)
            time.sleep(1)
            break
        elif(i >= 2):
            print(text_auth_fail)
            time.sleep(1)
            break

# The register authentication process is simple and straight forward.
# It will ask the user for the username first, then the password, and then the hostname.
# After given the input, the user is prompt to confirm their information given in the input.
# If yes, the program will encrypt and write the user information into the user_db.txt, and vice versa.
def authentication_register():
    global registering_check
    global userpass_db
    global userhost_db
    
    registering_check = 1
    input_choice = ''
    
    while True:
        print(SCRCLR)
        print("Username must be at least 5-20 characters.\n"
              "Username is case-insensitive.\n"
              "Input Q or E if you want to cancel the registration.")
        username_input = authentication_username_determiner()
        if(registering_check == 0):
            break
        
        print(SCRCLR)
        print("Password must be at least 5-20 characters.\n"
              "Password is case-sensitive.\n"
              "Input Q or E if you want to cancel the registration.")
        password_input = authentication_password_determiner(text_auth_password_input)
        if(registering_check == 0):
            break
        
        print(SCRCLR)
        print("Hostname must not be the same as other users.\n"
              "Input Q or E if you want to cancel the registration.")
        hostname_input = authentication_hostname_determiner(text_auth_hostname_input)
        if(registering_check == 0):
            break
        
        print(SCRCLR)
        print("Username: " + username_input +
              "\nPassword: " + ("*" * len(password_input)) +
              "\nHostname: " + hostname_input)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''
    
    if(registering_check == 1):
        userpass_db[username_input] = password_input
        userhost_db[username_input] = hostname_input
        
        for i in range(3):
            if(i == 0):
                temp_encrypted_data = username_input
            elif(i == 1):
                temp_encrypted_data = password_input
            elif(i == 2):
                temp_encrypted_data = hostname_input
            temp_encrypted_data = simple_decrypt_encrypt(temp_encrypted_data, ENCRYPT_KEY, ALPHANUMSYM)
            if(i == 0):
                username_input = temp_encrypted_data
            elif(i == 1):
                password_input = temp_encrypted_data
            elif(i == 2):
                hostname_input = temp_encrypted_data
        
        user_register = open('user_db.txt','a')
        user_register.write(username_input + "[]" + password_input + "[]" + hostname_input + "\n") 
        user_register.close

# A function to determine whether the username is valid and available to be used.
# The username must be at least 5-20 characters, alphanumerical, and not similar to others.
def authentication_username_determiner():
    global registering_check
    
    while True:
        input_username = input("Username: ")
        if(input_username.upper() == "Q" or input_username.upper() == "E"):
            registering_check = 0
            break
        elif(input_username.replace(' ','') == ""):
            print("Please input username.")
        elif(input_username.isspace() == True):
            print("No space is allowed.")
        elif(input_username.isalnum() == False):
            print("No special character allowed.")
        elif(len(input_username) < 5 or len(input_username) > 20):
            print("Username must be at least 5-20 characters.")
        elif(input_username in userpass_db):
            print("Username already existed.")
        else:
            break
    input_username = input_username.lower()
    
    return input_username

# A function to determine whether the password is valid.
# The password must be at least 5-20 characters, and alphanumerical with allowed symbol.
def authentication_password_determiner(text_password):
    global registering_check

    temp_password_input = ""
    
    while True:
        input_password = input(text_password)
        if(input_password.upper() == "Q" or input_password.upper() == "E"):
            registering_check = 0
            break
        temp_input_password = input_password
        for i in range(len(ALLOWED_SYMBOL)):
            temp_input_password = temp_input_password.replace(ALLOWED_SYMBOL[i],'')
        if(input_password.replace(' ','') == ""):
            print("Please input password.")
        elif(input_password.isspace() == True):
            print("No space is allowed.")
        elif(temp_input_password.isalnum() == False):
            print("Contains disallowed symbol(s).")
        elif(len(input_password) < 5 or len(input_password) > 20):
            print("Password must be at least 5-20 characters.")
        else:
            break
    
    return input_password

# A function to determine whether the hostname is valid and available to be used.
# The hostname must be not using disallowed symbol and not similar to others.
def authentication_hostname_determiner(text_hostname):
    global registering_check

    temp_hostname_input = ""
    
    while True:
        input_hostname = input(text_hostname)
        if(input_hostname.upper() == "Q" or input_hostname.upper() == "E"):
            registering_check = 0
            break
        temp_hostname_input = input_hostname
        for i in range(len(ALLOWED_SYMBOL)):
            temp_hostname_input = temp_hostname_input.replace(ALLOWED_SYMBOL[i],'')
        if(input_hostname.replace(' ','') == ""):
            print("Please input hostname.")
        for host_search, userhost_data in userhost_db.items():
            if(input_hostname.lower().replace(' ','') in userhost_data.lower().replace(' ','') and
               input_hostname.lower().replace(' ','') != ""):
                print("Hostname is already taken by another user.")
                input_hostname = ""
                break
        if(temp_hostname_input.replace(' ','').isalnum() == False or input_hostname == ""):
            if(input_hostname.replace(' ','') != ""):
                print("Contains disallowed symbol(s).")
        else:
            break
    
    return input_hostname

# For security purposes, this function acts as authorisation validation.
# It is used in many parts of the modules and functions.
def authentication_process(text_password):
    authorise_check = 1

    print(SCRCLR)
    for i in range(3):
        if(i == 0):
            print("Awaiting authorisation...\n"
                  "Enter your current password.")
        print("You have " + str(3 - i) + " entry(s).\n"
              "Input Q or E if you want to cancel.")
        password = input(text_password)
        
        print(SCRCLR)
        if(password.upper() == "Q" or password.upper() == "E"):
            authorise_check = 3
            break
        if(password == userpass_db[username]):
            print(text_auth_success_pass)
            authorise_check = 2
            time.sleep(1)
            break
        else:
            print(text_auth_fail_pass)
            time.sleep(1)
            print(SCRCLR)
    
    return authorise_check

def authentication_pass_change():
    global password
    global username

    input_choice = ''
    temp_password_prev = userpass_db[username]

    print(SCRCLR)
    while True:
        print("Password must be at least 5-20 characters.\n"
              "Password is case-sensitive.\n"
              "Input Q or E if you want to cancel.")
        password = authentication_password_determiner(text_auth_password_new)
        if(password.upper() == "Q" or password.upper() == "E"):
            break
    
        print(SCRCLR)
        print("Password: " + password)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            userpass_db[username] = password
            
            for i in range(3):
                if(i == 0):
                    temp_encrypted_data = username
                elif(i == 1):
                    temp_encrypted_data = password
                elif(i == 2):
                    temp_encrypted_data = temp_password_prev
                temp_encrypted_data = simple_decrypt_encrypt(temp_encrypted_data, ENCRYPT_KEY, ALPHANUMSYM)
                if(i == 0):
                    temp_username = temp_encrypted_data
                elif(i == 1):
                    temp_password = temp_encrypted_data
                elif(i == 2):
                    temp_password_prev = temp_encrypted_data
    
            password_change = open('user_db.txt').read()
            password_change = password_change.replace(temp_username + "[]" + temp_password_prev + "[]",
                                                      temp_username + "[]" + temp_password + "[]")
            user_db_change = open('user_db.txt','w')
            user_db_change.write(password_change)
            user_db_change.close()
            break
        input_choice = ''

def authentication_hostname_change():
    global username
    global hostname

    input_choice = ''
    temp_hostname_prev = hostname
    
    while True:
        print(SCRCLR)
        print("Hostname must not be the same as other users.\n"
              "Input Q or E if you want to cancel the registration.")
        hostname = authentication_hostname_determiner(text_auth_hostname_new)
        if(hostname.upper() == "Q" or hostname.upper() == "E"):
            break
    
        print(SCRCLR)
        print("Hostname: " + hostname)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            userhost_db[username] = hostname
            
            for i in range(4):
                if(i == 0):
                    temp_encrypted_data = username
                elif(i == 1):
                    temp_encrypted_data = password
                elif(i == 2):
                    temp_encrypted_data = hostname
                elif(i == 3):
                    temp_encrypted_data = temp_hostname_prev
                temp_encrypted_data = simple_decrypt_encrypt(temp_encrypted_data, ENCRYPT_KEY, ALPHANUMSYM)
                if(i == 0):
                    temp_username = temp_encrypted_data
                elif(i == 1):
                    temp_password = temp_encrypted_data
                elif(i == 2):
                    temp_hostname = temp_encrypted_data
                elif(i == 3):
                    temp_hostname_prev = temp_encrypted_data
    
            hostname_change = open('user_db.txt').read()
            hostname_change = hostname_change.replace(temp_username + "[]" + temp_password + "[]" + temp_hostname_prev,
                                                      temp_username + "[]" + temp_password + "[]" + temp_hostname)
            user_db_change = open('user_db.txt','w')
            user_db_change.write(hostname_change)
            user_db_change.close()
            break
        input_choice == ""

# Self-explanatory, setting up an event name everytime the user login.
# This function also checks if there had been previous event name and prompts if the user wants to keep it.
def event_name_setup():
    input_choice = ''
    input_event_name = ""

    print(SCRCLR)
    if(event_name == ""):
        print("Enter the event name.\n"
              "Enter blank to go as Unnamed Event")
        while(input_event_name.replace(' ','') == ""):
            input_event_name = input(text_event_name_input)
            if(input_event_name.replace(' ','') == ""):
                input_event_name = "Unnamed Event"
    else:
        print("Do you want to keep the event name: " + event_name)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            input_event_name = event_name
        else:
            print(SCRCLR)
            print("Enter the event name.\n"
                  "Enter blank to go as Unnamed Event")
            while(input_event_name.replace(' ','') == ""):
                input_event_name = input(text_event_name_new)
                if(input_event_name.replace(' ','') == ""):
                    input_event_name = "Unnamed Event"
        input_choice = ''
    
    return input_event_name

# This is the main module where it contains almost every modules and functions available in the program.
# It contains at game menu, team menu, user settings, and starting the match.
def main_module():
    global authorise_check
    
    input_menu = ''
    
    print(SCRCLR)
    display_info_menu()
    print(text_title_main_menu)
    print("[1] Game Setup\n"
          "[2] Team Management\n"
          "[3] Start The Match")
    if(len(leaderboard_player) > 0 or len(leaderboard_team) > 0):
        print()
    if(len(match_history_recent) > 0):
        print("[5] View Recent Match(es)")
    if(len(leaderboard_team) > 0):
        print("[6] View Team Leaderboard")
    if(len(leaderboard_player) > 0):
        print("[7] View Player Leaderboard")
    print("\n[8] User Settings\n"
          "[0] Log Out\n")
    while(not(input_menu == '1' or input_menu == '2' or input_menu == '3' or input_menu == '5' or
              input_menu == '6' or input_menu == '7' or input_menu == '8' or input_menu == '0')):
        input_menu = input()
        input_menu = input_menu.upper()
        input_menu = input_menu.replace(' ','')
        if(len(input_menu) > 1):
            input_menu = input_menu[0:2]
            if(input_menu.isnumeric() == True):
                input_menu = input_menu[0]
            if(input_menu == 'GA' or input_menu == 'GS' or input_menu == '[1' or
               input_menu == 'TE' or input_menu == 'TM' or input_menu == '[2' or
               input_menu == 'ST' or input_menu == '[3' or
               input_menu == 'VI' or input_menu == 'VR' or input_menu == '[5' or
               input_menu == 'TL' or input_menu == '[6' or
               input_menu == 'PL' or input_menu == '[7' or
               input_menu == 'US' or input_menu == '[8' or
               input_menu == 'LO' or input_menu == '[0'):
                if(input_menu == 'GA' or input_menu == 'GS' or input_menu == '[1'):
                    input_menu = '1'
                elif(input_menu == 'TE' or input_menu == 'TM' or input_menu == '[2'):
                    input_menu = '2'
                elif(input_menu == 'ST' or input_menu == '[3'):
                    input_menu = '3'
                elif(input_menu == 'VI' or input_menu == 'VR' or input_menu == '[5'):
                    input_menu = '5'
                elif(input_menu == 'TL' or input_menu == '[6'):
                    input_menu = '6'
                elif(input_menu == 'PL' or input_menu == '[7'):
                    input_menu = '7'
                elif(input_menu == 'US' or input_menu == '[8'):
                    input_menu = '8'
                elif(input_menu == 'LO' or input_menu == '[0'):
                    input_menu = '0'
    
    if(input_menu == '1'):
        game_setup()
    elif(input_menu == '2'):
        team_management()
    elif(input_menu == '3'):
        print(SCRCLR)
        temp_counter_1 = 0
        temp_counter_2 = 0
        temp_team_roster_player = list(team_roster_player.keys())

        for i in range(len(temp_team_roster_player)):
            for j in range(len(team_roster_team)):
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[j]):
                    if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                        temp_counter_1 += 1
                    if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                        temp_counter_2 += 1
        if(game_selected == "" and team_roster_team == []):
            print("Please select the game and the playing team.")
            time.sleep(2)
        elif(game_selected == ""):
            print("Please select the game to play.")
            time.sleep(2)
        elif(team_roster_team == []):
            print("Please select the playing team.")
            time.sleep(2)
        elif(team_roster_player == {}):
            print("Please create the team roster.")
            time.sleep(2)
        elif(temp_counter_1 == 0 or temp_counter_2 == 0):
            print("Please assign at least one player in an empty team.")
            time.sleep(2)
        elif(game_max_player_strict == 1 and len(team_roster_player) != game_max_player):
            print("Please fill the team until player limit per team.")
            time.sleep(2)
        else:
            match_prompt_initial()
            time.sleep(2)
    elif(input_menu == '5' and len(match_history_recent) > 0):
        view_match_history()
    elif(input_menu == '6' and len(leaderboard_team) > 0):
        view_leaderboard_team()
    elif(input_menu == '7' and len(leaderboard_player) > 0):
        view_leaderboard_player()
    elif(input_menu == '8'):
        authorise_check = authentication_process(text_auth_password_auth)
        if(authorise_check == 2):
            authorise_check = 1
            user_settings()
        elif(authorise_check == 3):
            authorise_check = 1
            print(text_auth_cancel)
            time.sleep(1)
        else:
            print(text_auth_fail)
            time.sleep(1)
    elif(input_menu == '0'):
        authorise_check = 0

# The game setup is important to determine how the match will play out.
def game_setup():
    while True:
        input_menu = ''
        
        print(SCRCLR)
        display_info_menu()
        print(text_title_game_setup)
        print("[1] Select Game\n"
              "[2] Game Option\n"
              "[3] Manage Game\n"
              "\n[4] View Game\t\t[5] View Alias\n"
              "\n[0] Back\n")
        while(not(input_menu == '1' or input_menu == '2' or input_menu == '3' or
                  input_menu == '4' or input_menu == '5' or input_menu == '0')):
            input_menu = input()
            input_menu = input_menu.upper()
            input_menu = input_menu.replace(' ','')
            if(len(input_menu) > 1):
                input_menu = input_menu[0:2]
                if(input_menu.isnumeric() == True):
                    input_menu = input_menu[0]
                if(input_menu == 'SE' or input_menu == 'SG' or input_menu == '[1' or
                   input_menu == 'GA' or input_menu == 'GO' or input_menu == '[2' or
                   input_menu == 'MA' or input_menu == 'MG' or input_menu == '[3' or
                   input_menu == 'VG' or input_menu == '[4' or
                   input_menu == 'VA' or input_menu == '[5' or
                   input_menu == 'BA' or input_menu == '[0'):
                    if(input_menu == 'SE' or input_menu == 'SG' or input_menu == '[1'):
                        input_menu = '1'
                    elif(input_menu == 'GA' or input_menu == 'GO' or input_menu == '[2'):
                        input_menu = '2'
                    elif(input_menu == 'MA' or input_menu == 'MG' or input_menu == '[3'):
                        input_menu = '3'
                    elif(input_menu == 'VG' or input_menu == '[4'):
                        input_menu = '4'
                    elif(input_menu == 'VA' or input_menu == '[5'):
                        input_menu = '5'
                    elif(input_menu == 'BA' or input_menu == '[0'):
                        input_menu = '0'
    
        if(input_menu == '1'):
            game_selector()
        elif(input_menu == '2'):
            if(game_selected == ""):
                print(SCRCLR)
                print("Please select the game first.")
                time.sleep(2)
            else:
                game_option()
        elif(input_menu == '3'):
            game_management()
        if(input_menu == '4'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            else:
                game_view_game()
        elif(input_menu == '5'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            elif(len(game_alias) == 0):
                print(SCRCLR)
                print(text_message_game_no_alias)
                time.sleep(2)
            else:
                game_view_alias()
        elif(input_menu == '0'):
            break

# Self-explanatory, selecting the game/genre from the list.
# If the game is not found in the list, it prompts the user if they want to keep the game name input.
def game_selector():
    global game_selected
    global game_genre_selected

    input_choice = ''
    temp_input_game_select = ""
    
    while True:
        input_game_select = ""
        
        print(SCRCLR)
        if(len(game_name) > 0):
            print("List of available games:")
            for i in range(len(game_name)):
                print("  [" + str(i + 1) + "]\tName: " + game_name[i] + "\n\tGenre: " + game_genre_list[game_name[i]])
        if(len(game_name) == 0):
            print(text_message_game_no_game)
        print("\nSelect the game from the list.\n"
              "Enter blank to cancel.")
        input_game_select = input()
        temp_input_game_select = input_game_select
        if(input_game_select.replace(' ','') == ""):
            break
        for i in range(len(game_name)):
            if(input_game_select.lower() == game_name[i].lower()):
                game_selected = game_name[i]
                game_genre_selected = game_genre_list[game_name[i]]
                input_game_select = ""
            if(str(i + 1) == input_game_select):
                game_selected = game_name[i]
                game_genre_selected = game_genre_list[game_selected]
                input_game_select = ""
        if(input_game_select.replace(' ','') != ""):
            input_game_select = input_game_select.lower().replace(' ','')
            for i in range(len(ALLOWED_SYMBOL)):
                input_game_select = input_game_select.replace(ALLOWED_SYMBOL[i],'')
            if(input_game_select in game_alias):
                for i in range(len(game_alias)):
                    if(input_game_select == game_alias[i]):
                        game_selected = game_alias_list[game_alias[i]]
                        game_genre_selected = game_genre_list[game_selected]
                        input_game_select = ""
                        break
            else:
                print(SCRCLR)
                print("Unable to find the game with given name/alias input.\nAre you going to use " + temp_input_game_select + "?")
                input_choice = prompt_confirm()
                if(input_choice == 'Y'):
                    game_selected = temp_input_game_select
                    game_genre_selected = "Custom"
                    break
                input_choice = ''
        if(input_game_select.replace(' ','') == ""):
            break

# The game option is to determine the scoring type, game mode, max players, max players per team,
# and toggling between strict and unstrict max player rules.
def game_option():
    global game_max_player_strict

    while True:
        input_menu = ''
        
        print(SCRCLR)
        display_info_menu()
        print(text_title_game_option)
        print("[1] Change Score Type\t[2] Change Gamemode\n\n"
              "[3] Set Max Player\t[4]Set Max Player Per Team\n"
              "\t[5] Toggle Strict Max Player\n\n"
              "[6] Edit Additional Information\n"
              "[0] Back\n")
        while(not(input_menu == '1' or input_menu == '2' or input_menu == '3' or input_menu == '4' or
                  input_menu == '5' or input_menu == '6' or input_menu == '0')):
            input_menu = input()
            input_menu = input_menu.upper()
            input_menu = input_menu.replace(' ','')
            if(len(input_menu) > 1):
                input_menu = input_menu[0:2]
                if(input_menu.isnumeric() == True):
                    input_menu = input_menu[0]
                if(input_menu == 'CS' or input_menu == '[1' or
                   input_menu == 'CG' or input_menu == '[2' or
                   input_menu == 'SM' or input_menu == '[3' or
                   input_menu == 'ST' or input_menu == '[4' or
                   input_menu == 'TS' or input_menu == '[5' or
                   input_menu == 'ED' or input_menu == 'EA' or input_menu == '[6' or
                   input_menu == 'BA' or input_menu == '[0'):
                    if(input_menu == 'CS' or input_menu == '[1'):
                        input_menu = '1'
                    elif(input_menu == 'CG' or input_menu == '[2'):
                        input_menu = '2'
                    elif(input_menu == 'SM' or input_menu == '[3'):
                        input_menu = '3'
                    elif(input_menu == 'ST' or input_menu == '[4'):
                        input_menu = '4'
                    elif(input_menu == 'TS' or input_menu == '[5'):
                        input_menu = '5'
                    elif(input_menu == 'ED' or input_menu == 'EA' or input_menu == '[6'):
                        input_menu = '6'
                    elif(input_menu == 'BA' or input_menu == '[0'):
                        input_menu = '0'
    
        if(input_menu == '1'):
            if(game_selected == ""):
                print(SCRCLR)
                print("Please select the game to play.")
                time.sleep(2)
            else:
                game_change_score_type()
        elif(input_menu == '2'):
            if(game_selected == ""):
                print(SCRCLR)
                print("Please select the game to play.")
                time.sleep(2)
            else:
                game_change_mode()
        elif(input_menu == '3'):
            if(game_selected == ""):
                print(SCRCLR)
                print(text_message_game_max_player_strict)
                time.sleep(2)
            else:
                game_set_max_player()
        elif(input_menu == '4'):
            if(game_selected == ""):
                print(SCRCLR)
                print(text_message_game_max_player_strict)
                time.sleep(2)
            else:
                game_set_max_player_per_team()
        elif(input_menu == '5'):
            if(game_max_player % 2 == 0 and game_max_player / game_max_player_per_team == 2):
                if(game_max_player_strict == 0):
                    game_max_player_strict = 1
                else:
                    game_max_player_strict = 0
            elif(game_max_player % 2 == 1):
                print(SCRCLR)
                print(text_message_game_max_player_uneven)
                time.sleep(2)
            elif(game_max_player / game_max_player_per_team != 2):
                print(SCRCLR)
                print(text_message_game_max_player_team_uneven)
                time.sleep(2)
        elif(input_menu == '6'):
            if(game_selected == ""):
                print(SCRCLR)
                print("Please select the game to play.")
                time.sleep(2)
            else:
                game_edit_info_add()
        elif(input_menu == '0'):
            break

def game_change_score_type():
    global game_score_type_selected

    input_choice = ''
    
    while True:
        input_score_type_select = ""
        
        print(SCRCLR)
        print("[Standard] -- Team with highest score win\n"
              "[Highest Total Point] -- Team with the highest total score win\n"
              "[Highest Player Point] -- Team with the highest point player earned win\n"
              "[Highest Score Ratio] -- Team with the highest total point/score ratio win")
        print("List of available score type(s):")
        for i in range(len(game_score_type_list)):
            print("  [" + str(i + 1) + "]\t" + game_score_type_list[i])
        print("\nSelect the score type from the list.\n"
              "Enter blank to cancel.")
        input_score_type_select = input(text_game_score_type_input)
        if(input_score_type_select.replace(' ','') == ""):
            break
        for i in range(len(game_score_type_list)):
            if(input_score_type_select.lower() == game_score_type_list[i].lower()):
                game_score_type_selected = game_score_type_list[i]
                break
            if(str(i + 1) == input_score_type_select):
                game_score_type_selected = game_score_type_list[i]
                input_score_type_select = ""
                break
        if(input_score_type_select not in game_score_type_list and input_score_type_select != ""):
            print(SCRCLR)
            print("Could not find game with given input: " + input_score_type_select)
            time.sleep(1)
        else:
            break

def game_change_mode():
    global game_mode_selected

    input_choice = ''
    
    while True:
        input_mode_select = ""
        
        print(SCRCLR)
        print("[Competitive] -- Team will be shown in leaderboard\n"
              "[Classic] -- User determine whether to track it into leaderboard\n"
              "[Casual] -- No leaderboard tracking\n"
              "[Custom] -- Uses classic rule")
        print("List of available gamemode(s):")
        for i in range(len(game_mode_list)):
            print("  [" + str(i + 1) + "]\t" + game_mode_list[i])
        print("\nSelect the mode from the list.\n"
              "Enter blank to cancel.")
        input_mode_select = input(text_game_mode_input)
        if(input_mode_select.replace(' ','') == ""):
            break
        for i in range(len(game_mode_list)):
            if(input_mode_select.lower() == game_mode_list[i].lower()):
                game_mode_selected = game_mode_list[i]
                break
            if(str(i + 1) == input_mode_select):
                game_mode_selected = game_mode_list[i]
                input_mode_select = ""
                break
        if(input_mode_select not in game_mode_list and input_mode_select != ""):
            print(SCRCLR)
            print("Unable to find the gamemode with given input.\nAre you going to use " + input_mode_select + "?")
            input_choice = prompt_confirm()
            if(input_choice == 'Y'):
                game_mode_selected = input_mode_select
                break
            input_choice = ''
        if(input_mode_select.replace(' ','') == ""):
            break

def game_set_max_player():
    global game_max_player
    global game_max_player_per_team
    
    temp_counter_1 = 0
    temp_counter_2 = 0

    while True:
        input_number = 0
        
        print(SCRCLR)
        print("\nInput the maximum number of players (Max. 12).\n"
              "Enter blank to cancel.")
        input_number = input(text_max_player_input)
        if(input_number.replace(' ','') == ""):
            break
        if(input_number.isnumeric() == False):
            print(SCRCLR)
            print("Please input an integer.")
            time.sleep(1)
        elif(float(input_number).is_integer() == False):
            print(SCRCLR)
            print("Please input an integer.")
            time.sleep(1)
        else:
            input_number = int(input_number)
            if(input_number > 12):
                print(SCRCLR)
                print("Number exceed the limit.")
                time.sleep(1)
            elif(input_number < 2):
                print(SCRCLR)
                print("Number is too small.")
                time.sleep(1)
            elif(input_number <= 12 and input_number >= 2):
                game_max_player = input_number
                game_max_player_per_team = int((game_max_player / 2 + 0.5) // 1)
                if(len(team_roster_player) > game_max_player):
                    temp_team_roster_player = list(team_roster_player.keys())
                    for i in range(len(temp_team_roster_player)):
                        if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                            temp_counter_1 += 1
                            if(temp_counter_1 > (game_max_player / 2 + 0.5) // 1):
                                del team_roster_player[temp_team_roster_player[i]]
                        elif(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                            temp_counter_2 += 1
                            if(temp_counter_2 > game_max_player / 2):
                                del team_roster_player[temp_team_roster_player[i]]
            break

def game_set_max_player_per_team():
    global game_max_player_per_team
    
    temp_counter_1 = 0
    temp_counter_2 = 0

    while True:
        input_number = 0
        
        print(SCRCLR)
        print("\nInput the maximum number of players per team (Max. " + str(game_max_player - 1) + ").\n"
              "Enter blank to cancel.")
        input_number = input(text_max_player_team_input)
        if(input_number.replace(' ','') == ""):
            break
        if(input_number.isnumeric() == False):
            print(SCRCLR)
            print("Please input an integer.")
            time.sleep(1)
        elif(float(input_number).is_integer() == False):
            print(SCRCLR)
            print("Please input an integer.")
            time.sleep(1)
        else:
            input_number = int(input_number)
            if(input_number >= game_max_player):
                print(SCRCLR)
                print("Number is larger or equal to max player.")
                time.sleep(1)
            elif(input_number < game_max_player / 2):
                print(SCRCLR)
                print("Number is too small.")
                time.sleep(1)
            elif(input_number < game_max_player):
                game_max_player_per_team = input_number
                if(len(team_roster_player) > 0):
                    temp_team_roster_player = list(team_roster_player.keys())
                    for i in range(len(temp_team_roster_player)):
                        if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                            temp_counter_1 += 1
                            if(temp_counter_1 > game_max_player_per_team):
                                del team_roster_player[temp_team_roster_player[i]]
                        elif(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                            temp_counter_2 += 1
                            if(temp_counter_2 > game_max_player_per_team):
                                del team_roster_player[temp_team_roster_player[i]]
                break

# Optional function; used to tell additional information about the match.
def game_edit_info_add():
    global game_info_add

    temp_game_info_add_prev = game_info_add

    print(SCRCLR)
    print("Enter the additional information.\n"
          "Enter blank to cancel.")
    game_info_add = input(text_game_info_input)
    if(game_info_add.replace(' ','') == ""):
        game_info_add = temp_game_info_add_prev

# The game management is a sub-menu
# game_view_game function is to view the list of games
# game_view_alias function is to view the list of alias for the corresponding games
# game_adder function is to add a new game into the game list
# game_name_determiner function is to check whether the name of the game is valid
# game_genre_determiner function is to check whether the genre of the game is valid
# game_alias_adder funtion is to add a new alias to the game
# game_alias_determiner function is to check whether the alias of the newly added game is valid
# game_remover funtion is to remove a game from the game list
# game_alias_remover is to remove an alias of a game in the alias list
# game_name_changer function is to change the name of a game in the game list
# game_genre_changer function is to to change the genre of a game
def game_management():
    while True:
        input_menu = ''
        
        print(SCRCLR)
        display_info_menu()
        if(len(game_name) == 0):
            print(text_message_game_no_game)
        print(text_title_game_management)
        print("[1] View Game\t\t[2] View Alias\n"
              "[3] Add Game\t\t[4] Add Alias\n"
              "[5] Delete Game\t\t[6] Delete Alias\n"
              "[7] Change Game's Name\t[8] Change Game's Genre\n"
              "\n[0] Back\n")
        while(not(input_menu == '1' or input_menu == '2' or input_menu == '3' or input_menu == '4' or input_menu == '5' or
                  input_menu == '6' or input_menu == '7' or input_menu == '8' or input_menu == '0')):
            input_menu = input()
            input_menu = input_menu.upper()
            input_menu = input_menu.replace(' ','')
            if(len(input_menu) > 1):
                input_menu = input_menu[0:2]
                if(input_menu.isnumeric() == True):
                    input_menu = input_menu[0]
                if(input_menu == 'VG' or input_menu == '[1' or
                   input_menu == 'VA' or input_menu == '[2' or
                   input_menu == 'AG' or input_menu == '[3' or
                   input_menu == 'AA' or input_menu == '[4' or
                   input_menu == 'DG' or input_menu == '[5' or
                   input_menu == 'DA' or input_menu == '[6' or
                   input_menu == 'GN' or input_menu == '[7' or
                   input_menu == 'GG' or input_menu == '[8' or
                   input_menu == 'BA' or input_menu == '[0'):
                    if(input_menu == 'VG' or input_menu == '[1'):
                        input_menu = '1'
                    elif(input_menu == 'VA' or input_menu == '[2'):
                        input_menu = '2'
                    elif(input_menu == 'AG' or input_menu == '[3'):
                        input_menu = '3'
                    elif(input_menu == 'AA' or input_menu == '[4'):
                        input_menu = '4'
                    elif(input_menu == 'DG' or input_menu == '[5'):
                        input_menu = '5'
                    elif(input_menu == 'DA' or input_menu == '[6'):
                        input_menu = '6'
                    elif(input_menu == 'GN' or input_menu == '[7'):
                        input_menu = '7'
                    elif(input_menu == 'GG' or input_menu == '[8'):
                        input_menu = '8'
                    elif(input_menu == 'BA' or input_menu == '[0'):
                        input_menu = '0'
    
        if(input_menu == '1'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            else:
                game_view_game()
        elif(input_menu == '2'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            elif(len(game_alias) == 0):
                print(SCRCLR)
                print(text_message_game_no_alias)
                time.sleep(2)
            else:
                game_view_alias()
        elif(input_menu == '3'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                game_adder()
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_menu == '4'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            else:
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    game_alias_adder()
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_menu == '5'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            else:
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    game_remover()
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_menu == '6'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            elif(len(game_alias) == 0):
                print(SCRCLR)
                print(text_message_game_no_alias)
                time.sleep(2)
            else:
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    game_alias_remover()
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_menu == '7'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            else:
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    game_name_changer()
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_menu == '8'):
            if(len(game_name) == 0):
                print(SCRCLR)
                print(text_message_game_no_game)
                time.sleep(2)
            else:
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    game_genre_changer()
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_menu == '0'):
            break

def game_view_game():
    print(SCRCLR)
    print("List of available game(s):")
    for i in range(len(game_name)):
        print("  [" + str(i + 1) + "]\tName: " + game_name[i] + "\n\tGenre: " + game_genre_list[game_name[i]])
    input("\nEnter to exit...")

def game_view_alias():
    print(SCRCLR)
    print("\nList of possible alias(es):")
    for i in range(len(game_alias)):
        print("  [" + str(i + 1) + "]\t" + game_alias[i] + " for " + game_alias_list[game_alias[i]])
    input("\nEnter to exit...")

def game_adder():
    global game_adding_check
    global game_name
    global game_genre
    global game_genre_list
    
    game_adding_check = 1
    input_choice = ''

    while True:
        print(SCRCLR)
        print("Use proper name for the game itself.\n"
              "Input Q or E if you want to cancel.")
        game_name_input = game_name_determiner(text_game_name_input)
        if(game_adding_check == 0):
            break
        
        print(SCRCLR)
        print("Genre must be at least 3-24 characters.\n"
              "Input Q or E if you want to cancel.")
        game_genre_input = game_genre_determiner(text_game_genre_input)
        if(game_adding_check == 0):
            break

        print(SCRCLR)
        print("Game: " + game_name_input)
        print("Genre: " + game_genre_input)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''
    
    if(game_adding_check == 1):
        game_name.append(game_name_input)
        if(game_genre_input not in game_genre):
            game_genre.append(game_genre_input)
        game_genre_list[game_name_input] = game_genre_input
        
        game_adder = open('game_list.txt','a') 
        game_adder.write(game_name_input + "][" + game_genre_input + "\n") 
        game_adder.close

def game_name_determiner(text_game_name):
    global game_adding_check

    temp_input_game_name = ""
    
    while True:
        input_game_name = input(text_game_name)
        if(input_game_name.upper() == "Q" or input_game_name.upper() == "E"):
            game_adding_check = 0
            break
        temp_input_game_name = input_game_name
        for i in range(len(ALLOWED_SYMBOL)):
            temp_input_game_name = temp_input_game_name.replace(ALLOWED_SYMBOL[i],'')
        if(input_game_name == ""):
            print("Please input name.")
        for game_search, game_name_data in game_alias_list.items():
            if(input_game_name.lower().replace(' ','') in game_name_data.lower().replace(' ','')):
                print("Game already existed in the list.")
                input_game_name = ""
                break
        if(temp_input_game_name.replace(' ','').isalnum() == False or input_game_name == ""):
            if(input_game_name.replace(' ','') != ""):
                print("Contains disallowed symbol(s).")
        else:
            break
    
    return input_game_name

def game_genre_determiner(text_game_genre):
    global game_adding_check
    
    print("List of available genre:")
    for i in range(len(game_genre)):
        print("  [" + str(i + 1) + "]\t" + game_genre[i])
    while True:
        input_game_genre = input(text_game_genre)
        if(input_game_genre.upper() == "Q" or input_game_genre.upper() == "E"):
            game_adding_check = 0
            break
        for i in range(len(game_genre)):
            if(str(i + 1) == input_game_genre):
                input_game_genre = game_genre[i]
        if(input_game_genre == ""):
            print("Please input genre.")
        elif(input_game_genre.replace(' ','').isalnum() == False):
            print("No special character allowed.")
        elif(len(input_game_genre) < 2 or len(input_game_genre) > 24):
            print("Genre must be at least 3-24 characters.")
        else:
            break
    
    return input_game_genre

def game_alias_adder():
    global game_adding_check
    global game_alias
    global game_alias_list
    global game_selected
    global game_genre_selected

    game_adding_check = 1
    input_choice = ''
    temp_game_selected_prev = game_selected
    temp_game_genre_selected_prev = game_genre_selected
    
    while True:
        game_selected = ""
        game_genre_selected = ""
        game_selector()
        if(game_selected == ""):
            game_adding_check = 0
            break
        
        print(SCRCLR)
        print("Give an alias for " + game_selected + ".\n"
              "Input Q or E if you want to cancel.")
        game_alias_input = game_alias_determiner()
        if(game_adding_check == 0):
            break

        print(SCRCLR)
        print("Giving " + game_alias_input + " alias to " + game_selected + ".")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(game_adding_check == 1):
        game_alias.append(game_alias_input)
        game_alias_list[game_alias_input] = game_selected
        
        game_alias_add = open('game_list.txt').read()
        game_alias_add = game_alias_add.replace(game_selected + "][" + game_genre_selected,
                                                game_selected + "][" + game_genre_selected + "]" + game_alias_input + "[")
        game_list_change = open('game_list.txt','w')
        game_list_change.write(game_alias_add)
        game_list_change.close()
    
    game_selected = ""
    game_genre_selected = ""

def game_alias_determiner():
    global game_adding_check
    
    while True:
        input_game_alias = input()
        if(input_game_alias.upper() == "Q" or input_game_alias.upper() == "E"):
            game_adding_check = 0
            break
        input_game_alias = input_game_alias.lower().replace(' ','')
        if(input_game_alias == ""):
            print("Please input alias.")
        elif(input_game_alias in game_alias):
            print("Alias already existed in the list.")
        elif(input_game_alias.replace(' ','').isalnum() == False and input_game_alias != ""):
            print("No special character allowed.")
        else:
            break
    
    return input_game_alias

def game_remover():
    global game_name
    global game_genre
    global game_alias
    global game_genre_list
    global game_selected
    global game_genre_selected

    input_choice = ''
    temp_game_alias = ""
    temp_game_alias_list = []
    temp_game_genre_list = []
    temp_game_selected_prev = game_selected
    temp_game_genre_selected_prev = game_genre_selected
    
    while True:
        game_selected = ""
        game_genre_selected = ""
        game_selector()
        if(game_selected == ""):
            game_adding_check = 0
            break

        print(SCRCLR)
        print("Game to remove: " + game_selected)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            if(game_selected not in game_name):
                print(SCRCLR)
                print("Could not find game with given input: " + game_selected)
                time.sleep(1)
                break
            
            for i in range(len(game_alias_list)):
                if(game_selected == game_alias_list[game_alias[i]]):
                    temp_game_alias = temp_game_alias + "]" + game_alias[i] + "["
                    temp_game_alias_list.append(game_alias[i])
            game_name.remove(game_selected)
            del game_genre_list[game_selected]
            for i in range(len(game_alias_list)):
                if(game_selected == game_alias_list[game_alias[i]]):
                    del game_alias_list[game_alias[i]]
            for i in range(len(temp_game_alias_list)):
                game_alias.remove(temp_game_alias_list[i])
            for i in range(len(game_genre)):
                for j in range(len(game_genre_list)):
                    if(game_genre_list[game_name[j]] == game_genre[i] and game_genre[i] not in temp_game_genre_list):
                        temp_game_genre_list.append(game_genre[i])
            if(game_genre_selected not in temp_game_genre_list):
                game_genre.remove(game_genre_selected)
            
            game_remove = open('game_list.txt').read()
            game_remove = game_remove.replace(game_selected + "][" + game_genre_selected + temp_game_alias + "\n",
                                              "")
            game_list_remove = open('game_list.txt','w')
            game_list_remove.write(game_remove)
            game_list_remove.close()
            break
        input_choice = ''
    
    game_selected = ""
    game_genre_selected = ""

def game_alias_remover():
    global game_adding_check
    global game_alias
    global game_alias_list
    global game_selected

    game_adding_check = 1
    input_choice = ''
    
    while True:
        print(SCRCLR)
        for i in range(len(game_alias)):
            print("  [" + str(i + 1) + "]\t" + game_alias[i] + " for " + game_alias_list[game_alias[i]])
        print("\nInput the alias to remove.\n"
              "Input Q or E if you want to cancel.")
        while True:
            input_game_alias = input()
            if(input_game_alias.upper() == "Q" or input_game_alias.upper() == "E"):
                game_adding_check = 0
                break
            input_game_alias = input_game_alias.lower().replace(' ','')
            if(input_game_alias == ""):
                print("Please input alias.")
            for i in range(len(game_alias)):
                if(str(i + 1) == input_game_alias):
                    input_game_alias = game_alias[i]
                    break
            if(input_game_alias in game_alias):
                break
            else:
                print("Could not find alias with given input: " + input_game_alias)
        if(game_adding_check == 0):
            break

        print(SCRCLR)
        print("Game to remove alias: " + game_selected)
        print("Removing " + input_game_alias + " alias from " + game_alias_list[input_game_alias] + ".")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(game_adding_check == 1):
        game_alias.remove(input_game_alias)
        del game_alias_list[input_game_alias]
        
        game_alias_remove = open('game_list.txt').read()
        game_alias_remove = game_alias_remove.replace("]" + input_game_alias + "[",
                                                      "")
        game_list_change = open('game_list.txt','w')
        game_list_change.write(game_alias_remove)
        game_list_change.close()

def game_name_changer():
    global game_name
    global game_genre_list
    global game_selected
    global game_genre_selected

    input_choice = ''
    temp_game_selected_prev = game_selected
    temp_game_genre_selected_prev = game_genre_selected
    
    while True:
        game_selected = ""
        game_genre_selected = ""
        game_selector()
        if(game_selected == ""):
            game_adding_check = 0
            break
        
        print(SCRCLR)
        print("Use proper name for the game itself.\n"
              "Input Q or E if you want to cancel.")
        game_name_input = game_name_determiner(text_game_name_new)
        if(game_name_input.upper() == "Q" or game_name_input.upper() == "E"):
            break

        print(SCRCLR)
        print("Game to change name: " + game_selected)
        print("Changing name from " + game_selected + " to " + game_name_input + ".")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            game_name.remove(game_selected)
            game_name.append(game_name_input)
            del game_genre_list[game_selected]
            game_genre_list[game_name_input] = game_genre_selected
            
            game_name_change = open('game_list.txt').read()
            game_name_change = game_name_change.replace(game_selected + "][" + game_genre_selected,
                                                        game_name_input + "][" + game_genre_selected)
            game_list_change = open('game_list.txt','w')
            game_list_change.write(game_name_change)
            game_list_change.close()
            break
        input_choice = ''
    
    game_selected = ""
    game_genre_selected = ""

def game_genre_changer():
    global game_genre
    global game_genre_list
    global game_selected
    global game_genre_selected

    input_choice = ''
    temp_game_selected_prev = game_selected
    temp_game_genre_selected_prev = game_genre_selected
    
    while True:
        game_selected = ""
        game_genre_selected = ""
        game_selector()
        if(game_selected == ""):
            game_adding_check = 0
            break

        temp_game_genre_prev = game_genre_selected
        
        print(SCRCLR)
        print("Genre must be at least 3-24 characters.\n"
              "Input Q or E if you want to cancel.")
        game_genre_input = game_genre_determiner(text_game_genre_new)
        if(game_genre_input.upper() == "Q" or game_genre_input.upper() == "E"):
            break

        print(SCRCLR)
        print("Game to change genre: " + game_selected)
        print("Changing genre from " + temp_game_genre_prev + " to " + game_genre_input + ".")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            game_genre_list[game_selected] = game_genre_input
            if(game_genre_input not in game_genre):
                game_genre.append(game_genre_input)
            
            game_genre_change = open('game_list.txt').read()
            game_genre_change = game_genre_change.replace(game_selected + "][" + temp_game_genre_prev,
                                                          game_selected + "][" + game_genre_input)
            game_list_change = open('game_list.txt','w')
            game_list_change.write(game_genre_change)
            game_list_change.close()
            break
        input_choice = ''
    
    game_selected = ""
    game_genre_selected = ""

# Part of the main module, this is the team system
# team_roster_add_team function is to add a team for a game
# team_roster_remove_team function is to remove a team for a game
# team_roster_add_player function is to add a player in a team for a game
# team_roster_remove_player function isto remove a player in a team for a game
def team_management():
    while True:
        input_menu = ''
        
        print(SCRCLR)
        display_info_menu()
        if(len(team_list) <= 1):
            print(text_message_team_no_team)
        elif(len(player_list) == 0):
            print(text_message_team_no_player)
        print(text_title_team_management)
        print("[1] View Teams\t\t[2] View Players\n"
              "[3] Add Team Playing\t[4] Add Player to Roster\n"
              "[5] Remove Team Playing\t[6] Remove Player from Roster\n"
              "\n\t\t[7] Manage Teams\n"
              "\n[0] Back\n")
        while(not(input_menu == '1' or input_menu == '2' or input_menu == '3' or input_menu == '4' or 
                  input_menu == '5' or input_menu == '6' or input_menu == '7' or input_menu == '0')):
            input_menu = input()
            input_menu = input_menu.upper()
            input_menu = input_menu.replace(' ','')
            if(len(input_menu) > 1):
                input_menu = input_menu[0:2]
                if(input_menu.isnumeric() == True):
                    input_menu = input_menu[0]
                if(input_menu == 'AT' or input_menu == '[1' or
                   input_menu == 'AP' or input_menu == '[2' or
                   input_menu == 'RT' or input_menu == '[3' or
                   input_menu == 'RP' or input_menu == '[4' or
                   input_menu == 'MT' or input_menu == 'MA' or input_menu == '[5' or
                   input_menu == 'VT' or input_menu == '[6' or
                   input_menu == 'VP' or input_menu == '[7' or
                   input_menu == 'BA' or input_menu == '[0'):
                    if(input_menu == 'VT' or input_menu == '[1'):
                        input_menu = '1'
                    elif(input_menu == 'VP' or input_menu == '[2'):
                        input_menu = '2'
                    elif(input_menu == 'AT' or input_menu == '[3'):
                        input_menu = '3'
                    elif(input_menu == 'AP' or input_menu == '[4'):
                        input_menu = '4'
                    elif(input_menu == 'RT' or input_menu == '[5'):
                        input_menu = '5'
                    elif(input_menu == 'RP' or input_menu == '[6'):
                        input_menu = '6'
                    elif(input_menu == 'MT' or input_menu == 'MA' or input_menu == '[7'):
                        input_menu = '7'
                    elif(input_menu == 'BA' or input_menu == '[0'):
                        input_menu = '0'
    
        if(input_menu == '1'):
            if(len(team_list) <= 1):
                print(SCRCLR)
                print(text_message_team_no_team)
                time.sleep(2)
            else:
                team_view_teams()
        elif(input_menu == '2'):
            if(len(player_list) == 0):
                print(SCRCLR)
                print(text_message_team_no_player)
                time.sleep(2)
            else:
                team_view_players()
        elif(input_menu == '3'):
            if(len(team_list) <= 1):
                print(SCRCLR)
                print(text_message_team_no_team)
                time.sleep(2)
            elif(len(team_roster_team) == 2):
                print(SCRCLR)
                print(text_message_team_full_team)
                time.sleep(2)
            else:
                team_roster_add_team()
        elif(input_menu == '4'):
            if(len(player_list) == 0):
                print(SCRCLR)
                print(text_message_team_no_player)
                time.sleep(2)
            elif(len(team_roster_team) == 0):
                print(SCRCLR)
                print(text_message_team_no_team_select)
                time.sleep(2)
            elif(len(team_roster_team) == 1):
                print(SCRCLR)
                print(text_message_team_one_team_select)
                time.sleep(2)
            elif(len(team_roster_player) == game_max_player):
                print(SCRCLR)
                print(text_message_team_maxed_player)
                time.sleep(2)
            else:
                team_roster_add_player()
        elif(input_menu == '5'):
            if(len(team_list) <= 1):
                print(SCRCLR)
                print(text_message_team_no_team)
                time.sleep(2)
            elif(len(team_roster_team) == 0):
                print(SCRCLR)
                print(text_message_team_no_team_select)
                time.sleep(2)
            else:
                team_roster_remove_team()
        elif(input_menu == '6'):
            if(len(player_list) == 0):
                print(SCRCLR)
                print(text_message_team_no_player)
                time.sleep(2)
            elif(len(team_roster_team) == 0):
                print(SCRCLR)
                print(text_message_team_no_team_select)
                time.sleep(2)
            elif(len(team_roster_team) == 1):
                print(SCRCLR)
                print(text_message_team_one_team_select)
                time.sleep(2)
            elif(len(team_roster_player) == 0):
                print(SCRCLR)
                print(text_message_team_no_player_select)
                time.sleep(2)
            else:
                team_roster_remove_player()
        elif(input_menu == '7'):
            team_manage()
        elif(input_menu == '0'):
            break

def team_roster_add_team():
    global team_adding_check
    global team_roster_team

    team_adding_check = 1
    input_choice_team = ''
    
    print(SCRCLR)
    print("List of available team(s): ")
    for i in range(len(team_list)):
        if(i != 0):
            print("  [" + str(i) + "]\t" + team_list[i])
    print("\nChoose the team to play."
          "\nEnter blank to cancel.")
    while True:
        input_choice_team = input(text_team_name_input)
        if(input_choice_team.replace(' ','') == ""):
            team_adding_check = 0
            break
        for i in range(len(team_list)):
            if(str(i) == input_choice_team and i != 0):
                input_choice_team = team_list[i]
                break
        if(input_choice_team in team_list):
            if(input_choice_team not in team_roster_team):
                break
            else:
                print("The team is already being selected.")
        else:
            print("Could not find team with given input: " + input_choice_team)

    if(team_adding_check == 1):
        if(len(team_roster_team) == 2):
            team_roster_team.remove(team_roster_team[0])
        team_roster_team.append(team_list[i])

def team_roster_remove_team():
    global team_adding_check
    global team_roster_team

    team_adding_check = 1
    input_choice_team = ''
    
    print(SCRCLR)
    print("Team(s) playing: ")
    for i in range(len(team_roster_team)):
        print("  [" + str(i + 1) + "]\t" + team_roster_team[i])
    print("\nChoose the team to remove from playing."
          "\nEnter blank to cancel.")
    while True:
        input_choice_team = input(text_team_name_input)
        if(input_choice_team.replace(' ','') == ""):
            team_adding_check = 0
            break
        for i in range(len(team_roster_team)):
            if(str(i + 1) == input_choice_team):
                input_choice_team = team_roster_team[i]
                break
        if(input_choice_team in team_roster_team):
            break
        else:
            print("Could not find team with given input: " + input_choice_team)

    if(team_adding_check == 1):
        team_roster_team.remove(input_choice_team)
        if(len(team_roster_player) > 0):
            for i in range(len(player_list)):
                if(input_choice_team == team_player_list[player_list[i]] and player_list[i] in team_roster_player):
                    if(input_choice_team == team_roster_player[player_list[i]]):
                        del team_roster_player[player_list[i]]

def team_roster_add_player():
    global team_adding_check
    global team_roster_player

    team_adding_check = 1
    input_choice_player = ''
    temp_counter = 0
    temp_counter_1 = 0
    temp_counter_2 = 0
    
    print(SCRCLR)
    print("List of available player(s): ")
    for i in range(len(player_list)):
        for j in range(len(team_roster_team)):
            if(team_roster_team[j] == team_player_list[player_list[i]]):
                temp_counter += 1
                print("  [" + str(temp_counter) + "]\t[" + team_roster_team[j] + "] " + player_list[i])
    print("\nChoose the player in team to play."
          "\nEnter blank to cancel.")
    while True:
        temp_counter = 0

        input_choice_player = input(text_team_player_input)
        if(input_choice_player.replace(' ','') == ""):
            team_adding_check = 0
            break
        for i in range(len(player_list)):
            for j in range(len(team_roster_team)):
                if(team_roster_team[j] == team_player_list[player_list[i]]):
                    temp_counter += 1
                    if(str(temp_counter) == input_choice_player):
                        input_choice_player = player_list[i]
                    break
        if(input_choice_player in player_list):
            if(input_choice_player not in team_roster_player):
                break
            else:
                print("The player is already being selected.")
        else:
            print("Could not find player with given input: " + input_choice_player)

    if(team_adding_check == 1):
        temp_team_roster_player = list(team_roster_player.keys())
        for i in range(len(temp_team_roster_player)):
            if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                temp_counter_1 += 1
            elif(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                temp_counter_2 += 1
        if(temp_counter_1 != game_max_player_per_team and team_player_list[input_choice_player] == team_roster_team[0]):
            team_roster_player[input_choice_player] = team_player_list[input_choice_player]
        elif(temp_counter_2 != game_max_player_per_team and team_player_list[input_choice_player] == team_roster_team[1]):
            team_roster_player[input_choice_player] = team_player_list[input_choice_player]
        else:
            print(SCRCLR)
            print("Max player per team amount reached limit: " + str(game_max_player_per_team))
            time.sleep(2)

def team_roster_remove_player():
    global team_adding_check
    global team_roster_player

    team_adding_check = 1
    input_choice_player = ''
    temp_counter = 0
    
    print(SCRCLR)
    print("List of available player(s): ")
    temp_team_roster_player = list(team_roster_player.keys())
    for i in range(len(temp_team_roster_player)):
        for j in range(len(team_roster_team)):
            if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[j]):
                temp_counter += 1
                print("  [" + str(temp_counter) + "]\t[" + team_roster_team[j] + "] " + temp_team_roster_player[i])
    print("\nChoose the player in team to remove from playing."
          "\nEnter blank to cancel.")
    while True:
        temp_counter = 0

        input_choice_player = input(text_team_player_input)
        if(input_choice_player.replace(' ','') == ""):
            team_adding_check = 0
            break
        for i in range(len(player_list)):
            for j in range(len(team_roster_team)):
                if(team_roster_team[j] == team_player_list[player_list[i]] and player_list[i] in team_roster_player):
                    if(team_roster_player[player_list[i]] == team_roster_team[0]):
                        temp_counter += 1
                        if(str(temp_counter) == input_choice_player):
                            input_choice_player = player_list[i]
                    elif(team_roster_player[player_list[i]] == team_roster_team[1]):
                        temp_counter += 1
                        if(str(temp_counter) == input_choice_player):
                            input_choice_player = player_list[i]
        if(input_choice_player in team_roster_player):
            break
        else:
            print("Could not find player with given input: " + input_choice_player)

    if(team_adding_check == 1):
        del team_roster_player[input_choice_player]

# This is the part to manage the team and the players for their correspoding team
# team_add_team() function is to add teams in the team management menu
# team_name_determiner function is to check whether the name of the teams are valid
# team_add_player() function is to add players into a team in the team management menu
# team_player_determiner function is to check whether the name of the player is valid
# team_swap_player() function to swap the players to another team
# team_change_team_name() function is to change the name of the teams 
# team_change_player_name() function is to change the name of the players 
# team_delete_team() function is to remove a team in the team list
# team_delete_player() function is to remove a player in the player list
# team_view_teams function is to view the team list
# team_view_players function is to view the player list
def team_manage():
    while True:
        input_menu = ''
        
        print(SCRCLR)
        display_info_menu()
        if(len(team_list) <= 1):
            print(text_message_team_no_team)
        elif(len(player_list) == 0):
            print(text_message_team_no_player)
        print(text_title_team_manage)
        print("[1] View Teams\t\t[2] View Players\n"
              "[3] Add Team\t\t[4] Add Player\n"
              "[5] Swap Player\n\n"
              "[6] Change Team Name\t[7] Change Player Name\n"
              "[8] Delete Team\t\t[9] Delete Player\n"
              "\n[0] Back\n")
        while(not(input_menu == '1' or input_menu == '2' or input_menu == '3' or input_menu == '4' or input_menu == '5' or
                  input_menu == '6' or input_menu == '7' or input_menu == '8' or input_menu == '9' or input_menu == '0')):
            input_menu = input()
            input_menu = input_menu.upper()
            input_menu = input_menu.replace(' ','')
            if(len(input_menu) > 1):
                input_menu = input_menu[0:2]
                if(input_menu.isnumeric() == True):
                    input_menu = input_menu[0]
                if(input_menu == 'VT' or input_menu == '[1' or
                   input_menu == 'VP' or input_menu == '[2' or
                   input_menu == 'AT' or input_menu == '[3' or
                   input_menu == 'AP' or input_menu == '[4' or
                   input_menu == 'SW' or input_menu == 'SP' or input_menu == '[5' or
                   input_menu == 'CT' or input_menu == '[6' or
                   input_menu == 'CP' or input_menu == '[7' or
                   input_menu == 'DT' or input_menu == '[8' or
                   input_menu == 'DP' or input_menu == '[9' or
                   input_menu == 'BA' or input_menu == '[0'):
                    if(input_menu == 'VT' or input_menu == '[1'):
                        input_menu = '1'
                    elif(input_menu == 'VP' or input_menu == '[2'):
                        input_menu = '2'
                    elif(input_menu == 'AT' or input_menu == '[3'):
                        input_menu = '3'
                    elif(input_menu == 'AP' or input_menu == '[4'):
                        input_menu = '4'
                    elif(input_menu == 'SW' or input_menu == 'SP' or input_menu == '[5'):
                        input_menu = '5'
                    elif(input_menu == 'CT' or input_menu == '[6'):
                        input_menu = '6'
                    elif(input_menu == 'CP' or input_menu == '[7'):
                        input_menu = '7'
                    elif(input_menu == 'DT' or input_menu == '[8'):
                        input_menu = '8'
                    elif(input_menu == 'DP' or input_menu == '[9'):
                        input_menu = '9'
                    elif(input_menu == 'BA' or input_menu == '[0'):
                        input_menu = '0'
    
        if(input_menu == '1'):
            if(len(team_list) <= 1):
                print(SCRCLR)
                print(text_message_team_no_team)
                time.sleep(2)
            else:
                team_view_teams()
        elif(input_menu == '2'):
            if(len(player_list) == 0):
                print(SCRCLR)
                print(text_message_team_no_player)
                time.sleep(2)
            else:
                team_view_players()
        elif(input_menu == '3'):      
            team_add_team()
        elif(input_menu == '4'):
            team_add_player()
        elif(input_menu == '5'):
            if(len(player_list) == 0):
                print(SCRCLR)
                print(text_message_team_no_player)
                time.sleep(2)
            else:
                team_swap_player()
        elif(input_menu == '6'):
            if(len(team_list) <= 1):
                print(SCRCLR)
                print(text_message_team_no_team)
                time.sleep(2)
            else:
                team_change_team_name()
        elif(input_menu == '7'):
            if(len(player_list) == 0):
                print(SCRCLR)
                print(text_message_team_no_player)
                time.sleep(2)
            else:
                team_change_player_name()
        elif(input_menu == '8'):
            if(len(team_list) <= 1):
                print(SCRCLR)
                print(text_message_team_no_team)
                time.sleep(2)
            else:
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    team_delete_team()
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_menu == '9'):
            if(len(player_list) == 0):
                print(SCRCLR)
                print(text_message_team_no_player)
                time.sleep(2)
            else:
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    team_delete_player()
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_menu == '0'):
            break

def team_add_team():
    global team_adding_check
    global team_list
    
    team_adding_check = 1
    input_choice = ''

    while True:
        print(SCRCLR)
        print("Use unique team name.\n"
              "Input Q or E if you want to cancel.")
        team_name_input = team_name_determiner(text_team_name_input)
        if(team_adding_check == 0):
            break

        print(SCRCLR)
        print("Team name: " + team_name_input)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''
    
    if(team_adding_check == 1):
        team_list.append(team_name_input)
        
        team_name_adder = open('team_player_list.txt','a') 
        team_name_adder.write("==TEAM========\n"
                              + team_name_input +
                              "\n==PLAYER======\n"
                              "==============\n\n")
        team_name_adder.close

def team_name_determiner(text_team_name):
    global team_adding_check

    temp_input_team_name  = ""
    
    while True:
        input_team_name = input(text_team_name)
        if(input_team_name.upper() == "Q" or input_team_name.upper() == "E"):
            team_adding_check = 0
            break
        temp_input_team_name = input_team_name
        for i in range(len(ALLOWED_SYMBOL)):
            temp_input_team_name = temp_input_team_name.replace(ALLOWED_SYMBOL[i],'')
        if(input_team_name == ""):
            print("Please input name.")
        if(input_team_name.replace(' ','').lower() == "unassigned"):
            print("You cannot use that team name.")
        for i in range(len(team_list)):
            if(input_team_name.lower() == team_list[i].lower()):
                print("Team already existed in the list.")
                input_team_name = ""
                break
        for i in range(len(player_list)):
            if(input_team_name.lower() == player_list[i].lower()):
                print("Team name must not be the same as the player.")
                input_team_name = ""
                break
        if(temp_input_team_name.replace(' ','').isalnum() == False or input_team_name == ""):
            if(input_team_name.replace(' ','') != ""):
                print("Contains disallowed symbol(s).")
        else:
            break
    
    return input_team_name

def team_add_player():
    global team_adding_check
    global player_list
    global team_player_list

    team_adding_check = 1
    input_choice = ''
    input_choice_team = ''
    
    while True:
        print(SCRCLR)
        print("Use unique player name."
              "\nInput Q or E if you want to cancel.")
        team_player_input = team_player_determiner(text_team_player_input)
        if(team_adding_check == 0):
            break
        
        print(SCRCLR)
        print("List of available team(s): ")
        for i in range(len(team_list)):
            if(i != 0):
                print("  [" + str(i) + "]\t" + team_list[i])
        print("\nChoose the team for " + team_player_input + " to join."
              "\nEnter blank to move them to unassigned."
              "\nInput Q or E if you want to cancel.")
        while True:
            input_choice_team = input(text_team_name_input)
            if(input_choice_team.replace(' ','') == ""):
                input_choice_team = "Unassigned"
                break
            if(input_choice_team.upper() == 'Q' or input_choice_team.upper() == 'E'):
                team_adding_check = 0
                break
            for i in range(len(team_list)):
                if(str(i) == input_choice_team and i != 0):
                    input_choice_team = team_list[i]
                    break
            if(input_choice_team in team_list):
                break
            else:
                print("Could not find team with given input: " + input_choice_team)
        if(team_adding_check == 0):
            break

        print(SCRCLR)
        print("Player name: " + team_player_input)
        print("Assigning to " + input_choice_team)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(team_adding_check == 1):
        player_list.append(team_player_input)
        team_player_list[team_player_input] = input_choice_team
            
        team_player_adder = open('team_player_list.txt').read()
        team_player_adder = team_player_adder.replace("==TEAM========\n"
                                                      + input_choice_team +
                                                      "\n==PLAYER======\n",
                                                      "==TEAM========\n"
                                                      + input_choice_team +
                                                      "\n==PLAYER======\n"
                                                      + team_player_input + "\n")
        team_player_change = open('team_player_list.txt','w')
        team_player_change.write(team_player_adder)
        team_player_change.close()

def team_player_determiner(text_team_player):
    global team_adding_check

    temp_input_player_name = ""
    
    while True:
        input_player_name = input(text_team_player)
        if(input_player_name.upper() == "Q" or input_player_name.upper() == "E"):
            team_adding_check = 0
            break
        temp_input_player_name = input_player_name
        for i in range(len(ALLOWED_SYMBOL)):
            temp_input_player_name = temp_input_player_name.replace(ALLOWED_SYMBOL[i],'')
        if(input_player_name == ""):
            print("Please input name.")
        for i in range(len(player_list)):
            if(input_player_name.lower() == player_list[i].lower()):
                print("Player already existed in the list.")
                input_player_name = ""
                break
        for i in range(len(team_list)):
            if(input_player_name.lower() == team_list[i].lower()):
                print("Player name must not be the same as the team.")
                input_player_name = ""
                break
        if(temp_input_player_name.replace(' ','').isalnum() == False or input_player_name == ""):
            if(input_player_name.replace(' ','') != ""):
                print("Contains disallowed symbol(s).")
        else:
            break
    
    return input_player_name

def team_swap_player():
    global team_adding_check
    global player_list
    global team_player_list

    team_adding_check = 1
    input_choice = ''
    input_choice_player = ''
    input_choice_team = ''
    
    while True:
        print(SCRCLR)
        print("List of available player(s): ")
        for i in range(len(player_list)):
            print("  [" + str(i + 1) + "]\t[" + team_player_list[player_list[i]] + "] " + player_list[i])
        print("\nChoose the player to swap."
              "\nInput Q or E if you want to cancel.")
        while True:
            input_choice_player = input(text_team_player_input)
            if(input_choice_player.replace(' ','') == ""):
                print("Please input player name or ID.")
            if(input_choice_player.upper() == 'Q' or input_choice_player.upper() == 'E'):
                team_adding_check = 0
                break
            for i in range(len(player_list)):
                if(str(i + 1) == input_choice_player):
                    input_choice_player = player_list[i]
                    break
            if(input_choice_player in player_list):
                break
            else:
                print("Could not find player with given input: " + input_choice_player)
        if(team_adding_check == 0):
            break
        
        print(SCRCLR)
        print("List of available team(s): ")
        for i in range(len(team_list)):
            if(i != 0):
                print("  [" + str(i) + "]\t" + team_list[i])
        print("\nChoose the team for " + input_choice_player + " to join."
              "\nEnter blank to move them to unassigned."
              "\nInput Q or E if you want to cancel.")
        while True:
            input_choice_team = input(text_team_name_input)
            if(input_choice_team.replace(' ','') == ""):
                input_choice_team = "Unassigned"
                break
            if(input_choice_team.upper() == 'Q' or input_choice_team.upper() == 'E'):
                team_adding_check = 0
                break
            for i in range(len(team_list)):
                if(str(i) == input_choice_team and i != 0):
                    input_choice_team = team_list[i]
                    break
            if(input_choice_team in team_list):
                break
            else:
                print("Could not find team with given input: " + input_choice_team)
        if(team_adding_check == 0):
            break

        print(SCRCLR)
        print("Swapping " + input_choice_player + " from " + team_player_list[input_choice_player] + " to " + input_choice_team + ".")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(team_adding_check == 1):
        if(input_choice_player in team_roster_player):
            del team_roster_player[input_choice_player]
        del team_player_list[input_choice_player]
        team_player_list[input_choice_player] = input_choice_team
        
        team_player_swapper = open('team_player_list.txt').read()
        team_player_swapper = team_player_swapper.replace(input_choice_player + "\n",""
                                                          ).replace("==TEAM========\n"
                                                          + input_choice_team +
                                                          "\n==PLAYER======\n",
                                                          "==TEAM========\n"
                                                          + input_choice_team +
                                                          "\n==PLAYER======\n"
                                                          + input_choice_player + "\n")
        team_player_change = open('team_player_list.txt','w')
        team_player_change.write(team_player_swapper)
        team_player_change.close()

def team_change_team_name():
    global team_adding_check
    global team_list
    global team_player_list

    team_adding_check = 1
    input_choice = ''
    input_choice_team = ''
    
    while True:
        print(SCRCLR)
        print("List of available team(s): ")
        for i in range(len(team_list)):
            if(i != 0):
                print("  [" + str(i) + "]\t" + team_list[i])
        print("\nChoose the team to change name."
              "\nInput Q or E if you want to cancel.")
        while True:
            input_choice_team = input(text_team_name_input)
            if(input_choice_team.replace(' ','') == ""):
                print("Please input team name.")
            if(input_choice_team.replace(' ','').lower() == "unassigned"):
                print("You cannot change that team name.")
                input_choice_team = ""
            if(input_choice_team.upper() == 'Q' or input_choice_team.upper() == 'E'):
                team_adding_check = 0
                break
            for i in range(len(team_list)):
                if(str(i) == input_choice_team and i != 0):
                    input_choice_team = team_list[i]
                    break
            if(input_choice_team in team_list):
                break
            else:
                print("Could not find team with given input: " + input_choice_team)
        if(team_adding_check == 0):
            break
        
        print(SCRCLR)
        print("Use unique team name.\n"
              "Input Q or E if you want to cancel.")
        team_name_input = team_name_determiner(text_team_name_new)
        if(team_adding_check == 0):
            break

        print(SCRCLR)
        print("Changing team name from " + input_choice_team + " to " + team_name_input + ".")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(team_adding_check == 1):
        if(input_choice_team in team_roster_team):
            if(len(team_roster_player) > 0):
                for i in range(len(player_list)):
                    if(input_choice_team == team_player_list[player_list[i]] and player_list[i] in team_roster_player):
                        if(team_roster_player[player_list[i]] == input_choice_team):
                            team_roster_player[player_list[i]] = team_name_input
            team_roster_team.remove(input_choice_team)
            team_roster_team.append(team_name_input)
        if(input_choice_team in leaderboard_team):
            leaderboard_team[team_name_input] = leaderboard_team[input_choice_team]
            del leaderboard_team[input_choice_team]
        team_list.remove(input_choice_team)
        team_list.append(team_name_input)
        for i in range(len(player_list)):
            if(team_player_list[player_list[i]] == input_choice_team):
                del team_player_list[player_list[i]]
                team_player_list[player_list[i]] = team_name_input
                if(player_list[i] in team_roster_player):
                    team_roster_player[player_list[i]] = team_name_input
            
        team_name_changer = open('team_player_list.txt').read()
        team_name_changer = team_name_changer.replace("==TEAM========\n"
                                                      + input_choice_team +
                                                      "\n==PLAYER======\n",
                                                      "==TEAM========\n"
                                                      + team_name_input +
                                                      "\n==PLAYER======\n")
        team_player_change = open('team_player_list.txt','w')
        team_player_change.write(team_name_changer)
        team_player_change.close()

def team_change_player_name():
    global team_adding_check
    global player_list
    global team_player_list

    team_adding_check = 1
    input_choice = ''
    input_choice_player = ''
    temp_team_prev = ""
    
    while True:
        print(SCRCLR)
        print("List of available player(s): ")
        for i in range(len(player_list)):
            print("  [" + str(i + 1) + "]\t[" + team_player_list[player_list[i]] + "] " + player_list[i])
        print("\nChoose the player to change name."
              "\nInput Q or E if you want to cancel.")
        while True:
            input_choice_player = input(text_team_player_input)
            if(input_choice_player.replace(' ','') == ""):
                print("Please input player name or ID.")
            if(input_choice_player.upper() == 'Q' or input_choice_player.upper() == 'E'):
                team_adding_check = 0
                break
            for i in range(len(player_list)):
                if(str(i + 1) == input_choice_player):
                    input_choice_player = player_list[i]
                    break
            if(input_choice_player in player_list):
                break
            else:
                print("Could not find player with given input: " + input_choice_player)
        if(team_adding_check == 0):
            break
        
        print(SCRCLR)
        print("Use unique player name."
              "\nInput Q or E if you want to cancel.")
        team_player_input = team_player_determiner(text_team_player_new)
        if(team_adding_check == 0):
            break

        print(SCRCLR)
        print("Changing player name from " + input_choice_player + " to " + team_player_input + ".")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(team_adding_check == 1):
        if(input_choice_player in team_roster_player):
            team_roster_player[team_player_input] = team_roster_player[input_choice_player]
            del team_roster_player[input_choice_player]
        if(input_choice_player in leaderboard_player):
            leaderboard_player[team_player_input] = leaderboard_player[input_choice_player]
            del leaderboard_player[input_choice_player]
        for i in range(len(player_list)):
            if(team_player_list[input_choice_player] == team_player_list[player_list[i]]):
                temp_team_prev = team_player_list[input_choice_player]
                break
        player_list.remove(input_choice_player)
        player_list.append(team_player_input)
        del team_player_list[input_choice_player]
        team_player_list[team_player_input] = temp_team_prev
            
        team_player_changer = open('team_player_list.txt').read()
        team_player_changer = team_player_changer.replace(input_choice_player, team_player_input)
        team_player_change = open('team_player_list.txt','w')
        team_player_change.write(team_player_changer)
        team_player_change.close()

def team_delete_team():
    global team_adding_check
    global team_list
    global team_player_list

    team_adding_check = 1
    input_choice = ''
    input_choice_team = ''
    temp_player_list = ""
    
    while True:
        print(SCRCLR)
        print("List of available team(s): ")
        for i in range(len(team_list)):
            if(i != 0):
                print("  [" + str(i) + "]\t" + team_list[i])
        print("\nChoose the team to delete."
              "\nInput Q or E if you want to cancel.")
        while True:
            input_choice_team = input(text_team_name_input)
            if(input_choice_team.replace(' ','') == ""):
                print("Please input team name.")
            if(input_choice_team.replace(' ','').lower() == "unassigned"):
                print("You cannot delete that team name.")
                input_choice_team = ""
            if(input_choice_team.upper() == 'Q' or input_choice_team.upper() == 'E'):
                team_adding_check = 0
                break
            for i in range(len(team_list)):
                if(str(i) == input_choice_team and i != 0):
                    input_choice_team = team_list[i]
                    break
            if(input_choice_team in team_list):
                break
            else:
                print("Could not find team with given input: " + input_choice_team)
        
        print(SCRCLR)
        print("Team to remove: " + input_choice_team)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(team_adding_check == 1):
        if(input_choice_team in team_roster_team):
            team_roster_team.remove(input_choice_team)
        if(input_choice_team in leaderboard_team):
            del leaderboard_team[input_choice_team]
        if(len(team_roster_player) > 0):
            for i in range(len(player_list)):
                if(input_choice_team == team_player_list[player_list[i]] and player_list[i] in team_roster_player):
                    if(input_choice_team == team_roster_player[player_list[i]]):
                        del team_roster_player[player_list[i]]
        team_list.remove(input_choice_team)
        for i in range(len(player_list)):
            if(team_player_list[player_list[i]] == input_choice_team):
                temp_player_list = temp_player_list + player_list[i] + "\n"
                team_player_list[player_list[i]] = "Unassigned"
        
        team_name_remover = open('team_player_list.txt').read()
        team_name_remover = team_name_remover.replace("==TEAM========\n"
                                                      "Unassigned\n"
                                                      "==PLAYER======\n",
                                                      "==TEAM========\n"
                                                      "Unassigned\n"
                                                      "==PLAYER======\n" +
                                                      temp_player_list
                                                      ).replace("==TEAM========\n"
                                                      + input_choice_team +
                                                      "\n==PLAYER======\n" +
                                                      temp_player_list +
                                                      "==============\n\n",
                                                      "")
        team_player_change = open('team_player_list.txt','w')
        team_player_change.write(team_name_remover)
        team_player_change.close()

def team_delete_player():
    global team_adding_check
    global player_list
    global team_player_list

    team_adding_check = 1
    input_choice = ''
    input_choice_player = ''
    
    while True:
        print(SCRCLR)
        print("List of available player(s): ")
        for i in range(len(player_list)):
            print("  [" + str(i + 1) + "]\t[" + team_player_list[player_list[i]] + "] " + player_list[i])
        print("\nChoose the player to delete."
              "\nInput Q or E if you want to cancel.")
        while True:
            input_choice_player = input(text_team_player_input)
            if(input_choice_player.replace(' ','') == ""):
                print("Please input player name or ID.")
            if(input_choice_player.upper() == 'Q' or input_choice_player.upper() == 'E'):
                team_adding_check = 0
                break
            for i in range(len(player_list)):
                if(str(i + 1) == input_choice_player):
                    input_choice_player = player_list[i]
                    break
            if(input_choice_player in player_list):
                break
            else:
                print("Could not find player with given input: " + input_choice_player)
        
        print(SCRCLR)
        print("Player to remove: " + input_choice_player)
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            break
        input_choice = ''

    if(team_adding_check == 1):
        if(input_choice_player in team_roster_player):
            del team_roster_player[input_choice_player]
        if(input_choice_player in leaderboard_player):
            del leaderboard_player[input_choice_player]
        player_list.remove(input_choice_player)
        del team_player_list[input_choice_player]
            
        team_player_remover = open('team_player_list.txt').read()
        team_player_remover = team_player_remover.replace(input_choice_player + "\n",'')
        team_player_change = open('team_player_list.txt','w')
        team_player_change.write(team_player_remover)
        team_player_change.close()

def team_view_teams():
    print(SCRCLR)
    print("\nList of team(s): ")
    for i in range(len(team_list)):
        if(i != 0):
            print("  [" + str(i) + "]\t" + team_list[i])
    input("\nEnter to exit...")

def team_view_players():
    """ 
    """
    print(SCRCLR)
    print("List of player(s): ")
    for i in range(len(player_list)):
        print("  [" + str(i + 1) + "]\t[" + team_player_list[player_list[i]] + "] " + player_list[i])
    input("\nEnter to exit...")

# This is the match modules.
# match_prompt_continue function is to prompt the user whether to continue the match or not  
# match_initialise function is to start the match by defining the variables
def match_prompt_initial():
    display_info_match()
    print("Check the information before starting the match.")
    input_choice = prompt_confirm()
    if(input_choice == 'Y'):
        match_initialise()
    else:
        print("Please wait...")

def match_prompt_continue():
    global scoreboard_team
    global scoreboard_team_score
    global scoreboard_player
    global scoreboard_player_score
    global scoreboard_match_team_score

    print(SCRCLR)
    display_info_scoreboard()
    print("Do you want to continue for another match?")
    input_choice = prompt_confirm()
    if(input_choice == 'Y'):
        match_initialise()
    else:
        scoreboard_team = []
        scoreboard_team_score = {}
        scoreboard_player = []
        scoreboard_player_score = {}
        scoreboard_match_team_score = {}
        print("Please wait...")
 
def match_initialise():
    global scoreboard_team
    global scoreboard_team_score
    global scoreboard_player
    global scoreboard_player_score
    global scoreboard_match_team_score
    global leaderboard_team
    global leaderboard_player
    global match_check

    temp_team_roster_player = list(team_roster_player.keys())

    for i in range(len(team_roster_team)):
        if(team_roster_team[i] not in scoreboard_team):
            scoreboard_team.append(team_roster_team[i])
            scoreboard_match_team_score[team_roster_team[i]] = 0
        if(team_roster_team[i] not in leaderboard_team):
            leaderboard_team[team_roster_team[i]] = 0
        scoreboard_team_score[team_roster_team[i]] = 0
    for i in range(len(temp_team_roster_player)):
        if(temp_team_roster_player[i] not in scoreboard_player):
            scoreboard_player.append(temp_team_roster_player[i])
        if(temp_team_roster_player[i] not in leaderboard_player):
            leaderboard_player[temp_team_roster_player[i]] = 0
        scoreboard_player_score[temp_team_roster_player[i]] = 0
    match_check = 1
    
    match_scoring_start()

# match_scoring_start function is to start the scoring
# match_scoring_panel function is to display the score of the teams and the players
# match_score_update_team function is to update the team score
# match_score_update_player function is to update the player score
# match_scoring_end function is to end the scoring
# match_scoring_finalise function is to finalise the score
# match_print_result_file function is to print the match logs in .txt format 
# match_save_recent_match function is to save the when the match end with date and time and the team details
def match_scoring_start():
    while(match_check == 1):
        print(SCRCLR)
        display_match_scoreboard()
        match_scoring_panel()
    match_scoring_end()

def match_scoring_panel():
    global match_check
    
    input_panel = ''

    if(game_score_type_selected == "Standard"):
        print(text_title_match_panel_standard)
    elif(game_score_type_selected == "Highest Total Point"):
        print(text_title_match_panel_total_point)
    elif(game_score_type_selected == "Highest Player Score"):
        print(text_title_match_panel_player_point)
    elif(game_score_type_selected == "Highest Ratio"):
        print(text_title_match_panel_score_ratio)
    print("[1] Update " + scoreboard_team[0] + " Score  \t[2] Update " + scoreboard_team[0] + "'s Player(s) Score\n"
          "[3] Update " + scoreboard_team[1] + " Score  \t[4] Update " + scoreboard_team[1] + "'s Player(s) Score\n"
          "\n[0] End Match Scoring\n")
    input_panel = input()
    input_panel = input_panel.upper()
    input_panel = input_panel.replace(' ','')
    if(len(input_panel) > 1):
        input_panel = input_panel[0:2]
        if(input_panel.isnumeric() == True):
            input_panel = input_panel[0]
        if(input_panel == '[1' or input_panel == '[2' or input_panel == '[3' or input_panel == '[4' or
           input_panel == 'EN' or input_panel == 'EM' or input_panel == '[0'):
            if(input_panel == '[1'):
                input_panel = '1'
            elif(input_panel == '[2'):
                input_panel = '2'
            elif(input_panel == '[3'):
                input_panel = '3'
            elif(input_panel == '[4'):
                input_panel = '4'
            elif(input_panel == 'EN' or input_panel == 'EM' or input_panel == '[0'):
                input_panel = '0'
    
    if(input_panel == '1'):
        match_score_update_team(scoreboard_team[0])
    elif(input_panel == '2'):
        match_score_update_player(scoreboard_team[0])
    elif(input_panel == '3'):
        match_score_update_team(scoreboard_team[1])
    elif(input_panel == '4'):
        match_score_update_player(scoreboard_team[1])
    elif(input_panel == '0'):
        if(calc_point_total(scoreboard_team[0]) == 0 and calc_point_total(scoreboard_team[1]) == 0):
            print("No player score recorded.\nPlayer scores are required to end the scoring.")
            time.sleep(2)
        elif(game_score_type_selected == "Standard" and scoreboard_team_score[scoreboard_team[0]] == 0 and scoreboard_team_score[scoreboard_team[1]] == 0):
            print("Team scores are required for this mode to end.")
            time.sleep(2)
        else:
            print("Are you sure you want to end now?")
            input_choice = prompt_confirm()
            if(input_choice == 'Y'):
                match_check = 0

def match_score_update_team(team_name):
    global scoreboard_team_score

    while True:
        print("\nInput the score of " + team_name + " currently has.\n"
              "Enter blank to cancel.")
        input_score = input("Score: ")
        if(input_score.replace(' ','') == ""):
            break
        if(input_score.isnumeric() == False):
            print(SCRCLR)
            print("Please input an integer.")
            time.sleep(1)
        elif(float(input_score).is_integer() == False):
            print(SCRCLR)
            print("Please input an integer.")
            time.sleep(1)
        else:
            input_score = int(input_score)
            scoreboard_team_score[team_name] = input_score
            break

def match_score_update_player(team_name):
    global scoreboard_player_score

    scoring_check = 1
    temp_counter = 0
    temp_player_list = []

    print("Player(s) in " + team_name + ":")
    for i in range(len(scoreboard_player)):
        if(team_name == team_roster_player[scoreboard_player[i]]):
            temp_counter += 1
            temp_player_list.append(scoreboard_player[i])
            print("[" + str(temp_counter) + "] " + scoreboard_player[i])
    print("\nSelect the player from " + team_name + ".\n"
          "Enter blank to cancel.")
    while True:
        input_choice_player = input("Player name: ")
        if(input_choice_player.replace(' ','') == ""):
            break
        for i in range(len(temp_player_list)):
            if(str(i + 1) == input_choice_player):
                input_choice_player = temp_player_list[i]
                break
        if(input_choice_player in temp_player_list):
            while True:
                print("\nInput the number of point " + input_choice_player + " have now.\n"
                      "Currently have " + str(scoreboard_player_score[input_choice_player]) + " point(s).\n"
                      "Enter blank to cancel.")
                input_score = input("Score: ")
                if(input_score.replace(' ','') == ""):
                    break
                if(input_score.isnumeric() == False):
                    print(SCRCLR)
                    print("Please input an integer.")
                    time.sleep(1)
                elif(float(input_score).is_integer() == False):
                    print(SCRCLR)
                    print("Please input an integer.")
                    time.sleep(1)
                else:
                    input_score = int(input_score)
                    scoreboard_player_score[input_choice_player] = input_score
                    break
            break
        else:
            print("Could not find player with given input: " + input_choice_player)

def match_scoring_end():
    while True:
        input_panel = ''
        
        print(SCRCLR)
        display_match_scoreboard()
        print(text_subtitle_match_end)
        if(game_score_type_selected == "Standard"):
            print(text_title_match_panel_standard)
        elif(game_score_type_selected == "Highest Total Point"):
            print(text_title_match_panel_total_point)
        elif(game_score_type_selected == "Highest Player Point"):
            print(text_title_match_panel_player_point)
        elif(game_score_type_selected == "Highest Score Ratio"):
            print(text_title_match_panel_score_ratio)
        print("[1] Modify " + scoreboard_team[0] + " Score  \t[2] Modify " + scoreboard_team[0] + "'s Player(s) Score\n"
              "[3] Modify " + scoreboard_team[1] + " Score  \t[4] Modify " + scoreboard_team[1] + "'s Player(s) Score\n"
              "\n[8] Discard Match\n"
              "[0] Finalise Match\n")
        while(not(input_panel == '1' or input_panel == '2' or input_panel == '3' or
                  input_panel == '4' or input_panel == '8' or input_panel == '0')):
            input_panel = input()
            input_panel = input_panel.upper()
            input_panel = input_panel.replace(' ','')
            if(len(input_panel) > 1):
                input_panel = input_panel[0:2]
                if(input_panel.isnumeric() == True):
                    input_panel = input_panel[0]
                if(input_panel == '[1' or input_panel == '[2' or
                   input_panel == '[3' or input_panel == '[4' or
                   input_panel == 'DI' or input_panel == 'DM' or input_panel == '[8' or
                   input_panel == 'FI' or input_panel == 'FM' or input_panel == '[0'):
                    if(input_panel == '[1'):
                        input_panel = '1'
                    elif(input_panel == '[2'):
                        input_panel = '2'
                    elif(input_panel == '[3'):
                        input_panel = '3'
                    elif(input_panel == '[4'):
                        input_panel = '4'
                    elif(input_panel == 'DI' or input_panel == 'DM' or input_panel == '[8'):
                        input_panel = '8'
                    elif(input_panel == 'FI' or input_panel == 'FM' or input_panel == '[0'):
                        input_panel = '0'
    
        if(input_panel == '1'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                match_score_update_team(scoreboard_team[0])
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_panel == '2'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                match_score_update_player(scoreboard_team[0])
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_panel == '3'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                match_score_update_team(scoreboard_team[1])
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_panel == '4'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                match_score_update_player(scoreboard_team[1])
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_panel == '8'):
            print("Do you want to discard the match?")
            input_choice = prompt_confirm()
            if(input_choice == 'Y'):
                authorise_check = authentication_process(text_auth_password_auth)
                if(authorise_check == 2):
                    authorise_check = 1
                    match_save_recent_match()
                    break
                elif(authorise_check == 3):
                    authorise_check = 1
                    print(text_auth_cancel)
                    time.sleep(1)
                else:
                    print(text_auth_fail)
                    time.sleep(1)
        elif(input_panel == '0'):
            print("Are you sure to finalise the match?")
            input_choice = prompt_confirm()
            if(input_choice == 'Y'):
                match_save_recent_match()
                match_scoring_finalise()
                break
    match_prompt_continue()

def match_scoring_finalise():
    global leaderboard_team
    global leaderboard_player
    global scoreboard_match_team_score

    temp_player_scorer = []
    temp_point = 0
    point_player_highest = 0
    leaderboard_check = 0

    if(game_mode_selected == "Competitive"):
        leaderboard_check = 1
    elif(game_mode_selected == "Classic" or game_mode_selected not in game_mode_list):
        print(SCRCLR)
        print("Do you want to count this towards the leaderboard?")
        input_choice = prompt_confirm()
        if(input_choice == 'Y'):
            leaderboard_check = 1
    input_choice = ''

    for i in range(len(scoreboard_player)):
        temp_point = scoreboard_player_score[scoreboard_player[i]]
        if(temp_point > point_player_highest):
            point_player_highest = temp_point
    for i in range(len(scoreboard_player)):
        if(scoreboard_player_score[scoreboard_player[i]] == point_player_highest):
            temp_player_scorer.append(scoreboard_player[i])
            temp_team_scorer = team_player_list[scoreboard_player[i]]

    print(SCRCLR)
    print("//=====-====-===-==-=||")
    if(game_score_type_selected == "Standard"):
        if(scoreboard_team_score[scoreboard_team[0]] > scoreboard_team_score[scoreboard_team[1]]):
            if(leaderboard_check == 1):
                leaderboard_team[scoreboard_team[0]] = (leaderboard_team[scoreboard_team[0]] + 1)
            scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
            print("  " + scoreboard_team[0] + " Won!")
            if(len(temp_player_scorer) == 1):
                print(" MVP: " + temp_player_scorer[0])
                if(leaderboard_check == 1):
                    leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
                
        elif(scoreboard_team_score[scoreboard_team[0]] < scoreboard_team_score[scoreboard_team[1]]):
            if(leaderboard_check == 1):
                leaderboard_team[scoreboard_team[1]] = (leaderboard_team[scoreboard_team[1]] + 1)
            scoreboard_match_team_score[scoreboard_team[1]] = (scoreboard_match_team_score[scoreboard_team[1]] + 1)
            print("  " + scoreboard_team[1] + " Won!")
            if(len(temp_player_scorer) == 1):
                print(" MVP: " + temp_player_scorer[0])
                if(leaderboard_check == 1):
                    leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
        elif(scoreboard_team_score[scoreboard_team[0]] == scoreboard_team_score[scoreboard_team[1]]):
            print("   MATCH TIED")
    elif(game_score_type_selected == "Highest Total Point"):
        if(calc_point_total(scoreboard_team[0]) > calc_point_total(scoreboard_team[1])):
            if(leaderboard_check == 1):
                leaderboard_team[scoreboard_team[0]] = (leaderboard_team[scoreboard_team[0]] + 1)
            scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
            print("  " + scoreboard_team[0] + " Won!")
            if(len(temp_player_scorer) == 1):
                print(" MVP: " + temp_player_scorer[0])
                if(leaderboard_check == 1):
                    leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
        elif(calc_point_total(scoreboard_team[0]) < calc_point_total(scoreboard_team[1])):
            if(leaderboard_check == 1):
                leaderboard_team[scoreboard_team[1]] = (leaderboard_team[scoreboard_team[1]] + 1)
            scoreboard_match_team_score[scoreboard_team[1]] = (scoreboard_match_team_score[scoreboard_team[1]] + 1)
            print("  " + scoreboard_team[1] + " Won!")
            if(len(temp_player_scorer) == 1):
                print(" MVP: " + temp_player_scorer[0])
                if(leaderboard_check == 1):
                    leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
        elif(calc_point_total(scoreboard_team[0]) == calc_point_total(scoreboard_team[1])):
            if(scoreboard_team_score[scoreboard_team[0]] > scoreboard_team_score[scoreboard_team[1]]):
                if(leaderboard_check == 1):
                    leaderboard_team[scoreboard_team[0]] = (leaderboard_team[scoreboard_team[0]] + 1)
                scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
                print("  " + scoreboard_team[0] + " Won by highest team score!")
                if(len(temp_player_scorer) == 1):
                    print(" MVP: " + temp_player_scorer[0])
                    if(leaderboard_check == 1):
                        leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
            elif(scoreboard_team_score[scoreboard_team[0]] < scoreboard_team_score[scoreboard_team[1]]):
                if(leaderboard_check == 1):
                    leaderboard_team[scoreboard_team[1]] = (leaderboard_team[scoreboard_team[1]] + 1)
                scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
                print("  " + scoreboard_team[1] + " Won by highest team score!")
                if(len(temp_player_scorer) == 1):
                    print(" MVP: " + temp_player_scorer[0])
                    if(leaderboard_check == 1):
                        leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
            elif(scoreboard_team_score[scoreboard_team[0]] == scoreboard_team_score[scoreboard_team[1]]):
                print("   MATCH TIED")
    elif(game_score_type_selected == "Highest Player Point"):
        if(len(temp_player_scorer) == 1):
            if(leaderboard_check == 1):
                leaderboard_team[temp_team_scorer] = (leaderboard_team[temp_team_scorer] + 1)
                leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
            print("  " + temp_team_scorer + " Won!")
            print(" MVP: " + temp_player_scorer[0])
        elif(len(temp_player_scorer) > 1):
            if(scoreboard_team_score[scoreboard_team[0]] > scoreboard_team_score[scoreboard_team[1]]):
                if(leaderboard_check == 1):
                    leaderboard_team[scoreboard_team[0]] = (leaderboard_team[scoreboard_team[0]] + 1)
                scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
                print("  " + scoreboard_team[0] + " Won by highest team score!")
            elif(scoreboard_team_score[scoreboard_team[0]] < scoreboard_team_score[scoreboard_team[1]]):
                if(leaderboard_check == 1):
                    leaderboard_team[scoreboard_team[1]] = (leaderboard_team[scoreboard_team[1]] + 1)
                scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
                print("  " + scoreboard_team[1] + " Won by highest team score!")
            elif(scoreboard_team_score[scoreboard_team[0]] == scoreboard_team_score[scoreboard_team[1]]):
                print("   MATCH TIED")
    elif(game_score_type_selected == "Highest Score Ratio"):
        if(calc_point_score_ratio(scoreboard_team[0]) > calc_point_score_ratio(scoreboard_team[1])):
            if(leaderboard_check == 1):
                leaderboard_team[scoreboard_team[0]] = (leaderboard_team[scoreboard_team[0]] + 1)
            scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
            print("  " + scoreboard_team[0] + " Won!")
            if(len(temp_player_scorer) == 1):
                print(" MVP: " + temp_player_scorer[0])
                if(leaderboard_check == 1):
                    leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
        elif(calc_point_score_ratio(scoreboard_team[0]) < calc_point_score_ratio(scoreboard_team[1])):
            if(leaderboard_check == 1):
                leaderboard_team[scoreboard_team[1]] = (leaderboard_team[scoreboard_team[1]] + 1)
            scoreboard_match_team_score[scoreboard_team[1]] = (scoreboard_match_team_score[scoreboard_team[1]] + 1)
            print("  " + scoreboard_team[1] + " Won!")
            if(len(temp_player_scorer) == 1):
                print(" MVP: " + temp_player_scorer[0])
                if(leaderboard_check == 1):
                    leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
        elif(calc_point_score_ratio(scoreboard_team[0]) == calc_point_score_ratio(scoreboard_team[1])):
            if(scoreboard_team_score[scoreboard_team[0]] > scoreboard_team_score[scoreboard_team[1]]):
                if(leaderboard_check == 1):
                    leaderboard_team[scoreboard_team[0]] = (leaderboard_team[scoreboard_team[0]] + 1)
                scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
                print("  " + scoreboard_team[0] + " Won by highest team score!")
                if(len(temp_player_scorer) == 1):
                    print(" MVP: " + temp_player_scorer[0])
                    if(leaderboard_check == 1):
                        leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
            elif(scoreboard_team_score[scoreboard_team[0]] < scoreboard_team_score[scoreboard_team[1]]):
                if(leaderboard_check == 1):
                    leaderboard_team[scoreboard_team[1]] = (leaderboard_team[scoreboard_team[1]] + 1)
                scoreboard_match_team_score[scoreboard_team[0]] = (scoreboard_match_team_score[scoreboard_team[0]] + 1)
                print("  " + scoreboard_team[1] + " Won by highest team score!")
                if(len(temp_player_scorer) == 1):
                    print(" MVP: " + temp_player_scorer[0])
                    if(leaderboard_check == 1):
                        leaderboard_player[temp_player_scorer[0]] = (leaderboard_player[temp_player_scorer[0]] + 1)
            elif(scoreboard_team_score[scoreboard_team[0]] == scoreboard_team_score[scoreboard_team[1]]):
                print("   MATCH TIED")
    print("\\\\=====-====-===-==-=||")
    
    print("\nDo you want to save match logs?")
    input_choice = prompt_confirm()
    if(input_choice == 'Y'):
        authorise_check = authentication_process(text_auth_password_auth)
        if(authorise_check == 2):
            authorise_check = 1
            match_print_result_file()
        elif(authorise_check == 3):
            authorise_check = 1
            print(text_auth_cancel)
            time.sleep(1)
        else:
            print(text_auth_fail)
            time.sleep(1)

def match_print_result_file():
    temp_counter_1 = 0
    temp_counter_2 = 0
    temp_team_roster_1 = ""
    temp_team_roster_2 = ""
    temp_team_roster_player = list(team_roster_player.keys())
    temp_max_player_string = ""
    temp_team_string = ""

    if(game_max_player_strict == 0):
        temp_max_player_string = ("\nMax Player(s): " + str(game_max_player) +
                                  "\nMax Player(s) in Team: " + str(game_max_player_per_team))
    elif(game_max_player_strict == 1):
        temp_max_player_string = ("\nMax Player(s) in Team (REQUIRED): " + str(game_max_player_per_team))
    for i in range(len(temp_team_roster_player)):
        for j in range(len(team_roster_team)):
            if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[j]):
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[0]):
                    temp_counter_1 += 1
                    temp_team_roster_1 = temp_team_roster_1 + " [" + str(scoreboard_player_score[temp_team_roster_player[i]]) + " Pt] > "  + temp_team_roster_player[i] + "\n"
                if(team_roster_player[temp_team_roster_player[i]] == team_roster_team[1]):
                    temp_counter_2 += 1
                    temp_team_roster_2 = temp_team_roster_2 + " [" + str(scoreboard_player_score[temp_team_roster_player[i]]) + " Pt] > "  + temp_team_roster_player[i] + "\n"
    if(game_max_player_strict == 0):
        temp_team_string = ("\n\nTeam Playing:\n" +
                            " ====== " * 8 +
                            "\n[" + team_roster_team[0] + "] --- " + str(scoreboard_team_score[scoreboard_team[0]]) + " score(s)" + " --- " + str(scoreboard_match_team_score[team_roster_team[0]]) + " Win(s)\n" + temp_team_roster_1 +
                            "Total Point: " + str(calc_point_total(scoreboard_team[0])) +
                            "\nAvg. Point: " + str(calc_point_avg(scoreboard_team[0])) +
                            "\nPoint/Score Ratio: " + str(calc_point_score_ratio(scoreboard_team[0])) + "\n" +
                            " ====== " * 8 +
                            "\n[" + team_roster_team[1] + "] --- " + str(scoreboard_team_score[scoreboard_team[1]]) + " score(s)" + " --- " + str(scoreboard_match_team_score[team_roster_team[1]]) + " Win(s)\n" + temp_team_roster_2 + 
                            "Total Point: " + str(calc_point_total(scoreboard_team[1])) +
                            "\nAvg. Point: " + str(calc_point_avg(scoreboard_team[1])) +
                            "\nPoint/Score Ratio: " + str(calc_point_score_ratio(scoreboard_team[1])) + "\n" +
                            " ====== " * 8)
    else:
        temp_team_string = ("\n\nTeam Playing: [" + str(game_max_player_per_team) + " PLAYER(S) TEAM]\n" +
                            " ====== " * 8 +
                            "\n[" + team_roster_team[0] + "] --- " + str(scoreboard_team_score[scoreboard_team[0]]) + " score(s)" + " --- " + str(scoreboard_match_team_score[team_roster_team[0]]) + " Win(s)\n" + temp_team_roster_1 +
                            "Total Point: " + str(calc_point_total(scoreboard_team[0])) +
                            "\nAvg. Point: " + str(calc_point_avg(scoreboard_team[0])) +
                            "\nPoint/Score Ratio: " + str(calc_point_score_ratio(scoreboard_team[0])) + "\n" +
                            " ====== " * 8 +
                            "\n[" + team_roster_team[1] + "] --- " + str(scoreboard_team_score[scoreboard_team[1]]) + " score(s)" + " --- " + str(scoreboard_match_team_score[team_roster_team[1]]) + " Win(s)\n" + temp_team_roster_2 + 
                            "Total Point: " + str(calc_point_total(scoreboard_team[1])) +
                            "\nAvg. Point: " + str(calc_point_avg(scoreboard_team[1])) +
                            "\nPoint/Score Ratio: " + str(calc_point_score_ratio(scoreboard_team[1])) + "\n" +
                            " ====== " * 8)
    match_name = "matchlogs" + match_history_recent_time_short + ".txt"

    file_match_result = open(match_name,'w')
    file_match_result.write(" ======== " * 8 + "\n" +
                            text_title_program + "\n" +
                            "|  | ||| " + event_name +
                            "\n\  \ Hosted by " + hostname +
                            "\n\nGame Selected: " + game_selected +
                            "\nGame Genre: " + game_genre_selected +
                            "\nGamemode: " + game_mode_selected +
                            temp_max_player_string +
                            "\n\nScoring Type: " + game_score_type_selected +
                            "\nAdditional Info.: " + game_info_add +
                            temp_team_string + "\n" + match_history_recent_time)
    file_match_result.close()

def match_save_recent_match():
    global match_history_recent
    global match_history_recent_time
    global match_history_recent_time_short

    match_history_recent_time = strftime("%A, %d %B %Y, %H:%M:%S", localtime())
    match_history_recent_time_short = strftime("%y%m%d%H%M%S", localtime())

    temp_match_log = ("[" + str(leaderboard_team[scoreboard_team[0]]) + "][" + scoreboard_team[0] + "] <" + str(scoreboard_team_score[scoreboard_team[0]]) +
                      ":" + str(scoreboard_team_score[scoreboard_team[1]]) + "> [" + scoreboard_team[1] + "][" + str(leaderboard_team[scoreboard_team[1]]) +
                      "]\n\t[" + game_mode_selected + "] " + game_selected + " match ended on " + match_history_recent_time)
    match_history_recent.append(temp_match_log)

# Calculate the point/score given the input.
# calc_point_total function is to calculate the total point 
# calc_point_avg function is to calculate the average point
# calc_point_score_ratio function is to calculate the point score ratio
def calc_point_total(team_name_score):
    point_total = 0
    for i in range(len(scoreboard_player)):
        if(team_roster_player[scoreboard_player[i]] == team_name_score):
            point_total = point_total + scoreboard_player_score[scoreboard_player[i]]
    
    return point_total

def calc_point_avg(team_name_score):
    point_total = 0
    temp_counter = 0
    for i in range(len(scoreboard_player)):
        if(team_roster_player[scoreboard_player[i]] == team_name_score):
            temp_counter += 1
            point_total = point_total + scoreboard_player_score[scoreboard_player[i]]
    point_avg = point_total / temp_counter
    
    return point_avg

def calc_point_score_ratio(team_name_score):
    point_score_ratio = 0
    if((scoreboard_team_score[scoreboard_team[0]] + scoreboard_team_score[scoreboard_team[1]]) != 0):
        point_score_ratio = calc_point_total(team_name_score) / (scoreboard_team_score[scoreboard_team[0]] + scoreboard_team_score[scoreboard_team[1]])
    
    return point_score_ratio

# Self-explanatory.
# view_match_history function is to view the match history
# view_leaderboard_team function is to view the team leaderboard
# view_leaderboard_player function is to view the player leaderboard
def view_match_history():
    print(SCRCLR)
    print("\nRecent matches(es): ")
    for i in range(len(match_history_recent)):
        print("  [" + str(i + 1) + "]\t" + match_history_recent[i])
    input("\nEnter to exit...")

def view_leaderboard_team():
    leaderboard_sorted_team = dict(sorted(leaderboard_team.items(), key=operator.itemgetter(1), reverse=True))
    temp_leaderboard_team = list(leaderboard_sorted_team.keys())

    print(SCRCLR)
    print("\nTeam Leaderboard | Win")
    for i in range(len(temp_leaderboard_team)):
        print("  [" + str(i + 1) + "]\t[" + str(leaderboard_sorted_team[temp_leaderboard_team[i]]) + " Win(s)] " + temp_leaderboard_team[i])
    input("\nEnter to exit...")

def view_leaderboard_player():
    temp_team_roster_player = list(team_roster_player.keys())
    leaderboard_sorted_player = dict(sorted(leaderboard_player.items(), key=operator.itemgetter(1), reverse=True))
    temp_leaderboard_player = list(leaderboard_sorted_player.keys())

    print(SCRCLR)
    print("\nPlayer Leaderboard | MVP")
    for i in range(len(temp_leaderboard_player)):
        print("  [" + str(i + 1) + "]\t[" + str(leaderboard_sorted_player[temp_leaderboard_player[i]]) + " MVP(s)] [" + team_player_list[temp_leaderboard_player[i]] + "] " + temp_leaderboard_player[i])
    input("\nEnter to exit...")

# This is simple and short functions for user settings menu.
# The user can change their password, hostname, and event name here but not the username.
# Read the comments of the authentication_pass_change(), authentication_hostname_change(), and event_name_setup()
# for more details regarding their functions.
def user_settings():
    global event_name
    
    while True:
        input_menu = ''
        
        print(SCRCLR)
        display_info_settings()
        print(text_title_user_settings)
        print("[1] Change Event Name\n"
              "[2] Change Hostname\n"
              "[3] Change Password\n"
              "\n[0] Back\n")
        while(not(input_menu == '1' or input_menu == '2' or input_menu == '3' or input_menu == '0')):
            input_menu = input()
            input_menu = input_menu.upper()
            input_menu = input_menu.replace(' ','')
            if(len(input_menu) > 1):
                input_menu = input_menu[0:2]
                if(input_menu.isnumeric() == True):
                    input_menu = input_menu[0]
                if(input_menu == 'CE' or input_menu == '[1' or
                   input_menu == 'CH' or input_menu == '[2' or
                   input_menu == 'CP' or input_menu == '[3' or
                   input_menu == 'BA' or input_menu == '[0'):
                    if(input_menu == 'CE' or input_menu == '[1'):
                        input_menu = '1'
                    elif(input_menu == 'CH' or input_menu == '[2'):
                        input_menu = '2'
                    elif(input_menu == 'CP' or input_menu == '[3'):
                        input_menu = '3'
                    elif(input_menu == 'BA' or input_menu == '[0'):
                        input_menu = '0'
    
        if(input_menu == '1'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                event_name = event_name_setup()
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_menu == '2'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                authentication_hostname_change()
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_menu == '3'):
            authorise_check = authentication_process(text_auth_password_auth)
            if(authorise_check == 2):
                authorise_check = 1
                authentication_pass_change()
            elif(authorise_check == 3):
                authorise_check = 1
                print(text_auth_cancel)
                time.sleep(1)
            else:
                print(text_auth_fail)
                time.sleep(1)
        elif(input_menu == '0'):
            break
### END PARAMETER ###

# This is where it began to run all of the codes, modules and functions.
# Using program_run to assign that the program to loop itself, thus keeping it running until the user exit.
# The initialise function (self-explanatory) will always start first, see initialise function comment for more details.
initialise()
while(program_run == 1):
    authentication_module()
    if(program_run == 1 and authorise_check == 1 and predefine_mode == 0):
        event_name = event_name_setup()
    while(authorise_check == 1):
        main_module()
