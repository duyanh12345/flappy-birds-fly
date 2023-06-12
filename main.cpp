#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

const int WIDTH = 1000, HEIGHT = 700;

struct BIRD {
    float x;
    float y;
    float vx;
    float vy;
} bird;

int cnt=0;


int main( int argc, char *argv[] )
{   
    SDL_Surface * birdsurface= IMG_Load("yellowbird-downflap.png");
    SDL_Surface * windowsurface=NULL;
    SDL_Window * window=SDL_CreateWindow("Bird",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer * render=SDL_CreateRenderer(window,-1,0);

    SDL_Rect birdrect={0,0,34,24};
    SDL_FRect windowrect;
    SDL_Event windowevent;

    while (true)
    {
         if(SDL_PollEvent(&windowevent))
         {
             if(SDL_QUIT == windowevent. type)
                break;
            else
            if(windowevent.type==SDL_MOUSEBUTTONDOWN)
            {   
                int X,Y;
                SDL_GetMouseState(&X,&Y);
                cnt++;
                bird[cnt].x=X;
                bird[cnt].y=Y;
                bird[cnt].vx=1.0f*(rand()%101)/100;
                bird[cnt].vy=sqrt(1-bird[cnt].vx*bird[cnt].vx);

                int ok=rand()%2;
                if(ok==0)
                ok=-1;

                bird[cnt].vx*=ok;

                ok=rand()%2;
                if(ok==0)
                ok=-1;

                bird[cnt].vy*=ok;
            }
         }

        SDL_SetRenderDrawColor(render,58,168,201,255);
        SDL_RenderClear(render);

        for(int i=1;i<=cnt;++i)
        {
         bird[i].x+=bird[i].vx;
         bird[i].y+=bird[i].vy;

        if(bird[i].x<0)
            bird[i].x=0,bird[i].vx=-bird[i].vx;

        if(bird[i].x>WIDTH)
            bird[i].x=WIDTH,bird[i].vx=-bird[i].vx;

        if(bird[i].y<0)
            bird[i].y=0,bird[i].vy=-bird[i].vy;

        if(bird[i].y>HEIGHT)
            bird[i].y=HEIGHT,bird[i].vy=-bird[i].vy;

         windowrect={bird[i].x,bird[i].y,34,24};

         SDL_Texture * birdtext =SDL_CreateTextureFromSurface(render,birdsurface);
         SDL_RenderCopyF(render, birdtext, &birdrect,&windowrect);
        }
         SDL_RenderPresent(render);    
    }
}
