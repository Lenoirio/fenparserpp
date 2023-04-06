# FEN-Parser
fenparserpp is a simple C++ (>= C++17) library to parse a chess position in the de-facto standard FEN.

Further information about FEN can be found at: [FEN notation](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation)

**Disclaimer:** I'm working as a full-time Java-developer and recently I found joy in using C++ again (after 15 years without using it). I'm aware that C++ programmers usually use another naming scheme for e.g. method-names but I don't want to make the transition between both worlds harder for me than it already is ;-) 

## Usage
In order to use this parser, just include the files *fenparserpp.cpp* and *fenparserpp.h* in your project.
The makefile in this repository is only used to generate an automated test-suite.

### Result of the parsing
The parser is using a listener (interface described in the virtual class *BoardListener*).
You can either implement that listener with your own implementation to fill your own data-structure while parsing.
Or you might want to pass an object of the *SimpleBoard* class which is a simple container for the chess position (including castling-rights, en-passant etc.).
Everything is kept in the namespace *fenparserpp*

For usage, please just take a look at the test-cases in the file *parsertest.cpp*

### Simple usage example
        FENParser parser;
        SimpleBoard board;
        bool ok = parser.parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

Whereas *ok* will be *true* if parsing did not encounter errors.
*board* will be filled with the information from the FEN-string and you can use simple getters to get information of the position.
