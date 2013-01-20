\verbatimtex
%& latex
\documentclass{article}
\begin{document}
etex

input blockdraw;

numeric u;
u := 1cm;

longblockrx := 0.9u;
longblockry := 0.4u;

beginfig( -1 )
  picture DAQ;
  DAQ := longblock( btex {\tt DAQ} etex, (-1.2u,0) );
	
  picture Channel;
  Channel := longblock( btex {\tt Channel} etex, (1.2u,0) );
    
  longblockrx := 2.7u;
  
  picture TemperatureDisplay;
  TemperatureDisplay := longblock( btex {\tt TemperatureDisplay} etex, (5.9u,1u) );
  
  picture MeasurementTimeOffset;
  MeasurementTimeOffset := longblock( btex {\tt MeasurementTimeOffset} etex, (5.9u, 0) );
  
  picture ZeroEmitter;
  ZeroEmitter := longblock(btex {\tt ZeroEmitter} etex, (5.9u, -1u) );
  
  picture ZoomLog;
  ZoomLog := longblock(btex {\tt ZoomLog} etex, (5.9u, -3u) );
    
  picture MeasurementModel;
  MeasurementModel := longblock(btex {\tt MeasurementModel} etex, (5.9u, -4.5u) );
  
  longblockrx := 2.2u;
  
  picture MeasurementAdapter;
  MeasurementAdapter := longblock( btex {\kern-1em \tt MeasurementAdapter} etex, (11.5u, 0) );
  
  picture GraphView;
  GraphView := longblock(btex {\tt GraphView} etex, (11.5u, -3u) );

  
  path con;
  picture lab;
  con := rlconnect( DAQ, Channel );
  con := rlconnect( Channel, TemperatureDisplay );
  con := rlconnect( Channel, MeasurementTimeOffset );
  con := rlconnect( MeasurementTimeOffset, MeasurementAdapter );
  con := rlconnect( Channel, ZeroEmitter );
  con := btconnect( ZeroEmitter, ZoomLog );
  con := btconnect( ZeroEmitter, GraphView );
  con := btconnect( MeasurementAdapter, GraphView );
  con := btconnect( ZoomLog, MeasurementModel );
	
endfig;
end;
