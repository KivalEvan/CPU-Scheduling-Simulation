chocBar = []
counter = 0
totalCuts = 0
chocRows = int(input("Input number of chocolate rows: "))
chocColumns = int(input("Input number of chocolate columns: "))
maxCount = chocRows * chocColumns - 1
for i in range(0,chocRows):
	temp = []
	for j in range (0, chocColumns):
		temp.append(0) 
	chocBar.append(temp)

def pieceShow(num):
	num -= 1
	print("Piece number [", num, "]")
	for i in range(0, chocRows):
		for j in range (0, chocColumns):
			if chocBar[i][j] == num:
				print("[ ]"),
		print("")

def pieceCut(direction, pieceNum, index):
	pieceNew = []
	for i in range (0, chocRows):
		temp = []
		for j in range (0, chocColumns):
			if chocBar[i][j] == pieceNum:
				temp.append(1)
		pieceNew.append(temp)
	pieceRow = len(pieceNew)
	pieceCol = len(pieceNew[0]) 
	print(pieceCol)
	if (direction == "h" or direction == "H"):
		for i in range(0, index):
			for j in range(0, pieceCol):
				chocBar[i][j] = totalCuts
	else:
		for i in range(0, pieceRow):
			for j in range(0, index):
				chocBar[i][j] = totalCuts


while (totalCuts <= maxCount):	
	totalCuts += 1
	for i in range (1, totalCuts+1):
		pieceShow(i)

	pieceNum = int(input("Which number of piece(s) do you want to cut? "))
	direction = input("Enter H to cut [h]orizontally or V to cut [v]ertically? ")
	while (not(direction == "h" or direction == "H" or direction == "v" or direction == "V")):
		direction = input("Incorrect input. Enter H to cut [h]orizontally or V to cut [v]ertically" )
	index = int(input("From which index? "))
	pieceCut(direction,pieceNum,index)
	
	input("Continue?")

