#pragma once
#ifndef SHADER_CLASS_H
	#define SHADER_CLASS_H

	#include<glad/glad.h>
	#include<string>
	#include<fstream>
	#include<sstream>

	std::string get_file_content(const char* filename);

	class Shader {
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void activate();
		void deactivate();

		void Delete();
	};

	#endif
