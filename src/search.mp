\verbatimtex
%& latex
\documentclass{article}
\begin{document}
etex

input blockdraw;

numeric u;
u := 1cm;

longblockrx := 2u;
longblockry := 0.4u;

beginfig(-1)
  picture Initialize;
  Initialize := longblock( btex {\tt Initialize} etex, (0, 0) );
  
  picture loop;
  loop := longblock( btex $n>0$? etex, (0, -2u) );
  path con;
  con := btconnect( Initialize, loop );
  
  picture success;
  success := termcircle( (5u, -1.8u) );
  con := hhconnect( rightpoint( loop, 3, 3 ), leftpoint( success, 1, 1), 0, 0.5 );
  picture lab;
  lab := conlabel( to_top, btex no etex, mspoint( con, 0.5, 0 ) );
  
  picture midpoint;
  midpoint := longblock( btex {\tt Get midpoint} etex, (0, -4u) );
  con := btconnect( loop, midpoint );
  lab := conlabel( to_lft, btex yes~ etex, mspoint( con, 0.5, 0 ) );
  
  picture compare;
  compare := longblock( btex {\tt Compare} etex, (0, -6u) );
  con := btconnect( midpoint, compare );
  
  picture lower;
  lower := longblock( btex {\tt Adjust lower bound} etex, (-5u, -4u) );
  con := lbconnect( compare, lower );
  lab := conlabel( to_top, btex $m < k$ etex, mspoint( con, 0.25, 0 ) );
  con := tlconnect( lower, loop );
  
  picture upper;
  upper := longblock( btex {\tt Adjust upper bound} etex, (5u, -4u) );
  con := rbconnect( compare, upper );
  lab := conlabel( to_top, btex $\displaystyle m \geq k$ etex, mspoint( con, 0.25, 0) );
  con := vhconnect( toppoint( upper, 1, 1 ), rightpoint( loop, 3, 1 ) );
    
endfig;
end;