//#include "Button.h"

class SlotMachine
{	
	Reel r[5];			//катушка отдельный класс
    int velocities[5];	//cкорость
    int positions[5];    
    int money;
    int lastwin;
    UINT TextureArray[6];

    bool ismoving(void)
    {
        return (velocities[0] ||
        velocities[1] ||
        velocities[2] ||
        velocities[3] ||
        velocities[4]);                
    }
   
    public:
    
    void physicsproc(void) //физика вращения
    {                                               
        bool ismovingatstart = ismoving();        
        
        for (int ctr = 0; ctr < 5; ctr++)
        {            
            positions[ctr]+=min(velocities[ctr], 10+5-ctr);

            // Если предыдущая катушка не остановилась, давайте не замедлять эту
            if (ctr > 0 && velocities[ctr-1]>0) continue;    
            
            velocities[ctr]--;
            if (velocities[ctr] < 0) velocities[ctr]=0;   
            
            
            if (velocities[ctr] != 9 || !(positions[ctr]%45)) continue;
            // Если скорость = 8 и позиция не кратна 45,
			// Тогда давайте двигать позицию, пока она не будет кратна
			// 45 градусам
            
			// Заметьте, что сумма чисел от 1 до 9 = 45.
			// Так, если скорость 9, и мы кратны 45 градусов
			// Тогда мы в конечном счете завершим кратность на 45 градусов.
            velocities[ctr]=10;
            if (rand()%5==0) positions[ctr]++;                        
        }                
    }
    
    
    SlotMachine(void)
    {
        Load_Texture( TextureArray[0], "../data/texture/thereel1.jpg");        
        Load_Texture( TextureArray[1], "../data/texture/background1.jpg");        
        Load_Texture( TextureArray[2], "../data/texture/startEna.bmp");
		Load_Texture( TextureArray[3], "../data/texture/startDis.bmp");
		Load_Texture( TextureArray[4], "../data/texture/selectEna.bmp");
		Load_Texture( TextureArray[5], "../data/texture/selectDis.bmp");
        
		memset(positions, 0, sizeof(int)*5);
        memset(velocities, 0, sizeof(int)*5);
	}
    
    ~SlotMachine(void)
    {
    }

    // вращение барабанов
    void roll(void)
	{
        if (ismoving()) return;
    
        
        for (int ctr = 0; ctr < 5; ctr++) 
        velocities[ctr] = rand()%10+10;
    }
    
    
    void draw(void)
    {
        glDisable(GL_LIGHTING);  
        glDisable(GL_DEPTH_TEST);                                                  
        glDepthMask(GL_FALSE);
        glTranslatef(0, 0, -1);
        
        float xdist = .77;
        float ydist = .58;
        
        glColor3f(1, 1, 1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureArray[1]); //cвязываем фон, с фоновой текстурой 
        // background 
        glBegin(GL_QUADS); //рисуем квадрат
        glTexCoord2f(0, 0); glVertex2f(-xdist, ydist);
        glTexCoord2f(1, 0); glVertex2f(xdist, ydist);
        glTexCoord2f(1, 1); glVertex2f(xdist, -ydist);
        glTexCoord2f(0, 1); glVertex2f(-xdist, -ydist);
        glEnd();

        /* ЗДЕСЬ ДОЛЖНА БЫЛА БЫТЬ РИСОВАЛКА КНОПОК
		Button *button;
		button = new Button(_start,_enabled);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, TextureArray[2]);
		button->drawbutton(); 
		*/

    	glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);  
        
        glTranslatef(0, 0, -3.5);
        glBindTexture(GL_TEXTURE_2D, TextureArray[0]);        
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);                    
        
        glTranslatef(-2.4, 0, 0);        
        
        // center the reel faces        
        glRotatef (-22.5, 1.0f, 0.0f, 0.0f);        
        
        for (int ctr = 0; ctr < 5; ctr++)
        {                                    
            glTranslatef(.8, 0, 0);
            glPushMatrix();
            glRotatef (positions[ctr], 1.0f, 0.0f, 0.0f);
            r[ctr].drawreel();    
            glPopMatrix();            
        }           
        glDisable(GL_CULL_FACE);                                  
    }
    
    
    
};
