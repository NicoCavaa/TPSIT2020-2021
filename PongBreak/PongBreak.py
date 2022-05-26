from re import L, X
import sys, pygame, random
from typing import ByteString
import serial, time
import threading, queue
import time
import keyboard



q = queue.Queue()
#inizializzo variabili per la grafica
GAME_OVER = pygame.image.load('gameOver.png')
GAME_OVER = pygame.transform.scale(GAME_OVER,(350, 350))
WIN = pygame.image.load('vittoria.png')
WIN = pygame.transform.scale(WIN ,(380, 327))
SFONDO_MENU = pygame.image.load('background.png')
SFONDO_MENU = pygame.transform.scale(SFONDO_MENU,(640,480))

#parte dei thread
class Read_Microbit(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self._running = True
      
    def terminate(self):
        self._running = False
        
    def run(self):
        #serial config
        port = "COM10"
        s = serial.Serial(port)
        s.baudrate = 115200
        while self._running:
            data = s.readline().decode() 
            acc = [float(x) for x in data[1:-3].split(",")]
            q.put(acc)
            time.sleep(0.01)

#classe per il muro composto da mattoncini
class Wall():

    def __init__(self):
        #carico immagine mattone
        self.brick = pygame.image.load("brick.png")   
        brickrect = self.brick.get_rect()
        #lunghezza e altezza del mattone
        self.bricklength = brickrect.right - brickrect.left       
        self.brickheight = brickrect.bottom - brickrect.top             
    #funzione per la costruzione del muro
    def build_wall(self, width):        
        xpos = 0
        ypos = 60
        k = 0
        self.brickrect = []
        #52 è il numero dei mattoncini che compongono il muro
        for i in range (0, 52):           
            if xpos > width:
                if k == 0:
                    k = self.bricklength / 2#impostazione sfalsata
                else:
                    k = 0
                xpos = -k
                ypos += self.brickheight
                
            self.brickrect.append(self.brick.get_rect())    
            self.brickrect[i] = self.brickrect[i].move(xpos, ypos)
            xpos = xpos + self.bricklength


def main():
    
    #inizializzo variabili per la bara, punteggio 
    xspeed = 4
    yspeed = 4
    max_lives = 5
    bat_speed = 10
    score = 0 
    bgcolour = 13, 124, 112
    txtcolour = 9, 9, 9
    
    size = width, height = 640, 480

    pygame.init()            
    screen = pygame.display.set_mode(size) #per finestra
    #screen = pygame.display.set_mode(size, pygame.FULLSCREEN)#per gioco in fullscreen
    #carica l'immagine della paletta
    bat = pygame.image.load("bat.png")        
    batrect = bat.get_rect()
    #carica l'immagine della pallina
    ball = pygame.image.load("ball.png")      
    ball.set_colorkey((255, 255, 255))  
    ballrect = ball.get_rect()
    

    #richiamo le funzioni per la costruzione e la distruzione del muro
    wall = Wall()       #distruggere
    wall.build_wall(width)      #muro

    batrect = batrect.move((width / 2) - (batrect.right / 2), height - 20)
    ballrect = ballrect.move(width / 2, height / 2)       
    lives = max_lives
    clock = pygame.time.Clock()
    #pygame.key.set_repeat(1,30)      nn dovrebbe servire cancellare   
    pygame.mouse.set_visible(0)

    #menu 
    tasto = "p"
    while True:
        #fin che non si preme P non parte il gioco.
        if tasto == "p":
            while keyboard.is_pressed("p") == False:
                screen.blit(SFONDO_MENU, (0,0))
                pygame.display.flip()
            tasto = "y"
        

        clock.tick(60)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                rm.terminate()
                rm.join()
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    rm.terminate()
                    rm.join()
                    pygame.quit()
                    sys.exit()

        acc = q.get()
        #if per capire in che senso è inclinato il microbit, <150 andrà a sinistra, >150 andrà a destra
        if (acc[0] < -150):#sinistra
            batrect = batrect.move(-bat_speed, 0)
            screen.blit(bat, batrect)
        elif (acc[0] > 150):#destra
            batrect = batrect.move(+bat_speed, 0)
            screen.blit(bat, batrect)
        q.task_done()

        #controlllo del muro sia a destra che a sinistra
        if (batrect.left < 0):                           
            batrect.left = 0
        if (batrect.right > 640):
            batrect.right = 640

        #se la palla ha toccato la piattaforma la fa rimbalzare    
        if ballrect.bottom >= batrect.top and ballrect.bottom <= batrect.bottom and ballrect.right >= batrect.left and ballrect.left <= batrect.right:
            yspeed = -yspeed                
            
        #muove con la velocità
        ballrect = ballrect.move(xspeed, yspeed)        
        if ballrect.left < 0 or ballrect.right > width:
            #modifica la velocità x facendola rimbalzare
            xspeed = -xspeed                               
        if ballrect.top < 0:
            yspeed = -yspeed                      
        

        if ballrect.top > height:
            lives -= 1
            if score > 15:
                score -= 15
            rand = random.random()                
            if random.random() > 0.5:
                xspeed = -xspeed           
            ballrect.center = width * random.random(), height / 3 #centro della palla                        
            if lives == 0:             
                screen.fill(bgcolour)
                screen.blit(GAME_OVER, (145, 50))
                fnt_score = pygame.font.SysFont("inkfree", 40)
                surf_txt_score = fnt_score.render("Score: " + str(score), True, txtcolour)
                screen.blit(surf_txt_score, (260, 420))

                pygame.display.flip()


                while True:
                    for event in pygame.event.get():
                        if event.type == pygame.QUIT:
                            rm.terminate()
                            rm.join()
                            pygame.quit()
                            sys.exit()
                        if event.type == pygame.KEYDOWN:
                            if event.key == pygame.K_ESCAPE:
                                rm.terminate()
                                rm.join()
                                pygame.quit()
                                sys.exit()
                                  
        #controllo collisione con mattone
        index = ballrect.collidelist(wall.brickrect)       
        if index != -1: 
            #ogni 100pt la velocità della pallina e dalla barra aumenterà
            if finale == 100:
                bat_speed += 2
                xspeed = abs(xspeed) + 0.7
                yspeed = abs(yspeed) + 0.7
            elif finale == 200:
                bat_speed += 2
                xspeed = abs(xspeed) + 1
                yspeed = abs(yspeed) + 1
            elif finale == 300:
                bat_speed += 2
                xspeed = abs(xspeed) + 0.7
                yspeed = abs(yspeed) + 0.7
            
            #controllo collisione e modifica rimbalzo
            if ballrect.center[0] > wall.brickrect[index].right or \
                ballrect.center[0] < wall.brickrect[index].left:     

                xspeed = -xspeed
            else:
                yspeed = -yspeed                
            #+10pt ad ogni mattoncino rotto
            wall.brickrect[index:index + 1] = []
            score += 10     

                        
        #stampa punteggio
        finale = score*lives#moltiplica il punteggio dei mattoncini con la vita 
        screen.fill(bgcolour)
        fnt_score = pygame.font.SysFont("inkfree", 30)
        surf_txt_score = fnt_score.render("Score: " + str(finale), True, txtcolour)
        screen.blit(surf_txt_score, (450, 10))

        

        #stampa vite
        fnt_lives = pygame.font.SysFont("inkfree", 30)
        surf_txt_lives = fnt_lives.render("Lives: " + str(lives), True, txtcolour)
        screen.blit(surf_txt_lives, (20, 10))

        for i in range(0, len(wall.brickrect)):
            screen.blit(wall.brick, wall.brickrect[i])    

        #controllo del muro, se non c'è si ha vinto
        if wall.brickrect == []:              
            screen.fill(bgcolour)
            screen.blit(WIN, (130, 50))
            fnt_score = pygame.font.SysFont("inkfree", 40)
            surf_txt_score = fnt_score.render("Score: " + str(finale), True, txtcolour)
            screen.blit(surf_txt_score, (260, 390))

            pygame.display.flip()
            
            while True:
                    for event in pygame.event.get():
                        if event.type == pygame.QUIT:
                            rm.terminate()
                            rm.join()
                            pygame.quit()
                            sys.exit()
                        if event.type == pygame.KEYDOWN:
                            if event.key == pygame.K_ESCAPE:
                                rm.terminate()
                                rm.join()
                                pygame.quit()
                                sys.exit()
        
        screen.blit(ball, ballrect)
        screen.blit(bat, batrect)
        pygame.display.flip()





if __name__ == '__main__':
    rm = Read_Microbit()
    rm.start()
    pygame.init()
    main()
    