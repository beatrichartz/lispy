#include "print.h"

void print_lval_expr(lval *v, char open, char close) {
    putchar(open);
    for (int i = 0; i < v->count; i++) {
        print_lval(v->cell[i]);

        if (i != (v->count - 1)) {
            putchar(' ');
        }
    }
    putchar(close);
}

void print_lval(lval *v) {
    switch (v->type) {
    case LVAL_LONG:
        printf("%li", v->data.l);
        break;

    case LVAL_DOUBLE:
        printf("%f", v->data.d);
        break;

    case LVAL_SYM:
        printf("%s", v->sym);
        break;

    case LVAL_SEXPR:
        print_lval_expr(v, '(', ')');
        break;

    case LVAL_QEXPR:
        print_lval_expr(v, '{', '}');
        break;

    case LVAL_ERR:
        printf("Error: %s", v->err);
        break;

    default:
        printf("Unknown lval type: %d\n", v->type);
        break;
    }
}

void println_lval(lval *v) {
    print_lval(v);
    putchar('\n');
}
