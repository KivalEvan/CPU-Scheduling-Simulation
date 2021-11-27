import time

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0987654321`~!@#$%^&*()_-+=[]{}|:;'<>?,./"
encrypt_key = "UEJOBTPZWCNSRKDGVMLFAQIYXH 0987654321`~!@#$%^&*()_-+=[]{}|:;'<>?,./"
end_word = ["ING", "ISM", "HIP"]
symbol = "`~!@#$%^&*()_-+=[]{}|:;'<>?,./"
symbol = list(symbol)
text = ""

def get_choice():
    global choice
    choice = ""
    while(not(choice == "D" or choice == "E" or choice == "Q")):
        choice = input("[D]ecryption\n[E]ncryption\n\n[Q]uit\n\n")
        choice = choice.upper()
        if(choice == "EXIT"):
            choice = "Q"
        try:
            choice = choice[0]
        except IndexError:
            choice = ""

def get_message():
    global input_text
    if(choice == "D"):
        input_text = input("Input encrypted text: ")
    if(choice == "E"):
        input_text = input("Input to encrypt text: ")

def get_algo_order():
    global order
    order = []
    input_order = 999
    if(choice == "D"):
        print("Enter the encrytion algorithm (at least 2)\n[1] [S]ubstitution\n[2] [T]ransposition\n[3] [E]xpansion\n[4] [C]ompaction\n\n[0] to exit\n")
    elif(choice == "E"):
        print("Create the encryption algorithm (at least 2)\n[1] [S]ubstitution\n[2] [T]ransposition\n[3] [E]xpansion\n[4] [C]ompaction\n\n[0] to exit\n")
    while True:
        while(not(input_order == 0 or input_order == 1 or input_order == 2 or input_order == 3 or input_order == 4)):
            input_order = input("")
            input_order = list(input_order)
            try:
                input_order = str(input_order[0])
            except IndexError:
                input_order = ""
            input_order = input_order.upper()
            if(input_order == "S"):
                input_order = 1
            elif(input_order == "T"):
                input_order = 2
            elif(input_order == "E"):
                input_order = 3
            elif(input_order == "C"):
                input_order = 4
            else:
                if(not(input_order == "0" or input_order == "1" or input_order == "2" or input_order == "3" or input_order == "4")):
                    input_order = 999
            try:
                input_order = int(input_order)
            except:
                print("Please input the integer or the initial letter.")
            if(input_order > 4  or input_order < 0):
                print("Integer must not be more than 4 or less than 0.")
        if(input_order != 0):
            order.append(input_order)
            print("Index Order:", order, "\nEnter 0 to exit")
        elif(len(order) == 0):
            print("Please input the order before proceeding.")
        elif(len(order) == 1):
            print("Please input another another encryption algorithm before proceeding.")
        else:
            break
        input_order = 999

def processing():
    global text
    order_reverse = []
    text = input_text.upper()
    if(choice == "D"):
        print("\n[ STARTING TO DECRYPT MESSAGES ]")
    if(choice == "E"):
        print("\n[ STARTING TO ENCRPYT MESSAGES ]")
    print("[ INPUT ]\n" + text)
    if(choice == "D"):
        print("\nReceiving Encryption Algorithm:")
        for i in range(len(order)):
            if(order[i] == 1):
                print("[ " + str(i + 1) + " ] Substituting")
            if(order[i] == 2):
                print("[ " + str(i + 1) + " ] Repositioning")
            if(order[i] == 3):
                print("[ " + str(i + 1) + " ] Expanding")
            if(order[i] == 4):
                print("[ " + str(i + 1) + " ] Compacting")
        order_reverse = order[::-1]
        time.sleep(2)
        print("\nProcessing Decryption:")
        time_initial = time.time()
        for i in range(len(order_reverse)):
            progress = (i + 1)/len(order_reverse) * 100
            if(order_reverse[i] == 1):
                print("[ SUBSTITUTION PROCESS ]")
                encrypted_text = substitution_encrypt(text, encrypt_key, alphabet)
                text = substitution_decrypt(encrypted_text, encrypt_key, alphabet)
                print("> Allocating keys", list(text))
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            if(order_reverse[i] == 2):
                print("[ TRANSPOSITION PROCESS ]")
                text = transposition(text)
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            if(order_reverse[i] == 3):
                print("[ REDUCTION PROCESS ]")
                text = expansion_decrypt(text)
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            if(order_reverse[i] == 4):
                print("[ DECOMPACTION PROCESS ]")
                text = compaction_decrypt(text)
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            print("Time elapsed: %.2f" % (time.time() - time_initial) + "s\n")
    if(choice == "E"):
        print("\nPreparing Encryption Algorithm:")
        for i in range(len(order)):
            if(order[i] == 1):
                print("[ " + str(i + 1) + " ] Substituting")
            if(order[i] == 2):
                print("[ " + str(i + 1) + " ] Repositioning")
            if(order[i] == 3):
                print("[ " + str(i + 1) + " ] Expanding")
            if(order[i] == 4):
                print("[ " + str(i + 1) + " ] Compacting")
        time.sleep(2)
        print("\nProcessing Encryption:")
        time_initial = time.time()
        for i in range(len(order)):
            progress = (i + 1)/len(order) * 100
            if(order[i] == 1):
                print("[ SUBSTITUTION PROCESS ]")
                encrypted_text = substitution_encrypt(text, encrypt_key, alphabet)
                text = substitution_decrypt(encrypted_text, encrypt_key, alphabet)
                print("> Allocating keys:", list(text))
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            if(order[i] == 2):
                print("[ TRANSPOSITION PROCESS ]")
                text = transposition(text)
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            if(order[i] == 3):
                print("[ EXPANSION PROCESS ]")
                text = expansion_encrypt(text)
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            if(order[i] == 4):
                print("[ COMPACTION PROCESS ]")
                text = compaction_encrypt(text)
                print("\n[ Progress: %.2f" % progress + "% ] " + text)
            print("Time elapsed: %.2f" % (time.time() - time_initial) + "s\n")

def substitution_decrypt(encrypted_text, encrypt_key, alphabet):
    key_indices = [encrypt_key.index(k) for k in encrypted_text]
    return "".join(alphabet[key_index] for key_index in key_indices)

def substitution_encrypt(text, encrypt_key, alphabet):
    key_indices = [encrypt_key.index(k.upper()) for k in text]
    print("> Break apart texts:", list(text))
    print("> Key element allocations:", key_indices)
    return "".join(encrypt_key[key_index] for key_index in key_indices)

def transposition(text):
    text_array = text.split(" ")
    for i in range(len(text_array)):
        print("> Checking text:", text_array[i])
        chk_transposition = 0
        temp_element = []
        num_element = []
        text_transpo = list(text_array[i])
        temp_letter = text_transpo[0]
        for j in range(len(text_transpo)):
            for k in range(len(symbol)):
                if(symbol[k] == text_transpo[j]):
                    temp_element.append(text_transpo[j])
                    num_element.append(j)
        if(len(num_element) > 0):
            for j in range(len(num_element)):
                text_transpo.remove(temp_element[j])
                print("> Removing symbol(s):", "".join(text_transpo))
            print("> Temp. symbol element(s):", " ".join(temp_element))
            print("> Temp. element(s) index:", num_element)
        if(len(text_transpo) > 3):
            chk_transposition = 1
            print("> Initiate transposition for:", "".join(text_transpo))
            temp_letter = text_transpo[0]
            text_transpo[0] = text_transpo[len(text_transpo) - 1]
            text_transpo[len(text_transpo) - 1] = temp_letter
            print("> Repositioning:", "".join(text_transpo))
        if(len(num_element) > 0):
            for j in range(len(num_element)):
                text_transpo.insert(num_element[j], temp_element[j])
                print("> Re-adding symbol(s):", "".join(text_transpo))
        text_array[i] = "".join(text_transpo)
        if(chk_transposition == 1):
            print("> Result:", "".join(text_transpo))
    text = str(" ".join(text_array))
    return text;

def expansion_decrypt(text):
    text_array = text.split(" ")
    for i in range(len(text_array)):
        print("> Checking text:", text_array[i])
        chk_expansion = 0
        temp_element = []
        text_expand = list(text_array[i])
        temp_element = list(text_expand)
        if(len(temp_element) > 5):
            del temp_element[0]
            del temp_element[-1]
        if(len(temp_element) > 3 and text_expand[-1] == symbol[len(temp_element) - 1] and text_expand[0] == symbol[-(len(temp_element))]):
            chk_expansion = 1
            print("> Initiate reduction for:", "".join(text_expand))
            del text_expand[0]
            del text_expand[-1]
        text_array[i] = "".join(text_expand)
        if(chk_expansion == 1):
            print("> Result:", "".join(text_expand))
    text = str(" ".join(text_array))
    return text;

def expansion_encrypt(text):
    text_array = text.split(" ")
    for i in range(len(text_array)):
        print("> Checking text:", text_array[i])
        chk_expansion = 0
        temp_element_exp = []
        temp_element = []
        num_element = []
        text_expand = list(text_array[i])
        for j in range(len(text_expand)):
            for k in range(len(symbol)):
                if(symbol[k] == text_expand[j]):
                    temp_element.append(text_expand[j])
                    num_element.append(j)
        if(len(num_element) > 0):
            for j in range(len(num_element)):
                text_expand.remove(temp_element[j])
                print("> Removing symbol(s):", "".join(text_expand))
            print("> Temp. symbol element(s):", " ".join(temp_element))
            print("> Temp. element(s) index:", num_element)
        if(len(text_expand) > 3):
            chk_expansion = 1
            print("> Initiate expansion for:", "".join(text_expand))
            text_expand.append(symbol[len(text_array[i]) - 1])
            text_expand.insert(0, symbol[-(len(text_array[i]))])
            print("> Expanding:", "".join(text_expand))
        if(len(num_element) > 0):
            if(chk_expansion == 1):
                temp_element_exp = text_expand[0]
                text_expand.remove(symbol[-(len(text_array[i]))])
                print("> Removing initial expansion symbol:", "".join(text_expand))
            for j in range(len(num_element)):
                text_expand.insert(num_element[j], temp_element[j])
                print("> Re-adding symbol(s):", "".join(text_expand))
            if(chk_expansion == 1):
                text_expand.insert(0, temp_element_exp)
                print("> Re-adding initial expansion symbol:", "".join(text_expand))
        text_array[i] = "".join(text_expand)
        if(chk_expansion == 1):
            print("> Result:", "".join(text_expand))
    text = str(" ".join(text_array))
    return text;

def compaction_decrypt(text):
    text_array = text.split(" ")
    for i in range(len(text_array)):
        print("> Checking text:", text_array[i])
        chk_compaction = 0
        temp_element = []
        num_element = []
        text_compact = list(text_array[i])
        for j in range(len(text_compact)):
            for k in range(len(symbol)):
                if(symbol[k] == text_compact[j]):
                    temp_element.append(text_compact[j])
                    num_element.append(j)
        if(len(num_element) > 0):
            for j in range(len(num_element)):
                text_compact.remove(temp_element[j])
                print("> Removing symbol(s):", "".join(text_compact))
            print("> Temp. symbol element(s):", " ".join(temp_element))
            print("> Temp. element(s) index:", num_element)
        if(len(text_compact) > 5):
            for j in range(len(end_word)):
                end_word_array = list(end_word[j])
                if(text_compact[-(len(end_word_array)) + 1] == end_word_array[0] and text_compact[-(len(end_word_array)) + 2] == end_word_array[2]):
                    chk_compaction = 1
                    print("> Initiate decompaction for:", "".join(text_compact))
                    text_compact.insert(-(len(end_word_array)) + 2, end_word_array[1])
                    print("> Decompacting:", "".join(text_compact))
        if(len(num_element) > 0):
            for j in range(len(num_element)):
                text_compact.insert(num_element[j], temp_element[j])
                print("> Re-adding symbol(s):", "".join(text_compact))
        text_array[i] = "".join(text_compact)
        if(chk_compaction == 1):
            print("> Result:", "".join(text_compact))
    text = str(" ".join(text_array))
    return text;

def compaction_encrypt(text):
    text_array = text.split(" ")
    for i in range(len(text_array)):
        print("> Checking text:", text_array[i])
        chk_compaction = 0
        temp_element = []
        num_element = []
        text_compact = list(text_array[i])
        for j in range(len(text_compact)):
            for k in range(len(symbol)):
                if(symbol[k] == text_compact[j]):
                    temp_element.append(text_compact[j])
                    num_element.append(j)
        if(len(num_element) > 0):
            for j in range(len(num_element)):
                text_compact.remove(temp_element[j])
                print("> Removing symbol(s):", "".join(text_compact))
            print("> Temp. symbol element(s):", " ".join(temp_element))
            print("> Temp. element(s) index:", num_element)
        if(len(text_compact) > 7):
            for j in range(len(end_word)):
                end_word_array = list(end_word[j])
                if(text_compact[-(len(end_word_array))] == end_word_array[0] and text_compact[-(len(end_word_array)) + 1] == end_word_array[1] and text_compact[-(len(end_word_array)) + 2] == end_word_array[2]):
                      chk_compaction = 1
                      print("> Initiate compaction for:", "".join(text_compact))
                      del text_compact[-(len(end_word_array)) + 1]
                      print("> Compacting:", "".join(text_compact))
            print("> Compacting:", "".join(text_compact))
        if(len(num_element) > 0):
            for j in range(len(num_element)):
                text_compact.insert(num_element[j], temp_element[j])
                print("> Re-adding symbol(s):", "".join(text_compact))
        text_array[i] = "".join(text_compact)
        if(chk_compaction == 1):
            print("> Result:", "".join(text_compact))
    text = str(" ".join(text_array))
    return text;

def output():
    print("[ OUTPUT ]\n" + text)
    print("")
    global choice
    while(not(choice == "Q" or choice == "N" or choice == "Y")):
        choice = input("Continue? ( [Y]es / [N]o )\n")
        choice = choice.upper()
        try:
            choice = choice[0]
        except IndexError:
            choice = "Y"

while True:
    get_choice()
    if(choice == "Q"):
        print("Thank you for using this program.")
        break
    get_message()
    get_algo_order()
    processing()

    output()
    if(choice == "Q" or choice == "N"):
        print("Thank you for using this program.")
        break
