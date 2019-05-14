
#include "RenderUtil.hpp"
/*
std::vector<Vert> load_verts_from_file(const char* path)
{
	std::vector<Vec3> verts;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

	std::vector<Vert> out_verts;

	//TODO: parse each line of the file.
	//depending on the first 1-2 chars the line represents something different.
	//mtllib is supposed to be important, but idgaf
	//o denotes a new object, we'll have to have submeshes within each model.
	//v is a vertex position. they should be loaded in the order they appear.
	//vt is a texture coordinate.
	//vn is a normal, the number of these does not neccessarily correspond
		//to the number of vertices, sometimes it's the number of faces, sometimes it's vertices.
	//no idea what s means (smoothing group, but no idea what THAT means)
	//usemtl is another idgaf
	//blender exports model info in a very specific way:
	//o object_name
	//v x.x y.y z.z
	//...
	//vt u.u v.v
	//...
	//vn x.x y.y z.z
	//...
	//usemtl
	//s ?
	//f v/vt/vn v/vt/vn v/vt/vn
	//...
	//next object or eof
	//
	//the spec seems to assume that data is not thrown out when the next object is loaded.
	//
	//process:
	//parse each line, if line is v, vt, or vn push vec3 or vec2 to appropriate vector
	//if line is f, assemble a trio of verts using the v, vt, vn indices specified by the line.
	//if line is o, create a new mesh named whatever comes after o
	//verts are pushed to the last o created


	std::ifstream file(path);
	while (!file.eof())
	{
		std::string buffer;
		std::getline(file, buffer);
		std::stringstream line(buffer);
		//printf("%s\n", buffer);
		std::string token;
		line >> token;

		if (token == "v")
		{
			std::string vx, vy, vz;
			line >> vx;
			line >> vy;
			line >> vz;
			Vec3 vec = { std::stof(vx), std::stof(vx), std::stof(vx) };
			verts.push_back(vec);
		}
		else if (token == "vn")
		{
			std::string vx, vy, vz;
			line >> vx;
			line >> vy;
			line >> vz;
			Vec3 vec = { std::stof(vx), std::stof(vx), std::stof(vx) };
			normals.push_back(vec);
		}
		else if (token == "vt")
		{
			std::string vx, vy;
			line >> vx;
			line >> vy;
			Vec2 vec = { std::stof(vx), std::stof(vx) };
			uvs.push_back(vec);
		}
		else if (token == "f")
		{
			Face face;
			std::string v, vn, vt;

			std::getline(line, v, '/');
			std::getline(line, vt, '/');
			std::getline(line, vn, ' ');

			face.vert[0] = std::stoi(v) - 1;
			face.uv[0] = std::stoi(vt) - 1;
			face.normal[0] = std::stoi(vn) - 1;

			printf("v: %s | vt: %s | vn: %s\n", v.c_str(), vt.c_str(), vn.c_str());

			std::getline(line, v, '/');
			std::getline(line, vt, '/');
			std::getline(line, vn, ' ');

			face.vert[1] = std::stoi(v) - 1;
			face.uv[1] = std::stoi(vt) - 1;
			face.normal[1] = std::stoi(vn) - 1;

			printf("v: %s | vt: %s | vn: %s\n", v.c_str(), vt.c_str(), vn.c_str());

			std::getline(line, v, '/');
			std::getline(line, vt, '/');
			std::getline(line, vn, ' ');

			face.vert[2] = std::stoi(v) - 1;
			face.uv[2] = std::stoi(vt) - 1;
			face.normal[2] = std::stoi(vn) - 1;

			printf("v: %s | vt: %s | vn: %s\n", v.c_str(), vt.c_str(), vn.c_str());

			faces.push_back(face);
		}
		//TODO: add support for 'o' instructions, and return multiple meshes, one for each 'o'
	}

	for (int i = 0; i < faces.size(); i++)
	{
		out_verts.push_back({
			{verts[faces[i].vert[0]].x, verts[faces[i].vert[0]].y, verts[faces[i].vert[0]].z},
			{uvs[faces[i].uv[0]].x, uvs[faces[i].uv[0]].y},
			{normals[faces[i].normal[0]].x, normals[faces[i].normal[0]].y, normals[faces[i].normal[0]].z}
			});

		out_verts.push_back({
			{verts[faces[i].vert[1]].x, verts[faces[i].vert[1]].y, verts[faces[i].vert[1]].z},
			{uvs[faces[i].uv[1]].x, uvs[faces[i].uv[1]].y},
			{normals[faces[i].normal[1]].x, normals[faces[i].normal[1]].y, normals[faces[i].normal[1]].z}
			});

		out_verts.push_back({
			{verts[faces[i].vert[2]].x, verts[faces[i].vert[2]].y, verts[faces[i].vert[2]].z},
			{uvs[faces[i].uv[2]].x, uvs[faces[i].uv[2]].y},
			{normals[faces[i].normal[2]].x, normals[faces[i].normal[2]].y, normals[faces[i].normal[2]].z}
			});
	}

	return out_verts;
}
*/

void parse_obj(const char* filename, std::vector<Vert> &buffer)
{
	std::vector<Vec3> verts;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

	FILE * file = NULL;
	fopen_s(&file, filename, "r");

	while (!feof(file))
	{
		char t1[3];

		fscanf_s(file, " %s", t1, sizeof(t1));

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