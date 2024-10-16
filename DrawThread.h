#pragma once
#include "CommonObject.h"

class DrawThread
{
public:
	void operator()(CommonObjects& common);
	//void DrawAppWindow(void* common_ptr);
};

