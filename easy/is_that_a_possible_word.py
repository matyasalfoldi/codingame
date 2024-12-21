from dataclasses import dataclass
import sys
from typing import Dict, List

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

@dataclass
class StateInitializer:
    start: str
    transitions: Dict[str, Dict[str, str]]
    end_states: List[str]
    state_changers: List[str]


class State:
    def __init__(self, state_init: StateInitializer):
        self.state = state_init.start
        self.transitions = state_init.transitions
        self.end_states = state_init.end_states
        self.state_changers = state_init.state_changers
        
    def transition(self, character):
        # If in invalid state, we don't do anything, which will cause is_valid to be false
        if not self.state:
            return
        if character in self.state_changers:
            try:
                self.state = self.transitions[self.state][character]
            except KeyError:
                # If you are in a state and get a character that is in the alphabet but no transition, also return "false"
                self.state = None
        else:
            # If the word contains a character that is not in the alphabet, "false" is expected.
            self.state = None
    
    def is_valid(self):
        return self.state in self.end_states


def get_state_initializer():
    state_changers = input().split()
    print(f'{state_changers=}', file=sys.stderr, flush=True)
    states = input() # Not needed since transitions contain the states
    number_of_transitions = int(input())
    transitions = {}
    for i in range(number_of_transitions):
        t = input().split()
        if not transitions.get(t[0]):
            transitions[t[0]] = {}
        transitions[t[0]][t[1]] = t[2]
    print(f'{transitions=}', file=sys.stderr, flush=True)
    start_state = input()
    print(f'{start_state=}', file=sys.stderr, flush=True)
    end_states = input().split()
    print(f'{end_states=}', file=sys.stderr, flush=True)

    return StateInitializer(
        start = start_state,
        transitions = transitions,
        end_states = end_states,
        state_changers = state_changers
    )

si = get_state_initializer()
number_of_words = int(input())
for i in range(number_of_words):
    word = input()
    print(f'{word=}', file=sys.stderr, flush=True)
    state = State(si)
    for char in word:
        state.transition(char)
    if state.is_valid():
        print('true')
    else:
        print('false')
