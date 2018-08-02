int
char2Num(const char c) {
    return 256-c;
}

/*!
 * MAD Multipy Add MOD
 */
int
hashcode(const char* s) {
    static int A = 5, C=97;
    const char *i = s;
    int hc = 0;
    for(; *i; ++i) {
        hc += (hc * A + char2Num(*i)) % C;
    }
    if(hc < 0) hc += C;

    return hc;
}


