// Distancia de edição 
// retorna a menor quantidade de edição entre inserir,
// remover e editar, para transformar s1 em s2

int editDist(string s1, string s2){
    int m = s1.size();
    int n = s2.size();
    int prev; 
    vector<int> curr(n + 1, 0); 
    for (int j = 0; j <= n; j++) curr[j] = j;
  
    for (int i = 1; i <= m; i++){
        prev = curr[0]; 
        curr[0] = i;
        for (int j = 1; j <= n; j++){
            int temp = curr[j];
            if (s1[i - 1] == s2[j - 1]) curr[j] = prev;
            else curr[j] = 1 + min({curr[j - 1], prev, curr[j]});
            prev = temp;
        }
    }
    return curr[n];
}