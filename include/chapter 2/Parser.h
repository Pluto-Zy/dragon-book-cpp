/*
* A **parser** that translates arithmetic expressions into equivalent postfix 
* expression forms.
* 
* From the dragon book, the grammer
*   expr -> expr + term | expr - term | term
*   term -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
* 
* Translation schemes:
*   expr -> expr + term { print('+') }
*         | expr - term { print('-') }
*         | term
*   term -> 0           { print('0') }
*         | 1           { print('1') }
*           ...
*         | 9           { print('9') }
* 
* Since the grammer above is left recursive, it will loop forever.
* 
* Apply the rule that
* 
*   A -> Aa | Ab | c
* 
* is equivalent to 
* 
*   A -> cR
*   R -> aR | bR | epsilon
* 
* In this example, 
*   A is expr, 
*   a is '+ term { print('+') }', 
*   b is '- term { print('-') }',
*   c is term,
* 
* so it is equivalent to
* 
*   expr -> term rest
*   rest -> + term { print('+') } rest
*         | - term { print('-') } rest
*         | epsilon
*   term -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
*/

// According to the grammer above:

/*
void expr() {
  term(); rest();
}

void rest() {
  if (lookahead == '+') {
    match('+'); term(); print('+'); rest();
  }
  else if (lookahead == '-') {
    match('-'); term(); print('-'); rest();
  }
}

void term() {
  if (condition) {  // check whether `lookahead` is a digit
    int temp = lookahead; match(lookahead); print(temp);  
  }
  else
    // report error
}
*/

// We can change the rest() function from recursion to iteration 
// because it is **rail recursive** in the case of '+' and '-'
/*
void rest() {
  while (true) {
    if (lookahead == '+') {
      match('+'); term(); print('+');
    }
    else if (lookahead == '-') {
      match('-'); term(); print('-');
    }
    else
      break;
  }
}
*/
// and merge rest() to expr()

// Complete code
#include <iostream>

namespace chapter2 {
  class Parser {
  public:
    Parser();
    Parser(std::istream& in, std::ostream& out);

    void expr();
    void term();
    void match(int val);
    void print(int val);
    [[noreturn]] void report_error() const;
  private:
    std::istream& _in;
    std::ostream& _out;
    int lookahead;
  };
}
