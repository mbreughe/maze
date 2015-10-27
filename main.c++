#include <iostream>
#include <cstdint>
#include <vector>
#include <utility>
using namespace std;

// Using pre-increment style
uint32_t& moduloIncrement(uint32_t& portals_used, uint32_t incr = 1){
    portals_used += incr;
    portals_used = portals_used % 1000000007;
    return portals_used;
}

class Node{
    private:
        unsigned int num_;
        bool use_left_portal_;
        bool round_trip_calculated_;
        uint32_t round_trip_time_;
    public:
        Node* left;
        Node* right;
    public:
        Node(int n):
            num_(n),
            use_left_portal_ (false),
            round_trip_calculated_(false)
            {;}

        // brief: Calculate how many portal traversals it takes to go left
        // Return: (left node, port traversal time)
        // Note: Sets use_left_portal to false, since we will use the left portal
        pair<Node*, uint32_t> goLeft(){
            pair <Node*, uint32_t> ret;

            // I don't expect To ever hit this case
            if(use_left_portal_){
                ret.first = left;
                ret.second = 1;
                use_left_portal_ = false;
            }
            else{
                // Cost to get back in the current node
                uint32_t traverseRight = getRoundTripTime();
                // At this point we can take left. Add cost to take left (i.e., 1 traversal)
                moduloIncrement(traverseRight);
                ret.first = left;
                ret.second = traverseRight;
                use_left_portal_ = false;
            }
            return ret;
        }

        Node * traverse(){
            Node * return_node;
            if(use_left_portal_){
                return_node = left;
            }else{
                return_node = right;
            }

            // Toggle
            use_left_portal_ = ! use_left_portal_;

            return return_node;
        }

        unsigned int nodeNum(){
            return num_;
        }
        
    private:
        // brief: Calculate the time it takes to get back to the current node
        uint32_t getRoundTripTime(){
            // If round trip time not cached, calculate it
            if (!round_trip_calculated_){
                // Cost to go right
                round_trip_time_ = 1;
                Node* next_node = right;
                while(next_node->nodeNum() != this->nodeNum()){
                    auto p = next_node->goLeft();
                    // Get the node on the left
                    next_node = p.first;
                    // Add the cost of taking the left node
                    moduloIncrement(round_trip_time_, p.second);
                }

                round_trip_calculated_ = true;
            }

            return round_trip_time_;
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

void setRightLinks(istream& in, vector<Node*> nodes){
    for (size_t i=0; i != nodes.size() - 1; ++i){
        unsigned int node_num;
        in >> node_num;
        nodes[i]->right = nodes[node_num-1];
    }

}

uint32_t solve(vector<Node*> nodes){
    uint32_t portals_used = 0; 
    Node * curr_node = nodes[0];
    while(curr_node->nodeNum() != nodes.size()){
        curr_node = curr_node->traverse();
        // perform modulo increment in case there are a large number of traversals
        moduloIncrement(portals_used);
    }

    return portals_used;
}

uint32_t solve_optimized(vector<Node*> nodes){
    uint32_t fitbit = 0;
    for (int i=0; i < nodes.size()-1 ; i++){
        moduloIncrement(fitbit, nodes[i]->goLeft().second);
    }

    return fitbit;
}
int main(){
    // Number of Rooms
    unsigned int n;
    cin >> n;

    vector<Node*> nodes(n+1);

    for(int i=0; i < n+1; i++){
        nodes[i] = new Node(i+1);
    }
    
    setLeftLinks(nodes);

    setRightLinks(cin, nodes);

    cout << solve_optimized(nodes) << endl;


    for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++){
        delete *it;
    }
    nodes.clear();


    return 0;
}
