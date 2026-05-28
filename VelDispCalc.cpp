#include <iostream>

const float GRAVITY = 9.8; //gravity in m/s2
const float COE_REST = 0.8; //coefficient of restitution
const float dt = 0.02; //time interval 20ms
const float FLOOR_DIST = 4; //floor at 4m distance from initial position of the ball

enum class direction {UP, DOWN};

int main(){
    float cur_vel = 0;
    float cur_pos = 0;
    direction dir = direction::DOWN;
    for(int i=0; i<=100; i++){
        switch(dir){
            case direction::DOWN:
                cur_vel = cur_vel + GRAVITY * dt;
                cur_pos = cur_pos + cur_vel * dt;
                std::cout << "cur_vel = " << cur_vel << "\t";
                std::cout << "cur_pos = " << cur_pos << "\n";
                if(cur_pos >=4){
                    std::cout << "We have hit the floor\n";
                    cur_vel = cur_vel * COE_REST;
                    dir = direction::UP;
                }
                    break;
            case direction::UP:
                cur_vel = cur_vel - GRAVITY * dt;
                cur_pos = cur_pos - cur_vel * dt;
                std::cout << "cur_vel = " << cur_vel << "\t";
                std::cout << "cur_pos = " << cur_pos << "\n";
                if(cur_vel <=0){
                    std::cout << "We have reached the top\n";
                    dir = direction::DOWN;
                    cur_vel = 0;
                }
                    break;

        }
    }

}