#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <string>

class WindowManager {
public:
	WindowManager();
	~WindowManager() {};

	void setWindowDimensions(int w, int h);
	void setWindowPosition(int xPos, int yPos);
	int getWindowWidth();
	int getWindowHeight();
	void setWindowTitle(std::string str);
	void createWindow(int argc, char** argv);

private:
	int windowWidth;
	int windowHeight;
	int windowPosX;
	int windowPosY;
	std::string windowTitle;
};

#endif // WINDOW_MANAGER_H