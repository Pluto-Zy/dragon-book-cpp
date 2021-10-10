#include "Parser.h"

/*
* expr -> term rest
* rest -> + term { print('+') } rest
*       | - term { print('-') } rest
*       | epsilon
* term -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
*/
namespace chapter2 {
  Parser::Parser() : Parser(std::cin, std::cout) { }

  Parser::Parser(std::istream& in, std::ostream& out)
    : _in(in), _out(out), lookahead(_in.get()) { }

  void Parser::expr() {
    term();
    // rest
    while (true) {
      if (lookahead == '+') {
        match('+');
        term();
        print('+');
      }
      else if (lookahead == '-') {
        match('-');
        term();
        print('-');
      }
      else
        break;
    }
  }

  void Parser::term() {
    if (std::isdigit(lookahead)) {
      // lookahead is changed after calling match()
      // Changing the order here has no effect.
      print(lookahead);
      match(lookahead);
    }
    else
      report_error();
  }

  void Parser::match(int val) {
    if (lookahead == val) {
      lookahead = _in.get();
    }
    else
      report_error();
  }

  void Parser::print(int val) {
    _out << static_cast<char>(val);
  }

  void Parser::report_error() const {
    throw std::exception("syntax error");
  }
}
