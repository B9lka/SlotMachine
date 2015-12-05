#define _USE_MATH_DEFINES

#include <math.h>


class Reel 
{
    // ѕор€док значков на барабане
    char permutation[8]; //перемещение
    
    
    // ¬озвращение случайного числа между start и end включительно
    int randominclusive(int start, int end)
    {
        int randnum = rand()%(end-start+1);
        return (randnum+start);
    }
    
    
    // ѕеремешаем массив случайным образом 
    template <class T> void shuffle(T myarray[], int N)
    {
        int thesize = N-1;
        
        for (int x = 0; x < thesize; x++)
        {
            // √енерируем случайное число между X и thesize включительно
            int i = randominclusive(x, thesize);
            int temp = myarray[x];
            
            myarray[x] = myarray[i];
            myarray[i] = temp;
        }
        
    }       
    
    
    float getYtexture(float initialy) //первоначально
    {    
        int index = int(initialy*8.0);      
        float fraction = initialy*8.0 - float(index);
        int newoffset = permutation[index]; //перемещение
        float newy = (fraction+newoffset)/8.0;
        return newy;
    }
    
    
    public:    
    
    
    Reel(void)
    {
        for (int ctr = 0; ctr < 8; ctr++) permutation[ctr] = ctr;
        shuffle(permutation, 8);        
    }
    
    
    void drawreel(void) //рисуем барабан
    {
        float increment = 0.03;
        glBegin(GL_QUADS);
        for (float angle = 0; angle < 2*M_PI; angle+=increment)
        {
            float y = sin(angle);
            float z = cos(angle);
            
            float texturey = 1.0 - angle/(2*M_PI);
            
            texturey = getYtexture(texturey);
            
            glTexCoord2f(0, texturey);
            glNormal3f(0, y, z);
            glVertex3f(-0.39, y, z);    
            glTexCoord2f(1, texturey);
            glNormal3f(0, y, z);
            glVertex3f(0.39, y, z);    
            
            float nexty = sin(angle+increment);
            float nextz = cos(angle+increment);
            
            texturey = texturey-increment/(2*M_PI);
            
            glTexCoord2f(1, texturey);
            glNormal3f(0, nexty, nextz);
            glVertex3f(0.39, nexty, nextz);    
            glTexCoord2f(0, texturey);
            glNormal3f(0, nexty, nextz);
            glVertex3f(-0.39, nexty, nextz);                            
        }
        glEnd();        
    }
    
    int getvalue(float angindegrees)
    {
        int index = int(angindegrees)%360;
        index/=45;  
        index = (7 - index + 1)%8;  
        return permutation[index];    
    }
    
};
