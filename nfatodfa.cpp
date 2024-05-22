#include <iostream>
using namespace std;


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
                if(transitions[j][1] == "$")
                {
                    res[i][alphabet_size+1] += transitions[j][2];
                }
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

    //hande epsilons
    for(int i = 0; i <= ind; i++)
    {
        if(res[i][alphabet_size+1] != "")
        {
            for(int j = 0; j < ind; j++)
            {
                if(res[j][0] == res[i][alphabet_size+1])
                {
                    for(int x = 1; x < alphabet_size+2; x++)
                    {
                        res[i][x] += " ";
                        res[i][x] += res[j][x];
                    }
                    break;
                }
            }
        }
    }

    //add new nodes and calculate 

    for(int i = 0; i <= ind; i++)
    {
        for(int j = 1; j < alphabet_size+1; j++)
        {    
            bool istekrari = false;
            for(int z = 0; z <= ind; z++)
            {
                if(res[z][0] == res[i][j])
                {
                    istekrari = true;
                    break;
                }
            }

            if(!istekrari)
            {
                string strings[10];
                split(res[i][j], ' ', strings);
                ind++;
                res[ind][0] = res[i][j];
                                
                for(int y = 0; y < size(strings); y++)
                {
                    for(int z = 0; z < ind; z++)
                    {
                        if(res[z][0] == strings[y])
                        {
                            for(int x = 1; x < alphabet_size+1; x++)
                            {
                                res[ind][x] += res[z][x];
                            }
                        }
                    }
                }   
            }
        }
    }

    //print the result
    cout << ind;

    return 52;
}