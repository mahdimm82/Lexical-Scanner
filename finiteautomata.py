def finite_automata(start, alphabet, final_states, transition_functions, tsize, test, ind = 0):

    #check the test case 
    for i in test:
        if i not in alphabet:
            raise ValueError("the testcase is not valid!")

    #check accepted or not
        
    #check end of test case    
    if ind == len(test):
        if start in final_states:
            print("Accepted")
            return
        else:
            print("Rejected")
            return

    #call the function for next states
    else:
        for i in range(tsize):

            trans = True
            if(start == transition_functions[i][0]):
                
                if(transition_functions[i][1] == test[ind]):
                    ind += 1
                    trans = False
                    return finite_automata(transition_functions[i][2], alphabet, final_states, transition_functions, tsize, test, ind)
                
                elif(transition_functions[i][1] == '$'):
                    return finite_automata(transition_functions[i][2], alphabet, final_states, transition_functions, tsize, test, ind)
                
        if(trans):
            ind += 1
            return finite_automata(start, alphabet, final_states, transition_functions, tsize, test, ind)

    print("Rejected")
    return 



#main
states_size = int(input())
states_input = input()

alphabet_size = int(input())
alphabet_input = input()

final_size = int(input())
final_input = input()

transition_functions = []
transition_size = int(input())
for i in range(transition_size):
    transition_input = input()
    lst = []
    lst = transition_input.split(',')
    transition_functions.append(lst)

testcase = input()

states_lst = states_input.split()
alphabet_lst = alphabet_input.split()
final_lst = final_input.split()

# print(states_lst)
# print(alphabet_lst)
# print(final_lst)
# print(transition_functions)

finite_automata(states_lst[0], alphabet_lst, final_lst, transition_functions, transition_size, testcase, 0)