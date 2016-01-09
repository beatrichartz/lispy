#include "math.h"

lval *builtin_op_long(lval *x, char *op, lval *y) {
    if (strcmp(op, "+") == 0) {
        x->data.l += y->data.l;
        return x;
    }
    if (strcmp(op, "add") == 0) {
        x->data.l += y->data.l;
        return x;
    }

    if (strcmp(op, "-") == 0) {
        x->data.l -= y->data.l;
        return x;
    }
    if (strcmp(op, "sub") == 0) {
        x->data.l -= y->data.l;
        return x;
    }

    if (strcmp(op, "*") == 0) {
        x->data.l *= y->data.l;
        return x;
    }
    if (strcmp(op, "mul") == 0) {
        x->data.l *= y->data.l;
        return x;
    }

    int is_div = (strcmp(op, "/") == 0 || strcmp(op, "div") == 0.0);
    if (is_div && y->data.l == 0) {
        return lval_err("division by zero");
    } else if (is_div) {
        x->data.l /= y->data.l;
        return x;
    }

    if (strcmp(op, "%") == 0) {
        x->data.l %= y->data.l;
        return x;
    }
    if (strcmp(op, "mod") == 0) {
        x->data.l %= y->data.l;
        return x;
    }

    if (strcmp(op, "^") == 0) {
        x->data.l = pow(x->data.l, y->data.l);
        return x;
    }
    if (strcmp(op, "pow") == 0) {
        x->data.l = pow(x->data.l, y->data.l);
        return x;
    }

    int is_max = (strcmp(op, "max") == 0);
    if (is_max && x->data.l < y->data.l) {
        x->data.l = y->data.l;
        return x;
    } else if (is_max) {
        return x;
    }

    int is_min = (strcmp(op, "min") == 0);
    if (is_min && x->data.l > y->data.l) {
        x->data.l = y->data.l;
        return x;
    } else if (is_min) {
        return x;
    }

    return lval_err("Unknown operation");
}

lval *builtin_op_double(lval *x, char *op, lval *y) {
    if (strcmp(op, "+") == 0) {
        x->data.d += y->data.d;
        return x;
    }
    if (strcmp(op, "add") == 0) {
        x->data.d += y->data.d;
        return x;
    }

    if (strcmp(op, "-") == 0) {
        x->data.d -= y->data.d;
        return x;
    }
    if (strcmp(op, "sub") == 0) {
        x->data.d -= y->data.d;
        return x;
    }

    if (strcmp(op, "*") == 0) {
        x->data.d *= y->data.d;
        return x;
    }
    if (strcmp(op, "mul") == 0) {
        x->data.d *= y->data.d;
        return x;
    }

    int is_div = (strcmp(op, "/") == 0 || strcmp(op, "div") == 0.0);
    if (is_div && y->data.d == 0) {
        return lval_err("division by zero");
    } else if (is_div) {
        x->data.d /= y->data.d;
        return x;
    }

    if (strcmp(op, "%") == 0) {
        x->data.d = fmod(x->data.d, y->data.d);
        return x;
    }
    if (strcmp(op, "mod") == 0) {
        x->data.d = fmod(x->data.d, y->data.d);
        return x;
    }

    if (strcmp(op, "^") == 0) {
        x->data.d = pow(x->data.d, y->data.d);
        return x;
    }
    if (strcmp(op, "pow") == 0) {
        x->data.d = pow(x->data.d, y->data.d);
        return x;
    }

    int is_max = (strcmp(op, "max") == 0);
    if (is_max && x->data.d < y->data.d) {
        x->data.d = y->data.d;
        return x;
    } else if (is_max) {
        return x;
    }

    int is_min = (strcmp(op, "min") == 0);
    if (is_min && x->data.d > y->data.d) {
        x->data.d = y->data.d;
        return x;
    } else if (is_min) {
        return x;
    }

    return lval_err("Unknown operation");
}

lval *builtin_op(lval *a, char *op) {
    for (int i = 0; i < a->count; i++) {
        switch (a->cell[i]->type) {
        case LVAL_LONG:
            break;
        case LVAL_DOUBLE:
            break;
        default:
            lval_del(a);
            return lval_err("Can not operate on non-number");
        }
    }

    lval *x = lval_pop(a, 0);
    int is_unary_minus = (strcmp(op, "-") == 0 || strcmp(op, "sub") == 0);

    if (is_unary_minus && a->count == 0) {
        switch (x->type) {
        case LVAL_LONG:
            x->data.l = -x->data.l;
            break;
        case LVAL_DOUBLE:
            x->data.d = -x->data.d;
            break;
        default:
            lval_del(x);
            lval_del(a);
            return lval_err("Can not apply unary operation to non-number");
        }
    } else if (!is_unary_minus && a->count == 0) {
        lval_del(x);
        lval_del(a);
        return lval_err("Unknown unary operation");
    }

    while (a->count > 0) {
        lval *y = lval_pop(a, 0);
        lval *result = NULL;

        switch (x->type) {
        case LVAL_LONG:
            result = builtin_op_long(x, op, y);
            break;
        case LVAL_DOUBLE:
            result = builtin_op_double(x, op, y);
            break;
        default:
            result = lval_err("can not apply operation to a non-number");
            break;
        }

        lval_del(y);

        if (result->type == LVAL_ERR) {
            lval_del(x);
            lval_del(a);
            return result;
        }
    }

    lval_del(a);

    return x;
}
