# include "iGraphics.h"
#include "bitmap_loader.h"


#define ScreenHeight 1000
#define ScreenWidth 600
#define doctor_Speed 10
#define Num_Of_eVirus 3

int image_x=450;
int image_y=390;

int music=1;

int Medkit;
double medkit_Speed = 5;
int med_x= ScreenHeight+50;
int med_y=60;
int size_dx = 60;
int size_dy = 60;
bool med_Show=true;

char str[100], str2[100];
int len=0;
int mode=0;


int score = 0;
char score_1[20];
char score_2[20];

int bullet;
int Bullet_x[10];
int Bullet_y[10];
int Bullet_Speed=3;
bool Bullet[10]={false,false,false,false,false,false,false,false,false,false};

int life[3];
bool Life[3]={true,true,true};
int life_index=0;

int Bg[5];
char highscore1[10];
int menubar[6];

int EVirus[3];
int EVirusOne,EVirusTwo,EVirusThree;
int eVirus_x=950;
int eVirus_y=90;
double eVirus_Speed = 5;

int chara[3];
int storymode[6];
int index=0;
int screen=0;



int about;
int over;
int Exit;
int yes;

int flag=0;

//highscore input
void drawTextBox()
{
	iSetColor(250, 250, 250);
	iText(390,480,"Enter Your Name:",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(150, 150, 150);
	iRectangle(580, 470, 200, 30);
}

//Doctor all 
struct doctor
{
	int doctor_x;
    int doctor_y;
	int Size_dx ;
	int Size_dy ;
	int Image;
	doctor()
	{
		 doctor_x=0;
         doctor_y=0;
	     Size_dx = 90;
	     Size_dy = 110;
	}
};
doctor d;



void medchange()
{
	if(flag==2)
	{
		med_x -= medkit_Speed;
		if (med_x <= 0)
	     {
			med_x = ScreenWidth + rand() % ScreenWidth - size_dx;
			med_y = 60 + rand() % 400;
		 }
    }
	
}

void medspeed()
{
	medkit_Speed=medkit_Speed+0.1;
}



void medkit_collision()
{
		if(med_Show=true && d.doctor_x+50>=med_x && d.doctor_x<=med_x+size_dx &&  d.doctor_y+d.Size_dy>=med_y && d.doctor_y<=med_y+size_dy)
            {
				PlaySound("music\\medkit.wav",NULL,SND_ASYNC);
                 med_x= ScreenHeight+50;
                 med_y=60 +rand() % 400;
           
				 Life[life_index]=true;

				if(life_index<0)
						life_index=0;
				life_index --;
			
				
            }
 
}


//eVirus all
struct eVirus
{
	int Position_x;
	int Position_y;
	int Size_dx ;
	int Size_dy ;
	int image;
	int index;
	bool eVirus_Show;
	eVirus()

	{
		Size_dx = 60;
        Size_dy = 60;
		index = 0;
	   eVirus_Show = true;
	}

}evirus[Num_Of_eVirus];


 void MovementOfeVirus()
{
	for (int i = 0; i < 3; i++)
	{
		if (evirus[i].eVirus_Show)
		{
			iShowImage(evirus[i].Position_x, evirus[i].Position_y, evirus[i].Size_dx, evirus[i].Size_dy, evirus[i].image);
	
		}
	}
}

 //eVirus position set
 void Set_eVirus()
{


	evirus[0].Position_x = ScreenHeight + evirus[0].Size_dx;
	evirus[0].Position_y = 40;
	evirus[0].Size_dx = evirus[0].Size_dx;
	evirus[1].Position_x = ScreenHeight + evirus[1].Size_dx;
	evirus[1].Position_y = 185;
	evirus[2].Position_x = ScreenHeight + evirus[2].Size_dx;
	evirus[2].Position_y = 350;


}



 void change()
{
	if( flag==2)
	{
	evirus[0].Position_x -= eVirus_Speed;
	if (evirus[0].Position_x <= 0)
	{
		evirus[0].Position_x = ScreenWidth + rand() % ScreenWidth - evirus[0].Size_dx;
		evirus[0].Position_y = 40 + rand() % 70;
		evirus[0].image = EVirus[rand()%3];
	}
	evirus[1].Position_x -= eVirus_Speed;
	if (evirus[1].Position_x <= 0)
	{
		evirus[1].Position_x = ScreenWidth + rand() % ScreenWidth - evirus[1].Size_dx;
		evirus[1].Position_y = 185 + rand() % 70;
		evirus[1].image = EVirus[rand()%3];
	
	}
	evirus[2].Position_x -= eVirus_Speed;
	if (evirus[2].Position_x <= 0)
	{
		evirus[2].Position_x = ScreenWidth + rand() % ScreenWidth - evirus[2].Size_dx;
		evirus[2].Position_y = 350 + rand() % 70;
		evirus[2].image = EVirus[rand()%3];
	
	}
	}

}

void Increasing_Speed()
{
	eVirus_Speed=eVirus_Speed+0.05;

	if(score_1[0] >=1 && score_1[0]> 0)
		eVirus_Speed=eVirus_Speed+0.5;
	if(score_1[0] >=2 && score_1[0]> 0)
		eVirus_Speed=eVirus_Speed+1;

}




//Collision between evirus and bullet
void Collision()
{
    for(int i=0;i<10;i++)
    {  
        for(int j=0;j<3;j++)
        {
            if(Bullet[i]==true && Bullet_x[i]>=evirus[j].Position_x && Bullet_x[i]<=evirus[j].Position_x+10 && Bullet_y[i]>=evirus[j].Position_y && Bullet_y[i]<=evirus[j].Position_y+evirus[j].Size_dy)
			{
				PlaySound("music\\col.wav", NULL,SND_ASYNC);
				score++;
                evirus[j].eVirus_Show= false;
                evirus[j].Position_x = ScreenWidth + rand() % ScreenWidth - evirus[i].Size_dx;
                Bullet[i]=false;
				Bullet_x[i] = d.doctor_x + d.Size_dx;
				Bullet_y[i] = d.doctor_y + d.Size_dy;
				sprintf(score_1,"%d",score);
			}
		}
	}
	FILE *f3=fopen("High_Score.txt","r");
	fscanf(f3,"%s",score_2);
	fclose(f3);
	if(score_1>score_2)
	{
		FILE *f1=fopen("High_Score.txt","w");
		fprintf(f1,"%s",score_1);
		fclose(f1);
	}
	else
		FILE *f3=fopen("High_Score.txt","w");
		fprintf(f3,"%s",score_2);
		fclose(f3);
                
	
}



//Collision between doctor and evirus
void doctor_collision()
{
     
        for(int j=0;j<3;j++)
        {
            if(evirus[j].eVirus_Show==true) 
				if(d.doctor_x+50>=evirus[j].Position_x && d.doctor_x<=evirus[j].Position_x+evirus[j].Size_dx &&  d.doctor_y+d.Size_dy>=evirus[j].Position_y && d.doctor_y<=evirus[j].Position_y+evirus[j].Size_dy)
            {
				PlaySound("music\\col.wav", NULL,SND_ASYNC);
                evirus[j].eVirus_Show= false;
				Life[life_index]=false;
                life_index++;
               // printf("collided with hero %d %d\n",j,life_index);
          

            }
 
        }
 
}


//after Collision bring back the evirus in the screen
void eVirus_True()
    {
       for(int i=0;i<3;i++)
 
        {  
			if(evirus[i].eVirus_Show==false)
 
           {
            evirus[i].eVirus_Show=true;
            evirus[i].Position_x =ScreenWidth + rand() % ScreenWidth - evirus[i].Size_dx;
            if(i==0)
                evirus[i].Position_y = 35 + rand() % 70;
            else if(i==1 )
                evirus[i].Position_y = 185 + rand() % 70;
            else if(i==2)
                evirus[i].Position_y = 350 + rand() % 70;

				evirus[i].image = EVirus[rand()%3];
	
           }
			
        }
    }








void iDraw()
{
   iClear();

   if(flag==0)
   {

		iShowImage(0,0,ScreenHeight,ScreenWidth,Bg[0]);
		iSetColor(0,0,0);
		iRectangle(95,35,200,25);
		iText(100,40,"Press LMB to Start", GLUT_BITMAP_TIMES_ROMAN_24); 

   }

   if(flag==1)
   {
	    iShowImage(0,0,ScreenHeight,ScreenWidth,Bg[1]);

		iShowImage(image_x,image_y,100,50,menubar[0]);
		iShowImage(image_x+5,image_y-80,100,50,menubar[1]);
		iShowImage(image_x+5,image_y-160,100,50,menubar[2]);
		iShowImage(image_x+5,image_y-240,100,50,menubar[3]);
		iShowImage(image_x+5,image_y-320,100,50,menubar[4]);
		iShowImage(image_x+5,image_y+80,100,50,menubar[5]);

   }

   if(flag==2)
   {
	   iShowImage(0,0,ScreenHeight,ScreenWidth,Bg[2]);
	     iSetColor(255,255,255);
	   iFilledRectangle(490,540,150,40);
	   iFilledRectangle(815,540,150,40);
	     iSetColor(0,0,0);
	   iRectangle(490,540,150,40);
	   iRectangle(815,540,150,40);
	   
	   iShowImage(d.doctor_x,d.doctor_y,d.Size_dx,d.Size_dy,chara[0]);

	   iShowImage(med_x,med_y,size_dx,size_dy,Medkit);

	   iText(200,10,"Press 'p' to pause game, 'r' to resume game & 'b' to homepage");
       iText(830,555,"Score:",GLUT_BITMAP_TIMES_ROMAN_24);
	   iText(910,555,score_1,GLUT_BITMAP_TIMES_ROMAN_24);

		if(Life[0]==true)
		iShowImage(495,545,40,30,life[0]);
		if(Life[1]==true)
		iShowImage(545,545,40,30,life[1]);
		if(Life[2]==true)
		iShowImage(595,545,40,30,life[2]);
		if(life_index == 3)
		{
			for(int i=0; i<3; i++)
			evirus[i].eVirus_Show= false;
			iShowImage(0,0,ScreenHeight,ScreenWidth,over);
			iSetColor(255,255,255);
			iText(390,530,"Your Score:",GLUT_BITMAP_TIMES_ROMAN_24);
			iText(550,530,score_1,GLUT_BITMAP_TIMES_ROMAN_24);

			drawTextBox();
			if(mode == 1)
			{
				iSetColor(255, 255, 255);
				iText(605, 485, str);
				iText(400, 5, "Click to activate the box, Press 'k' and 'b' to finish.");
			}

		}
		

	   for (int i = 0; i < 10; i++)
       { 
		   if (Bullet[i] == true)
            {
			iShowImage(Bullet_x[i], Bullet_y[i],30,30,bullet);
            Bullet_x[i] += Bullet_Speed;
            if(Bullet_x[i]>= ScreenHeight)
               Bullet[i]=false;
           
            }
	   }

	  for(int i=0;i<3;i++)
       {
           if(evirus[i].eVirus_Show==true)
		   {
			    Collision();
		   }
          
       }
	      
            MovementOfeVirus();
			medkit_collision();
			doctor_collision();
		    

			
   }

    if(flag==3)
   {

	    iShowImage(0,0,ScreenHeight,ScreenWidth,Bg[3]);


        FILE *f2=fopen("High_Score.txt","r");
        fscanf(f2,"%s",score_1);
	
		//FILE *f4=fopen("High_Scorer_Name.txt","r");
        //fscanf(f4,"%s",str2);

		iSetColor(0,0,0);
		iText(340,180,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(337,170,"-----",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(340,140,str2,GLUT_BITMAP_TIMES_ROMAN_24);

		iText(650,180,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(647,170,"-----",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(650,140,score_1,GLUT_BITMAP_TIMES_ROMAN_24);
        fclose(f2);
	    

   }
	 if(flag==4)
   {
	   iShowImage(0,0,ScreenHeight,ScreenWidth,Bg[4]);
	   

   }
	 if(flag==5)
   {
	   iShowImage(0,0,ScreenHeight,ScreenWidth,about);
   }
	  if(flag==6)
   {
	   
	  iShowImage(0,0,ScreenHeight,ScreenWidth,Exit);
	  iShowImage(485,15,45,25,yes);


   }
	  //story mode
	  if(flag==7)
   {
	   iSetColor(255,255,255);
	  
	    if (screen==0)
		{
		    iShowImage(0,0,ScreenHeight,ScreenWidth,storymode[0]);
			iRectangle(95,25,315,20);
		    iText(100,30,"Press '1' to See the Moral of the game");
		}
	    else if (screen==1)
		{
	        iShowImage(0,0,ScreenHeight,ScreenWidth,storymode[1]);
			iSetColor(0,0,0);
			iRectangle(363,10,207,20);
		    iText(368,15,"Press '2' to See the Next");
		}
		else if (screen==2)
		{
		   iShowImage(0,0,ScreenHeight,ScreenWidth,storymode[2]);
		    iSetColor(0,0,0);
			iRectangle(363,10,207,20);
		    iText(368,15,"Press '3' to See the Next");
		}
		else if (screen==3)
		{
	        iShowImage(0,0,ScreenHeight,ScreenWidth,storymode[3]);
			iSetColor(0,0,0);
			iRectangle(363,10,207,20);
		    iText(368,15,"Press '4' to See the Next");
		}
		else if (screen==4)
		{
	        iShowImage(0,0,ScreenHeight,ScreenWidth,storymode[4]);
			iSetColor(0,0,0);
			iRectangle(363,10,207,20);
		    iText(368,15,"Press '5' to See the Next");
		}
		else if (screen==5)
		{
	        iShowImage(0,0,ScreenHeight,ScreenWidth,storymode[5]);
			iSetColor(0,0,0);
			iRectangle(363,10,370,20);
		    iText(368,15,"Again See To Press '1',Homepage To Press 'b'");
		}
		 
	  

   }

	
}

void iMouseMove(int mx, int my)
{
	
}


void iPassiveMouse(int mx, int my)
{
	
}


void iMouse(int button, int state, int mx, int my)
{
	    if(flag==0)
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			  if( mx>=0 && mx<=ScreenHeight && my>=0 && my<=ScreenWidth)
					 {
						//PlaySound("music\\intro.wav", NULL, SND_LOOP | SND_ASYNC);
						 flag=1;
			         }
		}

		if(flag==1)
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			  if( mx>=450 && mx<=550 && my>=390 && my<=440)
					 flag=2;
			  if( mx>=450 && mx<=550 && my>=315 && my<=365)
					 flag=3;
			  if( mx>=450 && mx<=550 && my>=235 && my<=285)
					 flag=4;
			  if( mx>=450 && mx<=550 && my>=155 && my<=205)
					 flag=5;
			  if( mx>=440 && mx<=546 && my>=80 && my<=130)
				     flag=6;
			  if( mx>=450 && mx<=550 && my>=470 && my<=520)
					 flag=7;

			 
		}

		if(flag==2)
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
		
			if(mx >= 600 && mx <= 800 && my >= 480 && my <= 510 && mode == 0)
			{
				mode = 1;
			}
		}

		if(flag==6)
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			  if( mx>=485 && mx<=530 && my>=20 && my<=40)
					 exit(0);
		}


		printf("%d %d \n",mx,my);


		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			//PlaySound("music\\gun.wav", NULL,SND_ASYNC);
			if (index == 10)
        {
            
            index = 0;
            Bullet[index] = true;
			Bullet_x[index] = d.doctor_x + d.Size_dx;
			Bullet_y[index] = d.doctor_y + 60;
            index++;
        }

        else
        {
            Bullet[index]= true;
			Bullet_x[index] = d.doctor_x + d.Size_dx;
			Bullet_y[index] = d.doctor_y + 60;
            index++;
 
        }

			
  }
}


void iKeyboard(unsigned char key)
{

	if(key == 'w')
	{

		if (d.doctor_y >= 440)
		     d.doctor_y = 440;
		else
		     d.doctor_y +=doctor_Speed;
	}
	else if(key == 's')
	{
			
		if (d.doctor_y <= 2)
		    d.doctor_y = 2;
		else
		     d.doctor_y -=doctor_Speed;
	}

	else if(key == 'a')
	{

		if(d.doctor_x <= 2)
		     d.doctor_x =2;
		else
		     d.doctor_x -=doctor_Speed;
	}
	else if(key == 'd')
	{
		if (d.doctor_x >= 335)
		     d.doctor_x =335;
		else
		     d.doctor_x +=doctor_Speed;
	}
	if(key == 'b')
	{
	  flag=1;
	}


	if(key == '1')
	{
	  screen=1;
		
	}
	if(key == '2')
	{
	  screen=2;
		
	}
	if(key == '3')
	{
	  screen=3;
		
	}
	if(key == '4')
	{
	  screen=4;
		
	}
	if(key == '5')
	{
	  screen=5;
		
	}

	if(key == 'p')
	{
	
		iPauseTimer(0);
	}

	if(key == 'r')
	{
		iResumeTimer(0);
	}

	
	if(mode == 1)
	{
        if(key == '\k')
		{
			mode = 0;
			strcpy(str2, str);
			printf("%s\n", str2);
			for(int i = 0; i < len; i++)
				str[i] = 0;
			    len = 0;
		}
		else
		{
			str[len] = key;
			len++;
		}

		FILE *f4=fopen("High_Scorer_Name.txt","r");
	    fscanf(f4,"%s",str2);
	    fclose(f4);
	
		FILE *f4=fopen("High_Scorer_Name.txt","w");
		fprintf(f4,"%s",str2);
		fclose(f4);

	}
	
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{
	
	if(key == GLUT_KEY_UP)
	{

		if (d.doctor_y >= 440)
		     d.doctor_y = 440;
		else
		     d.doctor_y +=doctor_Speed;
	}
	else if(key == GLUT_KEY_DOWN)
	{
			
		if (d.doctor_y <= 2)
		     d.doctor_y = 2;
		else
		    d.doctor_y -=doctor_Speed;
	}
	else if(key == GLUT_KEY_LEFT)
	{

		if(d.doctor_x <= 2)
		     d.doctor_x =2;
		else
		     d.doctor_x -=doctor_Speed;

	}
	else if(key == GLUT_KEY_RIGHT)
	{
		if (d.doctor_x >= 335)
		     d.doctor_x =335;
		else
		     d.doctor_x +=doctor_Speed;
	
	}

	
	
}




int main()
{
	srand(time(NULL));
    Set_eVirus();
	iSetTimer(25,change);
    iSetTimer(1000,eVirus_True);
	iSetTimer(5000,Increasing_Speed);

	iSetTimer(20,medchange);
	iSetTimer(3000,medspeed);
	 


	//if(music==1)
	//PlaySound("music\\intro2.wav", NULL, SND_LOOP | SND_ASYNC);



	iInitialize(ScreenHeight,ScreenWidth,"Captain White Apron");

	Bg[0]=iLoadImage("images//opening.png");
	Bg[1]=iLoadImage("images//bg.jpg");
	Bg[2]=iLoadImage("images//gamebg.png");
	Bg[3]=iLoadImage("images//highs.jpg");
	Bg[4]=iLoadImage("images//htp.jpg");


	menubar[0]=iLoadImage("images//menubar.png");
	menubar[1]=iLoadImage("images//highscore.png");
	menubar[2]=iLoadImage("images//menubar3.png");
	menubar[3]=iLoadImage("images//menubar4.png");
	menubar[4]=iLoadImage("images//menubar5.png");
	menubar[5]=iLoadImage("images//menubar6.png");

	storymode[0]=iLoadImage("story//s.jpg");
    storymode[1]=iLoadImage("story//s1.png");
	storymode[2]=iLoadImage("story//s2.png");
	storymode[3]=iLoadImage("story//s3.png");
    storymode[4]=iLoadImage("story//s4.png");
	storymode[5]=iLoadImage("story//s5.png");
	
	

	chara[0]=iLoadImage("images//2.png");

	EVirusOne=iLoadImage("images//eVirus.png");
	EVirusTwo=iLoadImage("images//eVirus.png");
	EVirusThree=iLoadImage("images//eVirus.png");

	EVirus[0]=EVirusOne;
	EVirus[1]=EVirusTwo;
	EVirus[2]=EVirusThree;

	

	for(int i=0;i<3;i++)
		evirus[i].image=EVirus[rand() % 3];

	life[0]=iLoadImage("images//life.png");
	life[1]=iLoadImage("images//life.png");
	life[2]=iLoadImage("images//life.png");


	bullet=iLoadImage("images//bullet.png");

	about=iLoadImage("images//about.png");

	over=iLoadImage("images//over.png");
	str[0]= 0;

	Exit=iLoadImage("images//exit.jpg");
	yes=iLoadImage("images//yes.png");

	Medkit=iLoadImage("images//medkit.png");


	iStart();

	return 0;
}

