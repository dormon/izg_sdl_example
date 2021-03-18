#include<iostream>

#include<SDL.h>

int main(int argc,char*argv[]){

  SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

  if(SDL_Init(SDL_INIT_VIDEO)!=0){
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail: %s\n",SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Window*window = SDL_CreateWindow("izg_example",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1024,768,0);
  if(!window){
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow fail: %s\n",SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Surface*surface = SDL_GetWindowSurface(window);
  if(!surface){
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GetWindowSurface fail: %s\n",SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer*renderer = SDL_CreateSoftwareRenderer(surface);
  if(!renderer){
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateSoftwareRenderer: %s\n",SDL_GetError());
    return EXIT_FAILURE;

  }

  bool running = true;
  while(running){//main loop

    uint32_t x=200;
    uint32_t y=200;

    //event handling
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT)running = false;

      if(event.type == SDL_KEYDOWN){//
        if(event.key.keysym.sym==SDLK_a)
          std::cerr << "mackame a" << std::endl;
        if(event.key.keysym.sym==SDLK_d)
          std::cerr << "mackame d" << std::endl;
      }
      if(event.type == SDL_MOUSEMOTION){
        if(event.motion.state&SDL_BUTTON_LMASK){
          x = event.motion.x;
          y = event.motion.y;
        }
      }
    }

    SDL_LockSurface(surface);

    uint8_t*pixels = (uint8_t*)surface->pixels;

    uint32_t const swizzleTable[] = {                                    
        surface->format->Rshift / 8u,                                    
        surface->format->Gshift / 8u,                                    
        surface->format->Bshift / 8u,                                    
    }; 

    pixels[y*surface->pitch + x*surface->format->BytesPerPixel + swizzleTable[0]] = 255;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel + swizzleTable[1]] = 0;
    pixels[y*surface->pitch + x*surface->format->BytesPerPixel + swizzleTable[2]] = 0;

    SDL_UnlockSurface(surface);

    SDL_UpdateWindowSurface(window);


  }

  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
