#include "nat.h"
#include "natop.h"

nat sum(nat x, nat y) {
    if (is_undef(x) || is_undef(y)) {
        return undef();
    }
    if (is_infty(x) || is_infty(y)) {
        return infty();
    }
    if (is_zero(x)) {
        return y;
    }
    if (is_zero(y)) {
        return x;
    }
    return succ(sum(pred(x), y));
}

nat dist(nat x, nat y) {
    if (is_undef(x) || is_undef(y)) {
        return undef();
    }
    if (is_infty(x) || is_infty(y)) {
        return infty();
    }
    if (is_zero(x)) {
        return y;
    }
    if (is_zero(y)) {
        return x;
    }
    if (is_leq(x, y)) {
        return dist(pred(y), x);
    }
    return dist(pred(x), pred(y));
}


nat min(nat x, nat y) {
    if (is_undef(x) || is_undef(y)) {
        return undef();
    }
    if (is_infty(x) || is_infty(y)) {
        return infty();
    }
    if (is_zero(x)) {
        return x;  
    }
    if (is_zero(y)) {
        return y;  
    }
    if (is_leq(x, y)) {
        return x;  
    }
    return min(pred(x), y);  
}

nat max(nat x, nat y) {
    if (is_undef(x) || is_undef(y)) {
        return undef();
    }
    if (is_infty(x) || is_infty(y)) {
        return infty();
    }
    if (is_zero(x)) {
        return y;  
    }
    if (is_zero(y)) {
        return x;  
    }
    if (is_leq(x, y)) {
        return y;  
    }
    return max(pred(x), y); 
}



bool is_eq(nat x, nat y) {
    if (is_undef(x) || is_undef(y)) {
        return false;
    }
    if (is_infty(x) || is_infty(y)) {
        return false;
    }
    if (is_zero(x) && is_zero(y)) {
        return true;
    }
    if (is_zero(x) || is_zero(y)) {
        return false;
    }
    return is_eq(pred(x), pred(y));
}

bool is_neq(nat x, nat y) {
    return !is_eq(x, y);
}


bool is_leq(nat x, nat y) {
    if (is_undef(x) || is_undef(y)) {
        return false;
    }
    if (is_infty(x)) {
        return true;
    }
    if (is_infty(y)) {
        return false;
    }
    if (is_zero(x)) {
        return true;
    }
    if (is_zero(y)) {
        return false;
    }
    return is_leq(pred(x), y);
}


bool is_lth(nat x, nat y) {
    return is_leq(x, y) && is_neq(x, y);
}


bool is_geq(nat x, nat y) {
    return is_leq(y, x);
}


bool is_gth(nat x, nat y) {
    return is_leq(y, x) && is_neq(x, y);
}
