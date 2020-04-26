deque<int> Q;
stack<int> s;
int cnt = 0;
vector<int> visited(n, 0), num(n);
s.emplace(0);
while(!s.empty()){
    int a = s.top(); s.pop();
    visited[a]++;
    num[a] = cnt++;
    Q.emplace_front(a);
    for (auto &&i : v[a]) {
        if(!visited[i]) s.emplace(i);
    }
}