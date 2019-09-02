#pragma once

#include <map>
#include <SDL.h>

//! InputKey
/*! Helper class for RandomInput */
/*! Used to create a map for keyboard keys and their current state*/
class InputKey {
	public:
		/**
		*InputKey constructor
		*@param {bool} keyDown - variable that is true only if the key has just been pressed
		*@param {bool} keyHeldDown - variable that is true while the key is being pressed
		*@param {bool} keyUp - variable that is true when the key is released
		*/
		InputKey(bool keyDown, bool keyHeldDown, bool keyUp);
		bool keyDown;
		bool keyHeldDown;
		bool keyUp;
};
//! RandomInput
/*! Class for handling keyboard input */
/*! Relies on a map of InputKey objects to get and update the state of the various keyboard keys */
class RandomInput {
public:
	/*! Returns the keyDown value of the InputKey */
	/*! If the key doesn't exist in the myInputList map yet, it is emplaced in it */
	/**
	* @param {int} index - index of the key to search for
	* @return {bool}
	*/
	static bool getKeyDown(int index);
	/*! Returns the keyUp value of the InputKey */
	/*! If the key doesn't exist in the myInputList map yet, it is emplaced in it */
	/**
	* @param {int} index - index of the key to search for 
	* @return {bool}
	*/
	static bool getKeyUp(int index);
	
	/*! Returns the keyHeldDown value of the InputKey  */
	/*! If the key doesn't exist in the myInputList map yet, it is emplaced in it  */
	/**
	* @param {int} index - index of the key to search for 
	* @return {bool}
	*/
	static bool getKey(int index);
	/*! This function gets the state of the keyboard and goes through the myInputList map  */
	/*! For each key in the map, if it is being pressed, it calls updateKeyDown  */
	/*! Otherwise, it calls updateKeyUp  */
	/**
	* @return {bool}
	*/
	void checkInput();
	/**
	* Deletes the contents of the map
	*/
	void onQuitClear();
private:
	static std::map<int, InputKey*> myInputList;
	/**
	* Function that updates keyDown and keyHeldDown values for InputKey
	* @param {int} index - index of the key to search for 
	*/
	void updateKeyDown(int index);
	/**
	* Function that updates keyUp value for InputKey
	* @param {int} index - index of the key to search for
	*/
	void updateKeyUp(int index);
	const Uint8 *keyboardState;
};

