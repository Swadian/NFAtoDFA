#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

struct transition{char l;string dest;};

string SortString(string input)
{
    vector<char> v;

    for(int i=0;i<(int)input.length();i++)
        v.push_back(input[i]);
    sort(v.begin(),v.end());
    string out;
    for(auto it=v.begin();it!=v.end();it++)
        out+=*it;
    return out;
}
int main()
{
    ifstream fin("NFA.txt");
    ofstream fout("DFA.txt");
    int n;//number of states
    fin>>n;
    set<string> DFAstates;
    string s;
    for(int i=0;i<n;i++)
        {
            fin>>s;
            DFAstates.insert(s);
        }
    int Numararce;
    fin>>Numararce;
    unordered_map<string,vector<transition>> arce;
    set<char> alphabet;
    string start,dest;
    transition t;
    for(int i=0;i<Numararce;i++)
    {
        fin>>start>>t.dest>>t.l;
        alphabet.insert(t.l);
        arce[start].push_back(t);
    }
    string current_state;
    queue<string> process;//procesez starile
    for(auto it=DFAstates.begin();it!=DFAstates.end();it++)
        process.push(*it);//inserez starile initiale in queue
    string ss;
    while(!process.empty())
    {
        current_state=process.front();
        process.pop();
        for(auto it=alphabet.begin();it!=alphabet.end();it++)//pentru fiecare litera din alfabet
        {
            ss="";//outputul din parcurgerea cu un caracter
            char c=*it;//litera curenta din alfabet
            for(int j=0;j<(int)current_state.length();j++)//procesez substarile din starea curent
                {
                string l{current_state[j]};
                for(int i=0;i<(int)arce[l].size();i++)//parcurg lista de arce
                    if(arce[current_state][i].l==c)
                        ss+=arce[current_state][i].dest;
                }
                ss=SortString(ss);
                if(ss!="")//daca nu e stare vida
                {
                    if(DFAstates.find(ss)==DFAstates.end())//daca e un subset nou
                    {
                        process.push(ss);
                    }
                    DFAstates.insert(ss);//inserez in setul de stari
                    t.dest=ss;
                    t.l=c;
                    arce[current_state].push_back(t);//creez tranzitia
                    Numararce++;
                }
        }
    }
    fout<<DFAstates.size()<<'\n';
    for(auto it=DFAstates.begin();it!=DFAstates.end();it++)
        fout<<*it<<' ';
    //output stari dfa
        fout<<'\n';
        fout<<Numararce<<'\n';
    for(auto it=DFAstates.begin();it!=DFAstates.end();it++)
    {
        for(int i=0;i<(int)arce[*it].size();i++)
            fout<<*it<<' '<<arce[*it][i].dest<<' '<<arce[*it][i].l<<'\n';
    }
    return 0;
}
