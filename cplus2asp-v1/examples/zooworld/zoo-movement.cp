%%% CHANGING POSITION %%%

%:- constants
%  ab(animal) :: abAction(boolean).

:- constants
accessible(position,position)       :: sdFluent.

caused accessible(P,P1)
   if neighbor(P,P1) & -[\/G | sides(P,P1,G) & -opened(G)].
default -accessible(P,P1).

% In one unit of time, an animal can move to one of the posi-
%  tions accessible from its present one, or stay in the posi-
%  tion where it is.  Moves to non-accessible positions are 
%  never possible (lmw)
constraint pos(ANML)\=P1 
   after pos(ANML)=P & -(P=P1 ++ accessible(P,P1)).

% A concurrent move where animal A moves into a position at the 
%  same time as animal B moves out of it, is only possible if 
%  at least one of A and B is a small animal. (lmw)   
%  Exceptions for (failed) mount actions and certain occurrences
%  of throwOff -- when thrown human ends up where another large 
%  animal was (see the first two propositions in '%%% ACTIONS %%%')
constraint -(pos(ANML)=P & pos(ANML1)\=P)
   after pos(ANML)\=P & pos(ANML1)=P 
         & large(ANML) & large(ANML1) unless ab(ANML).

% Two large animals cannot pass through a gate at the same time
% (neither in the same direction nor opposite directions) (lmw)
constraint -(pos(ANML)=P1 & pos(ANML1)=P1)
   after pos(ANML)=P & pos(ANML1)=P & sides(P,P1,G)
         & large(ANML) & large(ANML1) where ANML@<ANML1.
constraint -(pos(ANML)=P & pos(ANML1)=P1)
   after pos(ANML)=P1 & pos(ANML1)=P & sides(P,P1,G)
         & large(ANML) & large(ANML1) where ANML@<ANML1.

% While a gate is closing, an animal cannot pass through it
constraint -opened(G) ->> pos(ANML)\=P1
   after pos(ANML)=P & sides(P,P1,G) & opened(G).

