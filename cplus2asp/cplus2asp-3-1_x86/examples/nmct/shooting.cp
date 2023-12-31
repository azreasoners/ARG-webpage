% File 'shooting.cp'
% Shooting Turkeys ("Nonmonotonic Causal Theories," Figure 5)

:- sorts
  turkey.

 :- objects 
  turkey1, turkey2    :: turkey.

:- variables
  T                   :: turkey.

:- constants
  loaded,
  alive(turkey)       :: inertialFluent;
  target              :: inertialFluent(turkey+none); 
  load,
  shoot,
  aim(turkey)         :: exogenousAction.

aim(T) causes target=T.

load causes loaded.
load causes target=none.

shoot causes -alive(T) if target=T.
shoot causes -loaded.
nonexecutable shoot if -loaded.

noconcurrency.

:- query
maxstep :: 6;
0: alive(T),
   target=none,
   -loaded;
maxstep:
  -alive(T).
