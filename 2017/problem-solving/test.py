import random
# VARINDEX
var1 = ["1", "2", "3", "4", "5"] # \_ 
var2 = ["123", "234", "345", "456", "567"] # /

#random.shuffle(var1)
#random.shuffle(var2)

varIndex = list(zip(var1, var2))
random.shuffle(varIndex)

var1, var2 = zip(*varIndex)
var1 = var1[0]
var2 = var2[0]
print(var1)
print(var2)
