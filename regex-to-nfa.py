
def shunt(infix):

    specials = {'*': 4, '(': 3, '|': 2, ')' : 1}


    pofix, stack = "", ""  

    for c in infix:
        if c == '(':
            stack = stack + c  
        
        elif c == ')':
            while stack[-1] != '(':  
                pofix = pofix + stack[-1]  
                stack = stack[:-1]  
            stack = stack[:-1]  

        elif c in specials:
            while stack and specials.get(c, 0) <= specials.get(stack[-1], 0):
                pofix += stack[-1]
                stack = stack[:-1]
            stack += c

        else:
            pofix += c

    while stack:
        pofix += stack[-1]
        stack = stack[:-1]

    # returns pofix argument
    return pofix


class state:
    label, edge1, edge2 = None, None, None



class nfa:
    initial, accept = None, None

    def __init__(self, initial, accept):
        self.initial, self.accept = initial, accept



def compile(pofix):
    nfaStack = []

    # looping through the postfix expression
    for c in pofix:

        # If c is the 'kleene star' operator
        if c == '*':
            nfa1 = nfaStack.pop()
            initial, accept = state(), state()
            initial.edge1 = nfa1.initial
            initial.edge2 = accept
            nfa1.accept.edge1 = nfa1.initial
            nfa1.accept.edge2 = accept
            nfaStack.append(nfa(initial, accept))


        # If c is the 'concatenate' operator
        elif c == '.':
            
            nfa2, nfa1 = nfaStack.pop(), nfaStack.pop()
            nfa1.accept.edge1 = nfa2.initial
            nfaStack.append(nfa(nfa1.initial, nfa2.accept))


        # If c is the 'or' operator
        elif c == '|':

            nfa2, nfa1 = nfaStack.pop(), nfaStack.pop()
            initial = state()
            initial.edge1 = nfa1.initial
            initial.edge2 = nfa2.initial
            accept = state()
            nfa1.accept.edge1 = accept
            nfa2.accept.edge1 = accept
            nfaStack.append(nfa(initial, accept))
        
        
        else:
            accept = state()
            initial = state()
            initial.label = c
            initial.edge1 = accept
            if len(nfaStack) > 1:
                nfa2, nfa1 = nfaStack.pop(), nfaStack.pop()
                nfa1.accept.edge1 = nfa2.initial
                nfaStack.append(nfa(nfa1.initial, nfa2.accept))
            nfaStack.append(nfa(initial, accept))

    # at this point, nfastack should have a single nfa on it
    return nfaStack.pop()



def followes(state):
    # Create a new set, with state as its only member
    states = set()
    states.add(state)

    # Check if state has arrows labelled e from it
    if state.label is None:
        if state.edge1 is not None:
            states |= followes(state.edge1)
        if state.edge2 is not None:
            states |= followes(state.edge2)

    return states


# Matches a string to an infix regular expression
def match(infix, string):
    # Shunt and compile the regular expression
    postfix = shunt(infix)
    nfa = compile(postfix)

    current = set()
    nexts = set()

    current |= followes(nfa.initial)

    for s in string:
        for c in current:
            if c.label == s:
                nexts |= followes(c.edge1)
        
        current = nexts
        # next is back to an empty set
        nexts = set()

    return (nfa.accept in current)


#main
alphabet_size = int(input())
alphabet_input = input()
regex = input()
testcase = input()

spc = ['*', '|', '(', ')']
mod_regex = ""

for i in range(len(regex)-1):
    mod_regex += regex[i]

    if regex[i] not in spc:
        if regex[i+1] not in spc:
            mod_regex += '.'

        elif regex[i+1] == '(':
            mod_regex += '.' 

    
    elif regex[i] == '*':
        if regex[i+1] not in spc:
            mod_regex += '.'

        elif regex[i+1] == '(':
            mod_regex += '.' 

    
    elif regex[i] == ')':
        if regex[i+1] not in spc:
            mod_regex += '.'

        elif regex[i+1] == '(':
            mod_regex += '.' 

mod_regex += regex[-1]
#print(mod_regex)
print(match(mod_regex, testcase), mod_regex, testcase)