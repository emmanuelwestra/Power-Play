#include<iostream>
using namespace std;

int main () {

    float num1, num2;
    char operation;
    float result;
    
    //Ask user input
    cout<<"\nEnter first number, operator, second number (with spaces in between): ";
    cin>>num1>>operation>>num2;
    
    switch(operation)
    {
        case '+': result = num1 + num2;
                  cout << "The addition of " << num1 << " and " << num2 << " is: " << result << endl;
                  break;

        case '-': result = num1 - num2;
                  cout << "The subtraction of " <f< num1 << " and " << num2 << " is: " << result << endl;
                  break;

        case '*': result = num1 * num2;
                  cout << "The multiplication of " << num1 << " and " << num2 << " is: " << result << endl;
                  break;

        case '/': if (num2 != 0)
                  {
                      result = num1 / num2;
                      cout << "The division of " << num1 << " and " << " by " << num2 << " is: " << result << endl;
                  }
                  else
                  {
                      cout << "Division by 0 is not allowed." << endl;
                  }
                  break;

        default: cout << "Invalid operation. Please enter '+' for addition, '-' for subtraction, '*' for multiplication, or '/' for division." << endl;
    }
    
    return 0;
}