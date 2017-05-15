pathFixture = 'C:\Users\Juan Grandoso\Desktop\matches.txt'; 
% Path segun el directorio

fixtureArchivo = fopen(pathFixture);
datos = fscanf(fixtureArchivo, '%f');

sizeDatos = size(datos);
tamanio = sizeDatos(1);

cantEquipos = datos(1); % Primer dato del archivo
cantPartidos = datos(2); 
cantFechas = 23;

A = zeros(cantEquipos);

i = 3;

for j = 1 : cantFechas
    if(i > tamanio)
       
    else
        fecha = datos(i);
    end
        while(i < tamanio && fecha == datos(i))
           posColumna = datos(i + 3); % Simboliza el 'j' rival
           posFila = datos(i + 1); % Simboliza el 'i' rival
           resultadoPartido = datos(i+2) - datos(i+4); % Por cuanto perdio el equipo 'i' contra el 'j'
           if( resultadoPartido == 0 ) % En caso de empate
               A(posColumna, posFila) = A(posColumna, posFila) + 1;
               A(posFila, posColumna) = A(posFila, posColumna) + 1;
           else
               if ( resultadoPartido < 0 ) % Rival 'i' perdio contra 'j'
                   A(posFila,posColumna) =  A(posFila,posColumna) + abs(resultadoPartido);  
               else % Rival 'j' perdio contra 'i'
                   A(posColumna,posFila) = A(posColumna,posFila) + resultadoPartido;
               end
           end
           i = i + 5;
        end
end


vectorSumaFilas = sum(transpose(A));
H = zeros(cantEquipos);

for fila = 1 : cantEquipos
    for columna = 1 : cantEquipos
        if (A(fila, columna) ~= 0)
            H(fila, columna) = A(fila, columna) / vectorSumaFilas(fila);
        end
    end
    if ( H(fila,:) == zeros(1, cantEquipos) ) % Equipo invicto
            H(fila,:) = zeros(1, cantEquipos) + (1 / cantEquipos);
    end
end

constante = 0.3;

G = (constante) * H  + (1 - constante) * (zeros( cantEquipos) + (1/ cantEquipos)) ;

%res = powerMethod(G,0.00001);


            
