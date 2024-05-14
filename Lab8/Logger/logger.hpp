//Logger HPP for Lab 8
//Tyler Gargasz
//03-11-21

#ifndef __LOGGER__
#define __LOGGER__

#include <iostream>
#include <fstream>

class Logger {
public:

    static Logger& instance() {
		static Logger log;
		return log;
	}

    
	void report(const std::string& append) {
		file << append;
	}

    ~Logger(){
		if(file.is_open()) {
			file.close();
		}
	}

private:

    Logger() {                                                          //One-time instantiation, other creation prohibited
        
        file.open("log.txt", std::fstream::out | std::fstream::app);
		if(!file.is_open()) {
			std::cout << "Could not open file." << std::endl;
			exit(0);     
        }   
    }

    Logger(const Logger&) = delete;                                     //Copying Prohibited
    Logger operator=(const Logger&) = delete;                           //Assignment Prohibited?

    std::ofstream file;


};
#endif