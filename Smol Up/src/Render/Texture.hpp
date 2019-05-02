#include "../stb_image.h"

#include "RenderUtil.hpp"

//TODO: add loading an error texture when textures do not exist.
class Texture
{
public:
	Texture(Image img);
	Texture(const char* path);
	~Texture();

	void upload();

	void bind();
	void unbind();

	Pixel get_pixel(u32 x, u32 y);
	void set_pixel(u32 x, u32 y, u8 r, u8 g, u8 b);

	Image image;
	GLuint id = 0;
protected:
private:
};