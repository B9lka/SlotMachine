/* Class Button */

enum ButtonState
{
	_enabled,
	_disabled
};

/* ���� ������. Start ��� Select */
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

	// ����������� ����� ��� ���������� �������� ��������� �������
	virtual void Update();
	// ������������� ��������� ��� �������. 
	void setState(int _state)
	{
		state = _state;
	}
	// �������� ������� ���������
	int getState() const 
	{
		return state;
	}
	// ���������� ���� ������� 
	ButtonRole getButtonRole() const
	{
		return role;
	}
	
	/*!!!!!!!!!!!!!!!!!!!!!! ������������� ��������������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ������� ���������� ������������� ���������� x � y � ���������
	// ��������� �� ��� � ������������� ����������� �������. ����������� ��� 
	// ��������, ���� �� ������ ��� �� ��������������� �������
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
	// ���� ������ (����� ������ ������)
	ButtonRole role;
	// ���������� ��������� ������
	int state;
	// ��������� ��������. ���������� ��������� ������,
	// ���� ��� ��������� ��� ��������
	//TextureObjectManager *textureEna;
	//TextureObjectManager *textureDis;

};	
	

	/*������� �� �������, �������� ���� ��� ������ �������� �������� � ����������� �� �������
	void Update() 
	{
	
		// ��������� �������� ����� ena ��� �������, ��������� � �������
		// ���� �������� ���������, ������ ��������, 
		// � ����������� �� ����������� ���������
		
		TextureMap *TextureMap = this->getTextureMap();
		TextureMap::iterator it;
		for (it = TextureMap->begin(); it != TextureMap->end(); it ++)
		{
			it->second->ena = !(it->second->ena);
		}
	
		// �������� ������� ��������� �� ���������������
		if (this->getState() == ButtonState::_disabled) {
			this->setState(ButtonState::_enabled);
		}
		else {
			this->setState(ButtonState::_disabled);
		}
		
	}
	*/


	/*!!!!!!!!!!!!!!!!!!!!!! ������������� ��������������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
