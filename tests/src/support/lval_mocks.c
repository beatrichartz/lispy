#include "lval_mocks.h"

lval* sexpr_double_mock(int count,...) {
  lval* e = lval_sexpr();

  va_list arguments;
  va_start(arguments, count);

  for (int i = 0; i < count; i++) {
    lval* x = lval_double(va_arg(arguments, double));
    lval_add(e, x);
  }

  va_end(arguments);

  return e;
}

lval* sexpr_long_mock(int count,...) {
  lval* e = lval_sexpr();

  va_list arguments;
  va_start(arguments, count);

  for (int i = 0; i < count; i++) {
    lval* x = lval_long(va_arg(arguments, long));
    lval_add(e, x);
  }

  va_end(arguments);

  return e;
}
