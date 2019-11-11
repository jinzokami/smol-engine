
#include "RenderUtil.hpp"

void parse_obj(const char* filename, std::vector<Vert> &buffer, bool &has_uv, bool &has_normal)
{
	//if any features are missing, fill them with dummy values, the shader should ignore the dummy values, wasteful improve this.
	std::vector<Vec3> verts;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

	bool tex_present = true;
	bool norm_present = true;

	FILE * file = NULL;
	fopen_s(&file, filename, "r");

	if (file == NULL)
	{
		printf("Error: Model \"%s\" not loaded, doesn't exist.\n", filename);
		return;
	}

	while (!feof(file))
	{
		char token[3];

		fscanf_s(file, "%s", token, (unsigned int)sizeof(token));

		if (strcmp(token, "v") == 0)
		{
			Vec3 vert;
			fscanf_s(file, "%f %f %f", &vert.x, &vert.y, &vert.z);
			verts.push_back(vert);
		}
		else if (strcmp(token, "vt") == 0)
		{
			Vec2 uv;
			fscanf_s(file, "%f %f", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (strcmp(token, "vn") == 0)
		{
			Vec3 normal;
			fscanf_s(file, "%f %f %f", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(token, "f") == 0)
		{
			//means tokens 2, 3, and 4 are v/vt/vn v/vt/vn v/vt/vn
			Face face;
			int matched;
			char f[3][256];
			fscanf_s(file, "%s %s %s", f[0], (unsigned int)sizeof(f[0]), f[1], (unsigned int)sizeof(f[1]), f[2], (unsigned int)sizeof(f[2]));
			for (int i = 0; i < 3; i++)
			{
				//detect missing features
				int match = sscanf_s(f[i], "%d/%d/%d", &face.vert[i], &face.uv[i], &face.normal[i]);
				if (match != 3)
				{
					match = sscanf_s(f[i], "%d//%d", &face.vert[i], &face.normal[i]);

					if (match != 2)
					{
						match = sscanf_s(f[i], "%d/%d", &face.vert[i], &face.uv[i]);

						if (match != 2)
						{
							match = sscanf_s(f[i], "%d", &face.vert[i]);

							//missing normal and uv
							face.uv[i] = 0;

							face.normal[i] = 0;

							tex_present = false;
							norm_present = false;
						}
						else
						{
							//missing normal
							face.normal[i] = 0;

							norm_present = false;
						}
					}
					else
					{
						//missing uv
						face.uv[i] = 0;

						tex_present = false;
					}
				}
			}

			//obj files count from 1 here we move down to 0
			face.vert[0]--; face.vert[1]--; face.vert[2]--;
			face.uv[0]--; face.uv[1]--; face.uv[2]--;
			face.normal[0]--; face.normal[1]--; face.normal[2]--;
			faces.push_back(face);
		}
		//advance to the next line. maybe. TODO: guarantee advancement to the next line.
		char dec_buf[256];
		fgets(dec_buf, 256, file);
	}

	for (int i = 0; i < faces.size(); i++)
	{
		for (int j = 0; j < 3; j++) //that hardcoded 3 could be however many vertices in the "face" if we ever support n-gons or quads
		{
			Vert vertex;

			if (tex_present && norm_present)
			{
				vertex = {
				{verts[faces[i].vert[j]].x, verts[faces[i].vert[j]].y, verts[faces[i].vert[j]].z},
				{uvs[faces[i].uv[j]].x, uvs[faces[i].uv[j]].y},
				{normals[faces[i].normal[j]].x, normals[faces[i].normal[j]].y, normals[faces[i].normal[j]].z}
				};
			}
			else if (tex_present)
			{
				vertex = {
				{verts[faces[i].vert[j]].x, verts[faces[i].vert[j]].y, verts[faces[i].vert[j]].z},
				{uvs[faces[i].uv[j]].x, uvs[faces[i].uv[j]].y},
				{0, 0, 0}
				};
			}
			else if (norm_present)
			{
				vertex = {
				{verts[faces[i].vert[j]].x, verts[faces[i].vert[j]].y, verts[faces[i].vert[j]].z},
				{0, 0},
				{normals[faces[i].normal[j]].x, normals[faces[i].normal[j]].y, normals[faces[i].normal[j]].z}
				};
			}
			else
			{
				vertex = {
				{verts[faces[i].vert[j]].x, verts[faces[i].vert[j]].y, verts[faces[i].vert[j]].z},
				{0, 0},
				{0, 0, 0}
				};
			}
			
			buffer.push_back(vertex);
		}
	}
}