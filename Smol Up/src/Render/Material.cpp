#include "Material.hpp"
Material::Material()
{
}
//Materials are shaders coupled with textures that actually apply visual effects to meshes.
//eventually, fetch shaders and textures from a cache system, loading them from disk each time/creating new ones before instantiating could be a pain.
Material::Material(Shader shader)
{
	this->shader = shader;
	//error for now, just a white texture, eventually
	this->texture[0] = Texture("res/texture/error.bmp");
	this->texture[1] = Texture("res/texture/error.bmp");
	this->texture[2] = Texture("res/texture/error.bmp");
	this->texture[3] = Texture("res/texture/error.bmp");
}

Material::Material(Shader shader, Texture texture[4])
{
	this->shader = shader;
	this->texture[0] = texture[0];
	this->texture[1] = texture[1];
	this->texture[2] = texture[2];
	this->texture[3] = texture[3];
}

Material::~Material()
{
}

void Material::bind()
{
	shader.bind();
	for (int i = 0; i < 4; i++)
	{
		texture[i].bind(i);
	}
}
