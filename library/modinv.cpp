template<typename T>  
T mod_inv(T x, T M){  
   T u = 1, t = 1, v = 0, s = 0, m = M;  
   while (x) { T q = m/x; swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }  
   if(s < 0) s += M;  
   return s;  
}
