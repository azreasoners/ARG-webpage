% File 'zoo-test1'

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
  jumbo                        :: elephant.

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

% The gate is closed, and Homer, an adult human, is in position 6. 
% His goal is to mount Jumbo, an adult elephant, which is in 
% position 3 and is not going to move around. How many steps are 
% required to achieve this goal?

:- sorts
  stepnum.

:- variables
  T      :: stepnum.

:- objects
  0..10  :: stepnum.

:- query 
maxstep :: 3..4;    
0: -opened(gateAO),
    pos(homer)=6;
maxstep: mounted(homer,jumbo);
T=<maxstep ->> (T: pos(jumbo)=3).

