#pragma once
#include "Base.h"

class RESOURCE
{
public:
	std::vector<IMAGE*>frame_list;
public:
	RESOURCE(LPCTSTR path,int n)
	{
		TCHAR path_file[256];
		for (int i = 0; i < n; i++)
		{
			_stprintf_s(path_file, path, i);
			IMAGE* image = new IMAGE;
			loadimage(image, path_file);
			frame_list.push_back(image);
		}
	}
	~RESOURCE()
	{
		for (int i = 0; i <frame_list.size(); i++)
			delete frame_list[i];
	}
};

