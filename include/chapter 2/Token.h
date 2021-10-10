#include "TokenKinds.h"
#include <string>

namespace chapter2 {
  struct Token {
    const TokenKind tag;
    constexpr Token(TokenKind tag) : tag(tag) { }
    Token(const Token&) = default;
    Token(Token&&) = default;
    // assignment operators are deleted because of const data member
    virtual ~Token() = default;
  };

  struct Num : public Token {
    int value;
    constexpr Num(int v) : Token(TokenKind::NUM), value(v) { }
  };

  struct Word : public Token {
    std::string lexeme;
    Word(TokenKind tag, std::string s) : Token(tag), lexeme(std::move(s)) { }
  };
}
