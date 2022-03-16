#include "Landing_Queue.h"
#include "Takeoff_Queue.h"

struct emergency_plane_position{
    int id;
    int Q;
    int idx;
};

class Runway : public LandQ, public TakeoffQ{
public:
    Runway();
    void one_time_iter();
    void vector_clear();
    void checkall_LandQ();
    void dealwith_emergency();
    void runway_reset();
    void step3_handle_emergency_plane();
    void step4_runway_allocate();

    friend ostream& operator<<(ostream& os, const Runway& data){
        os << "-----Landing Queue -----\n";
        for(int i=0;i<6;i++){
            os << "Queue " << i+1 << " : ";
            for(int j=0;j<data.LandQ_vector[i].size();j++){
                // os << "(" << data.LandQ_vector[i][j].id << "," << data.LandQ_vector[i][j].fuel - gobal_timestamp + data.LandQ_vector[i][j].timestamp << ") | ";
                os << "(" << data.LandQ_vector[i][j].id << "," 
                          << data.LandQ_vector[i][j].fuel << ","
                          << gobal_timestamp << ","
                          << data.LandQ_vector[i][j].timestamp << ") | ";
            }
            os << endl;
        }
        os << "-----Takeoff Queue -----\n";
        for(int i=0;i<4;i++){
            os << "Queue " << i+1 << " : ";
            for(int j=0;j<data.TakeoffQ_vector[i].size();j++){
                os << "(" << data.TakeoffQ_vector[i][j].id << ") | ";
            }
            os << endl;
        }
        os << "-----  emergency plane -----\n";
        os << "|";
        for(auto a : data.emergency_vector){
            os << " (" << a.id << ") |";
        }
        os << endl;
        os << "-----  Runway plane -----\n";
        os << "|";
        for(auto a : data.Runway_vector){
            os << " (" << a.id << ") " << "|";
        }
        os << endl;
        return os;
        
    };


    vector<Airplane> Runway_vector;
    vector<Airplane> Crashed_plane;
    vector<emergency_plane_position> emergency_vector;
    

    int land_wait_time;
    int takeoff_wait_time;
    int fuel_save;
    int emergency_plane;
    int crased_plane;
    int land_plane;
    int takeoff_plane;
};

Runway::Runway(): land_wait_time(0), takeoff_wait_time(0), fuel_save(0), emergency_plane(0), crased_plane(0){
    runway_reset();
}

void Runway::one_time_iter(){
    step1_LandQ_create_and_push();
    step2_TakeoffQ_create_and_push();
    step3_handle_emergency_plane();

    // cout << TakeoffQ_;
}

void Runway::step3_handle_emergency_plane(){
    checkall_LandQ();
    dealwith_emergency();
}

void Runway::checkall_LandQ(){
    for(int i=0;i<6;i++){
        for(int j=0;j<LandQ_vector[i].size();j++){
            if(LandQ_vector[i][j].timestamp + LandQ_vector[i][j].fuel == gobal_timestamp){
                emergency_vector.push_back({LandQ_vector[i][j].id,i,j});
            }
        }
    }
}

void Runway::dealwith_emergency(){
    int count = 0;
    for(auto e : emergency_vector){
        if(count < 4){
            Runway_vector[count] = LandQ_vector[e.Q][e.idx];
            count++;
        }else{
            Crashed_plane.push_back(LandQ_vector[e.Q][e.idx]);
        }
    }
    for(auto e : emergency_vector){
        LandQ_vector[e.Q].erase(LandQ_vector[e.Q].begin() + e.idx);
    }
}

void Runway::step4_runway_allocate(){
    
}

void Runway::runway_reset(){
    Runway_vector.clear();
    for(int i=0;i<4;i++){
        Airplane plane_space;
        Runway_vector.push_back(plane_space);
    }
}

void Runway::vector_clear(){
    emergency_vector.clear();
    runway_reset();
}