#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

class Node{
    private:
        unsigned int num_;
    public:
        Node* left;
        Node* right;
    public:
        Node(int n):
            num_(n){};

};

void setLeftLinks(vector<Node*> nodes){
    (void) nodes;
}

void setRightLinks(istream& in){
    (void) in;
}

uint32_t solve(vector<Node*> nodes){
    return 0;
}
int main(){
    // Number of Rooms
    unsigned int n;
    cin >> n;

    vector<Node*> nodes(n);

    for(int i=0; i < n+1; i++){
        nodes[i] = new Node(i);
    }
    
    setLeftLinks(nodes);

    setRightLinks(cin);

    uint32_t a = solve(nodes);


    return 0;
}
