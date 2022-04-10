def Prime(x):
    for i in range(2, x, 1):
        if x % i == 0:
            return False
    return True

def NextPrime(x):
    n = x + 1
    while n:
        if Prime(n):
            return n
        n += 1
    
class Hashing:
    def __init__(self, TableSize):
        self.A = [None] * NextPrime(TableSize)
        self.size = NextPrime(TableSize)
    
    def Hash(self, key):
        return key % self.size
    
    def Find(self, key):
        index = self.Hash(key)
        if self.A[index] == key:
            return index
        else:
            CNum = 0
            pos = index
            while self.A[pos] != None and self.A[pos] != key:
                CNum += 1
                if CNum % 2 == 1:
                    pos = index + (CNum + 1)**2 // 4
                    if pos >= self.size:
                        pos -= self.size
                else:
                    pos = index - CNum**2 // 4
                    if pos < 0:
                        pos += self.size
            return pos
    
    def Insert(self, key):
        index = self.Find(key)
        self.A[index] = key
        
    def Delete(self, key):
        index = self.Find(key)
        self.A[index] = None
        
        
H = Hashing(9)
A = [10,21,32,1,12,7,18,20,11]
for a in A:
    i = H.Insert(a)
    
for a in H.A:
    if a == None:
        print(0)
    else:
        print(a)
