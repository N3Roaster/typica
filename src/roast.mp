\verbatimtex
\documentclass{article}
\begin{document}
etex

beginfig(-1)

drawarrow (0,0)--(250,0);
drawarrow (0,0)--(0, 125);

%What I really want here is text rotated 90 degrees, but for some reason this causes the entire
%image to be rotated as well here.
label.lft( btex {\tt temperature} etex rotated 89, (0, 70) );

label.top( btex {\tt time} etex, (125, 0) );

draw
(0,275/4)..(30/4,195/4)..(60/4,159/4)..(90/4,155/4)..(120/4,165/4)..(180/4,195/4)..(360/4,280/4)..(420/4,300/4)..(720/4,380/4)..(900/4,440/4) withcolor red;

endfig;

end;