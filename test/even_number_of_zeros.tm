initial(Even)
state(Odd,F)
state(YES,T)
state(NO,T)
blank(B)
symbol(0,T)
symbol(1,T)
transition(Even,0,Odd,0,R)
transition(Odd,0,Even,0,R)
transition(Even,1,Even,1,R)
transition(Odd,1,Odd,1,R)
transition(Even,B,YES,B,R)
transition(Odd,B,NO,B,R)