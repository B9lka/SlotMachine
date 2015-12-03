/* Class Button */

enum ButtonState
{
	_enabled,
	_disabled
};

/* Роль кнопки. Start или Select */
enum ButtonRole
{
	_start,
	_select,
};

class Button
{
public:

	Button( ButtonRole _role, ButtonState);
	virtual ~Button();

	// Виртуальный метод для обновления текущего состояния объекта
	virtual void Update();
	// Устанавливает состояние для объекта. 
	void setState(int _state)
	{
		state = _state;
	}
	// Получаем текущее состояние
	int getState() const 
	{
		return state;
	}
	// Возвращает роль объекта 
	ButtonRole getButtonRole() const
	{
		return role;
	}
	
	/*!!!!!!!!!!!!!!!!!!!!!! ВОЗМОЖНОООООО ПОНАДОБИТСЯЯЯЯ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Фунцция приинимает относительные координаты x и y и проверяет
	// находятся ли они в относительных координатах объекта. Применяется для 
	// проверки, была ли нажата ЛКМ на соответствующем объекте
	bool checkPos(double x, double y);
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	void drawbutton(void)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( -3.0, -2.0,  -0.1);
		glTexCoord2f(0, 1); glVertex3f( -3.0, -1.5,  -0.1);
		glTexCoord2f(1, 1); glVertex3f( -2.0, -1.5,  -0.1);
		glTexCoord2f(1, 0); glVertex3f( -2.0, -2.0,  -0.1);
		glEnd();
	}

private:
	UINT ButtonTextureArray[4];
	// Роль кнопки (какая именно кнопка)
	ButtonRole role;
	// Возвращает состояние кнопки
	int state;
	// Связанные текстуры. Отображают состояние кнопки,
	// кога она выключена или включена
	//TextureObjectManager *textureEna;
	//TextureObjectManager *textureDis;

};	
	

	/*Выдрано из примера, набросок того как должна меняться текстура в зависимости от нажатия
	void Update() 
	{
	
		// Обновляем значение флага ena для текстур, связанных с кнопкой
		// одну текстуру выключаем, другую включаем, 
		// в зависимости от предыдущего состояния
		
		TextureMap *TextureMap = this->getTextureMap();
		TextureMap::iterator it;
		for (it = TextureMap->begin(); it != TextureMap->end(); it ++)
		{
			it->second->ena = !(it->second->ena);
		}
	
		// Изменяем текущее состояние на противоположное
		if (this->getState() == ButtonState::_disabled) {
			this->setState(ButtonState::_enabled);
		}
		else {
			this->setState(ButtonState::_disabled);
		}
		
	}
	*/


	/*!!!!!!!!!!!!!!!!!!!!!! ВОЗМОЖНОООООО ПОНАДОБИТСЯЯЯЯ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ButtonState getButtonState() const
	{
		return state
	}
	bool Button::checkPos(double x, double y) 
	{
		if ((x > pos.lb_xrf) && (x < pos.rt_xrf) && (y > pos.lb_yrf) && (y < pos.rt_yrf)) 
		{
			return true;
		}
		else {
			return false;
		}
	}
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
