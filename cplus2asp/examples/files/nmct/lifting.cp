% File 'lifting.cp'
% Lifting the Ends of the Table ("Nonmonotonic Causal Theories," Figure 7)

:- sorts
  end; height.

:- objects
  leftEnd, rightEnd    :: end;
  low, high            :: height.

:- variables
  X                    :: end.

:- constants
  level(end)           :: inertialFluent(height);
  onTable              :: inertialFluent;
  lift(end)            :: exogenousAction.

lift(X) causes level(X)=high.
nonexecutable lift(X) if level(X)=high.

caused -onTable if level(leftEnd)\=level(rightEnd).

:- query
maxstep :: 1;
0: onTable;
1: onTable.
