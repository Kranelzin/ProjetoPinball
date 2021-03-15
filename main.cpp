#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include "Line.h"
#include "Vetor2.h"
#include "Circle.h"
using namespace std;

void set_pixel(SDL_Renderer* rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(rend, r, g, b, a);
	SDL_RenderDrawPoint(rend, x, y);
}
void draw_circle(SDL_Renderer* surface, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

	double error = (double)-radius;
	double x = (double)radius - 0.5;
	double y = (double)0.5;
	double cx = n_cx - 0.5;
	double cy = n_cy - 0.5;

	while (x >= y)
	{
		set_pixel(surface, (int)(cx + x), (int)(cy + y), r, g, b, a);
		set_pixel(surface, (int)(cx + y), (int)(cy + x), r, g, b, a);

		if (x != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy + y), r, g, b, a);
			set_pixel(surface, (int)(cx + y), (int)(cy - x), r, g, b, a);
		}

		if (y != 0)
		{
			set_pixel(surface, (int)(cx + x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy + x), r, g, b, a);
		}

		if (x != 0 && y != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy - x), r, g, b, a);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}

	}
}
void fill_circle(SDL_Renderer* surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

	static const int BPP = 4;


	for (double dy = 1; dy <= radius; dy += 1.0)
	{

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(surface, r, g, b, a);
		SDL_RenderDrawLine(surface, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(surface, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
	}
}

int main(int argc, char* argv[]) {
	//SETUP
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Pinball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
	SDL_Event event;
	int tempX = 0, tempY = 0;
	float VerSpeed1 = 0.0f, HorSpeed1 = 0.0f, gravity = 0.3f, friction = 3.0f;
	bool play = true, collision = false;

	Line line(550,700,50,700);
	Line line2(150,50,450,50);
	Line line3(450,50,550,150);
	Line line4(150,50,50,150);
	Line line5(50,150,50,700);
	Line line6(550,150,550,700);


	double flipper1x1 = 175;
	double flipper1y1 = 650;
	double flipper1x2 = 275;
	double flipper1y2 = 650;

	double flipper2x1 = 425;
	double flipper2y1 = 650;
    double flipper2x2 = 325;
	double flipper2y2 = 650;

	Line flipper1(flipper1x1,flipper1y1,flipper1x2, flipper1y2);
	Line flipper2(flipper2x1,flipper2y1,flipper2x2,flipper2y2);

	Line obstaculo1(50,600,175,650);
	Line obstaculo2(550,600,425,650);

    Line obstaculo3(100,400,150,450);
    Line obstaculo4(450,450,500,400);

	Circle circle(150,400,10);


    bool colisaof1 = false;
    bool colisaof2 = false;

	while (play) {

		while (SDL_PollEvent(&event) != 0){

			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
                    HorSpeed1 += 2;
                    if(flipper1y2 < 682){

                        flipper1y2= flipper1y2 + 8;
                        double diferenca = 650 - flipper1y2;
                        flipper1x2= flipper1x1  + pow(10000 - (diferenca * diferenca),0.5);
					}

                    if(flipper2y2 < 682){

                        flipper2y2= flipper2y2 + 8;
                        double diferenca2 = 650 - flipper2y2;
                        flipper2x2= flipper2x1  - pow(10000 - (diferenca2 * diferenca2),0.5);
					}

					break;
				case SDLK_LEFT:
                    HorSpeed1 += -2;
                    if(flipper1y2 > 562){

                        flipper1y2= flipper1y2 - 8;
                        double diferenca = 650 - flipper1y2;
                        flipper1x2= flipper1x1  + pow(10000 - (diferenca * diferenca),0.5);
					}

                    if(flipper2y2 > 562){

                        flipper2y2= flipper2y2 - 8;
                        double diferenca2 = 650 - flipper2y2;
                        flipper2x2= flipper2x1  - pow(10000 - (diferenca2 * diferenca2),0.5);
					}
					break;

                case SDLK_DOWN:
                    VerSpeed1 += 2;
                    break;

                case SDLK_UP:
                    VerSpeed1 += -5;
                    break;

				case SDLK_ESCAPE:
					play = false;

				}
			}
		}

		//VALORES

		VerSpeed1 += gravity;
        circle.x += HorSpeed1;
		circle.y += VerSpeed1;

        //LIMITADOR

		if (VerSpeed1 > 10){
            VerSpeed1 = 10;
		}

		if(VerSpeed1 < -10){
            VerSpeed1 = -10;
		}

		if (HorSpeed1 > 10){
            HorSpeed1 = 10;
		}

		if(HorSpeed1 < -10){
            HorSpeed1 = -10;
		}


		//COLISÃO VERTICAL
		if (circle.y - circle.radius < 50) {
			circle.y = 50 + circle.radius;
			VerSpeed1 = -(VerSpeed1);
		}
		if (circle.y + circle.radius > 700) {
			circle.y = 700 - circle.radius;
            if(VerSpeed1>-1 && VerSpeed1<0){
                VerSpeed1 =0;
            }
		}

        //COLISÃO QUINAS

        double colisaoobstaculo1 = obstaculo1.distancia(circle.x ,circle.y)-circle.radius;
        double colisaoobstaculo2 = obstaculo2.distancia(circle.x ,circle.y)-circle.radius;
        double colisaoobstaculo3 = obstaculo3.distancia(circle.x ,circle.y)-circle.radius;
        double colisaoobstaculo4 = obstaculo4.distancia(circle.x ,circle.y)-circle.radius;


        double colisaoline3 = line3.distancia(circle.x ,circle.y)-circle.radius;
        double colisaoline4 = line4.distancia(circle.x ,circle.y)-circle.radius;

        if (colisaoobstaculo1<1){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + (-VerSpeed1) - friction;
        }

        if (colisaoobstaculo2<1){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + VerSpeed1 - friction;

        }

        if (colisaoline4<1){
            VerSpeed1 =-(VerSpeed1 +gravity);
            HorSpeed1 = HorSpeed1 + VerSpeed1 - friction;
        }

        if (colisaoline3<1){
            VerSpeed1 =-(VerSpeed1 +gravity);
            HorSpeed1 = HorSpeed1 + (-VerSpeed1) - friction;

        }

        if (colisaoobstaculo3<1.5 && colisaoobstaculo3 >0.5 && circle.x+circle.radius >100 && circle.x - circle.radius <150){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + (-VerSpeed1) - friction;

        }

        if(colisaoobstaculo3>-1.5 && colisaoobstaculo3 < -0.5 && circle.x+circle.radius >100 && circle.x -circle.radius <150){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + (-VerSpeed1) - friction;
        }

        if (colisaoobstaculo4<1.5 && colisaoobstaculo4 > 0.5 && circle.x+circle.radius >450 && circle.x -circle.radius <500){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + VerSpeed1 - friction;

        }
        if(colisaoobstaculo4>-1.5 && colisaoobstaculo4 < -0.5 && circle.x+circle.radius >450 && circle.x -circle.radius <500){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + VerSpeed1 - friction;
        }


        //COLISÃO HORIZONTAL

		if (circle.x - circle.radius < 50) {
			circle.x = 50 + circle.radius;
			HorSpeed1 = -(HorSpeed1+1);
		}
		if (circle.x + circle.radius > 550) {
			circle.x = 550 - circle.radius;
			HorSpeed1 = -(HorSpeed1-1);
		}

		//COLISÃO FLIPPERS

		double colisaoflipper1 = flipper1.distancia(circle.x,circle.y) - circle.radius;
		double colisaoflipper2 = flipper2.distancia(circle.x,circle.y) - circle.radius;

        if(colisaoflipper1 <0&&circle.x + circle.radius > flipper1x1 && circle.x - circle.radius <flipper1x2){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + (-VerSpeed1) - friction;
        }
        if(colisaoflipper2 <0&&circle.x + circle.radius > flipper2x1 && circle.x - circle.radius <flipper2x2){
            VerSpeed1 =-(VerSpeed1 -gravity);
            HorSpeed1 = HorSpeed1 + VerSpeed1 - friction;
        }



		//DESENHAR


		SDL_SetRenderDrawColor(render, 0, 0, 0, 0);


		SDL_RenderClear(render);

		//DESENHAR CÍRCULOS
		draw_circle(render, circle.x, circle.y, circle.radius, 255, 255, 255, 0);
		fill_circle(render, circle.x, circle.y, circle.radius, 255, 255, 255, 0);


		//LINHAS

		SDL_RenderDrawLine(render,550,700,50,700);
        SDL_RenderDrawLine(render,150,50,450,50);
        SDL_RenderDrawLine(render,450,50,550,150);
        SDL_RenderDrawLine(render,150,50,50,150);
        SDL_RenderDrawLine(render,50,150,50,700);
        SDL_RenderDrawLine(render,550,150,550,700);
        SDL_RenderDrawLine(render,550,150,550,700);

        SDL_RenderDrawLine(render,flipper1x1,flipper1y1,flipper1x2,flipper1y2);
        SDL_RenderDrawLine(render,flipper2x1,flipper2y1,flipper2x2,flipper2y2);

        SDL_RenderDrawLine(render,50,600,175,650);
        SDL_RenderDrawLine(render,550,600,425,650);
        SDL_RenderDrawLine(render,100,400,150,450);
        SDL_RenderDrawLine(render,450,450,500,400);


		SDL_RenderPresent(render);

		SDL_Delay(1000 / 60);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
