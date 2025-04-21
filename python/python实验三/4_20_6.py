decn = int(input())
binn = bin(decn)[2:]
octn = oct(decn)[2:]
hexn = hex(decn)[2:]
# print(binn)
print("{:} {:} {:}".format(binn,octn,hexn))
