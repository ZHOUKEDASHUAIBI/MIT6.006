def InsertLast(A, i):
    if i > 0 and A[i] < A[i - 1]:
        A[i] , A[i - 1] = A[i - 1] , A[i]
        InsertLast(A, i-1)
        
def InsertionSort(A, i):
    if i < len(A):
        InsertLast(A, i)
        InsertionSort(A, i + 1)
        
A = [4,6,1,9,10,2,77]
InsertionSort(A, 1)
print(A)
