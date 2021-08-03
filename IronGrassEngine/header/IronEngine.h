#pragma once

#include "IronWindow.h"
class IronEngine
{
public:
	IronWindow main_window;


public:
	void initialize();
	void setWindow(IronWindow window);
	void exit();
};

