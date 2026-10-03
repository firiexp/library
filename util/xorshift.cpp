class xor_shift {
    uint32_t x, y, z, w;
public:
    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL << 32)-1))),
    y(1068246329), z(321908594), w(1234567890) {};

    uint32_t urand(){
        uint32_t t;
        t = x ^ (x << 11);
        x = y; y = z; z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    };

    int rand(int n){
        return rand(0, n);
    }

    int rand(int a, int b){
        if(a > b) swap(a, b);
        uint64_t width = int64_t(b) - int64_t(a) + 1;
        uint64_t limit = (uint64_t(1) << 32) / width * width;
        uint64_t e = urand();
        while(e >= limit) e = urand();
        return static_cast<int>(int64_t(a) + int64_t(e % width));
    }
};
