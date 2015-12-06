#include "Button.h"

Button::Button(ButtonRole _role, ButtonState _state) :
role(_role),
state(_state)

{
	// Инициализируем тестуры (не загружаем их) посреством TextureObjectManager
	// куда переаётся информация о назначении кнопки
	textureEna = nullptr;
	textureDis = nullptr;
	TextureRole enaRole, disRole;
	switch (_role)
	{
	case ButtonRole::_start:
		enaRole = TextureRole::_startEna;	//тут нужно прямую привязку к текстуре влючения выключения 
		disRole = _startDis;				//В этом коде фактически приравнивание временной переменной EnaRole или disRole
		break;								//к переменным через указатель на структуру  TexureRole и элемент из нее _startEna или _StartDis
	case ButtonRole::_select:
		enaRole = TextureRole::_selectEna; 
		disRole = _selectDis;
		break;
	}

	Какие-то махинации по присвоению текстур в определенном случае
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

/*!!!!!!!!!!!!!!!!!!!!!! ВОЗМОЖНОООООО ПОНАДОБИТСЯЯЯЯ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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