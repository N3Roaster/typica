%% bondgraph.mp
%% Copyright 2007 Henrik Tidefelt
% 
% This work may be distributed and/or modified under the 
% conditions of the LaTeX Project Public License, either version 1.3 
% of this license or (at your option) any later version.
% The latest version of this license is in 
% http://www.latex-project.org/lppl.txt 
% and version 1.3 or later is part of all distributions of LaTeX 
% version 2005/12/01 or later.
% 
% This work has the LPPL maintenance status `maintained´.
% 
% The Current Maintainer of this work is Henrik Tidefelt,
% tidefelt@isy.liu.se.
% 
% This work, referred to as blockdraw.mp, consists of the files
%   shiftoff.mp
%   blockdraw.mp
%   bondgraph.mp
%   blockdraw_mp.pdf
%
%
% === Notes regarding the backward incompatible changes of 2007-01-21. ===
%
% As it was discovered that MetaPost uses the verbatimtex construct only in
% the file it appears in, it was concluded that package files cannot contain
% any content that depends on the LaTeX preamble.  In other words, any
% btex ... etex constructs must be moved from package files to the application
% sources from where the package files are included.
%
% With the definition of, say, p-junction blocks in the application source,
% it is easy to change notation from the letters "p" and "s" to the numbers
% "0" and "1".
%
% The obvious drawback, beside backward incompatibility, is that this will
% cause a lot of code replication, making bond graph source files
% less concise, and require multiple file search-and-replace actions when
% changing junction notation for a collection of graphs.  However, since
% MetaPost only allows literal character strings in the btex ... etex
% construct, these inconveniences seem impossible to work around.  Ideas,
% anyone?

input blockdraw;
implicitdraw := false;

boolean junctionimplicitdraw;
junctionimplicitdraw := true;

boolean useopenbonds;
useopenbonds := false;

connectionlw := 0.5pt;
ahlength := 3mm;
bboxmargin := 1.5mm;

def withbbmargin(expr pic ) =
  begingroup
    save tmppic;
    picture tmppic;
    tmppic = pic;
    setbounds tmppic to bbox pic;
    tmppic
  endgroup
enddef;

def junction(expr txt, z ) =
  begingroup
    save tmppic;
    picture tmppic;
    tmppic := nullpicture;
    addto tmppic also shiftoff( txt scaled textscale, to_center );
    setbounds tmppic to (-smallblockr,-smallblockr)--(-smallblockr,smallblockr)--(smallblockr,smallblockr)--(smallblockr,-smallblockr)--cycle;
    tmppic := tmppic shifted z;
    if junctionimplicitdraw:
      draw tmppic;
    fi
    tmppic
  endgroup
enddef;


def junctionlbl(expr txt, arrowdir, lbl, z, arrow ) =
  begingroup
    save tmppic, ahlength, p, d;
    ahlength := 1mm;
    path p;
    numeric d;
    picture tmppic;
    tmppic := nullpicture;
    addto tmppic also shiftoff( txt scaled textscale, to_center );

    if arrowdir = to_top:
      p := ((lrcorner tmppic)--(urcorner tmppic)) shifted ( z + (connectionlw + 2*ahlength*sind(0.5*ahangle),0) );
      d = to_rt;
    elseif arrowdir = to_lft:
      p := ((urcorner tmppic)--(ulcorner tmppic)) shifted ( z + (0,connectionlw + 2*ahlength*sind(0.5*ahangle)) );
      d = to_top;
    elseif arrowdir = to_bot:
      p := ((urcorner tmppic)--(lrcorner tmppic)) shifted ( z + (connectionlw + 2*ahlength*sind(0.5*ahangle),0) );
      d = to_rt;
    elseif arrowdir = to_rt:
      p := ((ulcorner tmppic)--(urcorner tmppic)) shifted ( z + (0,connectionlw + 2*ahlength*sind(0.5*ahangle)) );
      d = to_top;
    fi

    setbounds tmppic to (-smallblockr,-smallblockr)--(-smallblockr,smallblockr)--(smallblockr,smallblockr)--(smallblockr,-smallblockr)--cycle;
    tmppic := tmppic shifted z;

    if junctionimplicitdraw:
      if arrow:
	drawarrow p withpen pencircle scaled connectionlw;
      fi
      draw conlabel( d, lbl, mspoint( p, 0.5, 0 ) );
      draw tmppic;
    fi
    tmppic
  endgroup
enddef;

def terminal(expr d, txt, z ) =
  begingroup
    save tmppic;
    picture tmppic;
    tmppic := shiftoff( withbbmargin( txt scaled textscale ), d ) shifted ( z - smallblockr * dir_to( d ) );
    if junctionimplicitdraw:
      draw tmppic;
    fi
    tmppic
  endgroup  
enddef;

def ignorepicture(expr pic ) =
  show 0
enddef;

def terminalto(expr j, txt, z ) =
  begingroup
    ignorepicture( terminal( to_dir( z - (center j) ), txt, z ) );
    bgconnect( pointpicture( z ) , j )
  endgroup
enddef;

def terminalfr(expr j, txt, z ) =
  begingroup
    ignorepicture( terminal( to_dir( z - (center j) ), txt, z ) );
    bgconnect( j, pointpicture( z ) )
  endgroup
enddef;

def bgconnect(expr pica, picb ) =
  begingroup
    save d;
    pair d;
    if (center pica) = (center picb):
      d := (1,0);
    else:
      d := unitvector( (center picb) - (center pica) );
    fi
    ((center pica)+d*smallblockr)--((center picb)-d*smallblockr)
  endgroup
enddef;

def bond(expr p ) =
  begingroup
    save t;
    numeric t;
    t := arctime arclength(p) - ahlength of p;
    save z;
    pair z;
    z = (point t of p) + dir(angle(direction t of p)+90) * ahlength*sind(0.5*ahangle);
    save res;
    path res;
    if useopenbonds:
      draw p--z withpen pencircle scaled connectionlw
    else:
      draw p withpen pencircle scaled connectionlw;
      res = (subpath (t,infinity) of p)--z--cycle;
      filldraw res withpen pencircle scaled connectionlw
    fi
  endgroup
enddef;

def causalmark(expr p, where ) =
  begingroup
    save d;
    numeric d;
    d = angle( direction where of p );
    if where = 0:
      d := d + 180;
    fi
    save z;
    pair z;
    z = ( point where of p ) + dir(d) * connectionlw;
    save res;
    path res;
    res = (z+dir(d+90)*ahlength*sind(0.5*ahangle))--(z+dir(d-90)*ahlength*sind(0.5*ahangle));
    draw res withpen pencircle scaled (2*connectionlw)
  endgroup
enddef;

def hbond(expr p ) =
  begingroup
    bond( p );
    causalmark( p, infinity )
  endgroup
enddef;

def tbond(expr p ) =
  begingroup
    bond( p );
    causalmark( p, 0 )
  endgroup
enddef;

def flowlabel(expr p, txt ) =
%  the midpoint has typically singular direction, so we can't do the obvious:
%  draw( conlabel( to_dir( dir( angle( direction (0.5*length(p)) of p ) - 90 ) ), txt, mspoint( p, 0.5, 0 ) ) )
  draw conlabel( to_dir( dir( angle( (point infinity of p) - (point 0 of p) ) - 90 ) ), txt, mspoint( p, 0.5, 0 ) ) withpen pencircle scaled connectionlw
enddef;

def effortlabel(expr p, txt ) =
%  the midpoint has typically singular direction, so we can't do the obvious:
%  draw( conlabel( to_dir( dir( angle( direction (0.5*length(p)) of p ) + 90 ) ), txt, mspoint( p, 0.5, 0 ) ) )
  draw conlabel( to_dir( dir( angle( (point infinity of p) - (point 0 of p) ) + 90 ) ), txt, mspoint( p, 0.5, 0 ) ) withpen pencircle scaled connectionlw
enddef;
