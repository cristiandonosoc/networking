#include <SDL.h>
#include <GL/gl3w.h>

#include "imgui/imgui.h"

#include <fstream>
#include <streambuf>

void RenderDrawLists(ImDrawData *drawData)
{

}

bool Init(SDL_Window *window)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;                     // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
    io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
    io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
    io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
    io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
    io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
    io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
    io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
    io.KeyMap[ImGuiKey_A] = SDLK_a;
    io.KeyMap[ImGuiKey_C] = SDLK_c;
    io.KeyMap[ImGuiKey_V] = SDLK_v;
    io.KeyMap[ImGuiKey_X] = SDLK_x;
    io.KeyMap[ImGuiKey_Y] = SDLK_y;
    io.KeyMap[ImGuiKey_Z] = SDLK_z;

    io.RenderDrawListsFn = RenderDrawLists;

    return true;
}

static GLuint gFontTexture = 0;
static int gShaderHandle = 0;
static int gVertexShaderHandle = 0;
static int gFragmentShaderHandle = 0;

static int gAttribLocationTex = 0;
static int gAttribLocationProjMtx = 0;
static int gAttribLocationPosition = 0;
static int gAttribLocationUV = 0;



bool CreateDeviceObjects()
{
    // Backup GL state
    GLint lastTexture, lastArrayBuffer, lastVertexArray;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &lastArrayBuffer);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &lastVertexArray);

    // We create the shaders
    std::ifstream vt("vertex_shader.vert");
    std::string str((std::istreambuf_iterator<char>(vt)),
                     std::istreambuf_iterator<char>());
    const GLchar *vertexShaderSource = str.c_str();

    std::ifstream ft("fragment_shader.frag");
    str = std::string((std::istreambuf_iterator<char>(ft)),
                       std::istreambuf_iterator<char>());
    const GLchar *fragmentShaderSource = str.c_str();

    gShaderHandle = glCreateProgram();
    gVertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(gVertexShaderHandle, 1, &vertexShaderSource, 0);
    glCompileShader(gVertexShaderHandle);
    glAttachShader(gShaderHandle, gVertexShaderHandle);

    gFragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(gFragmentShaderHandle, 1, &fragmentShaderSource, 0);
    glCompileShader(gFragmentShaderHandle);
    glAttachShader(gShaderHandle, gFragmentShaderHandle);

    glLinkProgram(gShaderHandle);







    gFragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
    gkS
    



}

void NewFrame(SDL_Window *window)
{
    if (!gFontTexture)
    {
        CreateDeviceObjects();
    }

}
