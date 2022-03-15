#include "Landing_Queue.h"
#include "Takeoff_Queue.h"

class Runway : public LandQ, public TakeoffQ{
public:
    Runway();
    void one_time_iter();
    int step3_checkall_LandQ();

    friend ostream& operator<<(ostream& os, const Runway& data){
        os << "-----Landing Queue info-----\n";
        for(int i=0;i<6;i++){
            os << "Queue " << i+1 << " : ";
            for(int j=0;j<data.LandQ_vector[i].size();j++){
                os << "(" << data.LandQ_vector[i][j].id << "," << data.LandQ_vector[i][j].fuel << ") | ";
            }
            os << endl;
        }
        os << "-----  Landing Q End -----\n";
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
        return os;
    };


    vector<Airplane> Runway_vector;
    // LandQ LandQ_;
    // TakeoffQ TakeoffQ_;
    int land_wait_time;
    int takeoff_wait_time;
    int fuel_save;
    int emergency_plane;
    int crased_plane;
    int land_plane;
    int takeoff_plane;
};

Runway::Runway(): land_wait_time(0), takeoff_wait_time(0), fuel_save(0), emergency_plane(0), crased_plane(0){
    for(int i=0;i<4;i++){
        Airplane plane_space;
        Runway_vector.push_back(plane_space);
    }
}

void Runway::one_time_iter(){
    step1_create_and_push();
    step2_create_and_push();
    int emergency_plane_num = step3_checkall_LandQ();


    // cout << TakeoffQ_;
}

int Runway::step3_checkall_LandQ(){
    int i=0;
    for(auto landqueue : LandQ_vector){
        for(int j=0;j<landqueue.size();j++){
            if(landqueue[j].timestamp + landqueue[j].fuel == timestamp){
                Runway_vector[i] = landqueue[j];
                i++;
                landqueue.erase(landqueue.begin() + j);
                j--;
                
                if(i >= 4) return 4;
            }
        }
    }
    return i;
}