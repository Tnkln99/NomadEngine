#include "Engine.h"
#include "SandBoxScene.h"


int main()
{
	Engine engine{std::make_shared<SandBoxScene>()};
	engine.run();

	return 0;
}
