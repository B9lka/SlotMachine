// TODO: В C++ правильно использовать хедеры из стандартной библиотеки С так:
// xxx.h = cxxx
//#include <time.h>
#include <ctime>

#include <gl\glut.h>

#include "main.hpp"
#include "texture.hpp"
#include "reel.hpp"
#include "slotmachine.hpp"

/* TODO: тут и далее, глобалы - зло. Если пишешь на сpp напрашивается какой-то основновной класс как точка входа, все эти глобалы будут там как прайваты. */
HDC			hDC=NULL;				// Приватный контекст устройства GDI
HGLRC		hRC=NULL;				// Постоянный контекст рендеринга
HWND		hWnd=NULL;				// Указатель на наше окно
HINSTANCE	hInstance;				// Указывает на дескриптор текущего приложения

bool		keys[256];				// Массив для процедуры обработки клавиатуры
bool		active=TRUE;			// Флаг активности окна, по умолчанию=TRUE
bool		fullscreen=TRUE;		// Флаг полноэкранного режима, по умолчанию=TRUE

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //Объявление для WndProc

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

SlotMachine *slotmachine;
//Button *button; 

void CALLBACK cbFunct(UINT, UINT, DWORD_PTR, DWORD_PTR , DWORD_PTR) 
{ 
    slotmachine->physicsproc();
}

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height==0)
	{
		Height=1;						// Предотвращение деления на ноль, если окно слишком мало
	}		
		
	glViewport(0, 0, Width, Height);	// Сброс текущей области вывода и перспективных преобразований
	
	glMatrixMode(GL_PROJECTION);		// Выбор матрицы проекций
	glLoadIdentity();					// Сброс матрицы проекции
	
	// Вычисление соотношения геометрических размеров для окна
	//gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
		
	glMatrixMode(GL_MODELVIEW);			// Выбор матрицы просмотра модели
	glLoadIdentity();
	
}

int InitGL()											// Инициализация OpenGL
{
	glEnable(GL_LIGHTING);
    GLfloat LightAmbient[]= { .001f, .001f, .001f, 1.0f };
    GLfloat LightDiffuse[]= { .04f, .04f, .04f, 1.0f };
    GLfloat LightPosition[]= { 0.0f, 0.0f, -100.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
    glEnable(GL_LIGHT1);
	
	glShadeModel(GL_SMOOTH);							// Включить сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Очистка экрана черным цветом
	glClearDepth(1.0f);									// Установка буфера глубины
	glEnable(GL_DEPTH_TEST);							// Включить буфер глубины
	glDepthFunc(GL_LEQUAL);								// Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Улучшенные вычисления перспективы
	
	return TRUE;										// Инициализация прошла успешно
}

int DrawGLScene()										// Здесь содержится код рисования
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Очистка экрана и буфера глубины
	glLoadIdentity();									// Сброс просмотра
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
    glLoadIdentity();
	gluPerspective(60.0f, 1.33, .1, 100.0f);
	slotmachine->draw();
    Sleep (1);
	//button->drawbutton(); 
	/* НАМЕТКИ КНОПОК
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -3.0, -2.0,  -0.1);
	glTexCoord2f(0, 1); glVertex3f( -3.0, -1.5,  -0.1);
	glTexCoord2f(1, 1); glVertex3f( -2.0, -1.5,  -0.1);
	glTexCoord2f(1, 0); glVertex3f( -2.0, -2.0,  -0.1);
	glEnd();	

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f( -1.5, -2.0,  -0.1);
	glTexCoord2f(0, 1); glVertex3f( -1.5, -1.5,  -0.1);
	glTexCoord2f(1, 1); glVertex3f( -0.5, -1.5,  -0.1);
	glTexCoord2f(1, 0); glVertex3f( -0.5, -2.0,  -0.1);
	glEnd();	
	*/

	return TRUE;						
}

GLvoid KillGLWindow(GLvoid)								// Должным образом уничтожаем окно
{
	if (fullscreen)										// Мы в полно экранном режииме?
	{
		ChangeDisplaySettings (NULL, 0);				// Если да, то перключаемся на рабочий стол
		ShowCursor (TRUE);								// Показываем курсор мыши
	}
	
	DisableOpenGL (hWnd, hDC, hRC);
	DestroyWindow (hWnd);
	UnregisterClass ("GLSample", hInstance);			// Разрегистрируем класс

}

/*	Эта часть программы создает наше окно OpenGL.  Параметры:							*
 *	title			- Заголовок, отображаемый наверху окна								*
 *	width			- Ширина GL окна или полноэкранного режима							*
 *	height			- Высота GL окна или полноэкранного режима							*
 *	bits			- Количество бит на цвет (8/16/24/32)								*
 *	fullscreenflag	- Использование полноэкранного (TRUE) или оконного(FALSE) режимов	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	WNDCLASS	wc;						// Структура классов Windows
	DWORD		dwExStyle;				// Расширенный стиль окна
	DWORD		dwStyle;				// Стиль окна
	RECT		WindowRect;				// Получает значения верхнего левого и нижнего правого углов прямоугольника
	WindowRect.left=(long)0;			// Устанавливает значение лево (Left) в 0
	WindowRect.right=(long)width;		// Устанавливает значение право (Right) в требуемую ширину (Width)
	WindowRect.top=(long)0;				// Устанавливает значение верх (Top) в 0
	WindowRect.bottom=(long)height;		// Устанавливает значение низ (Bottom) в требуемую высоту (Height)

	fullscreen=fullscreenflag;			// Устанавливаем глобальный флвг Fullscreen

	hInstance			= GetModuleHandle(NULL);				// Захватываем Instance для нашего окна
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Перерисовываем по размеру, и получаем DC для окна.
	wc.lpfnWndProc		= WndProc;								// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// Нет дополнительных данных окна
	wc.cbWndExtra		= 0;									// Нет дополнительных данных окна
	wc.hInstance		= hInstance;							// Установим Instance
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// Згрузим иконку по умолчанию
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Згрузим стрелку курсора
	wc.hbrBackground	= (HBRUSH) GetStockObject (BLACK_BRUSH);// Фон для GL
	wc.lpszMenuName		= NULL;									// Нам не нужны меню
	wc.lpszClassName	= "GLSample";							// Установим имя класса
	RegisterClass(&wc);											// Регистрируем класс окна
		
	if (fullscreen)												// Попытаться включить полноеэкранный режим?
	{
		DEVMODE dmScreenSettings;								// Режим устройства
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Убедимся, что памать очищена
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Размер структуры devmode
		dmScreenSettings.dmPelsWidth	= width;				// Выбрана ширина экрана
		dmScreenSettings.dmPelsHeight	= height;				// Выбрана высота экрана
		dmScreenSettings.dmBitsPerPel	= bits;					// Выбрано количество бит на пиксель
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Попытаемся установить выбранный режим и получить резутьтаты.
		//К сведению: CDS_FULLSCREEN избавляется от стартбара.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// Если режиим не включился, предложим две возможности. Выйти или использовать оконный режим.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?"," GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Выбран оконный режим.
			}
			else
			{
				// Показать сообщение, что приложение закончило работу.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									
			}
		}
	}
	
	if (fullscreen)												// Мы в полноэкранном режиме?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Расширенный стиль окна
		dwStyle=WS_POPUP;										// Стиль окна
		ShowCursor(FALSE);										// Скрыть курсор мыши
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Расширенный стиль окна
		dwStyle=WS_OVERLAPPEDWINDOW;							// Стиль окна
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Подстроить окно, чтобы оно соответствовало требуемому размеру

	/* Создаем окно */
	hWnd=CreateWindowEx(dwExStyle,							// Расширенный стиль для окна
						"GLSample",							// Наименование класса
						title,								// Заголовок окна
						dwStyle |							// Определенный стиль окна
						WS_CLIPSIBLINGS |					// Требуемый стиль окна
						WS_CLIPCHILDREN,					// Требуемый стиль окна
						0, 0,								// Местоположение окна
						WindowRect.right-WindowRect.left,	// Вычисление ширины окна
						WindowRect.bottom-WindowRect.top,	// Вычисление высоты окна
						NULL,								// Нет родительского окна
						NULL,								// Нет меню
						hInstance,							// Instance
						NULL);								// Не посылать сообщение по WM_CREATE
	
    EnableOpenGL (hWnd, &hDC, &hRC);						// Включение OpenGL для окна
	
	slotmachine = new SlotMachine();    
	
    timeSetEvent(25, 0, cbFunct, NULL, TIME_PERIODIC);		//таймер для вызова вращения
    
    srand(time(NULL));
		
	ShowWindow(hWnd,SW_SHOW);						// Показать окно
	ReSizeGLScene(width, height);					// Устанавливаем наше GL окно с перспективой
	
	InitGL();										// Инициализируем наше GL окно
	return TRUE;									// Успешное завершение инициализациии
}


LRESULT CALLBACK WndProc(	HWND	hWnd,			// Указатель на окно
							UINT	message,		// Сообщение для этого окна
							WPARAM	wParam,			// Параметры сообщения
							LPARAM	lParam)			// Параметры сообщения
{
	switch (message)								// Проверим сообщения окна
	{
		case WM_ACTIVATE:							//Cообщение об активизации окна
		{
			if (!HIWORD(wParam))					// Проверим состояние минимизациии
			{
				active=TRUE;						// Программа активна
			}
			else
			{
				active=FALSE;						// Программа больше не активна
			}

			return 0;								// Вернуться к циклу сообщений
		}
		
		case WM_CLOSE:								// Мы получили сообщение о закрытии программы?
		{
			PostQuitMessage(0);						// Послать сообщение о выходе
			return 0;				
		}

		case WM_LBUTTONDOWN:						//Получи Левый клик мыши?
		{			
			return 0;				
		}

		case WM_KEYDOWN:							// Клавиша была нажата?
		{
			switch (wParam)
			{            
				case VK_ESCAPE:
					{
						PostQuitMessage(0);
						break;
					}
				default:
				slotmachine->roll();                      
				return 0;
			}
			keys[wParam] = TRUE;					// Если так – пометим это TRUE
			return 0;				
		}

		case WM_KEYUP:								// Клавиша была отпущена?
		{
			keys[wParam] = FALSE;					// Если так – пометим это FALSE
			return 0;				
		}

		case WM_SIZE:								// Изменились окна OpenGL
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));	// LoWord=ширина, HiWord=высота
			return 0;				
		}
	}
	/* Пересылаем все прочие сообщения в DefWindowProc */
	return DefWindowProc (hWnd, message, wParam, lParam);
}


int WINAPI WinMain(	HINSTANCE	hInstance,			// Экземпляр
					HINSTANCE	hPrevInstance,		// Предыдущий экземпляр
					LPSTR		lpCmdLine,			// Параметры командной строки			
					int			nCmdShow)			// Показать состояние окна
{
	MSG msg;					// Структура сообщения окна
	BOOL bQuit = FALSE;			// Булевская переменная выхода из цикла

	/* Запросим пользователя какой режим отображения он предпочитает */
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;				// Оконный режим
	}

	/* Создадим наше окно OpenGL */
	CreateGLWindow("Slot Machine", 640, 480, 16, fullscreen);
		
	/* Ocновной цикл программы */
	while(!bQuit)							
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Есть ожидаемое сообщение?
		{
			if (msg.message == WM_QUIT)					// Мы получили сообщение о выходе?
			{
				bQuit=TRUE;			
			}
			else									
			{
				TranslateMessage(&msg);					// Переводим сообщение
				DispatchMessage(&msg);					// Отсылаем сообщение
			}
		}
		else											// Cообщений нет?
		{
			/* Рисуем сцену. Ожидаем нажатия кнопки ESC и сообщения о выходе от DrawGLScene() */		
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	
			{
				bQuit=TRUE;				// ESC или DrawGLScene просигналили "выход"
			}
			else if (active)			// Не время выходить, обновляем экран
			{
				SwapBuffers(hDC);		// Переключаем буферы
			}
			
			if (keys[VK_F1])			// Была нажата кнопка F1?
			{
				keys[VK_F1]=FALSE;		// Если так - установим значение FALSE
				KillGLWindow();			// Закроем текущее окно OpenGL  
				fullscreen=!fullscreen;	// Переключим режим "Полный экран"/"Оконный"
				/* Заново создадим наше окно OpenGL*/
				CreateGLWindow("Slot Machine", 640, 480, 16, fullscreen);
			}		
		}
	}

	delete slotmachine;
	KillGLWindow();						// Закроем окно
	return (msg.wParam);				// Выйдем из программы
}

/* Enable OpenGL */

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
	PIXELFORMATDESCRIPTOR pfd;						// pfd сообщает Windows какие параметры мы хотим
	int PixelFormat;								// Содержит результаты подбора глубины цвета
	
	ZeroMemory (&pfd, sizeof (pfd));
	pfd.nSize = sizeof(pfd);						// Размер дескриптора формата пикселей
	pfd.nVersion = 1;								// Номер версии
	pfd.dwFlags =	PFD_DRAW_TO_WINDOW |			// Формат должен поддерживать окно
					PFD_SUPPORT_OPENGL |			// Формат должен поддерживать OpenGL
					PFD_DOUBLEBUFFER;				// Должна поддерживаться двойная буферизация
	pfd.iPixelType = PFD_TYPE_RGBA;					// Запрос RGBA формата
	pfd.cColorBits = 24;							// Выбор глубины цвета
	pfd.cDepthBits = 16;							// 16битный Z-бувер (Буфер глубины)  
	pfd.iLayerType = PFD_MAIN_PLANE;				// Главная плоскость рисования
	
	*hDC = GetDC (hWnd);							// Получаем device context (DC)
	PixelFormat = ChoosePixelFormat(*hDC,&pfd);		// Windows нашла соответствующий формат пикселя
	SetPixelFormat (*hDC, PixelFormat, &pfd);		// Установливаем формат пикселя
	
	*hRC = wglCreateContext( *hDC );				// Получаем render context (RC)
	wglMakeCurrent( *hDC, *hRC );					// Активируем render context (RC)
}

/* Disable OpenGL */

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent (NULL, NULL);					//Освободим RC и DC контексты
	wglDeleteContext (hRC);							//Удаляем RC
	ReleaseDC(hWnd,hDC);
}
















































































/*
float WinWidth = 400.0;
float WinHeight = 400.0;
float Angle = 0.0, Scale = 1.0;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	Scale = 1.0 - abs(sin(3.14*Angle/90.0)/sqrt(3.0)/2);
	glRotatef(Angle, 0.0, 0.0, 1.0);
	glScalef(Scale, Scale, 1.0);
	glBegin(GL_LINES);
		for(float i = -WinWidth/2; i <=WinWidth/2; i+=20.0)
		{
			glVertex2f(i, -WinHeight/2);
			glVertex2f(i, WinHeight/2);
		}
		for(float i = -WinWidth/2; i <=WinWidth/2; i+=20.0)
		{
			glVertex2f(-WinWidth/2, i);
			glVertex2f(WinWidth/2, i);
		}
	glEnd(); 
	glPopMatrix();
	glutSwapBuffers();
}

void Timer(int value)
{
	switch(value)
	{
	case 0: glColor3f(1.0, 1.0, 1.0);
		break;
	case 1: glColor3f(1.0, 0.0, 0.0);
		break;
	}
	//glRotatef(1, 0.0, 0.0, 1.0);
	++Angle;
	//Draw();
	glutPostRedisplay();
	glutTimerFunc(50, Timer, rand() % 2);
}

void Timer2(int)
{
	glColor3f(0.0, 1.0,0.0);
	glutPostRedisplay();
	glutTimerFunc(1000, Timer2, 0);
}
void  Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WinWidth/2, WinWidth/2, -WinHeight/2, WinHeight/2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(WinWidth, WinHeight);
	glutInitWindowPosition(100,200);
	glutCreateWindow("Fucking_Test3");
	glutDisplayFunc(Draw);
	glutTimerFunc(500, Timer, 0);
	glutTimerFunc(1000, Timer2, 0);
	Initialize();
	glutMainLoop();
	return 0;
}
*/