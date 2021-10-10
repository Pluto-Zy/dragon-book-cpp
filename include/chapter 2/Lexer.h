#include <unordered_map>
#include <memory>
#include <iostream>

namespace chapter2 {
  struct Token;
  struct Word;

  class Lexer {
  public:
    Lexer();
    Lexer(std::istream& in);

    std::shared_ptr<Token> scan();
  private:
    int  _line;   // line number
    char _peek;   // last character
    std::istream& _in;
    std::unordered_map<std::string, std::shared_ptr<Word>> words;

    void reserve(std::shared_ptr<Word> word);
  };
}
