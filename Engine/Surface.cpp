#include "Surface.h"
#include "ChiliWin.h"
#include <fstream>
#include "assert.h"

Surface::Surface(int width_in, int height_in)
	:
	width(width_in),
	height(height_in)
{
	pPixels = new Color[width * height];
}

Surface::Surface(const std::string & filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);
	
	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);

	const bool is32bit = (bmInfoHeader.biBitCount == 32);

	width = bmInfoHeader.biWidth;

	// intialzing loop control depending on direction (top left or bottom left)
	int yStart;
	int yEnd;
	int dy;

	height = bmInfoHeader.biHeight;

	if (height < 0)
	{
		height *= -1;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}

	pPixels = new Color[width * height];

	file.seekg(bmFileHeader.bfOffBits);

	const int padding = (4 - (width * 3) % 4) % 4;

	for (int j = yStart; j != yEnd; j += dy)
	{
		for (int i = 0; i < width; i++)
		{
			PutPixel(i, j, Color(file.get(), file.get(), file.get()));

			if (is32bit)
			{
				file.seekg(1, std::ios::cur);
			}
		}

		if (!is32bit)
		{
			file.seekg(padding, std::ios::cur);
		}
	}
}

Surface::Surface(const Surface & src)
	:
	width(src.width),
	height(src.height)
{
	pPixels = new Color[src.width, src.height];

	for (int x = 0; x < src.width; x++)
	{
		for (int y = 0; y < src.height; y++)
		{
			pPixels[y * src.width + x] = src.pPixels[y * src.width + x];
		}
	}
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface & Surface::operator=(const Surface & src)
{
	width = src.width;
	height = src.height;

	//deep copying surface
	delete[] pPixels;
	pPixels = nullptr;

	pPixels = new Color[src.width, src.height];

	for (int x = 0; x < src.width; x++)
	{
		for (int y = 0; y < src.height; y++)
		{
			pPixels[y * src.width + x] = src.pPixels[y * src.width + x];
		}
	}

	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}
