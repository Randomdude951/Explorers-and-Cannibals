//
// Created by tjfrank on 11/2/24.
//

#include <iostream>

using namespace std;

//checking if safe move
bool is_safe(string explorer_l, string cannibal_l, string explorer_r, string cannibal_r){

        return(explorer_l.size() == 0 || explorer_l.size() >= cannibal_l.size()) && (explorer_r.size() == 0 || explorer_r.size() >= cannibal_r.size());
}

void print_state(string explorer_l, string cannibal_l, string explorer_r, string cannibal_r, string boat, char boat_p){
    //dont print boat in water first round.
    static bool first = true;
    if(!first){
        cout << "            " << boat << "          \n";
    }
    first = false;

    if(boat_p == 'L'){
        cout << explorer_l << cannibal_l << "|--|" << "                " << explorer_r << cannibal_r << endl;
    }
    else if(boat_p == 'R'){
        cout << explorer_l << cannibal_l << "                " << "|--|" << explorer_r << cannibal_r << endl;
    }
}

void solve(string explorer_l, string cannibal_l, string explorer_r, string cannibal_r, string boat, char boat_p){
    //Print current state
    print_state(explorer_l, cannibal_l, explorer_r, cannibal_r, boat, boat_p);
    //Checking if all have crossed
    if(explorer_l.size() == 0 && cannibal_l.size() == 0){
        return;
    }
    //Checking boat position
    if(boat_p == 'L'){
        //switch sides for next iteration
        boat_p = 'R';
        //checking for two L explorers
        if(explorer_l.size() > 1){
            //attempt to fill with EE
            explorer_l.resize(explorer_l.size() - 2);
            explorer_r.insert(explorer_r.end(), {'E', 'E'});
            if(is_safe(explorer_l, cannibal_l, explorer_r, cannibal_r)){
                solve(explorer_l, cannibal_l, explorer_r, cannibal_r, "|EE|", boat_p);
                return;
            } else {
                explorer_r.resize(explorer_r.size() - 2);
                explorer_l.insert(explorer_l.end(), {'E', 'E'});
            }
        }
        //checking for one of each L explorer and L cannibal
        if(explorer_l.size() > 0 && cannibal_l.size() > 0){
            //attempt filling boat with EC
            explorer_l.pop_back();
            explorer_r.push_back('E');
            cannibal_l.pop_back();
            cannibal_r.push_back('C');
            if(is_safe(explorer_l, cannibal_l, explorer_r, cannibal_r)){
                solve(explorer_l, cannibal_l, explorer_r, cannibal_r, "|EC|", boat_p);
                return;
            } else{
                explorer_r.pop_back();
                explorer_l.push_back('E');
                cannibal_r.pop_back();
                cannibal_l.push_back('C');
            }
        }
        //checking for 2 L cannibals
        if(cannibal_l.size() > 1){
            //attempt to fill with CC
            cannibal_l.resize(cannibal_l.size() - 2);
            cannibal_r.insert(cannibal_r.end(), {'C', 'C'});
            if(is_safe(explorer_l, cannibal_l, explorer_r, cannibal_r)){
                solve(explorer_l, cannibal_l, explorer_r, cannibal_r, "|CC|", boat_p);
                return;
            } else{
                cannibal_r.resize(cannibal_r.size() - 2);
                cannibal_l.insert(cannibal_l.end(), {'C', 'C'});
            }
        }

    } else if(boat_p == 'R'){
        boat_p = 'L';
        //if(explorer_r.size() > 0 && cannibal_r.size() > 0){
        if(explorer_r.size() > 0){
            //attempt E
            explorer_r.pop_back();
            explorer_l.push_back('E');
            if(is_safe(explorer_l, cannibal_l, explorer_r, cannibal_r)){
                solve(explorer_l, cannibal_l, explorer_r, cannibal_r, "|E-|", boat_p);
                return;
            } else {
                explorer_l.pop_back();
                explorer_r.push_back('E');
            }
        }
        if(cannibal_r.size() > 0){
            //attempt C
            cannibal_r.pop_back();
            cannibal_l.push_back('C');
            if(is_safe(explorer_l, cannibal_l, explorer_r, cannibal_r)){
                solve(explorer_l, cannibal_l, explorer_r, cannibal_r, "|C-|", boat_p);
                return;
            } else {
                cannibal_l.pop_back();
                cannibal_r.push_back('C');
            }
        }
        if(explorer_r.size() > 0 && cannibal_r.size() > 0){
            //attempt EC
            explorer_r.pop_back();
            explorer_l.push_back('E');
            cannibal_r.pop_back();
            cannibal_l.push_back('C');
            if(is_safe(explorer_l, cannibal_l, explorer_r, cannibal_r)){
                solve(explorer_l, cannibal_l, explorer_r, cannibal_r, "|EC|", boat_p);
                return;
            } else{
                explorer_l.pop_back();
                explorer_r.push_back('E');
                cannibal_l.pop_back();
                cannibal_r.push_back('C');
            }
        }
    }
}




int main(int argc, const char * argv[]) {
    string explorer_l = "EEE", cannibal_l = "CCC", explorer_r = "", cannibal_r = "", boat = "|--|";
    char boat_p = 'L';

    solve(explorer_l, cannibal_l, explorer_r, cannibal_r, boat, boat_p);

    return 0;
}


