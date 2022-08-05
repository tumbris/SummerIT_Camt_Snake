#include <Snake/SIC_ExecutionContext.hpp>

#include <Snake/Constants.hpp>

std::unique_ptr<SIC_ExecutionContext> SIC_ExecutionContext::PrepareContext()
{
	std::unique_ptr<SIC_ExecutionContext> context(new SIC_ExecutionContext);
	context->myWindow.create(sf::VideoMode(Constants::WindowSizeX, Constants::WindowSizeY), Constants::WindowTitle);
	
	context->Initialize();
	return std::move(context);
}

void SIC_ExecutionContext::Initialize()
{
	myWorldModel.Initialize();
}

void SIC_ExecutionContext::Update()
{
	myFrameTime = myFrameClock.restart().asSeconds();

	myWindow.clear();

	myWorldModel.Update(*this);

	myWindow.display();
}

bool SIC_ExecutionContext::ShouldUpdate() const
{
	return myWindow.isOpen();
}
