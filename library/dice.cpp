struct dice {
    int u, d, l, r, f, b;
 
    void spinl(){ // f -> l
        int tmp = f; f = r; r = b; b = l; l = tmp;
    }
    void spinr(){
        for (int i = 0; i < 3; ++i) spinl();
    }
 
    void gof(){
        int tmp = f; f = u; u = b; b = d; d = tmp;
    }
 
    void gob(){
        for (int i = 0; i < 3; ++i) gof();
    }
 
    void gor(){
        int tmp = u; u = l; l = d; d = r; r = tmp;
    }
 
    void gol(){
        for (int i = 0; i < 3; ++i) gor();
    }
 
    dice(int a, int x) {
        u = 1, d = 6, f = 2, b = 5, l = 4, r = 3;
        if(a == 2) gob();
        else if(a == 3) gol();
        else if(a == 4) gor();
        else if(a == 5) gof();
        else if(a == 6) gof(), gof();
        while(f != x) spinl();
    }
};