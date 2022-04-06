'''
  Two part: [start , mid + 1] and [mid + 1 : end + 1].
  In python, that means part1 is from start to mid, while the part2 is from mid + 1 to end.
  Initially, start = 0, end = len(A) - 1.
'''
def Merge(L, R, A, i, j, a, b):
    if b >= a:
        if (j < 0 and i >= 0) or (i >= 0 and L[i] > R[j]):
            A[b] = L[i]
            i = i - 1
        else:
            A[b] = R[j]
            j = j - 1
        Merge(L, R, A, i, j, a, b - 1)
        
def MergeSort(A, start, end):
    if end - start > 1:
        mid = (start + end + 1) // 2
        MergeSort(A, start, mid)
        MergeSort(A, mid + 1, end)
        L = A[start : mid + 1]
        R = A[mid + 1 : end+1]
        Merge(L, R, A, len(L) - 1, len(R) - 1, start, end)
    elif end - start == 1:
        if A[start] > A[end]:
            A[start] , A[end] = A[end] , A[start]
        
A = [4,6,1,9,10,2,7,7]
MergeSort(A, 0, 7)
print(A)
