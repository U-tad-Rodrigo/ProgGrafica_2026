#pragma once

#define _USE_MATH_DEFINES

#ifdef GLAD_BIN
#define GLAD_GL_IMPLEMENTATION
#endif

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

// Constantes de la ventana
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Callback para redimensionar ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Procesar entrada de teclado
void processInput(GLFWwindow* window);

template <typename T>
std::vector<T> splitString(const std::string& str, char delim) {
	std::vector<T> elems;
	std::stringstream sstream(str);
	std::string item;
	T tipoDato;
	if (str != "") {
		while (std::getline(sstream, item, delim))
		{
			std::istringstream str(item);
			str >> tipoDato;
			elems.push_back(tipoDato);
		}
	}
	return elems;
}
