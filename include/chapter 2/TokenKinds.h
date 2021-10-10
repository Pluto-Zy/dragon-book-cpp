namespace chapter2 {
  enum class TokenKind : unsigned short {
    /* 0 - 255 are reserved for characters */
    plus            = '+',
    minus           = '-',
    star            = '*',
    slash           = '/',
    left_paren      = '(',
    right_paren     = ')',

    NUM             = 256,
    ID              = 257,
    TRUE            = 258,
    FALSE           = 259,
  };
}