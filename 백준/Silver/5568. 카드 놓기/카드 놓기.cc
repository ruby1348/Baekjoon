#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

int count = 0;
void select(int index, int n, int k, int max);
void execute(int max);
std::vector<std::string> vec;
std::vector<int> select_vec;
std::map<std::string, int> map;

int main(){
    int n, k;
    
    std::cin >> n >> k;
    for(int i = 0; i < n; i++){
        std::string str;
        std::cin >> str;
        vec.push_back(str);
    }
    
    for(int i = 0; i < n; i++) select(i, 1, k, n);
    
    std::cout << count;
}

void select(int index, int n, int k, int max){
    select_vec.push_back(index);
    if(n == k){
        execute(k);
        select_vec.pop_back();
        return;
    }
    for(int i = index + 1; i < max; i++){
        select(i, n + 1, k, max);
    }
    
    select_vec.pop_back();
}

void execute(int max){
    std::sort(select_vec.begin(), select_vec.end()); 
    
    std::string str = "";
    for(int i = 0; i < max; i++){
        str += vec[select_vec[i]];
    }
        
    if(map[str] == 0){
        map[str] = 1;
        count++;
    }
    
    while(std::next_permutation(select_vec.begin(), select_vec.end())){
        std::string str = "";
        for(int i = 0; i < max; i++){
            str += vec[select_vec[i]];
        }
        
        if(map[str] == 0){
            map[str] = 1;
            count++;
        }
    }
}