#include "Lexer.h"
#include <iostream>
#include "Token.h"

namespace chapter2 {
  Lexer::Lexer() : Lexer(std::cin) { }
  Lexer::Lexer(std::istream& in) : _line(0), _peek(' '), _in(in) {
    reserve(std::make_shared<Word>(TokenKind::TRUE,  "true"));
    reserve(std::make_shared<Word>(TokenKind::FALSE, "false"));
  }

  void Lexer::reserve(std::shared_ptr<Word> word) {
    // we need this statement
    // because if we write 
    // words.emplace(std::piecewise_construct, std::forward_as_tuple(word->lexeme), std::forward_as_tuple(std::move(word)));
    // it will cause undefined-behaviour
    std::string key = word->lexeme;
    words.emplace(std::piecewise_construct, 
      std::forward_as_tuple(key), std::forward_as_tuple(std::move(word)));
  }

  std::shared_ptr<Token> Lexer::scan() {
    // skip space
    for (;; _peek = _in.get()) {
      if (_peek == '\n')
        ++_line;
      else if (std::isspace(_peek))
        continue;
      else
        break;
    }

    // now _peek is not a space
    // num
    if (std::isdigit(_peek)) {
      int value = 0;
      do {
        value = value * 10 + (_peek - '0');
      } while (std::isdigit(_peek = _in.get()));
      return std::make_shared<Num>(value);
    }
    // name
    if (std::isalpha(_peek)) {
      std::string name;
      do {
        name += _peek;
      } while (std::isalnum(_peek = _in.get()));
      // search name
      auto iter = words.find(name);
      if (iter != words.end())
        return iter->second;
      std::shared_ptr<Word> w = std::make_shared<Word>(TokenKind::ID, name);
      iter = words.emplace_hint(iter, std::move(name), w);
      return w;
    }
    // operators
    char temp = _peek;
    _peek = ' ';
    return std::make_shared<Token>(static_cast<TokenKind>(temp));
  }
}