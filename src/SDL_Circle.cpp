#include <iostream>
#include <SDL2/SDL.h>

const float GRAVITY = 9.8; //earths gravity
const float FLOOR_DIST = 4.2; //ball is 4 meter above ground
const float dt = 0.02;  //iteration interval 20ms
const float COE_REST = 0.8; //coefficient of restitution

enum class direction{UP, DOWN};

const int SCREEN_WIDTH = 800; 
const int SCREEN_HEIGHT = 600;
const int START_X = 100; 
const int START_Y = 100;
const float PPM = 100;

class Ball{
    int centerX;
    int centerY;
    float radius;
    float cur_vel;
    float cur_pos;
    direction dir;

public:

    Ball():centerX(100),centerY(100),radius(20),
           cur_vel(0),cur_pos(0),dir(direction::DOWN) {}
    Ball(int x, int y, int r):centerX(x),centerY(y),radius(r),
           cur_vel(0),cur_pos(0),dir(direction::DOWN) {}

    void update(){
        switch(dir){
            case direction::DOWN:
                cur_vel = cur_vel + GRAVITY * dt;
                cur_pos = cur_pos + cur_vel * dt;
                //std::cout << "cur_vel = " << cur_vel << "\t";
                //std::cout << "cur_pos = " << cur_pos << "\n";
                if(cur_pos + radius/PPM >=4.2){
                    //std::cout << "We have hit the floor\n";
                    cur_vel = cur_vel * COE_REST;
                    cur_pos = FLOOR_DIST - radius/PPM;
                    dir = direction::UP;
                }
                centerY = cur_pos * PPM + 100;
                    break;
            case direction::UP:
                cur_vel = cur_vel - GRAVITY * dt;
                cur_pos = cur_pos - cur_vel * dt;
                //std::cout << "cur_vel = " << cur_vel << "\t";
                //std::cout << "cur_pos = " << cur_pos << "\n";
                if(cur_vel <=0){
                    //std::cout << "We have reached the top\n";
                    dir = direction::DOWN;
                    cur_vel = 0;
                }
                centerY = cur_pos * PPM + 100;
                    break;

        }
    } 

    void draw_circle(SDL_Renderer* renderer) {
        const int32_t diameter = (radius * 2);

        int32_t x = (radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        while (x >= y) {
            // Each of the following renders an octant of the circle
            SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

            if (error <= 0) {
                ++y;
                error += ty;
                ty += 2;
            }
            if (error > 0) {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }

};



int main(){
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout << "Error: SDL_Init()\n";
        return -1;
    }

    window = SDL_CreateWindow("Bouncing Ball", 200, 200, 
                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        std::cout << "Error: SDL_CreateWindow()\n";
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        std::cout << "Error: SDL_CreateRenderer()\n";
        return -1;
    }

    bool running = true;
    SDL_Event e;
    Ball ball;
    
    while(running){
        
        // A. Handle Events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        ball.update();
        ball.draw_circle(renderer);
        SDL_RenderDrawLineF(renderer, 0, 520, 799, 520);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        
    }
}