#include <iostream>
#include <vector>

using namespace std;

class Fibonacci{
public:
    vector<int> num1_UBFR;
    vector<int> num2_UBFR;
    vector<int> num1_STFR;
    vector<int> num2_STFR;
    vector<int> result_STFR;
    vector<int> base_fibonacci;
    int digit;
    int value1, value2;

    Fibonacci(int input, int input1, int input2){
        value1 = input1;
        value2 = input2;
        digit = input;

        int base0 = 0, base1 = 1;
        for(int i = 0; i <= input; i++){
            base_fibonacci.push_back(base0+base1);
            base0 = base1;
            base1 = base_fibonacci[i];
            num1_UBFR.push_back(0);
            num2_UBFR.push_back(0);
            if(i%2 == 0) {
                num1_STFR.push_back(0);
                num2_STFR.push_back(0);
                result_STFR.push_back(0);
            }
        }
    }

    void Decimal_UBFR(){
        int start = digit-1;
        while(start > 0 && value1 > 0){
            if(value1 < base_fibonacci[start-1]){
                start -= 1;
            } else {
                num1_UBFR[start] = 1;
                value1 -= base_fibonacci[start-1];
                start -= 2;
            }
        }
        start = digit-1;
        while(start > 0 && value2 > 0){
            if(value2 < base_fibonacci[start-1]){
                start -= 1;
            } else {
                num2_UBFR[start] = 1;
                value2 -= base_fibonacci[start-1];
                start -= 2;
            }
        }
    }

    void UBFR_STFR(){
        for(int i = 0; i < num1_STFR.size()-1; i++){
            num1_STFR[i] = num1_UBFR[i*2] + num1_UBFR[i*2+1] - num1_UBFR[i*2+2];
            num2_STFR[i] = num2_UBFR[i*2] + num2_UBFR[i*2+1] - num2_UBFR[i*2+2];
        }

    }

    void Addition(){
        this->Decimal_UBFR();
        this->UBFR_STFR();
        for(int i = 0; i < result_STFR.size(); i++){
            result_STFR[i] = num1_STFR[i] + num2_STFR[i];
        }
        bool flag = true;
        while(flag){
            int i_h = check_highest();
            if(i_h < 0){
                flag = false;
            } else {
                correct(i_h);
            }
        }
    }
    int check_highest(){
        int i = result_STFR.size()-2;
        while(i >= 0){
            if(abs(result_STFR[i]) >= 2) {
                break;
            } else {
                i--;
            }
        }
        return i;
    }
    void correct(int i_h){
        if(result_STFR[i_h] == 2 || result_STFR[i_h] == 3){
            result_STFR[i_h+1]++;
            if(i_h != 0) {
                result_STFR[i_h - 1]++;
            }
            if(result_STFR[i_h] == 2){
                result_STFR[i_h] = -1;
            } else {
                result_STFR[i_h] = 0;
            }
        } else {
            result_STFR[i_h+1]--;
            if(i_h != 0) {
                result_STFR[i_h - 1]--;
            }
            if(result_STFR[i_h] == -2){
                result_STFR[i_h] = 1;
            } else {
                result_STFR[i_h] = 0;
            }
        }
    }
};

int main() {
    int input1, input2;
    input1 = 6;
    input2 = 14;
    Fibonacci Fib(8, input1, input2);
    Fib.Addition();
    /*
    for(int i = 0; i < Fib.num1_UBFR.size(); i++)
        cout << Fib.num1_UBFR[i] << endl;
    */
    for(int i = 0; i < Fib.num2_STFR.size(); i++){
        cout << Fib.result_STFR[i] << endl;
    }

    return 0;
}