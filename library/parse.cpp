using state = string::const_iterator;
 
int num(state &cur);
int factor(state &cur);
int muldiv(state &cur);
int addsub(state &cur);
int expr(state &cur);
 
int factor(state &cur) {
    if(isdigit(*cur)) return num(cur);
    cur++;
    int ans = addsub(cur);
    cur++;
    return ans;
}
 
int num(state &cur) {
    int ans = *cur -'0';
    while(isdigit(*++cur)) ans = ans*10 + (*cur-'0');
    return ans;
}
 
int muldiv(state &cur) {
    int ans = factor(cur);
    while(true){
        if(*cur == '*'){
            cur++;
            ans *= factor(cur);
        }else if(*cur == '/'){
            cur++;
            ans /= factor(cur);
        }else break;
    }
    return ans;
}
 
int addsub(state &cur){
    int ans = muldiv(cur);
    while(true){
        if(*cur == '+'){
            cur++;
            ans += muldiv(cur);
        }else if(*cur == '-'){
            cur++;
            ans -= muldiv(cur);
        }else break;
    }
    return ans;
}
 
int expr(state &cur){
    return addsub(cur);
}