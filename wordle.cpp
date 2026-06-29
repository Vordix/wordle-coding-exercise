#include <iostream>
#include <time.h>
#include <fstream>
#include <map>

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

class Wordle_bot{
    public:
char solution[5][2];
char correct_letters[5];
char incorrect_letters[21];
char partially_correct_letters_with_incorrect_pos[20][2];

void bot_guess(string wordle,string guess){
    fstream file("words.txt");
    for(int i=0;i<=4;i++){
        if(guess[i] == wordle[i]){
            correct_letters[i] = guess[i];
        }else{
            for(int j=0;j<=4;j++){
                if(!(i == j)){
                    if(guess[i] == wordle[j]){
                        int l=0;
                        while(!(partially_correct_letters_with_incorrect_pos[l][0] == '0')){
                            if(partially_correct_letters_with_incorrect_pos[l][0] != guess[i]){
                                l++;
                            }
                            else{
                                return;
                            }
                        }
                        partially_correct_letters_with_incorrect_pos[l][0] = guess[i];
                        partially_correct_letters_with_incorrect_pos[l][1] = char(i);
                    }
                    else{
                        int t=0;
                        while(!(incorrect_letters[t]=='0')){
                            t++;
                        }
                        incorrect_letters[t] = guess[i];
                    }

                }
            }
        }
    }
}


void play(string wordle){
    
    bot_guess(wordle,"nanny");
    print_all_arrays();
}

void print_all_arrays(){
    cout<<"correct_letters: "<<endl;
    for(int i = 1; i<= (sizeof(correct_letters) / sizeof(correct_letters[0])); i++){
        cout<<correct_letters[(i-1)]<<" ";
    }
    cout<<endl;

    cout<<"incorrect_letters: "<<endl;
    for(int i = 1; i<= (sizeof(incorrect_letters) / sizeof(incorrect_letters[0])); i++){
        cout<<incorrect_letters[(i-1)]<<" ";
    }
    cout<<endl;

    cout<<"partially_correct_letters_with_incorrect_pos: "<<endl;
    for(int i = 1; i<=20; i++){
        for(int j=0;j<=1;j++){
            cout<<partially_correct_letters_with_incorrect_pos[(i-1)][j]<<" ";
        }
        
    }
    cout<<endl;
}

Wordle_bot(){
    for(int i=0;i<=4;i++){
        correct_letters[i] = '0';
        for(int j=0; j<=1;j++){
            solution[i][j] = '0';
        }
    }
    for(int i=0; i<=20;i++){
        incorrect_letters[i] = '0';
    }
    for(int i=0;i<=19;i++){
        for(int j=0;j<=1;j++){
            partially_correct_letters_with_incorrect_pos[i][j] = '0';
        }
    }
}; //Constructor

};

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

bool is_guess_real_word(string guess){
    ifstream words("words.txt");
    string linebuffer;

    for(int i=1; i<=5756; i++){
        getline(words,linebuffer);
        if(guess == linebuffer){
            return true;
        }
    }
    cout<<BOLDRED<<"[ERROR]"<<RESET<<RED<<" guessed word is not in word list - guess a different word"<<RESET<<endl;
    return false;
}

void write_boxes_when_partially_correct(char solution[5][2]){

    for(int i=0;i<=4;i++){
        if(solution[i][1] == 'b'){
            cout<<BOLDBLACK<<'['<<solution[i][0]<<']'<<RESET;
        }else{
            if(solution[i][1] == 'y'){
                cout<<BOLDYELLOW<<'['<<solution[i][0]<<']'<<RESET;
            }else{
                if(solution[i][1] == 'g'){
                    cout<<BOLDGREEN<<'['<<solution[i][0]<<']'<<RESET;
                }
            }
        }
    }
    cout<<endl;
}

bool is_correct_and_prints(string wordle, string guess, map<char,char> &farben_map){

    if(guess == wordle){
        cout<<BOLDGREEN<<   "["<<guess[0]<<"]"<<
                            "["<<guess[1]<<"]"<<
                            "["<<guess[2]<<"]"<<
                            "["<<guess[3]<<"]"<<
                            "["<<guess[4]<<"]"<<RESET;

                            return true;
    }else{ 

        char solution[5][2];

        for(int i=0; i<=4;i++){
            solution[i][0] = guess[i];
            solution[i][1] = 'b'; //b = black -> char not found as default

            if(farben_map[solution[i][0]] == 'w'){
                farben_map[solution[i][0]] = 'b';
            }

            if(guess[i] == wordle[i]){
                solution[i][0] = wordle[i];
                solution[i][1] = 'g'; //g = green -> char is in wordle and even in the correct place

                farben_map[wordle[i]] = 'g';

                wordle[i] = '0'; //crosses out the already used up char so it cannot be used again for a false positive as a yellow char
                
            }
        }
        for(int i=0; i<=4;i++){
            for(int j=0; j<=4;j++){
                if(guess[i] == wordle[j]){
                    if(!(solution[i][1]=='g')){
                        solution[i][0] = wordle[j];
                        solution[i][1] = 'y'; //y = yellow -> char is in there somewhere but not on the correct position 

                        if(farben_map[solution[i][0]] != 'g'){  //green letters should not be overwritten
                            farben_map[solution[i][0]] = 'y';
                        } 
                        wordle[j] = '0';
                        break;
                    }
                }
            }
        }
        write_boxes_when_partially_correct(solution);
    }
    return false;
}

string makeInput(){
    cout<<BOLDWHITE<<"--- Guess a Word ---"<<RESET<<endl;
    string input;
    cin>>input;

    return input;
}

void print_farben_map(map<char,char> &farben_map){
    for(const auto& item : farben_map){
        if(item.second == 'w'){
            cout<<RESET<<WHITE<<"["<<item.first<<"]";
        }else{
            if(item.second == 'b'){
                cout<<BOLDBLACK<<"["<<item.first<<"]";
            }else{
                if(item.second == 'y'){
                    cout<<BOLDYELLOW<<"["<<item.first<<"]";
                }else{
                    if(item.second == 'g'){
                        cout<<BOLDGREEN<<"["<<item.first<<"]";
                    }
                }
            }
        }
    }
    cout<<RESET<<endl;
}

void eineRunde(string wordle, int &guess_counter, map<char,char> &farben_map){
    string guess = makeInput();

    if(guess == "s"){
        print_farben_map(farben_map);
        eineRunde(wordle,guess_counter,farben_map);

    }else{      //if you dont want to see the statistics
        while(!(is_guess_real_word(guess))){
        guess = makeInput();
    }

    guess_counter++;

    if(is_correct_and_prints(wordle,guess,farben_map)){
        return;
    }else{
        eineRunde(wordle, guess_counter, farben_map);
    }
    return;
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

void mache_farben_map(map<char,char> &farben_map ){
    farben_map.insert({'a','w'});
    farben_map.insert({'b','w'});
    farben_map.insert({'c','w'});
    farben_map.insert({'d','w'});
    farben_map.insert({'e','w'});
    farben_map.insert({'f','w'});
    farben_map.insert({'g','w'});
    farben_map.insert({'h','w'});
    farben_map.insert({'i','w'});
    farben_map.insert({'j','w'});
    farben_map.insert({'k','w'});
    farben_map.insert({'l','w'});
    farben_map.insert({'m','w'});
    farben_map.insert({'n','w'});
    farben_map.insert({'o','w'});
    farben_map.insert({'p','w'});
    farben_map.insert({'q','w'});
    farben_map.insert({'r','w'});
    farben_map.insert({'s','w'});
    farben_map.insert({'t','w'});
    farben_map.insert({'u','w'});
    farben_map.insert({'v','w'});
    farben_map.insert({'w','w'});
    farben_map.insert({'x','w'});
    farben_map.insert({'y','w'});
    farben_map.insert({'z','w'});
}

int main(){
    int difficulty = select_difficulty();

    map<char,char> farben_map;
    mache_farben_map(farben_map);

    int guess_counter = 0;

    string wordle = chooseNewWordle(difficulty);
    
    Wordle_bot bot;
    bot.play(wordle);

    int time_beg = time(NULL);

    eineRunde(wordle,guess_counter,farben_map);

    int time_end = time(NULL);

    cout<<"You took "<<time_end - time_beg<<" seconds and "<<guess_counter<<" guesses"<<endl;
    return 0;
}
