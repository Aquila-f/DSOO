#include <stdlib.h>
#include <time.h>
#include "Runway.h"


using namespace std;

// static int timestamp;

main(){
    srand(time(NULL));

    // LandQ aaa;
    // TakeoffQ bbb;
    Runway rrr;

    
    int limit_t = 5;

    for(;timestamp<limit_t;timestamp++){
        rrr.one_time_iter();
        cout << rrr;
        // aaa.step1_create_and_push();
        // bbb.step2_create_and_push();
        
    }

    // cout << aaa;
    // cout << bbb;

    // int i = 0;
    // for(auto s : aaa.LandQvector){
    //     cout << "-------" << i++ << "-------\n";
    //     for(auto ss : s){
    //         cout << ss.id << " : " << ss.fuel << " : " << ss.timestamp << endl;
    //     }
    // }
    // for(auto s : bbb.TakeoffQ_vector){
    //     cout << "-------" << i++ << "-------\n";
    //     for(auto ss : s){
    //         cout << ss.id << " : " << " : " << ss.timestamp << endl;
    //     }
    // }
    // cout << bbb;
    
    
    // return 0;
}