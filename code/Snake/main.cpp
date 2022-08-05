#include <Snake/SIC_ExecutionContext.hpp>

int main()
{
	auto gameContext = SIC_ExecutionContext::PrepareContext();

	while (gameContext->ShouldUpdate())
		gameContext->Update();

	return 0;
}