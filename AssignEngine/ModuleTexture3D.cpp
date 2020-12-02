#include "Globals.h"

#include "ModuleTexture3D.h"
#include "BaseMesh.h"

#include "Devil/include/IL/il.h"
#include "Devil/include/IL/ilu.h"
#include "Devil/include/IL/ilut.h"

#pragma comment(lib, "Devil/libx86/DevIL.lib")
#pragma comment(lib, "Devil/libx86/ILU.lib")
#pragma comment(lib, "Devil/libx86/ILUT.lib")

ModuleTexture3D::ModuleTexture3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleTexture3D::~ModuleTexture3D()
{
}

bool ModuleTexture3D::Init()
{
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) {
		LOG("DevIL version is different...exiting!\n");
		return false;
	}

	ilInit();
	iluInit();
	ilutInit();

	ilutRenderer(ILUT_OPENGL);

	return true;
}

bool ModuleTexture3D::Start()
{
	return true;
}

GLuint ModuleTexture3D::LoadTexture(const char* name)
{
	ILuint imageID;
	GLuint textureID;
	ILenum error;
	ILboolean success;

	ilGenImages(1, &imageID);
	ilBindImage(imageID);

	success = ilLoadImage(name);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	if (success) {
		ILinfo info_img;
		iluGetImageInfo(&info_img);

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		ILubyte* DataTexture = ilGetData();
		int width = 0;
		int height = 0;

		width = (int)ilGetInteger(IL_IMAGE_WIDTH);
		height = (int)ilGetInteger(IL_IMAGE_HEIGHT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, DataTexture);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		error = ilGetError();
		LOG("Loading image fail. Error: %i, %s", error, iluErrorString(error));

	}

	ilDeleteImages(1, &imageID);

	LOG("Texture created succesfully");
	return textureID;


}

bool ModuleTexture3D::CleanUp()
{

	return UPDATE_CONTINUE;
}
