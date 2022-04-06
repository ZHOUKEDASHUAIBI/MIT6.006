def PreMax(A,i):
    if i > 0:
        j = PreMax(A, i - 1)
        if A[i] < A[j]:
            return j
    return i
    
def SelectionSort(A, i = None):
    if i == None: i = len(A) - 1
    if i > 0:
        j = PreMax(A, i)
        A[i],A[j] = A[j],A[i]
        SelectionSort(A, i - 1)

        
A = [2,1,4,7,4,8,2,9,5]
SelectionSort(A)
print(A)
