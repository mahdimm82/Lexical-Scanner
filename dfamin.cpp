#include <iostream>
using namespace std;


bool exist(string final[1000], int size, string a)
{
    bool ex = false;

    for(int i = 0; i < size; i++)
    {
        if(final[i] == a)
        {
            ex = true;
            break;
        }
    }

    if(ex)
        return true;
    else
        return false;
}


int get_index(string arr[1000], int size, string s)
{
    for(int i = 0; i < size; i++)
    {
        if(s == arr[i])
            return i;
    }
    return -1;
}

void split (string str, char seperator, string strings[1000])  
{  
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {  
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }     
}  


int main()
{
    //input values

    int states_size, alphabet_size, final_size, trans_size;
    
    cin >> states_size;
    string states[states_size];
    for(int i = 0; i < states_size; i++)
    {
        cin >> states[i];
    }

    cin >> alphabet_size;
    string alphabet[alphabet_size];

    for(int i = 0; i < alphabet_size; i++)
    {
        cin >> alphabet[i];
    }

    cin >> final_size;
    string final[final_size];

    for(int i = 0; i < final_size; i++)
    {
        cin >> final[i];
    }

    cin >> trans_size;
    string transitions[trans_size][3];

    for(int i = 0; i < trans_size; i++)
    {
        string strings[3];
        string str ="";
        cin >> str;
        split(str, ',', strings);
        transitions[i][0] = strings[0];
        transitions[i][1] = strings[1];
        transitions[i][2] = strings[2];
    }


    //creating table

    string res[1000][alphabet_size+2];
    int ind = 0;

    for(int i = 0; i < states_size; i++)
    {
        ind = i;
        res[i][0] += states[i];

        for(int j = 0; j < trans_size; j++)
        {
            if(transitions[j][0] == states[i])
            {
                for(int x = 0; x < alphabet_size; x++)
                {
                    if(transitions[j][1] == alphabet[x])
                    {
                        res[i][x+1] += transitions[j][2];
                    }
                }
            }
        }
    }

    bool table[states_size][states_size] = {false};

    for(int i = 0; i < states_size; i++)
    {
        for(int j = i+1; j < states_size; j++)
        {
            if(exist(final, final_size, res[i][0]) == exist(final, final_size, res[j][0]))
            {
                table[i][j] = true;
            }
        }
    }

    for(int i = 0; i < states_size; i++)
    {
        for(int j = i+1; j < states_size; j++)
        {
            if(table[i][j])
            {
                for(int x = i; x < alphabet_size; x++)
                {
                    if(!table[get_index(states, states_size, res[i][x])][get_index(states, states_size, res[j][x])])
                    {
                        table[i][j] = false;
                    }
                }
            }
        }
    }

    int final_result = states_size;


    for(int i = 0; i < states_size; i++)
    {
        for(int j = i+1; j < states_size; j++)
        {
            // cout << table[i][j] << " ";
            if(table[i][j] == 1)
            {
                final_result--;
                if(table[j][i] == 1)
                {
                    table[j][i] = 0;
                }
            }
        }
        // cout << endl;
    }

    cout << final_result << " ";    

    return 52;
}
