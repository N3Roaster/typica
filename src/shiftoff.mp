%% shiftoff.mp
%% Copyright 2006 Henrik Tidefelt
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

numeric to_lft;
to_lft = 0;
numeric to_llft;
to_llft = 1;
numeric to_bot;
to_bot = 2;
numeric to_lrt;
to_lrt = 3;
numeric to_rt;
to_rt = 4;
numeric to_urt;
to_urt = 5;
numeric to_top;
to_top = 6;
numeric to_ulft;
to_ulft = 7;
numeric to_center;
to_center = 8;

def to_dir(expr z ) =
  if (xpart z) > 0:
    if (ypart z) > 0:
      if abs(xpart z) > 2*abs(ypart z):
	to_rt
      elseif abs(ypart z) > 2*abs(xpart z):
	to_top
      else:
	to_urt
      fi
    else:
      if abs(xpart z) > 2*abs(ypart z):
	to_rt
      elseif abs(ypart z) > 2*abs(xpart z):
	to_bot
      else:
	to_lrt
      fi
    fi
  else:
    if (ypart z) > 0:
      if abs(xpart z) > 2*abs(ypart z):
	to_lft
      elseif abs(ypart z) > 2*abs(xpart z):
	to_top
      else:
	to_ulft
      fi
    else:
      if abs(xpart z) > 2*abs(ypart z):
	to_lft
      elseif abs(ypart z) > 2*abs(xpart z):
	to_bot
      else:
	to_llft
      fi
    fi
  fi
enddef;

def dir_to(expr d ) =
  dir( 180 + d * 45 )
enddef;

def shiftoff(expr pic, corner ) =
  if corner = to_lft:
    (pic shifted ((-center pic)+((xpart llcorner pic)-(xpart center pic),0)))
  elseif corner = to_llft:
    (pic shifted ((-center pic)+(llcorner pic)-(center pic)))
  elseif corner = to_bot:
    (pic shifted ((-center pic)+(0,(ypart llcorner pic)-(ypart center pic))))
  elseif corner = to_lrt:
    (pic shifted ((-center pic)+(lrcorner pic)-(center pic)))
  elseif corner = to_rt:
    (pic shifted ((-center pic)+((xpart lrcorner pic)-(xpart center pic),0)))
  elseif corner = to_urt:
    (pic shifted ((-center pic)+(urcorner pic)-(center pic)))
  elseif corner = to_top:
    (pic shifted ((-center pic)+(0,(ypart ulcorner pic)-(ypart center pic))))
  elseif corner = to_ulft:
    (pic shifted ((-center pic)+(ulcorner pic)-(center pic)))
  else:
    (pic shifted (-center pic))
  fi
enddef;

numeric shiftofflabelmargin;
shiftofflabelmargin := bboxmargin;
def shiftoffwlm(expr pic, corner ) =
  if corner = to_lft:
    (pic shifted ((-center pic)+((xpart llcorner pic)-(xpart center pic),0)+(-shiftofflabelmargin,0)))
  elseif corner = to_llft:
    (pic shifted ((-center pic)+(llcorner pic)-(center pic)+(-shiftofflabelmargin,-shiftofflabelmargin)))
  elseif corner = to_bot:
    (pic shifted ((-center pic)+(0,(ypart llcorner pic)-(ypart center pic))+(0,-shiftofflabelmargin)))
  elseif corner = to_lrt:
    (pic shifted ((-center pic)+(lrcorner pic)-(center pic)+(shiftofflabelmargin,-shiftofflabelmargin)))
  elseif corner = to_rt:
    (pic shifted ((-center pic)+((xpart lrcorner pic)-(xpart center pic),0)+(shiftofflabelmargin,0)))
  elseif corner = to_urt:
    (pic shifted ((-center pic)+(urcorner pic)-(center pic)+(shiftofflabelmargin,shiftofflabelmargin)))
  elseif corner = to_top:
    (pic shifted ((-center pic)+(0,(ypart ulcorner pic)-(ypart center pic))+(0,shiftofflabelmargin)))
  elseif corner = to_ulft:
    (pic shifted ((-center pic)+(ulcorner pic)-(center pic)+(-shiftofflabelmargin,shiftofflabelmargin)))
  else:
    (pic shifted (-center pic))
  fi
enddef;
