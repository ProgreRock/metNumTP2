   tol = 0.00001;
   sizeA = size(G);
   tamanio = sizeA(1);
   % % % % % % % %
   xInicial = zeros(tamanio,1) + 9;
   xAnterior = xInicial;
   xProximo = zeros(tamanio,1);
   % % % % % % % %
   %i = 1;
   ERR = 1; %Washington  Dallas  Philadelphia  Houston  New Orleans  Carolina
   %posAutoValores = zeros(200,1);
   while(tol < ERR)
       y = transpose(G) * xAnterior;
       posAutoValor = max(abs(y));
       %posAutoValores(i) = posAutoValor;
       % % % % % % % % % % % %
       xProximo = (y/posAutoValor);
       % % % % % % % % % % % %
       prueba = xAnterior- xProximo;
       ERR =  norm(prueba,inf);
       %i = i + 1;
       xAnterior = xProximo;
   end
   res = xAnterior;
  % res = posAutoValor;

