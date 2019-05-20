#include "Material.hpp"
Material::Material()
{
}
//Materials are shaders coupled with textures that actually apply visual effects to meshes.
//eventually, fetch shaders and textures from a cache system, loading them from disk each time/creating new ones before instantiating could be a pain.
Material::Material(Shader shader) : shader(shader)
{
}

Material::Material(Shader shader, std::vector<Texture> &textures) : shader(shader), textures(textures)
{
}

Material::~Material()
{
}

void Material::bind()
{
	shader.bind();
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i].bind(i);
	}
}
