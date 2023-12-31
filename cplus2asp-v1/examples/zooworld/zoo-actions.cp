%%% ACTIONS %%%

:- variables
  A,A1                              :: exogenousAction.

:- constants
  move(animal,position),
  open(human,gate),
  close(human,gate),
  mount(human,animal),
  getOff(human,animal,position),
  throwOff(animal,human)            :: exogenousAction.

:- macros
% Action #1 is executed by animal #2
  doneBy(#1,#2) ->
    ([\/P | #1==move(#2,P)] ++
     [\/G | #1==open(#2,G) ++ #1==close(#2,G)] ++
     [\/ANML | #1==mount(#2,ANML)] ++
     [\/ANML \/P | #1==getOff(#2,ANML,P)] ++
     [\/H | #1==throwOff(#2,H)]).

% A failed mount is not subject to the usual, rather strict, 
%  movement restriction on large animals
mount(H,ANML) causes ab(H).

% If the position a large human is thrown into was previously 
%  occupied by another large animal, the usual movement restric-
%  tion doesn't apply
throwOff(ANML,H) causes ab(H).

% Every animal can execute only one action at a time
nonexecutable A & A1 if doneBy(A,ANML1) & doneBy(A1,ANML1) 
                                              where A@<A1. 

% Direct effect of move action
move(ANML,P) causes pos(ANML)=P.

% An animal can't move to the position where it is now
nonexecutable move(ANML,V_position) if pos(ANML)=V_position.

% A human riding an animal cannot perform the move action (lmw)
nonexecutable move(H,P) if mounted(H,ANML).

% Effect of opening a gate
open(H,G) causes opened(G).

% A human cannot open a gate if he is not located at a position
%  to the side of the gate (lmw)
nonexecutable open(H,G)
           if -(pos(H)=side1(G) ++ pos(H)=side2(G)).

% A human cannot open a gate if he is mounted on an animal
nonexecutable open(H,G) if mounted(H,ANML).

% A human cannot open a gate if it is already opened
nonexecutable open(H,G) if opened(G).

% Effect of closing a gate
close(H,G) causes -opened(G).

% A human cannot close a gate if he is not located at a posi-
%  tion to the side of the gate (lmw)
nonexecutable close(H,G)
           if -(pos(H)=side1(G) ++ pos(H)=side2(G)).

% A human cannot close a gate if he is mounted on an animal
nonexecutable close(H,G) if mounted(H,ANML).

% A human cannot close a gate if it is already closed
nonexecutable close(H,G) if -opened(G).

% When a human rides an animal, his position is the same as the 
%  animal's position while the animal moves (lmw)
caused pos(H)=P if mounted(H,ANML) & pos(ANML)=P.

% If a human tries to mount an animal that doesn't change posi-
%  tion, mounting is successful
caused mounted(H,ANML) if pos(ANML)=P
                       after pos(ANML)=P & mount(H,ANML).

% The action fails if the animal changes position, and in this 
%  case the result of the action is that the human ends up in 
%  the position where the animal was (lmw)
caused pos(H)=P if pos(ANML)\=P
                after pos(ANML)=P & mount(H,ANML).

% A human already mounted on some animal cannot attempt to mount
nonexecutable mount(H,ANML) if mounted(H,ANML1).

% A human can only be mounted on a large animal
constraint mounted(H,ANML) ->> large(ANML).

% A human cannot attempt to mount a small animal (lmw)
nonexecutable mount(H,ANML) if -large(ANML).

% A large human cannot be mounted on a human
constraint mounted(H,H1) ->> -large(H).

% A large human cannot attempt to mount a human
nonexecutable mount(H,H1) if large(H).

% An animal can be mounted by at most one human at a time
constraint -(mounted(H,ANML) & mounted(H1,ANML)) where H@<H1.

% A human cannot attempt to mount an animal already mounted by
%  a human
nonexecutable mount(H,ANML) if mounted(H1,ANML).

% A human cannot be mounted on a human who is mounted
constraint -(mounted(H,H1) & mounted(H1,ANML)).

% A human cannot attempt to mount an animal if the human is 
%  already mounted by a human
nonexecutable mount(H,ANML) if mounted(H1,H).

% A human cannot attempt to mount a human who is mounted
nonexecutable mount(H,H1) if mounted(H1,ANML).

% The getOff action is successful provided that the animal does 
%  not move at the same time.  It fails if the animal moves, and
%  in this case the rider stays on the animal (lmw)
caused pos(H)=P if pos(ANML)=P1
                after pos(ANML)=P1 & getOff(H,ANML,P).

caused -mounted(H,ANML) if pos(ANML)=P1
                        after pos(ANML)=P1 & getOff(H,ANML,P).

% The action cannot be performed by a human not riding an animal
%  (lmw)
nonexecutable getOff(H,ANML,P) if -mounted(H,ANML).

% A human cannot attempt to getOff to a position that is not
%  accessible from the current position
nonexecutable getOff(H,ANML,P) if (-accessible(V_position,P) & pos(ANML)=V_position).

% The throwOff action results in the human no longer riding the 
%  animal and ending in a position adjacent to the animal's 
%  present position. It is nondeterministic since the rider may 
%  end up in any position adjacent to the animal's present posi-
%  tion (lmw)
throwOff(ANML,H) may cause pos(H)=P.
throwOff(ANML,H) causes -mounted(H,ANML).

% If the resultant position is occupied by another large animal 
%  then the human will result in riding that animal instead 
%  (lmw)
caused mounted(H,ANML1) if pos(H)=pos(ANML1) & large(ANML1)
   after throwOff(ANML,H) where H\=ANML1.

% The action cannot be performed by an animal not ridden by a 
%  human  (lmw)
nonexecutable throwOff(ANML,H) if -mounted(H,ANML).

% The actions getOff and throwOff cannot be executed 
%  concurrently
nonexecutable getOff(H,ANML,P) & throwOff(ANML,H).