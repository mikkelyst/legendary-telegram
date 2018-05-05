#pragma once  
#include <vector> 
 
class CellGrid
{
private:
	GLuint tex;
	std::vector<float> cells; 
	unsigned int sizex = 0;
	unsigned int sizey = 0;

public:

	CellGrid(unsigned int x = 4, unsigned int y = 4)
	{
		sizex = (unsigned int)pow(2, x);
		sizey = (unsigned int)pow(2, y);
		glGenTextures(1, &tex); 
		cells = std::vector<float>(3 * sizex * sizey, 1.0);
		for (unsigned int i = 0; i < sizex * sizey; i++) { 
			float f = (float)(i % 2);
			cells.at(3 * (i) + 0) = f; // R
			cells.at(3 * (i) + 1) = f; // G
			cells.at(3 * (i) + 2) = f; // B 
		}

	}

	~CellGrid()
	{ 
		delete &cells;
	}

	GLuint UpdateTexture() {
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizex, sizey, 0, GL_RGB, GL_FLOAT, cells.data());
		glGenerateMipmap(GL_TEXTURE_2D);
		return tex;
	}

	void ChangePixel(unsigned int col, unsigned int row, bool state)
	{
		if (col < sizey && row < sizex)
		{
			if (state) {
				cells[3 * (sizex * row + col) + 0] = 1.0f; // R
				cells[3 * (sizex * row + col) + 1] = 1.0f; // G
				cells[3 * (sizex * row + col) + 2] = 1.0f; // B
			}
			else {
				cells[3 * (sizex * row + col) + 0] = 0.0f; // R
				cells[3 * (sizex * row + col) + 1] = 0.0f; // G
				cells[3 * (sizex * row + col) + 2] = 0.0f; // B
			}
		}else{
			std::cout << "Nonexistent cell at " << col << ',' << row << std::endl;
		}
		

	}

	 
};

