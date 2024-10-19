# include <bits/stdc++.h>
using namespace std;
 class info{
    private:
    string pw;
    public:
    string un;
    string getpw(){
        return pw;
    }
    void setpw(string s){
        pw=s;
    }
 };
 int main(){
    string s;
    info i;
    cout<<"Enter your username : "<<endl;
    cin>>i.un;
    cout<<"Enter your password"<<endl;
    cin>>s;
    i.setpw(s);
    return 0;
 }
 