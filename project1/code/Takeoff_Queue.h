#include <vector>
#include <queue>
#include <iostream>
using namespace std;


// struct TakeoffQplane{
//     int id;
//     int timestamp;
// };



class TakeoffQ{
public:
    TakeoffQ();
    void create_airplane();
    void push_airplane_into_landQ();
    void step2_TakeoffQ_create_and_push();

    friend ostream& operator<<(ostream& os, const TakeoffQ& data){
        os << "-----Takeoff Queue info-----\n";
        for(int i=0;i<4;i++){
            os << "Queue " << i+1 << " : ";
            for(int j=0;j<data.TakeoffQ_vector[i].size();j++){
                os << "(" << data.TakeoffQ_vector[i][j].id << ") | ";
            }
            os << endl;
        }
        os << "-----  Takeoff Q End -----\n";
        return os;
    };


protected:
    vector<vector<Airplane>> TakeoffQ_vector;
    vector<Airplane> create_plane_vector;
    int TakeoffQ_index;
};

TakeoffQ::TakeoffQ():TakeoffQ_index(0){
    for(int i=0;i<4;i++){
        vector<Airplane> temp;
        TakeoffQ_vector.push_back(temp);
    }
}

void TakeoffQ::create_airplane(){
    int create_limit = rand() % TakeoffQRange;
    for(int i=0;i<create_limit;i++){
        create_plane_vector.push_back({TakeoffQ_index * 2, INT16_MAX, gobal_timestamp});
        TakeoffQ_index++;
    }
}

void TakeoffQ::push_airplane_into_landQ(){
    for(auto newplane : create_plane_vector){
        int minQ = 0;
        int minQsize = 1000;
        for(int i = 0;i < 6;i++){
            if(minQsize > TakeoffQ_vector[i].size()){
                minQ = i;
                minQsize = TakeoffQ_vector[i].size();
            }
        }
        TakeoffQ_vector[minQ].push_back(newplane);
    }
}

void TakeoffQ::step2_TakeoffQ_create_and_push(){
    create_airplane();
    push_airplane_into_landQ();
    create_plane_vector.clear();
}