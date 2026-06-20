#include <iostream>
#include <time.h>
#include <fstream>

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

string chooseNewWordle(int difficulty){
    int time_beg = time(NULL);

    ifstream words("words.txt");
    string linebuffer;

    srand(time(NULL));
    int random_word_pos;
    if(difficulty == 1){
        random_word_pos = rand() % 2000;
    }
    if(difficulty == 2){
        random_word_pos = rand() % 3000;
    }
    if(difficulty == 3){
        random_word_pos = rand() % 5756;
    }
    

    for(int i=1; i<=random_word_pos; ++i){
        getline(words,linebuffer);
    }
    return linebuffer;
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
    cout<<BOLDWHITE<<"--- Guess a Word ---"<<RESET<<endl;
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

int select_difficulty(){
    int input;
    cout<<"Select a Difficulty:"<<endl;
    cout<<BOLDGREEN<<"1 - normal difficulty"<<RESET<<endl;
    cout<<BOLDYELLOW<<"2 - hard difficulty"<<RESET<<endl;
    cout<<BOLDRED<<"3 - impossible difficulty"<<RESET<<endl;
    cout<<endl;
    cout<<BOLDWHITE<<"--- Choose difficulty Level ---"<<RESET<<endl;
    cin>>input;
    if(!(input == 1 || input == 2 || input == 3)){
        cout<<RED<<"[ERROR] invalid input - please try again"<<RESET<<endl;
        select_difficulty();
    }
    return input;
}

int main(){
    int difficulty = select_difficulty();
    string wordle = chooseNewWordle(difficulty);

    int time_beg = time(NULL);

    eineRunde(wordle);

    int time_end = time(NULL);

    cout<<"You took "<<time_end - time_beg<<" seconds."<<endl;
    return 0;
}
