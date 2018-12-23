#include<iostream>
#include<cmath>
using namespace std;

int main(){
    double sum = 0;
    for(int i=2;i<700;i++){
        double term = 0.01 * (i-1) * pow(0.99,i-2) * 0.01;
        sum += term;
        cout << i <<" : " <<sum<<endl;
        if(sum > 0.99){
            break;
        }
    }
}