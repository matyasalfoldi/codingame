import sys

class Node:
    def __init__(self, num):
        self.val = num
        self.next = None
            

maxnum, start = [int(i) for i in input().split()]
d = input()
direction = 1 if d == "LEFT" else -1
iterate_over = range(2, maxnum+1) if direction == 1 else range(maxnum-1, 0, -1)
start_val = 1 if direction == 1 else maxnum
start_node = None
first_node = Node(start_val)
prev = first_node
for i in iterate_over:
    curr_node = Node(i)
    if i == start:
        start_node = curr_node
    prev.next = curr_node
    prev = curr_node
    if i == maxnum or i == 1:
        curr_node.next = first_node

curr = start_node
while curr.next.val != curr.val:
    #kill
    curr.next = curr.next.next
    #after kill
    curr = curr.next

print(curr.val)

"""
direction = 1 if d == "LEFT" else -1
killed = set()
one_left = False
current = start
to_kill = (start + direction) % maxnum
while not one_left:
    if to_kill == current:
        one_left = True
        continue
    if to_kill not in killed:
        killed.add(to_kill)
        current = (to_kill + direction) % maxnum
        while current in killed:
            current = (current + direction) % maxnum
        to_kill = (current + direction) % maxnum
    else:
        to_kill = (to_kill + direction) % maxnum
        while to_kill in killed:
            to_kill = (to_kill + direction) % maxnum

print(current)
"""
