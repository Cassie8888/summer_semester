# -*- coding: cp936 -*-//字符集
import pygame,sys,os,random,time
pygame.init()#pygame库初始化
pygame.mixer.init()
pygame.time.delay(1000)#等待1秒让mixer完成初始化
soundwav=pygame.mixer.Sound("music.wav") 
soundwav.play()

running=True

class rect():#画出小人
    def __init__(self,filename,initial_position):
        self.image=pygame.image.load(filename)
        self.rect=self.image.get_rect()
        self.rect.topleft=initial_position
        
class firstrect(pygame.sprite.Sprite):#绘出浆果1
    def __init__(self,first_position,speed1):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image\\Pecha-1.png')
        self.rect=self.image.get_rect()
        self.rect.topleft=first_position
        self.speed=speed1
    def move(self):
        self.rect=self.rect.move(self.speed)

class secondrect(pygame.sprite.Sprite):#绘出浆果2
    def __init__(self,second_position,speed2):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image\\Liechi-2.png')
        self.rect=self.image.get_rect()
        self.rect.topleft=second_position
        self.speed=speed2
    def move(self):   
        self.rect=self.rect.move(self.speed)
        
class thirdrect(pygame.sprite.Sprite):#绘出浆果3
    def __init__(self,third_position,speed3):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image\\Pamtre-3.png')
        self.rect=self.image.get_rect()
        self.rect.topleft=third_position
        self.speed=speed3
    def move(self):   
        self.rect=self.rect.move(self.speed)
        
class fourthrect(pygame.sprite.Sprite):#绘出浆果4
    def __init__(self,fourth_position,speed4):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image\\Sitrus-4.png')
        self.rect=self.image.get_rect()
        self.rect.topleft=fourth_position
        self.speed=speed4
    def move(self):   
        self.rect=self.rect.move(self.speed)
                
class bombrect(pygame.sprite.Sprite):#绘出浆果4
    def __init__(self,bomb_position,speed5):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image\\bomb.png')
        self.rect=self.image.get_rect()
        self.rect.topleft=bomb_position
        self.speed=speed5
    def move(self):   
        self.rect=self.rect.move(self.speed)
                
def drawback(): #绘出背景图片
    my_back=pygame.image.load('image\\pi1.png') 
    bakscreen.blit(my_back,[0,0])

def loadtext(levelnum,score):#绘出成绩、level
    my_font=pygame.font.SysFont(None,40)
    levelstr='Level:'+str(levelnum)
    text_screen=my_font.render(levelstr, True, (255, 0, 0))
    bakscreen.blit(text_screen, (800,50))
    scorestr='Score:'+str(score)
    text_screen=my_font.render(scorestr, True, (255, 0, 0))
    bakscreen.blit(text_screen, (800,80))    

def loadgameover(scorenum):#绘出GAME OVER
    my_font=pygame.font.SysFont(None,50)
    levelstr='GAME OVER'
    over_screen=my_font.render(levelstr, True, (255, 0, 0))
    bakscreen.blit(over_screen, (300,240))
    highscorestr='YOUR SCORE IS '+str(scorenum)
    over_screen=my_font.render(highscorestr, True, (255, 0, 0))
    bakscreen.blit(over_screen, (280,290))
     
bakscreen=pygame.display.set_mode([1024,614])
bakscreen.fill([0,160,233])
pygame.display.set_caption('Dare it!')

drawback()

levelnum=1 #level
scorenum=0 #得分
ileft=1  #记录向左移动步数，用来控制图片
iright=10 #记录向右移动步数，用来控制图片
x=100
y=450
filename='image\\1.png'
backimg_ren=rect(filename,[x,y])
bakscreen.blit(backimg_ren.image,backimg_ren.rect)
loadtext(levelnum,scorenum)

firstx=random.randint(50,980)
secondx=random.randint(50,980)
thirdx=random.randint(50,980)
fourthx=random.randint(50,980)
bombx=random.randint(50,980)

speed1=[0,levelnum]
speed2=[0,levelnum*1.5]
speed3=[0,levelnum*2]
speed4=[0,levelnum*3]
speed5=[0,levelnum*2.5]

myfirst=firstrect([firstx,100],speed1) 
mysecond=secondrect([secondx,100],speed2)
mythird=thirdrect([thirdx,100],speed3)
myfourth=fourthrect([fourthx,100],speed4)
mybomb=bombrect([bombx,100],speed5)
pygame.display.update()

while running:
    if scorenum>0:#当得分是50的倍数时修改level
        levelnum=int(scorenum/50)+1
        speed1=[0,levelnum]
        speed2=[0,levelnum*1.5]
        speed3=[0,levelnum*2]
        speed4=[0,levelnum*3]
        speed5=[0,levelnum*2.5]
    
    for event in pygame.event.get():
        if event.type==pygame.QUIT:
            sys.exit()
    #make gold    

    pressed_keys = pygame.key.get_pressed()
    if pressed_keys[pygame.K_LEFT]:#按下左键

        drawback()  
        loadtext(levelnum,scorenum)

        if iright > 12 :iright=10
        iright=iright+1
        filename='image\\'+str(iright)+'.png'
        if x<50 :
            x=50
        else:
            x=x-20

        backimg_surface=rect(filename,[x,y])
        bakscreen.blit(backimg_surface.image,backimg_surface.rect)

        
    if pressed_keys[pygame.K_RIGHT]:#按下右键

        drawback()
        loadtext(levelnum,scorenum)

        if ileft > 2 :ileft=0
        ileft=ileft+1
        filename='image\\'+str(ileft)+'.png'
        if x>980:
            x=980
        else:
            x=x+20

        backimg_surface=rect(filename,[x,y])
        bakscreen.blit(backimg_surface.image,backimg_surface.rect)

    drawback()
    loadtext(levelnum,scorenum)
    
    myfirst.move()
    mysecond.move()
    mythird.move()
    myfourth.move()
    mybomb.move()
    
    bakscreen.blit(myfirst.image,myfirst.rect) 
    bakscreen.blit(mysecond.image,mysecond.rect)
    bakscreen.blit(mythird.image,mythird.rect)
    bakscreen.blit(myfourth.image,myfourth.rect)
    bakscreen.blit(mybomb.image,mybomb.rect)
    
    backimg_surface=rect(filename,[x,y])
    bakscreen.blit(backimg_surface.image,backimg_surface.rect)
    
    if myfirst.rect.top>500:#判断浆果是否着地，一但着地，游戏结束
        loadgameover(scorenum)
        
    if mysecond.rect.top>500:
        loadgameover(scorenum) 
        
    if mythird.rect.top>500:
        loadgameover(scorenum) 
        
    if myfourth.rect.top>500:
        loadgameover(scorenum)
                
         
    if myfirst.rect.colliderect(backimg_surface.rect):#判断浆果是否与小人碰撞，如果碰撞表示小人接到金币
        scorenum+=5
        loadtext(levelnum,scorenum)
        firstx=random.randint(50,980)
        myfirst=firstrect([firstx,100],speed1) 
        
    if mysecond.rect.colliderect(backimg_surface.rect):
        scorenum+=10
        loadtext(levelnum,scorenum)  
        secondx=random.randint(50,980)
        mysecond=secondrect([secondx,100],speed2)  
        
    if mythird.rect.colliderect(backimg_surface.rect):
        scorenum+=15
        loadtext(levelnum,scorenum)  
        thirdx=random.randint(50,980)
        mythird=thirdrect([thirdx,100],speed3)
          
    if myfourth.rect.colliderect(backimg_surface.rect):
        scorenum+=20
        loadtext(levelnum,scorenum)  
        fourthx=random.randint(50,980)
        myfourth=fourthrect([fourthx,100],speed4) 
        
    if mybomb.rect.colliderect(backimg_surface.rect):
        scorenum-=15
        loadtext(levelnum,scorenum)  
        bombx=random.randint(50,980)
        mybomb=bombrect([bombx,100],speed5)    
          
    pygame.display.update()
    
    
    
    
    
    
    
    
    
    
    
    