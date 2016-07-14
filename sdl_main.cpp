#include "imgui/imgui.h"
#include <GL/gl3w.h>

#include <iostream>
#include <SDL.h>

#include "imgui_impl.cpp"

int main(int, char **)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Initial OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // TODO(Cristian): Is this necessary?
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    // We create the window
    SDL_Window *window = SDL_CreateWindow("ImGui SDL2+OpenGL3 example", 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          1280, 720, 
                                          SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // We init the open gl extensions
    gl3wInit();
    Init();
    
    // "Game loop"
    ImVec4 clearColor = ImColor(114, 114, 154);
    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // TODO(Cristian): Process events
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        NewFrame(window);

        // Show simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() 
        // the widgets appears in a window automatically called "Debug"
        ImGui::Text("Hello World!");

        // Rendering
        ImGuiIO& io = ImGui::GetIO();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    Shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
