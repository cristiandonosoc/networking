#include <SDL.h>
#include <GL/gl3w.h>

#include "imgui/imgui.h"

#include <fstream>
#include <streambuf>

void RenderDrawLists(ImDrawData *drawData)
{

}

bool Init()
{
    ImGuiIO& io = ImGui::GetIO();
    // Keyboard mapping. 
    // ImGui will use those indices to peek into the io.KeyDown[] array.
    io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;                     
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
    
    // io.SetClipboardTextFn
    // io.GetClipboardTextFn
    
    return true;
}

static GLuint gFontTexture = 0;

void CreateFontsTexture()
{
    ImGuiIO& io = ImGui::GetIO();
    unsigned char *pixels;
    int width, height;

    // Load as RGBA 32-bits for OpenGL3 demo because it is 
    // more likely to be compatible with user's existing shader.
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    // Upload texture to graphics system
    GLint lastTexture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
    glGenTextures(1, &gFontTexture);
    glBindTexture(GL_TEXTURE_2D, gFontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Send the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, 
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Store the identief
    io.Fonts->TexID = (void *)(intptr_t)gFontTexture;

    // Restore the state
    glBindTexture(GL_TEXTURE_2D, lastTexture);
}

static int gShaderHandle = 0;
static int gVertexShaderHandle = 0;
static int gFragmentShaderHandle = 0;

static int gAttribLocationTex = 0;
static int gAttribLocationProjMtx = 0;
static int gAttribLocationPosition = 0;
static int gAttribLocationUV = 0;
static int gAttribLocationColor = 0;

static unsigned int gVBOHandle = 0;
static unsigned int gVAOHandle = 0;
static unsigned int gElementsHandle = 0;

bool CreateDeviceObjects()
{
    // Backup GL state
    GLint lastTexture, lastArrayBuffer, lastVertexArray;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &lastArrayBuffer);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &lastVertexArray);

    // We create the shaders
    gShaderHandle = glCreateProgram();

    // Vertex Shader
    // Read
    std::ifstream vt("vertex_shader.vert");
    std::string str((std::istreambuf_iterator<char>(vt)),
                     std::istreambuf_iterator<char>());
    const GLchar *vertexShaderSource = str.c_str();
    // Compile/Create/Attach
    gVertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(gVertexShaderHandle, 1, &vertexShaderSource, 0);
    glCompileShader(gVertexShaderHandle);
    glAttachShader(gShaderHandle, gVertexShaderHandle);

    // Fragment Shader
    // Read
    std::ifstream ft("fragment_shader.frag");
    str = std::string((std::istreambuf_iterator<char>(ft)),
                       std::istreambuf_iterator<char>());
    const GLchar *fragmentShaderSource = str.c_str();
    // Compile/Create/Attach
    gFragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(gFragmentShaderHandle, 1, &fragmentShaderSource, 0);
    glCompileShader(gFragmentShaderHandle);
    glAttachShader(gShaderHandle, gFragmentShaderHandle);

    glLinkProgram(gShaderHandle);

    gAttribLocationTex      = glGetUniformLocation(gShaderHandle, "Texture");
    gAttribLocationProjMtx  = glGetUniformLocation(gShaderHandle, "ProjMtx");

    gAttribLocationPosition = glGetAttribLocation(gShaderHandle, "Position");
    gAttribLocationUV       = glGetAttribLocation(gShaderHandle, "UV");
    gAttribLocationColor    = glGetAttribLocation(gShaderHandle, "Color");

    glGenBuffers(1, &gVBOHandle);
    glBindBuffer(GL_ARRAY_BUFFER, gVBOHandle);

    glGenBuffers(1, &gVAOHandle);
    glBindVertexArray(gVAOHandle);

    glGenBuffers(1, &gElementsHandle);

    glEnableVertexAttribArray(gAttribLocationPosition);
    glEnableVertexAttribArray(gAttribLocationUV);
    glEnableVertexAttribArray(gAttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    glVertexAttribPointer(gAttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
    glVertexAttribPointer(gAttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
    glVertexAttribPointer(gAttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

    CreateFontsTexture();

    // Restore modified OpenGL state
    glBindTexture(GL_TEXTURE_2D, lastTexture);
    glBindBuffer(GL_ARRAY_BUFFER, lastArrayBuffer);
    glBindVertexArray(lastVertexArray);

    return true;
}

static double gTime = 0.0f;
static bool gMousePressed[3] = { false, false, false };
static float gMouseWheel = 0.0f;

void NewFrame(SDL_Window *window)
{
    if (!gFontTexture)
    {
        CreateDeviceObjects();
    }

    ImGuiIO& io = ImGui::GetIO();

    // Setup display size (every frame to accommodate for window resizing)
    int windowWidth, windowHeight;
    int displayWidth, displayHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    SDL_GL_GetDrawableSize(window, &displayWidth, &displayHeight);
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);
    io.DisplayFramebufferScale = ImVec2((windowWidth > 0) ? ((float)displayWidth / windowWidth) : 0,
                                        (windowHeight > 0) ? ((float)displayHeight / windowHeight) : 0);

    // Setup the timestep
    Uint32 time = SDL_GetTicks();
    double currentTime = time / 1000.0;
    io.DeltaTime = (gTime > 0.0) ? (float)(currentTime - gTime) : (float)(1.0f / 60.0f);
    gTime = currentTime;

    // Setup inputs
    // (we already got mouse wheel, keyboard & characters from SDL_PollEvent)
    
    // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
    int mouseX, mouseY;
    Uint32 mouseMask = SDL_GetMouseState(&mouseX, &mouseY);
    if (!(SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS))
    {
        mouseX = -1;
        mouseY = -1;
    }
    io.MousePos = ImVec2((float)mouseX, (float)mouseY);

    io.MouseDown[0] = gMousePressed[0] || ((mouseMask & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0);
    io.MouseDown[1] = gMousePressed[1] || ((mouseMask & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0);
    io.MouseDown[2] = gMousePressed[2] || ((mouseMask & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);

    gMousePressed[0] = gMousePressed[1] = gMousePressed[2] = false;

    io.MouseWheel = gMouseWheel;
    gMouseWheel = 0.0f;

    // Hide OS cursor if ImGui is drawing it
    SDL_ShowCursor(io.MouseDrawCursor ? 0 : 1);

    // Start the frame
    ImGui::NewFrame();
}


void InvalidateDeviceObjects()
{
    if (gVAOHandle) { glDeleteVertexArrays(1, &gVAOHandle); }
    if (gVBOHandle) { glDeleteBuffers(1, &gVBOHandle); }
    if (gElementsHandle) { glDeleteBuffers(1, &gElementsHandle); }

    gVAOHandle = gVBOHandle = gElementsHandle = 0;

    glDetachShader(gShaderHandle, gVertexShaderHandle);
    glDeleteShader(gVertexShaderHandle);
    gVertexShaderHandle = 0;

    glDetachShader(gShaderHandle, gFragmentShaderHandle);
    glDeleteShader(gFragmentShaderHandle);
    gFragmentShaderHandle = 0;

    glDeleteProgram(gShaderHandle);

    if (gFontTexture)
    {
        glDeleteTextures(1, &gFontTexture);
        ImGui::GetIO().Fonts->TexID = 0;
        gFontTexture = 0;
    }
}

void Shutdown()
{
    InvalidateDeviceObjects();
    ImGui::Shutdown();
}
