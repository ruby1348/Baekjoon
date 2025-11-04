#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Student{
public:
    std::string name;
    int lan;
    int math;
    int english;
};

int main(){
    int n;
    std::cin >> n;
    std::vector<Student> vec;
    
    for(int i = 0; i < n; i++){
        Student temp;
        std::cin >> temp.name >> temp.lan >> temp.math >> temp.english;
        vec.push_back(temp);
    }
    
    std::sort(vec.begin(), vec.end(), [](const Student& a, const Student& b){
        if(a.lan != b.lan) return a.lan > b.lan;
        if(a.math != b.math) return a.math < b.math;
        if(a.english != b.english) return a.english > b.english;
        return a.name < b.name;
    });
    
    for(int i = 0; i < n; i++){
        std::cout << vec[i].name << "\n";
    }
}