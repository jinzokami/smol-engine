
#include "RenderUtil.hpp"

void parse_obj(const char* filename, std::vector<Vert> &buffer)
{
	std::vector<Vec3> verts;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

	FILE * file = NULL;
	fopen_s(&file, filename, "r");

	if (file == NULL)
	{
		printf("Error: Model \"%s\" not loaded, doesn't exist.\n", filename);
		return;
	}

	while (!feof(file))
	{
		char t1[3];

		fscanf_s(file, " %s", t1, (unsigned int)sizeof(t1));

		if (strcmp(t1, "v") == 0)
		{
			Vec3 vert;
			fscanf_s(file, "%f %f %f", &vert.x, &vert.y, &vert.z);
			verts.push_back(vert);
		}
		else if (strcmp(t1, "vt") == 0)
		{
			Vec2 uv;
			fscanf_s(file, "%f %f", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (strcmp(t1, "vn") == 0)
		{
			Vec3 normal;
			fscanf_s(file, "%f %f %f", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(t1, "f") == 0)
		{
			//means t2, t3, t4 are v/vt/vn v/vt/vn v/vt/vn
			Face face;
			fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &face.vert[0], &face.uv[0], &face.normal[0], &face.vert[1], &face.uv[1], &face.normal[1], &face.vert[2], &face.uv[2], &face.normal[2]);
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
			Vert vertex = {
				{verts[faces[i].vert[j]].x, verts[faces[i].vert[j]].y, verts[faces[i].vert[j]].z},
				{uvs[faces[i].uv[j]].x, uvs[faces[i].uv[j]].y},
				{normals[faces[i].normal[j]].x, normals[faces[i].normal[j]].y, normals[faces[i].normal[j]].z}
			};
			buffer.push_back(vertex);
		}
	}
}