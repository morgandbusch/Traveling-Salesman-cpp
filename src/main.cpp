// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "node.h"
#include "plotter.cpp"
#include "algs.h"
#include "manager.h"
#include <stdio.h>
#include <string>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    int height = 720;
    int width = 1280;


    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(width, height, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Our state
    bool do_2swap = false;
    int swap_iterations = 1;
    float p_anneal = 0;

    //view state
    bool view_current_path = true;
    bool view_best_path = false;
    bool view_nodes = true;
    bool graph_open = true;

    int nodes_to_add = 5;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    
    Manager manager;
    Plotter plotter;

    srand(time(0));
    manager.populate(10);
    manager.reset_paths();

    plotter.load_bounds(manager);


    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwGetFramebufferSize(window, &height, &width);
        
        

        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImVec2 winsize = ImVec2(height, width);
        
        

        // do algs
        if (do_2swap){
            for(int i = 0; i < swap_iterations; i++)
                manager.random_2swap(p_anneal / 1000.0);
        }



        // graph
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Graph", &graph_open, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollWithMouse);
            ImGui::SetWindowSize(winsize);
            if(plotter.start_plot(ImGui::GetWindowSize())){
                plotter.plot_nodes(manager.get_nodes(), view_nodes);

                if(view_best_path)
                    plotter.plot_path(manager.get_best_path(), ImVec4(1, 1, 1, 1));

                if(view_current_path)
                    plotter.plot_path(manager.get_current_path(), ImVec4(0, .33f, 1, 1));
                


                plotter.end_plot();
            }
            ImGui::End();
            
        }

        // view options
        {
            ImGui::Begin("View");
            ImGui::Checkbox("Nodes", &view_nodes);
            ImGui::Checkbox("Current Path", &view_current_path);
            ImGui::Checkbox("Best Path", &view_best_path);
            ImGui::End();
        }

        // alg control panel
        {
            ImGui::Begin("Algorithms");
            ImGui::SliderInt("Iterations", &swap_iterations, 1, 1000);            
            ImGui::SameLine();
            ImGui::Checkbox("2swap", &do_2swap);

            ImGui::SliderInt("nodes", &nodes_to_add, 1, 20);
            ImGui::SameLine();
            if(ImGui::Button("Add Nodes")){
                manager.add_nodes(nodes_to_add);
                manager.reset_paths();
            }
            ImGui::SameLine();
            if(ImGui::Button("Set Nodes")){
                manager.populate(nodes_to_add);
                manager.reset_paths();
            }

            if(ImGui::Button("Reset Path")){
                manager.reset_current_path();
            }

            ImGui::SliderFloat("Prob.", &p_anneal, 0, 0.1);

            ImGui::End();
        }

        {   // Info
            ImGui::Begin("Info");


            float current_cost = manager.get_current_path().get_cost();
            std::string cost_string = "Path Cost: " + std::to_string(current_cost);
            ImGui::Text("%s", cost_string.c_str());
            
            float best_cost = manager.get_best_cost();
            std::string best_cost_string = "Best Cost: "+ std::to_string(best_cost);
            ImGui::Text("%s", best_cost_string.c_str());


            if(ImGui::Button("Reset Saved Stats")){
                manager.reset_best_path();
            }

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
