#include <vector>
#include <queue>
#include <iostream>
#define FuelRange 10
#define LandQRange 4
#define TakeoffQRange 3

using namespace std;


static int gobal_timestamp = 0;

struct Airplane{
    int id;
    int fuel;
    int timestamp;
    Airplane() : id(-1){};
    Airplane(int id_, int fuel_, int timestamp_) : id(id_), fuel(fuel_), timestamp(timestamp_){}
};

// struct LandQplane{
//     int id;
//     int fuel;
//     int timestamp;
// };



class LandQ{
public:
    LandQ();
    void create_airplane();
    void push_airplane_into_landQ();
    void step1_LandQ_create_and_push();

    friend ostream& operator<<(ostream& os, const LandQ& data){
        os << "-----Landing Queue info-----\n";
        for(int i=0;i<6;i++){
            os << "Queue " << i+1 << " : ";
            for(int j=0;j<data.LandQ_vector[i].size();j++){
                os << "(" << data.LandQ_vector[i][j].id << "," << data.LandQ_vector[i][j].fuel << ") | ";
            }
            os << endl;
        }
        os << "-----  Landing Q End -----\n";
        return os;
    };


protected:
    vector<vector<Airplane>> LandQ_vector;
    vector<Airplane> create_plane_vector;
    int LandQ_index;
};

inline LandQ::LandQ():LandQ_index(0){
    for(int i=0;i<6;i++){
        vector<Airplane> temp;
        LandQ_vector.push_back(temp);
    }
}

inline void LandQ::create_airplane(){
    int create_limit = rand() % LandQRange;
    for(int i=0;i<create_limit;i++){
        create_plane_vector.push_back({LandQ_index * 2 + 1, rand() % FuelRange + 1, gobal_timestamp});
        LandQ_index++;
    }
}

inline void LandQ::push_airplane_into_landQ(){
    for(auto newplane : create_plane_vector){
        int minQ = 0;
        int minQsize = 1000;
        for(int i = 0;i < 6;i++){
            if(minQsize > LandQ_vector[i].size()){
                minQ = i;
                minQsize = LandQ_vector[i].size();
            }
        }
        LandQ_vector[minQ].push_back(newplane);
    }
}

inline void LandQ::step1_LandQ_create_and_push(){
    create_airplane();
    push_airplane_into_landQ();
    create_plane_vector.clear();
}