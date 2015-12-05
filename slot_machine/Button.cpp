#include "Button.h"

Button::Button(ButtonRole _role, ButtonState _state) :
role(_role),
state(_state)

{
	// �������������� ������� (�� ��������� ��) ���������� TextureObjectManager
	// ���� �������� ���������� � ���������� ������
	textureEna = nullptr;
	textureDis = nullptr;
	TextureRole enaRole, disRole;
	switch (_role)
	{
	case ButtonRole::_start:
		enaRole = TextureRole::_startEna;	//��� ����� ������ �������� � �������� �������� ���������� 
		disRole = _startDis;				//� ���� ���� ���������� ������������� ��������� ���������� EnaRole ��� disRole
		break;								//� ���������� ����� ��������� �� ���������  TexureRole � ������� �� ��� _startEna ��� _StartDis
	case ButtonRole::_select:
		enaRole = TextureRole::_selectEna; 
		disRole = _selectDis;
		break;
	}

	�����-�� ��������� �� ���������� ������� � ������������ ������
	textureEna = new TextureObjectManager(TextureGroup::_buttons, false, this);
	textureDis = new TextureObjectManager(TextureGroup::_buttons, true, this);

	TextureMap *textureMap = this->getTextureMap();
	textureMap->insert(TexturePair(enaRole, textureEna->getTexture()));
	textureMap->insert(TexturePair(disRole, textureDis->getTexture()));
}


Button::~Button()
{
}



void Button::Update() 
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



ButtonRole Button::getButtonRole() const
{
	return role;
}

void Button::setState(int _state) 
{
	state = _state;
}

int Button::getState() const 
{
	return state;
}
	
void drawbutton(void)
{
	
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -3.0, -2.0,  -0.1);
	glTexCoord2f(0, 1); glVertex3f( -3.0, -1.5,  -0.1);
	glTexCoord2f(1, 1); glVertex3f( -2.0, -1.5,  -0.1);
	glTexCoord2f(1, 0); glVertex3f( -2.0, -2.0,  -0.1);
	glEnd();
	/*
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -3.0, -2.0,  -0.1);
	glTexCoord2f(0, 1); glVertex3f( -3.0, -1.5,  -0.1);
	glTexCoord2f(1, 1); glVertex3f( -2.0, -1.5,  -0.1);
	glTexCoord2f(1, 0); glVertex3f( -2.0, -2.0,  -0.1);
	glEnd();
	*/
}

/*!!!!!!!!!!!!!!!!!!!!!! ������������� ��������������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ButtonState Button::getButtonState() const
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