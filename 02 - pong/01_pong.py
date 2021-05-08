import turtle
import tkinter as tk


wn = turtle.Screen()
wn.title("Ping - Pong")
wn.bgcolor("#89E8FD")
wn.setup(width=640, height=360)
wn.tracer(0)


# score
score_a = 0
score_b = 0


# papan A
papan_a = turtle.Turtle() 
papan_a.speed(0)
papan_a.shape("square")
papan_a.color("#FF5E74")
papan_a.shapesize(stretch_wid=2.5, stretch_len=0.001, outline=13)
papan_a.penup()
papan_a.goto(-290, 0)


# papan B
papan_b = turtle.Turtle() S
papan_b.speed(0)
papan_b.shape("square")
papan_b.color("#FFA051")
papan_b.shapesize(stretch_wid=2.5, stretch_len=0.001, outline=15)
papan_b.penup()
papan_b.goto(280, 0)


# bola
bola = turtle.Turtle() 
bola.speed(0)
bola.shape("circle")
bola.color("#505582")
bola.penup()
bola.goto(0, 0)
cepat = 0.3
bola.dx = cepat
bola.dy = cepat


# Pen
pen = turtle.Turtle()
pen.speed(0)
pen.color("#F8FFBC")
pen.penup()
pen.hideturtle()
pen.goto(0, 153)
pen.write("Player A:  {}    <|>    Player B:  {}".format(score_a,score_b), align="center", font=("Nirmala UI",11, "bold"))



# box
box = turtle.Turtle()
box.speed(0)
box.shape("square")
box.color("#501731")
box.shapesize(stretch_wid=0.1, stretch_len=12, outline=5)
box.penup()
box.goto(0, 179)


# function
def papan_a_up():
    y = papan_a.ycor()
    y += 30
    papan_a.sety(y)
    if (y >= 175):
        papan_a.goto(-290,140)

def papan_a_down():
    y = papan_a.ycor()
    y -= 30
    papan_a.sety(y)
    if (y <= -175):
        papan_a.goto(-290,-140)

def papan_b_up():
    y = papan_b.ycor()
    y += 30
    papan_b.sety(y)
    if (y >= 175):
        papan_b.goto(280,140)

def papan_b_down():
    y = papan_b.ycor()
    y -= 30
    papan_b.sety(y)
    if (y <= -175):
        papan_b.goto(280,-140)


# keyboard binding
wn.listen()
wn.onkeypress(papan_a_up,"w")
wn.onkeypress(papan_a_down,"s")
wn.onkeypress(papan_b_up,"Up")
wn.onkeypress(papan_b_down,"Down")


# Main game loop
while True:
    wn.update()

    # move the ball
    bola.setx(bola.xcor() + bola.dx)
    bola.sety(bola.ycor() + bola.dy)

    # border check
    if bola.ycor() > 180:
        bola.sety(180)
        bola.dy = -cepat

    elif bola.ycor() < -180:
        bola.sety(-180)
        bola.dy = cepat

    if bola.xcor() > 320:
        bola.setx(320)
        bola.goto(0,0)
        score_b += 1
        pen.clear()
        pen.write("Player A:  {}    <|>    Player B:  {}".format(score_a,score_b), align="center", font=("Nirmala UI",11, "bold"))

    elif bola.xcor() < -320:
        bola.setx(-320)
        bola.goto(0,0)
        score_a += 1
        pen.clear()
        pen.write("Player A:  {}    <|>    Player B:  {}".format(score_a,score_b), align="center", font=("Nirmala UI",11, "bold"))

    # bola bertemu papan
    if (bola.xcor() < 278 and bola.xcor() > 265) and (bola.ycor() < papan_b.ycor() + 45 and bola.ycor() > papan_b.ycor() - 45):
        bola.dx = -cepat

    if (bola.xcor() > -275 and bola.xcor() < -270) and (bola.ycor() < papan_a.ycor() + 45 and bola.ycor() > papan_a.ycor() - 45):
        bola.dx = cepat
