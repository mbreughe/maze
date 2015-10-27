#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

class Node{
    private:
        unsigned int num_;
        bool use_left_portal_;
    public:
        Node* left;
        Node* right;
    public:
        Node(int n):
            num_(n){;}
        
        Node * traverse(){
            cout << "Toggle between left and right" << endl;
            cout << "Going to " << left->nodeNum() << endl;
            return left;
        }

        unsigned int nodeNum(){
            return num_;
        }

};

void setLeftLinks(vector<Node*> nodes){
    // Initialize with the last element
    Node * next = *(nodes.end() - 1);

    // Last node does not have a left pointer
    next->left = 0;

    
    // Loop from node N until Node 1
    size_t node_idx = nodes.size() - 2;
    do{
        nodes[node_idx]->left = next;
        next = nodes[node_idx];
        --node_idx;
    }while (next->nodeNum() != 1);
}

void setRightLinks(istream& in){
    (void) in;
    cout << " Set up right links" << endl;
}

uint32_t solve(vector<Node*> nodes){
    uint32_t portals_used = 0; 
    Node * curr_node = nodes[0];
    while(curr_node->nodeNum() != nodes.size()){
        curr_node = curr_node->traverse();
        ++portals_used;
    }
    cout << "Do the modulo" << endl;

    return portals_used;
}
int main(){
    // Number of Rooms
    unsigned int n;
    cin >> n;

    vector<Node*> nodes(n);

    for(int i=0; i < n+1; i++){
        nodes[i] = new Node(i+1);
    }
    
    setLeftLinks(nodes);

    setRightLinks(cin);

    uint32_t a = solve(nodes);
    cout << a << endl;

    for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
        delete *it;
    }
    nodes.clear();


    return 0;
}
