#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>

using namespace std;
struct Register {
    char var[10];
    int alive;
};

Register preg[10];

void substring(char exp[], int st, int end) {
    int i, j = 0;
    char dup[10] = "";
    for (i = st; i < end; i++)
        dup[j++] = exp[i];
    dup[j] = '0';
    strcpy(exp, dup);
}

int getregister(char var[]) {
    int i;
    for (i = 0; i < 10; i++) {
        if (preg[i].alive == 0) {
            strcpy(preg[i].var, var);
            break;
        }
    }
    return i;
}

void getvar(char exp[], char v[]) {
    int i, j = 0;
    char var[10] = "";
    for (i = 0; exp[i] != '\0'; i++)
        if (isalpha(exp[i]))
            var[j++] = exp[i];
        else
            break;
    strcpy(v, var);
}
int isKeyword(char buffer[])
{
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"};

    int i, flag = 0;

    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}
int main() {
	int type;
	cout<<" If you want Code Generation Algorithm Enter 1\n ";
	cout<<"If you want Lexical Analysis Algorithm Enter 2\n ";
	cin>>type;
	switch (type) {
            case  1 :{	
             	cin.ignore(); // To clear the newline character from the buffer
                char basic[10][10], var[10][10], fstr[10], op;
                int i, j, k, reg, vc, flag = 0;

                cout << "\nEnter the Three Address Equations:\n";

                for (i = 0;; i++) {
                    cin.getline(basic[i], 10);
                    if (strcmp(basic[i], "exit") == 0)
                        break;
                }

                cout << "\nThe Equivalent Assembly Code is:\n";

                for (j = 0; j < i; j++) {
                    vc = 0;
                    getvar(basic[j], var[vc++]);
                    strcpy(fstr, var[vc - 1]);
                    substring(basic[j], strlen(var[vc - 1]) + 1, strlen(basic[j]));
                    getvar(basic[j], var[vc++]);
                    reg = getregister(var[vc - 1]);

                    if (preg[reg].alive == 0) {
                        cout << "\nMov R" << reg << "," << var[vc - 1];
                        preg[reg].alive = 1;
                    }

                    op = basic[j][strlen(var[vc - 1])];
                    substring(basic[j], strlen(var[vc - 1]) + 1, strlen(basic[j]));
                    getvar(basic[j], var[vc++]);

                    switch (op) {
                        case '+':
                            cout << "\nAdd";
                            break;
                        case '-':
                            cout << "\nSub";
                            break;
                        case '*':
                            cout << "\nMul";
                            break;
                        case '/':
                            cout << "\nDiv";
                            break;
                    }

                    flag = 1;

                    for (k = 0; k <= reg; k++) {
                        if (strcmp(preg[k].var, var[vc - 1]) == 0) {
                            cout << " R" << k << ", R" << reg;
                            preg[k].alive = 0;
                            flag = 0;
                            break;
                        }
                    }

                    if (flag) {
                        cout << " " << var[vc - 1] << ", R" << reg;
                        cout << "\nMov " << fstr << ", R" << reg;
                    }

                    strcpy(preg[reg].var, var[vc - 3]);
                }
            } break;
            case 2 :{
                char ch2,ch, buffer[15], b[30], logical_op[] = "><", math_op[] = "+-*/=", numer[] = ".0123456789", other[] = ",;\(){}[]'':";
                int mark[256] = {0};
                int i, j = 0, kc = 0, ic = 0, lc = 0, mc = 0, nc = 0, oc = 0, aaa = 0;
                vector<string> k;
                vector<char> id;
                vector<char> lo;
                vector<char> ma;
                vector<string> nu;
                vector<char> ot;

                cout << "Enter the input : \n";
                cin.ignore(); // To clear the newline character from the buffer
                while (cin.get(ch)){
                    for (i = 0; i < 12; ++i)
                    {
                        if (ch == other[i])
                        {
                            int aa = ch;
                            if (mark[aa] != 1)
                            {
                                ot.push_back(ch);
                                mark[aa] = 1;
                                ++oc;
                            }
                        }
                    }

                    for (i = 0; i < 5; ++i)
                    {
                        if (ch == math_op[i])
                        {
                            int aa = ch;
                            if (mark[aa] != 1)
                            {
                                ma.push_back(ch);
                                mark[aa] = 1;
                                ++mc;
                            }
                        }
                    }
                    for (i = 0; i < 2; ++i)
                    {
                        if (ch == logical_op[i])
                        {
                            int aa = ch;
                            if (mark[aa] != 1)
                            {
                                lo.push_back(ch);
                                mark[aa] = 1;
                                ++lc;
                            }
                        }
                    }
                    if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '.' || ch == ' ' || ch == '\n' || ch == ';')
                    {
            
                        if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '.')
                            b[aaa++] = ch;
                        if ((ch == ' ' || ch == '\n' || ch == ';') && (aaa != 0))
                        {
                            b[aaa] = '\0';
                            aaa = 0;
                            char arr[30];
                            strcpy(arr, b);
                            nu.push_back(arr);
                            ++nc;
                        }
                    }
            
                    if (isalnum(ch))
                    {
                        buffer[j++] = ch;
                    }
                    else if ((ch == ' ' || ch == '\n') && (j != 0))
                    {
                        buffer[j] = '\0';
                        j = 0;

                        if (isKeyword(buffer) == 1)
                        {
                            k.push_back(buffer);
                            ++kc;
                        }
                        else
                        {
                            if (buffer[0] >= 97 && buffer[0] <= 122)
                            {
                               if (mark[buffer[0] - 'a'] != 1)
                               {
                                   id.push_back(buffer[0]);
                                   id.push_back(buffer[1]);
                                   id.push_back(buffer[2]);      
                                   id.push_back(buffer[3]);                        
                                   ++ic;
                                   mark[buffer[0] - 'a'] = 1;
                               }
                            }
                        }
                    }
                    if(ch == '\n')
	                	{
                    	break;
		                }
                }
                cout << "\nKeywords: ";
                for (int f = 0; f < kc; ++f)
                {
                    if (f == kc - 1)
                    {
                        cout << k[f] << "\n";
                    }
                    else
                    {
                        cout << k[f] << ", ";
                    }
                }
                cout << "Identifiers: ";
                for (int f = 0; f < 4; ++f)
                {
                    if (f == 4 - 1)
                    {
                        cout << id[f] << "\n";
                    }
                    else
                    {
                        cout << id[f] << ", ";
                    }
                }
                cout << "Math Operators: ";
                for (int f = 0; f < mc; ++f)
                {
                    if (f == mc - 1)
                    {
                        cout << ma[f] << "\n";
                    }
                    else
                    {
                        cout << ma[f] << ", ";
                    }
                }
                cout << "Logical Operators: ";
                for (int f = 0; f < lc; ++f)
                {
                    if (f == lc - 1)
                    {
                        cout << lo[f] << "\n";
                    }
                    else
                    {
                        cout << lo[f] << ", ";
                    }
                }
                cout << "Numerical Values: ";
                for (int f = 0; f < nc; ++f)
                {
                    if (f == nc - 1)
                    {
                        cout << nu[f] << "\n";
                    }
                    else
                    {
                        cout << nu[f] << ", ";
                    }
                }
                cout << "Special Character: ";
                for (int f = 0; f < oc; ++f)
                {
                    if (f == oc - 1)
                    {
                        cout << ot[f] << "\n";
                    }
                    else
                    {
                        cout << ot[f] << " ";
                    }
                }

                }break;
            default:
                 	cout << "Enter only 1 or 2";
            }
            return 0;
        }
