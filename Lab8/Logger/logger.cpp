//Main for Logger, Lab 8
//Tyler Gargasz
//03-11-21

#include "logger.hpp"

int main() {
    Logger& log1 = Logger::instance();
    log1.report("Hello\n");
    log1.report("World\n");
    Logger& log2 = Logger::instance();
    log2.report("Goodbye\n");
    log2.report("World\n");
}