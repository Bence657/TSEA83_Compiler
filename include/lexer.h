#ifndef COM_LEXER_H
#define COM_LEXER_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <regex>

#include "tokens.h"

#define BUFFER_SIZE 4096
#define READ_SIZE BUFFER_SIZE - 1

#define MAX_TOKEN_SIZE 64

class lexer {
private:

    // Keyword map
    std::unordered_map<std::string, keyword_token*> reserved_words;
    
    // Input stream and double buffer
    std::ifstream file;
    char *buffer_1;
    const char* buffer_1_end;

    char *buffer_2;
    const char* buffer_2_end;
    // True if currently on buffer 1, false if on buffer 2
    bool buffer_switch;

    // Pointers for reading
    char *lexeme_start;
    char *forward;

    // Current line
    int line;
    
    // Regular expressions
    std::regex identifier_regex;
    std::regex int_literal_regex;
    std::regex str_literal_regex;
    std::regex whitespace_regex;
    std::regex half_str_literal_regex;

    // Converts an ASCII digit character to its corresponding integer digit
    int char_to_digit(char c);
    
    // Reads from the file into the non-current buffer and switches to it
    char* switch_buffer();

    // Handles tokens that are split between two buffers
    void handle_split(std::regex r, std::string& result, unsigned int size);

    // Returns a pointer to the current buffer being read from
    char* get_current_buffer();

    const char* get_current_buffer_end();

public:
    lexer(std::string filename);

    // Acquires the next token from the buffer
    token* get_next_token();

};

#endif