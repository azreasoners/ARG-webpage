% File 'scenario2.cp'

:- macros
  maxInt -> 9;
  varsigma -> 1.

:- macros
  segNode(#1,#2,#3) -> (startNode(#1)=(#2) & endNode(#1)=(#3)).

:- objects
  a, b                 :: node;
  seg_ab               :: segment;
  car1, car2, car3     :: car.


caused segNode(seg_ab,a,b).

caused length(seg_ab)=9.

caused speedLimit(seg_ab)=3.

caused topSpeed(car1)=3.
caused topSpeed(car2)=2.
caused topSpeed(car3)=1.


% Three cars on a segment.  car1 will need to slow down twice.  First
% when it gets varsigma behind car2 and then again when car2 gets varsigma
% behind car3.
%
%           v=3         v=2               v=1
% t=0       car1        car2              car3
%            0-----1-----2-----3-----4-----5-----6-----7-----8
%
%
%
%                             v=2   v=2         v=1
% t=1                         car1  car2        car3
%            0-----1-----2-----3-----4-----5-----6-----7-----8
%
%
%
%                                         v=1   v=1   v=1
% t=2                                     car1  car2  car3
%            0-----1-----2-----3-----4-----5-----6-----7-----8


%:- show distance(C); speed(C).

:- query
label    :: 0;
maxstep  :: 3;
0: position(car1,seg_ab,0);
0: positiveOrientation(car1);
0: position(car2,seg_ab,2);
0: positiveOrientation(car2);
0: position(car3,seg_ab,5);
0: positiveOrientation(car3).


