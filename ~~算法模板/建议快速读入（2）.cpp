namespace IO { // øÏ∂¡œ‡πÿ
    const int BUFSZ = 1e7;
    char buf[BUFSZ]; int idx, end;
    void init() { idx = BUFSZ; }
    char getch() {
        if( idx == BUFSZ ) {
            end = fread( buf, 1, BUFSZ, stdin ); idx = 0;
        }
        if( idx == end ) return EOF;
        return buf[idx++];
    }
    int getint() {
        int num = 0; char ch;
        while( isspace(ch=getch()) );
        do { num = num*10 + ch-'0'; } while( isdigit(ch=getch()) );
        return num;
    }
}
