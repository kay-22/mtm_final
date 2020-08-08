#include "Instruction.h"

using std::map;
using std::string;
using graph::Instruction;
using graph::Declaration;
using graph::Quit;
using graph::Reset;
using graph::Delete;
using graph::Print;
using graph::Save;
using graph::Load;
using graph::Empty;

const char Declaration::DECLARATION_CHAR = '=';
const map<Instruction::keyword, string> Instruction::KEYWORDS = {
                                                                    {PRINT, "print"}, 
                                                                    {DELETE, "delete"},
                                                                    {RESET, "reset"}, 
                                                                    {QUIT, "quit"}, 
                                                                    {SAVE, "save"}, 
                                                                    {LOAD, "load"}
                                                                };

Instruction::code Declaration::execute(std::set<Graph>& who_set)  {return okCode;}
Instruction::code Print::execute(std::set<Graph>& who_set)  {return okCode;}
Instruction::code Delete::execute(std::set<Graph>& who_set) {return okCode;}
Instruction::code Reset::execute(std::set<Graph>& who_set) {return okCode;}
Instruction::code Quit::execute(std::set<Graph>& who_set) {return okCode;}
Instruction::code Save::execute(std::set<Graph>& who_set) {return okCode;}
Instruction::code Load::execute(std::set<Graph>& who_set) {return okCode;}
Instruction::code Empty::execute(std::set<Graph>& who_set) {return okCode;}