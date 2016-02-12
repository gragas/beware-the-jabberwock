#ifdef DEBUG
#define WINDOW_MODE NULL
#else
#define WINDOW_MODE glfwGetPrimaryMonitor()
#endif

#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode,
						 int action, int mods);

int main() {
    glfwSetErrorCallback(error_callback);

    if(glfwInit() == GL_FALSE) {
		exit(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(1280, 960,
										  "Beware The Jabberwock",
										  WINDOW_MODE, NULL);
    if(window == NULL) {
		glfwTerminate();
		exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    glfwSetKeyCallback(window, key_callback);

    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);


    while(!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();	
		
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

static void key_callback(GLFWwindow* window, int key, int scancode,
						 int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "ERROR!\nError Number: %d\n%s", error, description);
}
