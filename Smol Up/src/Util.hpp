#pragma once

#include <vector>
#include <stdio.h>

#include <GLM\glm.hpp>

#include "Math\Arith.hpp"

inline char* load_ascii(const char* path)
{
	char* str;

	FILE * file;
	fopen_s(&file, path, "rb");
	if (file == NULL)
	{
		printf("Error: File \"%s\" not loaded, doesn't exist.\n", path);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	printf("File Loaded: \"%s\"\nFile Size is: %d\n\n", path, size);

	str = new char[size + 1];
	fread((void *)str, 1, size, file);
	str[size] = 0;
	//printf("%s\n\n", str);

	return str;
}

inline void print_mat(glm::mat4 mat)
{
	printf("[ %f, %f, %f, %f ]\n", mat[0][0], mat[1][0], mat[2][0], mat[3][0]);
	printf("[ %f, %f, %f, %f ]\n", mat[0][1], mat[1][1], mat[2][1], mat[3][1]);
	printf("[ %f, %f, %f, %f ]\n", mat[0][2], mat[1][2], mat[2][2], mat[3][2]);
	printf("[ %f, %f, %f, %f ]\n", mat[0][3], mat[1][3], mat[2][3], mat[3][3]);
}

