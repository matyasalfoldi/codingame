import sys
import math

n = int(input())

s = 1
summ = 1
end = n**2

while s < end:
    for i in range(0,4):
        if s >= end:
            break
        s = s + n-1
        summ += s
    n = n-2

print(summ)
