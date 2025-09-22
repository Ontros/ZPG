#include "Renderer.h"

int main(void)
{
	Renderer renderer = Renderer();
	renderer.init();

	renderer.loadShaders();
	renderer.loadModels();
	renderer.run();
}
