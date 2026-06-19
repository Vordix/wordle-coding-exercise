#include <iostream>

using namespace std;

//Color definitions
    #define RESET   "\033[0m"
    #define BLACK   "\033[30m"      /* Black */
    #define RED     "\033[31m"      /* Red */
    #define GREEN   "\033[32m"      /* Green */
    #define YELLOW  "\033[33m"      /* Yellow */
    #define BLUE    "\033[34m"      /* Blue */
    #define MAGENTA "\033[35m"      /* Magenta */
    #define CYAN    "\033[36m"      /* Cyan */
    #define WHITE   "\033[37m"      /* White */
    #define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
    #define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
    #define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
    #define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
    #define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
    #define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
    #define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
    #define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
    //source: https://gist.github.com/Kielx/2917687bc30f567d45e15a4577772b02

string chooseNewWordle(){
    static string wordle = "sepia";
    //api call to merriam Webster for random word
    return wordle;
}

bool printBoxes(string wordle, string guess){

    if(guess == wordle){
        cout<<BOLDGREEN<<   "["<<guess[0]<<"]"<<
                            "["<<guess[1]<<"]"<<
                            "["<<guess[2]<<"]"<<
                            "["<<guess[3]<<"]"<<
                            "["<<guess[4]<<"]"<<RESET;

                            return true;
    }else{
            for(int i=0;i<=4;i++){
                if(guess[i] == wordle[i]){
                    cout<<BOLDGREEN<<"["<<guess[i]<<"]"<<RESET;
                } else {
                        bool temp_letter_found = false;
                            for(int j=0;j<=4;j++){
                                
                                if(guess[i] == wordle[j]){
                                    temp_letter_found = true;
                                }
                            }
                            if(temp_letter_found){
                                cout<<BOLDYELLOW<<"["<<guess[i]<<"]"<<RESET;

                            }else{cout<<BOLDBLACK<<"["<<guess[i]<<"]"<<RESET;}
                        }
            } 
        
        }
    cout<<endl;
    return false;
}

string makeInput(){
    cout<<BOLDWHITE<<"--- Choose a Word ---"<<RESET<<endl;
    string input;
    cin>>input;
    return input;
}

void eineRunde(string wordle){
    string guess = makeInput();
    if(printBoxes(wordle,guess)){
        return;
    }else{
        eineRunde(wordle);
    }
}

int main(){
    string wordle = chooseNewWordle();
    eineRunde(wordle);
    return 0;
}
