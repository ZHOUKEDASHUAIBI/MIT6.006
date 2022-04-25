def Radix_Sort(A):
    max = A[0]
    for x in A:
        if x > max:
            max = x
    u = max
    n = len(A)
    c = 1 + ((u + 1).bit_length() // n.bit_length())
    count = [None]*n
    for i in range(n):
        count[i] = []
    D = []
    for x in A:
        B = []
        B.append(x)
        high = x
        for j in range(c):
            (high, low) = divmod(high, n)
            B.append(low)
        D.append(B)
    for i in range(c):
        for x in D:
            count[x[i+1]].append(x)
        D = []
        for k in range(n):
            for x in count[k]:
                D.append(x)
        for i in range(n):
            count[i] = []
    Array = []
    for x in D:
        Array.append(x[0])
    return Array

A = [64,8,216,512,27,729,1,0,343,125]
B = Radix_Sort(A)
print(B)
