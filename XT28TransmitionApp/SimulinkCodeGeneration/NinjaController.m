function [ outputSignal ] = NinjaController( speedError, angleError )



  outputSignal = 10 * speedError + 5 * angleError;


end

