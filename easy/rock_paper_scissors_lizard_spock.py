import sys

def R(other):
    if other.sign == "P":
        return True
    elif other.sign == "L":
        return False
    elif other.sign == "S":
        return True
    elif other.sign == "C":
        return False
def P(other):
    if other.sign == "C":
        return True
    elif other.sign == "R":
        return False
    elif other.sign == "L":
        return True
    elif other.sign == "S":
        return False
def C(other):
    if other.sign == "P":
        return False
    elif other.sign == "S":
        return True
    elif other.sign == "L":
        return False
    elif other.sign == "R":
        return True
def L(other):
    if other.sign == "R":
        return True
    elif other.sign == "S":
        return False
    elif other.sign == "C":
        return True
    elif other.sign == "P":
        return False
def S(other):
    if other.sign == "L":
        return True
    elif other.sign == "C":
        return False
    elif other.sign == "P":
        return True
    elif other.sign == "R":
        return False


class Player:
    def __init__(self, number, sign):
        self.number = int(number)
        self.sign = sign
        self.opponents = []

    def __lt__(self, other):
        if self.sign == other.sign:
            return self.number > other.number
        else:
            return globals()[self.sign](other)

    def __repr__(self):
        return f"number:{self.number} sign:{self.sign}"

def tournament(matches):
    if len(matches) == 1:
        for players in matches:
            if players[0] < players[1]:
                players[1].opponents.append(players[0].number)
                return players[1]
            else:
                players[0].opponents.append(players[1].number)
                return players[0]
    nextMatches = []
    for players in matches:
        if players[0] < players[1]:
            players[1].opponents.append(players[0].number)
            nextMatches.append(players[1])
        else:
            players[0].opponents.append(players[1].number)
            nextMatches.append(players[0])
    return tournament(list(zip(nextMatches[::2], nextMatches[1::2])))

n = int(input())
players = []
for i in range(n):
    players.append(Player(*input().split()))

matches = list(zip(players[::2], players[1::2]))
result = tournament(matches)
print(result.number)
print(result.opponents, file=sys.stderr)
print(" ".join([str(r) for r in result.opponents]))
