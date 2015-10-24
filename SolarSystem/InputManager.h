#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class InputManager {
public:
	InputManager() {};
	~InputManager() {};
	void bindInputCallbacks();
private:
	static void mouseClickCallback(int button, int state, int x, int y);
	static void mouseMoveCallback(int x, int y);
	static void passiveMouseMoveCallback(int x, int y);
	static void keyboardInputCallback(unsigned char key, int x, int y);
	static void specialKeyboardInputCallback(int key, int x, int y);
};

#endif // INPUT_MANAGER_H