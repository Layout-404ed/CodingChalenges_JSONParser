// challenge: https://codingchallenges.fyi/challenges/challenge-json-parser

// libraries
#include <iostream> // io
#include <string> // strings
#include <fstream> // fileio
#include <filesystem> // file exists, is normal, set directory

// define ansi color codes
#define RESET "\033[0m"
#define RED "\033[31m"

// methods
bool parse(std::fstream& file){
    char f, l; // first and last char
    std::string line = ""; // temp line var
    
    // first char of file
    getline(file, line);
    f = line[0];
    
    //last char of file
    while(getline(file, line))
    {}
    l = line[line.length()-1];
    
    if(f == '{' && l == '}'){ // if valid
        return true;
    }else{
        return false;
    }
}

bool parse(std::fstream& file){
    if(step1(file) && step2(file)){
        return true;
    }else{
        return false;
    }
}

bool step1(std::fstream& file){
    // step 1
    file.seekg(0); // return reading to 0

    char f, l; // first and last char
    std::string line = ""; // temp line var
    
    // first char of file
    file.get(f);

    while(getline(file, line)) // ignore everything else
    {}
    
    //last char of file
    l = line[line.length()-1];
    
    if(f == '{' && l == '}'){ // if valid
        return true;
    }else{
        return false;
    }
}

bool step2(std::fstream& file){
    // consume first char like u did in step 1
}

// main method
int main(void)
{
    do{
        // get path to file
        std::cout << "Input path to file [^C to Quit]: ";
        std::string input; getline(std::cin, input);
        std::filesystem::path path = input;

        // try to run methods
        std::string output = "";
        try{
            std::string path_s = path.string();
            // check if anything is wrong
            if(path_s.substr(path_s.length()-5, 5) != ".json"){ // wrong file type
                throw 415;
            }else if(!std::filesystem::exists(path)){ // not found / doesn't exist
                throw 404;
            }else if(!std::filesystem::is_regular_file(path)){ // not regular file
                throw 422;
            }else{ // is "fine"
                std::fstream file(path); // create file
                if(!step1(file)){
                    throw 400;
                }else{
                    // do wtv
                }
            }
        }
        catch(int error){
            output += std::string(RED) + "ERROR " + std::to_string(error) + ": ";
            if(error == 415){
                output += "WRONG FILE TYPE!";
            }else if(error == 404){
                output += "FILE NOT FOUND!";
            }else if(error == 422){
                output += "FILE NOT REGULAR!";
            }else if(error == 400){
                output += "FILE NOT VALID!";
            }
            output += std::string(RESET) + "\n";
        }
        catch(...){
            output = std::string(RED) + "ERROR: UNKNOWN!\n" + std::string(RESET) + "n";
        }
        
        std::cout << output; // output
    }while(true);
    
    return 0;
}