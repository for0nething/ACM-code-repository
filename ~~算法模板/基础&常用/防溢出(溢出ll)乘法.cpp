LL mul(LL a , LL b){
    return (a * b - (LL) ((long double)a * b / Q) * Q) % Q;
}
