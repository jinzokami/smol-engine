#pragma once

#include <cstdio>
#include <iostream>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION

#include "Util.hpp"
#include "Render/RenderUtil.hpp"

#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Window.hpp"
#include "Render/Mesh.hpp"
#include "Render/Shader.hpp"
#include "Render/Texture.hpp"
#include "Render/Camera.hpp"
#include "Render/VertexBuffer.hpp"
#include "Render/VertexArray.hpp"
#include "Render/VertexLayout.hpp"