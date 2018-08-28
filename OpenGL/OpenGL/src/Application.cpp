#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	const int width = 960;
	const int height = 540;
	const std::string title = "Hello World";

	const double scale = 2;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow((int) (width * scale), (int)(height * scale), title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); 

	if (glewInit() != GLEW_OK)
		std::cout << "ERROR!" << std::endl;

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	{
		float positions[] = {
			 -50.0f, -50.0f, 0.0f, 0.0f, // 0
			  50.0f, -50.0f, 1.0f, 0.0f, // 1
			  50.0f,  50.0f, 1.0f, 1.0f, // 2
			 -50.0f,  50.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indicies[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indicies, 6);

		glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float) height, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform1i("u_Texture", 0);

		Texture texture("res/textures/baseball.png");
		texture.Bind();

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind(); 


		float r = 0.0f;
		float increment = 0.05f;

		glm::vec3 translationA(200, 200, 0);
		glm::vec3 translationB(400, 200, 0);

		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			ImGui_ImplGlfwGL3_NewFrame();

			shader.Bind();

			// draw A
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}

			// draw B
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				renderer.Draw(va, ib, shader);
			}




			r += increment;
			if (r > 1.0f) {
				increment = -0.05f;
			}
			else if (r < 0.0f) {
				increment = 0.05f;
			}

			{
				ImGui::SliderFloat3("Translation A", &translationA.x, 0, width);            // Edit 1 float using a slider from 0.0f to 1.0f    
				ImGui::SliderFloat3("Translation B", &translationB.x, 0, width);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}


	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}