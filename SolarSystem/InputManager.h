/*
File: InputManager.h
Author: Richard Flanagan
Description:
*/
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class InputManager {
public:
	InputManager();
	~InputManager() {};

	void bindInputCallbacks();

	const bool isUpPressed();
	const bool isDownPressed();
	const bool isLeftPressed();
	const bool isRightPressed();
	const bool isZoomInPressed();
	const bool isZoomOutPressed();
private:
	static InputManager* thisInstance;

	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool zoomInPressed;
	bool zoomOutPressed;
	
	static void keyboardInputCallback(unsigned char key, int x, int y);
	static void keyboardInputUpCallback(unsigned char key, int x, int y);
	static void specialKeyboardInputCallback(int key, int x, int y);
	static void specialKeyboardInputUpCallback(int key, int x, int y);
};

#endif // INPUT_MANAGER_H