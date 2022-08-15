//
//  App.h
//  vulkan-learning
//
//  Created by Shaun Mitchell on 12/08/2022.
//

#ifndef App_h
#define App_h


#include <SDL.h>
#include <SDL_vulkan.h>

class SDL_Window;

class App final {
    
public:
    void run();
    
private:
    void init();
    void mainLoop();
    void shutdown();
    
private:
    SDL_Window* m_pWindow {nullptr};
    bool m_bRunning {false};
    VkInstance vulkanInstance;
    
};


#endif /* App_h */
