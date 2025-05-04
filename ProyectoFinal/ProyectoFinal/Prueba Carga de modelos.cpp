//p10

//Prueba carga de proyectos
//  Eduardo Zavala Sanchez
//	318105538
//

#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


//KeyFrames
float PersonaPosX=4.0f, PersonaPosY=1.0f, PersonaPosZ=-3.8f;

#define MAX_FRAMES 9
int i_max_steps = 190;
int i_curr_steps = 0;
glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotChair = 180.0f; //Angulo de rotacion de sillas
float rotChair1 = 180.0f;
float rotChair2 = 180.0f;
float rotChair3 = 180.0f;
float rotChair4 = 180.0f;
float rotChair5 = 180.0f;
float rotChair6 = 180.0f;
float rotChair7 = 180.0f;
float rotChair8 = 180.0f;
float rotChair9 = 180.0f;
float rotChair10 = 180.0f;
float rotChair11 = 180.0f;
float rotChair12 = 180.0f;
float rotChair13 = 180.0f;
float rotChair14 = 180.0f;
float rotChair15 = 180.0f;
float rotChair16 = 180.0f;
float rotChair17 = 180.0f;
float rotChair18 = 180.0f;
float rotChair19 = 180.0f;
float rotChair1N = 180.0f;
float rotChair2N = 180.0f;
float rotChair3N = 180.0f;
float rotChair4N = 180.0f;
float rotChair5N = 180.0f;
float rotChair6N = 180.0f;
float rotChair7N = 180.0f;
float rotChair8N = 180.0f;
float rotChair9N = 180.0f;
float rotChair10N = 180.0f;
float rotChair11N = 180.0f;
float rotChair12N = 180.0f;
float rotChair13N = 180.0f;
float rotChair14N = 180.0f;
float rotChair15N = 180.0f;
float rotChair16N = 180.0f;
float rotChair17N = 180.0f;
float rotChair18N = 180.0f;
float rotChair19N = 180.0f;
float rotExtintor = 270.0f;
float direccion = 1.0f;
float maxRot = 2.0f;
float radio = 1.0f;        // Radio del c rculo
float amplitud = 0.5f;     // Amplitud del movimiento senoidal
float frecuencia = 2.0f;   // Frecuencia del movimiento senoidal
float velocidad = 0.01f;
bool AnimBall = false;
bool AnimChairs = false;
bool AnimChairs2 = false;
bool AnimChairs3 = false;
bool AnimChairs4 = false;
bool AnimChairs5 = false;
bool AnimChairs6 = false;
bool AnimChairs7 = false;
bool AnimFurniture = false;
bool AnimFurniture2 = false;
bool AnimFurniture3 = false;
bool AnimFurniture4 = false;
bool step = false;
float Brazos = 0.0f;
float Piernas = 0.0f;
float Cabeza = 0.0f;
float Brazos1 = 0.0f;
float Piernas1 = 0.0f;
float Cabeza1 = 0.0f;
float head = 0.0f;
int PersonaAnim1 = 0.0f;
int PersonaAnim2 = 0.0f;
int PersonaAnim3 = 0.0f;
int PersonaAnim4 = 0.0f;
float rotPantalla = 180.0f;
float rotPC = 90.0f;
float rotMonitor = -90.0f;
float angulo = 180.0f;
float rotTable = -270.0f;
float rotLib = -90.0f;
float PersonaRot = 0.0f;
glm::vec3 chairPos1(3.4f, 0.01f, -2.4f);
glm::vec3 chairPos2(3.4f, 0.01f, -1.5f);
glm::vec3 chairPos3(3.4f, 0.01f, -0.5f);
glm::vec3 chairPos4(3.4f, 0.01f, 0.5);
glm::vec3 chairPos5(3.4f, 0.01f, 1.3f);
glm::vec3 chairPos6(3.4f, 0.01f, 2.3f);
glm::vec3 chairPos7(3.4f, 0.01f, 3.0f);
glm::vec3 chairPos8(1.0f, 0.01f, -2.5f);
glm::vec3 chairPos9(1.5f, 0.01f, -1.8f);
glm::vec3 chairPos10(1.5f, 0.01f, -0.8f);
glm::vec3 chairPos11(1.5f, 0.01f, -0.1f);
glm::vec3 chairPos12(1.5f, 0.01f, 0.5f);
glm::vec3 chairPos13(1.5f, 0.01f, 1.4f);
glm::vec3 chairPos14(1.5f, 0.01f, 2.3f);
glm::vec3 chairPos15(1.0f, 0.01f, 3.0f);
glm::vec3 chairPos16(-0.3f, 0.01f, 0.0f);
glm::vec3 chairPos17(-0.3f, 0.01f, 1.3f);
glm::vec3 chairPos18(-0.3f, 0.01f, 2.5f);
glm::vec3 chairPos19(-0.3f, 0.01f, 3.0f);
glm::vec3 chairPos1N(2.8f, 0.5f, -1.9f);
glm::vec3 chairPos2N(2.8f, 0.5f, -1.0f);
glm::vec3 chairPos3N(2.8f, 0.5f, 0.0f);
glm::vec3 chairPos4N(2.8f, 0.5f, 1.0f);
glm::vec3 chairPos5N(2.8f, 0.5f, 1.8f);
glm::vec3 chairPos6N(2.8f, 0.5f, 2.7f);
glm::vec3 chairPos7N(2.8f, 0.5f, 3.4f);
glm::vec3 chairPos8N(1.6f, 0.5f, -1.8f);
glm::vec3 chairPos9N(1.0f, 0.5f, -2.0f);
glm::vec3 chairPos10N(1.0f, 0.5f, -1.3f);
glm::vec3 chairPos11N(1.0f, 0.5f, -0.3f);
glm::vec3 chairPos12N(1.0f, 0.5f, 0.3f);
glm::vec3 chairPos13N(1.0f, 0.5f, 1.0f);
glm::vec3 chairPos14N(1.0f, 0.5f, 2.0);
glm::vec3 chairPos15N(0.5f, 0.01f, 0.0f);
glm::vec3 chairPos16N(-0.8f, 0.5f, 0.0f);
glm::vec3 chairPos17N(-0.8f, 0.5f, 1.0f);
glm::vec3 chairPos18N(-0.8f, 0.5f, 2.0f);
glm::vec3 chairPos19N(-0.8f, 0.5f, 2.7f);
glm::vec3 TablePos1(2.59f, 0.0f, -3.3f);
glm::vec3 TablePos2(2.59f, 0.0f, 0.0f);
glm::vec3 TablePos3(2.59f, 0.0f, 2.4f);
glm::vec3 TablePos4(0.8f, 0.0f, -3.3f);
glm::vec3 TablePos5(0.8f, 0.0f, 0.0f);
glm::vec3 TablePos6(0.8f, 0.0f, 2.4f);
glm::vec3 TablePos7(-0.8f, 0.0f, -3.3f);
glm::vec3 TablePos8(-0.8f, 0.0f, 0.0f);
glm::vec3 TablePos9(-0.8f, 0.0f, 2.4f);
glm::vec3 chairEsc(0.0001f, 0.0001f, 0.0001f);
glm::vec3 TableEsc(0.05f, 0.05f, 0.05f);
glm::vec3 TableEsc2(0.0001f, 0.0001f, 0.0001f);
glm::vec3 PCPos1(2.6f, 0.05f, -2.6f);
glm::vec3 PCPos2(2.6f, 0.05f, 0.6f);
glm::vec3 PCPos3(2.6f, 0.05f, 3.0f);
glm::vec3 PCPos4(0.8f, 0.05f, -2.6f);
glm::vec3 PCPos5(0.8f, 0.05f, 0.6f);
glm::vec3 PCPos6(0.8f, 0.05f, 3.0f);
glm::vec3 PCPos7(-0.7f, 0.05f, -2.6f);
glm::vec3 PCPos8(-0.7f, 0.05f, 0.6f);
glm::vec3 PCPos9(-0.7f, 0.05f, 3.0f);
glm::vec3 BrazoIzqPos(2.4f, 0.808f, -3.1f);
glm::vec3 MonitorPos2(2.4f, 0.808f, 0.0f);
glm::vec3 MonitorPos3(2.4f, 0.808f, 2.4f);
glm::vec3 MonitorPos4(0.6f, 0.808f, -3.1f);
glm::vec3 MonitorPos5(0.6f, 0.808f, 0.0f);
glm::vec3 MonitorPos6(0.6f, 0.808f, 2.4f);
glm::vec3 MonitorPos7(-1.0f, 0.808f, -3.1f);
glm::vec3 MonitorPos8(-1.0f, 0.808f, 0.0f);
glm::vec3 MonitorPos9(-1.0f, 0.808f, 2.4f);
//glm::vec3 PersonaPos(4.0f, 1.00f, -3.8f);
glm::vec3 PersonaPos(PersonaPosX, PersonaPosY, PersonaPosZ);
glm::vec3 PersonaEsc(1.2f, 1.2f, 1.2f);
glm::vec3 PCEsc(0.0001f, 0.0001f, 0.0001f);
glm::vec3 MonitorEsc(0.0001f, 0.0001f, 0.0001f);


typedef struct _frame {

	float PersonaRot = 0.0f;;
	float PersonaRotInc = 0.0f;
	float PersonaPosX=4.0f;
	float PersonaPosY=1.0f;
	float PersonaPosZ=-3.8f;
	float incX;
	float incY;
	float incZ;
	float head;
	float headInc;
	float Brazos = 0.0f;
	float Piernas = 0.0f;
	float BrazosInc = 0.0f;
	float PiernasInc = 0.0f;



}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

//=================================KEYFRAMES=============================================

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].PersonaPosX = PersonaPosX;
	KeyFrame[FrameIndex].PersonaPosY = PersonaPosY;
	KeyFrame[FrameIndex].PersonaPosZ = PersonaPosZ;

	KeyFrame[FrameIndex].PersonaRot = PersonaRot;

	//Partes dela persona
	KeyFrame[FrameIndex].head = head;
	KeyFrame[FrameIndex].Brazos = Brazos;
	KeyFrame[FrameIndex].Piernas = Piernas;


	FrameIndex++;
}

void resetElements(void)
{
	PersonaPosX = KeyFrame[0].PersonaPosX;
	PersonaPosY = KeyFrame[0].PersonaPosY;
	PersonaPosZ = KeyFrame[0].PersonaPosZ;

	PersonaRot = KeyFrame[0].PersonaRot;
	//Partes del perro
	head = KeyFrame[0].head;
	Brazos = KeyFrame[0].Brazos;
	Piernas = KeyFrame[0].Piernas;
}
void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].PersonaPosX - KeyFrame[playIndex].PersonaPosX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].PersonaPosY - KeyFrame[playIndex].PersonaPosY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].PersonaPosZ - KeyFrame[playIndex].PersonaPosZ) / i_max_steps;

	KeyFrame[playIndex].PersonaRotInc = (KeyFrame[playIndex + 1].PersonaRot - KeyFrame[playIndex].PersonaRot) / i_max_steps;


}

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Eduardo Zavala Sanchez Prueba de Modelos y animacion ", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	//models
	/*Model Piso((char*)"Models/Piso.obj");
	Model Gabeta((char*)"Models/Pantalla.obj");
	Model Repisas((char*)"Models/Proyecto/Repisas.obj");
	Model Servidor((char*)"Models/Proyecto/Servidor1.obj");
	Model Lampara((char*)"Models/Proyecto/Lampara.obj");
	Model Gabeta((char*)"Models/Proyecto/Gabeta.obj");*/
	Model Mesa((char*)"Models/Proyecto/Mesa.obj");
	Model Mesa2((char*)"Models/Proyecto/Mesa2.obj");
	Model Fila_Mesa1((char*)"Models/Proyecto/Fila_Mesas1.obj");
	Model Fila_Mesa2((char*)"Models/Proyecto/Fila_Mesas2.obj");
	Model Fila_Mesa3((char*)"Models/Proyecto/Fila_Mesas3.obj");
	Model Silla_A((char*)"Models/Proyecto/Silla_A.obj");
	Model Silla_Nueva_A((char*)"Models/Proyecto/Silla_Nueva_A.obj");
	Model Silla_Nueva_G((char*)"Models/Proyecto/Silla_Nueva_G.obj");
	Model Silla_Nueva_B((char*)"Models/Proyecto/Silla_Nueva_B.obj");
	Model Silla_Nueva_N((char*)"Models/Proyecto/Silla_Nueva_N.obj");
	Model Silla_B((char*)"Models/Proyecto/Silla_B.obj");
	Model Silla_N((char*)"Models/Proyecto/Silla_N.obj");
	Model Cuarto((char*)"Models/Proyecto/labprueba.obj");
	Model Techo((char*)"Models/Proyecto/techo.obj");
	Model PC((char*)"Models/Proyecto/PC.obj");
	Model Libreria((char*)"Models/Proyecto/Libreria.obj");
	Model Puerta((char*)"Models/Proyecto/Puerta.obj");
	Model Pantalla((char*)"Models/Proyecto/Pantalla.obj");
	Model PantallaInteligente((char*)"Models/Proyecto/Pantalla_Inteligente.obj");
	Model Pizarron((char*)"Models/Proyecto/Pizarron.obj");
	Model Monitor((char*)"Models/Proyecto/Monitor.obj");
	Model TecladoMouse((char*)"Models/Proyecto/TecladoMouse.obj");
	Model Extintor((char*)"Models/Proyecto/Extintor.obj");
	Model LentesVR((char*)"Models/Proyecto/Lentes_VR.obj");
	Model Cabeza((char*)"Models/Proyecto/Cabeza.obj");
	Model Cuerpo((char*)"Models/Proyecto/Cuerpo.obj");
	Model BrazoI((char*)"Models/Proyecto/BrazoI.obj");
	Model BrazoD((char*)"Models/Proyecto/BrazoD.obj");
	Model PiernaI((char*)"Models/Proyecto/PiernaI.obj");
	Model PiernaD((char*)"Models/Proyecto/PiernaD.obj");
	//=================================================================================================================================

	//KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].PersonaPosX = 0;
		KeyFrame[i].PersonaPosY = 0;
		KeyFrame[i].PersonaPosZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].PersonaRot = 0;
		KeyFrame[i].PersonaRotInc = 0;
		KeyFrame[i].head = 0;
		KeyFrame[i].headInc = 0;
		KeyFrame[i].Brazos = 0;
		KeyFrame[i].BrazosInc = 0;
		KeyFrame[i].Piernas = 0;
		KeyFrame[i].PiernasInc = 0;

	}

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		angulo += deltaTime * 16.0f; //se puede multiplicar por una cantidad para aumentar la velocidad de rotacion
		if (angulo > 360) {
			angulo = 0.0f;
		}

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);






		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);
		glm::mat4 modelTemp(1);


		//================================================================================================================
		//Carga de modelo 
		//================================================================================================================
		view = camera.GetViewMatrix();
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cuarto.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.0f,0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Techo.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.597f, 0.0f, -0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Puerta.Draw(lightingShader);
		//==================================Carga de modelos Primera Fila=======================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(2.5f, 0.0f, 0.3f));
		model = glm::scale(model, TableEsc);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fila_Mesa1.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos7);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair7), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos6);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair6), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos5);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair5), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos4);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair4), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos3);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair3), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos2);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair2), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos1);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair1), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos1N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair7N+90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos2N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair6N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos3N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair5N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos4N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair4N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos5N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair3N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos6N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair2N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos7N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair1N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);
		//==================================Carga de modelos Segunda Fila=======================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.3f));
		model = glm::scale(model, TableEsc);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fila_Mesa2.Draw(lightingShader);
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos15);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair15-50), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos14);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair14-25), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos13);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair13 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos12);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair12 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos11);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair11), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos10);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair10 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos9);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair9 ), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos8);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair8+60), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos8N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair8N+180), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos9N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair9N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos10N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair10N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos11N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair11N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos12N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair12N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos13N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair13N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos14N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair14N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);
		//==================================Carga de modelos Tercera Fila=======================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.2f, 0.0f, 2.6f));
		model = glm::scale(model, TableEsc);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Fila_Mesa3.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos19);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair19), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos18);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair18), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos17);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair17), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_N.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos16);
		model = glm::scale(model, glm::vec3(0.037f, 0.037f, 0.037f));
		model = glm::rotate(model, glm::radians(rotChair16), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos16N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair16N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_A.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos17N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair17N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_B.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos18N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair18N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_G.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, chairPos19N);
		model = glm::scale(model, chairEsc);
		model = glm::rotate(model, glm::radians(rotChair19N + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Silla_Nueva_N.Draw(lightingShader);
		//======================================================================================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(4.1f, 0.02f, 2.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		model = glm::rotate(model, glm::radians(rotLib), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Libreria.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.7f, 3.4f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(rotPantalla), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pantalla.Draw(lightingShader);
		
		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-1.3f, 0.7f, -2.5f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(rotPantalla-90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pantalla.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-2.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, glm::radians(rotPantalla - 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PantallaInteligente.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotPantalla +90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.0f, 0.2f, 2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, glm::radians(rotPantalla + 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pizarron.Draw(lightingShader);

		//model = glm::mat4(1);
		//model = glm::translate(modelTemp, glm::vec3(4.0f, 0.2f, -3.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, glm::radians(rotPantalla - 90), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Pizarron.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.5f, 1.5f, -3.8f));
		model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
		model = glm::rotate(model, glm::radians(rotExtintor ), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Extintor.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(0.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, glm::radians(rotPantalla - 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		LentesVR.Draw(lightingShader);
		//============================================Mesas========================================================================================

		model = glm::mat4(1);
		model = glm::translate(modelTemp, glm::vec3(-3.0f, 0.2f, 2.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, glm::radians(rotTable - 90), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa.Draw(lightingShader);
		////=====================================Fila1=============================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp,TablePos1);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos1);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, BrazoIzqPos);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos2);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos2);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos2);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos3);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos3);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos3);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);
		//=====================================Fila2=============================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos4);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos4);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos4);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos5);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos5);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos5);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos6);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos6);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos6);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);
		//=====================================Fila3=============================================
		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos7);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos7);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos7);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos8);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos8);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos8);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, TablePos9);
		model = glm::scale(model, TableEsc2);
		model = glm::rotate(model, glm::radians(rotTable), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mesa2.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, PCPos9);
		model = glm::scale(model, PCEsc);
		model = glm::rotate(model, glm::radians(rotPC), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PC.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(modelTemp, MonitorPos9);
		model = glm::scale(model, MonitorEsc);
		model = glm::rotate(model, glm::radians(rotMonitor), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Monitor.Draw(lightingShader);
		//=====================================Modelo de Persona==========================================================
		model = glm::mat4(1);
		modelTemp = model = glm::translate(model, glm::vec3(PersonaPosX, PersonaPosY, PersonaPosZ));
		model = glm::scale(model, PersonaEsc);
		modelTemp = model = glm::rotate(model, glm::radians(PersonaRot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo.Draw(lightingShader);

		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.031f, 0.173f, 0.0f));
		model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza.Draw(lightingShader);

		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.061f, 0.107f, -0.05f));
		model = glm::rotate(model, glm::radians(Brazos1), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoI.Draw(lightingShader);

		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.00f, 0.107f, -0.05f));
		model = glm::rotate(model, glm::radians(Brazos1), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		BrazoD.Draw(lightingShader);

		model = modelTemp;
		//model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218));
		model = glm::rotate(model, glm::radians(Piernas1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaI.Draw(lightingShader);

		model = modelTemp;
		//model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		model = glm::rotate(model, glm::radians(Piernas1), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		PiernaD.Draw(lightingShader);
		//================================================================================================================
		// 
		//================================================================================================================
		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)

		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_K])
	{
		PersonaPosZ += 0.008f;
		printf("%f", PersonaPosZ);
	}

	if (keys[GLFW_KEY_H])
	{
		PersonaPosZ -= 0.008f;
		printf("%f", PersonaPosZ);
	}
	if (keys[GLFW_KEY_U])
	{
		PersonaPosX += 0.008f;
		printf("%f", PersonaPosX);
	}
	if (keys[GLFW_KEY_J])
	{
		PersonaPosX -= 0.008f;
		printf("%f", PersonaPosX);
	}
	if (keys[GLFW_KEY_Z])
	{
		PersonaPosY -= 1.0f;
		printf("%f", PersonaPosY);
	}
	if (keys[GLFW_KEY_X])
	{
		PersonaPosZ += 1.0f;
		printf("%f", PersonaPosY);
	}
	if (keys[GLFW_KEY_B])
	{
		PersonaAnim1 = 1;
	}

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);

		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
	if (keys[GLFW_KEY_N])
	{
		AnimChairs = !AnimChairs;
		chairPos15.x += 0.7;
		chairPos14.x += 0.2;

	}
	if (keys[GLFW_KEY_M])
	{
		AnimChairs7 = !AnimChairs7;
		AnimFurniture = !AnimFurniture;
		rotChair8N -= 90;

	}
	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{
			printf("sI SE ESTA PRESIONANDOOOOOO%f");
			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}
	if (keys[GLFW_KEY_1])
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

	}
}
//GLuint modelLoc = glGetUniformLocation(lampShader.Program, "model");
void Animation() {

	if (AnimChairs) {
		if (chairPos1.z >= -3.8) {
			chairPos1.z -= 0.01;
			AnimChairs2 = !AnimChairs2;
		}
		if (chairPos2.z >= -3.8) {
			chairPos2.z -= 0.01;
		}
		if (chairPos3.z >= -3.8) {
			chairPos3.z -= 0.01;
		}
		if (chairPos4.z >= -3.8) {
			chairPos4.z -= 0.01;
		}
		if (chairPos5.z >= -3.8) {
			chairPos5.z -= 0.01;
		}
		if (chairPos6.z >= -3.8) {
			chairPos6.z -= 0.01;
		}
		if (chairPos7.z >= -3.8) {
			chairPos7.z -= 0.01;
		}

	}
	
	if (AnimChairs2) {
		if (chairPos1.z <= -3.8) {
			rotChair1 += 1.01;
			chairPos1.x += 0.01;
		}
		if (chairPos2.z <= -3.8) {
			rotChair2 += 1.01;
			chairPos2.x += 0.01;
		}
		if (chairPos3.z <= -3.8) {
			rotChair3 += 1.01;
			chairPos3.x += 0.01;
		}
		if (chairPos4.z <= -3.8) {
			rotChair4 += 1.01;
			chairPos4.x += 0.01;
		}
		if (chairPos5.z <= -3.8) {
			rotChair5 += 1.01;
			chairPos5.x += 0.01;
		}
		if (chairPos6.z <= -3.8) {
			rotChair6 += 1.01;
			chairPos6.x += 0.01;
		}
		if (chairPos7.z <= -3.8) {
			rotChair7 += 1.01;
			chairPos7.x += 0.01;
		}
		if (chairPos7.x >= 4.0) {
			AnimChairs3 = !AnimChairs3;
		}
		
	}
	if (AnimChairs3) {
		if (chairPos8.z >= -3.8) {
			chairPos8.z -= 0.01;
			AnimChairs4 = !AnimChairs4;
		}
		if (chairPos9.z >= -3.8) {
			chairPos9.z -= 0.01;
		}
		if (chairPos10.z >= -3.8) {
			chairPos10.z -= 0.01;
		}
		if (chairPos11.z >= -3.8) {
			chairPos11.z -= 0.01;
		}
		if (chairPos12.z >= -3.8) {
			chairPos12.z -= 0.01;
		}
		if (chairPos13.z >= -3.8) {
			chairPos13.z -= 0.01;
		}
		if (chairPos14.z >= -3.8) {
			chairPos14.z -= 0.01;
		}
		if (chairPos15.z >= -3.8) {
			chairPos15.z -= 0.01;
		}
	}
	if (AnimChairs4) {
		if (chairPos8.z <= -3.8) {
			rotChair8 += 1.01;
			chairPos8.x += 0.01;
		}
		if (chairPos9.z <= -3.8) {
			rotChair9 += 1.01;
			chairPos9.x += 0.01;
		}
		if (chairPos10.z <= -3.8) {
			rotChair10 += 1.01;
			chairPos10.x += 0.01;
		}
		if (chairPos11.z <= -3.8) {
			rotChair11 += 1.01;
			chairPos11.x += 0.01;
		}
		if (chairPos12.z <= -3.8) {
			rotChair12 += 1.01;
			chairPos12.x += 0.01;
		}
		if (chairPos13.z <= -3.8) {
			rotChair13 += 1.01;
			chairPos13.x += 0.01;
		}
		if (chairPos14.z <= -3.8) {
			rotChair14 += 1.01;
			chairPos14.x += 0.01;
		}
		if (chairPos15.z <= -3.8) {
			rotChair15 += 1.01;
			chairPos15.x += 0.01;
		}
		if (chairPos15.x >= 4.0) {
			AnimChairs5 = !AnimChairs5;
		}
		

	}
	if (AnimChairs5) {
		if (chairPos16.z >= -3.8) {
			chairPos16.z -= 0.01;
			AnimChairs6 = !AnimChairs6;
		}
		if (chairPos17.z >= -3.8) {
			chairPos17.z -= 0.01;
		}
		if (chairPos18.z >= -3.8) {
			chairPos18.z -= 0.01;
		}
		if (chairPos19.z >= -3.8) {
			chairPos19.z -= 0.01;
		}
	}
	if (AnimChairs6) {
		if (chairPos16.z <= -3.8) {
			rotChair16 += 1.01;
			chairPos16.x += 0.01;
		}
		if (chairPos17.z <= -3.8) {
			rotChair17 += 1.01;
			chairPos17.x += 0.01;
		}
		if (chairPos18.z <= -3.8) {
			rotChair18 += 1.01;
			chairPos18.x += 0.01;
		}
		if (chairPos19.z <= -3.8) {
			rotChair19 += 1.01;
			chairPos19.x += 0.01;
		}
		if (chairPos19.x >= 4.0) {
			AnimChairs7 = !AnimChairs7;
		}
	}
	if (AnimChairs7) {
		if (chairEsc.z <=1.1) {
			chairEsc.z += 0.01;
		}
		if (chairEsc.y <= 1.1) {
			chairEsc.y += 0.01;
		}
		if (chairEsc.x <= 1.1) {
			chairEsc.x += 0.01;
		}
	}
	if (AnimFurniture) {
		if (TableEsc.z >= -0.0001) {
			TableEsc.z -= 0.001;
		}
		if (TableEsc.y >= -0.0001) {
			TableEsc.y -= 0.001;
		}
		if (TableEsc.x >= -0.0001) {
			TableEsc.x -= 0.001;
		}
		if (chairPos1N.x>=2.6) {
			chairPos1N.x -= 0.01;
		}
		if (chairPos1N.z >= -3.5) {
			chairPos1N.z -= 0.01;
		}
		if (chairPos2N.x >= 2.6) {
			chairPos2N.x -= 0.01;
		}
		if (chairPos2N.z >= -2.7) {
			chairPos2N.z -= 0.01;
		}
		if (chairPos3N.x >= 2.6) {
			chairPos3N.x -= 0.01;
		}
		if (chairPos3N.z >= 0) {
			chairPos3N.z -= 0.01;
		}
		if (chairPos4N.x >= 2.6) {
			chairPos4N.x -= 0.01;
		}
		if (chairPos4N.z >= 0.8) {
			chairPos4N.z -= 0.01;
		}
		if (chairPos5N.x >= 0.9) {
			chairPos5N.x -= 0.01;
		}
		if (chairPos5N.z <= 3.3) {
			chairPos5N.z += 0.01;
		}
		if (chairPos6N.x >= 2.6) {
			chairPos6N.x -= 0.01;
		}
		if (chairPos6N.z >= 2.7) {
			chairPos6N.z -= 0.01;
		}
		if (chairPos7N.x >= 2.6) {
			chairPos7N.x -= 0.01;
		}
		if (chairPos7N.z >= 3.3) {
			chairPos7N.z -= 0.01;
		}
		if (chairPos8N.x >= 0.9) {
			chairPos8N.x -= 0.01;
		}
		if (chairPos8N.z >= -3.5) {
			chairPos8N.z -= 0.01;
		}
		if (chairPos9N.x >= 0.9) {
			chairPos9N.x -= 0.01;
		}
		if (chairPos9N.z >= -2.7) {
			chairPos9N.z -= 0.01;
		}
		if (chairPos10N.x >= 0.9) {
			chairPos10N.x -= 0.01;
		}
		if (chairPos10N.z <= 0.0) {
			chairPos10N.z += 0.01;
		}
		if (chairPos11N.x >= 0.9) {
			chairPos11N.x -= 0.01;
		}
		if (chairPos11N.z <= 0.8) {
			chairPos11N.z += 0.01;
		}
		if (chairPos12N.x >= 0.9) {
			chairPos12N.x -= 0.01;
		}
		if (chairPos12N.z <= 2.7) {
			chairPos12N.z += 0.01;
		}
		if (chairPos13N.x >=-0.7) {
			chairPos13N.x -= 0.01;
		}
		if (chairPos13N.z >=-3.5) {
			chairPos13N.z -= 0.01;
		}
		if (chairPos14N.x >=-0.7) {
			chairPos14N.x -= 0.01;
		}
		else {
			AnimFurniture2 = !AnimFurniture2;
		}
		if (chairPos14N.z >=-2.7) {
			chairPos14N.z -= 0.01;
		}
		if (chairPos16N.x <= -0.7) {
			chairPos16N.x += 0.01;
		}
		if (chairPos16N.z >= 0.0) {
			chairPos16N.z -= 0.01;
		}
		if (chairPos17N.x <= -0.7) {
			chairPos17N.x += 0.01;
		}
		if (chairPos17N.z >= 0.8) {
			chairPos17N.z -= 0.01;
		}
		if (chairPos18N.x <= -0.7) {
			chairPos18N.x += 0.01;
		}
		if (chairPos18N.z <= 2.7) {
			chairPos18N.z += 0.01;
		}
		if (chairPos19N.x <= -0.7) {
			chairPos19N.x += 0.01;
		}
		if (chairPos19N.z <= 3.4) {
			chairPos19N.z += 0.01;
			
		}
		
	}
	if (AnimFurniture2) {
		if (TableEsc2.z <= 0.05) {
			TableEsc2.z += 0.001;
		}
		if (TableEsc2.y <= 0.05) {
			TableEsc2.y += 0.001;
		}
		if (TableEsc2.x <= 0.05) {
			TableEsc2.x += 0.001;
		}

		else {
			AnimFurniture3 = !AnimFurniture3;
		}
		
	}
	if (AnimFurniture3) {
		if (PCEsc.z <= 0.05) {
			PCEsc.z += 0.001;
		}
		if (PCEsc.y <= 0.05) {
			PCEsc.y += 0.001;
		}
		if (PCEsc.x <= 0.05) {
			PCEsc.x += 0.001;
		}
		if (MonitorEsc.z <= 0.05) {
			MonitorEsc.z += 0.0005;
		}
		if (MonitorEsc.y <= 0.05) {
			MonitorEsc.y += 0.0005;
		}
		if (MonitorEsc.x <= 0.05) {
			MonitorEsc.x += 0.0005;
		}
		if (rotMonitor < 1710) {
			rotMonitor += 10;
		}
	}
	if (PersonaAnim1 == 1 && FrameIndex<5)
	{

		KeyFrame[FrameIndex].PersonaPosX = PersonaPosX;
		KeyFrame[FrameIndex].PersonaPosY = PersonaPosY;
		KeyFrame[FrameIndex].PersonaPosZ = PersonaPosZ;
		KeyFrame[FrameIndex].PersonaRot = PersonaRot;
		KeyFrame[FrameIndex].head = head;
		KeyFrame[FrameIndex].Brazos = Brazos;
		KeyFrame[FrameIndex].Piernas = Piernas;
		FrameIndex++;

		KeyFrame[FrameIndex].PersonaPosX = 6.0f;
		KeyFrame[FrameIndex].PersonaPosY = 1.0f;
		KeyFrame[FrameIndex].PersonaPosZ = -3.8f;
		KeyFrame[FrameIndex].PersonaRot = PersonaRot;
		KeyFrame[FrameIndex].head = head;
		KeyFrame[FrameIndex].Brazos = Brazos;
		KeyFrame[FrameIndex].Piernas = Piernas;
		FrameIndex++;
		
		KeyFrame[FrameIndex].PersonaPosX = 4.0f;
		KeyFrame[FrameIndex].PersonaPosY = 1.0f;
		KeyFrame[FrameIndex].PersonaPosZ = -3.8f;
		KeyFrame[FrameIndex].PersonaRot = PersonaRot;
		KeyFrame[FrameIndex].head = head;
		KeyFrame[FrameIndex].Brazos = Brazos;
		KeyFrame[FrameIndex].Piernas = Piernas;
		FrameIndex++;
	
		KeyFrame[FrameIndex].PersonaPosX = 3.5f;
		KeyFrame[FrameIndex].PersonaPosY = 1.0f;
		KeyFrame[FrameIndex].PersonaPosZ = 1.23f;
		KeyFrame[FrameIndex].PersonaRot = -90;
		KeyFrame[FrameIndex].head = head;
		KeyFrame[FrameIndex].Brazos = Brazos;
		KeyFrame[FrameIndex].Piernas = Piernas;
		FrameIndex++;
	
		KeyFrame[FrameIndex].PersonaPosX = -1.7f;
		KeyFrame[FrameIndex].PersonaPosY = 1.0;
		KeyFrame[FrameIndex].PersonaPosZ = 1.23;
		KeyFrame[FrameIndex].PersonaRot = PersonaRot;
		KeyFrame[FrameIndex].head = 0.03;
		KeyFrame[FrameIndex].Brazos = 15.1;
		KeyFrame[FrameIndex].Piernas = 15.1;
		FrameIndex++;

		KeyFrame[FrameIndex].PersonaPosX = 3.5f;
		KeyFrame[FrameIndex].PersonaPosY = 1.0f;
		KeyFrame[FrameIndex].PersonaPosZ = 1.23;
		KeyFrame[FrameIndex].PersonaRot = +180;
		KeyFrame[FrameIndex].head = -0.003;
		KeyFrame[FrameIndex].Brazos = -15.1;
		KeyFrame[FrameIndex].Piernas = -15.1;
		FrameIndex++;

		KeyFrame[FrameIndex].PersonaPosX = 4.0f;
		KeyFrame[FrameIndex].PersonaPosY = 1.0f;
		KeyFrame[FrameIndex].PersonaPosZ = -3.8f;
		KeyFrame[FrameIndex].PersonaRot = 90;
		KeyFrame[FrameIndex].head = head;
		KeyFrame[FrameIndex].Brazos = 15.1;
		KeyFrame[FrameIndex].Piernas = 15.1;
		FrameIndex++;

		KeyFrame[FrameIndex].PersonaPosX = 6.0f;
		KeyFrame[FrameIndex].PersonaPosY = 1.0f;
		KeyFrame[FrameIndex].PersonaPosZ = -3.8f;
		KeyFrame[FrameIndex].PersonaRot = PersonaRot;
		KeyFrame[FrameIndex].head = head;
		KeyFrame[FrameIndex].Brazos = -15.1;
		KeyFrame[FrameIndex].Piernas = -15.1;
		FrameIndex++;

		PersonaAnim1 = 2;
		
	}
	if (PersonaAnim1 == 2)
	{
		if (!step) {
			Piernas1 += 0.1f;
			Brazos1 += 0.1f;
			head += 0.03f;

			if (Piernas1 > 15.0f)
				step = true;
		}
		else {
			Piernas1 -= 0.1f;
			Brazos1 -= 0.1f;
			head -= 0.03f;

			if (Piernas1 < -15.0f)
				step = false;
		}
	}
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			PersonaPosX += KeyFrame[playIndex].incX;
			PersonaPosY += KeyFrame[playIndex].incY;
			PersonaPosZ += KeyFrame[playIndex].incZ;
			head += KeyFrame[playIndex].headInc;
			PersonaRot += KeyFrame[playIndex].PersonaRotInc;

			Brazos += KeyFrame[playIndex].BrazosInc;
			Piernas += KeyFrame[playIndex].PiernasInc;

			i_curr_steps++;
		}

	}
	}




void MouseCallback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}