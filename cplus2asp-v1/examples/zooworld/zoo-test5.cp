% File 'zoo-test5.cp'

:- sorts
  animal >> (elephant; horse; dog).

:- variables
  SP                           :: species;
  E                            :: elephant;
  HR                           :: horse;
  D                            :: dog.
  
:- objects
  elephantSpecies, 
  horseSpecies,
  dogSpecies                   :: species.

caused sp(E)=elephantSpecies.
constraint sp(ANML)=elephantSpecies ->> [\/E | ANML=E].

caused sp(HR)=horseSpecies.
constraint sp(ANML)=horseSpecies ->> [\/HR | ANML=HR].

caused sp(D)=dogSpecies.
constraint sp(ANML)=dogSpecies ->> [\/D | ANML=D].

default largeSpecies(SP). 
caused -largeSpecies(dogSpecies).


:- objects
  homer                        :: human;
  jumbo                        :: elephant;
  silver                       :: horse.

:- begin_asp.
#hide h(eql(accessible(_,_),_),_).
#hide h(eql(adult(_),_)).
#hide h(eql(largeSpecies(_),_)).
#hide h(eql(loc(_),_)).
#hide h(eql(neighbor(_,_),_)).
#hide h(eql(side1(_),_)).
#hide h(eql(side2(_),_)).
#hide h(eql(sides(_,_,_),_)).
#hide h(eql(sp(_),_)).
:- end_asp.

% Can a large animal move into a position at the same time as another large 
%  animal moves out of it? 
% --- Yes. Although the occupancy restriction applies within the duration 
%     of moves, there are exceptions. For instance, 
%     - If Homer is thown off into the position just vacated by the Jumbo. 

:- query
label :: 0;
maxstep :: 1;
[\/P | (0: -(pos(homer)=P)) && 
      (1: pos(homer)=P) && 
      (0: pos(jumbo)=P) && 
      (1: -(pos(jumbo)=P))];
0: mounted(homer,silver).

:- query
label :: 11;
maxstep :: 1;
0: mounted(homer,silver);
1: throwOff(silver,homer).

%     - If Homer tries to mount Jumbo while Jumbo moves out.

:- query
label :: 1; 
maxstep :: 1;
[\/P | (0: -(pos(homer)=P)) && 
      (1: pos(homer)=P) && 
      (0: pos(jumbo)=P) && 
      (1: -(pos(jumbo)=P))];
0: [/\ANML | -throwOff(ANML,homer)].


% These exceptions are not applied if the first animal is not a human. 
%  For instance, a horse, Silver, cannot move into a position at the same 
%  time as Jumbo moves out of it.

:- query
label :: 2;
maxstep :: 1;
[\/P | (0: -(pos(silver)=P)) && 
       (1: pos(silver)=P) && 
       (0: pos(jumbo)=P) && 
       (1: -(pos(jumbo)=P))].


