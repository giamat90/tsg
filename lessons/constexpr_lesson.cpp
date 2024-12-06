int get_value(){
    return 42;
}

const int get_cvalue(){
    return 42;
}

constexpr int get_cevalue(){
    return 42;
}

int fact(int n){
    return n <= 1 ? 1 : n*fact(n-1);
}

const int cfact(const int n){
    return n <= 1 ? 1 : n*cfact(n-1);
}

constexpr int cefact(const int n){
    return n <= 1 ? 1 : n*cefact(n-1);
}

int main() {
    int i = get_value();
    const int ci = get_cvalue();
    constexpr int cei = get_cevalue();

    int fact10 = fact(10);
    const int cfact10 = cfact(10);
    constexpr int cefact10 = cefact(10);

    return 0;
}