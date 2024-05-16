// Debug
// 1. Precisa compilar com -DDEBUG

// para pair
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }

// para vector,set,...
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ","; return os << '}'; }

// debug
void debug_out(string s) { cerr << endl; }
template<typename H, typename... T>
void debug_out(string s, H h, T... t) {
    do { cerr << s[0]; s = s.substr(1);
    } while (s.size() and s[0] != ',');
    cerr << "=" << h;
    debug_out(s, t...);
}
#ifdef DEBUG
#define debug(...) cerr << "Line(" << __LINE__ << "): "; debug_out(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#endif