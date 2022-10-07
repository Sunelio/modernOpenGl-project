#include <App.h>


using namespace Core;
using namespace LowRendere;
using namespace std;


bool App::mouseCaptured = false;
float App::mouseDeltaX = 0.0;
float App::mouseDeltaY = 0.0;
int App::width = 0;
int App::height = 0;

void processInput(GLFWwindow* window, bool  mouseCaptured)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void cursorEnterCallback(GLFWwindow* window, int enterd);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);




void App::Init(AppInitializer init)
{
	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	window = glfwCreateWindow(init.width, init.height, init.name, NULL, NULL);
	width = init.width;
	height = init.height;
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, init.Framebuffer_size_callback);

	// glfw set cursor parameters.
	// -------------------------------------------
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);

	glfwSetMouseButtonCallback(window, mouseButtonCallback);



	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;

	}


	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(init.glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}


}



void App::Update()
{
	glEnable(GL_DEPTH_TEST);


	Vector3D translate;
	Vector3D rotation;
	Vector3D rotate;

	CameraInputs inputs;
	Camera camera(width, height);


	// Create resources.
	resource.Create(new Resources::Model, "cube", "Resources/Obj/cube.obj");
	resource.Create(new Resources::Model, "robot", "Resources/Obj/bender.obj");
	resource.Create(new Resources::Texture, "bender","Resources/Textures/bender.png");
	resource.Create(new Resources::Texture, "harold", "Resources/Textures/harold.jpg");
	resource.Create(new Resources::Texture, "wall", "Resources/Textures/wall.jpg");

	// Set Shader and link.
	shader.SetVertexShader("Resources/Shaders/vertexShaderSource.vert");
	shader.SetFragmentShader("Resources/Shaders/fragmentShaderSource.frag");
	shader.Link();

	// Create gameObject;
	GameObject robot(((Resources::Model*)resource.Get("robot")),&shader,((Resources::Texture*)resource.Get("bender")));
	GameObject cube1(((Resources::Model*)resource.Get("cube")), &shader, ((Resources::Texture*)resource.Get("harold")));
	GameObject cube2(((Resources::Model*)resource.Get("cube")),&shader, ((Resources::Texture*)resource.Get("wall")));
	GameObject cubeLight1(((Resources::Model*)resource.Get("cube")), &shader, ((Resources::Texture*)resource.Get("wall")));
	GameObject cubeLight2(((Resources::Model*)resource.Get("cube")), &shader, ((Resources::Texture*)resource.Get("wall")));
	GameObject cubeLight3(((Resources::Model*)resource.Get("cube")), &shader, ((Resources::Texture*)resource.Get("wall")));

	//robot.AddChild(cube1);

	GLuint sampler = 0;
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

	GLint max = 0;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

	glBindSampler(0, sampler);

	//glBindTextureUnit(1, texture2);
	//glBindSampler(1, sampler);

	//pointer inside the light table in the .h.
	dirLights->activeLight = 1;
	pointLights->activeLight = 0;
	spotLights->activeLight = 0;

	Vector3D rotationX = Vector3D::zero;
	Vector3D rotationY = Vector3D::zero;
	Vector3D rotationZ = Vector3D::zero;

	while (!glfwWindowShouldClose(window))
	{
		for (int i = 0; i < dirLights->activeLight ; ++i)
		{
			dirLights->LightSetUp(shader.shaderProgram, i);
		}

		for (int i = 0; i < pointLights->activeLight ; ++i)
		{
			pointLights->LightSetUp(shader.shaderProgram, i);
		}

		for (int i = 0; i < spotLights->activeLight; ++i)
		{
			spotLights->LightSetUp(shader.shaderProgram, i);
		}
		// input
		// lights intensity to set
		spotLights[0].intensity = 0.8f;
		pointLights[0].intensity = 0.8f;
		dirLights[0].intensity = 0.8f;

		// -----
		glfwPollEvents();
		processInput(window, mouseCaptured);
		CameraInputApp(camera, inputs, mouseCaptured, mouseDeltaX, mouseDeltaY, window);
		// render
		// ------
		glClearColor(0, 0, 0, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		//glBindTexture(GL_TEXTURE_2D, texture);

		
		// Draw object.
		
		robot.mesh->Draw();
		cube1.mesh->Draw();
		cube2.mesh->Draw();
		cubeLight1.mesh->Draw();
		cubeLight2.mesh->Draw();
		cubeLight3.mesh->Draw();

		//Direction light
		//spotLights[0].direction = Vector3D(0,0,1);
		//dirLights[0].direction = Vector3D(0, 0, 1);

		//move lights
		//spotLights[0].position = camera.transform.position;
		spotLights[0].position = Vector3D(-1.0f, 0.0f, 0.0f);
		pointLights[0].position = Vector3D(3.0f, 0.0f, 0.0f);
		//Move object.
		// 
		rotationZ.z++;
		rotationX.x++;
		rotationY.y++;

		cubeLight1.transform.scale = Vector3D(0.1, 0.1, 0.1);
		cubeLight1.transform.position = pointLights[0].position;

		cubeLight2.transform.scale = Vector3D(0.1, 0.1, 0.1);

		cubeLight3.transform.scale = Vector3D(0.1, 0.1, 0.1);
		cubeLight3.transform.position = spotLights[0].position;
		
		cube1.transform.scale = Vector3D(5, 5, 0.5);
		cube1.transform.position = Vector3D(0.0f, 4.5f, -7.0f);

		cube2.transform.scale = Vector3D(4, 0.5, 4);
		cube2.transform.position = Vector3D(0.0f, -2.0f, 0.0f);

		robot.transform.position = Vector3D(0.0f, -1.0f, 1.0f);
		robot.transform.rotation = rotationY;

		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);

	}
	resource.DeleteAll();
	//glDeleteTextures(1, &texture1);
	glDeleteSamplers(1, &sampler);
}


void App::CameraInputApp(Camera& camera, CameraInputs& inputs, bool& mouseCaptured, double mouseDeltaX, double mouseDeltaY, GLFWwindow* window)
{
	const float deltatime = 0.1;
	if (mouseCaptured)
	{
		inputs.deltaX = mouseDeltaX;
		inputs.deltaY = mouseDeltaY;
		inputs.moveForward = glfwGetKey(window, GLFW_KEY_UP);
		inputs.moveForward == GLFW_PRESS;
		inputs.moveBackward = glfwGetKey(window, GLFW_KEY_DOWN);
		inputs.moveBackward == GLFW_PRESS;
		inputs.moveLeftSide = glfwGetKey(window, GLFW_KEY_LEFT);
		inputs.moveLeftSide == GLFW_PRESS;
		inputs.moveRightSide = glfwGetKey(window, GLFW_KEY_RIGHT);
		inputs.moveRightSide == GLFW_PRESS;
		inputs.rotateRight = glfwGetKey(window, GLFW_KEY_D);
		inputs.rotateRight == GLFW_PRESS;
		inputs.rotateLeft = glfwGetKey(window, GLFW_KEY_A);
		inputs.rotateLeft == GLFW_PRESS;
		inputs.rotateUp = glfwGetKey(window, GLFW_KEY_W);
		inputs.rotateUp == GLFW_PRESS;
		inputs.rotateDown = glfwGetKey(window, GLFW_KEY_S);
		inputs.rotateDown == GLFW_PRESS;

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
			camera.ResetCameraTransform();

		camera.Update(deltatime, inputs);
	}
}
void cursorEnterCallback(GLFWwindow* window, int enterd)
{
	if (enterd)
	{
		App::mouseCaptured = true;
	}
	else
		App::mouseCaptured = false;
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}

App::App()
{

}

