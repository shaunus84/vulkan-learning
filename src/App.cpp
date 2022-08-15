//
//  App.cpp
//  vulkan-learning
//
//  Created by Shaun Mitchell on 12/08/2022.
//

#include <stdio.h>
#include <App.h>
#include <vector>
#include <iostream>

#define VOLK_IMPLEMENTATION
#include <volk.h>

void App::run() {
    init();
    mainLoop();
    shutdown();
}

void App::init() {
    
    SDL_Init(SDL_INIT_VIDEO);

    m_pWindow = SDL_CreateWindow(
        "Vulkan Learning",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_VULKAN
    );
    
    volkInitialize();
    
    VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Vulkan Learning";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;
    
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    uint32_t extensionCount;
    SDL_Vulkan_GetInstanceExtensions(m_pWindow, &extensionCount, nullptr);
    std::vector<const char *> extensionNames(extensionCount);
    extensionNames.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    SDL_Vulkan_GetInstanceExtensions(m_pWindow, &extensionCount, extensionNames.data());
    
    createInfo.enabledExtensionCount = extensionCount + 1;
    createInfo.ppEnabledExtensionNames = extensionNames.data();
    createInfo.enabledLayerCount = 0;
    
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    
    VkResult result = vkCreateInstance(&createInfo, nullptr, &vulkanInstance);
            if (result != VK_SUCCESS) {
                printf("failed to create instance with error_code %d", result);
                throw std::runtime_error("failed to create instance!");
            } else {
                std::cout << "Instance for application " << appInfo.pApplicationName << " created successfully";
            }
    
    volkLoadInstance(vulkanInstance);
    
    m_bRunning = true;
    SDL_PumpEvents();
    
}

void App::mainLoop() {
    while(m_bRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    m_bRunning = false;
                    break;
                    
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        m_bRunning = false;
                    }
                    break;
                    
                default:
                    break;
            }
        }
    }
}

void App::shutdown() {
    
    vkDestroyInstance(vulkanInstance, nullptr);
    
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}
