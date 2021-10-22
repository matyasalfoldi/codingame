from enum import Enum
import math
from queue import PriorityQueue
import sys

# Move.Left.value -> (0,-1)
# Move.Left.name -> 'Left'
# Move((0,-1)).name -> 'Left'
class Move(Enum):
	LEFT = (0,-1)
	RIGHT = (0,1)
	UP = (-1,0)
	DOWN = (1,0)

class Labyrinth:
    visitedNodes = []
    moves = []

    def __init__(self, rows, cols):
        self._rows = rows
        self._cols = cols
        self._labyrinth = [[] for i in range(rows)]
        self.ctrlFound = False
        self.startPosSet = False

    def __getitem__(self, row):
        return self._labyrinth[row]
    
    def __setitem__(self, row, value):
        self._labyrinth[row] = []
        self._labyrinth[row].extend(value)
        if not self.ctrlFound:
            try:
                self._ctrlCol = value.index('C')
                self._ctrlRow = row
                self.ctrlFound = True     
            except ValueError:
                pass
        if not self.startPosSet:
            try:
                self._startCol = value.index('T')
                self._startRow = row
                self.startPosSet = True
            except ValueError:
                pass

    @property
    def start_pos(self):
        """Returns the starting position in (row, col) format."""
        if self.startPosSet:
            return (self._startRow, self._startCol)
        else:
            raise AttributeError("'Labyrinth' object hasn't got a starting position yet!")
    
    @property
    def ctrl_pos(self):
        """Returns the control rooms position in (row, col) format."""
        if self.ctrlFound:
            return (self._ctrlRow, self._ctrlCol)
        else:
            raise AttributeError("'Labyrinth' object hasn't got the control rooms position yet!")

    def _can_move(self, row, col):
        if row < 0 or col < 0:
            return False
        try:
            if self._labyrinth[row][col] in ['.','T','C']:
                return True
        except IndexError:
            pass
        return False

    def explore(self, currRow, currCol):
        """Explores the map to find the ctrl room behind a '?'"""
        print("exploring", file=sys.stderr)
        def can_find_unexplored_area(move, start, end):
            if start < 0:
                return False
            if Move.RIGHT == move or Move.LEFT == move:
                if start >= end:
                    start = currCol
                for i in range(start, end):
                    if self._labyrinth[currRow][i] == '?':
                        return True
            elif Move.DOWN == move or Move.UP == move:
                if start >= end:
                    start = currRow
                for i in range(start, end):
                    if self._labyrinth[i][currCol] == '?':
                        return True
            return False
        # 0. append to visited Nodes the current position
        self.visitedNodes.append((currRow, currCol))
        # 1. check if you can go right, and if '?' can be found to the right -> go right
        # check between [currRow][currCol+3, _cols) if currCol+3 >= _cols stop this check
        if ((currRow, currCol+1) not in self.visitedNodes and
            self._can_move(currRow, currCol+1) and
            can_find_unexplored_area(Move.RIGHT, currCol+3, self._cols)):
            self.moves.append(Move.RIGHT)
            return Move.RIGHT.name
        # 2. check if you can go down, and if '?' can be found down -> go down
        # check between [currRow+3, _rows)[currCol] if currRow+3 >= _rows stop this check
        if ((currRow+1, currCol) not in self.visitedNodes and
            self._can_move(currRow+1, currCol) and 
            can_find_unexplored_area(Move.DOWN, currRow+3, self._rows)):
            self.moves.append(Move.DOWN)
            return Move.DOWN.name
        # 3. left ... [currRow][0,currCol-3] if currCol < 0 stop this check
        if ((currRow, currCol-1) not in self.visitedNodes and
            self._can_move(currRow, currCol-1) and
            can_find_unexplored_area(Move.LEFT, 0, currCol-3)):
            self.moves.append(Move.LEFT)
            return Move.LEFT.name
        # 4. up ... [0, currRow-3][currCol] if currRow-3 < 0 stop this check
        if ((currRow-1, currCol) not in self.visitedNodes and
            self._can_move(currRow-1, currCol) and
            can_find_unexplored_area(Move.UP, 0, currRow-3)):
            self.moves.append(Move.UP)
            return Move.UP.name
        # 5. if we are here we need to backtrack
        return self._backtrack()

    def _backtrack(self):
        lastMove = self.moves[-1]
        del self.moves[-1]
        if lastMove == Move.RIGHT:
            return Move.LEFT.name
        elif lastMove == Move.LEFT:
            return Move.RIGHT.name
        elif lastMove == Move.DOWN:
            return Move.UP.name
        elif lastMove == Move.UP:
            return Move.DOWN.name

    def to_ctrl_room(self, currRow, currCol):
        def create_successor(row, col):
            return Node(
                q.g+1,
                (abs(row - self._ctrlRow) +
                 abs(col - self._ctrlCol)),
                (row, col),
                q.pos
            )
        print("moving to ctrl room", file=sys.stderr)
        openQueue = PriorityQueue()
        openQueue.put(Node(0, 0, (currRow, currCol), None))
        closed = []
        while not openQueue.empty():
            q = openQueue.get()
            successors = []
            qRow, qCol = q.pos
            if self._can_move(qRow, qCol+1):
                successors.append(create_successor(qRow, qCol+1))
            if self._can_move(qRow, qCol-1):
                successors.append(create_successor(qRow, qCol-1))
            if self._can_move(qRow+1, qCol):
                successors.append(create_successor(qRow+1, qCol))
            if self._can_move(qRow-1, qCol):
                successors.append(create_successor(qRow-1, qCol))
            for successor in successors:
                # if successor is the goal, stop search.
                if successor.pos == (self._ctrlRow, self._ctrlCol):
                    succRow, succCol = successor.pos
                    if not closed:
                        moveRow = succRow - currRow
                        moveCol = succCol - currCol
                    elif len(closed) == 1:
                        moveRow = qRow - currRow
                        moveCol = qCol - currCol
                    else:
                        nextRow, nextCol = closed[1].pos
                        moveRow = nextRow - currRow
                        moveCol = nextCol - currCol
                    move = (moveRow, moveCol)
                    self.moves.append(Move(move))
                    print(Move(move).name, file=sys.stderr)
                    return Move(move).name
                # if a node with the same pos as successor is in
                # the open list which has a lower f than successor,
                # skip
                skip = False
                for o in openQueue.queue:
                    if (successor.pos == o.pos and
                        o.f < successor.f):
                        skip = True
                        break
                if not skip:
                    # if a node with the same pos as successor is in
                    # the closed list which has a lower f than successor,
                    # skip this successor otherwise, add to the open list
                    skip = False
                    for c in closed:
                        if (successor.pos == c.pos and
                            c.f < successor.f):
                            skip = True
                            break
                    if not skip:
                        openQueue.put(successor)
            closed.append(q)                     


    def to_starting_point(self, currRow, currCol):
        print("moving back to start pos", file=sys.stderr)
        # check if backtracking is fast enough, otherwise a* back
        return self._backtrack()


class Node:
    def __init__(self, g, h, pos, parent):
        self.g = g
        self.h = h
        self.pos = pos
        self.parent = parent
        
    def __lt__(self, other):
        return(self.g+self.h < other.g+other.h)

    @property
    def f(self):
        return self.g+self.h

    # for debugging
    def __repr__(self):
        return f"g:{self.g} h:{self.h} pos:{self.pos} parent:{self.parent}"


class Kirk:
    
    def __init__(self):
        self.ctrlReached = False

    @property
    def pos(self):
        return (self.row, self.col)

    @pos.setter
    def pos(self, value):
        self.row, self.col = value

# rows: number of rows.
# cols: number of columns.
# alarmCountdown: number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
rows, cols, alarmCountdown = [int(i) for i in input().split()]
lab = Labyrinth(rows,cols)
kirk = Kirk()
# game loop
while True:
    # kr: row where Kirk is located.
    # kc: column where Kirk is located.
    kirk.pos = [int(i) for i in input().split()]
    for row in range(rows):
        lab[row] = [cell for cell in input()]
        # C of the characters in '#.TC?' (i.e. one line of the ASCII maze).

    # while control room is not found stroll
    if not lab.ctrlFound:
        print(lab.explore(*kirk.pos))
    # if ctrl room is found 
    elif lab.ctrlFound:
        # check if kirk is at the ctrl room yet
        if kirk.pos == lab.ctrl_pos:
            kirk.ctrlReached = True
        # if haven't reached it yet go to it
        if not kirk.ctrlReached:
            print(lab.to_ctrl_room(*kirk.pos))
        # if ctrl room reached go to start
        elif kirk.ctrlReached:
            print(lab.to_starting_point(*kirk.pos))
